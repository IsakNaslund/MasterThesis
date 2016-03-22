#pragma once
#include <vector>
#include "WR_Utilisation.h"
#include "Utilisation.h"



namespace Utilities
{
	// C++ to C# conversion functions
	System::Collections::Generic::List<double> ^ GetListFromVector(std::vector<double> vec);
	System::Collections::Generic::List<CIFem_wrapper::WR_Utilisation ^> ^ GetListFromVector(std::vector<std::shared_ptr<CIFem::Utilisation>> vec);

	// C# to C++ conversion functions

}