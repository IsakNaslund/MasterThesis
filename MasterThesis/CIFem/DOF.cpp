#include "DOF.h"

using namespace CIFem;

CIFem::DOF::DOF()
{
	_index = 0;
	_hasTransformedBC = false;
	_hasSetTranslation = false;
	_f = 0;
}

DOF::DOF(unsigned int index)
{
	_index = index;
	_hasTransformedBC = false;
	_hasSetTranslation = false;
	_f = 0;
}


DOF::~DOF()
{
}

void CIFem::DOF::AddLoad(const double load)
{
	_f += load;
}

int DOF::GetIndex()
{
	return _index;
}
