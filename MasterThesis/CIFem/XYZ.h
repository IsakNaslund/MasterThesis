#pragma once

#include "CIFem_dll.h"
#include <math.h>


namespace CIFem
{
	
	class CIFEM_API XYZ
	{
		double _x, _y, _z;
	public:
		XYZ();
		XYZ(const double x, const double y, const double z);
		~XYZ();

		double DistanceTo(const XYZ other) const;
	};

}

