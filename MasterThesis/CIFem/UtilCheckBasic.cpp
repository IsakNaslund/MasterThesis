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
			results._util[i]->Update(AxialCheck(xSec, mat, results, i), "Axial");

			// Do check
			// Update elem util

			// Do check
			// Update elem util

			// Do check
			// Update elem util
		}
	}


	double UtilCheck3dBasic::AxialCheck(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results, int i)
	{
		double N = results.N()[i];
		double A = xSec->GetArea();

		return (N / A)/(mat->Fu());
	}
}