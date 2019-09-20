#pragma once

#include <list>
#include "ISudoku.h"

namespace SudokuLogic
{
	class SudokuSolver
	{
	public:
		SudokuSolver(ISudoku* sudoku);
		~SudokuSolver();
		void Solve();
		void ResultReport();

	private:

		std::list<ISudoku*> unsolved;
		std::list<ISudoku*> solved;
	};

}
