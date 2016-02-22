#include "ElementProperty.h"

using namespace CIFem;
using namespace CIFem;

ElementProperty::ElementProperty()
{
	// Needs to be removed, bad way to do it! /C
	// Best would be to find a way of removing the constructor without arguments altogether.
	//_E = -1;
	//_G = -1;
	//_A = -1;
	//_Iyy = -1;
	//_Izz = -1;
	//_Kv = -1;
}

ElementProperty::ElementProperty(double E, double G, double A, double Iy, double Iz, double Kv)
{
	_E = E;
	_G = G;
	_A = A;
	_Iy = Iy;
	_Iz = Iz;
	_Kv = Kv;
}


ElementProperty::~ElementProperty()
{
}

double ElementProperty::GetE()
{
	return _E;
}

double ElementProperty::GetG()
{
	return _G;
}

double ElementProperty::GetA()
{
	return _A;
}

double ElementProperty::GetIy()
{
	return _Iy;
}

double ElementProperty::GetIz()
{
	return _Iz;
}

double ElementProperty::GetKv()
{
	return _Kv;
}
