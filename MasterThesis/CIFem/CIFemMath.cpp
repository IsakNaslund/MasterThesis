#include "CIFemMath.h"


double CIFem::Interpolate(const double val, const double upBound, const double lowBound, const double upVal, const double lowVal)
{
	return lowBound + (upBound - lowBound)*(val-lowVal) / (upVal - lowVal);
}
