//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#ifndef __RANDOMW_HOST_H_
#define __RANDOMW_HOST_H_

#include <omnetpp.h>
#include "RandomWalkerMsg_m.h"

using namespace omnetpp;

class Host : public cSimpleModule {
public:
  virtual int getStartNodeIndex() const;

protected:
  virtual void initialize(int stage);
  virtual int numInitStages() const { return 3; }
  virtual void handleMessage(cMessage *msg) override;
  virtual void finish() override;
//   virtual void finish();

  // std::map<std::pair<int, int>, double> linkWeights;
  // virtual void handleMessage(cMessage *msg) override;

private:
  RandomWalkerMsg *lastWalkerMsg = nullptr;
  cTopology topo;
  int startNode;
  int startNodeIndex;

  // cTopology::Node* parentNode = nullptr;
};

#endif
