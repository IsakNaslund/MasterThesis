#pragma once
#include "CIFem_dll.h"
#include <vector>
#include "INode.h"
#include "IElementRcp.h"

namespace CIFem
{
	class CIFEM_API Structure
	{
		std::vector<INode *> _nodes;
		std::vector<IElementRcp *> _elements;

	public:
		Structure();
		~Structure();

		void AddNode(INode *);
		void AddNode(std::vector<INode *>);
		void AddElementRcp(IElementRcp *);
		void AddElementRcp(std::vector<IElementRcp *>);

		void Solve();

	private:
		void BuildStructure();
	};
}

