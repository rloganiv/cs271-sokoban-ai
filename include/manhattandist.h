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
#include <algorithm>

class ManhattanDist
{
public:
    ManhattanDist (Graph &g, Coord goal); //constructor
    
    ManhattanDist (const ManhattanDist & other): // Copy constructor
        graph(other.graph),
        goal(other.goal),
        dist(new int[State::width * State::height])
    {
        std::copy(other.dist, other.dist + (State::width * State::height), dist);
    }
    
    
    // Copy swap idiom from StackOverflow
    friend void swap(ManhattanDist& first, ManhattanDist& second) // nothrow
    {
        using std::swap;
        
        // by swapping the members of two objects,
        // the two objects are effectively swapped
        swap(first.goal, second.goal);
        swap(first.graph, second.graph);
        swap(first.dist, second.dist);
    }
    
    ManhattanDist & operator =(ManhattanDist & other){
        ManhattanDist temp(other);
        swap(*this, temp);
        return *this;
    }
    
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
