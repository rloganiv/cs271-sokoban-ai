#include "deadlock.h"
#include "problem.h"
#include <iostream>

int main(int argc, char** argv){
    using namespace std;
    cout << "Initializing Problem" << endl;
    Problem test_problem(argv[1]);
    State *init_state = test_problem.get_init_state();
    int height = init_state->height;
    int width = init_state->width;

    cout << "Printing initial state" << endl;
    init_state->print();

    cout << "Creating deadlock array" << endl;
    bool* deadlock_arr = get_deadlocks(init_state);

    cout << "Printing deadlock array" << endl;
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            cout << deadlock_arr[i*width + j] << " " ;
        }
        cout << endl;
    }


}
