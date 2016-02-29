#pragma once
#include "IElementRcp.h"

namespace CIFem_wrapper
{

	public ref class WR_IElemRcp
	{

	public:
		virtual CIFem::IElementRcp* GetRecipe()= 0;
	};

}