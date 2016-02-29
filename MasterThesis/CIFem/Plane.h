#pragma once
#include "CIFem_dll.h"
#include "Vector3d.h"
#include "XYZ.h"

namespace CIFem
{
	class CIFEM_API Plane
	{
		Vector3d _x, _y, _z;

	public:
		Plane();
		Plane(Vector3d, Vector3d, Vector3d, XYZ);
		Plane(Vector3d, Vector3d, Vector3d);
		~Plane();

		XYZ _origin;
		Vector3d GetX();
		Vector3d GetY();
		Vector3d GetZ();

	private:
		bool CheckOrthogonality(Vector3d, Vector3d, Vector3d);
	};
}

