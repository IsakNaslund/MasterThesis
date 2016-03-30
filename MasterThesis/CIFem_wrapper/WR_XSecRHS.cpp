#include "stdafx.h"
#include "WR_XSecRHS.h"


CIFem_wrapper::WR_XSecRHS::WR_XSecRHS()
{
	_xSec =  gcnew m_shared_ptr<CIFem::RHS3d>(new CIFem::RHS3d());
}

CIFem_wrapper::WR_XSecRHS::WR_XSecRHS(double height, double width, double thickness)
{
	_xSec = gcnew m_shared_ptr<CIFem::RHS3d>(new CIFem::RHS3d(height,width,thickness));
}


System::String ^ CIFem_wrapper::WR_XSecRHS::ToString()
{
	double height, width;
	//height = _xSec.operator std::shared_ptr<CIFem::ICrossSection>()->GetHeight();
	//width = _xSec.operator std::shared_ptr<CIFem::ICrossSection>()->GetWidth();
	return "RHS";// +height + "*" + width;
}

std::shared_ptr<CIFem::ICrossSection> CIFem_wrapper::WR_XSecRHS::GetCrossSection()
{
	std::shared_ptr<CIFem::ICrossSection> ptr = *_xSec.share();

	return ptr;
}
