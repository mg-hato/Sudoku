#pragma once

namespace RulesLogic
{
	#pragma region Field class

	class Field
	{
	public:
		/// <summary>
		///     Constructor: Class will represent a field uniquely given row and column number
		///     <param name="x">Number of the row</param>
		///     <param name="y">Number of the column</param>
		/// </summary>
		Field(int x, int y);

		/// <summary>
		///     Constructor: Makes a copy of the given field class
		///     <param name="f">Class that represents a field</param>
		/// </summary>
		Field(const Field& f);

		/// <summary>
		///     Returns the row number of the represented field
		/// </summary>
		int Row() const;

		/// <summary>
		///     Returns the column number of the represented field
		/// </summary>
		int Col() const;

	private:
		/// <summary>
		///     Row number
		/// </summary>
		int row;

		/// <summary>
		///     Column number
		/// </summary>
		int col;
	};

	#pragma endregion	

}

