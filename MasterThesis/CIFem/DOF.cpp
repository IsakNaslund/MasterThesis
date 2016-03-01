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
}


DOF::~DOF()
{
}

int DOF::GetIndex()
{
	return _index;
}
