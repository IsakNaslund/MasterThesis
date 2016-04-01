#include "ShearZCheck.h"



CIFem::ShearZCheck::ShearZCheck()
{
	_checkName = "Shear in local z-direction";
}


CIFem::ShearZCheck::~ShearZCheck()
{
}

double CIFem::ShearZCheck::CheckElementUtilisations(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results, std::string resName, int elementPosition)
{
	return (xSec->CheckShearZ(results.Vz()[resName][elementPosition]) / (mat->Fu() / sqrt(3)));
}
