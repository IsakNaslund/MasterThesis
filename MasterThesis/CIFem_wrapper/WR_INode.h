#pragma once
#include "INode.h"

ref class WR_INode
{
protected:
	CIFem::INode* _node;
public:
	~WR_INode();
	CIFem::INode* GetNode();
	
};

