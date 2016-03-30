#pragma once
#include "m_shared_ptr.h"
#include "RHS3d.h"
#include "WR_IXSec.h"

namespace CIFem_wrapper
{
	public ref class WR_XSecRHS : public WR_IXSec
	{
		m_shared_ptr<CIFem::RHS3d> _xSec;
	public:
		WR_XSecRHS();
		WR_XSecRHS(double height, double width, double thickness);

		virtual std::shared_ptr<CIFem::ICrossSection> GetCrossSection() override;
		virtual System::String^ ToString() override;
	};
}

