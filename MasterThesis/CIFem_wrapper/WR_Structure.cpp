#include "stdafx.h"
#include "WR_Structure.h"

using namespace CIFem_wrapper;

WR_Structure::WR_Structure()
{
	_structure = gcnew m_shared_ptr<CIFem::Structure>(new CIFem::Structure());
}

WR_Structure::~WR_Structure()
{

}

void WR_Structure::AddNode(WR_INode^ wrNode)
{
	_structure.operator std::shared_ptr<CIFem::Structure>()->AddNode(wrNode->GetNode());
}

void CIFem_wrapper::WR_Structure::AddElementRcp(WR_IElemRcp^ wrRcp)
{
	_structure.operator std::shared_ptr<CIFem::Structure>()->AddElementRcp(wrRcp->GetRecipe());
}

System::Collections::Generic::List<WR_IElement^>^ CIFem_wrapper::WR_Structure::GetElements()
{
	System::Collections::Generic::List<WR_IElement^>^ elems =
		gcnew System::Collections::Generic::List<WR_IElement^>();
	
	
	throw gcnew System::NotImplementedException();
	// TODO: insert return statement here
}

void CIFem_wrapper::WR_Structure::Solve()
{
	_structure.operator std::shared_ptr<CIFem::Structure>()->Solve();
}

