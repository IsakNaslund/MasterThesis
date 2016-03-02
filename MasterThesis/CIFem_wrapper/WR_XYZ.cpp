#include "stdafx.h"
#include "WR_XYZ.h"

using namespace CIFem_wrapper;

WR_XYZ::WR_XYZ()
{
	_xyz = gcnew m_shared_ptr<XYZ>(new XYZ());
}

WR_XYZ::WR_XYZ(double x, double y, double z)
{
	_xyz = gcnew m_shared_ptr<XYZ>(new XYZ(x, y, z));
}

WR_XYZ::~WR_XYZ()
{
	//delete _xyz;
	//_xyz = 0;
}

std::shared_ptr<XYZ> CIFem_wrapper::WR_XYZ::GetPos()
{
	return _xyz.operator std::shared_ptr<CIFem::XYZ>();
}
