#pragma once

#include "CIFem_dll.h"

namespace CIFem
{

	class CIFEM_API Material
	{
		double _E, _poi, _rho;
	public:
		Material();
		Material(double E, double poi, double rho);
		~Material();


		double E();
		double Rho();
		double G();
		double Poisson();
	};
}

