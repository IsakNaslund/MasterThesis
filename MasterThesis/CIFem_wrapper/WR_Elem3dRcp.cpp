#include "stdafx.h"
#include "WR_Elem3dRcp.h"


WR_Elem3dRcp::WR_Elem3dRcp()
{
	_eleRcp = new Element3dRcp();
}

WR_Elem3dRcp::~WR_Elem3dRcp()
{

}

WR_Elem3dRcp::WR_Elem3dRcp(XYZ stPos, XYZ enPos, ReleaseBeam3d stRel, ReleaseBeam3d enRel, ICrossSection * xSec, double matStiff, double poisonRatio, std::vector<double> normal)
{
	_eleRcp = new Element3dRcp( stPos,  enPos,  stRel,  enRel,  xSec,  matStiff,  poisonRatio,  normal);
}
