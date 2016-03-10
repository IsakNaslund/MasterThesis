#pragma once
#include "CIFem_dll.h"
#include <vector>
#include "IElement.h"

namespace CIFem
{
	class CIFEM_API IElementResults
	{

	public:
		IElementResults();
		~IElementResults();

		virtual void Reset() = 0;
		double GetMaxAbsolute(std::vector<double> forces);
		void UpdateUtilisation(double u);

	protected:
		//Utilisation
		double _maxUtil = 0;	// Initialise to 0
	};
}

