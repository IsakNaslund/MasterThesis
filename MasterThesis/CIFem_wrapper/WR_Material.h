#pragma once

#include "Material.h"
#include "m_shared_ptr.h"


namespace CIFem_wrapper
{

	public ref class WR_Material
	{
		m_shared_ptr<CIFem::Material> _mat;


	public:
		WR_Material();
		WR_Material(double E, double poi, double rho);

		std::shared_ptr<CIFem::Material> GetMaterial();

		WR_Material ^ Copy();

		System::String^ ToString() override;
	};
}

