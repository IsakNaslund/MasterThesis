#pragma once

#include "include\armadillo"
#include "CIFem_dll.h"
#include <memory>
#include <vector>
#include "DOF.h"

namespace CIFem
{
	class CIFEM_API IElement
	{
	protected:
		std::vector<std::shared_ptr<DOF>> _dof;
		virtual int GetSize() =0;
		void SetEdof(std::vector<std::shared_ptr<DOF> > edof);

	public:
		virtual arma::Mat<double> GetStiffnessMatrix() = 0;
		std::vector<std::shared_ptr<DOF>> GetDofs() { return _dof; }
		std::vector<int> GetDofIndecies();
	};
}

