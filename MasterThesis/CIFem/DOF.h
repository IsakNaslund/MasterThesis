#pragma once
#include "CIFem_dll.h"

namespace CIFem
{
	class CIFEM_API DOF
	{
		unsigned int _index;
		double _a;
		bool _hasSetTranslation;

	public:
		DOF();
		DOF(unsigned int);
		~DOF();

		int _kIndex;					// (Renumbered) index in K matrix
		double _f;

		// Results (maybe create results class? /C)
		double _resA;
		double _resF;

		bool HasSetTranslation();
		double GetTranslation();
		int GetIndex();
		void SetTranslation(double);
	};
}

