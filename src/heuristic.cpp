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


static const int K_PLAYER_CLOSE_TO_BLOCK_BONUS[] = {-12, -10, -8, -4, 0 };
const int * K::PLAYER_CLOSE_TO_BLOCK_BONUS = K_PLAYER_CLOSE_TO_BLOCK_BONUS;

Heuristic :: Heuristic (State * s, AssignmentSolver * assign_solver)
{
    init_state = s;
    this->assign_solver = assign_solver;
    init_goals = get_locations(*init_state, GOAL);
    unmovabilty_default = init_goals.size();
    block_dist.reserve(init_goals.size());

    for(unsigned int i = 0; i < init_goals.size(); i++)
    {
        Graph g(init_state);
        graph = g;
        ManhattanDist d(graph, init_goals[i]);  //assumes the ordering of the goals is consistent
        block_dist.push_back(d);

    }

    gen_um_deg();

}

Heuristic :: ~Heuristic(){
    delete [] unmovabilty_deg;
}

/*
    Generates the degree of unmovability of a given coord.
    If it is_wall_unpushable then the result 0. Then all the
    wall unpushables are turned into walls and the same procedure
    repeated via the helper gen_um_deg_ex.

*/
void Heuristic::gen_um_deg(){
    State copy_state(*init_state);

    unmovabilty_deg = new int[State::width*State::height];
    for(int i = 0; i < State::width * State::height; i++)
        unmovabilty_deg[i] = unmovabilty_default;


    for(unsigned int d = 0; d < init_goals.size(); d++){
        gen_um_deg_ex(copy_state, d);
    }

}

/*
    Does the actual heavy lifting in generating the unmovability_deg table

 */
void Heuristic::gen_um_deg_ex(State &s, int degree){
    std::vector<Coord> changes;
    for(int y=0; y < State::height; y++)
        for(int x=0; x< State::width; x++){

            if(unmovabilty_deg[y*State::width + x] == unmovabilty_default &&
               is_wall_unpushable(s, make_coord(x,y))){


                unmovabilty_deg[y*State::width + x] = degree;
                changes.push_back(make_coord(x, y));

            }
        }

    std::vector<Coord>::iterator it;
    for(it = changes.begin(); it!= changes.end(); it++){
        s.set_tile(it->x, it->y, WALL);
    }
}


/*
  A box is block unpushable if it is not wall unpushable and there are obstructions
  on two adjacent sides
*/

bool Heuristic::is_block_unpushable(State &s, Coord block){
    if (is_wall_unpushable(s, block))
        return false;

    int x = block.x;
    int y = block.y;

    Tile left = s.get_tile(x-1, y);
    Tile right = s.get_tile(x+1, y);
    Tile up = s.get_tile(x, y-1);
    Tile down = s.get_tile(x, y+1);

    return  (is_obstruction(s, left) && is_obstruction(s, up)) ||
             (is_obstruction(s, up) && is_obstruction(s, right)) ||
              (is_obstruction(s, right) && is_obstruction(s, down)) ||
               (is_obstruction(s, down) && is_obstruction(s, left));
}

bool Heuristic::is_wall_unpushable(State &s, Coord block){
    int x = block.x;
    int y = block.y;

    Tile left = s.get_tile(x-1, y);
    Tile right = s.get_tile(x+1, y);
    Tile up = s.get_tile(x, y-1);
    Tile down = s.get_tile(x, y+1);

    // Strongly unpushable due to walls
    return
       ((left == WALL && up == WALL) ||
        (up == WALL && right == WALL) ||
        (right == WALL && down == WALL) ||
        (down == WALL && left == WALL));

}



int Heuristic::unpushable_bonus(State &s){
    std::vector<Coord> blocks = get_locations(s, BOX);

    int wall_unpushable_count = 0;

    int block_unpushable_count = 0;

    for(unsigned int i = 0; i < blocks.size(); i++){
        if(s.get_tile(blocks[i].x, blocks[i].y) != GOALBOX &&
           get_unmovability_deg(blocks[i]) == 0)
            wall_unpushable_count++;

        if(s.get_tile(blocks[i].x, blocks[i].y) != GOALBOX && is_block_unpushable(s, blocks[i]))
            block_unpushable_count++;
    }

    if( wall_unpushable_count > 0) return K::IMMOVABLE_BONUS;
    if( block_unpushable_count > 0) return K::BLOCK_UNPUSHABLE_BONUS;
    return 0;
}

int Heuristic::next_to_block_bonus(State &s){
    Coord player = s.player;
    std::vector<Coord> neighbors = graph.getNeighbors(player.x, player.y);

    for(unsigned int i = 0; i < neighbors.size(); i++){
        Coord n = neighbors[i];

        if(s.get_tile(n.x, n.y)== BOX)
            return K::NEXT_TO_BLOCK_BONUS;
    }

    return 0;
}

int Heuristic::goal_score(State &s, Coord goal){
    // If the goal is occupied, return 0;
    if(s.get_tile(goal.x, goal.y) == GOALBOX)
        return 0;

    int um_deg = get_unmovability_deg(goal);
    return unmovabilty_default - um_deg;
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


/********************************************

    Finds the optimum pairing of goals to boxes based on cost matrix

*********************************************/
int Heuristic::manhattan_dist_score(State &s){
    std::vector<Coord> blocks = get_locations(s, BOX);

    int ** costMatrix = new int *[blocks.size()];
    for(unsigned int i = 0; i < blocks.size(); i++){
        costMatrix[i] = new int[blocks.size()];
    }

    for(unsigned int i = 0; i < blocks.size(); i++)
        for(unsigned int j = 0; j < blocks.size(); j++){
            costMatrix[i][j] =
              K::STEP_SCALE * block_dist[j].getDist(blocks[i].x, blocks[i].y)
              - K::GOAL_SCORE_SCALE * goal_score(s, init_goals[j]);
            costMatrix[i][j] = std::max(costMatrix[i][j], 0);
        }



    assign_solver->setCostMatrix(costMatrix, blocks.size());

    int result = assign_solver->minCost();

    for(unsigned int i = 0; i < blocks.size(); i++)
        delete [] costMatrix[i];

    delete [] costMatrix;
    return result;
}

void Heuristic::print_unmovability_table(){
    for(int y = 0; y < State::height; y++){
        for(int x = 0; x < State::width; x++)
            std::cout << get_unmovability_deg(make_coord(x, y)) << " ";
        std::cout << std::endl;
    }


}

int Heuristic::player_to_block_dist(State &s){
    std::vector<Coord> blocks = get_locations(s, BOX);
    int min = INT_MAX;
    for(unsigned int i = 0; i < blocks.size(); i++){
        int value = quick_dist_approx(s.player, blocks[i]);
        if(value < min)
            min = value;
    }
    return min;
}

int Heuristic::player_pos_bonus(State & s){
    int player_pos_bonus = 0;

    int d = player_to_block_dist(s);

    if(d <= 5)
        player_pos_bonus = K::PLAYER_CLOSE_TO_BLOCK_BONUS[d-1];
    else
        player_pos_bonus = d * K::PLAYER_NOT_CLOSE_TO_BLOCK_MULTIPLIER;

    return player_pos_bonus;
}

int Heuristic::evaluate(State &s){

    int man_dist_score = manhattan_dist_score(s);

    // Solved. This should only happen if all the blocks are on goals
    if(man_dist_score <= 0) return 0;

    int unpushable_score = unpushable_bonus(s);

    int player_pos_score = player_pos_bonus(s);

    return man_dist_score +
           unpushable_score +
           player_pos_score;
}

