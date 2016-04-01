#pragma once
#include <vector>
#include "WR_Utilisation.h"
#include "Utilisation.h"
#include <map>
#include <msclr\marshal_cppstd.h>



namespace Utilities
{
	// C++ to C# conversion functions
	System::Collections::Generic::List<double> ^ GetListFromVector(const std::vector<double> & vec);
	System::Collections::Generic::List<CIFem_wrapper::WR_Utilisation ^> ^ GetListFromVector(const std::vector<std::shared_ptr<CIFem::Utilisation>> & vec);

	System::String^ ConvertToSystemString(std::string);

	System::Collections::Generic::Dictionary<System::String^, System::Collections::Generic::List<double> ^> ^ MapToDictionary(const std::map<std::string, std::vector<double>> & map);
	System::Collections::Generic::Dictionary<System::String^, System::Collections::Generic::List<CIFem_wrapper::WR_Utilisation ^> ^> ^ MapToDictionary(const std::map<std::string, std::vector<std::shared_ptr<CIFem::Utilisation>>> & map);

	// C# to C++ conversion functions

}