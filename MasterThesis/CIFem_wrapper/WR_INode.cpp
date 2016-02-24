#include "stdafx.h"
#include "WR_INode.h"


WR_INode::~WR_INode()
{
	delete _node;
	_node = 0;
}

CIFem::INode * WR_INode::GetNode()
{
	return _node;
}
