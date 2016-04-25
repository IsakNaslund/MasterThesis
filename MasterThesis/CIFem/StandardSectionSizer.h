#pragma once

#include "CIFem_dll.h"
#include "Structure3d.h"
#include "LinearSolver.h"
#include <memory>

namespace CIFem
{

	class CIFEM_API StandardSectionSizer
	{
		LinearSolver _linSolver;
		std::shared_ptr<Structure> _structure;
		bool _updateOrientation;
		bool _updateSection;
	public:
		StandardSectionSizer();
		StandardSectionSizer(std::shared_ptr<Structure> structure);
		StandardSectionSizer(std::shared_ptr<Structure> structure, bool updateSection, bool updateOrientation);
		~StandardSectionSizer();


		//Main function for running section sizier
		int Run(int maxIterations);

		//Add load combination
		void AddLoadCombination(LoadCombination comb);

	private:

		bool CheckUtilization();
		bool CheckElementRotation();
		bool IncrementIteration(const int & maxIterations, int & iterationCount);
	};
}

