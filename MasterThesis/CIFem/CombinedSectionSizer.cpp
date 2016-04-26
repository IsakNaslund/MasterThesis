#include "CombinedSectionSizer.h"



CIFem::CombinedSectionSizer::CombinedSectionSizer()
{
}

CIFem::CombinedSectionSizer::CombinedSectionSizer(std::shared_ptr<Structure> structure)
{
	_modeShapeOptimizer = ModeShapeOptimizer(structure);
	_secSizer = StandardSectionSizer(structure);
}


CIFem::CombinedSectionSizer::~CombinedSectionSizer()
{
}

void CIFem::CombinedSectionSizer::Run(std::set<int> modes, int maxIter)
{
	_modeShapeOptimizer.Run(modes);
	_secSizer.Run(maxIter);
}

void CIFem::CombinedSectionSizer::AddLoadCombination(LoadCombination comb)
{
	_secSizer.AddLoadCombination(comb);
}
