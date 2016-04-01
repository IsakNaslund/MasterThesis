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

void StandardSectionSizer::Run(int maxIterations)
{
	int iterationCount = 0;

	//Run until all sections have utilization below 1
	while (CheckUtilization(maxIterations, iterationCount))
	{
		_linSolver.Solve();
		iterationCount++;
	}

}

void StandardSectionSizer::AddLoadCombination(LoadCombination comb)
{
	_linSolver.AddLoadCombination(comb);
}

bool StandardSectionSizer::CheckUtilization(int maxIterations, int iterationCount)
{

	if (iterationCount < 1)
		return true;

	if (iterationCount > maxIterations)
		return false;

	bool updated = false;
	for (int i = 0; i < _structure->ElementCount(); i++)
	{
		if (_structure->GetElements()[i]->CalcAndGetMaxUtil().GetUtil()>1)
		{
			_structure->GetElements()[i]->UpdateElement();
			updated = true;
		}
	}

	return updated;
}
