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

	double IElementResults::GetMaxAbsolute(const combResList & forces)
	{
		double max = -1e99;
		double min = 1e99;

		for each (std::pair<std::string, std::vector<double>> var in forces)
		{
			for (size_t i = 0; i < var.second.size(); i++)
			{
				if (var.second[i] > max)
					max = var.second[i];
				if (var.second[i] < min)
					min = var.second[i];
			}
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
