#include "DofRelease.h"



CIFem::DofRelease::DofRelease(bool isFixed)
{
	_isFixed = isFixed;
	_stiffness = 0;
	_index = 0;
}

CIFem::DofRelease::DofRelease(double stiffness)
{
	if (stiffness < 0)
	{
		_isFixed = true;
		_stiffness = 0;
	}
	else
	{
		_stiffness = stiffness;
		_isFixed = false;
	}

	_index = 0;
}

CIFem::DofRelease::~DofRelease()
{
}

bool CIFem::DofRelease::IsFixed()
{
	return _isFixed;
}

double CIFem::DofRelease::Stiffness()
{
	return _stiffness;
}
