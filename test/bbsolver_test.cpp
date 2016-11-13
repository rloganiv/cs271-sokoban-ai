#include <iostream>
#include <vector>
#include "bbsolver.h"


using namespace std;
const int MAX_N = 10;

void runTest(int costMatrix[MAX_N][MAX_N], int N){

    int ** cm = new int*[N];
    for(int i = 0; i < N; i++)
        cm[i] = new int[N];
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            cm[i][j] = costMatrix[i][j];

    BBSolver solver;

    solver.setCostMatrix(cm, N);

    vector<int> sol = solver.assignment();
    int cost = solver.minCost();

    cout << "-------------- Begin Test N = " << N << " -------------- " << endl;
    cout << "Cost is " << cost << endl;
    cout << "Assignment size: " << sol.size() << endl;
    cout << "Check if assignment cost equals min cost: " << solver.costOfAssignment(sol) << " == " << cost << endl;
    for(unsigned int i = 0; i < sol.size(); i++)
        cout << "Worker " << i << " is assigned to job " << sol[i] << endl;

    for(int i = 0; i < N; i++)
        delete [] cm[i];
    delete [] cm;
}



int main()
{
    const int N = 10;
    int costMatrix[N][N] = {
        {
           9, 2, 7, 8, 7, 3, 2, 1, 4, 3
        },
        {
            6, 4, 3, 7,2, 7, 8, 7, 3, 9
        },
        {
            5, 8, 1, 6, 2, 7, 8, 7, 3, 4
        },
        {
            1, 6, 2, 2, 8, 7, 3, 2, 9, 4
        },
        {
            1, 6, 2, 7, 4, 7, 3, 2, 9, 4
        },
        {
            1, 6, 2, 7, 8, 8, 3, 2, 9, 4
        },
        {
            1, 6, 2, 7, 8, 7, 8, 2, 9, 4
        },
        {
            1, 6, 2, 7, 8, 7, 3, 8, 9, 4
        },
        {
            1, 6, 2, 7, 8, 7, 3, 2, 2, 4
        },
        {
            1, 6, 2, 7, 8, 7, 3, 2, 9, 3
        }
    };

    runTest(costMatrix, 10);
    runTest(costMatrix, 4);
    runTest(costMatrix, 1);
    runTest(costMatrix, 5);

    int costMatrix2[N][N] = {
        {
           1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        },
        {
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        },
        {
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        },
        {
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        },
        {
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        },
        {
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        },
        {
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        },
        {
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        },
        {
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        },
        {
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        }
    };

    runTest(costMatrix2, 10);

    return 0;
}
