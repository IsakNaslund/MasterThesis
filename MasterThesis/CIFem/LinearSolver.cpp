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

	//Get the stiffness matrix from the structure
	arma::mat K = _structure->AssembleStiffnessMatrix(spDofs.size());

	for (int i = 0; i < _loadCobms.size(); i++)
	{
		//Reset all forces on dofs and elements
		ResetAllForces(spDofs);

		//Apply element loads to dofs (need to add something that creates linear loads over elements etc)
		ApplyGravityToElements(_loadCobms[i]);

		//Apply Node forces to dofs
		ApplyNodalForces(_loadCobms[i].getPointLoad());

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
		CalculateElementSectionForces(_loadCobms[i].Name());
	}
}

void CIFem::LinearSolver::AddLoadCombination(LoadCombination comb)
{
	_loadCobms.push_back(comb);
}

void CIFem::LinearSolver::ApplyGravityToElements(const LoadCombination & loadComb)
{
	if (loadComb.getGravityOn())
		_structure->ApplyGravityToElements(loadComb.getGravityField());
}

void CIFem::LinearSolver::ApplyNodalForces()
{
	_structure->ApplyNodalForces();
}

void CIFem::LinearSolver::ApplyNodalForces(const std::vector<PointLoad>& pointLoads)
{
	for (int i = 0; i < pointLoads.size(); i++)
	{
		for each (std::shared_ptr<INode> node in _structure->GetNodes())
		{
			//ugly way of applying the loads.... Should we even be working with INodes?....
			// forthis to be more generic we need to add other stuff such as Vector2d, Pointload 2d etc...
			double dist = node->DistanceTo(pointLoads[i].Pos());
			if (dist >= 0 && dist < GlobalTol)
			{
				std::vector<std::shared_ptr<DOF>> nodeDofs = node->GetDofs();
				nodeDofs[0]->AddLoad(pointLoads[i].Force().GetX());
				nodeDofs[1]->AddLoad(pointLoads[i].Force().GetY());
				nodeDofs[2]->AddLoad(pointLoads[i].Force().GetZ());
				nodeDofs[3]->AddLoad(pointLoads[i].Moment().GetX());
				nodeDofs[4]->AddLoad(pointLoads[i].Moment().GetY());
				nodeDofs[5]->AddLoad(pointLoads[i].Moment().GetZ());

				break;
			}
		}
	}
}

arma::colvec CIFem::LinearSolver::GetForceVector(DofSet & spDofs)
{
	arma::colvec f(spDofs.size(), arma::fill::zeros);

	for each (std::shared_ptr<DOF> spDof in spDofs)
		f(spDof->GetKIndex()) = spDof->GetLoad();

	return f;
}

// Creates a displacement vector from the dofs.
// N.B. the displacement vector is in transformed coordinates (am, rather than as)
arma::colvec CIFem::LinearSolver::GetDisplacementVector(DofSet & spDofs)
{
	arma::colvec a(spDofs.size(), arma::fill::zeros);

	for each (std::shared_ptr<DOF> spDof in spDofs)
		if (spDof->HasSetTranslation())
			a(spDof->GetKIndex()) = spDof->GetTranslation();

	return a;
}



void CIFem::LinearSolver::LinEqSolve(arma::mat & K, arma::colvec & a, arma::colvec & f, arma::mat & C, DofSet & spDofs, arma::colvec & s)
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