#include "Node.h"
#include "Host.h"

Define_Module(Node);

// Initialization of static members
std::vector<bool> Node::visited;
std::vector<int> Node::visitedPerTimestep;
bool Node::globalAllVisited = false;
int Node::numWalkers = 0;
int Node::walkersMovedThisStep = 0;
int Node::timestep = 0;

void Node::initialize(int stage) {
    if (stage == 0) {
        int numNodes = getParentModule()->par("numNodes").intValue();
        visitedVector.setName("visitedPerTimestep");
        if ((int)visited.size() != numNodes) {
            visited.assign(numNodes, false);
            globalAllVisited = false;
        }
        visitedPerTimestep.clear();
        visitedPerTimestep.push_back(0); // Start with timestep 0, 0 nodes visited
    }
    if (stage == 1) {
        numWalkers = par("numWalkers").intValue();
        cModule *hostModule = getParentModule()->getSubmodule("host");
        if (!hostModule)
            throw cRuntimeError("Host module not found!");

        int startNodeIndex = 0; // Always start from node 0
        if (getIndex() == startNodeIndex) {
            for (int i = 0; i < numWalkers; ++i) {
                startRandomWalker(i);
            }
        }
    }
}

void Node::handleMessage(cMessage *msg) {
    RandomWalkerMsg *rwMsg = check_and_cast<RandomWalkerMsg *>(msg);

    int nodeId = getIndex();
    if (!visited[nodeId]) {
        visited[nodeId] = true;
        getDisplayString().setTagArg("i", 1, "red"); // Color node red when visited
    }

    // Add to path (per walker)
    int pathLen = rwMsg->getPathArraySize();
    rwMsg->setPathArraySize(pathLen + 1);
    rwMsg->setPath(pathLen, nodeId);

    // Add to visitedNodes (per walker, for their own record)
    int visitedLen = rwMsg->getVisitedNodesArraySize();
    bool alreadyVisited = false;
    for (int i = 0; i < visitedLen; i++) {
        if (rwMsg->getVisitedNodes(i) == nodeId) {
            alreadyVisited = true;
            break;
        }
    }
    if (!alreadyVisited) {
        rwMsg->setVisitedNodesArraySize(visitedLen + 1);
        rwMsg->setVisitedNodes(visitedLen, nodeId);
    }

    // Increment walkersMovedThisStep
    walkersMovedThisStep++;

    // Only increment timestep and record data when all walkers have moved
    if (walkersMovedThisStep == numWalkers) {
        timestep++;
        walkersMovedThisStep = 0;

        // Record unique nodes visited at this timestep (shared)
        int uniqueVisited = std::count(visited.begin(), visited.end(), true);
        visitedPerTimestep.push_back(uniqueVisited);
        visitedVector.record(uniqueVisited);
    }

    // Stop when all nodes have been visited (shared between the RWs)
    int numNodes = getParentModule()->par("numNodes").intValue();
    int uniqueVisited = std::count(visited.begin(), visited.end(), true);
    if (!globalAllVisited && uniqueVisited >= numNodes) {
        globalAllVisited = true;
    }
    if (globalAllVisited) {
        // Copy per-timestep data into the message
        rwMsg->setVisitedPerHopArraySize(visitedPerTimestep.size());
        for (size_t i = 0; i < visitedPerTimestep.size(); ++i)
            rwMsg->setVisitedPerHop(i, visitedPerTimestep[i]);

        cModule *hostModule = getParentModule()->getSubmodule("host");
        if (hostModule) {
            sendDirect(rwMsg, hostModule, "directIn");
        } else {
            EV << "Host module not found!" << endl;
            delete rwMsg;
        }
    } else {
        sendToRandomNeighbor(rwMsg);
    }
}

void Node::sendToRandomNeighbor(RandomWalkerMsg *msg) {
    int n = gateSize("port");
    if (n > 0) {
        int neighbor = intuniform(0, n - 1);
        send(msg, "port$o", neighbor);
        EV << "Sent randomWalkerMsg to neighbor at gate index " << neighbor << endl;
    } else {
        EV << "No neighbors to send to!" << endl;
        delete msg;
    }
}

void Node::startRandomWalker(int walkerId) {
    RandomWalkerMsg *msg = new RandomWalkerMsg("randomWalkerMsg");
    msg->setPathArraySize(1);
    msg->setPath(0, getIndex());
    msg->setVisitedNodesArraySize(1);
    msg->setVisitedNodes(0, getIndex());
    msg->setHopCountr(0);
    msg->setVisitedPerHopArraySize(1);
    msg->setVisitedPerHop(0, 1); // Only itself visited at hop 0
    msg->setWalkerId(walkerId);  // Add this field in your .msg file if you want to distinguish walkers

    sendToRandomNeighbor(msg);
}
