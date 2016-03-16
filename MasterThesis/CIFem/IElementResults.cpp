#include "IElementResults.h"

namespace CIFem
{

	IElementResults::IElementResults()
	{
	}


	IElementResults::~IElementResults()
	{
	}

	double IElementResults::GetMaxAbsolute(std::vector<double> forces)
	{
		double max = -1e99;
		double min = 1e99;

		for (size_t i = 0; i < forces.size(); i++)
		{
			if (forces[i] > max)
				max = forces[i];
			if (forces[i] < min)
				min = forces[i];
		}

		if (abs(max) >= abs(min))
			return max;
		else
			return min;
	}

	void IElementResults::UpdateMaxUtilisation(Utilisation u)
	{
		_maxUtil.Update(u.GetUtil(), u.GetDesc());
	}
}
