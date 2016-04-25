#pragma once
#include "LinearSolver.h"
#include "m_shared_ptr.h"
#include "WR_Structure.h"
#include "WR_LoadCombination.h"

namespace CIFem_wrapper
{
	CIFem::LinearSolver* _solver;

	public ref class WR_LinearSolver
	{
	public:
		WR_LinearSolver();
		WR_LinearSolver(WR_Structure^ structure);
		WR_LinearSolver(WR_Structure^ structure, bool applyGravity);
		~WR_LinearSolver();

		void Solve();

		void AddLoadCombination(WR_LoadCombination^ comb);
		void CheckStructure();
	};
}
