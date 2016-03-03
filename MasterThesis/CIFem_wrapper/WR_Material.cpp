#include "stdafx.h"
#include "WR_Material.h"


CIFem_wrapper::WR_Material::WR_Material()
{
	_mat = gcnew m_shared_ptr<CIFem::Material>(new CIFem::Material());
}

CIFem_wrapper::WR_Material::WR_Material(double E, double poi, double rho)
{
	_mat = gcnew m_shared_ptr<CIFem::Material>(new CIFem::Material(E, poi, rho));
}

std::shared_ptr<CIFem::Material> CIFem_wrapper::WR_Material::GetMaterial()
{
	return _mat.operator std::shared_ptr<CIFem::Material>();
}

CIFem_wrapper::WR_Material^ CIFem_wrapper::WR_Material::Copy()
{
	return gcnew WR_Material(_mat.operator std::shared_ptr<CIFem::Material>()->E(), _mat.operator std::shared_ptr<CIFem::Material>()->Poisson(), _mat.operator std::shared_ptr<CIFem::Material>()->Rho());
}

System::String ^ CIFem_wrapper::WR_Material::ToString()
{

	System::String^ str = System::String::Format("E: {0}, Poi: {1}, G: {2}, Density: {3}", _mat.operator std::shared_ptr<CIFem::Material>()->E(), _mat.operator std::shared_ptr<CIFem::Material>()->Poisson(), _mat.operator std::shared_ptr<CIFem::Material>()->G(), _mat.operator std::shared_ptr<CIFem::Material>()->Rho());

	
	return str;
}
