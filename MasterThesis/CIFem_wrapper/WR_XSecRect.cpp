#include "stdafx.h"
#include "WR_XSecRect.h"
using namespace CIFem_wrapper;

WR_XSecRect::WR_XSecRect()
{
	_xSec = new CIFem::Rectangle3d();
}

WR_XSecRect::WR_XSecRect(const double height, const double width)
{
	_xSec = new CIFem::Rectangle3d(height, width);
}

WR_XSecRect::~WR_XSecRect()
{
	delete _xSec;
	_xSec = 0;
}

System::String ^ CIFem_wrapper::WR_XSecRect::ToString()
{
	double height, width;
	height = _xSec->GetHeight();
	width = _xSec->GetWidth();
	return "Rectangular cross section" + height + "*" + width;
}

CIFem::ICrossSection * CIFem_wrapper::WR_XSecRect::GetCrossSection()
{
	return _xSec;
}

