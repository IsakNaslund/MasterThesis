#pragma once

#include "CIFem_dll.h"
#include "Structure3d.h"
#include "LinearSolver.h"
#include <memory>


class CIFEM_API StandardSectionSizer
{
	LinearSolver _linSolver;
	std::shared_ptr<Structure> _structure;
public:
	StandardSectionSizer();
	StandardSectionSizer(std::shared_ptr<Structure> structure);
	~StandardSectionSizer();


	//Main function for running section sizier
	void Run();

	//Add load combination
	void AddLoadCombination(LoadCombination comb);

private:

	bool CheckUtilization();
};

