#include "stdafx.h"
#include "WR_XSecRHS.h"


CIFem_wrapper::WR_XSecRHS::WR_XSecRHS()
{
	_height = -1;
	_width = -1;
	_thickness = -1;

	_xSec =  gcnew m_shared_ptr<CIFem::RHS3d>(new CIFem::RHS3d());
}

CIFem_wrapper::WR_XSecRHS::WR_XSecRHS(double height, double width, double thickness)
{
	_height = height;
	_width = width;
	_thickness = thickness;

	_xSec = gcnew m_shared_ptr<CIFem::RHS3d>(new CIFem::RHS3d(height,width,thickness));
}


std::shared_ptr<CIFem::ICrossSection> CIFem_wrapper::WR_XSecRHS::GetCrossSection()
{
	std::shared_ptr<CIFem::ICrossSection> ptr = *_xSec.share();

	return ptr;
}
