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

	CalcSectionProperties();
}


RHS3d::~RHS3d()
{
}

void CIFem::RHS3d::CalcSectionProperties()
{
	double area, iy, iz, kv;
	
	area = 2 * (_height + _width)*_thickness;
	iy = 2 * (_thickness*pow(_height, 3) / 12 + (_width - _thickness)*pow(_thickness, 3) / 12 + (_width - _thickness)*_thickness*pow(((_height - _thickness) / 2), 2));
	iz = 2 * (_thickness*pow(_width, 3) / 12 + (_height - _thickness)*pow(_thickness, 3) / 12 + (_height - _thickness)*_thickness*pow(((_width - _thickness) / 2), 2));

	_secProp= SectionProperties(area, iy, iz, CalcStVenantsTorsionConstant());
}

double CIFem::RHS3d::CheckCombAxialBending(double N, double Myy, double Mzz)
{
	std::vector<double> yMinMax = { -_width / 2, _width / 2 };
	std::vector<double> zMinMax = { -_height / 2, _height / 2 };

	double absmax = 0;
	double val;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			val = (N / _secProp.A()) + ((Myy / _secProp.Iy()) * zMinMax[i]) + ((Mzz / _secProp.Iz()) * yMinMax[i]);
			if (abs(val) > abs(absmax))
				absmax = val;
		}
	}

	return absmax;
}

double CIFem::RHS3d::CheckShearY(double Vy)
{
	// Check performed in middle of section

	// Assign local variables for consistency with function CheckShearZ
	double b = _height;
	double tf = _thickness;
	double tw = _thickness;
	double hw = _width - tf;

	double I = _secProp.Iz();
	double S = tw*pow(hw, 2) + (b / 2)*(pow(hw + tf, 2) - pow(hw, 2));
	double t = _thickness;

	return (Vy*S) / (I*t);
}


double CIFem::RHS3d::CheckShearZ(double Vz)
{
	// Check performed in middle of section

	// Assign local variables for consistency with function CheckShearY
	double b = _width;
	double tf = _thickness;
	double tw = _thickness;
	double hw = _height - tf;
	
	double I = _secProp.Iy();
	double S = tw*pow(hw, 2) + (b / 2)*(pow(hw + tf, 2) - pow(hw, 2));
	double t = _thickness;

	return (Vz*S)/(I*t);
}

double CIFem::RHS3d::CalcStVenantsTorsionConstant()
{
	//Calculated according to:
	//http://www.cisc-icca.ca/files/technical/techdocs/updates/torsionprop.pdf

	//Valid for thinwalled sections _width/_thickness >= 10. Assuming true for now...

	//Calculating without knowing corner radius
	double Rc, Ap, p;

	Rc = 1.5*_thickness;     // = (Ro-Ri)/2
	Ap = (_width - _thickness)*(_height - _thickness) - pow(Rc, 2)*(4 - M_PI);
	p = 2 * ((_width - _thickness) + (_height - _thickness)) - 2 * Rc*(4 - M_PI);
	return 4 * pow(Ap, 2)*_thickness / p;
}
