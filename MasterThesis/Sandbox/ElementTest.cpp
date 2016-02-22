#include "stdafx.h"
#include "ElementTest.h"
#include "XYZ.h"
#include "Element3d.h"
#include <iostream>
#include <vector>

using namespace std;

ElementTest::ElementTest()
{
}


ElementTest::~ElementTest()
{
}

void ElementTest::EdofTest()
{
	
	XYZ sNode(0, 0, 0);
	XYZ eNode(1, 1, 0);

	vector<int> edof;
	for (int i = 0; i < 12; i++)
	{
		edof.push_back(i);
	}
	
	ElementProperty ep;						// Placeholder empty element property
	Element3d e(sNode, eNode, edof, ep);

	// Print element dofs
	vector<int> dofs = e.GetDofs();
	cout << "Element dofs: ";
	for (int i = 0; i < dofs.size(); i++)
		cout << " " << i;

	cout << endl;

	cout << "Element test complete" << endl << endl << endl;
}



void ElementTest::StiffnessMatrixTest()
{

}
