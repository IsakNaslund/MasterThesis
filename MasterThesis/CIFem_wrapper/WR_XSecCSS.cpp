#include "stdafx.h"
#include "WR_XSecCSS.h"


CIFem_wrapper::WR_XSecCSS::WR_XSecCSS()
{
	_radius = -1;

	_xSec = gcnew m_shared_ptr<CIFem::CircularSolid3d>(new CIFem::CircularSolid3d());
}


CIFem_wrapper::WR_XSecCSS::WR_XSecCSS(double radius)
{
	_radius = radius;

	_xSec = gcnew m_shared_ptr<CIFem::CircularSolid3d>(new CIFem::CircularSolid3d(radius));
}


std::shared_ptr<CIFem::ICrossSection> CIFem_wrapper::WR_XSecCSS::GetCrossSection()
{
	std::shared_ptr<CIFem::ICrossSection> ptr = *_xSec.share();

	return ptr;
}
