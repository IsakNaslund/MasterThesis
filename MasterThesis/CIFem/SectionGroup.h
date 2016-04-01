#pragma once
#include "CIFem_dll.h"
#include <set>
#include "ICrossSection.h"
#include <memory>
#include "Element3dChecks.h"

namespace CIFem
{
	class ElementResults3d;
	class Material;
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
		//std::set<std::shared_ptr<CIFem::ICrossSection>> _crossSections;
		Element3dChecks _checks;
	public:
		SectionGroup();
		SectionGroup(Element3dChecks checks);
		~SectionGroup();

		void Add(std::shared_ptr<CIFem::ICrossSection> crossSection);

		bool UpdateCrossSection(std::shared_ptr<Material> mat, ElementResults3d & results, std::shared_ptr<CIFem::ICrossSection> & updatedCrossSection);

		bool UpdateCrossSection(double N, double Vy, double Vz, double My, double Mz, double T, double fu, std::shared_ptr<CIFem::ICrossSection> & updatedCrossSection);


	};

}