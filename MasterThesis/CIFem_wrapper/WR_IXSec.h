#pragma once
#include "ICrossSection.h"
#include "m_shared_ptr.h"

namespace CIFem_wrapper
{

	public ref class WR_IXSec
	{
	public:
		virtual std::shared_ptr<CIFem::ICrossSection> GetCrossSection() = 0;
		virtual System::String^ ToString() override { return "Undefined Crossection"; }
	};

}