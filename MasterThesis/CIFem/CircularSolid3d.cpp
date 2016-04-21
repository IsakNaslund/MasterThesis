#include "CircularSolid3d.h"



CIFem::CircularSolid3d::CircularSolid3d()
{
}

CIFem::CircularSolid3d::CircularSolid3d(double radius)
{
	_radius = radius;

	CalcSectionProperties();
}


CIFem::CircularSolid3d::~CircularSolid3d()
{
}


void CIFem::CircularSolid3d::CalcSectionProperties()
{
	double area, iy, iz, kv;

	area = pow(_radius, 2) * M_PI;

	iy = (M_PI / 4)*pow(_radius, 4);
	iz = iy;
	kv = (M_PI / 2)*pow(_radius, 4);

	_secProp = SectionProperties(area, iy, iz, kv);
}

double CIFem::CircularSolid3d::CalcFirstMomentOfArea()
{
	return pow(_radius, 3) * 4 / 3;
}

double CIFem::CircularSolid3d::CheckCombAxialBending(double N, double Myy, double Mzz)
{
	// Since the section is circular, Iy == Iz, so calculate a principal moment
	// and use I for any axis to check it.

	double M = sqrt(pow(Myy, 2) + pow(Mzz, 2));
	
	if (N < 0)
		return N / _secProp.A() - (M / _secProp.Iy())*_radius;
	else
		return N / _secProp.A() + (M / _secProp.Iy())*_radius;
}

// Currently not implemented, will return -1
double CIFem::CircularSolid3d::CheckShearY(double Vy)
{
	double Sy = CalcFirstMomentOfArea();

	return -1;
}

// Currently not implemented, will return -1
double CIFem::CircularSolid3d::CheckShearZ(double Vz)
{
	double Sy = CalcFirstMomentOfArea();

	return -1;
}

std::string CIFem::CircularSolid3d::ToString()
{
	return "CSS" + std::to_string(_radius);
}