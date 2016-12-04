#include "state.h"
#include <iostream>
#include <algorithm>

// Declaring and initializing board width and height - defaults to 0
int State::width;
int State::height;

// Initializing board width and height based on parameters
void State::initDimensions(int w, int h)
{
	State::width = w;
	State::height = h;
}


State::State()
{
    tiles = new Tile[width * height];
    for (int x=0; x < width; x++) {
        for (int y=0; y < height; y++) {
            tiles[x + y*width] = EMPTY;
        }
    }
}

State::State(const State& b)
{
    tiles = new Tile[width * height];
    for (int i=0; i<width*height; i++){
        tiles[i] = b.tiles[i];
    }
    player = b.player;
}

State::~State() {
    //delete [] tiles;
}

bool State::operator==(const State& b) const {
    if (player.x != b.player.x) return false;
    if (player.y != b.player.y) return false;
    for (int x=0; x < width; x++){
        for (int y=0; y < height; y++){
            if (get_tile(x, y) != b.get_tile(x, y)) return false;
        }
    }
    return true;
}

void State::set_tile(int x, int y, Tile val) {
    tiles[x + width*y] = val;
}

Tile State::get_tile(int x, int y) const {
    return tiles[x + width*y];
}

const char* format(Tile t){
    switch(t) {
        case EMPTY: return " ";
        case WALL: return "#";
        case BOX: return "$";
        case GOAL: return ".";
        case GOALBOX: return "*";
        case PLAYER: return "@";
    }
}
void State::print() {
    using namespace std;
    Tile old_state = get_tile(player.x, player.y);
    set_tile(player.x, player.y, PLAYER);
    for (int y=0; y < height; y++) {
        for (int x=0; x < width; x++) {
            cout << format(get_tile(x, y)) << " ";
        }
        cout << endl;
    }
    set_tile(player.x, player.y, old_state);
}


size_t StateHasher::operator() (const State &state) const {
    std::string s;
    std::stringstream stream;
    for (int x=0; x < state.width; x++){
        for (int y=0; y < state.height; y++){
            stream << state.get_tile(x, y);
        }
    }
    stream << state.player.x;
    stream << state.player.y;
    s = stream.str();
    return std::hash<std::string>()(s);
}
