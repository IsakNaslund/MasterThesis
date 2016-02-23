#include "Structure.h"



CIFem::Structure::Structure()
{
}


CIFem::Structure::~Structure()
{
}

void CIFem::Structure::AddNode(INode * node)
{
	_nodes.push_back(node);
}

void CIFem::Structure::AddNode(std::vector<INode *> nodes)
{
	for (int i = 0; i < nodes.size(); i++)
		AddNode(nodes[i]);
}

void CIFem::Structure::AddElementRcp(IElementRcp * elementRcp)
{
	_elements.push_back(elementRcp);
}

void CIFem::Structure::AddElementRcp(std::vector<IElementRcp *> elements)
{
	for (int i = 0; i < elements.size(); i++)
		AddElementRcp(elements[i])
}

void CIFem::Structure::BuildStructure()
{

}
