#pragma once
#include "SectionGroup.h"
#include "m_shared_ptr.h"
#include "ICrossSection.h"
#include "WR_IXSec.h"
namespace CIFem_wrapper
{
	public ref class WR_SectionGroup
	{
		m_shared_ptr<CIFem::SectionGroup> _sectionGroup;
	public:
		WR_SectionGroup();
		void AddCrossSection(WR_IXSec^ crossSection);
		std::shared_ptr<CIFem::SectionGroup> GetSectionGroup();
	};
}

