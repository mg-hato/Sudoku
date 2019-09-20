#include "stdafx.h"
#include "SudokuSolver.h"
#include <algorithm>


namespace SudokuLogic
{

	SudokuSolver::SudokuSolver(ISudoku* sudoku)
	{
		unsolved.push_back(sudoku);
	}


	SudokuSolver::~SudokuSolver()
	{
		std::for_each(unsolved.begin(), unsolved.end(),
			[](ISudoku* x) { delete x;  });

		std::for_each(solved.begin(), solved.end(),
			[](ISudoku* x) { delete x;  });
	}

	void SudokuSolver::Solve()
	{
		while (!unsolved.empty())
		{
			ISudoku* sudoku = unsolved.front();
			unsolved.pop_front();

			sudoku->SolveSimples();
			if (sudoku->Solved() && sudoku->IsValid())
			{
				solved.push_back(sudoku);
				continue;
			}

			std::list<ISudoku*>* expansion = sudoku->Expand();
			unsolved.splice(unsolved.end(), *expansion);

			delete expansion;
			delete sudoku;
		}
	}

	
	void SudokuSolver::ResultReport()
	{
		if (solved.size() == 0)
		{
			printf("Given sudoku is incorrect, no solution exists.");
		}
		else if (solved.size() == 1)
		{
			printf("Unique solution exists, and it is as follows:\n");
		}
		else
		{
			printf("Given sudoku has (%d) valid solutions, they are as follows:\n", solved.size());
		}

		std::for_each(solved.begin(), solved.end(),
			[](ISudoku* x) { x->Print(); });
	}
}
