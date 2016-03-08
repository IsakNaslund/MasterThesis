#include "stdafx.h"
#include "WR_Element3d.h"

CIFem_wrapper::WR_Element3d::WR_Element3d()
{
	// do nothing
}

CIFem_wrapper::WR_Element3d::WR_Element3d(shared_ptr<CIFem::Element3d> const element)
{
	_element = element;
}

System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::NormalForce()
{
	return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->NormalForce());
}

System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::ShearForceZ()
{
	return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->ShearForceZ());
}

System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::ShearForceY()
{
	return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->ShearForceY());
}

System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::MomentY()
{
	return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->MomentY());
}

System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::MomentZ()
{
	return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->MomentZ());
}

System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::TorsionalForce()
{
	return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->TorsionalForce());
}

System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::DisplacementX()
{
	return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->DisplacementX());
}

System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::DisplacementY()
{
	return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->DisplacementY());
}

System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::DisplacementZ()
{
	return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->DisplacementZ());
}

System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::DisplacementTorsion()
{
	return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->DisplacementTorsion());
}

System::Collections::Generic::List<double>^ CIFem_wrapper::WR_Element3d::ResultPosition()
{
	return Utilities::GetListFromVector(_element.operator std::shared_ptr<CIFem::Element3d>()->ResultPosition());
}

