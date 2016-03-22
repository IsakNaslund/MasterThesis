#include "stdafx.h"
#include "Utilities.h"

//////////////   C++ to C# conversion functions   //////////////

// Convert a vector of doubles to a list managed pointer
System::Collections::Generic::List<double> ^ Utilities::GetListFromVector(std::vector<double> vec)
{
	System::Collections::Generic::List<double> ^ l = gcnew System::Collections::Generic::List<double>(vec.size());

	for (int i = 0; i < vec.size(); i++)
		l->Add(vec[i]);

	return l;
}

// Convert a vector of doubles to a list managed pointer
System::Collections::Generic::List<CIFem_wrapper::WR_Utilisation^> ^ Utilities::GetListFromVector(std::vector<std::shared_ptr<CIFem::Utilisation>> vec)
{
	System::Collections::Generic::List<CIFem_wrapper::WR_Utilisation^> ^ l = gcnew System::Collections::Generic::List<CIFem_wrapper::WR_Utilisation^>(vec.size());

	for (int i = 0; i < vec.size(); i++)
		l->Add(gcnew CIFem_wrapper::WR_Utilisation(vec[i]));

	return l;
}

