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
	class CIFEM_API Element3dOptProp
	{

		enum SectionChangeType
		{
			CheckAll=0,
			CheckClose=1,
			StepUpOne=2
		};

		struct cmp
		{
			bool operator()(std::shared_ptr<CIFem::ICrossSection> a, std::shared_ptr<CIFem::ICrossSection> b)
			{
				return a->GetArea() < b->GetArea();
			}
		};


		template <typename Iter>
		Iter next(Iter iter)
		{
			return ++iter;
		}

		template <typename Iter, typename Cont>
		bool is_last(Iter iter, const Cont& cont)
		{
			return (iter != cont.end()) && (next(iter) == cont.end());
		}


		std::set<std::shared_ptr<CIFem::ICrossSection>,cmp> _crossSections;
		//std::set<std::shared_ptr<CIFem::ICrossSection>> _crossSections;
		Element3dChecks _checks;
		bool _allowRotation;
		SectionChangeType _sectionChangeType;
	public:
		Element3dOptProp();
		Element3dOptProp(Element3dChecks checks);
		Element3dOptProp(bool allowRotation);
		Element3dOptProp(Element3dChecks checks, bool allowRotation);
		Element3dOptProp(bool allowRotation, int changeType);
		Element3dOptProp(Element3dChecks checks, bool allowRotation, int changeType);
		~Element3dOptProp();

		void Add(std::shared_ptr<CIFem::ICrossSection> crossSection);

		int SectionCount() { return _crossSections.size(); }
		const bool & AllowRotation() const { return _allowRotation; }


		bool UpdateCrossSection(std::shared_ptr<Material> mat, ElementResults3d & results, std::shared_ptr<CIFem::ICrossSection> & updatedCrossSection);


		bool UpdateCrossSectionCheckAll(std::shared_ptr<Material> mat, ElementResults3d & results, std::shared_ptr<CIFem::ICrossSection> & updatedCrossSection);
		bool UpdateCrossSection(std::shared_ptr<Material> mat, ElementResults3d & results, std::shared_ptr<CIFem::ICrossSection> & updatedCrossSection, std::string loadCase);


		bool CIFem::Element3dOptProp::UpdateCrossSectionClosePosition(std::shared_ptr<Material> mat, ElementResults3d & results, std::shared_ptr<CIFem::ICrossSection>& updatedCrossSection);
		bool CIFem::Element3dOptProp::UpdateCrossSectionStepOne(std::shared_ptr<CIFem::ICrossSection>& updatedCrossSection);


		bool UpdateCrossSection(double N, double Vy, double Vz, double My, double Mz, double T, double fu, std::shared_ptr<CIFem::ICrossSection> & updatedCrossSection);


	};

}