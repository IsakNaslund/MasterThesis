#pragma once

#include "XYZ.h"
#include "CIFem_dll.h"
#include "DOF.h"
#include <memory>
#include <vector>
#include "INode.h"

namespace CIFem
{
	class CIFEM_API Node3d : public INode
	{
		XYZ _location;
		std::vector<std::shared_ptr<DOF>> _dof;
	public:
		Node3d();
		Node3d(const XYZ location);
		Node3d(const XYZ location, unsigned int startindex);
		~Node3d();

		std::vector<std::shared_ptr<DOF>> GetDofs();

		double DistanceTo(const Node3d* other) const;
		double DistanceTo(const INode* other) const;
		double DistanceTo(const XYZ& otherPt) const;

	private:
		void InitNewDofs(int);
	};

}

