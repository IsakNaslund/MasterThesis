#pragma once
#include "WR_IElemRcp.h"
#include "Element3dRcp.h"
#include "WR_XYZ.h"
#include "WR_IXSec.h"
#include "WR_ReleaseBeam3d.h"
#include "WR_Vector.h"
#include "m_shared_ptr.h"
#include "WR_Material.h"

namespace CIFem_wrapper
{

	public ref class WR_Elem3dRcp : public WR_IElemRcp
	{
	private:
		
		m_shared_ptr<CIFem::Element3dRcp> _eleRcp;
		//CIFem::Element3dRcp* _eleRcp;
		WR_Elem3dRcp(Element3dRcp eleRcp);
		WR_Elem3dRcp(std::shared_ptr<Element3dRcp> eleRcp);

	public:
		WR_Elem3dRcp();
		~WR_Elem3dRcp();
		WR_Elem3dRcp(XYZ stPos, XYZ enPos, ReleaseBeam3d stRel, ReleaseBeam3d enRel, std::shared_ptr<ICrossSection> xSec, double matStiff, double poisonRatio, std::vector<double> normal);
		WR_Elem3dRcp(WR_XYZ^ stPos, WR_XYZ^ enPos, WR_ReleaseBeam3d^ stRel, WR_ReleaseBeam3d^ enRel, WR_IXSec^ xSec, double matStiff, double poisonRatio, WR_Vector^ normal);
		WR_Elem3dRcp(WR_XYZ^ stPos, WR_XYZ^ enPos, WR_ReleaseBeam3d^ stRel, WR_ReleaseBeam3d^ enRel, WR_IXSec^ xSec, WR_Material^ mat , WR_Vector^ normal);
		WR_Elem3dRcp^ Copy();
		virtual std::shared_ptr<CIFem::IElementRcp> GetRecipe() override;
	};

}