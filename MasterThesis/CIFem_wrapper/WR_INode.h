#pragma once
#include "INode.h"


namespace CIFem_wrapper
{

	ref class WR_INode
	{
	protected:
		CIFem::INode* _node;
	public:
		~WR_INode();
		CIFem::INode* GetNode();

	};

}