#pragma once


#include "CIFem_dll.h"
#include <string>
#include <vector>
#include "Vector3d.h"
#include "PointLoad.h"



namespace CIFem
{
	class CIFEM_API LoadCombination
	{
		std::string _name;
		Vector3d _gravField;
		bool _gravityOn;
		std::vector<PointLoad> _pointLoads;
		

	public:
		LoadCombination();
		~LoadCombination();

		void AddPointLoad(PointLoad ptL);
		void AddPointLoad(Vector3d force, Vector3d moment, XYZ pos);

	};
}

