#pragma once

#include "CIFem_dll.h"
#include "DOF.h"
#include "Element3d.h"
#include <vector>

using namespace std;

namespace CIFem
{
	class CIFEM_API Structure3d
	{
		vector<DOF> _dofs;				// Degrees of freedom containing boundary conditions and applied forces
		vector<IElement*> _elements;		// List of elements in structure
		int _maxDof;					// Highest dof of any element

	public:
		Structure3d();
		~Structure3d();
		void AddElement(IElement *);
		void ApplyForce(int, double);
		void SetTranslation(int, double);
		void Solve();
		vector<double> GetDisplacements();	// For debugging purposes, make available in a better way later /C

	private:
		DOF & FindDof(int);		// Finds a dof from an index (by reference)
		arma::mat AssembleStiffnessMatrix();
		

	};
}

