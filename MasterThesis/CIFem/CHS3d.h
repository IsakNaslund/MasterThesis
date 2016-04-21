#pragma once
#include "CircularSolid3d.h"
#define _USE_MATH_DEFINES

#include <math.h>

namespace CIFem
{
	class CIFEM_API CHS3d : public CircularSolid3d
	{
		double _thickness;

	public:
		CHS3d();
		CHS3d(double radius, double thickness);
		~CHS3d();

	private:
		void CalcSectionProperties();
		double CalcFirstMomentOfArea();

		//virtual double CheckShearY(double Vy) override;	// Currently implemented through base
		//virtual double CheckShearZ(double Vz) override;	// Currently implemented through base

		bool DirectionDependant() { return false; }

		std::string ToString() override;
	};
}

