#pragma once

#include "XYZ.h"
#include "CIFem_dll.h"
#include "DOF.h"
#include <memory>
#include <vector>

namespace CIFem
{
	class CIFEM_API Node3d
	{
		XYZ _location;
		std::vector<std::shared_ptr<DOF>> _dof;
	public:
		Node3d();
		Node3d(const XYZ location);
		Node3d(const XYZ location, unsigned int startindex);
		~Node3d();

		std::vector<std::shared_ptr<DOF>> GetDofs();

	private:
		void InitNewDofs(int);
	};

}

