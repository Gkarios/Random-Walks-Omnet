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
network GridNet
{
    parameters:
        int gridSize = default(5); // 5x5 grid
        @display("bgb=500,500");
    submodules:
        node[gridSize*gridSize]: Node {
            parameters:
                xCor = int(index % gridSize);
                yCor = int(index / gridSize);
        }
        host: Host;
    connections allowunconnected:
        // Connect each node to its 4 neighbors (up, down, left, right)
        for i=0..gridSize*gridSize-1 {
            // right neighbor
            if ((i+1) % gridSize != 0)
                node[i].port++ <--> node[i+1].port++;
            // down neighbor
            if (i + gridSize < gridSize*gridSize)
                node[i].port++ <--> node[i+gridSize].port++;
        }
}
