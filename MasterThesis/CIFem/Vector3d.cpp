#include "Vector3d.h"



CIFem::Vector3d::Vector3d()
{
}


CIFem::Vector3d::Vector3d(double x, double y, double z)
{
	_x = x;
	_y = y;
	_z = z;
}

CIFem::Vector3d::Vector3d(double x, double y, double z, bool unitize)
	: Vector3d(x, y, z)
{
	Unitize();
}

CIFem::Vector3d::Vector3d(XYZ st, XYZ en)
{
	_x = en.GetX() - st.GetX();
	_y = en.GetY() - st.GetY();
	_z = en.GetZ() - st.GetZ();
}

double CIFem::Vector3d::GetX() const
{
	return _x;
}

double CIFem::Vector3d::GetY() const
{
	return _y;
}

double CIFem::Vector3d::GetZ() const
{
	return _z;
}

double CIFem::Vector3d::GetLength() const
{
	return sqrt(pow(this->_x, 2) + pow(this->_y, 2) + pow(this->_z, 2));
}

double CIFem::Vector3d::DotProduct(Vector3d other)
{
	return _x * other.GetX() + _y * other.GetY() + _z * other.GetZ();
}

std::vector<double> CIFem::Vector3d::ToStandardVector() const
{
	std::vector<double> v;
	v.push_back(_x);
	v.push_back(_y);
	v.push_back(_z);
	return v;
}

void CIFem::Vector3d::Unitize()
{
	double length = GetLength();

	_x = _x / length;
	_y = _y / length;
	_z = _z / length;
}

CIFem::Vector3d::~Vector3d()
{
}

CIFem::Vector3d CIFem::Vector3d::operator* (double t)
{
	return Vector3d(_x*t, _y*t, _z*t);
}

CIFem::Vector3d CIFem::Vector3d::operator- (CIFem::Vector3d other)
{
	return Vector3d(_x-other._x, _y-other._y, _z-other._z);
}

CIFem::Vector3d CIFem::Vector3d::ZeroVec()
{
	return Vector3d(0,0,0);
}

CIFem::Vector3d CIFem::Vector3d::X()
{
	return Vector3d(1,0,0);
}

CIFem::Vector3d CIFem::Vector3d::Y()
{
	return Vector3d(0,1,0);
}

CIFem::Vector3d CIFem::Vector3d::Z()
{
	return Vector3d(0,0,1);
}
