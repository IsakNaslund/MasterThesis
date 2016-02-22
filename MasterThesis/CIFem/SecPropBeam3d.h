#pragma once

#include "ISectionProperties.h"

namespace CIFem
{
	struct SecPropBeam3d : ISectionProperties
	{
		double _Iy;
		double _Iz;
		double _Kv;
	public:
		SecPropBeam3d();
		SecPropBeam3d(const double area, const double iy, const double iz, const double kv);
		~SecPropBeam3d();
	};
}

