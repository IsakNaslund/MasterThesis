#pragma once

#include "CIFem_dll.h"
#include "include\armadillo"
#include "IElement.h"
#include <vector>
#include <memory>
#include "DOF.h"

namespace CIFem
{

	class CIFEM_API Spring :public IElement
	{
		double _k;
	public:
		Spring();
		Spring(double k);
		Spring(double k, std::vector<std::shared_ptr<DOF> > dofs);

		~Spring();
		arma::Mat<double> GetStiffnessMatrix();
		std::vector <int> GetDofs();

	protected:
		int GetSize() { return 2; };
	};

}
