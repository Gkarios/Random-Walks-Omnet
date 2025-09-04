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

package randomw.simulations;

import randomw.Node;
import randomw.Host;

network RGG
{
    parameters:
        int numNodes = default(25);
        double rc = default(0.2);
        int sinkNode = default(0) @mutable;
        int startNode = default(11);
        @display("bgb=1,1");
        bool enableDuplication = default(false) @mutable; // Enable walker duplication
        bool disableBacktracking = default(false) @mutable; // Disable backtracking for walkers
        int numWalkers = default(1);
    submodules:
        node[numNodes]: Node;
        host: Host;
    connections allowunconnected:
        for i=0..numNodes-1, for j=i+1..numNodes-1 {
            node[i].port++ <--> {@display("ls=green,1"); } <--> node[j].port++ if i!=j && sqrt((node[i].xCor - node[j].xCor)^2+(node[i].yCor - node[j].yCor)^2)<rc;
        } //Euclidean distance is supposed to calculate is 2 nodes are in the radius
}
