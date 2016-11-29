#ifndef STATE_H
#define STATE_H

#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>

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

        // Equivalence operator
        bool operator==(const State& b) const;

        // Board dimensions - same for all states
        static int width;
        static int height;

        // Player position
        Coord player;

        // Tile getters and setters
        void set_tile(int x, int y, Tile val);
        Tile get_tile(int x, int y) const;

        // Print function for debugging
        void print();

	// Function to initialize board dimensions
	static void initDimensions(int w, int h);

    private:
        // Array of board tiles
        Tile* tiles;
};

// State hashing function
//  Convert the tile array and player coords into a string and return the
//  hash of that string.
struct StateHasher {
    size_t operator() (const State &state) const;
};

#endif
