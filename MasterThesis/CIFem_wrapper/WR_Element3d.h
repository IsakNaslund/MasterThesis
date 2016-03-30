#pragma once

#include "WR_IElement.h"
#include "WR_Vector.h"
#include "Element3d.h"
#include "m_shared_ptr.h"
#include "Utilities.h"
#include "WR_Utilisation.h"

typedef System::Collections::Generic::Dictionary<System::String^, System::Collections::Generic::List<double> ^> ResultDictionary;
typedef System::Collections::Generic::Dictionary<System::String^, System::Collections::Generic::List<CIFem_wrapper::WR_Utilisation^> ^> UtilDictionary;

namespace CIFem_wrapper
{
	public ref class WR_Element3d : public WR_IElement
	{
		m_shared_ptr<CIFem::Element3d> _element;

	public:
		WR_Element3d();
		WR_Element3d(shared_ptr<CIFem::Element3d> const element);

		/*System::Collections::Generic::List<double> ^ NormalForce(System::String^ res);
		System::Collections::Generic::List<double> ^ ShearForceZ(System::String^ res);
		System::Collections::Generic::List<double> ^ ShearForceY(System::String^ res);
		System::Collections::Generic::List<double> ^ MomentY(System::String^ res);
		System::Collections::Generic::List<double> ^ MomentZ(System::String^ res);
		System::Collections::Generic::List<double> ^ TorsionalForce(System::String^ res);

		System::Collections::Generic::List<double> ^ DisplacementX(System::String^ res);
		System::Collections::Generic::List<double> ^ DisplacementY(System::String^ res);
		System::Collections::Generic::List<double> ^ DisplacementZ(System::String^ res);
		System::Collections::Generic::List<double> ^ DisplacementTorsion(System::String^ res);*/

		System::Collections::Generic::List<double> ^ ResultPosition();

		//System::Collections::Generic::List<WR_Utilisation^> ^ Utilisations(System::String^ res);

		ResultDictionary ^ AllNormalForce();
		ResultDictionary ^ AllShearForceZ();
		ResultDictionary ^ AllShearForceY();
		ResultDictionary ^ AllMomentY();
		ResultDictionary ^ AllMomentZ();
		ResultDictionary ^ AllTorsionalForce();

		ResultDictionary ^ AllDisplacementX();
		ResultDictionary ^ AllDisplacementY();
		ResultDictionary ^ AllDisplacementZ();
		ResultDictionary ^ AllDisplacementTorsion();

		UtilDictionary ^ AllUtilisations();

		WR_XYZ ^ GetStartPos();
		WR_XYZ ^ GetEndPos();
		WR_Vector ^ GetElementNormal();
	};
}

