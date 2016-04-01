#pragma once

#include "SectionProperties.h"
#include "CIFem_dll.h"
#include <vector>
#include <string>

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

		//Checks
		virtual double CheckCombAxialBending(double N, double Myy, double Mzz) = 0;	// Returns sigma
		virtual double CheckShearY(double Vy) = 0;	// Returns tau
		virtual double CheckShearZ(double Vz) = 0;	// Returns tau

		// Returns a string defining the cross section
		// Different format for each cross section. Needs to be handled in wrappers.
		virtual std::string ToString() = 0;
	};

}