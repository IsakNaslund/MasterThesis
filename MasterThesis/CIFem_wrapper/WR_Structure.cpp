#include "stdafx.h"
#include "WR_Structure.h"

using namespace CIFem_wrapper;

WR_Structure::WR_Structure()
{
	_structure = new CIFem::Structure();
}

WR_Structure::~WR_Structure()
{
	delete _structure;
	_structure = 0;
}

void WR_Structure::AddNode(WR_INode^ wrNode)
{
	_structure->AddNode(wrNode->GetNode());
}

void CIFem_wrapper::WR_Structure::AddElementRcp(WR_IElemRcp^ wrRcp)
{
	_structure->AddElementRcp(wrRcp->GetRecipe());
}

void CIFem_wrapper::WR_Structure::Solve()
{
	_structure->Solve();
}

