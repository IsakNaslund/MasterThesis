#include "Element3d.h"

using namespace arma;
using namespace CIFem;

Element3d::Element3d()
{
	Init();			//Initialise
}

Element3d::Element3d(const CIFem::XYZ sNode, const CIFem::XYZ eNode, vector<int> edof, ElementProperty ep)
{
	Init();			//Initialise

	_sNode = sNode;
	_eNode = eNode;

	try
	{
		SetEdof(edof);
	}
	catch (const std::exception& e)
	{
		// Possibly handle exception in a more meaningful way here. /CH
		throw e;
	}
	
	_ep = ep;

	_length = CalcLength(sNode, eNode);
}


Element3d::~Element3d()
{
}

vector<int> Element3d::GetDofs()
{
	return _edof;
}

// Creates and returns a global element stiffness matrix
arma::Mat<double> Element3d::GetStiffnessMatrix()
{
	// Get indata from element properties
	double A = _ep.GetA();
	double E = _ep.GetE();
	double G = _ep.GetG();
	double Iy = _ep.GetIy();
	double Iz = _ep.GetIz();
	double Kv = _ep.GetKv();

	// Simplify definitions
	double l = _length;
	double l2 = pow(l, 2);
	double l3 = pow(l, 3);

	double k1 = E*A / l;
	double k2 = G*Kv / l;

	////// Define matrix //////
	arma::Mat<double> Ke = zeros(12,12);

	// Row 1
	Ke(0, 0) = k1;				Ke(0, 6) = -k1;

	// Row 2
	Ke(1, 1) = 12 * E*Iz / l3;	Ke(1, 5) = 6 * E*Iz / l2; 
	Ke(1, 7) = -Ke(1, 1);		Ke(1, 11) = Ke(1, 5);

	// Row 3
	Ke(2, 2) = 12 * E*Iy / l3;	Ke(2, 4) = -6 * E*Iy / l2;
	Ke(2, 8) = -Ke(2, 2);		Ke(2, 10) = Ke(2, 4);

	// Row 4
	Ke(3, 3) = k2;				Ke(3, 9) = -k2;

	// Row 5
	Ke(4, 2) = -6 * E*Iy / l2;	Ke(4, 4) = 4 * E*Iy / l;
	Ke(4, 8) = 6 * E*Iy / l2;	Ke(4, 10) = 2 * E*Iy / l;

	// Row 6
	Ke(5, 1) = 6 * E*Iz / l2;	Ke(5, 5) = 4 * E*Iz / l;
	Ke(5, 7) = -6 * E*Iz / l2;	Ke(5, 11) = 2 * E*Iz / l;

	// Row 7
	Ke(6, 0) = -k1;				Ke(6, 6) = k1;

	// Row 8
	Ke(7, 1) = -12 * E*Iz / l3; Ke(7, 5) = -6 * E*Iz / l2;
	Ke(7, 7) = 12 * E*Iz / l3;	Ke(7, 11) = -6 * E*Iz / l2;

	// Row 9
	Ke(8, 2) = -12 * E*Iy / l3; Ke(8, 4) = 6 * E*Iy / l2;
	Ke(8, 8) = 12 * E*Iy / l3;	Ke(8, 10) = 6 * E*Iy / l2;

	// Row 10
	Ke(9, 3) = -k2;				Ke(9, 9) = k2;

	// Row 11
	Ke(10, 2) = -6 * E*Iy / l2; Ke(10, 4) = 2 * E*Iy / l;
	Ke(10, 8) = 6 * E*Iy / l2;	Ke(10, 10) = 4 * E*Iy / l;

	// Row 12
	Ke(11, 1) = 6 * E*Iz / l2;	Ke(11, 5) = 2 * E*Iz / l;
	Ke(11, 7) = -6 * E*Iz / l2; Ke(11, 11) = 4 * E*Iz / l;

	// (counting rows from 1, not 0)

	arma::mat GMat = GetTransformationMatrix();

	return GMat.t()*Ke*GMat;
}


// Creates and returns the transformation matrix G
arma::mat Element3d::GetTransformationMatrix()
{
	arma::mat G(12,12, fill::zeros);

	std::vector<double> bVec = { _eNode.GetX() - _sNode.GetX(), _eNode.GetY() - _sNode.GetY(), _eNode.GetZ() - _sNode.GetZ() };
	arma::vec b(bVec);

	arma::vec n1 = b / _length;
	arma::rowvec n1r = n1.t();
	arma::rowvec n3(_eo);
	arma::rowvec n2(3);

	n2(0) = n3(1)*n1(2) - n3(2)*n1(1);
	n2(1) = -n1(2)*n3(0) + n1(0)*n3(2);
	n2(2) = n3(0)*n1(1) - n1(0)*n3(1);

	arma::mat An(3, 3);
	An.row(0) = n1r;
	An.row(1) = n2;
	An.row(2) = n3;

	// Insert transformation submatrix "along diagonal"
	for (int i = 0; i < 12; i=i+3)
		G.submat(i, i, 2+i, 2+i) = An;

	return G;
}

// Initiates the element
void Element3d::Init()
{
	// Set element orientation to global z
	SetElementOrientation({ 0, 0, 1 });
}


void Element3d::SetEdof(vector<int> edof)
{
	int length = edof.size();
	if (length!=12)
		throw std::invalid_argument("Number of degrees of freedom should be 12.");
	else
		_edof = edof;
}


// Element orientation is the direction of the local z axis
void Element3d::SetElementOrientation(std::vector<double> eo)
{
	if (eo.size() != 3)
		throw invalid_argument("Element orientation vector should have length 3, [x y z]");
	else
	{
		double eoLength = sqrt(eo[0] * eo[0] + eo[1] * eo[1] + eo[2] * eo[2]);
		eo = { eo[0] / eoLength, eo[1] / eoLength, eo[2] / eoLength };
		_eo = eo;
	}
}


double Element3d::CalcLength(XYZ sNode, XYZ eNode)
{
	return sNode.DistanceTo(eNode);
}
