#pragma once
#include <list>

namespace SudokuLogic
{
	class ISudoku
	{
	public:

		/// <summary>
		///     Destructor
		/// </summary>
		virtual ~ISudoku() {};

		/// <summary>
		///     Once called, continuously finds "easy" spots and fills them in. Stops when no easy spots remain 
		/// </summary>
		virtual void SolveSimples() = 0;

		/// <summary>
		///     Expands sudoku - returns a list of sudoku puzzles derived from the current one, but with exactly one more field filled in
		/// </summary>
		virtual std::list<ISudoku*>* Expand() const = 0;

		/// <summary>
		///     Returns true iff sudoku is solved (i.e. iff all fields are filled)
		/// </summary>
		virtual bool Solved() const = 0;

		/// <summary>
		///     Returns true iff current sudoku is still deemed to be solvable
		/// </summary>
		virtual bool IsValid() const = 0;

		/// <summary>
		///     Returns true iff sudoku is determined to be done (i.e. it is solved or it is detected to be not solvable)
		/// </summary>
		virtual bool IsDone() const = 0;

		/// <summary>
		///     Prints out sudoku table on a console standard output
		/// </summary>
		virtual void Print() const = 0;
	};

}