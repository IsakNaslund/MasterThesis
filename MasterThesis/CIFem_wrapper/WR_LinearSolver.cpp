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
	try
	{
		try
		{
			_solver->Solve();
		}
		catch (const std::exception& e)
		{
			throw gcnew System::Exception(gcnew System::String(e.what()));
		}
	}
	catch (System::Exception^ e)
	{
		throw e;
	}
}

void CIFem_wrapper::WR_LinearSolver::AddLoadCombination(WR_LoadCombination ^ comb)
{
	_solver->AddLoadCombination(comb->GetCombination());
}

void CIFem_wrapper::WR_LinearSolver::CheckStructure()
{
	_solver->CheckStructure();
}
