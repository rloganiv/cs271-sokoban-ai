#include "problem.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <iostream>

/* str_to_ivec
 *      Converts a string into a vector of integers. This function helps parse
 *      the data from the problem specification files.
 */
std::vector<int> str_to_ivec(std::string *input_string) {
    using namespace std;
    istringstream stream(*input_string);
    vector<int> out(istream_iterator<int>(stream), {});
    return out;
}


/* to_coords
 *      Converts a vector of ints to a vector of Coords.
 */
std::vector<Coord> to_coords(std::vector<int> ivec) {
    std::vector<Coord> out;
    for (int i = 1; i < ivec.size(); i=i+2){
        Coord temp;
        temp.x = ivec[i+1];
        temp.y = ivec[i];
        out.push_back(temp);
    }
    return out;
}

/* place_tiles
 *      Given a line of coordinates from the input file, overwrites the
 *      corresponding tiles in state with val.
 */
void place_tiles(std::vector<Coord> coords, State* state, Tile val) {
    using namespace std;
    // Need to handle exceptions for when a box is placed on a goal & vice
    // versa.
    switch (val) {
        case BOX:
            for (auto const& coord: coords) {
                if (state->get_tile(coord.x-1, coord.y-1) == GOAL) {
                    state->set_tile(coord.x-1, coord.y-1, GOALBOX);
                } else {
                    state->set_tile(coord.x-1, coord.y-1, val);
                }
            }
            break;
        case GOAL:
            for (auto const& coord: coords) {
                if (state->get_tile(coord.x-1, coord.y-1) == BOX) {
                    state->set_tile(coord.x-1, coord.y-1, GOALBOX);
                } else {
                    state->set_tile(coord.x-1, coord.y-1, val);
                }
            }
            break;
        default:
            for (auto const& coord: coords) {
                state->set_tile(coord.x-1, coord.y-1, val);
            }
    }
}

Problem::Problem(std::string filename) {
    using namespace std;

    ifstream input_file(filename.c_str());
    string line;

    // Get board dimensions from first line of file
    getline(input_file, line);
    vector<int> dim = str_to_ivec(&line);

    // Initialize  board dimensions
    State::initDimensions(dim[0], dim[1]);

    State* temp_state = new State();

    // Place walls
    getline(input_file, line);
    vector<int> walls = str_to_ivec(&line);
    wall_coords = to_coords(walls);
    place_tiles(wall_coords, temp_state, WALL);

    // Place boxes
    getline(input_file, line);
    vector<int> boxes = str_to_ivec(&line);
    vector<Coord> box_coords = to_coords(boxes);
    place_tiles(box_coords, temp_state, BOX);

    // Place and store goals
    getline(input_file, line);
    vector<int> goals = str_to_ivec(&line);
    goal_coords = to_coords(goals);
    place_tiles(goal_coords, temp_state, GOAL);

    // Get player coordinates
    getline(input_file, line);
    vector<int> player_coords = str_to_ivec(&line);
    temp_state->player.x = player_coords[1] - 1;
    temp_state->player.y = player_coords[0] - 1;

    deadlock_arr = get_simple_deadlocks(temp_state);
    cout << "Printing simple deadlock array" << endl;
    for (int i=0; i<temp_state->height; i++){
        for (int j=0; j<temp_state->width; j++){
            cout << deadlock_arr[i*temp_state->width + j] << " " ;
        }
        cout << endl;
    }
    init_state = temp_state;
}

/* can_move
 *      Returns true if player can move into near.
 */
bool can_move(Tile near, Tile far) {
    if (near == EMPTY || near == GOAL) {
        return true;
    }
    else if (
        (near == BOX || near == GOALBOX) && (far == EMPTY || far == GOAL)
    ) {
        return true;
    }
    else {
        return false;
    }
}

