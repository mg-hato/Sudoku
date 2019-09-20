#include "stdafx.h"
#include "Rules.h"

namespace RulesLogic
{
	#pragma region Row Rules

	RowRules::RowRules(int n) : n(n)
	{
		fields = new listField[n];
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				fields[i].push_back(Field(i, j));
			}
		}
	}

	IRules* RowRules::copyRule() const
	{
		return new RowRules(n);
	}

	void RowRules::applyOn(const Field& f, const int entry, listInt** allowed, listField& q) const
	{
		applyOnFields(fields[f.Row()], entry, allowed, q);
	}

	#pragma endregion

	#pragma region Column Rules

	ColumnRules::ColumnRules(int n) : n(n)
	{
		fields = new listField[n];
		for (int j = 0; j < n; ++j)
		{
			for (int i = 0; i < n; ++i)
			{
				fields[j].push_back(Field(i, j));
			}
		}
	}


	void ColumnRules::applyOn(const Field& f, const int entry, listInt** allowed, listField& q) const
	{
		applyOnFields(fields[f.Col()], entry, allowed, q);
	}

	IRules* ColumnRules::copyRule() const
	{
		return new ColumnRules(n);
	}

	#pragma endregion

	#pragma region Box Rules

	BoxRules::BoxRules(int n, int box_rows, int box_cols) :
		n(n), box_rows(box_rows), box_cols(box_cols), x(n / box_rows), y(n / box_cols)
	{
		fields = new listField[n];
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				fields[toIdx(i, j)].push_back(Field(i, j));
			}
		}
	}

	void BoxRules::applyOn(const Field& f, const int entry, listInt** allowed, listField& q) const
	{
		applyOnFields(fields[toIdx(f.Row(), f.Col())], entry, allowed, q);
	}

	int BoxRules::toIdx(const int i, const int j) const
	{
		return (i / box_rows) * y + j / box_cols;
	}

	IRules* BoxRules::copyRule() const
	{
		return new BoxRules(n, box_rows, box_cols);
	}

	#pragma endregion

}
