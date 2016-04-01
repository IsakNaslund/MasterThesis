#include "AxialCheck.h"



CIFem::AxialCheck::AxialCheck()
{
	_checkName = "Pure axial";
}

CIFem::AxialCheck::~AxialCheck()
{
}


double CIFem::AxialCheck::CheckElementUtilisations(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results, std::string resName, int elementPosition)
{
	return (results.N()[resName][elementPosition] / xSec->GetArea()) / (mat->Fu());
}
