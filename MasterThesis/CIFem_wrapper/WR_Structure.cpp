#include "stdafx.h"
#include "WR_Structure.h"


WR_Structure::WR_Structure()
{
	_structure = new CIFem::Structure();
}

WR_Structure::~WR_Structure()
{
	delete _structure;
	_structure = 0;
}

void WR_Structure::AddNode(WR_INode wrNode)
{
	_structure->AddNode(wrNode.GetNode());
}

void WR_Structure::AddNode(std::vector<WR_INode> wrNodeList)
{
	throw gcnew System::NotImplementedException();
}
