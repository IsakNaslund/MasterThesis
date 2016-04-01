#pragma once

#include "ICrossSection.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdexcept>


namespace CIFem
{
	class CIFEM_API RHS3d : public ICrossSection
	{
		double _height;
		double _width;
		double _thickness;
	public:
		RHS3d();
		RHS3d(double height, double width, double thickness);
		~RHS3d();

	private:
		void CalcSectionProperties();

		// Inherited via ICrossSection
		virtual double CheckCombAxialBending(double N, double Myy, double Mzz) override;
		virtual double CheckShearY(double Vy) override;
		virtual double CheckShearZ(double Vz) override;

		double CalcStVenantsTorsionConstant();

		std::string ToString() override;
	};
}

