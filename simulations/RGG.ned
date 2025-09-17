package randomw.simulations;

import randomw.Node;
import randomw.Host;

network RGG
{
    parameters:
        int numNodes = default(25);
        double rc = default(0.2);
        @display("bgb=1,1");
        bool enableDuplication = default(false) @mutable;
        bool noBacktracking = default(false) @mutable;
        int numWalkers = default(1);
    submodules:
        node[numNodes]: Node;
        host: Host;
    connections allowunconnected:
        for i=0..numNodes-1, for j=i+1..numNodes-1 {
            node[i].port++ <--> {@display("ls=green,1"); } <--> 
            node[j].port++ if i!=j && sqrt((node[i].xCor - node[j].xCor)^2+(node[i].yCor - node[j].yCor)^2)<rc;
        }
}
