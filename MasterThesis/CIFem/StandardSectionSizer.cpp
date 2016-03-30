#include "StandardSectionSizer.h"



StandardSectionSizer::StandardSectionSizer()
{
}

StandardSectionSizer::StandardSectionSizer(std::shared_ptr<Structure> structure)
{
	_structure = structure;
	_linSolver = LinearSolver(_structure);
}


StandardSectionSizer::~StandardSectionSizer()
{
}

void StandardSectionSizer::Run()
{
	//Run until all sections have utilization below 1
	while (CheckUtilization())
	{
		_linSolver.Solve();
	}

}

void StandardSectionSizer::AddLoadCombination(LoadCombination comb)
{
	_linSolver.AddLoadCombination(comb);
}

bool StandardSectionSizer::CheckUtilization()
{
	return false;
}
