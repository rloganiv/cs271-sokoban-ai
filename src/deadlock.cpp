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

bool freeze_check(State *s, bool* deadlock_arr, Coord coord){
    State check = *s;

    std::queue<Coord> check_coords;
    check_coords.push(coord);
    int width = check.width;
    while (!check_coords.empty())
    {
        Coord front = check_coords.front();
        check_coords.pop();
        int x = front.x;
        int y = front.y;

        Tile c, u, d, l ,r;
        c = check.get_tile(front.x, front.y);
        u = check.get_tile(front.x, front.y - 1);
        d = check.get_tile(front.x, front.y + 1);
        l = check.get_tile(front.x - 1, front.y);
        r = check.get_tile(front.x + 1, front.y);

        if (c == GOALBOX) // If box is on a goal then freeze cannot be detected
        {
            return false;
        }
        else
        {
            bool lr1 = (l == WALL) || (r == WALL);
            bool lr2 = deadlock_arr[x + 1 + width*y] && deadlock_arr[x - 1 + width*y];
            bool lr3 = (l == BOX) || (r == BOX);
            bool ud1 = (u == WALL) || (d == WALL);
            bool ud2 = deadlock_arr[x + width*(y+1)] && deadlock_arr[x + width*(y-1)];
            bool ud3 = (u == BOX) || (d == BOX);

            if ((lr1 || lr2)&&(ud1 || ud2)){
                return true;
            } else {
                check.set_tile(x, y, WALL);
            }
            if (u==BOX && (lr1 || lr2 || lr3)){
                Coord temp;
                temp.x = x;
                temp.y = y - 1;
                check_coords.push(temp);
            }
            if (d==BOX && (lr1 || lr2 || lr3)){
                Coord temp;
                temp.x = x;
                temp.y = y + 1;
                check_coords.push(temp);
            }
            if (l==BOX && (ud1 || ud2 || ud3)){
                Coord temp;
                temp.x = x - 1;
                temp.y = y;
                check_coords.push(temp);
            }
            if (r==BOX && (ud1 || ud2 || ud3)){
                Coord temp;
                temp.x = x + 1;
                temp.y = y;
                check_coords.push(temp);
            }
        }
    }
    return false;
}
