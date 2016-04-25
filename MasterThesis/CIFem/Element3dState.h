#pragma once
#include "Material.h"
#include "ICrossSection.h"
#include "Vector3d.h"
#include <memory>
#include "ElementResults3d.h"

namespace CIFem
{
	class Element3dState
	{
		friend class Element3d;

		std::shared_ptr<Material> _mat;
		Vector3d _eo;			// Element orientation
		//ElementResults3d _results; //not sure if results should be stored in here....

		std::shared_ptr<ICrossSection> _crossSection;

	public:
		Element3dState();
		Element3dState(std::shared_ptr<Material> mat, Vector3d eo, std::shared_ptr<ICrossSection> crossSec);
		~Element3dState();
	};
}

