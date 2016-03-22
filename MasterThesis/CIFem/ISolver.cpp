#include "ISolver.h"


void CIFem::ISolver::SetUpDofs(DofSet & spDofs)
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

void CIFem::ISolver::StoreResultsInDofs(const arma::colvec & a, const arma::colvec & f, DofSet & spDofs)
{

	for each (std::shared_ptr<DOF> spDof in spDofs)
	{
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

void CIFem::ISolver::ResetAllForces(DofSet & spDofs)
{
	for each (std::shared_ptr<CIFem::DOF> dof in spDofs)
	{
		dof->ClearLoad();
	}
	_structure->ResetStructrualForces();
}



