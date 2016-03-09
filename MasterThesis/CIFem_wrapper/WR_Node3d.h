#pragma once
#include "Node3d.h"
#include "WR_INode.h"
#include "WR_Restraint.h"

namespace CIFem_wrapper
{

	public ref class WR_Node3d : public WR_INode
	{
	public:
		WR_Node3d();
		WR_Node3d(CIFem::XYZ location);
		WR_Node3d(CIFem::XYZ location, int index);
		WR_Node3d(const double x, const double y, const double z);
		WR_Node3d(const double x, const double y, const double z, int index);
		WR_Node3d(const double x, const double y, const double z, WR_Restraint^ wr_Rest);
		WR_Node3d(const double x, const double y, const double z, WR_Restraint^ wr_Rest, WR_Vector^ ptLoad, WR_Vector^ ptMoment);
		~WR_Node3d();
	};

}