#pragma once
#include <vector>
#include "WR_Utilisation.h"
#include "Utilisation.h"
#include <map>
#include <msclr\marshal_cppstd.h>



namespace Utilities
{
	// C++ to C# conversion functions
	System::Collections::Generic::List<double> ^ GetListFromVector(std::vector<double> vec);
	System::Collections::Generic::List<CIFem_wrapper::WR_Utilisation ^> ^ GetListFromVector(std::vector<std::shared_ptr<CIFem::Utilisation>> vec);

	System::Collections::Generic::Dictionary<System::String^, System::Collections::Generic::List<double> ^> ^ MapToDictionary(std::map<std::string, std::vector<double>> map);

	// C# to C++ conversion functions

}