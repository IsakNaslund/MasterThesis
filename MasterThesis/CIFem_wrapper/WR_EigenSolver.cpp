#include "stdafx.h"
#include "WR_EigenSolver.h"


CIFem_wrapper::WR_EigenSolver::WR_EigenSolver()
{
}

CIFem_wrapper::WR_EigenSolver::WR_EigenSolver(WR_Structure ^ structure)
{
	_solver = new EigenSolver(structure->GetStructure());
}

CIFem_wrapper::WR_EigenSolver::~WR_EigenSolver()
{
	delete _solver;
	_solver = 0;
}

void CIFem_wrapper::WR_EigenSolver::Solve()
{
	_solver->Solve();
}

double CIFem_wrapper::WR_EigenSolver::SetResultsToMode(int mode)
{
	return _solver->SetResultsToMode(mode);
}
