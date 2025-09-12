#include "Node.h"
#include "Host.h"

Define_Module(Node);

// Initialization of static members
std::vector<bool> Node::visited;
std::vector<int> Node::visitedPerTimestep;
bool Node::enableDuplication = false;
bool Node::disableBacktracking = false;
bool Node::globalAllVisited = false;
int Node::numWalkers = 0;
int Node::walkersMovedThisStep = 0;
int Node::duplicationInterval = 1000;
int Node::walkerIdCounter = 100000; 
int Node::timestep = 0;

void Node::initialize(int stage) {
    if (stage == 0) {
        //fetch values
        int numNodes = getParentModule()->par("numNodes").intValue();
        enableDuplication = getParentModule()->par("enableDuplication").boolValue();
        disableBacktracking = getParentModule()->par("disableBacktracking").boolValue();
        //initialize the static data
        visited.assign(numNodes, false);
        globalAllVisited = false;
        visitedPerTimestep.clear();
        visitedPerTimestep.push_back(0); // To start with [timestep, nodes] =  [0, 0] 
    }
    if (stage == 1) {
        numWalkers = getParentModule()->par("numWalkers").intValue();
        cModule *hostModule = getParentModule()->getSubmodule("host");
        if (!hostModule)
            throw cRuntimeError("Host module not found!");

        int startNodeIndex = hostModule->par("startNodeIndex").intValue();
        if (getIndex() == startNodeIndex) {
            for (int i = 0; i < numWalkers; ++i) {
                startRandomWalker(i);
                EV << "I'm starting node" << getIndex() << " and I started walker " << i << endl;
            }
        }
    }
}

void Node::handleMessage(cMessage *msg) {
    RandomWalkerMsg *rwMsg = check_and_cast<RandomWalkerMsg *>(msg);

    int nodeId = getIndex();
    if (!visited[nodeId]) {
        visited[nodeId] = true;
        getDisplayString().setTagArg("i", 1, "red");
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
        EV << "Timestep incremented to " << timestep << endl;
        walkersMovedThisStep = 0;
        int uniqueVisited = std::count(visited.begin(), visited.end(), true);

        // Record the number of visited nodes at this timestep
        visitedPerTimestep.push_back(uniqueVisited);

        // Stop when all nodes have been visited (shared between the RWs)
        int numNodes = getParentModule()->par("numNodes").intValue();
        if (!globalAllVisited && uniqueVisited >= numNodes) {
            globalAllVisited = true;
        }
    }

    duplicateWalker(rwMsg);

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
        int neighborGateIdx;
        if (disableBacktracking && msg->getPathArraySize() > 1) {
            int prevNode = msg->getPath(msg->getPathArraySize() - 2);
            std::vector<int> candidates;
            for (int i = 0; i < n; ++i) {
                cGate *outGate = gate("port$o", i);
                cGate *inGate = outGate->getNextGate();
                if (inGate) {
                    cModule *neighborMod = inGate->getOwnerModule();
                    int neighborNodeIdx = neighborMod->getIndex();
                    if (neighborNodeIdx != prevNode)
                        candidates.push_back(i);
                }
            }
            if (!candidates.empty()) {
                neighborGateIdx = candidates[intuniform(0, candidates.size() - 1)];
            } else {
                neighborGateIdx = intuniform(0, n - 1); // fallback: no choice but to backtrack
            }
        } else {
            neighborGateIdx = intuniform(0, n - 1);
        }
        send(msg, "port$o", neighborGateIdx);
        EV << "Sent randomWalkerMsg to neighbor at gate index " << neighborGateIdx << endl;
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

void Node::triggerWalkerDuplication() {
    // Only the node(s) currently holding a walker will execute this
    // Each walker duplicates itself

    int currentDupRound = (duplicationInterval > 0) ? (timestep / duplicationInterval) : -1;

    RandomWalkerMsg *dupMsg = new RandomWalkerMsg("randomWalkerMsg");
    dupMsg->setPathArraySize(1);
    dupMsg->setPath(0, getIndex());
    dupMsg->setVisitedNodesArraySize(1);
    dupMsg->setVisitedNodes(0, getIndex());
    dupMsg->setHopCountr(0);
    dupMsg->setVisitedPerHopArraySize(1);
    dupMsg->setVisitedPerHop(0, 1);
    dupMsg->setWalkerId(walkerIdCounter++);
    dupMsg->setLastDuplicationRound(currentDupRound); // <-- Set to current round!

    sendToRandomNeighbor(dupMsg);

    numWalkers++;
}

void Node::duplicateWalker(RandomWalkerMsg *rwMsg) {
    if (!enableDuplication)
        return;

    int currentDupRound = (duplicationInterval > 0) ? (timestep / duplicationInterval) : -1;
    if (!globalAllVisited && duplicationInterval > 0 && timestep > 0 && timestep % duplicationInterval == 0 &&
        rwMsg->getLastDuplicationRound() < currentDupRound) {
        rwMsg->setLastDuplicationRound(currentDupRound);
        triggerWalkerDuplication();
    }
}

void Node::finish() {
    EV << "number of walkers at the end of the simulation were:" << numWalkers << endl;
}