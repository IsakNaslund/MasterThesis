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

void CIFem::DOF::SetUpBoundaryCondition(bool isRestrained, double dist)
{
	_hasSetTranslation = isRestrained;
	_Am = dist;
}

inline void CIFem::DOF::SetResults(double a, double f)
{
	_resAs = a;
	_resF = f;
}

int DOF::GetIndex()
{
	return _index;
}
