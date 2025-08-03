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
simple Node
{
    parameters:
        double sendInterval = default(1.0);
        double xCor = default(0.0);
        double yCor = default(0.0);
        double packetLength = default(127); //bytes
        double bitrate = default(250000); //bps
        double initialEnergy = default(1000);
        bool isSink = default(false) @mutable;
        double ackTransmissionEnergyConsumption = default(0.0) @mutable; //An ack will deplete a proportion of the 
        double distanceToSink = default(0.0) @mutable; //distance to sink
        int duplicationInterval = default(100) @mutable; // Interval for walker duplication


        
        @display("p=$xCor,$yCor;i=block/process;is=vs;");
        @node;
    gates:
        inout port[];
        input radioIn @directIn;
}
