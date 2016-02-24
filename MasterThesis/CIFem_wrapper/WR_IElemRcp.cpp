#include "stdafx.h"
#include "WR_IElemRcp.h"



WR_IElemRcp::~WR_IElemRcp()
{
	delete _eleRcp;
	_eleRcp = 0;
}

CIFem::IElementRcp * WR_IElemRcp::GetRecipe()
{
	return _eleRcp;
}
