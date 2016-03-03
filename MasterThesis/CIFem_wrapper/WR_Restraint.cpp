#include "stdafx.h"
#include "WR_Restraint.h"

namespace CIFem_wrapper
{

	WR_Restraint::WR_Restraint()
	{
	}

	WR_Restraint::WR_Restraint(WR_Plane^ plane, bool x, bool y, bool z, bool xx, bool yy, bool zz)
	{

		_restraint = gcnew m_shared_ptr<CIFem::Restraint>(new CIFem::Restraint(*plane->GetPlane(), releases, ae));
	}

	std::shared_ptr<CIFem::Restraint> CIFem_wrapper::WR_Restraint::GetRestraint()
	{
		return _restraint.operator std::shared_ptr<CIFem::Restraint>();
	}
}