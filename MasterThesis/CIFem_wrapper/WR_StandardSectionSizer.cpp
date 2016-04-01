#include "stdafx.h"
#include "WR_StandardSectionSizer.h"


CIFem_wrapper::WR_StandardSectionSizer::WR_StandardSectionSizer()
{
	_secSizer = new CIFem::StandardSectionSizer();
}

CIFem_wrapper::WR_StandardSectionSizer::WR_StandardSectionSizer(WR_Structure^ structure)
{
	_secSizer = new CIFem::StandardSectionSizer(structure->GetStructure());
}

CIFem_wrapper::WR_StandardSectionSizer::~WR_StandardSectionSizer()
{
	delete _secSizer;
	_secSizer = 0;
}

void CIFem_wrapper::WR_StandardSectionSizer::AddLoadCombination(WR_LoadCombination ^ comb)
{
	_secSizer->AddLoadCombination(comb->GetCombination());
}

void CIFem_wrapper::WR_StandardSectionSizer::Run(int maxIterations)
{
	_secSizer->Run(maxIterations);
}
