#include "Element3dRcp.h"




CIFem::Element3dRcp::Element3dRcp()
{
}

CIFem::Element3dRcp::Element3dRcp(XYZ stPos, XYZ enPos, ReleaseBeam3d stRel, ReleaseBeam3d enRel, ICrossSection * xSec, double matStiff, std::vector<double> normal)
{
	_stPos = stPos;
	_enPos = enPos;
	_stRel = stRel;
	_enRel = enRel;
	_xSec = xSec;
	_matStiff = matStiff;
	_normal = normal;

}

std::vector<IElement*> CIFem::Element3dRcp::CreateElement(std::vector<INode*> systemNodes)
{
	INode* stNode, *enNode;

	



	return std::vector<IElement*>();
}

Element3dRcp::~Element3dRcp()
{
}
