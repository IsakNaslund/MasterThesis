#include "StandardSectionSizer.h"



StandardSectionSizer::StandardSectionSizer()
{
	_updateOrientation = true;
	_updateSection = true;
}

StandardSectionSizer::StandardSectionSizer(std::shared_ptr<Structure> structure)
{
	_updateOrientation = true;
	_updateSection = true;
	_structure = structure;
	_linSolver = LinearSolver(_structure);
}

CIFem::StandardSectionSizer::StandardSectionSizer(std::shared_ptr<Structure> structure, bool updateSection, bool updateOrientation)
{
	_updateOrientation = updateOrientation;
	_updateSection = updateSection;
	_structure = structure;
	_linSolver = LinearSolver(_structure);
}


StandardSectionSizer::~StandardSectionSizer()
{
}

int StandardSectionSizer::Run(int maxIterations)
{
	if (!_updateOrientation && !_updateSection)
		return 0;


	int iterationCount = 0;
	bool run = true;
	//Run until all sections have utilization below 1
	while (run)
	{
		if (_updateOrientation)
		{
			_linSolver.Solve();
			run = CheckElementRotation();
		}

		if (_updateSection)
		{
			_linSolver.Solve();
			run = CheckUtilization() || run;
		}

		run = run & IncrementIteration(maxIterations, iterationCount);
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