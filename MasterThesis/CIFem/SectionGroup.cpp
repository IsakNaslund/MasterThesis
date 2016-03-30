#include "SectionGroup.h"



CIFem::SectionGroup::SectionGroup()
{
}


CIFem::SectionGroup::~SectionGroup()
{
}

void CIFem::SectionGroup::Add(std::shared_ptr<CIFem::ICrossSection> crossSection)
{
	_crossSections.push_back(crossSection);
}
