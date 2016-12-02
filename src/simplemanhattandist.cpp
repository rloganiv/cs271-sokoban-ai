//
//  SimpleManhattanDist.cpp
//  Final
//
//  Created by dalal alharthi on 3/3/1438 AH.
//  Copyright © 1438 dalal alharthi. All rights reserved.
//

#include "assignmentsolver.h"
#include "state.h"
#include "simplemanhattandist.h"
#include <vector>

SimpleManhattanDist::SimpleManhattanDist(AssignmentSolver * s) : solver(s) {}


// This should be provided efficiently in O(1) in State class
std::vector<Coord> get_locations( State &s, Tile type){
    
    std::vector<Coord> result;
    for (int y=0; y < State::height ; y++){
        for (int x = 0; x < State::width; x++)
        {
            if(s.get_tile (x,y) == type){
                Coord c;
                c.x= x;
                c.y=y;
                result.push_back(c);
            }
        }
    }
    
    return result;
    
}

int SimpleManhattanDist::evaluate(State &s){
    
    std::vector<Coord> blocks = get_locations(s, BOX);
    std::vector<Coord> goals = get_locations(s, GOAL);
    
    int N = (int)blocks.size();
    int ** costMatrix = new int * [N];
    
    for(int i = 0; i < N; i++)
        costMatrix[i] = new int[N];
    
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
        {
            costMatrix[i][j] = quick_dist_approx(blocks[i], goals[j]);
        }
    
    solver->setCostMatrix(costMatrix, N);
    return solver->minCost();
    
}
