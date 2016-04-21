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

	public:
		ModeShapeOptimizer();
		ModeShapeOptimizer(std::shared_ptr<Structure> structure);
		~ModeShapeOptimizer();

		void Run(double eigValRatio);
		void Run() { Run(100); }

	};
}

