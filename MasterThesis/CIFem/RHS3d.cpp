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

void CIFem::RHS3d::CalcSectionProperties()
{
	double area, iy, iz, kv;
	
	area = 2 * (_height + _width)*_thickness;
	iy = 2 * (_thickness*pow(_height, 3) / 12 + (_width - _thickness)*pow(_thickness, 3) / 12 + (_width - _thickness)*_thickness*pow(((_height - _thickness) / 2), 2));
	iz = 2 * (_thickness*pow(_width, 3) / 12 + (_height - _thickness)*pow(_thickness, 3) / 12 + (_height - _thickness)*_thickness*pow(((_width - _thickness) / 2), 2));

	_secProp= SectionProperties(area, iy, iz, -1);
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
