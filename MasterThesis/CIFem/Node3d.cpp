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

std::vector<DOF*> CIFem::Node3d::GetDofs()
{
	return _dof;
}

void CIFem::Node3d::InitNewDofs(int n)
{
	for (int i = 0; i < 6; i++)
	{
		_dof.push_back(std::shared_ptr<DOF> (new DOF(n)))
	}
}
