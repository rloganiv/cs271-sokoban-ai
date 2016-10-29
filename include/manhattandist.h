//
//  manhattandist.h
//  cs271-sokoban-ai
//
//  Created by dalal alharthi on 1/27/1438 AH.
//  Copyright © 1438 dalal alharthi. All rights reserved.
//

//Implement wavefront algorithm

#ifndef manhattandist_h
#define manhattandist_h

#include <stdio.h>
#include <vector>
#include "graph.h"
#include "state.h"

class ManhattanDist
{
public:
    ManhattanDist (Graph &g, Coord goal); //constructor
    ~ManhattanDist ();
    
    int getDist(int x, int y) {return dist[State::width * y + x];}
    
    Coord getGoal() { return goal;}
    Graph getGraph() {return graph;}
    static const int NOT_VISITED = -1;
private:
    Graph graph;
    Coord goal;
    
    int * dist;
    
    void computeDist(); // wavefront
    
};

#endif /* manhattandist_h */
