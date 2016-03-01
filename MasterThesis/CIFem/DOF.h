#pragma once
#include "CIFem_dll.h"

namespace CIFem
{
	class CIFEM_API DOF
	{
		unsigned int _index;

	public:
		DOF();
		DOF(unsigned int);
		~DOF();

		int _kIndex;				// (Renumbered) index in K matrix
		double _f;
		bool _hasTransformedBC;		// Indicator to identify elements that has transformed bc (for C matrix calc)
		bool _hasSetTranslation;
		double _Am;					// Resulting translation in transformed dof direction

		// Results (maybe create results class? /C)
		double _resAs;				// Resulting translation in global dof direction
		double _resF;				// 

		int GetIndex();
	};
}

