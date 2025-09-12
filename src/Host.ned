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

package randomw;

//
// TODO auto-generated module
//
simple Host
{
    parameters:
		int startNodeIndex = default(-1) @mutable;
        int startNode = default(11);
    	@display("i=abstract/penguin;is=vs;p=0,0");
        @name("Host");
    gates:
        input directIn; // Direct input gate for receiving messages from nodes
}
