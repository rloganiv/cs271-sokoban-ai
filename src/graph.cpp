//
//  graph.cpp
//  cs271-sokoban-ai
//
//  Created by dalal alharthi on 1/27/1438 AH.
//  Copyright © 1438 dalal alharthi. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include "graph.h"
#include "state.h"


/* TODO - recompute the neighbor values and store into hash table/map */

Graph::Graph(State *s)
{
    state = s;
    /*
    for(int x = 0; x < state::width; x++)
        for(int y = 0; y < state::height; y++)
            table.insert(new Coord(x, y), computeNeighbors(x,y));
     */
}


// hash table < Coord, <vector <Coord> >

// getNeighbors then returns table.get( new Coord(x, y))

std::vector<Coord> Graph::getNeighborsOfType(Coord c, Tile type){
    int x = c.x;
    int y = c.y;
    std::vector <Coord> result;
    Coord up, down, left, right;
    left.x = x-1;
    left.y = y;
    right.x = x+1;
    right.y = y;
    up.x = x;
    up.y = y-1;
    down.x = x;
    down.y = y+1;

    if( x > 0 && state->get_tile(x-1, y) == type){
       result.push_back(left);
    }

    if(x < State::width - 1 && state->get_tile(x+1, y) == type){
       result.push_back(right);
        }

    if(y > 0 && state->get_tile(x, y-1) == type)
        result.push_back(up);

    if(y < State::height - 1 && state->get_tile(x, y+1) == type)
        result.push_back(down);


       return result;

}

std::vector<Coord> Graph::getNeighbors (int x, int y)
{
    std::vector <Coord> result;
    Coord up, down, left, right;
    left.x = x-1;
    left.y = y;
    right.x = x+1;
    right.y = y;
    up.x = x;
    up.y = y-1;
    down.x = x;
    down.y = y+1;

    if( x > 0 && state->get_tile(x-1, y) != WALL){
       result.push_back(left);
    }

    if(x < State::width - 1 && state->get_tile(x+1, y) != WALL){
       result.push_back(right);
        }

    if(y > 0 && state->get_tile(x, y-1) != WALL)
        result.push_back(up);

    if(y < State::height - 1 && state->get_tile(x, y+1) != WALL)
        result.push_back(down);


       return result;
}
