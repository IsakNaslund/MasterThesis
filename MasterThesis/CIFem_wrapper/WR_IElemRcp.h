#pragma once
#include "IElementRcp.h"

namespace CIFem_wrapper
{

	ref class WR_IElemRcp
	{
	protected:
		CIFem::IElementRcp* _eleRcp;
	public:
		~WR_IElemRcp();
		CIFem::IElementRcp* GetRecipe();
	};

}