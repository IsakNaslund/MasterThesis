#pragma once

#include "WR_IElement.h"
#include "Element3d.h"
#include "m_shared_ptr.h"

namespace CIFem_wrapper
{
	ref class WR_Element3d : public WR_IElement
	{
		m_shared_ptr<CIFem::Element3d> _element;

	public:
		WR_Element3d();
		
	};
}

