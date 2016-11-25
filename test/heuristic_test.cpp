
#include "problem.h"
#include <iostream>
#include <vector>
#include "heuristic.h"
#include "assignmentsolver.h"
#include "bbsolver.h"
#include <string>

using namespace std;




void runTest(string testfile){
	Problem test_problem;

    cout << "Initializing problem from file" << endl;
    State init_state = test_problem.init_from_file(testfile);
    cout << "Printing initial state" << endl;
    init_state.print();

    BBSolver solver;
    cout << "Creating heuristic" << endl;
    cout << "Scale factor of a single step: " << K::STEP_SCALE << endl;
    Heuristic h(&init_state, &solver);
    cout << "Unmovability table" << endl;
    h.print_unmovability_table();
    cout << "Goal score: " << h.goal_score(init_state, h.make_coord(1,3)) << endl;
    cout << "Next to block bonus (currently unused): " << h.next_to_block_bonus(init_state) << endl;
    cout << "Manhattan Dist score: " << h.manhattan_dist_score(init_state) << endl;
    cout << "Player pos bonus: " << h.player_pos_bonus(init_state) << endl;
    cout << "Eval score: " << h.evaluate(init_state) << endl;
}

int main() {

    string test0 = "courseTestFile";
    string test1 = "std_suite/screen.1";
    
    runTest(test0);
    runTest(test1);

    return 0;
}