std::vector<Action> Problem::valid_actions(State *state){
    using namespace std;
    vector<Action> actions;
    int x = state->player.x;
    int y = state->player.y;
    int width = state->width;
    bool is_push;
    Tile near, far;
    State temp;

    // Check if player can move up
    near = state->get_tile(x, y - 1);
    far = state->get_tile(x, y - 2);
    is_push = (near == BOX) || (near == GOALBOX);

    // If player is not pushing & can move then add action
    if (!is_push && can_move(near, far))
        actions.push_back(UP);
    // If player is pushing do deadlock and freeze check
    else if (!deadlock_arr[x + (y - 2) * width] && can_move(near, far)){
        Coord to;
        to.x = x; to.y = y - 2;
        temp = result(state, UP);
        if (!freeze_check(&temp, deadlock_arr, to)){
            actions.push_back(UP);
        }
    }

    // Check if player can move down
    near = state->get_tile(x, y + 1);
    far = state->get_tile(x, y + 2);
    is_push = (near == BOX) || (near == GOALBOX);

    // If player is not pushing & can move then add action
    if (!is_push && can_move(near, far))
        actions.push_back(DOWN);
    // If player is pushing do deadlock and freeze check
    else if (!deadlock_arr[x + (y + 2) * width] && can_move(near, far)){
        Coord to;
        to.x = x; to.y = y + 2;
        temp = result(state, DOWN);
        if (!freeze_check(&temp, deadlock_arr, to)){
            actions.push_back(DOWN);
        }
    }

    // Check if player can move left
    near = state->get_tile(x - 1, y);
    far = state->get_tile(x - 2, y);
    is_push = (near == BOX) || (near == GOALBOX);

    // If player is not pushing & can move then add action
    if (!is_push && can_move(near, far))
        actions.push_back(LEFT);
    // If player is pushing do deadlock and freeze check
    else if (!deadlock_arr[x - 2 + y * width] && can_move(near, far)){
        Coord to;
        to.x = x - 2; to.y = y;
        temp = result(state, LEFT);
        if (!freeze_check(&temp, deadlock_arr, to)){
            actions.push_back(LEFT);
        }
    }

    // Check if player can move right
    near = state->get_tile(x + 1, y);
    far = state->get_tile(x + 2, y);
    is_push = (near == BOX) || (near == GOALBOX);

    // If player is not pushing & can move then add action
    if (!is_push && can_move(near, far))
        actions.push_back(RIGHT);
    // If player is pushing do deadlock and freeze check
    else if (!deadlock_arr[x + 2 + y * width] && can_move(near, far)){
        Coord to;
        to.x = x + 2; to.y = y;
        temp = result(state, RIGHT);
        if (!freeze_check(&temp, deadlock_arr, to)){
            actions.push_back(RIGHT);
        }
    }

    return actions;
}

State Problem::result(State *state, Action action) {
    using namespace std;

    // Initialize result state to be a copy of source state
    State result_state = *state;

    int x = state->player.x;
    int y = state->player.y;

    // Look at tiles involved with action
    Tile near, far;
    int dx = 0;
    int dy = 0;
    switch (action) {
        case UP:
            dy = -1;
            break;
        case DOWN:
            dy = 1;
            break;
        case LEFT:
            dx = -1;
            break;
        case RIGHT:
            dx = 1;
            break;
    }
    near = state->get_tile(x + dx, y + dy);
    far = state->get_tile(x + 2*dx, y + 2*dy);

    // Perform action
    if (can_move(near, far)) {
        // Move player
        result_state.player.x = x + dx;
        result_state.player.y = y + dy;

        // Move box
        switch (near) {
            case BOX:
                result_state.set_tile(x + dx, y + dy, EMPTY);
                switch (far) {
                    case EMPTY:
                        result_state.set_tile(x + 2*dx, y + 2*dy, BOX);
                        break;
                    case GOAL:
                        result_state.set_tile(x + 2*dx, y + 2*dy, GOALBOX);
                        break;
                }

                break;
            case GOALBOX:
                result_state.set_tile(x + dx, y + dy, GOAL);
                switch (far) {
                    case EMPTY:
                        result_state.set_tile(x + 2*dx, y + 2*dy, BOX);
                        break;
                    case GOAL:
                        result_state.set_tile(x + 2*dx, y + 2*dy, GOALBOX);
                        break;
                }

                break;
        }
    }

    return result_state;
}

bool Problem::goal_test(State *state) {
    for (auto const& coord: goal_coords) {
        if (state->get_tile(coord.x-1, coord.y-1) != GOALBOX) {
            return false;
        }
    }
    return true;
}

// Getters
State* Problem::get_init_state(){ return init_state; }
std::vector<Coord> Problem::get_wall_coords(){ return wall_coords; }
std::vector<Coord> Problem::get_goal_coords(){ return goal_coords; }
