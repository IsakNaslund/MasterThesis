#include "stdafx.h"
#include "WR_IXSec.h"



WR_IXSec::~WR_IXSec()
{
	delete _xSec;
	_xSec = 0;
}

CIFem::ICrossSection * WR_IXSec::GetCrossSection()
{
	return _xSec;
}
