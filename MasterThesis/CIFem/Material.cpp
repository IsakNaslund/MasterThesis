#include "Material.h"



CIFem::Material::Material()
{
}

CIFem::Material::Material(double E, double poi, double rho)
{
	_E = E;
	_poi = poi;
	_rho = rho;
}


CIFem::Material::~Material()
{
}

double CIFem::Material::E()
{
	return _E;
}

double CIFem::Material::Rho()
{
	return _rho;
}

double CIFem::Material::G()
{
	return _E / (2 * (_poi + 1));
}

double CIFem::Material::Poisson()
{
	return _poi;
}
