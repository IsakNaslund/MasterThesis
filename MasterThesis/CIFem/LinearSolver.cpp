#include "LinearSolver.h"



CIFem::LinearSolver::LinearSolver()
{
}

CIFem::LinearSolver::LinearSolver(std::shared_ptr<CIFem::Structure> structure)
{
	_structure = structure;
	_gravityOn = false;
}

CIFem::LinearSolver::LinearSolver(std::shared_ptr<CIFem::Structure> structure, bool applyGravity)
{
	_structure = structure;
	_gravityOn = applyGravity;
	_gravityField = Vector3d(0, 0, -9.82);
}

CIFem::LinearSolver::LinearSolver(std::shared_ptr<CIFem::Structure> structure, Vector3d gravityDirection)
{
	_structure = structure;
	_gravityOn = true;
	_gravityField = gravityDirection;
}


CIFem::LinearSolver::~LinearSolver()
{
}

void CIFem::LinearSolver::Solve()
{
	//Get all unique dofs from structure
	DofSet spDofs = GetDofs();

	// Update dof kIndex and clear dof loads
	SetUpDofs(spDofs);

	//Apply element loads to dofs (need to add something that creates linear loads over elements etc)
	ApplyGravityToElements();

	//Apply Node forces to dofs
	ApplyNodalForces();

	//Get the stiffness matrix from the structure
	arma::mat K = _structure->AssembleStiffnessMatrix(spDofs.size());

	
	arma::mat C = _structure->GetCMatrix();				// Get transformation vector for restraints

	// Get a and f vectors 
	arma::colvec am = GetDisplacementVector(spDofs);	// Get displacement vector
	arma::colvec f = GetForceVector(spDofs);			// Get force vector

	// Solve K matrix
	arma::colvec s;		// Resulting forces
	LinEqSolve(K, am, f, C, spDofs, s);

	// Store results in dofs
	StoreResultsInDofs(am, s, spDofs);

	//Calculate section forces for the elements
	CalculateElementSectionForces();

}

void CIFem::LinearSolver::ApplyGravityToElements()
{
	if (_gravityOn)
		_structure->ApplyGravityToElements(_gravityField);
}

void CIFem::LinearSolver::ApplyNodalForces()
{
	_structure->ApplyNodalForces();
}

arma::colvec CIFem::LinearSolver::GetForceVector(std::set<std::shared_ptr<DOF>> spDofs)
{
	arma::colvec f(spDofs.size(), arma::fill::zeros);

	for each (std::shared_ptr<DOF> spDof in spDofs)
		f(spDof->GetKIndex()) = spDof->GetLoad();

	return f;
}

// Creates a displacement vector from the dofs.
// N.B. the displacement vector is in transformed coordinates (am, rather than as)
arma::colvec CIFem::LinearSolver::GetDisplacementVector(std::set<std::shared_ptr<DOF>> spDofs)
{
	arma::colvec a(spDofs.size(), arma::fill::zeros);

	for each (std::shared_ptr<DOF> spDof in spDofs)
		if (spDof->HasSetTranslation())
			a(spDof->GetKIndex()) = spDof->GetTranslation();

	return a;
}



void CIFem::LinearSolver::LinEqSolve(arma::mat & K, arma::colvec & a, arma::colvec & f, arma::mat & C, DofSet spDofs, arma::colvec & s)
{
	// Check prescribed deformations
	std::vector<unsigned int> transBCDof;
	std::vector<unsigned int> fDof;
	std::vector<unsigned int> pDof;
	for each (std::shared_ptr<DOF> dof in spDofs)
	{
		// Check transformed bcs
		if (dof->HasTransformedBc())
			transBCDof.push_back(dof->GetKIndex());


		// Check prescribed deformations
		if (dof->HasSetTranslation())
			pDof.push_back(dof->GetKIndex());
		else
			fDof.push_back(dof->GetKIndex());

	}

	// There must be a way to do this from the start,
	// however, I think uvec is fixed size
	arma::uvec ufDof(fDof);
	arma::uvec upDof(pDof);

	arma::colvec fa(fDof.size());

	// Solve deformations

	arma::mat f_fsolved = f(ufDof) - K(ufDof, upDof) * a(upDof);
	//fa = arma::spsolve(Kff, f_fsolved);
	fa = arma::solve(K(ufDof, ufDof), f_fsolved);
	a(ufDof) = fa;

	// Solve forces
	s = K*a - f;
}