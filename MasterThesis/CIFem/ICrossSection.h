#pragma once

#include "ISectionProperties.h"


namespace CIFem
{
	class ICrossSection
	{
	public:
		virtual ISectionProperties CalcSectionProperties() = 0;
	};

}