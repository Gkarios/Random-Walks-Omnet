#include "Host.h"
#include <fstream>

Define_Module(Host);

void Host::initialize(int stage) {
  if (stage == 0) {
    topo.extractByProperty("node");

    // Get the number of nodes from omnetpp.ini
    int numNodes = getParentModule()->par("numNodes").intValue();

    // Pick a random starting node index for the Random Walker 
    int randomNodeIndex = intuniform(0, numNodes - 1);

    cTopology::Node *randomNode = topo.getNode(randomNodeIndex);
    if (randomNode) {
      startNodeIndex = 4;// randomNodeIndex;
      EV << "Randomly selected start node: " << randomNode->getModule()->getFullName()
         << " with index: " << startNodeIndex << endl;
    } else {
      throw cRuntimeError("No node found for random index: %d", randomNodeIndex);
    }
  }
}

void Host::handleMessage(cMessage *msg) {
  lastWalkerMsg = check_and_cast<RandomWalkerMsg *>(msg);
}

int Host::getStartNodeIndex() const{
  return startNodeIndex;
}

void Host::finish() {
    if (lastWalkerMsg) {
        std::ofstream out("prints/data/unique_visited_nodes.txt", std::ios::out | std::ios::trunc);
        if (out.is_open()) {
            int m = lastWalkerMsg->getVisitedPerHopArraySize();
            for (int i = 0; i < m; ++i)
                out << i << "," << lastWalkerMsg->getVisitedPerHop(i) << std::endl;
            out.close();
        } else {
            EV << "Could not open file for writing unique visited nodes.\n";
        }
    }
}