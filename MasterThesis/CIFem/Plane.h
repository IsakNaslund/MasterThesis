#pragma once
#include "CIFem_dll.h"
#include "Vector3d.h"
#include "XYZ.h"

namespace CIFem
{
	class CIFEM_API Plane
	{
		

	public:
		Plane(Vector3d, Vector3d, Vector3d, XYZ);
		Plane(Vector3d, Vector3d, Vector3d);
		Vector3d _x, _y, _z;
		XYZ _origin;
		~Plane();

	private:
		bool CheckOrthogonality(Vector3d, Vector3d, Vector3d);
	};
}

