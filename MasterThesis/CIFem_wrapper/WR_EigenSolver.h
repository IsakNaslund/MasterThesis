#pragma once

#include "EigenSolver.h"
#include "WR_Structure.h"


namespace CIFem_wrapper
{
	public ref class WR_EigenSolver
	{
		CIFem::EigenSolver * _solver;
	public:
		WR_EigenSolver();
		WR_EigenSolver(WR_Structure^ structure);
		~WR_EigenSolver();

		void Solve();
		double SetResultsToMode(int mode);
	};
}

