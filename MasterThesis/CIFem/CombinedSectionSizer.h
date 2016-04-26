#pragma once
#include "CIFem_dll.h"
#include "ModeShapeOptimizer.h"
#include "StandardSectionSizer.h"

namespace CIFem
{
	class CIFEM_API CombinedSectionSizer
	{
		ModeShapeOptimizer _modeShapeOptimizer;
		StandardSectionSizer _secSizer;
	public:
		CombinedSectionSizer();
		CombinedSectionSizer(std::shared_ptr<Structure> structure);
		~CombinedSectionSizer();


		void Run(std::set<int> modes, int maxIter);
		//Add load combination
		void AddLoadCombination(LoadCombination comb);
	};
}

