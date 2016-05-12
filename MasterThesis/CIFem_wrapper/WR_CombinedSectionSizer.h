#pragma once
#include "CombinedSectionSizer.h"
#include "WR_Structure.h"
#include "Utilities.h"
#include "WR_LoadCombination.h"

namespace CIFem_wrapper
{
	public ref class WR_CombinedSectionSizer
	{
		CIFem::CombinedSectionSizer* _sectionSizer;
	public:
		WR_CombinedSectionSizer();
		WR_CombinedSectionSizer(WR_Structure ^structure);
		~WR_CombinedSectionSizer();

		int Run(System::Collections::Generic::List<int>^ modes, int maxIter);
		void AddLoadCombination(WR_LoadCombination^ comb);
	};
}

