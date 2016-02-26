#pragma once
#include "CIFem_dll.h"
#include "XYZ.h"
#include "Vector3d.h"

namespace CIFem
{
	class CIFEM_API DisplacementRestraint
	{
		XYZ _coord;
		Vector3d _direction;
		double _displacement;

	public:
		DisplacementRestraint(XYZ, Vector3d, double);
		~DisplacementRestraint();
	};
}
