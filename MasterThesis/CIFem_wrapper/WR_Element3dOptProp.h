#pragma once
#include "Element3dOptProp.h"
#include "m_shared_ptr.h"
#include "ICrossSection.h"
#include "WR_IXSec.h"
namespace CIFem_wrapper
{
	public ref class WR_Element3dOptProp
	{
		m_shared_ptr<CIFem::Element3dOptProp> _optimizationProperties;
	public:
		WR_Element3dOptProp();
		WR_Element3dOptProp(bool allowRotation);
		WR_Element3dOptProp(bool allowRotation, int changeType);
		WR_Element3dOptProp(bool allowRotation, int changeType, double minUtil, double maxUtil);
		void AddCrossSection(WR_IXSec^ crossSection);
		std::shared_ptr<CIFem::Element3dOptProp> GetOptimizationProperties();
	};
}

