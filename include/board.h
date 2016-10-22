#ifndef BOARD_H
#define BOARD_H

enum Tile {
    EMPTY,
    WALL,
    BOX,
    GOAL,
    GOALBOX
};

class Board {
    public:
        // Initialize a board of EMPTY tiles
        Board(int w, int h);

        // Ensure that the tiles array is removed from the heap when we are
        // done
        ~Board();

        // Board dimensions
        const int width;
        const int height;

        // Get and set tiles
        void set_tile(int x, int y, Tile val);
        Tile get_tile(int x, int y);

    private:
        // Array of board tiles
        Tile* tiles;
};

#endif
