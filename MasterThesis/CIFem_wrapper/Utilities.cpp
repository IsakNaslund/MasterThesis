//Maybe need to include this
//#include "stdafx.h"

#include "Utilities.h"

//////////////   C++ to C# conversion functions   //////////////

// Convert a vector of doubles to a list managed pointer
System::Collections::Generic::List<double> ^ GetListFromVector(std::vector<double> vec)
{
	System::Collections::Generic::List<double> ^ l = gcnew System::Collections::Generic::List<double>(vec.size());

	for (int i = 0; i < vec.size(); i++)
		l->Add(vec[i]);

	return l;
}