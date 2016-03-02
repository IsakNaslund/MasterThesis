#include "stdafx.h"
#include "WR_XSecRect.h"
using namespace CIFem_wrapper;

WR_XSecRect::WR_XSecRect()
{
	_xSec = gcnew m_shared_ptr<CIFem::Rectangle3d>(new CIFem::Rectangle3d());
}

WR_XSecRect::WR_XSecRect(const double height, const double width)
{
	_xSec = gcnew m_shared_ptr<CIFem::Rectangle3d>(new CIFem::Rectangle3d(height, width));
}

WR_XSecRect::~WR_XSecRect()
{
	//delete _xSec;
	//_xSec = 0;
}

System::String ^ CIFem_wrapper::WR_XSecRect::ToString()
{
	double height, width;
	//height = _xSec.operator std::shared_ptr<CIFem::ICrossSection>()->GetHeight();
	//width = _xSec.operator std::shared_ptr<CIFem::ICrossSection>()->GetWidth();
	return "Rectangular cross section";// +height + "*" + width;
}

std::shared_ptr<CIFem::ICrossSection> CIFem_wrapper::WR_XSecRect::GetCrossSection()
{
	std::shared_ptr<CIFem::ICrossSection> ptr=  *_xSec.share();

	return ptr;
}

