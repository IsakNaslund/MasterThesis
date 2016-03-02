#pragma once

#include "Structure.h"
#include "WR_INode.h"
#include "WR_IElemRcp.h"
#include "m_shared_ptr.h"

namespace CIFem_wrapper
{
	public ref class WR_Structure
	{
		m_shared_ptr<CIFem::Structure> _structure;
	public:
		WR_Structure();
		~WR_Structure();

		void AddNode(WR_INode^ wrNode);
		//void AddNode(std::vector<WR_INode> wrNodeList);
		void AddElementRcp(WR_IElemRcp^ wrRcp);
		//void AddElementRcp(std::vector<IElementRcp *>);

		void Solve();
	};
}
