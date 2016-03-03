#include "IElement.h"


void CIFem::IElement::SetEdof(std::vector<std::shared_ptr<DOF> > edof)
{
	int length = edof.size();

	if (length != GetSize())
		throw std::invalid_argument("Number of degrees of freedom should be 12.");
	else
	{
		_dof.clear();
		for (int i = 0; i < length; i++)
		{
			_dof.push_back(edof[i]);
		}
	}
}

std::vector<int> CIFem::IElement::GetDofIndecies()
{
	std::vector<int> ind;

	for (int i = 0; i < GetSize(); i++)
	{
		ind.push_back(_dof[i]->GetKIndex());
	}

	return ind;
}
