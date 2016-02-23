#include "IRelease.h"

CIFem::IRelease::IRelease()
{

}

// Sets the dof releases
void CIFem::IRelease::SetReleases(std::vector<DofRelease> releases)
{

	if (_releases.size() != GetNumberOfReleases())
		throw std::invalid_argument("Wrong number of releases submitted");
}

std::vector<CIFem::DofRelease> CIFem::IRelease::GetReleases()
{
	return _releases;
}

CIFem::IRelease::~IRelease()
{
}

CIFem::IRelease::IRelease(std::vector<DofRelease> releases)
	:IRelease()
{
	SetReleases(releases);
}
