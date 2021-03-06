#include "Element3dRcp.h"




CIFem::Element3dRcp::Element3dRcp()
{
}

CIFem::Element3dRcp::Element3dRcp(std::shared_ptr<Element3dRcp> other)
{
	if (other != nullptr)
	{
		this->_stPos = other->_stPos;
		this->_enPos = other->_enPos;
		this->_stRel = other->_stRel;
		this->_enRel = other->_enRel;
		this->_mat = other->_mat;
		this->_xSec = other->_xSec;
		this->SetNormal(other->_normal);
	}
}

CIFem::Element3dRcp::Element3dRcp(XYZ stPos, XYZ enPos, ReleaseBeam3d stRel, ReleaseBeam3d enRel, std::shared_ptr<ICrossSection> xSec, double matStiff, double poisonRatio, std::vector<double> normal)
{
	_stPos = stPos;
	_enPos = enPos;
	_stRel = stRel;
	_enRel = enRel;
	_xSec = xSec;
	_mat = std::shared_ptr<Material>(new Material(matStiff, poisonRatio, 0, 0));
	SetNormal(normal);	// Set normal with format check
}

CIFem::Element3dRcp::Element3dRcp(XYZ stPos, XYZ enPos, ReleaseBeam3d stRel, ReleaseBeam3d enRel, std::shared_ptr<ICrossSection> xSec, double matStiff, double poisonRatio, double density, double fu, std::vector<double> normal)
{
	_stPos = stPos;
	_enPos = enPos;
	_stRel = stRel;
	_enRel = enRel;
	_xSec = xSec;
	_mat = std::shared_ptr<Material>(new Material(matStiff, poisonRatio, density, fu));
	SetNormal(normal);	// Set normal with format check
}

CIFem::Element3dRcp::Element3dRcp(XYZ stPos, XYZ enPos, ReleaseBeam3d stRel, ReleaseBeam3d enRel, std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> material, std::vector<double> normal)
{
	_stPos = stPos;
	_enPos = enPos;
	_stRel = stRel;
	_enRel = enRel;
	_xSec = xSec;
	_mat = material;
	SetNormal(normal);	// Set normal with format check
}

CIFem::Element3dRcp::Element3dRcp(XYZ stPos, XYZ enPos, ReleaseBeam3d stRel, ReleaseBeam3d enRel, std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> material, std::vector<double> normal, std::shared_ptr<Element3dOptProp> sectionGroup)
	: Element3dRcp(stPos, enPos, stRel, enRel, xSec, material, normal)
{
	_optimizationProperties = sectionGroup;
}

std::vector<std::shared_ptr<CIFem::IElement>> CIFem::Element3dRcp::CreateElement(std::vector<std::shared_ptr<INode>> & systemNodes)
{
	std::shared_ptr<INode> stNode, enNode;
	std::vector<std::shared_ptr<CIFem::IElement>> newElements;

	bool stFound = false;
	bool enFound = false;

	for each (std::shared_ptr<INode> n in systemNodes)
	{
		if (!stFound && n->DistanceTo(_stPos) < GlobalTol)
		{
			stNode = n;
			stFound = true;
		}
		else if (!enFound && n->DistanceTo(_enPos) < GlobalTol)
		{
			enNode = n;
			enFound = true;
		}

		if (stFound && enFound)
		{
			break;
		}
	}

	

	//Adds nodes to the list of system nodes if no corresponding node is found
	//Feels a little bit dangerous, with the new pointers... might be worth considering smart pointers here...
	if(!stFound)
	{
		stNode = shared_ptr<INode>(new Node3d(_stPos));
		systemNodes.push_back(stNode);
	}
	if(!enFound)
	{
		enNode = shared_ptr<INode>(new Node3d(_enPos));
		systemNodes.push_back(enNode);
	}


	std::vector<std::shared_ptr<DOF> > stNodDof = stNode->GetDofs();
	std::vector<std::shared_ptr<DOF> > enNodDof = enNode->GetDofs();


	std::vector<std::shared_ptr<DOF> > dof;


	//Get dofs for start node. Creates a spring element if the release demands it
	for (int i = 0; i < 6; i++)
	{
		if (_stRel.GetReleases()[i].IsFixed())
		{
			dof.push_back(stNodDof[i]);
		}
		else
		{
			std::shared_ptr<DOF> ptr(new DOF(0));
			dof.push_back(ptr);

			if (_stRel.GetReleases()[i].Stiffness() > 0)
			{
				std::vector<std::shared_ptr<DOF> > sprDof;
				sprDof.push_back(ptr);
				sprDof.push_back(stNodDof[i]);
				std::shared_ptr<CIFem::IElement> spring(new Spring(_stRel.GetReleases()[i].Stiffness(), sprDof));
				newElements.push_back(spring);
			}
		}
	}

	//Get dofs for end node. Creates a spring element if the release demands it
	for (int i = 0; i < 6; i++)
	{
		if (_enRel.GetReleases()[i].IsFixed())
		{
			dof.push_back(enNodDof[i]);
		}
		else
		{
			std::shared_ptr<DOF> ptr(new DOF(0));
			dof.push_back(ptr);

			if (_enRel.GetReleases()[i].Stiffness() > 0)
			{
				std::vector<std::shared_ptr<DOF> > sprDof;
				sprDof.push_back(ptr);
				sprDof.push_back(enNodDof[i]);
				std::shared_ptr<CIFem::IElement> spring(new Spring(_enRel.GetReleases()[i].Stiffness(), sprDof));
				newElements.push_back(spring);
			}
		}
	}

	//SectionProperties secProp = _xSec->CalcSectionProperties();
	//ElementProperty ep =ElementProperty(_mat.E(), _mat.G(), secProp._area, secProp._Iy, secProp._Iz, secProp._Kv);
	std::shared_ptr<CIFem::IElement> beam(new Element3d(_stPos, _enPos, dof, _xSec, _mat, Vector3d(_normal[0],_normal[1],_normal[2]), _optimizationProperties));

	newElements.push_back(beam);

	return newElements;
}

std::string CIFem::Element3dRcp::GetXSecString()
{
	return _xSec->ToString();
}

const XYZ & CIFem::Element3dRcp::GetStartPos()
{
	return _stPos;
}

const XYZ & CIFem::Element3dRcp::GetEndPos()
{
	return _enPos;
}

const Vector3d CIFem::Element3dRcp::GetNormal()
{
	try
	{
		return Vector3d(_normal[0], _normal[1], _normal[2]);
	}
	catch (const std::out_of_range& oor)
	{
		throw exception("Normal vector not set / set incorrectly");
	}
}

Element3dRcp::~Element3dRcp()
{
	_xSec.reset();
}

void CIFem::Element3dRcp::SetNormal(std::vector<double> normal)
{
	if (normal.size() != 3)
		std::invalid_argument("Input error, element normal should contain 3 elements [X Y Z]");
	else
	{
		_normal.clear();
		for (int i = 0; i < 3; i++)
		{
			_normal.push_back(normal[i]);
		}
	}
}
