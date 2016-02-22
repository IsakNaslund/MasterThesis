#pragma once

#include "include\armadillo"

namespace CIFem
{
	class IElement
	{
	public:
		virtual arma::Mat<double> GetStiffnessMatrix() = 0;
		virtual std::vector <int> GetDofs() = 0;
	};
}

