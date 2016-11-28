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

/* place_tiles
 *      Given a line of coordinates from the input file, overwrites the
 *      corresponding tiles in state with val.
 */
void place_tiles(std::vector<int> coords, State* state, Tile val) {
    using namespace std;
    int n = coords[0];
    // Need to handle exceptions for when a box is placed on a goal & vice
    // versa.
    switch (val) {
        case BOX:
            for (int i=1; i < 2*n; i = i+2) {
                if (state->get_tile(coords[i+1]-1, coords[i]-1) == GOAL) {
                    state->set_tile(coords[i+1]-1, coords[i]-1, GOALBOX);
                } else {
                    state->set_tile(coords[i+1]-1, coords[i]-1, val);
                }
            }
            break;
        case GOAL:
            for (int i=1; i < 2*n; i = i+2) {
                if (state->get_tile(coords[i+1]-1, coords[i]-1) == BOX) {
                    state->set_tile(coords[i+1]-1, coords[i]-1, GOALBOX);
                } else {
                    state->set_tile(coords[i+1]-1, coords[i]-1, val);
                }
            }
            break;
        default:
            for (int i=1; i < 2*n; i = i+2) {
                state->set_tile(coords[i+1]-1, coords[i]-1, val);
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
    vector<int> wall_coords = str_to_ivec(&line);
    place_tiles(wall_coords, temp_state, WALL);

    // Place boxes
    getline(input_file, line);
    vector<int> box_coords = str_to_ivec(&line);
    place_tiles(box_coords, temp_state, BOX);

    // Place and store goals
    getline(input_file, line);
    goal_coords = str_to_ivec(&line);
    place_tiles(goal_coords, temp_state, GOAL);

    // Get player coordinates
    getline(input_file, line);
    vector<int> player_coords = str_to_ivec(&line);
    temp_state->player.x = player_coords[0] - 1;
    temp_state->player.y = player_coords[1] - 1;

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
    Tile near, far;

    // Check if player can move up
    near = state->get_tile(x, y - 1);
    far = state->get_tile(x, y - 2);
    if (can_move(near, far)) { actions.push_back(UP); }

    // Check if player can move down
    near = state->get_tile(x, y + 1);
    far = state->get_tile(x, y + 2);
    if (can_move(near, far)) { actions.push_back(DOWN); }

    // Check if player can move left
    near = state->get_tile(x - 1, y);
    far = state->get_tile(x - 2, y);
    if (can_move(near, far)) { actions.push_back(LEFT); }

    // Check if player can move right
    near = state->get_tile(x + 1, y);
    far = state->get_tile(x + 2, y);
    if (can_move(near, far)) { actions.push_back(RIGHT); }

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
    int n = goal_coords[0];
    for (int i=1; i < 2*n; i = i+1) {
        if (state->get_tile(goal_coords[i+1]-1, goal_coords[i]-1) != GOALBOX) {
            return false;
        }
    }
    return true;
}

State* Problem::get_init_state() {
    return init_state;
}
