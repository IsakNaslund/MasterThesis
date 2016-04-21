#pragma once
#include "ICrossSection.h"
#define _USE_MATH_DEFINES

#include <math.h>

namespace CIFem
{
	class CIFEM_API CircularSolid3d : public ICrossSection
	{
	protected:
		double _radius;

	public:
		CircularSolid3d();
		CircularSolid3d(double radius);
		~CircularSolid3d();

	private:
		void CalcSectionProperties();
		double CalcFirstMomentOfArea();

		// Inherited via ICrossSection
		virtual double CheckCombAxialBending(double N, double Myy, double Mzz) override;
		virtual double CheckShearY(double Vy) override;
		virtual double CheckShearZ(double Vz) override;

		bool DirectionDependant() { return false; }

		std::string ToString() override;
	};
}

