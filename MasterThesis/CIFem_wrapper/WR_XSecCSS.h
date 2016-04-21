#pragma once
#include "m_shared_ptr.h"
#include "CircularSolid3d.h"
#include "WR_IXSec.h"

namespace CIFem_wrapper
{
	public ref class WR_XSecCSS : public WR_IXSec
	{
		m_shared_ptr<CIFem::CircularSolid3d> _xSec;
		double _radius;

	public:
		WR_XSecCSS();
		WR_XSecCSS(double radius);

		virtual std::shared_ptr<CIFem::ICrossSection> GetCrossSection() override;
		double GetRadius() { return _radius; };
	};

}
