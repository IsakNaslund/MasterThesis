#pragma once
#include "CIFem_dll.h"
#include <vector>
#include "DofRelease.h"

namespace CIFem
{
	class CIFEM_API IRelease
	{
	public:
		~IRelease();
		IRelease(std::vector<DofRelease>);

	protected:
		void SetReleases(std::vector<DofRelease>);
		virtual void SetNumberOfReleases() = 0;		// Sets number of releases, used in order to avoid coding errors
		int _nReleases;								// Number of releases

	private:
		IRelease();
		std::vector<DofRelease> _releases;
	};
}
