#include "Host.h"
#include <fstream>

Define_Module(Host);

void Host::initialize(int stage) {
  if (stage == 0) {
    topo.extractByProperty("node");
    int numNodes = getParentModule()->par("numNodes").intValue();

    int randomNodeIndex = intuniform(0, numNodes - 1); //or a fixed value for comparisons
    cTopology::Node *randomNode = topo.getNode(randomNodeIndex);
    if (randomNode) {
      // write value into the Host's parameter table
      par("startNodeIndex").setIntValue(randomNodeIndex);

      EV << "Randomly selected start node: " << randomNode->getModule()->getFullName()
         << " with index: " << par("startNodeIndex").intValue() << endl;
    } else {
      throw cRuntimeError("No node found for random index: %d", randomNodeIndex);
    }
  }
}

void Host::handleMessage(cMessage *msg) {
    if (lastWalkerMsg)
        delete lastWalkerMsg;
    lastWalkerMsg = check_and_cast<RandomWalkerMsg *>(msg);
}

void Host::finish() {
    if (lastWalkerMsg) {
        int runNumber = getSimulation()->getActiveEnvir()->getConfigEx()->getActiveRunNumber();
        std::string filename = "prints/data/qtcmd/unique_visited_nodes_run" + std::to_string(runNumber) + ".txt";
        std::ofstream out(filename, std::ios::out | std::ios::trunc);
        if (out.is_open()) {
            int m = lastWalkerMsg->getVisitedPerHopArraySize();
            for (int i = 0; i < m; ++i)
                out << i << "," << lastWalkerMsg->getVisitedPerHop(i) << std::endl;
            out.close();
        } else {
            EV << "Could not open file for writing unique visited nodes.\n";
        }
        delete lastWalkerMsg;
        lastWalkerMsg = nullptr;
    }
}