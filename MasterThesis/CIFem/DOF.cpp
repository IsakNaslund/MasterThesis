#include "DOF.h"

using namespace CIFem;

CIFem::DOF::DOF()
{
	_index = 0;
	_hasSetTranslation = false;
	_f = 0;
}

DOF::DOF(unsigned int index)
{
	_index = index;
	_hasSetTranslation = false;
	_f = 0;
}


DOF::~DOF()
{
}

bool DOF::HasSetTranslation()
{
	return _hasSetTranslation;
}

double DOF::GetTranslation()
{
	return _a;
}

int DOF::GetIndex()
{
	return _index;
}

void DOF::SetTranslation(double a)
{
	_a = a;
	_hasSetTranslation = true;
}
