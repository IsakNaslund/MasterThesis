#include "CombAxialBendingCheck.h"



CIFem::CombAxialBendingCheck::CombAxialBendingCheck()
{
	_checkName = "Combined axial and bending over two axes";
}


CIFem::CombAxialBendingCheck::~CombAxialBendingCheck()
{
}

double CIFem::CombAxialBendingCheck::CheckElementUtilisations(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results, std::string resName, int elementPosition)
{
	return (xSec->CheckCombAxialBending(results.N()[resName][elementPosition], results.Myy()[resName][elementPosition], results.Mzz()[resName][elementPosition]) / mat->Fu());
}
