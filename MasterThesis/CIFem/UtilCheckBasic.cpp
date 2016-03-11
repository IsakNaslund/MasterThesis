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

		// Do checks, update element utilisation
		double u = AxialCheck(xSec, mat, results);


		// Do check
		// Update elem util

		// Do check
		// Update elem util

		// Do check
		// Update elem util
	}

	double UtilCheck3dBasic::AxialCheck(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results)
	{
		double N = results.GetMaxAbsolute(results.N());
		double A = xSec->GetArea();

		return (N / A)/(mat->Fu());
	}
}