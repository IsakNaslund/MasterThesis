#include "stdafx.h"
#include "WR_Utilisation.h"

using namespace CIFem_wrapper;

WR_Utilisation::WR_Utilisation(std::shared_ptr<CIFem::Utilisation> const utilisation)
{
	_utilisation = utilisation;
}
