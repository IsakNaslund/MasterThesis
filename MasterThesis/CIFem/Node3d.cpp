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

std::vector<std::shared_ptr<DOF>> CIFem::Node3d::GetTranslationDofs()
{
	if (_dof.size() >= 3)
	{
		std::vector<std::shared_ptr<DOF>> translationDofs;
		for (int i = 0; i < 3; i++)
			translationDofs.push_back(_dof[i]);

		return translationDofs;
	}
	else
		throw std::exception("Node dofs unaccessible!");
}

std::vector<std::shared_ptr<DOF>> CIFem::Node3d::GetRotationDofs()
{
	throw std::exception("Function CIFem::Node3d::GetRotationDofs() not implemented!");
}

double CIFem::Node3d::DistanceTo(const Node3d* other) const
{
	return DistanceTo(other->_location);
}

double CIFem::Node3d::DistanceTo(const INode* other) const
{

	if (const Node3d * node3d = dynamic_cast<const Node3d*>(other))
	{
		return DistanceTo(node3d);
	}
	else
	{
		throw std::exception("Can only meassure distance between points of the same type");
		return -1;
	}


}

double CIFem::Node3d::DistanceTo(const XYZ & otherPt) const
{
	return this->_location.DistanceTo(otherPt);
}

void CIFem::Node3d::InitNewDofs(int n)
{
	for (int i = 0; i < 6; i++)
	{
		std::shared_ptr<DOF> ptr(new DOF(n+i));
		_dof.push_back(ptr);
	}
}
