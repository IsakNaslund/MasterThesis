#pragma once
#include "WR_IElemRcp.h"
#include "Element3dRcp.h"
#include "WR_XYZ.h"
#include "WR_IXSec.h"

ref class WR_Elem3dRcp : public WR_IElemRcp
{
public:
	WR_Elem3dRcp();
	~WR_Elem3dRcp();
	WR_Elem3dRcp(XYZ stPos, XYZ enPos, ReleaseBeam3d stRel, ReleaseBeam3d enRel, ICrossSection* xSec, double matStiff, double poisonRatio, std::vector<double> normal);
	WR_Elem3dRcp(XYZ stPos, XYZ enPos, ReleaseBeam3d stRel, ReleaseBeam3d enRel, ICrossSection* xSec, double matStiff, double poisonRatio, std::vector<double> normal);
};

