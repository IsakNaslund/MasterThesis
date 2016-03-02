#pragma once
#include "CIFem_dll.h"
#include "Vector3d.h"
#include "XYZ.h"
#include <math.h>

namespace CIFem
{
	class CIFEM_API Plane
	{

	public:
		Plane();
		Plane(Vector3d, Vector3d, Vector3d, XYZ);
		Plane(Vector3d, Vector3d, Vector3d);
		~Plane();

		XYZ _origin;
		Vector3d GetX() const;
		Vector3d GetY() const;
		Vector3d GetZ() const;
		bool CompareTo(const Plane) const;						// Compares the plane to another plane (orientation only)
		bool CompareTo(const Plane, bool checkOrigin) const;	// Compares the plane to another plane (orientation and possibly origin)

	private:
		Vector3d _x, _y, _z;
		bool CheckOrthogonality(Vector3d, Vector3d, Vector3d);
	};
}

