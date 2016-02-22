#pragma once

#include "ICrossSection.h"

namespace CIFem
{
	class RHS3d : ICrossSection
	{
		double _height;
		double _width;
		double _thickness;
	public:
		RHS3d();
		~RHS3d();
	};
}

