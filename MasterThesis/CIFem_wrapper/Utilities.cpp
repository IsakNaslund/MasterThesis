#include "stdafx.h"
#include "Utilities.h"

//////////////   C++ to C# conversion functions   //////////////

// Convert a vector of doubles to a list managed pointer
System::Collections::Generic::List<double> ^ Utilities::GetListFromVector(const std::vector<double> & vec)
{
	System::Collections::Generic::List<double> ^ l = gcnew System::Collections::Generic::List<double>(vec.size());

	for (int i = 0; i < vec.size(); i++)
		l->Add(vec[i]);

	return l;
}

// Convert a vector of doubles to a list managed pointer
System::Collections::Generic::List<CIFem_wrapper::WR_Utilisation^> ^ Utilities::GetListFromVector(const std::vector<std::shared_ptr<CIFem::Utilisation>> & vec)
{
	System::Collections::Generic::List<CIFem_wrapper::WR_Utilisation^> ^ l = gcnew System::Collections::Generic::List<CIFem_wrapper::WR_Utilisation^>(vec.size());

	for (int i = 0; i < vec.size(); i++)
		l->Add(gcnew CIFem_wrapper::WR_Utilisation(vec[i]));

	return l;
}

System::Collections::Generic::List<CIFem_wrapper::WR_Utilisation^>^ Utilities::GetListFromUtilSet(const CIFem::UtilisationSet & set)
{
	System::Collections::Generic::List<CIFem_wrapper::WR_Utilisation^> ^ l = gcnew System::Collections::Generic::List<CIFem_wrapper::WR_Utilisation^>(set.size());

	int size = set.size();
	for (int i = 0; i < size; i++)
		l->Add(gcnew CIFem_wrapper::WR_Utilisation(set[i]));

	return l;
}

System::String ^ Utilities::ConvertToSystemString(std::string stdStr)
{
	return msclr::interop::marshal_as<System::String ^>(stdStr);
}

System::Collections::Generic::Dictionary<System::String^, System::Collections::Generic::List<double>^>^ Utilities::MapToDictionary(const std::map<std::string, std::vector<double>> & map)
{
	System::Collections::Generic::Dictionary<System::String^, System::Collections::Generic::List<double>^> ^ dict = gcnew System::Collections::Generic::Dictionary<System::String^, System::Collections::Generic::List<double>^>();

	for each (std::pair<std::string, std::vector<double>> pair in map)
	{
		dict->Add(ConvertToSystemString(pair.first), GetListFromVector(pair.second));
	}
	return dict;
}

System::Collections::Generic::Dictionary<System::String^, System::Collections::Generic::List<CIFem_wrapper::WR_Utilisation^>^>^ Utilities::MapToDictionary(const std::map<std::string, std::vector<std::shared_ptr<CIFem::Utilisation>>> & map)
{
	System::Collections::Generic::Dictionary<System::String^, System::Collections::Generic::List<CIFem_wrapper::WR_Utilisation^>^> ^ dict = gcnew System::Collections::Generic::Dictionary<System::String^, System::Collections::Generic::List<CIFem_wrapper::WR_Utilisation^>^>();

	for each (std::pair<std::string, std::vector<std::shared_ptr<CIFem::Utilisation>>> pair in map)
	{
		dict->Add(ConvertToSystemString(pair.first), GetListFromVector(pair.second));
	}
	return dict;
}

System::Collections::Generic::Dictionary<System::String^, System::Collections::Generic::List<CIFem_wrapper::WR_Utilisation ^> ^> ^ Utilities::MapToDictionary(const std::map<std::string, CIFem::UtilisationSet> & map)
{
	System::Collections::Generic::Dictionary<System::String^, System::Collections::Generic::List<CIFem_wrapper::WR_Utilisation^>^> ^ dict = gcnew System::Collections::Generic::Dictionary<System::String^, System::Collections::Generic::List<CIFem_wrapper::WR_Utilisation^>^>();

	for each (std::pair<std::string, CIFem::UtilisationSet> pair in map)
	{
		dict->Add(ConvertToSystemString(pair.first), GetListFromUtilSet(pair.second));
	}
	return dict;
}

std::vector<int> Utilities::GetVectorFromList(System::Collections::Generic::List<int>^ list)
{
	std::vector<int> vec;

	for (int i = 0; i < list->Count; i++)
	{
		vec.push_back(list[i]);
	}
	return vec;
}

std::set<int> Utilities::GetSetFromList(System::Collections::Generic::List<int>^ list)
{
	std::set<int> set;

	for (int i = 0; i < list->Count; i++)
	{
		set.insert(list[i]);
	}
	return set;
}


