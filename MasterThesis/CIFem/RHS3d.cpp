#include "RHS3d.h"

using namespace CIFem;

RHS3d::RHS3d()
{
}

CIFem::RHS3d::RHS3d(double height, double width, double thickness)
{
	if (thickness > height / 2 || thickness > width / 2)
	{
		throw std::invalid_argument("Thickness needs to be smaller than height and width");
	}
	_height = height;
	_width = width;
	_thickness = thickness;
}


RHS3d::~RHS3d()
{
}

SectionProperties CIFem::RHS3d::CalcSectionProperties()
{
	double area, iy, iz, kv;
	
	area = 2 * (_height + _width)*_thickness;
	iy = 2 * (_thickness*pow(_height, 3) / 12 + (_width - _thickness)*pow(_thickness, 3) / 12 + (_width - _thickness)*_thickness*pow(((_height - _thickness) / 2), 2));
	iz = 2 * (_thickness*pow(_width, 3) / 12 + (_height - _thickness)*pow(_thickness, 3) / 12 + (_height - _thickness)*_thickness*pow(((_width - _thickness) / 2), 2));

	return SectionProperties(area, iy, iz, -1);
}
