#pragma once
#include "CIFem_dll.h"
#include <vector>
#include "ICrossSection.h"
#include <memory>

namespace CIFem
{
	class CIFEM_API SectionGroup
	{
		std::vector<std::shared_ptr<CIFem::ICrossSection>> _crossSections;
	public:
		SectionGroup();
		~SectionGroup();

		void Add(std::shared_ptr<CIFem::ICrossSection> crossSection);


	};

}