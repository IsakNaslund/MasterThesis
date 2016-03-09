#pragma once
#include "CIFem_dll.h"

namespace CIFem
{
	class CIFEM_API DOF
	{
		unsigned int _index;
		double _f;


		int _kIndex;				// (Renumbered) index in K matrix
		bool _hasTransformedBC;		// Indicator to identify elements that has transformed bc (for C matrix calc)
		bool _hasSetTranslation;
		double _Am;					// Resulting translation in transformed dof direction

									// Results (maybe create results class? /C)
		double _resAs;				// Resulting translation in global dof direction
		double _resF;				// 

	public:
		DOF();
		DOF(unsigned int);
		~DOF();

		inline void UpdateKIndex(int i) { _kIndex = i; }
		inline const int & GetKIndex() const { return _kIndex; }

		inline void AddLoad(const double load);
		inline double GetLoad() const { return _f; }
		inline void ClearLoad() { _f = 0; }


		void SetUpBoundaryCondition(bool isRestrained) { SetUpBoundaryCondition(isRestrained, 0); }
		void SetUpBoundaryCondition(bool isRestrained, double dist);

		inline bool HasSetTranslation() const { return _hasSetTranslation; }
		inline double GetTranslation() const { return _Am; }

		inline void SetTransformedBC(bool flag) { _hasTransformedBC = flag; }
		inline bool HasTransformedBc() { return _hasTransformedBC; }

		inline void SetResults(double a, double f);

		inline double GetResultingTranslation() const { return _resAs; }
		inline double GetResultingForce() const { return _resF; }

		int GetIndex();
	};
}

