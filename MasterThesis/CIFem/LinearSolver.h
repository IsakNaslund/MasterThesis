#pragma once

#include "CIFem_dll.h"
#include "Structure.h"
#include <memory>
#include "ISolver.h"
#include "Vector3d.h"

typedef std::set<std::shared_ptr<CIFem::DOF>> DofSet;

namespace CIFem
{
	class CIFEM_API LinearSolver : public CIFem::ISolver
	{
		bool _gravityOn;
		Vector3d _gravityField;

	public:
		LinearSolver();
		LinearSolver(std::shared_ptr<CIFem::Structure> structure);
		LinearSolver(std::shared_ptr<CIFem::Structure> structure, bool applyGravity);
		LinearSolver(std::shared_ptr<CIFem::Structure> structure, Vector3d gravityDirection);
		~LinearSolver();

		void Solve();


	private:

		void ApplyGravityToElements();
		void ApplyNodalForces();

		arma::colvec GetForceVector(std::set<std::shared_ptr<DOF>>);
		arma::colvec GetDisplacementVector(std::set<std::shared_ptr<DOF>>);

		void LinEqSolve(arma::mat & K, arma::colvec & a, arma::colvec & f, arma::mat & C, DofSet, arma::colvec & s);
	};
}

