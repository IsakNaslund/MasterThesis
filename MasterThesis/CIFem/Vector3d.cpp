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
