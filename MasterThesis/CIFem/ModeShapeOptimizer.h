#pragma once
#include "CIFem_dll.h"
#include "Structure3d.h"
#include "EigenSolver.h"
#include <memory>

namespace CIFem
{

	class CIFEM_API ModeShapeOptimizer
	{
		std::shared_ptr<Structure> _structure;
		EigenSolver _eigSolver;


		double FindLowestUtilisation(int mode);
		//Scale all element sectionforces and utilisations for the mode loadcase. Normalized to the lowest = 1;
		void ScaleElementSectionForces(int mode, double sFac);
		//Update crosssection-state to the lowest suitable
		void UpdateSectionCrossSection(int mode);

		//Set elements to worst state
		void SetElementToWorstState();

	public:
		ModeShapeOptimizer();
		ModeShapeOptimizer(std::shared_ptr<Structure> structure);
		~ModeShapeOptimizer();

		void Run(double eigValRatio);
		void Run() { Run(10); }
		void Run(std::set<int> modes);

	};
}

