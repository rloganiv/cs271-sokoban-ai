#ifndef STATE_H
#define STATE_H

enum Tile {
    EMPTY,
    WALL,
    BOX,
    GOAL,
    GOALBOX,
    PLAYER
};

struct Coord {
    int x = -1;
    int y = -1;
};

class State {
    public:
        // Initialize a board of EMPTY tiles
        State(int w, int h);

        // Copy constructor
        State(const State& b);

        // Ensure that the tiles array is removed from the heap when we are
        // done
        ~State();

        // State dimensions
        const int width;
        const int height;

        // Player position
        Coord player;

        // Tile getters and setters
        void set_tile(int x, int y, Tile val);
        Tile get_tile(int x, int y);

        // Print function for debugging
        void print();

    private:
        // Array of board tiles
        Tile* tiles;
};

#endif
