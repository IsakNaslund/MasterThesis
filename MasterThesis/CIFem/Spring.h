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

		arma::mat::fixed<2, 2> _Ke;
	public:
		Spring();
		Spring(double k);
		Spring(double k, std::vector<std::shared_ptr<DOF> > dofs);

		~Spring();


		void UpdateStiffnessMatrix();
		const arma::Mat<double> & GetStiffnessMatrix();
		std::vector<int> GetDofs();

		arma::Col<double> GravityLoad(Vector3d direction) { return arma::vec(); }

		void CalculateSectionForces(std::string resultName);
		

	protected:
		void DoSectionChecks(std::string resName);
		int GetSize() { return 2; };
	};

}
