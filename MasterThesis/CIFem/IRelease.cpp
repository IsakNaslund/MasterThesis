#include "IRelease.h"

CIFem::IRelease::IRelease()
{
	_nReleases = -1;		// Should be overridden in subclass method SetNumberOfReleases();
}

// Sets the dof releases
void CIFem::IRelease::SetReleases(std::vector<DofRelease> releases)
{
	SetNumberOfReleases();

	if (_releases.size() != _nReleases)
		throw std::invalid_argument("Wrong number of releases submitted");
}

CIFem::IRelease::~IRelease()
{
}
