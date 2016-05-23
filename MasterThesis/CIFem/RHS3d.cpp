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
	
	double ai, ao, iyi, iyo, izi, izo;

	RoundCornerRectangleProperties(_height, _width, _thickness*1.5, ao, iyo, izo);
	RoundCornerRectangleProperties(_height-_thickness*2, _width-_thickness * 2, _thickness, ai, iyi, izi);

	//double cornerArea = pow(_thickness, 2)*(5*M_PI / 16 + 7 / 4);


	//area = 2 * (_height + _width - 8 * _thickness)*_thickness + 4 * cornerArea;
	//iy = 2 * (_thickness*pow((_height - 2 * _thickness), 3) / 12 + (_width)*pow(_thickness, 3) / 12 + (_width)*_thickness*pow(((_height - _thickness) / 2), 2));
	//iz = 2 * (_thickness*pow(_width - 2 * _thickness, 3) / 12 + (_height)*pow(_thickness, 3) / 12 + (_height)*_thickness*pow(((_width - _thickness) / 2), 2));

	area = ao - ai;
	iy = iyo - iyi;
	iz = izo - izi;

	_secProp= SectionProperties(area, iy, iz, CalcStVenantsTorsionConstant());

	//_secProp = SectionProperties(ao-ai, iyo-iyi, izo-izi, CalcStVenantsTorsionConstant());

	_Nmax = area;
	double hw = _width - _thickness;
	double S = _thickness*pow(hw, 2) + (_height / 2)*(pow(hw + _thickness, 2) - pow(hw, 2));
	_Vymax = iz*_thickness / S;
	 hw = _height - _thickness;
	 S = _thickness*pow(hw, 2) + (_width / 2)*(pow(hw + _thickness, 2) - pow(hw, 2));
	_Vzmax = iy*_thickness / S;
	_Mymax = iy / (_width / 2);
	_Mzmax = iz / (_height / 2);
	//No checks for torsion yet implemented
	_Tmax = 100000000000;


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
			val = (N / _secProp.A()) + ((Myy / _secProp.Iy()) * zMinMax[i]) + ((Mzz / _secProp.Iz()) * yMinMax[j]);
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

std::string CIFem::RHS3d::ToString()
{
	return "RHS" + std::to_string(_height) + "x" + std::to_string(_width) + "x" + std::to_string(_thickness);
}

bool CIFem::RHS3d::RoundCornerRectangleProperties(double h, double b, double r, double & A, double & Iy, double & Iz)
{

	double hi = h - 2*r;
	double bi = b - 2*r;

	A = h*bi + hi*r * 2 + M_PI*pow(r, 2);

	double aint = M_PI / 16 - 4 / (9 * M_PI);

	Iy = bi*pow(h, 3) / 12 + r*pow(hi, 3) / 6;
	Iy += 4 * aint*pow(r, 4);
	Iy += pow(r, 2)*M_PI*pow((4 * r / (3 * M_PI) + hi / 2),2);


	Iz = hi*pow(b, 3) / 12 + r*pow(bi, 3) / 6;
	Iz += 4 * aint*pow(r, 4) + pow(r, 2)*M_PI*pow((4 * r / (3 * M_PI) + bi / 2),2);



	return true;
}
