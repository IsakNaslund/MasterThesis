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

int StandardSectionSizer::Run(int maxIterations)
{
	int iterationCount = 0;
	bool run = true;
	//Run until all sections have utilization below 1
	while (run)
	{
		_linSolver.Solve();
		run = CheckElementRotation();

		_linSolver.Solve();
		run = (CheckUtilization() || run) & IncrementIteration(maxIterations, iterationCount);
	}
	return iterationCount;
}

void StandardSectionSizer::AddLoadCombination(LoadCombination comb)
{
	_linSolver.AddLoadCombination(comb);
}

bool StandardSectionSizer::CheckUtilization()
{

	bool updated = false;
	for (int i = 0; i < _structure->ElementCount(); i++)
	{
		if (_structure->GetElements()[i]->CalcAndGetMaxUtil().GetUtil()>1)
		{
			if(_structure->GetElements()[i]->UpdateElement())
				updated = true;
		}
	}

	return updated;
}

bool StandardSectionSizer::CheckElementRotation()
{
	bool updated = false;
	for (int i = 0; i < _structure->ElementCount(); i++)
	{
		if (_structure->GetElements()[i]->UpdateElementOrientation())
			updated = true;
	}

	return updated;

}
bool StandardSectionSizer::IncrementIteration(const int & maxIterations, int & iterationCount)
{

	iterationCount++;

	return iterationCount < maxIterations;

}