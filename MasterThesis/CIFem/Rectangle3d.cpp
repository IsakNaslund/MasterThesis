#include "Rectangle3d.h"

using namespace CIFem;



CIFem::Rectangle3d::Rectangle3d()
{
}

CIFem::Rectangle3d::Rectangle3d(const double height, const double width)
{
	_height = height;
	_width = width;
	CalcSectionProperties();
}


CIFem::Rectangle3d::~Rectangle3d()
{
}

void Rectangle3d::CalcSectionProperties()
{
	double area = _height*_width;
	double iz = (_width*_height*_height*_height) / 12;
	double iy = (_height*_width*_width*_width) / 12;

	_secProp = SectionProperties(area, iy, iz, CalcTorsionalStiffness(iy, iz));

}

double CIFem::Rectangle3d::GetHeight() const
{
	return _height;
}

double CIFem::Rectangle3d::GetWidth() const 
{
	return _width;
}

double CIFem::Rectangle3d::CalcTorsionalStiffness(const double iy, const double iz)
{
	return CalcAlphaFactor()*(iy + iz);
}

//Correction factor to compensate for st vernants torsion
//Found on page 219 in Struktur mekanik book by K-G
double CIFem::Rectangle3d::CalcAlphaFactor()
{
	double ratio = _height / _width;
	
	if (ratio < 1)
	{	
		//Failure, height needs to be greater than width
	}
	else if (ratio < 1.5)
	{
		return CIFem::Interpolate(ratio, 0.724, 0.846, 1, 1.5);
	}
	else if (ratio < 2)
	{
		return CIFem::Interpolate(ratio, 0.550, 0.724, 1.5, 2);
	}
	else if (ratio < 2.5)
	{
		return CIFem::Interpolate(ratio, 0.412, 0.550, 2, 2.5);
	}
	else if (ratio < 3)
	{
		return CIFem::Interpolate(ratio, 0.316, 0.412, 2.5, 3);
	}
	else if (ratio < 4)
	{
		return CIFem::Interpolate(ratio, 0.198, 0.316, 3, 4);
	}
	else if (ratio < 6)
	{
		return CIFem::Interpolate(ratio, 0.097, 0.198, 4, 6);
	}
	else if (ratio < 10)
	{
		return CIFem::Interpolate(ratio, 0.037, 0.097, 6, 10);
	}
	else
	{
		//To thin....
	}
}
