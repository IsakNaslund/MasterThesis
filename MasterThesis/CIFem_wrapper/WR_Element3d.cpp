#include "stdafx.h"
#include "WR_Element3d.h"
#include <msclr\marshal_cppstd.h>

namespace CIFem_wrapper
{

	CIFem_wrapper::WR_Element3d::WR_Element3d()
	{
		// do nothing
	}

	CIFem_wrapper::WR_Element3d::WR_Element3d(shared_ptr<CIFem::Element3d> const element)
	{
		_element = element;
	}

	/*System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::NormalForce(System::String^ res)
	{
		return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->NormalForce(
			_element.operator std::shared_ptr<CIFem::Element3d>()->GetResult(msclr::interop::marshal_as<std::string>(res))));
	}

	System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::ShearForceZ(System::String^ res)
	{
		return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->ShearForceZ(
			_element.operator std::shared_ptr<CIFem::Element3d>()->GetResult(msclr::interop::marshal_as<std::string>(res))));
	}

	System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::ShearForceY(System::String^ res)
	{
		return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->ShearForceY(
			_element.operator std::shared_ptr<CIFem::Element3d>()->GetResult(msclr::interop::marshal_as<std::string>(res))));
	}

	System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::MomentY(System::String^ res)
	{
		return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->MomentY(
			_element.operator std::shared_ptr<CIFem::Element3d>()->GetResult(msclr::interop::marshal_as<std::string>(res))));
	}

	System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::MomentZ(System::String^ res)
	{
		return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->MomentZ(
			_element.operator std::shared_ptr<CIFem::Element3d>()->GetResult(msclr::interop::marshal_as<std::string>(res))));
	}

	System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::TorsionalForce(System::String^ res)
	{
		return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->TorsionalForce(
			_element.operator std::shared_ptr<CIFem::Element3d>()->GetResult(msclr::interop::marshal_as<std::string>(res))));
	}

	System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::DisplacementX(System::String^ res)
	{
		return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->DisplacementX(
			_element.operator std::shared_ptr<CIFem::Element3d>()->GetResult(msclr::interop::marshal_as<std::string>(res))));
	}

	System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::DisplacementY(System::String^ res)
	{
		return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->DisplacementY(
			_element.operator std::shared_ptr<CIFem::Element3d>()->GetResult(msclr::interop::marshal_as<std::string>(res))));
	}

	System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::DisplacementZ(System::String^ res)
	{
		return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->DisplacementZ(
			_element.operator std::shared_ptr<CIFem::Element3d>()->GetResult(msclr::interop::marshal_as<std::string>(res))));
	}

	System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::DisplacementTorsion(System::String^ res)
	{
		return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->DisplacementTorsion(
			_element.operator std::shared_ptr<CIFem::Element3d>()->GetResult(msclr::interop::marshal_as<std::string>(res))));
	}



	System::Collections::Generic::List<WR_Utilisation^>^ WR_Element3d::Utilisations(System::String^ res)
	{
		return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->Utilisations(
			_element.operator std::shared_ptr<CIFem::Element3d>()->GetResult(msclr::interop::marshal_as<std::string>(res))));
	}*/

	System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::ResultPosition()
	{
		return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->ResultPosition());
	}

	ResultDictionary ^ WR_Element3d::AllNormalForce()
	{
		return Utilities::MapToDictionary(_element.operator std::shared_ptr<CIFem::Element3d>()->AllNormalForce());
	}

	ResultDictionary ^ WR_Element3d::AllShearForceZ()
	{
		return Utilities::MapToDictionary(_element.operator std::shared_ptr<CIFem::Element3d>()->AllShearForceZ());
	}

	ResultDictionary ^ WR_Element3d::AllShearForceY()
	{
		return Utilities::MapToDictionary(_element.operator std::shared_ptr<CIFem::Element3d>()->AllShearForceY());
	}

	ResultDictionary ^ WR_Element3d::AllMomentY()
	{
		return Utilities::MapToDictionary(_element.operator std::shared_ptr<CIFem::Element3d>()->AllMomentY());
	}

	ResultDictionary ^ WR_Element3d::AllMomentZ()
	{
		return Utilities::MapToDictionary(_element.operator std::shared_ptr<CIFem::Element3d>()->AllMomentZ());
	}

	ResultDictionary ^ WR_Element3d::AllTorsionalForce()
	{
		return Utilities::MapToDictionary(_element.operator std::shared_ptr<CIFem::Element3d>()->AllTorsionalForce());
	}

	ResultDictionary ^ WR_Element3d::AllDisplacementX()
	{
		return Utilities::MapToDictionary(_element.operator std::shared_ptr<CIFem::Element3d>()->AllDisplacementX());
	}

	ResultDictionary ^ WR_Element3d::AllDisplacementY()
	{
		return Utilities::MapToDictionary(_element.operator std::shared_ptr<CIFem::Element3d>()->AllDisplacementY());
	}

	ResultDictionary ^ WR_Element3d::AllDisplacementZ()
	{
		return Utilities::MapToDictionary(_element.operator std::shared_ptr<CIFem::Element3d>()->AllDisplacementZ());
	}

	ResultDictionary ^ WR_Element3d::AllDisplacementTorsion()
	{
		return Utilities::MapToDictionary(_element.operator std::shared_ptr<CIFem::Element3d>()->AllDisplacementTorsion());
	}

	UtilDictionary ^ WR_Element3d::AllUtilisations()
	{
		return Utilities::MapToDictionary(_element.operator std::shared_ptr<CIFem::Element3d>()->AllUtilisation());
	}


	WR_XYZ ^ CIFem_wrapper::WR_Element3d::GetStartPos()
	{
		XYZ sPos = _element.get()->StartPosition();
		return gcnew WR_XYZ(sPos.GetX(), sPos.GetY(), sPos.GetZ());
	}

	WR_XYZ ^ WR_Element3d::GetEndPos()
	{
		XYZ ePos = _element.get()->EndPosition();
		return gcnew WR_XYZ(ePos.GetX(), ePos.GetY(), ePos.GetZ());
	}

	WR_Vector ^ WR_Element3d::GetElementNormal()
	{
		CIFem::Vector3d v = _element.operator std::shared_ptr<CIFem::Element3d>()->Orientation();
		return gcnew WR_Vector(v.GetX(), v.GetY(), v.GetZ());
	}

	System::String ^ WR_Element3d::GetSectionString()
	{
		return Utilities::ConvertToSystemString(_element.operator std::shared_ptr<CIFem::Element3d>()->GetCrossSection()->ToString());
	}

}