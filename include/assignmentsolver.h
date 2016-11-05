//
//  AssignmentSolver.h
//  cs271-sokoban-ai
//
//  Created by dalal alharthi on 2/5/1438 AH.
//  Copyright © 1438 dalal alharthi. All rights reserved.
//

#ifndef AssignmentSolver_h
#define AssignmentSolver_h

#include <stdio.h>

// Abstract class. Assignment solver interface for same size bipartite graphs G = vertices: V u U where |V| = |U|

class AssignmentSolver{
public:
    
    AssignmentSolver(int ** costMatrix){
        cmatrix = costMatrix;
    }
    
    virtual int minCost() = 0;
    
    virtual int * assignment() = 0;
    
private:
    
    int ** cmatrix;
    
};

#endif /* AssignmentSolver_h */
