#include "stdafx.h"
#include "WR_SectionGroup.h"


CIFem_wrapper::WR_SectionGroup::WR_SectionGroup()
{
	_sectionGroup = gcnew m_shared_ptr<CIFem::SectionGroup>(new CIFem::SectionGroup());
}

void CIFem_wrapper::WR_SectionGroup::AddCrossSection(CIFem_wrapper::WR_IXSec^ crossSection)
{
	_sectionGroup.operator std::shared_ptr<CIFem::SectionGroup>()->Add(crossSection->GetCrossSection());
}

std::shared_ptr<CIFem::SectionGroup> CIFem_wrapper::WR_SectionGroup::GetSectionGroup()
{
	return _sectionGroup.operator std::shared_ptr<CIFem::SectionGroup>();
}
