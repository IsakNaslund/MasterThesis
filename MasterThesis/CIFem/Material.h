#pragma once

#include "CIFem_dll.h"

namespace CIFem
{

	class CIFEM_API Material
	{
		double _E, _poi, _rho;
		double _fu;	// Ultimate stress capacity. Currently written for a "steel-like behaviour", so may need to be changed in the future.

	public:
		Material();
		Material(double E, double poi, double rho, double fu);
		~Material();


		double E();
		double Rho();
		double G();
		double Fu();
		double Poisson();
	};
}

