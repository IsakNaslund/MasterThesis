#pragma once

#include "SectionProperties.h"
#include "CIFem_dll.h"

namespace CIFem
{
	class CIFEM_API ICrossSection
	{
	public:
		virtual SectionProperties CalcSectionProperties() = 0;
	};

}