#pragma once
#include "CIFem_dll.h"
#include <vector>
#include "IElement.h"
#include "Utilisation.h"

namespace CIFem
{
	class CIFEM_API IElementResults
	{

	public:
		IElementResults();
		~IElementResults();

		virtual void Reset() = 0;
		double GetMaxAbsolute(std::vector<double> forces);
		void UpdateMaxUtilisation(Utilisation u);

	protected:
		//Utilisation
		Utilisation _maxUtil;
	};
}

