//
//  consistency_test.cpp
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
#include "state.h"
#include "heuristic.h"

using namespace std;
void runTest(std::string filename, int MAX_STEP){
    
    Problem test_problem(filename);
    
    cout << "Initializing problem from file" << endl;
    State* init_state = test_problem.get_init_state();
    cout << "Printing initial state" << endl;
    init_state->print();
    
    BBSolver solver;
    
    cout << "Creating simple manhattan distance heuristic" << endl;
    
    SimpleManhattanDist h(&solver);
    
    vector<int> scores;
    scores.push_back(h.evaluate(*init_state));
    for(int i = 0; i < MAX_STEP; i++){
        
       
        
        
        vector<Action> actions = test_problem.valid_actions(init_state);
        
        if(actions.empty())
            break;
        
        Action a = actions[rand() % actions.size()];
        
        *init_state = State(test_problem.result(init_state, a));
        scores.push_back(i + 1 + h.evaluate(*init_state));
        //cout << "Current board after action " << a << endl;
        //init_state->print();
    }
    
    cout << "The f values here should be monotone increasing" << endl;
    for(auto value: scores){
        cout << value << " ";
    }
    cout << endl;
    
    
}

void runHeuristicTest(string filename, int MAX_STEP){
    Problem test_problem(filename);
    
    cout << "Initializing problem from file" << endl;
    State* init_state = test_problem.get_init_state();
    cout << "Printing initial state" << endl;
    init_state->print();
    
    BBSolver solver;
    
    cout << "Creating complicated heuristic" << endl;
    
    Heuristic h( init_state, &solver);
    
    vector<double> scores;
    scores.push_back(h.evaluate(*init_state));
    for(int i = 0; i < MAX_STEP; i++){
        
        
        
        
        vector<Action> actions = test_problem.valid_actions(init_state);
        
        if(actions.empty())
            break;
        
        Action a = actions[rand() % actions.size()];
        
        *init_state = State(test_problem.result(init_state, a));
        scores.push_back(i + 1 + h.evaluate(*init_state));
        //cout << "Current board after action " << a << endl;
        //init_state->print();
    }
    
    cout << "The f values here should be monotone increasing" << endl;
    for(auto value: scores){
        cout << value << " ";
    }
    cout << endl;
    
}


int main(){
    
    string folder = "/Users/dalalalharthi/Documents/Final/addtl_test_suite/";
    
    runTest(folder + "testFile3", 10);
    runTest(folder + "testFile2", 10);
    runTest(folder + "microban01", 30);
    runTest(folder + "microban02", 40);
    
    runHeuristicTest(folder + "testFile3", 10);
    runHeuristicTest(folder + "testFile2", 10);
    runHeuristicTest(folder + "microban01", 20);
    runHeuristicTest(folder + "microban02", 30);
    runHeuristicTest(folder + "microban06", 50);
}
