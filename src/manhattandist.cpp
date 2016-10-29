//
//  manhattandist.cpp
//  cs271-sokoban-ai
//
//  Created by dalal alharthi on 1/27/1438 AH.
//  Copyright © 1438 dalal alharthi. All rights reserved.
//

#include "manhattandist.h"
#include <iostream>
#include <vector>
#include <queue>
#include "graph.h"
#include "state.h"

ManhattanDist :: ManhattanDist (Graph &g, Coord goal){
    graph = g;
    this->goal = goal;
    
    computeDist();
}

ManhattanDist :: ~ManhattanDist(){
    delete [] dist;
}

//Implement wavefront algorithm

void ManhattanDist :: computeDist(){
    size_t len = State::height * State::width;
    dist = new int [len];
  
    // Initialize all the squares to -1 (NOT_VISITED)
    for (int i=0 ; i < len; i++) {
        dist [i] = NOT_VISITED;
    }
    std::queue <Coord> fringe;
    fringe.push (goal);
    
    int d = 0;
    while (!fringe.empty ())
    {
        std::queue<Coord> newFringe;
        
        while (!fringe.empty ()){
            Coord c = fringe.front ();
            fringe.pop();
            
            if(dist[c.y * State::width + c.x] >= 0)
                continue;
            
            dist [c.y * State::width + c.x] = d;
            
            std::vector <Coord> neighbors = graph.getNeighbors (c.x, c.y);
            
            for (int i=0; i< neighbors.size (); i++) {
                Coord n = neighbors [i];
                if (dist[n.y * State::width + n.x] == NOT_VISITED)
                    newFringe.push (n);
            }
        }
        
        
        fringe = newFringe;
        d++;
    }
    
    // implement wavefront
}
