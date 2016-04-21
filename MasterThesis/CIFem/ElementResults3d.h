#pragma once
#include "CIFem_dll.h"
#include "IElementResults.h"
#include <map>
#include "UtilisationSet.h"


//typedef std::map<std::string, std::vector<double>> combResList;

namespace CIFem
{
	class Element3d;
	class UtilCheck3dBasic;

	class CIFEM_API ElementResults3d : public IElementResults
	{
		friend class Element3d;
		friend class Element3dChecks;

		//Lists of results
		combResList _N, _Vy, _Vz, _T, _My, _Mz, _u, _v, _w, _fi;
		std::vector<double> _pos;
		std::vector<std::string> _loadCases;

		//List of utilisations
		std::map<std::string, UtilisationSet> _util;

		//Maximum utilisation
		Utilisation _maxUtil;

		void SetUpLoadComb(std::string name);

		void CalcMaxUtil();

	public:
		ElementResults3d();
		~ElementResults3d();

		void Reset();
		combResList  N() const { return _N; }
		combResList  Vy() const { return _Vy; }
		combResList  Vz() const { return _Vz; }
		combResList  T() const { return _T; }
		combResList  Myy() const { return _My; }
		combResList  Mzz() const { return _Mz; }
		std::map<std::string, UtilisationSet> Utilisations() const { return _util; }

		void MaxMomentSection(double & my, double & mz);

	};
}