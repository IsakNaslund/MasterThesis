#pragma once
#include "CIFem_dll.h"

namespace CIFem
{
	class CIFEM_API DOF
	{
		unsigned int _index;
		double _f;

	public:
		DOF();
		DOF(unsigned int);
		~DOF();

		int _kIndex;				// (Renumbered) index in K matrix
		bool _hasTransformedBC;		// Indicator to identify elements that has transformed bc (for C matrix calc)
		bool _hasSetTranslation;
		double _Am;					// Resulting translation in transformed dof direction

		// Results (maybe create results class? /C)
		double _resAs;				// Resulting translation in global dof direction
		double _resF;				// 

		void AddLoad(const double load);
		double GetLoad() const { return _f; }

		int GetIndex();
	};
}

