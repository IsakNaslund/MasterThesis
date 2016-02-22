#include "stdafx.h"
#include "StructureTest01.h"
#include "Structure3d.h"
#include "Element3d.h"
#include "IElement.h"
#include "DOF.h"
#include "XYZ.h"
#include <iostream>

using namespace CIFem;

StructureTest01::StructureTest01()
{
	
}


StructureTest01::~StructureTest01()
{
}

void StructureTest01::RunTest()
{
	// Create structure
	Structure3d testStructure;

	//Create elements
	vector<IElement*> elements = CreateElements();
	for (int i = 0; i < elements.size(); i++)
		testStructure.AddElement(elements[i]);

	AddRestraints(testStructure);
	
	AddForces(testStructure);

	Solve(testStructure);

	PrintResults(GetResults(testStructure));
}

std::vector<IElement*> StructureTest01::CreateElements()
{
	std::vector<IElement*> elements;

	// Nodes
	XYZ lb(0, 0, 0);
	XYZ lt(0, 1, 0);
	XYZ rt(1, 1, 0);
	XYZ rb(1, 0, 0);

	// Element property
	double E = 210;
	double G = 1;						// Change in case of 3d test
	double A = 0.20*0.10;
	double Iy = 0.20*0.20*0.20*0.10;
	double Iz = 0.10*0.10*0.10*0.20;
	double Kv = 1;						// Change in case of 3d test
	ElementProperty ep(E, G, A, Iy, Iz, Kv);

	// Elements
	vector<int> edof;
	for (int i = 1; i <= 12; i++)
		edof.push_back(i);
	Element3d lCol(lb, lt, edof, ep);

	edof.clear();
	for (int i = 7; i <= 18; i++)
		edof.push_back(i);
	Element3d tBeam(lt, rt, edof, ep);

	edof.clear();
	for (int i = 13; i <= 24; i++)
		edof.push_back(i);
	Element3d rCol(rt, rb, edof, ep);

	elements.push_back(&lCol);
	elements.push_back(&tBeam);
	elements.push_back(&rCol);

	return elements;
}

void StructureTest01::AddRestraints(Structure3d &structure)
{
	// Bottom left corner
	structure.SetTranslation(1, 0);
	structure.SetTranslation(2, 0);
	structure.SetTranslation(3, 0);
	structure.SetTranslation(4, 0);
	structure.SetTranslation(5, 0);
	structure.SetTranslation(6, 0);

	// Z dir in top corners
	structure.SetTranslation(9, 0);
	structure.SetTranslation(15, 0);

	// Bottom right corner
	structure.SetTranslation(19, 0);
	structure.SetTranslation(20, 0);
	structure.SetTranslation(21, 0);
	structure.SetTranslation(22, 0);
	structure.SetTranslation(23, 0);
	structure.SetTranslation(24, 0);
}

void StructureTest01::AddForces(Structure3d &structure)
{
	structure.ApplyForce(7, 1000);
}

void StructureTest01::Solve(Structure3d &structure)
{
	structure.Solve();
}

void StructureTest01::PrintResults(vector<double> a)
{
	cout << "Operation results:" << endl << endl;
	for (int i = 0; i < a.size(); i++)
	{
		cout << "DOF " << i << ": " << a[i] << endl;
	}
}

std::vector<double> StructureTest01::GetResults(Structure3d &structure)
{
	return structure.GetDisplacements();
}


