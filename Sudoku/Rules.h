#pragma once

#include "IRules.h"
#include <vector>

namespace RulesLogic
{
	#pragma region Row rules

	class RowRules :
		public IRules
	{
	public:
		RowRules(int n);

		void applyOn(const Field& f, const int entry, listInt** allowed, listField& q) const;
		IRules* copyRule() const;

	private:
		int n;
	};

	#pragma endregion

	#pragma region Column rules

	class ColumnRules :
		public IRules
	{
	public:
		ColumnRules(int n);

		void applyOn(const Field& f, const int entry, listInt** allowed, listField& q) const;
		IRules* copyRule() const;

	private:
		int n;
	};

	#pragma endregion

	#pragma region Box rules

	class BoxRules :
		public IRules
	{
	public:
		BoxRules(int n, int box_rows, int box_cols);

		void applyOn(const Field& f, const int entry, listInt** allowed, listField& q) const;
		IRules* copyRule() const;

	private:
		int n;
		int box_rows;
		int box_cols;
		int x;
		int y;

		int toIdx(int i, int j) const;
	};

	#pragma endregion

}


