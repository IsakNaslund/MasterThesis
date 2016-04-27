#include "CombinedSectionSizer.h"




CIFem::CombinedSectionSizer::CombinedSectionSizer()
{
}

CIFem::CombinedSectionSizer::CombinedSectionSizer(std::shared_ptr<Structure> structure)
{
	_modeShapeOptimizer = ModeShapeOptimizer(structure);
	_secSizer = StandardSectionSizer(structure);
	_structure = structure;
}


CIFem::CombinedSectionSizer::~CombinedSectionSizer()
{
}

void CIFem::CombinedSectionSizer::ClearResults(int mode)
{
	std::string modeName = "Mode " + std::to_string(mode);
	_structure->ClearLoadCombination(modeName);
}


void CIFem::CombinedSectionSizer::Run(std::set<int> modes, int maxIter)
{
	_modeShapeOptimizer.Run(modes);

	for each (int mode in modes)
	{
		ClearResults(mode);
	}


	_secSizer.Run(maxIter);
}

void CIFem::CombinedSectionSizer::AddLoadCombination(LoadCombination comb)
{
	_secSizer.AddLoadCombination(comb);
}
