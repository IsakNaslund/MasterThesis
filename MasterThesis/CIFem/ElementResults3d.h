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

		//Utilisation
		double _maxUtil = 0;	// Initialise to 0

	public:
		ElementResults3d();
		~ElementResults3d();

		void Reset();

	};
}