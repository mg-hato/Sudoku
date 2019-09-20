#include "stdafx.h"
#include "Field.h"

namespace RulesLogic
{
	#pragma region Field

	Field::Field(int x, int y) : row(x), col(y)
	{
	}

	Field::Field(const Field& f) : row(f.Row()), col(f.Col())
	{
	}

	int Field::Row() const
	{
		return row;
	}

	int Field::Col() const
	{
		return col;
	}

	#pragma endregion

}

