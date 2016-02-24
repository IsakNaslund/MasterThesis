#include "Structure.h"

CIFem::Structure::Structure()
{
}


CIFem::Structure::~Structure()
{
	for (int i = 0; i < _elements.size(); i++)
		delete _elements[i];

	_elements.clear();
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
	_elementRcps.push_back(elementRcp);
}

void CIFem::Structure::AddElementRcp(std::vector<IElementRcp *> elements)
{
	for (int i = 0; i < elements.size(); i++)
		AddElementRcp(elements[i]);
}

void CIFem::Structure::Solve()
{
	// Build structure
	BuildStructure();

	// Update dof kIndex


	// Create K matrix


	// Solve K matrix


	// Store results in dofs
}


std::vector<CIFem::IElement *> CIFem::Structure::CreateElements(
	std::vector<IElementRcp *> elRcps, std::vector<INode *> nodes)
{
	std::vector<IElement *> elements;
	std::vector<IElement *> outElems;
	for (int i = 0; i < elRcps.size(); i++)
	{
		outElems.clear();
		outElems = elRcps[i]->CreateElement(nodes);

		for (int j = 0; j < outElems.size(); j++)
			elements.push_back(outElems[j]);
	}

	return elements;
}

void CIFem::Structure::BuildStructure()
{
	// Create elements from recipes and assign
	_elements = CreateElements(_elementRcps, _nodes);
}

void CIFem::Structure::SortAndIndexDofs()
{

}
