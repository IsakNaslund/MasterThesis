#include "PointLoad.h"



PointLoad::PointLoad()
{
}

CIFem::PointLoad::PointLoad(Vector3d force, Vector3d moment, XYZ pos)
{
	_force = force;
	_moment = moment;
	_pos = pos;
}


PointLoad::~PointLoad()
{
}
