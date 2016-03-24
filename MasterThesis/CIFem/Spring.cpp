#include "Spring.h"

using namespace CIFem;


Spring::Spring()
{
}

CIFem::Spring::Spring(double k)
{
	_k = k;
}

CIFem::Spring::Spring(double k, std::vector<std::shared_ptr<DOF>> dofs)
{
	_k = k;
	SetEdof(dofs);
	UpdateStiffnessMatrix();
}


Spring::~Spring()
{
}

void CIFem::Spring::UpdateStiffnessMatrix()
{
	_Ke << _k << -_k << arma::endr
		<< -_k << _k << arma::endr;

}

const arma::Mat<double> & CIFem::Spring::GetStiffnessMatrix()
{
	return _Ke;
}

std::vector<int> CIFem::Spring::GetDofs()
{
	return std::vector<int>();
}

void CIFem::Spring::CalculateSectionForces(std::string resultName)
{
	//save this is some way....
	double stress = _k*(_dof[1]->GetResultingTranslation() - _dof[0]->GetResultingTranslation());
}

void CIFem::Spring::DoSectionChecks(std::string resName)
{
	//do nothing, IMPLEMENT
}
