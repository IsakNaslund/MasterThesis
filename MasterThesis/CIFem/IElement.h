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
	class Utilisation;
	class CIFEM_API IElement
	{
	protected:

		bool _updateStiffnessMatrix;
		std::vector<std::shared_ptr<DOF>> _dof;
		virtual int GetSize() =0;
		void SetEdof(std::vector<std::shared_ptr<DOF> > edof);

		virtual void DoSectionChecks(std::string resName) = 0;
	public:

		virtual ~IElement();
		virtual const arma::Mat<double> & GetStiffnessMatrix() = 0;
		const std::vector<std::shared_ptr<DOF>> & GetDofs() { return _dof; }
		std::vector<int> GetDofIndecies();

		virtual void ResetElementForces() {  }

		virtual arma::Col<double> GravityLoad() {  return GravityLoad(-9.82); }
		virtual arma::Col<double> GravityLoad(double factor) { return GravityLoad(Vector3d(0, 0, factor)); }
		virtual arma::Col<double> GravityLoad(Vector3d direction) = 0;

		virtual void CalculateSectionForces(std::string resultName) = 0;

		virtual double Weight() const = 0;

		virtual bool UpdateElement() = 0;
		virtual bool UpdateElementOrientation() = 0;
		virtual Utilisation CalcAndGetMaxUtil() = 0;

	};
}

