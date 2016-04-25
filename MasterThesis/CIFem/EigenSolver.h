#pragma once

#include "CIFem_dll.h"
#include "Structure.h"
#include <memory>
#include "ISolver.h"

namespace CIFem
{
	class CIFEM_API EigenSolver :public ISolver
	{
		arma::mat _eigenVectors;
		arma::vec _eigenValues;
		arma::mat _K;

		arma::uvec _fDof; //Free dofs saved from solver
		DofSet _dofs;

	public:
		EigenSolver();
		EigenSolver(std::shared_ptr<CIFem::Structure> structure);
		~EigenSolver();

		void Solve();

		double SetResultsToMode(int mode);

		// Returns a list of the n first eigenvalues. Requires that the EigenSolve function has been called first
		std::vector<double> GetEigenValues(int n);

	private:

		void CIFem::EigenSolver::EigenSolve(arma::mat & K, arma::mat & C, DofSet spDofs);
	};
}

