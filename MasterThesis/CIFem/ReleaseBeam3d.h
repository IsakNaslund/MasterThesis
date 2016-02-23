#pragma once
#include "IRelease.h"
#include <vector>
#include "CIFem_dll.h"

namespace CIFem
{
	class CIFEM_API ReleaseBeam3d :
		public CIFem::IRelease
	{
	public:
		ReleaseBeam3d();
		~ReleaseBeam3d();

	protected:
		int GetNumberOfReleases();
	};
}

