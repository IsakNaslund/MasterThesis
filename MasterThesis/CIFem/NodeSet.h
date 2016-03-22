#pragma once

#include <vector>
#include "INode.h"
#include <memory>

namespace CIFem
{
	//Not implemented yet....... is it worth it??
	class NodeSet
	{
		std::vector<std::shared_ptr<INode>> _nodes;
	public:
		NodeSet();
		~NodeSet();
		
	};
}

