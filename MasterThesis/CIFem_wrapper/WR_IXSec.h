#pragma once
#include "ICrossSection.h"

namespace CIFem_wrapper
{

	public ref class WR_IXSec
	{
	public:
		virtual CIFem::ICrossSection* GetCrossSection() = 0;
		virtual System::String^ ToString() override { return "Undefined Crossection"; }
	};

}