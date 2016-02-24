#include "stdafx.h"
#include "WR_XYZ.h"

using namespace CIFem_wrapper;

WR_XYZ::WR_XYZ()
{
	_xyz = new XYZ();
}

WR_XYZ::WR_XYZ(double x, double y, double z)
{
	_xyz = new XYZ(x, y, z);
}

WR_XYZ::~WR_XYZ()
{
	delete _xyz;
	_xyz = 0;
}

XYZ * CIFem_wrapper::WR_XYZ::GetPos()
{
	return _xyz;
}
