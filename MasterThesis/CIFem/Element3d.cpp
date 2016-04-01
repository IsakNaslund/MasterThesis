#include "Element3d.h"

using namespace CIFem;

Element3d::Element3d()
{
	//Init();			//Initialise
}

// Creates an element with a basic check. If possible use overloaded function instead.
Element3d::Element3d(const CIFem::XYZ sNode, const CIFem::XYZ eNode, std::vector<std::shared_ptr<DOF> > dof, std::shared_ptr<ICrossSection> crossSec, std::shared_ptr<Material> mat, Vector3d normal) :
	Element3d(sNode, eNode, dof, crossSec, mat, normal, Element3dChecks::BasicCheckSharedPtr())
{
	
}

CIFem::Element3d::Element3d(const CIFem::XYZ sNode, const CIFem::XYZ eNode, std::vector<std::shared_ptr<DOF>> dof, std::shared_ptr<ICrossSection> crossSec, std::shared_ptr<Material> mat, Vector3d normal, std::shared_ptr<Element3dChecks> checktype)
{

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

	//Needs to be called after start and endnode has been initialized
	SetElementOrientation(normal);

	//Set up zero load
	_qx = _qy = _qz = _qw = 0;

	_utilCheck = checktype;

	_updateStiffnessMatrix = true;
}

CIFem::Element3d::Element3d(const CIFem::XYZ sNode, const CIFem::XYZ eNode, std::vector<std::shared_ptr<DOF>> dof, std::shared_ptr<ICrossSection> crossSec, std::shared_ptr<Material> mat, Vector3d normal, std::shared_ptr<Element3dChecks> checktype, std::shared_ptr<SectionGroup> sectionGroup)
:Element3d(sNode, eNode, dof, crossSec, mat, normal, checktype)
{
	_sectionGroup = sectionGroup;
}

CIFem::Element3d::Element3d(const CIFem::XYZ sNode, const CIFem::XYZ eNode, std::vector<std::shared_ptr<DOF>> dof, std::shared_ptr<ICrossSection> crossSec, std::shared_ptr<Material> mat, Vector3d normal, std::shared_ptr<SectionGroup> sectionGroup)
	: Element3d(sNode, eNode, dof, crossSec, mat, normal, Element3dChecks::BasicCheckSharedPtr(), sectionGroup)
{

}

Element3d::~Element3d()
{
}

double CIFem::Element3d::Weight() const
{
	return _length*_crossSection->GetArea()*_mat->Rho();
}

void CIFem::Element3d::ResetLineLoads()
{
	_qx = _qy = _qz = _qw = 0;
}


void CIFem::Element3d::UpdateStiffnessMatrix()
{
	// Get indata from element properties
	double A = _crossSection->GetArea();
	double E = _mat->E();
	double G = _mat->G();
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
	arma::Mat<double> Ke = arma::zeros(12, 12);

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

	_Ke = GMat.t()*Ke*GMat;
}

// Creates and returns a global element stiffness matrix
const arma::Mat<double> & Element3d::GetStiffnessMatrix()
{
	if (_updateStiffnessMatrix)
		UpdateStiffnessMatrix();

	return _Ke;
}

