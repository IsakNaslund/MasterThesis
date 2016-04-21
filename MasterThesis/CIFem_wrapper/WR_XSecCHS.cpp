#include "stdafx.h"
#include "WR_XSecCHS.h"


CIFem_wrapper::WR_XSecCHS::WR_XSecCHS()
{
	_radius = -1;
	_thickness = -1;

	_xSec = gcnew m_shared_ptr<CIFem::CHS3d>(new CIFem::CHS3d());
}

CIFem_wrapper::WR_XSecCHS::WR_XSecCHS(double radius, double thickness)
{
	_radius = radius;
	_thickness = thickness;

	_xSec = gcnew m_shared_ptr<CIFem::CHS3d>(new CIFem::CHS3d(radius, thickness));
}

std::shared_ptr<CIFem::ICrossSection> CIFem_wrapper::WR_XSecCHS::GetCrossSection()
{
	std::shared_ptr<CIFem::ICrossSection> ptr = *_xSec.share();

	return ptr;
}
