#pragma once
#include "CIFem_dll.h"
#include "IUtilisationCheck.h"
#include "ICrossSection.h"
#include "Material.h"

namespace CIFem
{
	class IUtilCheck3d : public IUtilisationCheck
	{
	public:
		IUtilCheck3d();
		~IUtilCheck3d();
		virtual void CheckElementUtilisations() = 0;
	};
}

