#include "stdafx.h"
#include "IRules.h"

namespace RulesLogic
{
	#pragma region IRules
	
	/// Implementation of common features of any IRules class

	IRules::~IRules()
	{
		delete[] fields;
	}

	void IRules::applyOnFields(const listField& listf, const int entry, listInt** allowed, listField& q) const
	{
		bool shouldCheck = false;
		for (listField::const_iterator it = listf.begin(); it != listf.end(); ++it)
		{
			listInt& current = allowed[it->Row()][it->Col()];
			shouldCheck = current.size() != 0;
			current.remove(entry);
			if(current.size() == 1)
			{
				q.push_back(Field(*it));
			}
			else if (shouldCheck && current.size() == 0)
			{
				q.push_front(Field(*it));
			}
		}
	}

	#pragma endregion

}
