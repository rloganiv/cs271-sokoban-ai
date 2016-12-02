//
//  simplemanhattan_test.cpp
//  Final
//
//  Created by dalal alharthi on 3/3/1438 AH.
//  Copyright © 1438 dalal alharthi. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "problem.h"
#include "simplemanhattandist.h"
#include "bbsolver.h"

using namespace std;
void runTest(std::string filename){
    
    Problem test_problem(filename);
    
    cout << "Initializing problem from file" << endl;
    State* init_state = test_problem.get_init_state();
    cout << "Printing initial state" << endl;
    init_state->print();
    
    BBSolver solver;
    
    cout << "Creating simple manhattan distance heuristic" << endl;
    
    SimpleManhattanDist h(&solver);
    
    cout << "Score is = " << h.evaluate(*init_state) << endl;
    
    
    
}


int main(){
    
    string folder = "addtl_test_suite/";
    
    runTest(folder + "testFile3");
    runTest(folder + "testFile2");
    runTest(folder + "microban01");
    runTest(folder + "microban02");
}
