#include "stdafx.h"
#include "WR_ReleaseBeam3d.h"


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

CIFem::ReleaseBeam3d*  WR_ReleaseBeam3d::GetRelease()
{
	return _release;
}
