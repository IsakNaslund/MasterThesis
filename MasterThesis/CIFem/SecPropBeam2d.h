#pragma once

#include "ISectionProperties.h"

namespace CIFem
{
	struct SecPropBeam2d : ISectionProperties
	{
		double _I;
	public:
		SecPropBeam2d();
		SecPropBeam2d(const double area, const double i);
		~SecPropBeam2d();
	};
}

