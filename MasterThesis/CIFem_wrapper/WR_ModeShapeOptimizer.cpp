#include "stdafx.h"
#include "WR_ModeShapeOptimizer.h"


CIFem_wrapper::WR_ModeShapeOptimizer::WR_ModeShapeOptimizer()
{
}

CIFem_wrapper::WR_ModeShapeOptimizer::WR_ModeShapeOptimizer(WR_Structure ^ structure)
{
	_optimizer = new CIFem::ModeShapeOptimizer(structure->GetStructure());
}

CIFem_wrapper::WR_ModeShapeOptimizer::~WR_ModeShapeOptimizer()
{
	delete _optimizer;
	_optimizer = 0;
}

void CIFem_wrapper::WR_ModeShapeOptimizer::Run()
{
	_optimizer->Run();
}

void CIFem_wrapper::WR_ModeShapeOptimizer::Run(double maxRatio)
{
	_optimizer->Run(maxRatio);
}

void CIFem_wrapper::WR_ModeShapeOptimizer::Run(System::Collections::Generic::List<int>^ modes)
{
	_optimizer->Run(Utilities::GetSetFromList(modes));
}
