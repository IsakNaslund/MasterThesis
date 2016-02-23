#pragma once
#include "IElementRcp.h"
#include "ReleaseBeam3d.h"
#include "ICrossSection.h"

using namespace CIFem;

namespace CIFem
{
	class Element3dRcp :
		public IElementRcp
	{
		XYZ _stPos, _enPos;
		ReleaseBeam3d _stRel, _enRel;
		ICrossSection * _xSec;
		double _matStiff;
		std::vector<double> _normal;

	public:
		Element3dRcp();
		Element3dRcp(XYZ stPos, XYZ enPos, ReleaseBeam3d stRel, ReleaseBeam3d enRel, ICrossSection* xSec, double matStiff, std::vector<double> normal);

		std::vector<IElement*> CreateElement(std::vector<INode> systemNodes);
		~Element3dRcp();
	};
}

