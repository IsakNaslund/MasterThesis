#include "ModeShapeOptimizer.h"

CIFem::ModeShapeOptimizer::ModeShapeOptimizer()
{
}

CIFem::ModeShapeOptimizer::ModeShapeOptimizer(std::shared_ptr<Structure> structure)
{
	_structure = structure;
	_eigSolver = EigenSolver(_structure);
}

CIFem::ModeShapeOptimizer::~ModeShapeOptimizer()
{
}

void CIFem::ModeShapeOptimizer::Run(double eigValRatio)
{
}
