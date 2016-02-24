#include "Element3dRcp.h"




CIFem::Element3dRcp::Element3dRcp()
{
}

CIFem::Element3dRcp::Element3dRcp(XYZ stPos, XYZ enPos, ReleaseBeam3d stRel, ReleaseBeam3d enRel, ICrossSection * xSec, double matStiff, double poisonRatio, std::vector<double> normal)
{
	_stPos = stPos;
	_enPos = enPos;
	_stRel = stRel;
	_enRel = enRel;
	_xSec = xSec;
	_matStiff = matStiff;
	_poisonsRatio = poisonRatio;
	SetNormal(normal);	// Set normal with format check
}

std::vector<IElement*> CIFem::Element3dRcp::CreateElement(std::vector<INode*> systemNodes)
{
	INode* stNode, *enNode;
	std::vector<IElement*> newElements;

	bool stFound = false;
	bool enFound = false;

	for each (INode* n in systemNodes)
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
				IElement* spring = new Spring(_stRel.GetReleases()[i].Stiffness(), sprDof);
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

			if (_stRel.GetReleases()[i].Stiffness() > 0)
			{
				std::vector<std::shared_ptr<DOF> > sprDof;
				sprDof.push_back(ptr);
				sprDof.push_back(enNodDof[i]);
				IElement* spring = new Spring(_stRel.GetReleases()[i].Stiffness(), sprDof);
				newElements.push_back(spring);
			}
		}
	}

	SectionProperties secProp = _xSec->CalcSectionProperties();
	double G = _matStiff / (2 * (_poisonsRatio + 1));
	ElementProperty ep =ElementProperty(_matStiff, G, secProp._area, secProp._Iy, secProp._Iz, secProp._Kv);
	IElement* beam = new Element3d(_stPos, _enPos, dof, ep);

	newElements.push_back(beam);

	return newElements;
}

Element3dRcp::~Element3dRcp()
{
}

void CIFem::Element3dRcp::SetNormal(std::vector<double> normal)
{
	if (normal.size() != 3)
		std::invalid_argument("Input error, element normal should contain 3 elements [X Y Z]");
}
