#include "stdafx.h"
#include "WR_Utilisation.h"

using namespace CIFem_wrapper;

CIFem_wrapper::WR_Utilisation::WR_Utilisation()
{
	std::shared_ptr<CIFem::Utilisation> u(new CIFem::Utilisation());
	_utilisation = u;
}

WR_Utilisation::WR_Utilisation(std::shared_ptr<CIFem::Utilisation> const utilisation)
{
	_utilisation = utilisation;
}

WR_Utilisation ^ CIFem_wrapper::WR_Utilisation::Copy()
{
	return gcnew WR_Utilisation(_utilisation.operator std::shared_ptr<CIFem::Utilisation>()->Copy());
}

System::String ^ CIFem_wrapper::WR_Utilisation::ToString()
{
	System::String ^ sysStr = msclr::interop::marshal_as<System::String ^>(_utilisation.operator std::shared_ptr<CIFem::Utilisation>()->GetDesc());
	return sysStr;
}

double CIFem_wrapper::WR_Utilisation::GetUtilisationDegree()
{
	return _utilisation.operator std::shared_ptr<CIFem::Utilisation>()->GetUtil();
}
	
