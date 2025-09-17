#ifndef __RANDOMW_HOST_H_
#define __RANDOMW_HOST_H_

#include <omnetpp.h>
#include "RandomWalkerMsg_m.h"

using namespace omnetpp;

class Host : public cSimpleModule {
public:
  int startNodeIndex;
protected:
  virtual void initialize(int stage);
  virtual int numInitStages() const { return 3; }
  virtual void handleMessage(cMessage *msg) override;
  virtual void finish() override;

private:
  RandomWalkerMsg *lastWalkerMsg = nullptr;
  cTopology topo;
  int startNode;
};

#endif
