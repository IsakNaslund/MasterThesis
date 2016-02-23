#pragma once

#include "CIFem_dll.h"


namespace CIFem
{
	class INode
	{
	public:
		//INode() {};
		virtual ~INode() {};

		virtual double DistanceTo(const INode* other) const = 0;
		virtual std::vector<std::shared_ptr<DOF>> GetDofs() = 0;
	};

}

