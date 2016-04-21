#pragma once
#include "ICrossSection.h"
#include "m_shared_ptr.h"
#include "Utilities.h"

namespace CIFem_wrapper
{

	public ref class WR_IXSec
	{
	public:
		virtual std::shared_ptr<CIFem::ICrossSection> GetCrossSection() = 0;
		virtual System::String^ ToString() override;
	};

}