#pragma once
#include "ICrossSection.h"
#include "m_shared_ptr.h"
#include "Utilities.h"

namespace CIFem_wrapper
{

	public ref class WR_IXSec
	{
	public:
		virtual std::shared_ptr<CIFem::ICrossSection> GetCrossSection() = 0;
		virtual System::String^ ToString() override;


		property double Area {virtual double get() { return GetCrossSection()->GetArea(); }}
		property double Iy {virtual double get() { return GetCrossSection()->GetIy(); }}
		property double Iz {virtual double get() { return GetCrossSection()->GetIz(); }}
		property double Kv {virtual double get() { return GetCrossSection()->GetKv(); }}
	};

}