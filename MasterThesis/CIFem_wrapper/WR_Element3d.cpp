#include "stdafx.h"
#include "WR_Element3d.h"

CIFem_wrapper::WR_Element3d::WR_Element3d()
{
	// do nothing
}

CIFem_wrapper::WR_Element3d::WR_Element3d(shared_ptr<CIFem::Element3d> const element)
{
	_element = element;
}
