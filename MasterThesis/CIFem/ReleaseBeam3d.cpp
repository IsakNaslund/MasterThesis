#include "ReleaseBeam3d.h"

CIFem::ReleaseBeam3d::ReleaseBeam3d()
{
	
}

CIFem::ReleaseBeam3d::ReleaseBeam3d(const ReleaseBeam3d * other)
{
	if(other != nullptr)
		SetReleases(other->GetReleases());
}

CIFem::ReleaseBeam3d::ReleaseBeam3d(bool x, bool y, bool z, bool xx, bool yy, bool zz)
{
	std::vector<DofRelease> rel;

	rel.push_back(DofRelease(x));
	rel.push_back(DofRelease(y));
	rel.push_back(DofRelease(z));
	rel.push_back(DofRelease(xx));
	rel.push_back(DofRelease(yy));
	rel.push_back(DofRelease(zz));

	SetReleases(rel);
}

CIFem::ReleaseBeam3d::ReleaseBeam3d(double x, double y, double z, double xx, double yy, double zz)
{
	std::vector<DofRelease> rel;

	rel.push_back(DofRelease(x));
	rel.push_back(DofRelease(y));
	rel.push_back(DofRelease(z));
	rel.push_back(DofRelease(xx));
	rel.push_back(DofRelease(yy));
	rel.push_back(DofRelease(zz));

	SetReleases(rel);
}

CIFem::ReleaseBeam3d::ReleaseBeam3d(std::vector<bool> rels)
{
	std::vector<DofRelease> rel;

	for (int i = 0; i < rels.size(); i++)
	{
		rel.push_back(DofRelease(rels[i]));
	}
	
	SetReleases(rel);
}

CIFem::ReleaseBeam3d::ReleaseBeam3d(std::vector<double> spRel)
{
	std::vector<DofRelease> rel;

	for (int i = 0; i < spRel.size(); i++)
	{
		rel.push_back(DofRelease(spRel[i]));
	}

	SetReleases(rel);
}

CIFem::ReleaseBeam3d::ReleaseBeam3d(std::vector<DofRelease> dofRel)
{
	SetReleases(dofRel);
}

CIFem::ReleaseBeam3d::~ReleaseBeam3d()
{
}

int CIFem::ReleaseBeam3d::GetNumberOfReleases()
{
	return 6;
}
