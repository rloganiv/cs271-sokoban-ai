#include "deadlock.h"

bool* get_deadlocks(State* s){
    int height = s->height;
    int width = s->width;
    bool val = false;
    bool* deadlock_arr = new bool[height * width];
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            // Level boundary is always deadlocked
            if (i==0 || i==(height-1) || j==0 || j==(width-1))
            {
                val = true;
            }
            else
            {
                Tile up = s->get_tile(j, i+1);
                Tile down = s->get_tile(j, i-1);
                Tile left = s->get_tile(j-1, i);
                Tile right = s->get_tile(j+1, i);
                Tile center = s->get_tile(j, i);
                bool vblock = (up == WALL) || (down == WALL);
                bool hblock = (left == WALL) || (right == WALL);
                bool goal_center = (center == GOAL || center == GOALBOX);
                val = vblock && hblock && !goal_center;
            }
            deadlock_arr[i*width + j] = val;
        }
    }
    return deadlock_arr;
}
