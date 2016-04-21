#pragma once
#include "m_shared_ptr.h"
#include "CHS3d.h"
#include "WR_IXSec.h"

namespace CIFem_wrapper
{
	public ref class WR_XSecCHS : public WR_IXSec
	{
		m_shared_ptr<CIFem::CHS3d> _xSec;
		double _radius, _thickness;

	public:
		WR_XSecCHS();
		WR_XSecCHS(double radius, double thickness);

		virtual std::shared_ptr<CIFem::ICrossSection> GetCrossSection() override;
		double GetRadius() { return _radius; };
		double GetThickness() { return _thickness; };
	};
}

