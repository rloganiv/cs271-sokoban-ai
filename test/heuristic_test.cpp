
#include "problem.h"
#include <iostream>
#include <vector>
#include "heuristic.h"
#include "assignmentsolver.h"
#include "bbsolver.h"
#include <string>

using namespace std;




void runTest(string testfile){
	Problem test_problem(testfile);

    cout << "Initializing problem from file" << endl;
    State* init_state = test_problem.get_init_state();
    cout << "Printing initial state" << endl;
    init_state->print();

    BBSolver solver;
    cout << "Creating heuristic" << endl;
    cout << "Scale factor of a single step: " << K::STEP_SCALE << endl;
    Heuristic h(init_state, &solver);
    cout << "Unmovability table" << endl;
    h.print_unmovability_table();
    cout << "Goal score: " << h.goal_score(*init_state, h.make_coord(1,3)) << endl;
    cout << "Manhattan Dist score: " << h.manhattan_dist_score(*init_state) << endl;
    cout << "Player pos bonus: " << h.player_pos_bonus(*init_state) << endl;
    cout << "Unpushable blocks score: " << h.unpushable_bonus(*init_state) << endl;
    cout << "Eval score = (man_dist + player_pos + unpushable)/scale_step = " << h.evaluate(*init_state) << endl;
    
    cout << "Move up" << endl;
    State s1 = test_problem.result(init_state, UP);
    s1.print();
    cout << "Goal score: " << h.goal_score(s1, h.make_coord(1,3)) << endl;
    cout << "Manhattan Dist score: " << h.manhattan_dist_score(s1) << endl;
    cout << "Player pos bonus: " << h.player_pos_bonus(s1) << endl;
    cout << "Unpushable blocks score: " << h.unpushable_bonus(s1) << endl;
    cout << "Eval score = (man_dist + player_pos + unpushable)/scale_step = " << h.evaluate(s1) << endl;

    cout << "Move right" << endl;
    State s2 = test_problem.result(&s1, RIGHT);
    s2.print();
    cout << "Goal score: " << h.goal_score(s2, h.make_coord(1,3)) << endl;
    cout << "Manhattan Dist score: " << h.manhattan_dist_score(s2) << endl;
    cout << "Player pos bonus: " << h.player_pos_bonus(s2) << endl;
    cout << "Unpushable blocks score: " << h.unpushable_bonus(s2) << endl;
    cout << "Eval score = (man_dist + player_pos + unpushable)/scale_step = " << h.evaluate(s2) << endl;
}

int main() {

    string test0 = "courseTestFile";
    string test1 = "std_suite/screen.1";
    string test2 = "addtl_test_suite/testFile3";

    runTest(test0);
    runTest(test1);
    runTest(test2);

    return 0;
}
