#include "SectionProperties.h"

CIFem::SectionProperties::SectionProperties()
{
}

CIFem::SectionProperties::SectionProperties(const double area)
{
	_area = area;
	_Iy = -1;
	_Iz = -1;
	_Kv = -1;
}

CIFem::SectionProperties::SectionProperties(const double area, const double i)
{
	_area = area;
	_Iz = i;
	_Iy = -1;
	_Kv = -1;
}

CIFem::SectionProperties::SectionProperties(const double area, const double iy, const double iz, const double kv)
{
	_area = area;
	_Iy = iy;
	_Iz = iz;
	_Kv = kv;
}

CIFem::SectionProperties::~SectionProperties()
{
}
