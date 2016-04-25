#include "DebugClass.h"


namespace CIFem
{
	DebugClass::DebugClass()
	{
	}


	DebugClass::~DebugClass()
	{
	}

	void DebugClass::DivByZero(int i)
	{
		double res = 1 / i;
	}


	void DebugClass::ThrowCrazyException()
	{
		std::exception e("Crrrrrrrazy exception!");

		throw e;
	}
}
