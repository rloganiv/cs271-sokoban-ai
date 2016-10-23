#include "state.h"
#include <iostream>
#include <algorithm>

State::State(int w, int h)
: width(w), height(h)
{
    tiles = new Tile[width * height];
    for (int x=0; x < width; x++) {
        for (int y=0; y < height; y++) {
            tiles[x + y*width] = EMPTY;
        }
    }
}

State::State(const State& b)
: width(b.width), height(b.height)
{
    tiles = new Tile[width * height];
    for (int i=0; i<width*height; i++){
        tiles[i] = b.tiles[i];
    }
    player = b.player;
}

State::~State() {
    delete [] tiles;
}

void State::set_tile(int x, int y, Tile val) {
    tiles[x + width*y] = val;
}

Tile State::get_tile(int x, int y) {
    return tiles[x + width*y];
}

void State::print() {
    using namespace std;
    Tile old_state = get_tile(player.x, player.y);
    set_tile(player.x, player.y, PLAYER);
    for (int y=0; y < height; y++) {
        for (int x=0; x < width; x++) {
            cout << get_tile(x, y) << " ";
        }
        cout << endl;
    }
    set_tile(player.x, player.y, old_state);
}
