#pragma once
#include <vector>

namespace Utilities
{
	// C++ to C# conversion functions
	System::Collections::Generic::List<double> ^ GetListFromVector(std::vector<double> vec);
}