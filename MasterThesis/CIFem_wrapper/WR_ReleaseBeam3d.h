#pragma once
#include "ReleaseBeam3d.h"

namespace CIFem_wrapper
{

	public ref class WR_ReleaseBeam3d
	{
		CIFem::ReleaseBeam3d* _release;

	public:
		WR_ReleaseBeam3d();
		WR_ReleaseBeam3d(CIFem::ReleaseBeam3d _release);
		WR_ReleaseBeam3d(const bool x, const bool y, const bool z, const bool xx, const bool yy, const bool zz);
		WR_ReleaseBeam3d(const double x, const double y, const double z, const double xx, const double yy, const double zz);
		WR_ReleaseBeam3d(std::vector<bool> rels);
		WR_ReleaseBeam3d(std::vector<double> spRel);
		~WR_ReleaseBeam3d();

		CIFem::ReleaseBeam3d* GetRelease();
	};

}