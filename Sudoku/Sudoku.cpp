#include "stdafx.h"
#include "Sudoku.h"
#include <cstdio>
#include <algorithm>

namespace SudokuLogic
{

	#pragma region Constructors

	RegularSudoku::RegularSudoku(const RegularSudoku& rs) : n(rs.n), valid(rs.valid)
	{
		Init();
		InitRules(rs.rules);
		InitPuzzle(rs.puzzle);
	}

	RegularSudoku::RegularSudoku(int** xss, int n) : n(n)
	{
		Init();

		rules.push_back(new RulesLogic::RowRules(n));
		rules.push_back(new RulesLogic::ColumnRules(n));
		if (n == 9)
		{
			rules.push_back(new RulesLogic::BoxRules(n, 3, 3));
		}

		InitPuzzle(xss);
	}
	
	#pragma endregion

	#pragma region Initialisation methods
		
	void RegularSudoku::InitRules(const ruleList& r)
	{
		for (ruleList::const_iterator it = r.begin(); it != r.end(); ++it)
		{
			rules.push_back((*it)->copyRule());
		}
	}

	void RegularSudoku::Init()
	{
		frees = n * n;

		allowed = new listInt*[n];
		puzzle = new int*[n];
		for (int i = 0; i < n; ++i)
		{
			allowed[i] = new listInt[n];
			puzzle[i] = new int[n];
			for (int j = 0; j < n; ++j)
			{
				for (int k = 0; k < n; ++k)
				{
					allowed[i][j].push_back(k);
				}
				puzzle[i][j] = -1;
			}
		}
	}

	void RegularSudoku::InitPuzzle(int** xss)
	{
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (xss[i][j] != -1)
				{
					Add(xss[i][j], i, j, true);
				}
			}
		}
	}

	#pragma endregion

	#pragma region Destructor

	/// Destructor
	RegularSudoku::~RegularSudoku()
	{
		for (int i = 0; i < n; ++i)
		{
			delete[] allowed[i];
			delete[] puzzle[i];
		}
		delete[] allowed;
		delete[] puzzle;

		std::for_each(rules.begin(), rules.end(),
			[](IRules* x) { delete x; });
	}

	#pragma endregion

	#pragma region Implementation of ISudoku

	void RegularSudoku::SolveSimples()
	{
		//Print();

		while (!IsDone() && !q.empty())
		{
			int row = q.front().Row();
			int col = q.front().Col();
			q.pop_front();

			if (puzzle[row][col] == -1)
			{
				if (allowed[row][col].size() == 0)
				{
					valid = false;
				}
				else
				{
					Add(allowed[row][col].front(), row, col);
				}
			}
		}

		//Print();
	}

	std::list<ISudoku*>* RegularSudoku::Expand() const
	{
		std::list<ISudoku*>* ret = new std::list<ISudoku*>();

		if (IsDone())
		{
			return ret;
		}

		Field* opt = findOptimal();
		int row = opt->Row();
		int col = opt->Col();
		delete opt;

		for (listInt::const_iterator it = allowed[row][col].begin();
			it != allowed[row][col].end(); ++it)
		{
			RegularSudoku* sudoku = new RegularSudoku(*this);
			sudoku->Add(*it, row, col);
			ret->push_back(sudoku);
		}

		return ret;
	}

	bool RegularSudoku::Solved() const
	{
		return frees == 0;
	}

	bool RegularSudoku::IsValid() const
	{
		return valid;
	}

	bool RegularSudoku::IsDone() const
	{
		return Solved() || !IsValid();
	}

	void RegularSudoku::Print() const
	{
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{

				printf(puzzle[i][j] == -1 ? " _" : " %d", puzzle[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}

	#pragma endregion

	bool RegularSudoku::IsIn(const listInt& l, int x) const
	{
		listInt::const_iterator i = l.begin();
		while (i != l.end() && *i != x)
		{
			++i;
		}
		return i != l.end();
	}

	void RegularSudoku::Add(int x, int row, int col, bool force)
	{
		if (row >= n || col >= n || row < 0 || col < 0)
		{
			return;
		}

		if ((puzzle[row][col] != -1) || !IsIn(allowed[row][col], x))
		{
			valid = false;
			if (force)
			{
				puzzle[row][col] = x;
			}
			return;
		}

		puzzle[row][col] = x;
		--frees;
		allowed[row][col].clear();

		for (ruleList::const_iterator it = rules.begin(); it != rules.end(); ++it)
		{
			(*it)->applyOn(Field(row, col), x, allowed, q);
		}
	}

	RulesLogic::Field* RegularSudoku::findOptimal() const
	{
		Field* ret = nullptr;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (allowed[i][j].size() == 0)
				{
					continue;
				}

				if (ret == nullptr || allowed[i][j].size() < allowed[ret->Row()][ret->Col()].size())
				{
					delete ret;
					ret = new Field(i, j);
				}
			}
		}

		return ret;
	}


}

