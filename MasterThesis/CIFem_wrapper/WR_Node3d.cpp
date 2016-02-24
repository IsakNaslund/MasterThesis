#include "stdafx.h"
#include "WR_Node3d.h"


WR_Node3d::WR_Node3d()
{
	_node = new CIFem::Node3d();
}

WR_Node3d::WR_Node3d(CIFem::XYZ location)
{
	_node = new CIFem::Node3d(location);
}

WR_Node3d::WR_Node3d(CIFem::XYZ location, int index)
{
	_node = new CIFem::Node3d(location, index);
}

WR_Node3d::WR_Node3d(const double x, const double y, const double z)
{
	_node = new CIFem::Node3d(CIFem::XYZ(x,y,z));
}

WR_Node3d::WR_Node3d(const double x, const double y, const double z, int index)
{
	_node = new CIFem::Node3d(CIFem::XYZ(x, y, z),index);
}

WR_Node3d::~WR_Node3d()
{

}
