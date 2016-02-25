#include "stdafx.h"
#include "StructureTest01.h"
#include "Structure.h"
#include "Element3d.h"
#include "IElement.h"
#include "DOF.h"
#include "XYZ.h"
#include "Node3d.h"
#include <iostream>
#include "Rectangle3d.h"
#include "ReleaseBeam3d.h"
#include "Element3dRcp.h"

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
	Structure testStructure;

	// Coordinates
	XYZ lb(0, 0, 0);
	XYZ lt(0, 1, 0);
	XYZ rt(1, 1, 0);
	XYZ rb(1, 0, 0);

	// Nodes
	Node3d nLB(lb);
	Node3d nLT(lt);
	Node3d nRT(rt);
	Node3d nRB(rb);

	testStructure.AddNode(&nLB);
	testStructure.AddNode(&nLT);
	testStructure.AddNode(&nRT);
	testStructure.AddNode(&nRB);

	//Create elements
	vector<IElementRcp*> elements = CreateElements(lb, lt, rt, rb);
	for (int i = 0; i < elements.size(); i++)
		testStructure.AddElementRcp(elements[i]);
	
	//AddForces(testStructure);

	Solve(testStructure);

	//PrintResults(GetResults(testStructure));
}

std::vector<IElementRcp*> StructureTest01::CreateElements(XYZ lb, XYZ lt, XYZ rt, XYZ rb)
{
	std::vector<IElementRcp*> elements;

	// Element property
	double E = 210;
	double G = 1;						// Change in case of 3d test
	double A = 0.20*0.10;
	double Iy = 0.20*0.20*0.20*0.10;
	double Iz = 0.10*0.10*0.10*0.20;
	double Kv = 1;						// Change in case of 3d test
	ElementProperty ep(E, G, A, Iy, Iz, Kv);


	// Elements
	ReleaseBeam3d relFixed(true, true, true, true, true, true);
	Rectangle3d * pXSec = new Rectangle3d(0.20, 0.10);
	//std::shared_ptr<DOF> ptr(new DOF(n+i));
	std::vector<double> orientation = { 0, 0, 1 };

	Element3dRcp * ptr;

	ptr= new Element3dRcp (lb, lt, relFixed, relFixed, pXSec, E, 0.3, orientation);

	elements.push_back(ptr);

	ptr = new Element3dRcp (lt, rt, relFixed, relFixed, pXSec, E, 0.3, orientation);

	elements.push_back(ptr);

	ptr = new Element3dRcp (rt, rb, relFixed, relFixed, pXSec, E, 0.3, orientation);

	elements.push_back(ptr);

	//elements.push_back(&lCol);
	//elements.push_back(&tBeam);
	//elements.push_back(&rCol);

	// OLD STUFF //
	/*	
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
	*/

	return elements;
}

void StructureTest01::AddRestraints(Structure &structure)
{
	/*
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
	*/
}

void StructureTest01::AddForces(Structure &structure)
{
	//structure.ApplyForce(7, 1000);
}

void StructureTest01::Solve(Structure &structure)
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

std::vector<double> StructureTest01::GetResults(Structure &structure)
{
	return std::vector<double> {-1};//structure.GetDisplacements();
}


