#include "UtilCheck3dBasic.h"


namespace CIFem
{
	UtilCheck3dBasic::UtilCheck3dBasic()
	{
	}


	UtilCheck3dBasic::~UtilCheck3dBasic()
	{
	}

	void UtilCheck3dBasic::CheckElementUtilisations(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results, std::string resName)
	{
		for (int i = 0; i < results.Utilisations().size(); i++)
		{
			// Do checks, update element utilisation
			results._util[resName][i]->Update(AxialCheck(xSec, mat, results.N()[resName][i]), "Pure axial");

			// Do check (combined bending and axial)
			results._util[resName][i]->Update(CheckCombAxialBending(xSec, mat, results.N()[resName][i], results.Myy()[resName][i], results.Mzz()[resName][i]),
				"Combined axial and bending over two axes");
			
			// Check shear
			results._util[resName][i]->Update(CheckShearY(xSec, mat, results.Vy()[resName][i]), "Shear in local y-direction");
			results._util[resName][i]->Update(CheckShearZ(xSec, mat, results.Vz()[resName][i]), "Shear in local z-direction");
		}
	}


	double UtilCheck3dBasic::AxialCheck(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, double N)
	{
		double A = xSec->GetArea();

		return (N / A)/(mat->Fu());
	}


	double UtilCheck3dBasic::CheckCombAxialBending(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, double N, double My, double Mz)
	{
		double stress = xSec->CheckCombAxialBending(N,My,Mz);

		return (stress / mat->Fu());
	}
	
	double UtilCheck3dBasic::
		CheckShearY(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, double Vy)
	{
		double tauXY = xSec->CheckShearY(Vy);

		return (tauXY / (mat->Fu() / sqrt(3)));
	}

	double UtilCheck3dBasic::CheckShearZ(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, double Vz)
	{
		double tauXZ = xSec->CheckShearZ(Vz);

		return (tauXZ / (mat->Fu() / sqrt(3)));
	}
}