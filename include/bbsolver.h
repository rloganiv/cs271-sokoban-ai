//
//  bbsolver.h
//  cs271-sokoban-ai
//
//  Created by dalal alharthi on 2/13/1438 AH.
//  Copyright © 1438 dalal alharthi. All rights reserved.

#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include<climits>
#include<cstdlib>
#include<set>
#include<vector>
#include<iostream>
#include "assignmentsolver.h"

/********************************

Solves the assignment problem using a variant of Branch and Bound
for problems of N workers and N jobs. This is used to assign free blocks
to the nearest goal.

*********************************/

struct bbNode {
	std::vector<int> assignment;
	std::set<int> free_jobs;
	int currCost;
};


class BBSolver : public AssignmentSolver {
public:
	BBSolver() : AssignmentSolver() {}

	void setCostMatrix(int ** costMatrix, int numWorkers){
        this->costMatrix = costMatrix;
		this->N = numWorkers;
		result = makeEmptyNode();
		solve();
	}

	int minCost(){return result.currCost;}

	inline int costOfAssignment(std::vector<int> assignment){
        int sum = 0;
        for(int i = 0; i < N; i++)
            sum += costMatrix[i][assignment[i]];
        return sum;
	}

	/*********************
        returns a vector assignment where
        assignment[i] = j means worker i is assigned job j
	***********************/
	std::vector<int> assignment(){return result.assignment;}

private:
	int N;
	int ** costMatrix;
    bbNode result;

    void solve();


	// Computes the lowerbound from a partial assignment
	inline int g_lower_bound(int start, int init_score, std::set<int> free_jobs){

		int result = init_score;
		for(int i = start; i < N; i++){
			int min = INT_MAX;
			int min_index = -1;
			for(int j = 0; j < N; j++){
				if(costMatrix[i][j] < min){
					min = costMatrix[i][j];
					min_index = j;
				}
			}
			free_jobs.erase(min_index);
			result += min;
		}
		return result;
	}

	inline bbNode h_upper_bound(){
		bbNode res = makeEmptyNode();
		for(int i = 0; i < N; i++){
			int max = INT_MIN;
			int max_index = -1;
			std::set<int>::iterator it;
			for(it = res.free_jobs.begin(); it != res.free_jobs.end(); it++){
				if(costMatrix[i][*it] > max){
					max = costMatrix[i][*it];
					max_index = *it;
				}
			}
			res = assign(res, max_index);
		}
		return res;
	}

	inline bbNode makeEmptyNode(){
		bbNode n;
		n.currCost = 0;
		for(int i = 0; i < N; i++)
			n.free_jobs.insert(i);
		return n;
	}

	inline bbNode assign(bbNode n, int job){
		int worker = n.assignment.size();
		n.currCost += costMatrix[worker][job];
		n.assignment.push_back(job);
		if(n.free_jobs.find(job) != n.free_jobs.end())
            n.free_jobs.erase(job);
		return n;
	}

	inline bbNode unassign(bbNode n){
		int job = n.assignment.back();
		int worker = n.assignment.size()-1;
	        n.currCost -= costMatrix[worker][job];
		n.assignment.pop_back();
		n.free_jobs.insert(job);
		return n;
	}



};

#endif
