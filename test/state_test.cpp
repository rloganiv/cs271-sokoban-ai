#include "state.h"
#include <iostream>

int main() {
    using namespace std;

    cout << "Instantiating 8 x 10 board..." << endl;
    State::initDimensions(8, 10);
    State test_board;

    cout << "Test - Print board dims" << endl;
    cout << "   Height: " << State::height << endl;
    cout << "   Width: " << State::width << endl;

    cout << "Test - Getting board tile 0, 0" << endl;
    cout << test_board.get_tile(0, 0) << endl;

    cout << "Test - Getting player coordinates" << endl;
    cout << "   x: " << test_board.player.x << endl;
    cout << "   y: " << test_board.player.y << endl;

    cout << "Test - Setting board tile 0, 0 to WALL" << endl;
    test_board.set_tile(0, 0, WALL);

    cout << "Test - Setting player coordinates to 5, 5" << endl;
    test_board.player.x = 5;
    test_board.player.y = 5;

    cout << "Test - Getting board tile 0, 0" << endl;
    cout << test_board.get_tile(0, 0) << endl;

    cout << "Test - Equivalence operator" << endl;
    cout << (test_board == test_board) <<endl;

    cout << "Test - StateHasher" << endl;
    StateHasher shash;
    cout << shash(test_board) << endl;

    cout << "Test - Getting player coordinates" << endl;
    cout << "   x: " << test_board.player.x << endl;
    cout << "   y: " << test_board.player.y << endl;

    cout << "Test - Copying board object" << endl;
    State copy_board = test_board;
    copy_board.print();

    cout << "Test - Change copy tile 0, 0 to EMPTY" << endl;
    copy_board.set_tile(0, 0, EMPTY);

    cout << "Test - Are boards same?" << endl;
    cout << (copy_board == test_board) << endl;

    cout << "Test - Print" << endl;
    test_board.print();

    return 0;
}
