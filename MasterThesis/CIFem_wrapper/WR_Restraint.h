#pragma once

#include "Restraint.h"
#include "WR_Plane.h"
#include "m_shared_ptr.h"

namespace CIFem_wrapper
{

	public ref class WR_Restraint
	{
		m_shared_ptr<CIFem::Restraint> _restraint;

	public:
		WR_Restraint();
		WR_Restraint(WR_Plane^ plane, bool x, bool y, bool z, bool xx, bool yy, bool zz);

		std::shared_ptr<CIFem::Restraint> GetRestraint();
	};

}

