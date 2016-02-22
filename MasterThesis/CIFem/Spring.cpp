#include "Spring.h"

using namespace CIFem;


Spring::Spring()
{
}


Spring::~Spring()
{
}

arma::Mat<double> CIFem::Spring::GetStiffnessMatrix()
{
	arma::Mat<double> ke;

	ke	<< _k << -_k << arma::endr
		<< -_k << _k << arma::endr;

	return ke;
}

std::vector<int> CIFem::Spring::GetDofs()
{
	return std::vector<int>();
}
