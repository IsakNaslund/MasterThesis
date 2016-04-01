#pragma once
#include "IUtilCheck3d.h"


namespace CIFem
{
	class ShearZCheck :
		public IUtilCheck3d
	{
	public:
		ShearZCheck();
		~ShearZCheck();

		double CheckElementUtilisations(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results, std::string resName, int elementPosition);
	};
}

