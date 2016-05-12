#pragma once
#include "CIFem_dll.h"
#include "ModeShapeOptimizer.h"
#include "StandardSectionSizer.h"
#include "Structure.h"

namespace CIFem
{
	class CIFEM_API CombinedSectionSizer
	{
		ModeShapeOptimizer _modeShapeOptimizer;
		StandardSectionSizer _secSizer;
		std::shared_ptr<Structure> _structure;

		void ClearResults(int mode);

	public:
		CombinedSectionSizer();
		CombinedSectionSizer(std::shared_ptr<Structure> structure);
		~CombinedSectionSizer();


		int Run(std::set<int> modes, int maxIter);
		//Add load combination
		void AddLoadCombination(LoadCombination comb);
	};
}

