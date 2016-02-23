#pragma once

#include "SectionProperties.h"


namespace CIFem
{
	class ICrossSection
	{
	public:
		virtual SectionProperties CalcSectionProperties() = 0;
	};

}