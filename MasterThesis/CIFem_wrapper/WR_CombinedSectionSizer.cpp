#include "stdafx.h"
#include "WR_CombinedSectionSizer.h"


CIFem_wrapper::WR_CombinedSectionSizer::WR_CombinedSectionSizer()
{
}

CIFem_wrapper::WR_CombinedSectionSizer::WR_CombinedSectionSizer(WR_Structure ^ structure)
{
	_sectionSizer = new CIFem::CombinedSectionSizer(structure->GetStructure());
}

CIFem_wrapper::WR_CombinedSectionSizer::~WR_CombinedSectionSizer()
{
	delete _sectionSizer;
	_sectionSizer = 0;
}

int CIFem_wrapper::WR_CombinedSectionSizer::Run(System::Collections::Generic::List<int>^ modes, int maxIter)
{
	return _sectionSizer->Run(Utilities::GetSetFromList(modes), maxIter);
}

void CIFem_wrapper::WR_CombinedSectionSizer::AddLoadCombination(WR_LoadCombination ^ comb)
{

	_sectionSizer->AddLoadCombination(comb->GetCombination());

}
