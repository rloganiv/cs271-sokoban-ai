//
//  graph.h
//  cs271-sokoban-ai
//
//  Created by dalal alharthi on 1/27/1438 AH.
//  Copyright © 1438 dalal alharthi. All rights reserved.
//

//Graph Structure (the legality of movements)


#ifndef graph_h
#define graph_h
#include "state.h"
#include <vector>

class Graph
{
public:
    
    Graph(){};
    Graph (State *s); //constructor
    std::vector<Coord> getNeighbors(int x, int y);
    
private:
    State * state;
    
};




#endif /* graph_h */