arma::Col<double> CIFem::Element3d::GravityLoad(Vector3d direction)
{
	//empty force vector
	//arma::vec f(12, arma::fill::zeros);

	//volume times density
	double volDens = _mat->Rho()*_crossSection->GetArea()*_length;

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

	//Store gravity loads in N/m for section force evaluation

	arma::mat T = GetSmallTransMatrix();

	arma::vec eq;
	eq<< 2*qx/_length << 2*qy / _length << 2*qz / _length;

	arma::vec lEq = T*eq;

	_qx += lEq[0];
	_qy += lEq[1];
	_qz += lEq[2];

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


//Calculated section forces and moments, and performs a section check.
void CIFem::Element3d::CalculateSectionForces(int n, string resultName)
{
	//ElementResults3d result = GetResult(resultName);

	//Reset result file:
	//result.Reset();
	_results.SetUpLoadComb(resultName);
	//Variables used frequently
	double EA, EIz, EIy, GKv, L2, L3, L4;

	EA = _crossSection->GetArea()*_mat->E();
	EIy = _crossSection->GetIy()*_mat->E();
	EIz = _crossSection->GetIz()*_mat->E();
	GKv = _crossSection->GetKv()*_mat->G();

	L2 = pow(_length, 2);
	L3 = pow(_length, 3);
	L4 = pow(_length, 4);

	arma::vec up;	//particular solution

	up << 0 << 0 << 0 << 0 << 0 << 0 << -_qx*L2 / 2 / EA << _qy*L4 / 24 / EIz << _qz*L4 / 24 / EIy << -_qw*L2 / 2 / GKv << -_qz*L3 / 6 / EIy << _qy*L3 / 6 / EIz;


	//solving without taking ito acount deformations from internal ditributed loads first.

	arma::mat G = GetTransformationMatrix();

	arma::vec ed(12);

	for (int i = 0; i < _dof.size(); i++)
	{
		ed[i] = _dof[i]->GetResultingTranslation();
	}

	arma::vec u = G*ed-up;

	arma::mat C = GetCMatrix();

	arma::vec m = arma::solve(C, u);

	//arma::vec m = arma::inv(C)*u;

	//_N1, _Vy, _Vz, _T, _My, _Mz, _u, _v, _w, _fi, pos;

	//TODO:: Make this in a cleaner way:
	_results._pos.clear();

	for (int i = 0; i < n; i++)
	{
		//position on the beam
		double x;

		if (n == 1)
			x = _length / 2;
		else
			x = (double)i * _length / ((double)(n - 1));

		_results._pos.push_back(x);

		double x2, x3, x4;

		x2 = pow(x, 2);
		x3 = pow(x, 3);
		x4 = pow(x, 4);
																						//Values ignored for now..
		_results._N[resultName].push_back(EA*m(0) - _qx*x);											//-qx*x
		_results._Vy[resultName].push_back(-6 * EIz*m(2) - _qy*x);									//-qy*x
		_results._Vz[resultName].push_back(-6 * EIy*m(6) - _qz*x);									//-qz*x
		_results._T[resultName].push_back(GKv*m(10) - _qw*x);										//-qw*x
		_results._My[resultName].push_back(-6 * EIy*x*m(6) - 2 * EIy*m(7) - _qz*x2 / 2);			//-qz*x^2/2
		_results._Mz[resultName].push_back(6 * EIz*x*m(2) + 2 * EIz*m(3) + _qy*x2 / 2);				//qy*x^2/2

		_results._u[resultName].push_back(x*m(0) + m(1) - _qx*x2 / (2 * EA));						//-qx*x^2/2/EA;
		_results._v[resultName].push_back(x3*m(2) + x2*m(3) + x*m(4) + m(5) + _qy*x4 / (24 * EIz));	//qy*x^4/24/EIz;
		_results._w[resultName].push_back(x3*m(6) + x2*m(7) + x*m(8) + m(9) + _qz*x4 / (24 * EIy));	//qz*x^4/24/EIy;
		_results._fi[resultName].push_back(x*m(10) + m(11) - _qw*x2 / (2 * GKv));					//-qw*x^2/2/GKv


		// Initialise list of utilisations so that it has as many points as the results
		std::shared_ptr<Utilisation> spU(new Utilisation());
		_results._util[resultName].push_back(spU);
	}

	// Do section checks when all results are stored
	DoSectionChecks(resultName);
}

void CIFem::Element3d::UpdateCrossSection(std::shared_ptr<ICrossSection> newCrossSection)
{
	_crossSection = newCrossSection;
	_updateStiffnessMatrix = true;
}

void CIFem::Element3d::UpdateMaterial(std::shared_ptr<Material> newMat)
{
	_mat = newMat;
	_updateStiffnessMatrix = true;
}

void CIFem::Element3d::UpdateNormal(Vector3d newNormal)
{
	_eo = newNormal;
	_updateStiffnessMatrix = true;
}

bool CIFem::Element3d::UpdateCrossSection()
{
	if (_results._maxUtil.GetUtil() > 1)
	{
		std::shared_ptr<ICrossSection> newSec;
		bool success = _sectionGroup->UpdateCrossSection(_mat, _results, newSec);

		//Should the cross section be updated if no match found? Doing it anyway for now....

		UpdateCrossSection(newSec);

		return success;
	}
	return true;
}




// Do section checks for all results stored in element
void CIFem::Element3d::DoSectionChecks(std::string resultName)
{
	_utilCheck->CheckElementUtilisations(this->_crossSection, this->_mat, _results, resultName);
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

arma::mat CIFem::Element3d::GetSmallTransMatrix()
{
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

	return An;
}

arma::mat CIFem::Element3d::GetCMatrix()
{

	double L, L2, L3;

	L = _length;
	L2 = pow(_length, 2);
	L3 = pow(_length, 3);


	arma::mat C;

	C << 0 << 1 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << arma::endr				//1
		<< 0 << 0 << 0 << 0 << 0 << 1 << 0 << 0 << 0 << 0 << 0 << 0 << arma::endr			//2
		<< 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 1 << 0 << 0 << arma::endr			//3
		<< 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 1 << arma::endr			//4
		<< 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << -1 << 0 << 0 << 0 << arma::endr			//5
		<< 0 << 0 << 0 << 0 << 1 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << arma::endr			//6
		<< L << 1 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << arma::endr			//7
		<< 0 << 0 << L3 << L2 << L << 1 << 0 << 0 << 0 << 0 << 0 << 0 << arma::endr			//8
		<< 0 << 0 << 0 << 0 << 0 << 0 << L3 << L2 << L << 1 << 0 << 0 << arma::endr			//9
		<< 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << L << 1 << arma::endr			//10
		<< 0 << 0 << 0 << 0 << 0 << 0 << -3*L2 << -2*L << -1 << 0 << 0 << 0 << arma::endr	//11
		<< 0 << 0 << 3*L2 << 2*L << 1 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << arma::endr;			//12
	  
	return C;

	/*C =  [0 1   0    0  0 0    0     0   0 0 0 0;		//1
			0 0   0    0  0 1    0     0   0 0 0 0;		//2
			0 0   0    0  0 0    0     0   0 1 0 0;		//3
			0 0   0    0  0 0    0     0   0 0 0 1;		//4
			0 0   0    0  0 0    0     0 - 1 0 0 0;		//5
			0 0   0    0  1 0    0     0   0 0 0 0;		//6
			L 1   0    0  0 0    0     0   0 0 0 0;		//7
			0 0  L^3  L^2 L 1    0     0   0 0 0 0;		//8
			0 0   0    0  0 0   L^3   L^2  L 1 0 0;		//9
			0 0   0    0  0 0    0     0   0 0 L 1;		//10
			0 0   0    0  0 0 -3*L^2 -2*L -1 0 0 0;		//11
			0 0 3*L^2 2*L 1 0    0     0   0 0 0 0];*/	//12
}





void CIFem::Element3d::SetElementOrientation(Vector3d eo)
{
	Vector3d tan(_sNode, _eNode);
	
	tan.Unitize();
	eo.Unitize();

	_eo = eo - tan*tan.DotProduct(eo);
	_eo.Unitize();


}


/*ElementResults3d & CIFem::Element3d::GetResult(std::string resultName)
{
	// Find or create result object
	ElementResults3d result;
	if (_results.find(resultName) != _results.end())
		result = _results.find(resultName)->second;
	else
		_results[resultName] = result;

	return result;
}*/

double Element3d::CalcLength(XYZ sNode, XYZ eNode)
{
	return sNode.DistanceTo(eNode);
}

std::vector<double> CIFem::Element3d::NormalForce(const std::string comb)
{
	return std::vector<double>();
}

std::vector<double> CIFem::Element3d::ShearForceZ(std::string comb)
{
	return std::vector<double>();
}

std::vector<double> CIFem::Element3d::ShearForceY(std::string comb)
{
	return std::vector<double>();
}

std::vector<double> CIFem::Element3d::MomentY(std::string comb)
{
	return std::vector<double>();
}

std::vector<double> CIFem::Element3d::MomentZ(std::string comb)
{
	return std::vector<double>();
}

std::vector<double> CIFem::Element3d::TorsionalForce(std::string comb)
{
	return std::vector<double>();
}

std::vector<double> CIFem::Element3d::DisplacementX(std::string comb)
{
	return std::vector<double>();
}

std::vector<double> CIFem::Element3d::DisplacementY(std::string comb) 
{
	return std::vector<double>();
}

std::vector<double> CIFem::Element3d::DisplacementZ(std::string comb) 
{
	return std::vector<double>();
}

std::vector<double> CIFem::Element3d::DisplacementTorsion(std::string comb) 
{
	return std::vector<double>();
}

std::vector<double> CIFem::Element3d::ResultPosition() 
{
	return _results._pos;
}

std::vector<std::shared_ptr<Utilisation>> CIFem::Element3d::Utilisations(std::string comb) 
{
	return std::vector<std::shared_ptr<Utilisation>>();
}

Utilisation CIFem::Element3d::CalcAndGetMaxUtil()
{
	_results.CalcMaxUtil();
	return _results._maxUtil;
}

const std::map<std::string, std::vector<double>> & CIFem::Element3d::AllNormalForce() const
{
	return _results._N;
}

const std::map<std::string, std::vector<double>>&  CIFem::Element3d::AllShearForceZ() const
{
	return _results._Vz;
}

const std::map<std::string, std::vector<double>> & CIFem::Element3d::AllShearForceY() const
{
	return _results._Vy;
}

const std::map<std::string, std::vector<double>> & CIFem::Element3d::AllMomentY() const
{
	return _results._My;
}

const std::map<std::string, std::vector<double>> & CIFem::Element3d::AllMomentZ() const
{
	return _results._Mz;
}

const std::map<std::string, std::vector<double>> & CIFem::Element3d::AllTorsionalForce() const
{
	return _results._T;
}

const std::map<std::string, std::vector<double>> & CIFem::Element3d::AllDisplacementX() const
{
	return _results._u;
}

const std::map<std::string, std::vector<double>> & CIFem::Element3d::AllDisplacementY() const
{
	return _results._v;
}

const std::map<std::string, std::vector<double>> & CIFem::Element3d::AllDisplacementZ() const
{
	return _results._w;
}

const std::map<std::string, std::vector<double>> & CIFem::Element3d::AllDisplacementTorsion() const
{
	return _results._fi;
}

const std::map<std::string, std::vector<std::shared_ptr<Utilisation>>>& CIFem::Element3d::AllUtilisation() const
{
	return _results._util;
}
