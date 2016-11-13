//
//  bbsolver.cpp
//  cs271-sokoban-ai
//
//  Created by dalal alharthi on 2/13/1438 AH.
//  Copyright © 1438 dalal alharthi. All rights reserved.


#include "bbsolver.h"
#include <vector>
#include <stack>
#include <set>
#include <iostream>

void BBSolver::solve(){
    using std::stack;
	using std::vector;
	using std::set;



	stack<bbNode > st;  // TODO: Consider switching this to a priority queue might be worthwhile in the future

	bbNode initial = makeEmptyNode();
	result = h_upper_bound();
	int B = result.currCost;
	st.push(initial);
	while(! st.empty()){
		bbNode n = st.top();
		st.pop();
		if((signed int)n.assignment.size() == N) // This is a full assignment
		{
			if(n.currCost <= B){
				B = n.currCost;
				result = n;
			}
		}
		else{
			set<int>::iterator it;
			for(it = n.free_jobs.begin(); it != n.free_jobs.end(); it++){
				bbNode next = assign(n, *it);
				int lb = g_lower_bound(next.assignment.size(), next.currCost, next.free_jobs);
				if(lb < B)
					st.push(next);
			}
		}
	}


}





