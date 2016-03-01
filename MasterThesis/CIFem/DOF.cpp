#include "DOF.h"

using namespace CIFem;

CIFem::DOF::DOF()
{
	_index = 0;
	_hasTransformedBC = false;
	_f = 0;
}

DOF::DOF(unsigned int index)
{
	_index = index;
	_f = 0;
}


DOF::~DOF()
{
}

int DOF::GetIndex()
{
	return _index;
}
