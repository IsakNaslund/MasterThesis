#include "Restraint.h"

namespace CIFem
{
	Restraint::Restraint()
	{
		_isValid = false;
	}

	Restraint::Restraint(Plane orientation, bool x, bool y, bool z, bool xx, bool yy, bool zz)
	{
		_orientation = orientation;

		std::vector<bool> releases = { x, y, z, xx, yy, zz };
		std::vector<double> displacements = { 0, 0, 0, 0, 0, 0 };

		SetReleases(releases, displacements);
	}

	Restraint::Restraint(Plane orientation, std::vector<bool> releases, std::vector<double> displacements)
	{
		// Set plane
		_orientation = orientation;

		SetReleases(releases, displacements);
	}

	void Restraint::SetReleases(std::vector<bool> rel, std::vector<double> disp)
	{
		// Set restraints
		if (rel.size() != 6 || disp.size() != 6)
		{
			throw std::invalid_argument("Error, number of releases and displacements should be 6!");
		}
		else
		{
			_releases = rel;
			_displacement = disp;

			_isValid = true;
		}
	}

	Restraint::~Restraint()
	{
	}


	Vector3d Restraint::GetXDir()
	{
		return _orientation.GetX();
	}

	Vector3d Restraint::GetYDir()
	{
		return _orientation.GetY();
	}

	Vector3d Restraint::GetZDir()
	{
		return _orientation.GetZ();
	}

	bool Restraint::IsValid()
	{
		return _isValid;
	}

	bool Restraint::GetCMatrix(const Plane structureOrientation, arma::mat & CN)
	{
		// Check if restraint plane differs from global plane
		if (structureOrientation.CompareTo(this->_orientation))
			return false;

		// If different
		CN = arma::mat(6, 6, arma::fill::zeros);

		Vector3d drX = this->GetXDir();
		Vector3d drY = this->GetYDir();
		Vector3d drZ = this->GetZDir();

		Vector3d strX = structureOrientation.GetX();
		Vector3d strY = structureOrientation.GetY();
		Vector3d strZ = structureOrientation.GetZ();

		double nxx = drX.DotProduct(strX);
		double nxy = drY.DotProduct(strY);
		double nxz = drZ.DotProduct(strZ);

		double nyx = drX.DotProduct(strX);
		double nyy = drY.DotProduct(strY);
		double nyz = drZ.DotProduct(strZ);

		double nzx = drX.DotProduct(strX);
		double nzy = drY.DotProduct(strY);
		double nzz = drZ.DotProduct(strZ);

		// Two times for same transformations for translations (1) and rotations(2)
		for (int i = 0; i < 2; i++)
		{
			CN[0 + i * 3, 0 + i * 3] = nxx;
			CN[0 + i * 3, 1 + i * 3] = nxy;
			CN[0 + i * 3, 2 + i * 3] = nxz;

			CN[1 + i * 3, 0 + i * 3] = nyx;
			CN[1 + i * 3, 1 + i * 3] = nyy;
			CN[1 + i * 3, 2 + i * 3] = nyz;

			CN[2 + i * 3, 0 + i * 3] = nyx;
			CN[2 + i * 3, 1 + i * 3] = nyy;
			CN[2 + i * 3, 2 + i * 3] = nyz;
		}

		return true;
	}

	std::vector<bool> Restraint::GetReleases()
	{
		return _releases;
	}

	std::vector<double> Restraint::GetDisplacements()
	{
		return _displacement;
	}



}