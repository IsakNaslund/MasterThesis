#pragma once

#include "XYZ.h"
#include "m_shared_ptr.h"

using namespace CIFem;
namespace CIFem_wrapper
{
	public ref class WR_XYZ
	{
		m_shared_ptr<XYZ> _xyz;

	public:
		WR_XYZ();
		WR_XYZ(double x, double y, double z);
		~WR_XYZ();
		std::shared_ptr<XYZ> GetPos();
	};

}

