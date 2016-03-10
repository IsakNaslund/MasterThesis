#pragma once

#include "CIFem_dll.h"
#include "Element3d.h"
#include "IUtilisationCheck.h"
#include "IUtilCheck3d.h"

namespace CIFem
{
	class CIFEM_API UtilCheck3dBasic : public IUtilCheck3d
	{
	
	public:
		UtilCheck3dBasic();
		~UtilCheck3dBasic();

		void CheckElementUtilisations(ICrossSection xSec, Material mat, ElementResults3d results) override;
		double AxialCheck(Element3d * elem);
	
	
	};
}

