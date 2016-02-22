#pragma once

#include "CIFem_dll.h"
#include "include\armadillo"
#include "IElement.h"

namespace CIFem
{

	class CIFEM_API Spring : IElement
	{
		double _k;
	public:
		Spring();
		~Spring();
		arma::Mat<double> GetStiffnessMatrix();
		std::vector <int> GetDofs();
	};

}
