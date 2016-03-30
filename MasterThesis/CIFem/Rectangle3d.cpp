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
	double iy = (_width*_height*_height*_height) / 12;
	double iz = (_height*_width*_width*_width) / 12;

	_secProp = SectionProperties(area, iy, iz, CalcTorsionalStiffness(iy, iz));
	_Nmax = area;
	_Vymax = iz*_height / (pow(_width, 2)*_height / 8);
	_Vzmax = iy*_height / (pow(_height, 2)*_width / 8);
	_Mymax = iy / (_width / 2);
	_Mzmax = iz / (_height / 2);
	//No checks for torsion yet implemented
	_Tmax = 100000000000;
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
		return CIFem::Interpolate(ratio, 0.846, 0.724, 1, 1.5);
	}
	else if (ratio < 2)
	{
		return CIFem::Interpolate(ratio, 0.724, 0.550, 1.5, 2);
	}
	else if (ratio < 2.5)
	{
		return CIFem::Interpolate(ratio, 0.550, 0.412, 2, 2.5);
	}
	else if (ratio < 3)
	{
		return CIFem::Interpolate(ratio, 0.412, 0.316, 2.5, 3);
	}
	else if (ratio < 4)
	{
		return CIFem::Interpolate(ratio, 0.316, 0.198, 3, 4);
	}
	else if (ratio < 6)
	{
		return CIFem::Interpolate(ratio, 0.198, 0.097, 4, 6);
	}
	else if (ratio < 10)
	{
		return CIFem::Interpolate(ratio, 0.097, 0.037, 6, 10);
	}
	else
	{
		//To thin....
	}
}

// Performs a shear check in the local y-direction
double CIFem::Rectangle3d::CheckShearY(double Vy)
{
	// "Flip" b and h since check is done in y-dir 
	double h = _width;
	double b = _height;
	
	// Assumptions: Shear checked in middle of section
	double S = pow(h, 2)*b / 8;
	double I = _secProp.Iz();

	return (S*Vy) / (I*h);
}

// Performs a shear check in the local z-direction
double CIFem::Rectangle3d::CheckShearZ(double Vz)
{
	double h = _height;
	double b = _width;

	// Assumptions: Shear checked in middle of section
	double S = pow(h, 2)*b / 8;
	double I = _secProp.Iy();

	return (S*Vz) / (I*b);
}

double CIFem::Rectangle3d::CheckCombAxialBending(double N, double Myy, double Mzz)
{
	std::vector<double> yMinMax = { -_width / 2, _width / 2 };
	std::vector<double> zMinMax = { -_height / 2, _height / 2 };

	double absmax = 0;
	double val;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			val = (N / _secProp.A()) + ((Myy / _secProp.Iy()) * zMinMax[i]) + ((Mzz / _secProp.Iz()) * yMinMax[j]);
			if (abs(val) > abs(absmax))
				absmax = val;
		}
	}

	return absmax;
}
