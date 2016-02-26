#pragma once
#include "WR_IElemRcp.h"
#include "Element3dRcp.h"
#include "WR_XYZ.h"
#include "WR_IXSec.h"
#include "WR_ReleaseBeam3d.h"
#include "WR_Vector.h"

namespace CIFem_wrapper
{

	public ref class WR_Elem3dRcp : public WR_IElemRcp
	{
	public:
		WR_Elem3dRcp();
		~WR_Elem3dRcp();
		WR_Elem3dRcp(XYZ stPos, XYZ enPos, ReleaseBeam3d stRel, ReleaseBeam3d enRel, ICrossSection* xSec, double matStiff, double poisonRatio, std::vector<double> normal);
		WR_Elem3dRcp(WR_XYZ^ stPos, WR_XYZ^ enPos, WR_ReleaseBeam3d^ stRel, WR_ReleaseBeam3d^ enRel, WR_IXSec^ xSec, double matStiff, double poisonRatio, WR_Vector^ normal);
	};

}