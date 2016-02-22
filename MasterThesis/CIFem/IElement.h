#pragma once

#include "include\armadillo"
#include "CIFem_dll.h"

namespace CIFem
{
	class CIFEM_API IElement
	{
	public:
		virtual arma::Mat<double> GetStiffnessMatrix() = 0;
		virtual std::vector <int> GetDofs() = 0;
	};
}

