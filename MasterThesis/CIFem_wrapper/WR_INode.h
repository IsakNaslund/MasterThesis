#pragma once
#include "INode.h"
#include "m_shared_ptr.h"


namespace CIFem_wrapper
{

	public ref class WR_INode
	{
	protected:
		m_shared_ptr<CIFem::INode> _node;
	public:
		~WR_INode();
		std::shared_ptr<CIFem::INode> GetNode();

	};

}