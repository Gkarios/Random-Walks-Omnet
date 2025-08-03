message RandomWalkerMsg{
    int hopCountr = 0;
    int path[];
    int visitedNodes[];
    int visitedPerHop[];
    int walkerId = -1;
    int lastDuplicationRound = -1;
}