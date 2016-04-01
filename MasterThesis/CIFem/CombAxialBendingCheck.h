#pragma once
#include "IUtilCheck3d.h"

namespace CIFem
{
	class CombAxialBendingCheck :
		public IUtilCheck3d
	{
	public:
		CombAxialBendingCheck();
		~CombAxialBendingCheck();

		double CheckElementUtilisations(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results, std::string resName, int elementPosition);
	};
}

