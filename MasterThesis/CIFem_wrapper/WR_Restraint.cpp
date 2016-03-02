#include "stdafx.h"
#include "WR_Restraint.h"

namespace CIFem_wrapper
{

	WR_Restraint::WR_Restraint()
	{
	}

	WR_Restraint::WR_Restraint(WR_Plane^ plane, std::vector<bool> releases, std::vector<double> ae)
	{
		_restraint = gcnew m_shared_ptr<CIFem::Restraint>(new CIFem::Restraint(*plane->GetPlane(), releases, ae));
	}

	std::shared_ptr<CIFem::Restraint> CIFem_wrapper::WR_Restraint::GetRestraint()
	{
		return _restraint.operator std::shared_ptr<CIFem::Restraint>();
	}
}