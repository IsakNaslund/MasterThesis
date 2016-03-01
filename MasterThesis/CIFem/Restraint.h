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
		bool _isValid;

	public:
		Restraint();
		Restraint(Plane, std::vector<bool>, std::vector<double>);
		~Restraint();

		Vector3d GetXDir();
		Vector3d GetYDir();
		Vector3d GetZDir();
		bool IsValid();
		bool GetCMatrix(const Plane, arma::mat &);
		std::vector<bool> GetReleases();
		std::vector<double> GetDisplacements();

	private:
		std::vector<bool> _releases;		// True = free, false = fixed
		std::vector<double> _displacement;
	};
}
