#include "stdafx.h"
#include "WR_DebugClass.h"

namespace CIFem_wrapper
{
	WR_DebugClass::WR_DebugClass()
	{
		_debugClass = new CIFem::DebugClass();
	}


	WR_DebugClass::~WR_DebugClass()
	{
		delete _debugClass;
		_debugClass = 0;
	}


	void WR_DebugClass::DivByZero(int i)
	{
		return _debugClass->DivByZero(i);
	}

	void WR_DebugClass::ThrowCrazyException()
	{
		try
		{
			return _debugClass->ThrowCrazyException();
		}
		catch (const std::exception& e)
		{
			System::Exception ^ sysE = Utilities::ConvertException(e);

			throw sysE;
		}
	}
}
