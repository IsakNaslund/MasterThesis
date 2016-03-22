#include "stdafx.h"
#include "WR_LoadCombination.h"

CIFem_wrapper::WR_LoadCombination::WR_LoadCombination(CIFem::LoadCombination comb)
{
	_loadComb = new CIFem::LoadCombination(comb);
}

CIFem_wrapper::WR_LoadCombination::WR_LoadCombination(System::String ^ name)
{
	_loadComb = new CIFem::LoadCombination(msclr::interop::marshal_as<std::string>(name));
}

CIFem_wrapper::WR_LoadCombination::WR_LoadCombination(System::String ^ name, WR_Vector ^ gravField)
{
	_loadComb = new CIFem::LoadCombination(msclr::interop::marshal_as<std::string>(name), gravField->GetAsVector3d());
}

CIFem_wrapper::WR_LoadCombination::WR_LoadCombination(System::String ^ name, bool gravityOn)
{
	_loadComb = new CIFem::LoadCombination(msclr::interop::marshal_as<std::string>(name), gravityOn);
}

CIFem_wrapper::WR_LoadCombination::~WR_LoadCombination()
{
	delete _loadComb;
	_loadComb = 0;
}

void CIFem_wrapper::WR_LoadCombination::AddPointLoad(WR_Vector ^ force, WR_Vector ^ moment, WR_XYZ^ pos)
{
	_loadComb->AddPointLoad(force->GetAsVector3d(), moment->GetAsVector3d(), *pos->GetPos());
}

void CIFem_wrapper::WR_LoadCombination::SetGravity(WR_Vector ^ gravField)
{
	_loadComb->SetGravity(gravField->GetAsVector3d());
}

void CIFem_wrapper::WR_LoadCombination::SetGravity(bool gravityOn)
{
	_loadComb->SetGravity(gravityOn);
}

CIFem_wrapper::WR_LoadCombination^ CIFem_wrapper::WR_LoadCombination::Copy()
{
	return gcnew WR_LoadCombination(*_loadComb);
}

LoadCombination CIFem_wrapper::WR_LoadCombination::GetCombination()
{
	return *_loadComb;
}
