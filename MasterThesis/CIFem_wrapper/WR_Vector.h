#pragma once

#include <vector>
#include "Vector3d.h"
#include "m_shared_ptr.h"

public ref class WR_Vector
{
	double _x, _y, _z;
public:
	WR_Vector();
	WR_Vector(const double x, const double y, const double z);

	CIFem::Vector3d GetAsVector3d();
	std::vector<double> GetAsCppVector();
	
};

