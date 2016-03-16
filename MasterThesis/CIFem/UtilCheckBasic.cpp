#include "UtilCheck3dBasic.h"


namespace CIFem
{
	UtilCheck3dBasic::UtilCheck3dBasic()
	{
	}


	UtilCheck3dBasic::~UtilCheck3dBasic()
	{
	}

	void UtilCheck3dBasic::CheckElementUtilisations(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results)
	{
		for (int i = 0; i < results.Utilisations().size(); i++)
		{
			// Do checks, update element utilisation
			results._util[i]->Update(AxialCheck(xSec, mat, results, i), "Pure axial");

			// Do check (combined bending and axial)
			results._util[i]->Update(CheckCombAxialBending(xSec, mat, results, i),
				"Combined axial and bending over two axes");
			
			// Check shear
			results._util[i]->Update(CheckShearY(xSec, mat, results, i), "Shear in local y-direction");
			results._util[i]->Update(CheckShearZ(xSec, mat, results, i), "Shear in local z-direction");
		}
	}


	double UtilCheck3dBasic::AxialCheck(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results, int i)
	{
		double N = results.N()[i];
		double A = xSec->GetArea();

		return (N / A)/(mat->Fu());
	}


	double UtilCheck3dBasic::CheckCombAxialBending(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results, int i)
	{
		double stress = xSec->CheckCombAxialBending(results.N()[i], results.Myy()[i], results.Mzz()[i]);

		return (stress / mat->Fu());
	}
	
	double UtilCheck3dBasic::
		CheckShearY(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results, int i)
	{
		double tauXY = xSec->CheckShearY(results.Vy()[i]);

		return (tauXY / (mat->Fu() / sqrt(3)));
	}

	double UtilCheck3dBasic::CheckShearZ(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results, int i)
	{
		double tauXZ = xSec->CheckShearZ(results.Vz()[i]);

		return (tauXZ / (mat->Fu() / sqrt(3)));
	}
}