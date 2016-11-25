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
#include <set>
#include <climits>
#include <cstdlib>
#include "assignmentsolver.h"
#include <iostream>

/******************************************

    SMALLER VALUES ARE BETTER. 0 means solved.


 ******************************************/

/***** K stands for constants *****/
struct K {
    /* Hard code constants for now. Refactor into HeuristicParams class and dependency inject
       if enough time */

    static const int NEXT_TO_BLOCK_BONUS = -10;
    static const int GOAL_SCORE_SCALE = 2;

    // Large value to indicate this is an unsolvable situation
    static const int IMMOVABLE_BONUS = 100000;


    static const int BLOCK_UNPUSHABLE_BONUS = 8;

    // To introduce greater granularity, a single manhattan distance
    // in the right direction is scaled to STEP_SCALE
    static const int STEP_SCALE = 100;

    static const int PLAYER_NOT_CLOSE_TO_BLOCK_MULTIPLIER = 3;

    static const int * PLAYER_CLOSE_TO_BLOCK_BONUS;

} ;



class Heuristic {
public:

    Heuristic();

    /*** Currently only bbsolver is available ***/
    Heuristic(State *s, AssignmentSolver * assign_solver);


    ~Heuristic();

    /*** This is the main evaluate routine ***/

    int evaluate(State &s);

    /*** ---------------------------------- ***/

    int next_to_block_bonus(State &s);
    int unpushable_bonus(State &s);

    int player_pos_bonus(State &s);


    // Please Robby try to push these into your State class or write your own
    std::vector<Coord> get_locations(State &s, Tile type);

    bool is_wall_unpushable(State & s, Coord block);

    bool is_block_unpushable(State &s, Coord block);
    inline bool is_obstruction(State &s, Tile t) {
        return t == WALL || t== BOX;
    }

    inline int quick_dist_approx(Coord a, Coord b){
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    }

    int player_to_block_dist(State &s);

    int * unmovabilty_deg;

    void gen_um_deg();
    void gen_um_deg_ex(State &s, int deg);

    int goal_score(State &s, Coord goal);

    int manhattan_dist_score(State &s);
    inline Coord make_coord(int x, int y){ Coord p; p.x = x; p.y = y; return p;}

    void print_unmovability_table();

private:
    std::vector<ManhattanDist> block_dist;

    State * init_state;
    AssignmentSolver * assign_solver;
    Graph graph;

    int unmovabilty_default;

    std::vector<Coord> init_goals;

    inline int get_unmovability_deg(Coord c){
        return unmovabilty_deg[c.y * State::width + c.x];
    }


};

#endif /* heuristic_h */
