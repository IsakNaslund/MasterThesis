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
		LoadCombination(std::string name);
		LoadCombination(std::string name, Vector3d gravField);
		LoadCombination(std::string name, bool gravityOn);
		~LoadCombination();

		void AddPointLoad(PointLoad ptL);
		void AddPointLoad(Vector3d force, Vector3d moment, XYZ pos);

		void SetGravity(Vector3d gravField);
		void SetGravity(bool gravityOn);

		const bool & getGravityOn() const { return _gravityOn; }
		const Vector3d & getGravityField() const { return _gravField; }
		const std::vector<PointLoad> & getPointLoad() const { return _pointLoads; }
	};
}

