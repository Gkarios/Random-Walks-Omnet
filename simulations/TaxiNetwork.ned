package randomw.simulations;

import randomw.Node;
import randomw.Host;

network TaxiNetwork
{
        parameters:
        int numNodes = default(145); // <-- will be set to actual number of Placemarks
        double rc = default(0.2);   // radius for connectivity
        double rcLong = default(1946); // for long-range connectivity
        int sinkNode = default(0) @mutable;
        int startNode = default(11);
           @display("bgb=6000,6000");
        bool enableDuplication = default(false) @mutable;
        bool noBacktracking = default(false) @mutable;
        int numWalkers = default(1);
    submodules:
        node[numNodes]: Node;
        host: Host;
   
    connections allowunconnected:
        for i=0..numNodes-1, for j=i+1..numNodes-1 {
            node[i].port++ <--> {@display("ls=green,1"); } <--> node[j].port++
                if i!=j &&
                   sqrt((node[i].xCor - node[j].xCor)^2 + (node[i].yCor - node[j].yCor)^2)
                   < ((i == 74 || i == 97 || i == 127) ? rcLong : rc);
        }
    
}
