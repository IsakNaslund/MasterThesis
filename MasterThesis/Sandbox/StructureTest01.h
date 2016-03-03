#pragma once

# include <vector>
# include "Element3d.h"
# include "Structure.h"

class StructureTest01
{

public:
	StructureTest01();
	~StructureTest01();

	void RunTest();
	vector<std::shared_ptr<IElementRcp>> CreateElements(XYZ, XYZ, XYZ, XYZ);
	void AddRestraints(Structure&);
	void AddForces(Structure&);
	void Solve(Structure&);
	std::vector<double> GetResults(Structure&);
	void PrintResults(vector<double>);
};

