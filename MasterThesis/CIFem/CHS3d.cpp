#include "CHS3d.h"



CIFem::CHS3d::CHS3d()
{
}

CIFem::CHS3d::CHS3d(double radius, double thickness)
{
	if (thickness > radius / 2)
	{
		throw std::invalid_argument("Thickness needs to be smaller than height and width");
	}
	_radius = radius;
	_thickness = thickness;

	CalcSectionProperties();
}


CIFem::CHS3d::~CHS3d()
{
}

void CIFem::CHS3d::CalcSectionProperties()
{
	double area, iy, iz, kv;

	area = (pow(_radius, 2) - pow(_radius-_thickness, 2)) * M_PI;
	
	iy = (M_PI / 4)*(pow(_radius, 4) - pow(_radius - _thickness, 4));
	iz = iy;
	kv = (M_PI / 2)*(pow(_radius, 4) - pow(_radius - _thickness, 4));

	_secProp = SectionProperties(area, iy, iz, kv);
}

double CIFem::CHS3d::CalcFirstMomentOfArea()
{
	return (pow(_radius, 3) - pow(_radius - _thickness, 3)) * 4 / 3;
}

std::string CIFem::CHS3d::ToString()
{
	return "CHS" + std::to_string(_radius) + "x" + std::to_string(_thickness);
}
