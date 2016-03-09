#include "stdafx.h"
#include "WR_Node3d.h"

using namespace CIFem_wrapper;

WR_Node3d::WR_Node3d()
{
	_node = gcnew m_shared_ptr<CIFem::INode>();
}

WR_Node3d::WR_Node3d(CIFem::XYZ location)
{
	_node = gcnew m_shared_ptr<CIFem::INode>(new CIFem::Node3d(location));
}

WR_Node3d::WR_Node3d(CIFem::XYZ location, int index)
{
	_node = gcnew m_shared_ptr<CIFem::INode>(new CIFem::Node3d(location, index));
}

WR_Node3d::WR_Node3d(const double x, const double y, const double z)
{
	_node = gcnew m_shared_ptr<CIFem::INode>(new CIFem::Node3d(CIFem::XYZ(x,y,z)));
}

WR_Node3d::WR_Node3d(const double x, const double y, const double z, int index)
{
	_node = gcnew m_shared_ptr<CIFem::INode>(new CIFem::Node3d(CIFem::XYZ(x, y, z),index));
}

CIFem_wrapper::WR_Node3d::WR_Node3d(const double x, const double y, const double z, WR_Restraint^ wr_Rest)
{
	_node = gcnew m_shared_ptr<CIFem::INode>(new CIFem::Node3d(CIFem::XYZ(x, y, z), *wr_Rest->GetRestraint()));
}

CIFem_wrapper::WR_Node3d::WR_Node3d(const double x, const double y, const double z, WR_Restraint ^ wr_Rest, WR_Vector^ ptLoad, WR_Vector^ ptMoment)
{
	_node = gcnew m_shared_ptr<CIFem::INode>(new CIFem::Node3d(CIFem::XYZ(x, y, z), *wr_Rest->GetRestraint(), ptLoad->GetAsVector3d(), ptMoment->GetAsVector3d()));
}

WR_Node3d::~WR_Node3d()
{

}
