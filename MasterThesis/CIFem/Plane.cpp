#include "Plane.h"
#include <exception>

namespace CIFem
{
	// Creates a standard XYZ plane with origin in (0, 0, 0)
	CIFem::Plane::Plane()
	{
		_x = Vector3d(1, 0, 0);
		_y = Vector3d(0, 1, 0);
		_z = Vector3d(0, 0, 1);
		_origin = XYZ(0, 0, 0);
	}

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

	CIFem::Plane::Plane(Vector3d x, Vector3d y, Vector3d z) :
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

	Vector3d CIFem::Plane::GetX() const
	{
		return _x;
	}

	Vector3d Plane::GetY() const
	{
		return _y;
	}

	Vector3d Plane::GetZ() const
	{
		return _z;
	}

	// Checks if two planes are the same (within a tolerance, currently 1e-6).
	// Returns true if same, false otherwise
	// Does not compare origins
	bool Plane::CompareTo(const Plane other) const
	{
		return CompareTo(other, false);
	}

	// Checks if two planes are the same (within a tolerance, currently 1e-6).
	// Returns true if same, false otherwise
	// Compares origin (optionally)
	bool Plane::CompareTo(const Plane other, bool checkOrigin) const
	{
		bool b;

		// Check plane alignment
		double tol = 1e-6;
		if (fabs(this->_x.GetLength() - other.GetX().GetLength()) < tol &&
			fabs(this->_y.GetLength() - other.GetY().GetLength()) < tol &&
			fabs(this->_z.GetLength() - other.GetZ().GetLength()) < tol)
		{
			b = true;
		}
		else
			b = false;

		// Check origin
		if (b && checkOrigin)
		{
			if (this->_origin.DistanceTo(other._origin) < tol)
				b = true;
			else
				b = false;
		}

		return b;
	}
}
