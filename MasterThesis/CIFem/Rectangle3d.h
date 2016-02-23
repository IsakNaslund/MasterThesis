#pragma once

//#include "ISectionProperties.h"
#include "SecPropBeam3d.h"
#include "CIFemMath.h"
#include "ICrossSection.h"

namespace CIFem
{

	class Rectangle3d :ICrossSection
	{
		double _height;
		double _width;
	public:
		Rectangle3d();
		Rectangle3d(const double height, const double width);
		~Rectangle3d();
		SectionProperties CalcSectionProperties();

	private:

		double CalcTorsionalStiffness(const double iy, const double iz);
		double CalcAlphaFactor();
	};
}

