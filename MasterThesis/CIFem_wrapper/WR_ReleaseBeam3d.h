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
		WR_ReleaseBeam3d(bool x, bool y, bool z, bool xx, bool yy, bool zz);
		WR_ReleaseBeam3d(double x, double y, double z, double xx, double yy, double zz);
		WR_ReleaseBeam3d(std::vector<bool> rels);
		WR_ReleaseBeam3d(std::vector<double> spRel);
		~WR_ReleaseBeam3d();

		CIFem::ReleaseBeam3d* GetRelease();
	};

}