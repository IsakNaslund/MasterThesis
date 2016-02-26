#pragma once

#include <vector>

public ref class WR_Vector
{
	double _x, _y, _z;
public:
	WR_Vector();
	WR_Vector(const double x, const double y, const double z);
	std::vector<double> GetAsCppVector();
	
};

