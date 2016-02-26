#include "IRelease.h"

CIFem::IRelease::IRelease()
{
	/*
	for (int i = 0; i < GetNumberOfReleases(); i++)
	{
		_releases.push_back(DofRelease(true));
	}*/
}


// Sets the dof releases
void CIFem::IRelease::SetReleases(const std::vector<DofRelease> releases)
{
	int size = releases.size();
	if (size != GetNumberOfReleases())
		throw std::invalid_argument("Wrong number of releases submitted");
	else
	_releases = releases;
}

std::vector<CIFem::DofRelease> CIFem::IRelease::GetReleases() const
{
	return _releases;
}

CIFem::IRelease::~IRelease()
{
	_releases.clear();

}

