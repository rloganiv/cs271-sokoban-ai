#include "deadlock.h"

std::vector<Coord> get_goal_coords(State *s){
    std::vector<Coord> out;
    Tile temp_tile;
    for (int i=0; i<s->width; i++){
        for (int j=0; j<s->height; j++){
            temp_tile = s->get_tile(i, j);
            if ((temp_tile == GOAL)||(temp_tile == GOALBOX)){
                Coord temp_coord;
                temp_coord.x = i;
                temp_coord.y = j;
                out.push_back(temp_coord);
            }
        }
    }
    return out;
}


State clear_blocks(State* s){
    State out = *s;
    Tile temp_tile;
    for (int i=0; i<out.width; i++){
        for (int j=0; j<out.height; j++){
            if (out.get_tile(i, j) == BOX){
                out.set_tile(i, j, EMPTY);
            }
            if (out.get_tile(i, j) == GOALBOX){
                out.set_tile(i, j, GOAL);
            }
        }
    }
    out.player.x = -1;
    out.player.y = -1;
    return out;
}

bool* get_simple_deadlocks(State* s){
    std::vector<Coord> goal_coords = get_goal_coords(s);
    int height = s->height;
    int width = s->width;

    State cleared = clear_blocks(s);
    bool* deadlock_arr = new bool[height * width];
    for (int i=0; i<height*width; i++) deadlock_arr[i]=true; // assume deadlocked

    for (auto const& coord : goal_coords){
        bool* temp = new bool[height * width];
        for (int i=0; i<height*width; i++) temp[i]=true;

        std::queue<Coord> frontier;
        frontier.push(coord);

        while (!frontier.empty()){
            Coord current = frontier.front();
            Tile near, far;

            frontier.pop();
            temp[current.x + width*current.y]=false;

            if ((current.x > 1) && temp[current.x - 1 + current.y * width] ){
                near = cleared.get_tile(current.x - 1, current.y);
                far = cleared.get_tile(current.x - 2, current.y);
                if ((near != WALL)&&(far != WALL)) {
                    Coord next = current;
                    next.x -= 1;
                    frontier.push(next);
                }
            }
            if (current.x < (width - 1) && temp[current.x + 1 + current.y * width] ){
                near = cleared.get_tile(current.x + 1, current.y);
                far = cleared.get_tile(current.x + 2, current.y);
                if ((near != WALL)&&(far != WALL)) {
                    Coord next = current;
                    next.x += 1;
                    frontier.push(next);
                }
            }
            if (current.y > 1 && temp[current.x + (current.y - 1) * width] ){
                near = cleared.get_tile(current.x, current.y - 1);
                far = cleared.get_tile(current.x, current.y - 2);
                if ((near != WALL)&&(far != WALL)) {
                    Coord next = current;
                    next.y -= 1;
                    frontier.push(next);
                }
            }
            if (current.y < (height - 1) && temp[current.x + (current.y + 1) * width] ){
                near = cleared.get_tile(current.x, current.y + 1);
                far = cleared.get_tile(current.x, current.y + 2);
                if ((near != WALL)&&(far != WALL)) {
                    Coord next = current;
                    next.y += 1;
                    frontier.push(next);
                }
            }
        }

        for (int i=0; i<height*width; i++){
            if (!temp[i]) deadlock_arr[i]=false;
        }
    }

    return deadlock_arr;
}
