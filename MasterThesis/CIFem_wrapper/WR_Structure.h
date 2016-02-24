#pragma once

#include "Structure.h"
#include "WR_INode.h"

ref class WR_Structure
{
	CIFem::Structure* _structure;
public:
	WR_Structure();
	~WR_Structure();

	void AddNode(WR_INode wrNode);
	void AddNode(std::vector<WR_INode> wrNodeList);
	void AddElementRcp(IElementRcp *);
	void AddElementRcp(std::vector<IElementRcp *>);

	void Solve();
};

