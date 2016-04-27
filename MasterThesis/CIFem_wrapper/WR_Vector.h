#pragma once

#include <vector>
#include "Vector3d.h"
#include "m_shared_ptr.h"
#include "WR_XYZ.h"

public ref class WR_Vector
{
	double _x, _y, _z;
public:
	WR_Vector();
	WR_Vector(const double x, const double y, const double z);

	CIFem::Vector3d GetAsVector3d();
	std::vector<double> GetAsCppVector();
	
	property double X {double get() { return _x; }}
	property double Y {double get() { return _y; }}
	property double Z {double get() { return _z; }}
};

