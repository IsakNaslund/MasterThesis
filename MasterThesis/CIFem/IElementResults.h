#pragma once
#include "CIFem_dll.h"
#include <vector>
#include "IElement.h"
#include "Utilisation.h"
#include <map>

typedef std::map<std::string, std::vector<double>> combResList;

namespace CIFem
{
	class CIFEM_API IElementResults
	{

	public:
		IElementResults();
		~IElementResults();

		virtual void Reset() = 0;
		double GetMaxAbsolute(std::vector<double> forces);
		double GetMaxAbsolute(const combResList & forces);
		void UpdateMaxUtilisation(Utilisation u);

	protected:
		//Utilisation
		Utilisation _maxUtil;
	};
}

