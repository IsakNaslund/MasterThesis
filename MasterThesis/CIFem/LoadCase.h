#pragma once

#include "CIFem_dll.h"
#include <string>

namespace CIFem
{
	class CIFEM_API LoadCase
	{
		std::string _name;
	public:
		LoadCase();
		~LoadCase();
	};

}

