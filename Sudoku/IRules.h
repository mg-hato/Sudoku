#pragma once

#include <list>
#include <vector>
#include "Field.h"

namespace RulesLogic
{
	#pragma region Typedefs
	
	/// Typedefs used in IRules and its subclasses
	typedef std::list<int> listInt;
	typedef std::list<Field> listField;

	#pragma endregion

	#pragma region IRules class

	class IRules
	{
	public:
		/// <summary>
		///     Destructor
		/// </summary>
		virtual ~IRules();

		virtual void applyOn(const Field& f, const int entry, listInt** allowed, listField& q) const = 0;

		/// <summary>
		///     Returns a copy of the current rule
		/// </summary>
		virtual IRules* copyRule() const = 0;

	protected:
		/// <summary>
		///     Updates `allowed` and `q` regarding affected fields and given entry
		///     <param name="listf">List of fields that are affected</param>
		///     <param name="entry">A number that cannot appear anymore in the affected fields</param>
		///     <param name="allowed">A matrix of lists of allowed numbers for fields</param>
		///     <param name="q">List of fields that require checking</param>
		/// </summary>
		void applyOnFields(const listField& listf, const int entry, listInt** allowed, listField& q) const;

		/// <summary>
		///     Grouped fields
		/// </summary>
		listField* fields;
	};

	#pragma endregion

}