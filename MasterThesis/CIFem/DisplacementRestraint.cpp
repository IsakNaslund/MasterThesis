#include "DisplacementRestraint.h"

namespace CIFem
{
	DisplacementRestraint::DisplacementRestraint(XYZ coord, Plane orientation, bool restraints[3], double displacement[3])
	{
		// Set restraint coordinate
		_coord = coord;
		
		// Set plane
		_orientation = orientation;

		// Set restraints
		for (int i = 0; i < 3; i++)
		{
			_restraints[i] = restraints[i];
			_displacement[i] = displacement[i];
		}
	}

	DisplacementRestraint::~DisplacementRestraint()
	{
	}

	XYZ DisplacementRestraint::GetXYZ()
	{
		return _coord;
	}

	Vector3d DisplacementRestraint::GetXDir()
	{
		return _orientation.GetX();
	}

	Vector3d DisplacementRestraint::GetYDir()
	{
		return _orientation.GetY();
	}

	Vector3d DisplacementRestraint::GetZDir()
	{
		return _orientation.GetZ();
	}

	arma::mat DisplacementRestraint::GetCMatrix(Plane structureOrientation)
	{
		arma::mat CN(6, 6, arma::fill::zeros);

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

		return arma::mat();
	}

}