#pragma once

#include "SectionProperties.h"
#include "CIFem_dll.h"

namespace CIFem
{
	class CIFEM_API ICrossSection
	{
	protected:
		SectionProperties _secProp;
		virtual void CalcSectionProperties() = 0;

	public:


		inline virtual double GetArea() const { return _secProp.A(); }
		inline virtual double  GetIy() const { return _secProp.Iy(); }
		inline virtual double  GetIz() const { return _secProp.Iz(); }
		inline virtual double  GetKv() const { return _secProp.Kv(); }
	};

}