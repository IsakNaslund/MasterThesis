#pragma once
#include "CIFem_dll.h"

namespace CIFem
{
	class CIFEM_API DofRelease
	{
		bool _isFixed;
		double _stiffness;

	public:
		DofRelease(bool);		// True = fixed, false = pinned
		DofRelease(double);		// Connection stiffness
		~DofRelease();
	};
}

