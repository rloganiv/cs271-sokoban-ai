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
        State();

        // Copy constructor
        State(const State& b);

        // Ensure that the tiles array is removed from the heap when we are
        // done
        ~State();

        // Board dimensions - same for all states
        static int width;
        static int height;

        // Player position
        Coord player;

        // Tile getters and setters
        void set_tile(int x, int y, Tile val);
        Tile get_tile(int x, int y);

        // Print function for debugging
        void print();
	
	// Function to initialize board dimensions
	 static void initDimensions(int w, int h);

    private:
        // Array of board tiles
        Tile* tiles;
};

#endif
