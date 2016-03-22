#include "Utilisation.h"

using namespace CIFem;

Utilisation::Utilisation()
{
	Reset();
}

CIFem::Utilisation::Utilisation(double utilisation, std::string description)
{
	_util = utilisation;
	_description = description;
}


Utilisation::~Utilisation()
{
}

// Returns a new shared pointer to an identical object
std::shared_ptr<Utilisation> CIFem::Utilisation::Copy()
{
	std::shared_ptr<Utilisation> u(new Utilisation(_util, _description));
	return u;
}

void CIFem::Utilisation::Reset()
{
	_util = 0;
	_description = "Unset utilisation";
}

//Updates information if new utilisation is larger than old one
void CIFem::Utilisation::Update(double utilisation, std::string description)
{
	if (abs(utilisation)>abs(_util))
	{
		_util = utilisation;
		_description = description;
	}
}
