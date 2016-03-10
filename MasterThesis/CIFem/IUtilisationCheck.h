#pragma once

#include "CIFem_dll.h"
#include "IElement.h"
#include <vector>
#include <memory>

namespace CIFem
{
	class CIFEM_API IUtilisationCheck
	{
	public:
		IUtilisationCheck();
		~IUtilisationCheck();

		//virtual void CheckElementUtilisations(std::vector<std::shared_ptr<IElement>> elements) = 0;
	};
}

