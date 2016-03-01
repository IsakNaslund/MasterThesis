#pragma once
#include "CIFem_dll.h"
#include "XYZ.h"
#include "Plane.h"
#include "include\armadillo"

namespace CIFem
{
	class CIFEM_API Restraint
	{
		XYZ _coord;
		Plane _orientation;
		bool _restraints[3];
		double _displacement[3];

	public:
		Restraint(XYZ, Plane, bool[6], double[6]);
		~Restraint();

		XYZ GetXYZ();
		Vector3d GetXDir();
		Vector3d GetYDir();
		Vector3d GetZDir();
		arma::mat GetCMatrix(Plane);
	};
}
