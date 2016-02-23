#include "Node3d.h"

using namespace CIFem;

Node3d::Node3d()
{
	InitNewDofs(0);
}

CIFem::Node3d::Node3d(const XYZ location)
{
	_location = location;
	InitNewDofs(0);
}

CIFem::Node3d::Node3d(const XYZ location, unsigned int startIndex)
{
	_location = location;
	InitNewDofs(startIndex);
}


Node3d::~Node3d()
{
	_dof.clear();
	
}

std::vector<std::shared_ptr<DOF>> CIFem::Node3d::GetDofs()
{
	return _dof;
}

void CIFem::Node3d::InitNewDofs(int n)
{
	for (int i = 0; i < 6; i++)
	{
		std::shared_ptr<DOF> ptr(new DOF(n));
		_dof.push_back(ptr);
	}
}
