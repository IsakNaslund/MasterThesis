#pragma once

# include <vector>
# include "Element3d.h"
# include "Structure3d.h"

class StructureTest01
{

public:
	StructureTest01();
	~StructureTest01();

	void RunTest();
	std::vector<Element3d> CreateElements();
	void AddRestraints(Structure3d&);
	void AddForces(Structure3d&);
	void Solve(Structure3d&);
	std::vector<double> GetResults(Structure3d&);
	void PrintResults(vector<double>);
};

