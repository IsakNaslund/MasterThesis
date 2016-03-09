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


/*
System::Collections::Generic::List<WR_Element3d^>^ CIFem_wrapper::WR_Structure::GetElements3d()
{
	System::Collections::Generic::List<WR_IElement^>^ elems = GetAllElements();

	for (int i = 0; i < elements.size(); i++)
	{
		CIFem::IElement* e = elements[i].get();

		// Element3d
		Element3d* elem3d = dynamic_cast<CIFem::Element3d*>(e);

		if (elem3d != NULL)
		{
			WR_Element3d^ addElem = gcnew WR_Element3d(std::shared_ptr<Element3d>(elem3d));
			elems->Add(addElem);
		}


		// ADD SPRING FUNCTIONS HERE

	}
	

	return elems;
}
*/


void CIFem_wrapper::WR_Structure::Solve()
{
	_structure.operator std::shared_ptr<CIFem::Structure>()->Solve();
}

double CIFem_wrapper::WR_Structure::EigenSolve(int mode)
{
	return _structure.operator std::shared_ptr<CIFem::Structure>()->SolveEigenvalue(mode);
}

// Currently only implemented to return Element3d
System::Collections::Generic::List<WR_IElement^>^ CIFem_wrapper::WR_Structure::GetAllElements()
{
	System::Collections::Generic::List<WR_IElement^>^ elems =
		gcnew System::Collections::Generic::List<WR_IElement^>();

	std::vector<std::shared_ptr<CIFem::IElement>> elements =
		_structure.operator std::shared_ptr<CIFem::Structure>()->GetElements();

	for (int i = 0; i < elements.size(); i++)
	{
		CIFem::IElement* e = elements[i].get();

		// Element3d
		Element3d* elem3d = dynamic_cast<CIFem::Element3d*>(e);

		if (elem3d != NULL && elem3d != nullptr)
		{
			WR_Element3d^ addElem = gcnew WR_Element3d(std::static_pointer_cast<Element3d>(elements[i]));
			//WR_Element3d^ addElem = gcnew WR_Element3d(std::shared_ptr<Element3d>(elem3d));
			elems->Add(addElem);
		}


		// Spring
		Spring* spring = dynamic_cast<CIFem::Spring*>(e);
		if (spring != NULL && spring != nullptr)
		{
			// TODO: IMPLEMENT
		}
	}

	return elems;
}

