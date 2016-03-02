#include "stdafx.h"
#include "WR_Plane.h"

namespace CIFem_wrapper
{

	WR_Plane::WR_Plane()
	{
	}

	WR_Plane::WR_Plane(WR_Vector^ plX, WR_Vector^ plY, WR_Vector^ plZ, WR_XYZ^ origin)
	{
		_plane = gcnew m_shared_ptr<CIFem::Plane>(new CIFem::Plane(plX->GetAsVector3d(), plY->GetAsVector3d(), plZ->GetAsVector3d(), *origin->GetPos()));
	}

	std::shared_ptr<CIFem::Plane> WR_Plane::GetPlane()
	{
		return _plane.operator std::shared_ptr<CIFem::Plane>();
	}
}