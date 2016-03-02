#include "stdafx.h"
#include "WR_Vector.h"


WR_Vector::WR_Vector()
{
	_x = 0;
	_y = 0;
	_z = 0;
}

WR_Vector::WR_Vector(const double x, const double y, const double z)
{
	_x = x;
	_y = y;
	_z = z;
}

CIFem::Vector3d WR_Vector::GetAsVector3d()
{
	return CIFem::Vector3d(_x, _y, _z);
}

std::vector<double> WR_Vector::GetAsCppVector()
{
	std::vector<double> v;
	double x = _x;
	double y = _y;
	double z = _z;
	v.push_back(x);
	v.push_back(y);
	v.push_back(z);

	return v;
}
