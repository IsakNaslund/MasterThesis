#pragma once
#include "ICrossSection.h"

namespace CIFem_wrapper
{

	ref class WR_IXSec
	{
	protected:
		CIFem::ICrossSection* _xSec;
	public:
		~WR_IXSec();
		CIFem::ICrossSection* GetCrossSection();
	};

}