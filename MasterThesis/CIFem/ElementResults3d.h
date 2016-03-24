#pragma once
#include "CIFem_dll.h"
#include "IElementResults.h"
#include <map>


typedef std::map<std::string, std::vector<double>> combResList;

namespace CIFem
{
	class Element3d;
	class UtilCheck3dBasic;

	class CIFEM_API ElementResults3d : public IElementResults
	{
		friend class Element3d;
		friend class UtilCheck3dBasic;

		//Lists of results
		combResList _N, _Vy, _Vz, _T, _My, _Mz, _u, _v, _w, _fi;
		std::vector<double> _pos;

		//List of utilisations
		std::map<std::string, std::vector<std::shared_ptr<Utilisation>>> _util;

		void SetUpLoadComb(std::string name);

	public:
		ElementResults3d();
		~ElementResults3d();

		void Reset();
		combResList N() const { return _N; }
		combResList Vy() const { return _Vy; }
		combResList Vz() const { return _Vz; }
		combResList T() const { return _T; }
		combResList Myy() const { return _My; }
		combResList Mzz() const { return _Mz; }
		std::map<std::string, std::vector<std::shared_ptr<Utilisation>>> Utilisations() const { return _util; }
	};
}