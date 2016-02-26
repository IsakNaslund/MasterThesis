#include "Plane.h"
#include <exception>


CIFem::Plane::Plane(Vector3d x, Vector3d y, Vector3d z, XYZ origin)
{
	if (!CheckOrthogonality(x, y, z))
		throw std::exception("Vectors not orthogonal!");

	_x = x;
	_x.Unitize();

	_y = y;
	_y.Unitize();

	_z = z;
	_z.Unitize();

	_origin = origin;
}

CIFem::Plane::Plane(Vector3d x, Vector3d y, Vector3d z):
	Plane(x, y, z, XYZ(0, 0, 0))
{
}

CIFem::Plane::~Plane()
{
}

bool CIFem::Plane::CheckOrthogonality(Vector3d x, Vector3d y, Vector3d z)
{
	if (x.DotProduct(y) != 0 || x.DotProduct(z) != 0 || y.DotProduct(z) != 0)
		return false;
	else
		return true;
}
