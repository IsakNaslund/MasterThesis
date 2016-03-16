#pragma once
#include <memory>
#include "m_shared_ptr.h"
#include "Utilisation.h"


namespace CIFem_wrapper
{
	public ref class WR_Utilisation
	{
		m_shared_ptr<CIFem::Utilisation> _utilisation;

	public:
		WR_Utilisation(std::shared_ptr<CIFem::Utilisation> const utilisation);
	};
}
