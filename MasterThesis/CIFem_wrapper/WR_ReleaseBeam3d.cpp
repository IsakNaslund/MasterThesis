#include "stdafx.h"
#include "WR_ReleaseBeam3d.h"

using namespace CIFem_wrapper;

WR_ReleaseBeam3d::WR_ReleaseBeam3d()
{
	_release = gcnew m_shared_ptr<CIFem::ReleaseBeam3d>(new CIFem::ReleaseBeam3d());
}

WR_ReleaseBeam3d::WR_ReleaseBeam3d(CIFem::ReleaseBeam3d release)
{
	_release = gcnew m_shared_ptr<CIFem::ReleaseBeam3d>(&release);
}

WR_ReleaseBeam3d::WR_ReleaseBeam3d(bool x, bool y, bool z, bool xx, bool yy, bool zz)
{
	_release = gcnew m_shared_ptr<CIFem::ReleaseBeam3d>(new CIFem::ReleaseBeam3d(x, y, z, xx, yy, zz));
}

WR_ReleaseBeam3d::WR_ReleaseBeam3d(double x, double y, double z, double xx, double yy, double zz)
{
	_release = gcnew m_shared_ptr<CIFem::ReleaseBeam3d>(new CIFem::ReleaseBeam3d(x, y, z, xx, yy, zz));
}

WR_ReleaseBeam3d::WR_ReleaseBeam3d(std::vector<bool> rels)
{
	_release = gcnew m_shared_ptr<CIFem::ReleaseBeam3d>(new CIFem::ReleaseBeam3d(rels));
}

WR_ReleaseBeam3d::WR_ReleaseBeam3d(std::vector<double> rels)
{
	_release = gcnew m_shared_ptr<CIFem::ReleaseBeam3d>(new CIFem::ReleaseBeam3d(rels));
}

WR_ReleaseBeam3d::~WR_ReleaseBeam3d()
{

}

WR_ReleaseBeam3d ^ CIFem_wrapper::WR_ReleaseBeam3d::Copy()
{
	return gcnew WR_ReleaseBeam3d(CIFem::ReleaseBeam3d(*_release.share()));
}

/*System::String ^ CIFem_wrapper::WR_ReleaseBeam3d::ToString()
{
	throw gcnew System::NotImplementedException();
	// TODO: insert return statement here
}*/

System::String ^ CIFem_wrapper::WR_ReleaseBeam3d::ToString()
{
	std::vector<CIFem::DofRelease> rels = _release.get()->GetReleases();

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

std::shared_ptr<CIFem::ReleaseBeam3d>  WR_ReleaseBeam3d::GetRelease()
{
	return _release.operator std::shared_ptr<CIFem::ReleaseBeam3d>();
}


std::vector<CIFem::DofRelease> CIFem_wrapper::WR_ReleaseBeam3d::GetReleases()
{
	return _release.operator std::shared_ptr<CIFem::ReleaseBeam3d>()->GetReleases();
}

CIFem::DofRelease CIFem_wrapper::WR_ReleaseBeam3d::GetReleaseFromIndex(int i)
{
	std::vector<CIFem::DofRelease> rels = GetReleases();

	try
	{
		return rels[i];
	}
	catch (const std::out_of_range&)
	{
		std::string s = "Release not set, index out of range.";
		std::exception e(s.c_str());
		throw e;
	}
}


// Returns a stiffness based on an index. Returns true if fixed, false if not
double CIFem_wrapper::WR_ReleaseBeam3d::GetReleaseStiffness(int i)
{
	CIFem::DofRelease rel = GetReleaseFromIndex(i);

	// Set stiffness
	if (rel.IsFixed())
	{
		return -1;
	}

	return rel.Stiffness();
}
