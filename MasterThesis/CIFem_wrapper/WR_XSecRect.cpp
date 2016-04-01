#include "stdafx.h"
#include "WR_XSecRect.h"
using namespace CIFem_wrapper;

WR_XSecRect::WR_XSecRect()
{
	_height = -1;
	_width = -1;
	_xSec = gcnew m_shared_ptr<CIFem::Rectangle3d>(new CIFem::Rectangle3d());
}

WR_XSecRect::WR_XSecRect(const double height, const double width)
{
	_height = height;
	_width = width;
	_xSec = gcnew m_shared_ptr<CIFem::Rectangle3d>(new CIFem::Rectangle3d(height, width));
}

WR_XSecRect::~WR_XSecRect()
{
	//delete _xSec;
	//_xSec = 0;
}

std::shared_ptr<CIFem::ICrossSection> CIFem_wrapper::WR_XSecRect::GetCrossSection()
{
	std::shared_ptr<CIFem::ICrossSection> ptr=  *_xSec.share();

	return ptr;
}

