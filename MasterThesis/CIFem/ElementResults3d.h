#pragma once
#include "CIFem_dll.h"
#include "IElementResults.h"


namespace CIFem
{
	class Element3d;
	class UtilCheck3dBasic;

	class CIFEM_API ElementResults3d : public IElementResults
	{
		friend class Element3d;
		friend class UtilCheck3dBasic;

		//Lists of results
		std::vector<double> _N, _Vy, _Vz, _T, _My, _Mz, _u, _v, _w, _fi, _pos;

		//List of utilisations
		std::vector<std::shared_ptr<Utilisation>> _util;

	public:
		ElementResults3d();
		~ElementResults3d();

		void Reset();
		std::vector<double> N() const { return _N; }
		std::vector<double> Vy() const { return _Vy; }
		std::vector<double> Vz() const { return _Vz; }
		std::vector<double> T() const { return _T; }
		std::vector<double> Myy() const { return _My; }
		std::vector<double> Mzz() const { return _Mz; }
		std::vector<std::shared_ptr<Utilisation>> Utilisations() const { return _util; }
	};
}