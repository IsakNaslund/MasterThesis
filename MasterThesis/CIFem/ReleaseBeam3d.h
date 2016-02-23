#pragma once
#include "IRelease.h"
#include <vector>

namespace CIFem
{
	class ReleaseBeam3d :
		public CIFem::IRelease
	{
	public:
		~ReleaseBeam3d();

	protected:
		void SetNumberOfReleases();
	};
}

