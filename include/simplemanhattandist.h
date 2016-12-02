//
//  SimpleManhattanDist.h
//  Final
//
//  Created by dalal alharthi on 3/3/1438 AH.
//  Copyright © 1438 dalal alharthi. All rights reserved.
//

#ifndef SimpleManhattanDist_h
#define SimpleManhattanDist_h

#include <stdio.h>
#include <cmath>
#include "AssignmentSolver.h"

class SimpleManhattanDist {
    
public:
    
    SimpleManhattanDist(AssignmentSolver * solver);
    
    int evaluate(State & s);
    
    
private:
    inline int quick_dist_approx(Coord a, Coord b){
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    }
    
    
    AssignmentSolver * solver;
    
    
};

#endif /* SimpleManhattanDist_h */


