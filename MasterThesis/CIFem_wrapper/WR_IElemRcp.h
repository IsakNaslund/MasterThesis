#pragma once
#include "IElementRcp.h"
#include <memory>

namespace CIFem_wrapper
{

	public ref class WR_IElemRcp
	{

	public:
		virtual std::shared_ptr<CIFem::IElementRcp> GetRecipe()= 0;
		virtual System::String ^ GetSectionString() = 0;
	};

}