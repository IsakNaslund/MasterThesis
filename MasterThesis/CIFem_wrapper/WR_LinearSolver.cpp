#include "stdafx.h"
#include "WR_LinearSolver.h"


CIFem_wrapper::WR_LinearSolver::WR_LinearSolver()
{
}

CIFem_wrapper::WR_LinearSolver::WR_LinearSolver(WR_Structure^ structure)
{
	_solver = new LinearSolver(structure->GetStructure());
}

CIFem_wrapper::WR_LinearSolver::WR_LinearSolver(WR_Structure ^ structure, bool applyGravity)
{
	_solver = new LinearSolver(structure->GetStructure(), applyGravity);
}

CIFem_wrapper::WR_LinearSolver::~WR_LinearSolver()
{
	delete _solver;
	_solver = 0;
}

void CIFem_wrapper::WR_LinearSolver::Solve()
{
	_solver->Solve();
}
