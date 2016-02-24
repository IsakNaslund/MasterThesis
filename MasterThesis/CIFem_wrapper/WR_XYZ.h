#pragma once

#include "XYZ.h"

using namespace CIFem;
namespace CIFem_wrapper
{
	public ref class WR_XYZ
	{
		XYZ* _xyz;

	public:
		WR_XYZ();
		WR_XYZ(double x, double y, double z);
		~WR_XYZ();
		XYZ* GetPos();
	};

}

