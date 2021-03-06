#include "XYZ.h"

using namespace CIFem;

XYZ::XYZ()
{
}

CIFem::XYZ::XYZ(const XYZ * other)
{
	if (other != nullptr)
	{
		_x = other->_x;
		_y = other->_y;
		_z = other->_z;
	}
}

CIFem::XYZ::XYZ(const double x, const double y, const double z)
{
	_x = x;
	_y = y;
	_z = z;
}


XYZ::~XYZ()
{
}

 double CIFem::XYZ::DistanceTo(const XYZ other)const
{
	return sqrt(pow(this->_x - other._x, 2) + pow(this->_y - other._y, 2) + pow(this->_z - other._z, 2));
}

 double CIFem::XYZ::GetX()
 {
	 return _x;
 }

 double CIFem::XYZ::GetY()
 {
	 return _y;
 }

 double CIFem::XYZ::GetZ()
 {
	 return _z;
 }

