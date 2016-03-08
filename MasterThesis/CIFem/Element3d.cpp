#include "Element3d.h"

using namespace CIFem;

Element3d::Element3d()
{
	//Init();			//Initialise
}

/*
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
}*/

Element3d::Element3d(const CIFem::XYZ sNode, const CIFem::XYZ eNode, std::vector<std::shared_ptr<DOF> > dof, std::shared_ptr<ICrossSection> crossSec, Material mat, Vector3d normal)
{
	//Init();			//Initialise

	_eo = normal;
	_eo.Unitize();

	_sNode = sNode;
	_eNode = eNode;

	try
	{
		SetEdof(dof);
	}
	catch (const std::exception& e)
	{
		// Possibly handle exception in a more meaningful way here. /CH
		throw e;
	}

	_crossSection = crossSec;
	_mat = mat;

	_length = CalcLength(sNode, eNode);
}


Element3d::~Element3d()
{
}

/*
vector<int> Element3d::GetDofs()
{
	return _edof;
}
*/

// Creates and returns a global element stiffness matrix
arma::Mat<double> Element3d::GetStiffnessMatrix()
{
	// Get indata from element properties
	double A = _crossSection->GetArea();
	double E = _mat.E();
	double G = _mat.G();
	double Iy = _crossSection->GetIy();
	double Iz = _crossSection->GetIz();
	double Kv = _crossSection->GetKv();

	// Simplify definitions
	double l = _length;
	double l2 = pow(l, 2);
	double l3 = pow(l, 3);

	double k1 = E*A / l;
	double k2 = G*Kv / l;

	////// Define matrix //////
	arma::Mat<double> Ke = arma::zeros(12,12);

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

arma::Col<double> CIFem::Element3d::GravityLoad(Vector3d direction)
{
	//empty force vector
	//arma::vec f(12, arma::fill::zeros);

	//volume times density
	double volDens = _mat.Rho()*_crossSection->GetArea()*_length;

	//temporary variables to fill the force vector
	double qx, qy, qz, mx, my, mz;

	qx = direction.GetX()*volDens / 2;
	qy = direction.GetY()*volDens / 2;
	qz = direction.GetZ()*volDens / 2;

	//to get leaverarms for moments
	Vector3d part(_sNode, _eNode);


	//End moments. calculated as g (gravity coefficients) times volumeDensity times leaverarms in diffrent directions divided by 12
	//Need to check that the signs of these gets correct...
	mx = volDens*(-direction.GetY()*part.GetZ() + direction.GetZ()*part.GetY()) / 12;
	my = volDens*(direction.GetX()*part.GetZ() - direction.GetZ()*part.GetX()) / 12;
	mz = volDens*(direction.GetY()*part.GetX() - direction.GetX()*part.GetY()) / 12;


	//Add load to the beams degees of freedom

	_dof[0]->AddLoad(qx);
	_dof[1]->AddLoad(qy);
	_dof[2]->AddLoad(qz);
	_dof[3]->AddLoad(mx);
	_dof[4]->AddLoad(my);
	_dof[5]->AddLoad(mz);
	_dof[6]->AddLoad(qx);
	_dof[7]->AddLoad(qy);
	_dof[8]->AddLoad(qz);
	_dof[9]->AddLoad(-mx);
	_dof[10]->AddLoad(-my);
	_dof[11]->AddLoad(-mz);



	/*f(0) = f(6) = qx;
	f(1) = f(7) = qy;
	f(2) = f(8) = qz;
	f(7) = mx;
	f(8) = my;
	f(9) = mz;
	f(9) = -mx;
	f(10) = -my;
	f(11) = -mz;

	return f;*/

	return arma::vec();
}

void CIFem::Element3d::CalculateSectionForces(int n)
{
	//solving without taking ito acount deformations from internal ditributed loads first.

	arma::mat G = GetTransformationMatrix();

	arma::vec ed(12);

	for (int i = 0; i < _dof.size(); i++)
	{
		ed[i] = _dof[i]->GetResultingTranslation();
	}

	arma::vec u = G*ed;

	arma::mat C = GetCMatrix();

	arma::vec m = arma::solve(C, u);

	//_N1, _Vy, _Vz, _T, _My, _Mz, _u, _v, _w, _fi, pos;

	double EA, EIz, EIy, GKv;

	EA = _crossSection->GetArea()*_mat.E();
	EIy = _crossSection->GetIy()*_mat.E();
	EIz = _crossSection->GetIz()*_mat.E();
	GKv = _crossSection->GetKv()*_mat.G();

	for (int i = 0; i < n; i++)
	{
		//position on the beam
		double x;

		if (n == 1)
			x = _length / 2;
		else
			x = (double)i * _length / ((double)(n - 1));
		
		_results._pos.push_back(x);

		double x2, x3;

		x2 = pow(x, 2);
		x3 = pow(x, 3);
																	//Values ignored for now..
		_results._N.push_back(EA*m(0));								//-qx*x
		_results._Vy.push_back(-6 * EIz*m(2));						//-qy*x
		_results._Vz.push_back(-6 * EIy*m(6));						//-qz*x
		_results._T.push_back(GKv*m(10));							//-qw*x
		_results._My.push_back(-6 * EIy*x*m(6) - 2 * EIy*m(7));		//-qz*x^2/2
		_results._Mz.push_back(6 * EIz*x*m(2) + 2 * EIz*m(3));		//qy*x^2/2

		_results._u.push_back(x*m(0) + m(1));						//-qx*x^2/2/EA;
		_results._v.push_back(x3*m(2) + x2*m(3) + x*m(4) + m(5));	//qy*x^4/24/EIz;
		_results._w.push_back(x3*m(6) + x2*m(7) + x*m(8) + m(9));	//qz*x^4/24/EIy;
		_results._fi.push_back(x*m(10) + m(11));					//-qw*x^2/2/GKv

	}

}


// Creates and returns the transformation matrix G
arma::mat Element3d::GetTransformationMatrix()
{
	arma::mat G(12,12, arma::fill::zeros);

	std::vector<double> bVec = { _eNode.GetX() - _sNode.GetX(), _eNode.GetY() - _sNode.GetY(), _eNode.GetZ() - _sNode.GetZ() };
	arma::vec b(bVec);

	arma::vec n1 = b / _length;
	arma::rowvec n1r = n1.t();
	arma::rowvec n3(_eo.ToStandardVector());
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

arma::mat CIFem::Element3d::GetCMatrix()
{
	arma::mat C(12, 12, arma::fill::zeros);

	double L, L2, L3;

	L = _length;
	L2 = pow(_length, 2);
	L3 = pow(_length, 3);

	C(0, 1) = 1;
	C(1, 5) = 1;
	C(2, 9) = 1;
	C(3, 11) = 1;
	C(4, 8) = -1;
	C(5, 4) = 1;

	C(6, 0) = L;
	C(6, 1) = 1;

	C(7, 2) = L3;
	C(7, 3) = L2;
	C(7, 4) = L;
	C(7, 5) = 1;

	C(8, 6) = L3;
	C(8, 7) = L2;
	C(8, 8) = L;
	C(8, 9) = 1;

	C(9, 10) = L;
	C(9, 11) = 1;

	C(10, 6) = -3*L2;
	C(10, 7) = -2*L;
	C(10, 8) = -1;

	C(10, 2) = 3*L2;
	C(10, 3) = 2*L;
	C(10, 4) = 1;

	return C;

	/*C = [0 1   0    0  0 0    0     0   0 0 0 0;
		 0 0   0    0  0 1    0     0   0 0 0 0;
		 0 0   0    0  0 0    0     0   0 1 0 0;
		 0 0   0    0  0 0    0     0   0 0 0 1;
		 0 0   0    0  0 0    0     0 - 1 0 0 0;
		 0 0   0    0  1 0    0     0   0 0 0 0;
		 L 1   0    0  0 0    0     0   0 0 0 0;
		 0 0  L^3  L^2 L 1    0     0   0 0 0 0;
		 0 0   0    0  0 0   L^3   L^2  L 1 0 0;
		 0 0   0    0  0 0    0     0   0 0 L 1;
		 0 0   0    0  0 0 -3*L^2 -2*L -1 0 0 0;
		 0 0 3*L^2 2*L 1 0    0     0   0 0 0 0];*/
}

// Initiates the element
/*void Element3d::Init()
{
	// Set element orientation to global z
	SetElementOrientation({ 0, 0, 1 });

}*/

/*
void Element3d::SetEdof(vector<int> edof)
{
	int length = edof.size();
	if (length!=12)
		throw std::invalid_argument("Number of degrees of freedom should be 12.");
	else
		_edof = edof;
}*/




// Element orientation is the direction of the local z axis
/*void Element3d::SetElementOrientation(std::vector<double> eo)
{
	if (eo.size() != 3)
		throw invalid_argument("Element orientation vector should have length 3, [x y z]");
	else
	{
		double eoLength = sqrt(eo[0] * eo[0] + eo[1] * eo[1] + eo[2] * eo[2]);
		eo = { eo[0] / eoLength, eo[1] / eoLength, eo[2] / eoLength };
		_eo = eo;
	}
}*/


double Element3d::CalcLength(XYZ sNode, XYZ eNode)
{
	return sNode.DistanceTo(eNode);
}
