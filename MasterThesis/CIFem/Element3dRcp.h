#pragma once
#include "CIFem_dll.h"
#include "IElementRcp.h"
#include "ReleaseBeam3d.h"
#include "ICrossSection.h"
#include "GlobalSettings.h"
#include <memory>
#include "Spring.h"
#include "Element3d.h"

using namespace CIFem;

namespace CIFem
{
	class CIFEM_API Element3dRcp :
		public IElementRcp
	{
		XYZ _stPos, _enPos;
		ReleaseBeam3d _stRel, _enRel;
		ICrossSection * _xSec;
		double _matStiff;
		double _poisonsRatio;
		std::vector<double> _normal;

	public:
		Element3dRcp();
		Element3dRcp(Element3dRcp* other);
		Element3dRcp(XYZ stPos, XYZ enPos, ReleaseBeam3d stRel, ReleaseBeam3d enRel, ICrossSection* xSec, double matStiff, double poisonRatio, std::vector<double> normal);

		std::vector<IElement*> CreateElement(std::vector<INode*> systemNodes);
		~Element3dRcp();

	private:
		void SetNormal(std::vector<double>);
	};
}

