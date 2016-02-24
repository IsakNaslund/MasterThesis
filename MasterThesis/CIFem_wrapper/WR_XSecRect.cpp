#include "stdafx.h"
#include "WR_XSecRect.h"


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

}
