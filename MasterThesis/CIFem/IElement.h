#pragma once

#include "include\armadillo"
#include "CIFem_dll.h"
#include <memory>

class DOF;

namespace CIFem
{
	class CIFEM_API IElement
	{
		std::vector<std::shared_ptr<DOF>> _dof;
	public:
		virtual arma::Mat<double> GetStiffnessMatrix() = 0;
		virtual std::vector <int> GetDofs() = 0;
	};
}

