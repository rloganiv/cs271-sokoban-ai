#include "board.h"

Board::Board(int w, int h)
: width(w), height(h)
{
    tiles = new Tile[width * height];
    for (int x=0; x < width; x++) {
        for (int y=0; y < height; y++) {
            tiles[x + y*width] = EMPTY;
        }
    }
}

Board::~Board() {
    delete [] tiles;
}

void Board::set_tile(int x, int y, Tile val) {
    tiles[x + width*y] = val;
}

Tile Board::get_tile(int x, int y) {
    return tiles[x + width*y];
}
