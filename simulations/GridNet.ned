package randomw.simulations;

import randomw.Node;
import randomw.Host;

network GridNet
{
        parameters:
		int numNodes = default(25);
        double rc = default(1.1); //0.5
        int numWalkers = default(1);
        bool enableDuplication = default(false);
        bool disableBacktracking = default(false);
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
            node[i].port++ <--> {@display("ls=green,1"); } <--> 
            node[j].port++ if i!=j && sqrt((node[i].xCor - node[j].xCor)^2+(node[i].yCor - node[j].yCor)^2)<rc;
        }
    
}
