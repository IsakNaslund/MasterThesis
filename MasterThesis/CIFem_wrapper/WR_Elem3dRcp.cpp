#include "stdafx.h"
#include "WR_Elem3dRcp.h"

using namespace CIFem_wrapper;

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

CIFem_wrapper::WR_Elem3dRcp::WR_Elem3dRcp(WR_XYZ^ stPos, WR_XYZ^ enPos, WR_ReleaseBeam3d^ stRel, WR_ReleaseBeam3d^ enRel, WR_IXSec^ xSec, double matStiff, double poisonRatio, WR_Vector^ normal)
{
	_eleRcp = new Element3dRcp(stPos->GetPos(), enPos->GetPos(), stRel->GetRelease(), enRel->GetRelease(), xSec->GetCrossSection(), matStiff, poisonRatio, normal->GetAsCppVector());
}
