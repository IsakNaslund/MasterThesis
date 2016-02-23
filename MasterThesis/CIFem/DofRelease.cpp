#include "DofRelease.h"



CIFem::DofRelease::DofRelease(bool isFixed)
{
	_isFixed = isFixed;
	_stiffness = 0;
}

CIFem::DofRelease::DofRelease(double stiffness)
{
	_stiffness = stiffness;
	_isFixed = false;
}

CIFem::DofRelease::~DofRelease()
{
}
