#include "ReleaseBeam3d.h"

CIFem::ReleaseBeam3d::ReleaseBeam3d(std::vector<DofRelease> releases)
{
	SetReleases(releases);
}

CIFem::ReleaseBeam3d::~ReleaseBeam3d()
{
}

void CIFem::ReleaseBeam3d::SetNumberOfReleases()
{
	_nReleases = 6;
}
