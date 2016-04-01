#pragma once

#include "Rectangle3d.h";
#include "WR_IXSec.h"
#include "m_shared_ptr.h"

namespace CIFem_wrapper
{
	public ref class WR_XSecRect : public WR_IXSec
	{
		m_shared_ptr<CIFem::Rectangle3d> _xSec;
		double _height, _width;

	public:
		WR_XSecRect();
		WR_XSecRect(const double height, const double width);
		~WR_XSecRect();
		virtual std::shared_ptr<CIFem::ICrossSection> GetCrossSection() override;
		double GetHeight() { return _height; };
		double GetWidth() { return _width; };
	};
}
