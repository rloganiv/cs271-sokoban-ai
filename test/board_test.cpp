#include "board.h"
#include <iostream>

int main() {
    using namespace std;
    cout << "Instantiating 10 x 10 board..." << endl;
    Board test_board(10, 10);
    cout << "Test - Print board dims" << endl;
    cout << "   Height: " << test_board.height << endl;
    cout << "   Width:  " << test_board.width << endl;
    cout << "Test - Getting board tile 0, 0" << endl;
    cout << test_board.get_tile(0, 0) << endl;
    cout << "Test - Setting board tile 0, 0 to WALL" << endl;
    test_board.set_tile(0, 0, WALL);
    cout << "Test - Getting board tile 0, 0" << endl;
    cout << test_board.get_tile(0, 0) << endl;
    return 0;
}
