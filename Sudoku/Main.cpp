// Sudoku.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include "Sudoku.h"
#include <iostream>
#include "SudokuSolver.h"
#include <ctime>

using namespace SudokuLogic;
using namespace RulesLogic;


int** xss = new int*[9]{
	new int[9]{  3, -1, -1, 	-1, -1,  4,		 5, -1,  -1 },
	new int[9]{ -1, -1, -1,		-1, -1,  6,		-1,  7,  -1 },
	new int[9]{ -1,  1, -1,		 0, -1, -1,		-1, -1,   8 },

	new int[9]{ -1, -1, -1,		 2, -1, -1,		-1, -1,   0 },
	new int[9]{ -1, -1,  6,		-1, -1, -1,		 3, -1,  -1 },
	new int[9]{  5, -1, -1,		-1, -1,  7,		-1, -1,  -1 },

	new int[9]{  4, -1, -1,		-1, -1,  5,		-1,  1,  -1 },
	new int[9]{ -1,  8, -1,		 3, -1, -1,		-1, -1,  -1 },
	new int[9]{ -1, -1,  0,		 6, -1, -1,		-1, -1,   2 },
};


int main()
{

	time_t startTime;
	time(&startTime);

	ISudoku* xxx = new RegularSudoku(xss, 9);

	SudokuSolver solver(new RegularSudoku(xss, 9));

	solver.Solve();
	solver.ResultReport();

	time_t endTime;
	time(&endTime);

	printf("\n\nTime: %.2f", difftime(endTime, startTime));

	getchar();
    return 0;
}

/*

{ {1, 2, 3, 4},
{3, 1, 4, 2},
{4, 3, 2, 1},
{2, 4, 1, 3} }


*/