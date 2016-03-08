#pragma once

#include "WR_IElement.h"
#include "WR_Vector.h"
#include "Element3d.h"
#include "m_shared_ptr.h"
#include "Utilities.h"

namespace CIFem_wrapper
{
	public ref class WR_Element3d : public WR_IElement
	{
		m_shared_ptr<CIFem::Element3d> _element;

	public:
		WR_Element3d();
		WR_Element3d(shared_ptr<CIFem::Element3d> const element);

		System::Collections::Generic::List<double> ^ NormalForce();
		System::Collections::Generic::List<double> ^ ShearForceZ();
		System::Collections::Generic::List<double> ^ ShearForceY();
		System::Collections::Generic::List<double> ^ MomentY();
		System::Collections::Generic::List<double> ^ MomentZ();
		System::Collections::Generic::List<double> ^ TorsionalForce();

		System::Collections::Generic::List<double> ^ DisplacementX();
		System::Collections::Generic::List<double> ^ DisplacementY();
		System::Collections::Generic::List<double> ^ DisplacementZ();
		System::Collections::Generic::List<double> ^ DisplacementTorsion();

		System::Collections::Generic::List<double> ^ ResultPosition();

		WR_XYZ ^ GetStartPos();
		WR_XYZ ^ GetEndPos();
		WR_Vector ^ GetElementNormal();
	};
}

