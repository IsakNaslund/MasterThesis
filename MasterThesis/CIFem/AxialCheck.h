#pragma once
#include "IUtilCheck3d.h"

namespace CIFem
{

	class AxialCheck :
		public IUtilCheck3d
	{
	public:
		AxialCheck();
		~AxialCheck();

		double CheckElementUtilisations(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results, std::string resName, int elementPosition);
	};
}

