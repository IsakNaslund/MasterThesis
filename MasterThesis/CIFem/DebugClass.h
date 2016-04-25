#pragma once
#include "CIFem_dll.h"
#include <exception>

namespace CIFem
{
	class CIFEM_API DebugClass
	{
	public:
		DebugClass();
		~DebugClass();

		void DivByZero(int i);
		void ThrowCrazyException();
	};
}

