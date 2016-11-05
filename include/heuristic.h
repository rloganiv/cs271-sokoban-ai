//
//  heuristic.hpp
//  cs271-sokoban-ai
//
//  Created by dalal alharthi on 2/2/1438 AH.
//  Copyright © 1438 dalal alharthi. All rights reserved.
//

#ifndef heuristic_h
#define heuristic_h

#include <stdio.h>
#include "graph.h"
#include "state.h"
#include "manhattandist.h"
#include <map>
#include <climits>



class Heuristic {
public:
    
    
    /* Hard code constants for now. Refactor into HeuristicParams class and dependency inject
       if enough time */
    
    const static int NEXT_TO_BLOCK_BONUS = 50;
    const static int ONE_STEP_REDUCTION_BONUS = 50;
    const static int UNPUSHABLE_BONUS = INT_MIN;
    
    
    Heuristic();
    Heuristic(State *s);
    int evaluate(State &s);
    
    int next_to_block_bonus(State &s);
    int one_step_reduction_bonus(State &s);
    int unpushable_bonus(State &s);
    
    // Please Robby try to push these into your State class or write your own
    std::vector<Coord> get_locations(State &s, Tile type);
    
    // The manhattan_dist of this box location to farthest goal
    int max_manhattan_dist(Coord box);
    
    
    
    int manhattan_dist_score(State &s);
    
private:
    std::vector<ManhattanDist> block_dist;
    
    State * init_state;
    Graph graph;
    
    
    
    

};

#endif /* heuristic_h */
