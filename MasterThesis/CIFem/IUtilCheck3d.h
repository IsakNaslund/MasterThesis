#pragma once
#include "CIFem_dll.h"
#include "IUtilisationCheck.h"
#include "ICrossSection.h"
#include "Material.h"
#include "ElementResults3d.h"

namespace CIFem
{
	class IUtilCheck3d : public IUtilisationCheck
	{
		friend class Element3dChecks;
	protected:
		std::string _checkName;
	public:
		IUtilCheck3d();
		~IUtilCheck3d();
		virtual double CheckElementUtilisations(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results, std::string resName, int elementPosition) = 0;
	};
}

