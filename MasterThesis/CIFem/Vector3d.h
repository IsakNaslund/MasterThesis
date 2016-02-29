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
		double GetX();
		double GetY();
		double GetZ();
		double GetLength(double x, double y, double z);
		double DotProduct(Vector3d other);
		void Unitize();
		~Vector3d();
	};

}