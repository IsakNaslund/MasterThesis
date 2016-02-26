#include "DisplacementRestraint.h"

namespace CIFem
{
	DisplacementRestraint::DisplacementRestraint(XYZ coord, Vector3d direction, double displacement)
	{
		_coord = coord;
		_direction = direction;
		_displacement = displacement;
	}

	DisplacementRestraint::~DisplacementRestraint()
	{
	}

}