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

CIFem::Node3d::Node3d(const XYZ location, Restraint restraint)
	:Node3d(location)
{
	SetRestraint(restraint);
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

void CIFem::Node3d::SetRestraint(Restraint r)
{
	_restraint = r;

	// Identify which dofs are restrained 
	// (global dofs or corrsponding if restraint is in non-global coordinates)
	std::vector<bool> releases = r.GetReleases();
	std::vector<double> displacements = r.GetDisplacements();
	for (int i = 0; i < releases.size(); i++)
		if (releases[i]) // If fixed
		{
			this->_dof[i]->_Am = displacements[i];
			this->_dof[i]->_hasSetTranslation = true;
		}
}

// Returns true if node has transformed coordinate system, false if not 
bool CIFem::Node3d::GetNodeCMatrix(const Plane globalOrientation, arma::mat & CN)
{
	if (_restraint.IsValid())
	{
		if (this->_restraint.GetCMatrix(globalOrientation, CN))
		{
			std::vector<std::shared_ptr<DOF>> dofs = this->GetDofs();
			for (int i = 0; i < dofs.size(); i++)
				dofs[i]->_hasTransformedBC = true;

			return true;
		}
	}

	// If checks fail
	return false;
}
