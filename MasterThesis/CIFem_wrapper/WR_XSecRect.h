#pragma once

#include "Rectangle3d.h";
#include "WR_IXSec.h"

namespace CIFem_wrapper
{
	public ref class WR_XSecRect : public WR_IXSec
	{

	public:
		WR_XSecRect();
		WR_XSecRect(const double height, const double width);
		~WR_XSecRect();
	};
}
