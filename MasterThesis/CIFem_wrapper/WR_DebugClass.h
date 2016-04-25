#pragma once
#include "DebugClass.h"
#include <string>
#include "Utilities.h"

namespace CIFem_wrapper
{

	public ref class WR_DebugClass
	{
		CIFem::DebugClass * _debugClass;

	public:
		WR_DebugClass();
		~WR_DebugClass();

		void DivByZero(int i);
		void ThrowCrazyException();
	};
}

