#include "stdafx.h"
#include "WR_INode.h"

using namespace CIFem_wrapper;

WR_INode::~WR_INode()
{
	delete _node;
	_node = 0;
}

CIFem::INode * WR_INode::GetNode()
{
	return _node;
}
