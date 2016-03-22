#pragma once

#include "CIFem_dll.h"
#include <memory>
#include <set>
#include "DOF.h"
#include "Structure.h"

typedef std::set<std::shared_ptr<CIFem::DOF>> DofSet;

namespace CIFem
{
	class CIFEM_API ISolver
	{
	protected:
		std::shared_ptr<CIFem::Structure> _structure;

		void SetUpDofs(DofSet & spDofs);
		void StoreResultsInDofs(const arma::colvec & a, const arma::colvec & f, DofSet & spDofs);
		void CalculateElementSectionForces();
		DofSet GetDofs();
		void ResetAllForces(DofSet & spDofs);

	public:

		virtual void Solve() = 0;

	};
}

