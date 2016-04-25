#include "UtilisationSet.h"



CIFem::UtilisationSet::UtilisationSet()
{
}


CIFem::UtilisationSet::~UtilisationSet()
{
}

void CIFem::UtilisationSet::Update(double utilisation, std::string description, int i)
{
	_maxUtil.Update(utilisation, description);
	_utilisations[i]->Update(utilisation, description);
}

void CIFem::UtilisationSet::Reset()
{
	_maxUtil.Reset();
	for (int i = 0; i < _utilisations.size(); i++)
	{
		_utilisations[i]->Reset();
	}
}

void CIFem::UtilisationSet::Clear()
{
	_maxUtil.Reset();
	_utilisations.clear();
}

void CIFem::UtilisationSet::SetUpEmptyUtilisations(int nb)
{
	for (int i = 0; i < nb; i++)
	{
		_utilisations.push_back(std::shared_ptr<Utilisation>(new Utilisation));
	}
}

void CIFem::UtilisationSet::ScaleUtilisation(double sFac)
{
	_maxUtil._util *= sFac;

	for (int i = 0; i < _utilisations.size(); i++)
	{
		_utilisations[i]->_util *= sFac;
	}
}





