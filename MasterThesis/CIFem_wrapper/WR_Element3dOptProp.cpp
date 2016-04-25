#include "stdafx.h"
#include "WR_Element3dOptProp.h"


CIFem_wrapper::WR_Element3dOptProp::WR_Element3dOptProp()
{
	_optimizationProperties = gcnew m_shared_ptr<CIFem::Element3dOptProp>(new CIFem::Element3dOptProp());
}

CIFem_wrapper::WR_Element3dOptProp::WR_Element3dOptProp(bool allowRotation)
{
	_optimizationProperties = gcnew m_shared_ptr<CIFem::Element3dOptProp>(new CIFem::Element3dOptProp(allowRotation));
}

CIFem_wrapper::WR_Element3dOptProp::WR_Element3dOptProp(bool allowRotation, int changeType)
{
	_optimizationProperties = gcnew m_shared_ptr<CIFem::Element3dOptProp>(new CIFem::Element3dOptProp(allowRotation, changeType));
}

void CIFem_wrapper::WR_Element3dOptProp::AddCrossSection(CIFem_wrapper::WR_IXSec^ crossSection)
{
	_optimizationProperties.operator std::shared_ptr<CIFem::Element3dOptProp>()->Add(crossSection->GetCrossSection());
}

std::shared_ptr<CIFem::Element3dOptProp> CIFem_wrapper::WR_Element3dOptProp::GetOptimizationProperties()
{
	return _optimizationProperties.operator std::shared_ptr<CIFem::Element3dOptProp>();
}
