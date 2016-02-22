#pragma once

#include "ISectionProperties.h"

namespace CIFem
{
	struct SecPropBar : ISectionProperties
	{
	public:
		SecPropBar();
		SecPropBar(const double area);
		~SecPropBar();
	};

}

