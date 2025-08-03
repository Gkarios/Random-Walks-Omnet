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

network GridNet
{
        parameters:
		int numNodes = default(25);
        double rc = default(1.1); //0.5
        int sinkNode @mutable = default(0);
        int startNode = default(11);
        int numWalkers = default(1);
        @display("bgb=4,4");
    submodules:
        node[5*5]: Node {
            parameters:
                xCor = int(index % 5);
                yCor = int(index / 5);
        }
        host: Host;
    connections allowunconnected:
        for i=0..numNodes-1, for j=i+1..numNodes-1 {
            node[i].port++ <--> {@display("ls=green,1"); } <--> node[j].port++ if i!=j && sqrt((node[i].xCor - node[j].xCor)^2+(node[i].yCor - node[j].yCor)^2)<rc;
        }
    
}
