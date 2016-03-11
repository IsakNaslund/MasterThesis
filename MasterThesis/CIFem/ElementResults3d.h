#pragma once
#include "CIFem_dll.h"
#include "IElementResults.h"


namespace CIFem
{
	class Element3d;

	class CIFEM_API ElementResults3d : public IElementResults
	{
		friend class Element3d;

		//Lists of results
		std::vector<double> _N, _Vy, _Vz, _T, _My, _Mz, _u, _v, _w, _fi, _pos;

	public:
		ElementResults3d();
		~ElementResults3d();

		void Reset();
		const std::vector<double> N() { return _N; }
		const std::vector<double> Vy() { return _Vy; }
		const std::vector<double> Vz() { return _Vz; }
		const std::vector<double> T() { return _T; }
		const std::vector<double> Myy() { return _My; }
		const std::vector<double> Mzz() { return _Mz; }
	};
}