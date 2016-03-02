#include "stdafx.h"
#include "WR_INode.h"

using namespace CIFem_wrapper;

WR_INode::~WR_INode()
{
}

std::shared_ptr<CIFem::INode> WR_INode::GetNode()
{
	return *_node.share();
}

WR_INode ^ CIFem_wrapper::WR_INode::Copy()
{
	throw gcnew System::NotImplementedException();
	// TODO: insert return statement here

}
