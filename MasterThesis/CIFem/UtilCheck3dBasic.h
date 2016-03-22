#pragma once

#include "CIFem_dll.h"
#include "IUtilisationCheck.h"
#include "IUtilCheck3d.h"

namespace CIFem
{
	class CIFEM_API UtilCheck3dBasic : public IUtilCheck3d
	{
	
	public:
		UtilCheck3dBasic();
		~UtilCheck3dBasic();

		void CheckElementUtilisations(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results) override;
		double AxialCheck(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results, int i);
		double CheckCombAxialBending(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results, int i);
		double CheckShearY(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results, int i);
		double CheckShearZ(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results, int i);
	};
}

