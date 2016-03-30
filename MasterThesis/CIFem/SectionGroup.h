#pragma once
#include "CIFem_dll.h"
#include <set>
#include "ICrossSection.h"
#include <memory>

namespace CIFem
{
	class CIFEM_API SectionGroup
	{

		struct cmp
		{
			bool operator()(std::shared_ptr<CIFem::ICrossSection> a, std::shared_ptr<CIFem::ICrossSection> b)
			{
				return a->GetArea() > b->GetArea();
			}
		};

		std::set<std::shared_ptr<CIFem::ICrossSection>,cmp> _crossSections;
	public:
		SectionGroup();
		~SectionGroup();

		void Add(std::shared_ptr<CIFem::ICrossSection> crossSection);

		bool UpdateCrossSection(double N, double Vy, double Vz, double My, double Mz, double T, double fu, std::shared_ptr<CIFem::ICrossSection> & updatedCrossSection);


	};

}