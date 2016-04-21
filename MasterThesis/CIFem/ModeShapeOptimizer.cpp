#include "ModeShapeOptimizer.h"

double CIFem::ModeShapeOptimizer::FindLowestUtilisation(int mode)
{
	double minUtil = 9e10;
	std::string modeName = "Mode " + std::to_string(mode);
	for (int i = 0; i < _structure->GetElements().size(); i++)
	{
		double util = _structure->GetElements()[i]->Utilisations(modeName).MaxUtil().GetUtil();
		if (util > 0 && util < minUtil)
		{
			minUtil = util;
		}
	}

	return minUtil;
}

void CIFem::ModeShapeOptimizer::ScaleElementSectionForces(int mode, double sFac)
{
	std::string modeName = "Mode " + std::to_string(mode);
	for (int i = 0; i < _structure->GetElements().size(); i++)
	{
		_structure->GetElements()[i]->ScaleResults(modeName, sFac);
	}
}

void CIFem::ModeShapeOptimizer::UpdateSectionCrossSection(int mode)
{
	std::string modeName = "Mode " + std::to_string(mode);
	for (int i = 0; i < _structure->GetElements().size(); i++)
	{
		_structure->GetElements()[i]->UpdateElement(modeName);
	}
}

void CIFem::ModeShapeOptimizer::SetElementToWorstState()
{
	for (int i = 0; i < _structure->GetElements().size(); i++)
	{
		_structure->GetElements()[i]->SetMaxState();
	}
}

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
	//Solve for initial eigenvalues
	_eigSolver.Solve();

	//Get the first (lowest) eigenvalue and the total number
	double firstEigVal = _eigSolver.EigenValues()[0];
	int nbVals = _eigSolver.EigenValues().size();

	//Initial setup values to use in iteration
	double ratio = 1;
	int n = 0;

	while (ratio < eigValRatio && n < nbVals)
	{
		//Calculate element forces and utilizations for a specific mode
		_eigSolver.SetResultsToMode(n);

		//Find the lowest max utilisation for the specific mode
		double minUtil = FindLowestUtilisation(n);

		//Scale factor to scale all loads with
		double sFac = 1 / minUtil * 1 / ratio;

		//Scale all element sectionforces and utilisations for the mode loadcase. Normalized to the lowest = 1;
		ScaleElementSectionForces(n, sFac);

		//Update crosssection-state to the lowest suitable
		UpdateSectionCrossSection(n);

		//Increase iterator
		n++;

		//Update ratio 
		ratio = _eigSolver.EigenValues()[n] / firstEigVal;
	}

	//Set elements to worst state
	SetElementToWorstState();

}
