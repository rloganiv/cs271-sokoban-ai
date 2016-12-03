//
//  AssignmentSolver.h
//  cs271-sokoban-ai
//
//  Created by dalal alharthi on 2/5/1438 AH.
//  Copyright © 1438 dalal alharthi. All rights reserved.
//

#ifndef AssignmentSolver_h
#define AssignmentSolver_h
#include <vector>

// Abstract class. Assignment solver interface for same size bipartite graphs G = vertices: V u U where |V| = |U|

class AssignmentSolver{
public:

    AssignmentSolver(){};

    virtual void setCostMatrix(int ** costMatrix, int numWorkers) = 0;

    virtual int minCost() = 0;

    virtual std::vector<int> assignment() = 0;

};

#endif /* AssignmentSolver_h */
