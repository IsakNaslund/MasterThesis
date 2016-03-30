#include "EigenSolver.h"



CIFem::EigenSolver::EigenSolver()
{
}

CIFem::EigenSolver::EigenSolver(std::shared_ptr<CIFem::Structure> structure)
{
	_structure = structure;
}


CIFem::EigenSolver::~EigenSolver()
{
}

void CIFem::EigenSolver::Solve()
{
	//Get dofs
	_dofs = GetDofs();

	// Update dof kIndex and clear dof loads
	SetUpDofs(_dofs);

	//Create K-matrix
	_K = _structure->AssembleStiffnessMatrix(_dofs.size());


	// Get a and f vectors 
	arma::mat C = _structure->GetCMatrix();				// Get transformation vector for restraints

														// Solve K matrix
	arma::colvec s;		// Resulting forces
	arma::colvec am;
	EigenSolve(_K, C, _dofs);

}

double CIFem::EigenSolver::SetResultsToMode(int mode)
{
	int size = _K.n_rows;
	arma::colvec a(size, arma::fill::zeros);

	a(_fDof) = _eigenVectors.col(mode);

	// Solve forces
	arma::colvec s = _K*a;



	StoreResultsInDofs(a, s, _dofs);

	CalculateElementSectionForces("Mode " + std::to_string(mode));

	return _eigenValues(mode);
}

void CIFem::EigenSolver::EigenSolve(arma::mat & K, arma::mat & C, DofSet spDofs)
{

	/////////////////////////////////////////////////////////////////////////////
	////////////////////////Uncompleted Eigensolver!!!!!!!!!!!!!!!///////////////
	/////////////////////////////////////////////////////////////////////////////


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
	_fDof = arma::uvec(fDof);
	arma::uvec upDof(pDof);

	// Solve Eigenvalue problem
	arma::eig_sym(_eigenValues, _eigenVectors, K(_fDof, _fDof));


}