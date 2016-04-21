#pragma once
#include "WR_Structure.h"
#include "ModeShapeOptimizer.h"
#include "Utilities.h"

namespace CIFem_wrapper
{

	public ref class WR_ModeShapeOptimizer
	{
		CIFem::ModeShapeOptimizer * _optimizer;
	public:
		WR_ModeShapeOptimizer();
		WR_ModeShapeOptimizer(WR_Structure ^structure);
		~WR_ModeShapeOptimizer();

		void Run();
		void Run(double maxRatio);
		void Run(System::Collections::Generic::List<int>^ modes);

	};
}

