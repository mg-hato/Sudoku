#pragma once

#include "ISudoku.h"
#include "IRules.h"
#include "Rules.h"
#include "Field.h"
#include <list>

namespace SudokuLogic
{
	class RegularSudoku :
		public ISudoku
	{

		#pragma region Typedefs

		typedef std::list<int> listInt;
		typedef RulesLogic::IRules IRules;
		typedef std::list<IRules*> ruleList;
		typedef RulesLogic::Field Field;
		typedef std::list<Field> listField;

		#pragma endregion

		#pragma region Constructors

	public:

		/// <summary>
		///     Class constructor that takes a matrix and a number
		///     <param name="xss">n by n matrix that describes sudoku's setting, with values -1 for empty spots and 0..n-1 for non empty</param>
		///     <param name="n">dimension of the matrix xss</param>
		/// </summary>
		RegularSudoku(int** xss, int n = 9);

	private:
		/// <summary>
		///     Class constructor that makes a copy of given sudoku
		///     <param name="rs">Sudoku that will be copied</param>
		/// </summary>
		RegularSudoku(const RegularSudoku& rs);

		#pragma endregion
	
	public:

		#pragma region Destructor

		/// <summary>
		///     Destructor
		/// </summary>
		~RegularSudoku();

		#pragma endregion

		#pragma region Implementation of ISudoku


		/// <inheritdoc />
		void SolveSimples();

		/// <inheritdoc />
		std::list<ISudoku*>* Expand() const;

		/// <inheritdoc />
		bool Solved() const;

		/// <inheritdoc />
		bool IsValid() const;

		/// <inheritdoc />
		bool IsDone() const;

		/// <inheritdoc />
		void Print() const;

		#pragma endregion

	private:

		#pragma region Initialisation methods

		/// <summary>
		///     Allocates all dynamical fields to their default values
		/// </summary>
		void Init();

		/// <summary>
		///     Sets the rules of this sudoku instance
		///     <param name="r">List of rules that will be used</param>
		/// </summary>
		void InitRules(const ruleList& r);

		/// <summary>
		///     Sets the initial state of the sudoku puzzle
		///     <param name="xss">A matrix describing initial state</param>
		/// </summary>
		void InitPuzzle(int** xss);

		#pragma endregion

		/// <summary>
		///     With `force` option set to false, adds given number in a puzzle only if that is a valid thing to do;
		///     With `force` option set to true, adds the given number in a puzzle regardless of validity
		///     <param name="x">A number to be enterd</param>
		///     <param name="row">Row number</param>
		///     <param name="col">Column number</param>
		///     <param name="force">Force option</param>
		/// </summary>
		void Add(int x, int row, int col, bool force = false);

		/// <summary>
		///     Returns true iff Inquired number is to be found inside of the given list
		///     <param name="v">Given list</param>
		///     <param name="x">Inquiry number</param>
		/// </summary>
		bool IsIn(const listInt& v, int x) const;

		/// <summary>
		///     In n by n sudoku puzzle, finds an emtpy field whose list of eligible numbers is the shortest.
		/// </summary>
		Field* findOptimal() const;

		#pragma region Data members

		/// <summary>
		///     n by n matrix, describing current sudoku's state
		/// </summary>
		int** puzzle;

		/// <summary>
		///     A matrix of lists. Entry at x,y (allowed[x][y]) is a list
		///     of numbers that are eligible for sudoku field (x,y)
		/// </summary>
		listInt** allowed;

		/// <summary>
		///     A list that explains the rules of the current sudoku setup
		/// </summary>
		ruleList rules;

		/// <summary>
		///     A list of fields that should be checked
		/// </summary>
		listField q;

		/// <summary>
		///     Data member that stores dimension of Sudoku puzzle
		/// </summary>
		int n;

		/// <summary>
		///     Data member that stores number of currently empty spots in sudoku
		/// </summary>
		int frees;

		/// <summary>
		///     Data member that tells whether sudoku has solution(s) with respect to sudoku rules
		///     true: means that for now, no discrepancies were detected
		///     false: a discrepancy(ies) detected, sudoku does not have a solution with respect to the rules
		/// </summary>
		bool valid = true;

		#pragma endregion

	};
}

