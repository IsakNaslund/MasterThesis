#include "ISolver.h"


void CIFem::ISolver::SetUpDofs(DofSet spDofs)
{
	//Counting dofs, assuming all dofs exists in the nodes
	//Clear loads from dofs
	int dofCounter = 0;
	for each (std::shared_ptr<CIFem::DOF> dof in spDofs)
	{
		dof->UpdateKIndex(dofCounter);
		dof->ClearLoad();
		dofCounter++;
	}

}

void CIFem::ISolver::StoreResultsInDofs(arma::colvec a, arma::colvec f, DofSet spDofs)
{

	for each (std::shared_ptr<DOF> spDof in spDofs)
	{
		arma::mat amat(24, 1);
		amat = amat + a;
		spDof->SetResults(a(spDof->GetKIndex()), f(spDof->GetKIndex()));
	}

}

void CIFem::ISolver::CalculateElementSectionForces()
{
	_structure->CalculateElementSectionForces();
}

DofSet CIFem::ISolver::GetDofs()
{
	return _structure->GetDofs();
}

