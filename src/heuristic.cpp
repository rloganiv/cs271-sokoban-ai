//
//  heuristic.cpp
//  cs271-sokoban-ai
//
//  Created by dalal alharthi on 2/2/1438 AH.
//  Copyright © 1438 dalal alharthi. All rights reserved.
//

#include "graph.h"
#include "state.h"
#include "heuristic.h"
#include "manhattandist.h"
#include <cstdlib>
#include <iostream>

Heuristic :: Heuristic (State * s)
{
    init_state = s;
    
    std::vector<Coord> init_goals = get_locations(*init_state, GOAL);
    block_dist.reserve(init_goals.size());
    
    for(int i = 0; i < init_goals.size(); i++)
    {
        Graph g(init_state);
        graph = g;
        ManhattanDist d(graph, init_goals[i]);  //assumes the ordering of the goals is consistent
        block_dist.push_back(d);
        
    }
    
    
}

int Heuristic::unpushable_bonus(State &s){
    std::vector<Coord> blocks = get_locations(s, BOX);
    
    int wallUnpushableCount = 0;
    
    // int blockUnpushableCount = 0;  TODO impelment block unpushable
    
    for(int i = 0; i < blocks.size(); i++){
        int x = blocks[i].x;
        int y = blocks[i].y;
        
        Tile left = s.get_tile(x-1, y);
        Tile right = s.get_tile(x+1, y);
        Tile up = s.get_tile(x, y-1);
        Tile down = s.get_tile(x, y+1);
        
        // Strongly unpushable due to walls
        if((s.get_tile(x, y) != GOALBOX) &&
           ((left == WALL && up == WALL) ||
           (up == WALL && right == WALL) ||
           (right == WALL && down == WALL) ||
           (down == WALL && left == WALL))){
            wallUnpushableCount++;
        }
        
    }
    
    return wallUnpushableCount > 0 ? UNPUSHABLE_BONUS : 0;
}

int Heuristic::next_to_block_bonus(State &s){
    Coord player = s.player;
    std::vector<Coord> neighbors = graph.getNeighbors(player.x, player.y);
    
    int result = 0;
    
    for(int i = 0; i < neighbors.size(); i++)
    {
        Coord n = neighbors[i];
        if(s.get_tile(n.x, n.y)== BOX)
        {
            result += NEXT_TO_BLOCK_BONUS;
            return result;
        }
    }
    

    return result;
}


int Heuristic::one_step_reduction_bonus(State &s){
    Coord player = s.player;
    std::vector<Coord> neighbors = graph.getNeighbors(player.x, player.y);
    
    int result = 0;
    
    for(int i = 0; i < neighbors.size(); i++)
    {
        Coord n = neighbors[i];
        if(s.get_tile(n.x, n.y)== BOX)
        {
            int dx = n.x - player.x;
            int dy = n.y - player.y;
            
            int currentDist = max_manhattan_dist(n);
            
            Coord n_next;
            n_next.x = n.x + dx;
            n_next.y = n.y + dy;
            
            int nextDist = max_manhattan_dist(n_next);
            
            if(nextDist < currentDist)
                result += ONE_STEP_REDUCTION_BONUS;
            return result;
        }
    }
    
    
    return result;
}

// This should be provided efficiently in O(1) in State class
std::vector<Coord> Heuristic::get_locations( State &s, Tile type){

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

int Heuristic::max_manhattan_dist(Coord box){
    int result = -99;
    
    for(int i =0; i < block_dist.size(); i++){
        int value = block_dist[i].getDist(box.x, box.y);
        if(value > result)
            result = value;
    }
    
    return result;
}
// Currently uses sum of maximums. Can solve the assignment problem
// later by changing to Greedy Approximation, Hungarian Agorithm, QuickMatch, Klein's Algorithm,
// or Auction Algorithm if time permits. Factor out into assignment
// problem class for now.
int Heuristic::manhattan_dist_score(State &s){
    std::vector<Coord> blocks = get_locations(s, BOX);
    
    int result = INT_MAX;
    
    /*
        If needed later:
     
        Cost matrix should be computed as engine is traversing nodes via the search
        and efficiently updated. Evaluate function should take an EvalInfo object containing
        useful information for the eval function like costMatrix, player dist to nearest goal,
        block locations, etc...
     
     
     
        AssignmentSolver solver(costMatrix)
        return solver.minCost();
     
     */
    
    for(int i = 0; i < blocks.size(); i++){
        result += max_manhattan_dist(blocks[i]);
    }
    
    
    return result;
    
}

int Heuristic::evaluate(State &s){
    int unpushable = unpushable_bonus(s);
    
    
    
    return unpushable < 0 ?
            unpushable :
            manhattan_dist_score(s) * 100 + one_step_reduction_bonus(s)  + next_to_block_bonus(s);
}

