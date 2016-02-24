#pragma once
#include "ICrossSection.h"

ref class WR_IXSec
{
protected:
	CIFem::ICrossSection* _xSec;
public:
	~WR_IXSec();
	CIFem::ICrossSection* GetCrossSection();
};

