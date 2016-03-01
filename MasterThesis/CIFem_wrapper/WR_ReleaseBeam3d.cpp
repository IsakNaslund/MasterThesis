#include "stdafx.h"
#include "WR_ReleaseBeam3d.h"

using namespace CIFem_wrapper;

WR_ReleaseBeam3d::WR_ReleaseBeam3d()
{
	_release = new CIFem::ReleaseBeam3d();
}

WR_ReleaseBeam3d::WR_ReleaseBeam3d(CIFem::ReleaseBeam3d release)
{
	_release = &release;
}

WR_ReleaseBeam3d::WR_ReleaseBeam3d(bool x, bool y, bool z, bool xx, bool yy, bool zz)
{
	_release = new CIFem::ReleaseBeam3d(x, y, z, xx, yy, zz);
}

WR_ReleaseBeam3d::WR_ReleaseBeam3d(double x, double y, double z, double xx, double yy, double zz)
{
	_release = new CIFem::ReleaseBeam3d(x, y, z, xx, yy, zz);
}

WR_ReleaseBeam3d::WR_ReleaseBeam3d(std::vector<bool> rels)
{
	_release = new CIFem::ReleaseBeam3d(rels);
}

WR_ReleaseBeam3d::WR_ReleaseBeam3d(std::vector<double> rels)
{
	_release = new CIFem::ReleaseBeam3d(rels);
}

WR_ReleaseBeam3d::~WR_ReleaseBeam3d()
{
	delete _release;
	_release = 0;
}

WR_ReleaseBeam3d ^ CIFem_wrapper::WR_ReleaseBeam3d::Copy()
{
	return gcnew WR_ReleaseBeam3d(new CIFem::ReleaseBeam3d(_release));
}

/*System::String ^ CIFem_wrapper::WR_ReleaseBeam3d::ToString()
{
	throw gcnew System::NotImplementedException();
	// TODO: insert return statement here
}*/

System::String ^ CIFem_wrapper::WR_ReleaseBeam3d::ToString()
{
	std::vector<CIFem::DofRelease> rels = _release->GetReleases();

	System::String^ str = gcnew System::String("");

	for (int i = 0; i < rels.size(); i++)
	{
		if (rels[i].IsFixed())
			str += gcnew System::String("f");
		else if(rels[i].Stiffness() > 0)
			str += gcnew System::String("s");
		else
			str += gcnew System::String("r");
	}
	return str;
	
}

CIFem::ReleaseBeam3d*  WR_ReleaseBeam3d::GetRelease()
{
	return _release;
}
