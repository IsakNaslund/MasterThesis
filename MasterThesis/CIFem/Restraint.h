#pragma once
#include "CIFem_dll.h"
#include "XYZ.h"
#include "Plane.h"
#include "include\armadillo"

namespace CIFem
{
	class CIFEM_API Restraint
	{
		Plane _orientation;
		bool _restraints[6];
		double _displacement[6];
		bool _isValid;

	public:
		Restraint();
		Restraint(Plane, bool[6], double[6]);
		~Restraint();

		Vector3d GetXDir();
		Vector3d GetYDir();
		Vector3d GetZDir();
		bool IsValid();
		bool GetCMatrix(const Plane, arma::mat &);
	};
}
