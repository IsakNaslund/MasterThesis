#pragma once
#include "IRelease.h"
#include <vector>

namespace CIFem
{
	class ReleaseBeam2d :
		public CIFem::IRelease
	{
	public:
		~ReleaseBeam2d();

	protected:
		int GetNumberOfReleases();
	};
}

