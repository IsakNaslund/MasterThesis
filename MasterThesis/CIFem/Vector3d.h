#pragma once
#include "CIFem_dll.h"
#include <math.h>

namespace CIFem
{

	class CIFEM_API Vector3d
	{
		double _x, _y, _z;

	public:
		Vector3d();
		Vector3d(double x, double y, double z);
		Vector3d(double x, double y, double z, bool unitize);
		double GetX() const;
		double GetY() const;
		double GetZ() const;
		double GetLength() const;
		double DotProduct(Vector3d other);
		void Unitize();
		~Vector3d();
	};

}