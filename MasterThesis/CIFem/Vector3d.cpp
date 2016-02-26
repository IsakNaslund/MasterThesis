#include "Vector3d.h"



Vector3d::Vector3d()
{
}


Vector3d::Vector3d(double x, double y, double z)
{
	_x = x;
	_y = y;
	_z = z;
}

Vector3d::Vector3d(double x, double y, double z, bool unitize)
{
	double length = GetLength(x, y, z);

	Vector3d(x / length, y / length, z / length);	//Does this work? /C
}

double Vector3d::GetX()
{
	return _x;
}

double Vector3d::GetY()
{
	return _y;
}

double Vector3d::GetZ()
{
	return _z;
}

double Vector3d::GetLength(double x, double y, double z)
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Vector3d::~Vector3d()
{
}
