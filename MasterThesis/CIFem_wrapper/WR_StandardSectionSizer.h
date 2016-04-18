#pragma once

#include "StandardSectionSizer.h"
#include "m_shared_ptr.h"
#include "WR_Structure.h"
#include "WR_LoadCombination.h"

namespace CIFem_wrapper
{
	public ref class WR_StandardSectionSizer
	{
		CIFem::StandardSectionSizer* _secSizer;
	public:
		WR_StandardSectionSizer();
		WR_StandardSectionSizer(WR_Structure^ structure);
		~WR_StandardSectionSizer();

		void AddLoadCombination(WR_LoadCombination^ comb);
		int Run(int maxIterations);
	};
}

