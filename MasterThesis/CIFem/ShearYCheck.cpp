#include "ShearYCheck.h"



CIFem::ShearYCheck::ShearYCheck()
{
	_checkName = "Shear in local y-direction";
}


CIFem::ShearYCheck::~ShearYCheck()
{
}

double CIFem::ShearYCheck::CheckElementUtilisations(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results, std::string resName, int elementPosition)
{
	return (xSec->CheckShearY(results.Vy()[resName][elementPosition]) / (mat->Fu() / sqrt(3)));
}

