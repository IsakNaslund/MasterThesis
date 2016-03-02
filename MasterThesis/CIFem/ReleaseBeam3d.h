#pragma once
#include "IRelease.h"
#include <vector>
#include "CIFem_dll.h"
#include <memory>

namespace CIFem
{
	class CIFEM_API ReleaseBeam3d :
		public CIFem::IRelease
	{
	public:
		ReleaseBeam3d();
		ReleaseBeam3d(const std::shared_ptr<ReleaseBeam3d> other);
		ReleaseBeam3d(bool x, bool y, bool z, bool xx, bool yy, bool zz);
		ReleaseBeam3d(double x, double y, double z, double xx, double yy, double zz);
		ReleaseBeam3d(std::vector<bool> rels);
		ReleaseBeam3d(std::vector<double> spRel);
		ReleaseBeam3d(std::vector<DofRelease> dofRel);

		~ReleaseBeam3d();

	protected:
		int GetNumberOfReleases();
	};
}

