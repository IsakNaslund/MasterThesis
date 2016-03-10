#pragma once

#include "include\armadillo"
#include "CIFem_dll.h"
#include <memory>
#include <vector>
#include "DOF.h"
#include "Vector3d.h"
#include "ICrossSection.h"
#include "IUtilisationCheck.h"

namespace CIFem
{
	class CIFEM_API IElement
	{
	protected:
		std::vector<std::shared_ptr<DOF>> _dof;
		virtual int GetSize() =0;
		void SetEdof(std::vector<std::shared_ptr<DOF> > edof);
		std::shared_ptr<ICrossSection> _crossSection;
	
	public:

		virtual ~IElement();
		virtual arma::Mat<double> GetStiffnessMatrix() = 0;
		const std::vector<std::shared_ptr<DOF>> & GetDofs() { return _dof; }
		std::vector<int> GetDofIndecies();


		virtual arma::Col<double> GravityLoad() {  return GravityLoad(-9.82); }
		virtual arma::Col<double> GravityLoad(double factor) { return GravityLoad(Vector3d(0, 0, factor)); }
		virtual arma::Col<double> GravityLoad(Vector3d direction) = 0;

		virtual void CalculateSectionForces() = 0;
		virtual void DoSectionChecks() = 0;
	};
}

