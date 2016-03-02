#pragma once

#include "WR_Vector.h"
#include "WR_XYZ.h"
#include "m_shared_ptr.h"
#include "Plane.h"

namespace CIFem_wrapper
{
	public ref class WR_Plane
	{
		m_shared_ptr<CIFem::Plane> _plane;

	public:
		WR_Plane();
		WR_Plane(WR_Vector^ plX, WR_Vector^ plY, WR_Vector^ plZ, WR_XYZ^ origin);

		std::shared_ptr<CIFem::Plane> GetPlane();
	};
}

