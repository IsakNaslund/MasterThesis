#pragma once
#include "CIFem_dll.h"
#include "IElementRcp.h"
#include "ReleaseBeam3d.h"
#include "ICrossSection.h"
#include "GlobalSettings.h"
#include <memory>
#include "Spring.h"
#include "Element3d.h"
#include "Material.h"

using namespace CIFem;

namespace CIFem
{
	class CIFEM_API Element3dRcp :
		public IElementRcp
	{
		XYZ _stPos, _enPos;
		ReleaseBeam3d _stRel, _enRel;
		std::shared_ptr<ICrossSection> _xSec;
		std::vector<double> _normal;
		std::shared_ptr<Material> _mat;
		std::shared_ptr<Element3dOptProp> _optimizationProperties;

	public:
		Element3dRcp();
		Element3dRcp(std::shared_ptr<Element3dRcp> other);
		Element3dRcp(XYZ stPos, XYZ enPos, ReleaseBeam3d stRel, ReleaseBeam3d enRel, std::shared_ptr<ICrossSection> xSec, double matStiff, double poisonRatio, std::vector<double> normal);
		Element3dRcp(XYZ stPos, XYZ enPos, ReleaseBeam3d stRel, ReleaseBeam3d enRel, std::shared_ptr<ICrossSection> xSec, double matStiff, double poisonRatio, double density, double fu, std::vector<double> normal);
		Element3dRcp(XYZ stPos, XYZ enPos, ReleaseBeam3d stRel, ReleaseBeam3d enRel, std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> material, std::vector<double> normal);
		Element3dRcp(XYZ stPos, XYZ enPos, ReleaseBeam3d stRel, ReleaseBeam3d enRel, std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> material, std::vector<double> normal, std::shared_ptr<Element3dOptProp> sectionGroup);


		std::vector<std::shared_ptr<CIFem::IElement>> CreateElement(std::vector<std::shared_ptr<INode>> & systemNodes);
		std::string GetXSecString();
		const XYZ & GetStartPos() override;
		const XYZ & GetEndPos() override;
		const Vector3d GetNormal();
		~Element3dRcp();

	private:
		void SetNormal(std::vector<double>);
	};
}

