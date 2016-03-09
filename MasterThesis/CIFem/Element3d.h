#pragma once

#include "CIFem_dll.h"
#include "XYZ.h"
#include <vector>
#include "Material.h"
#include "include\armadillo"
#include "IElement.h";
#include <memory>

using namespace std;
using namespace CIFem;

namespace CIFem
{
	class CIFEM_API Element3d : public IElement
	{

		struct Results
		{
			//Lists of results
			std::vector<double> _N, _Vy, _Vz, _T, _My, _Mz, _u, _v, _w, _fi, _pos;
		};

		XYZ _sNode, _eNode;		// Start and end node
		vector<int> _edof;		// Element degrees of freedom		
		double _length;			// Element length
		//ElementProperty _ep;	// Element property
		//SectionProperties _secProp;
		
		Material _mat;
		Vector3d _eo;// Element orientation
		Results _results;

		//Distributed loads
		double _qx, _qy, _qz,_qw;

	public:
		Element3d();
		//Element3d(XYZ, XYZ, vector<int>, ElementProperty);
		Element3d(const CIFem::XYZ sNode, const CIFem::XYZ eNode, std::vector<std::shared_ptr<DOF> > dof, std::shared_ptr<ICrossSection> crossSec, Material mat, Vector3d normal);
		~Element3d();

		arma::Mat<double> GetStiffnessMatrix();	// Returns the element stiffness (in global coordinates)

		arma::Col<double> GravityLoad(Vector3d direction);


		void CalculateSectionForces() {  CalculateSectionForces(11); }
		void CalculateSectionForces(int n);   //n is the number of evaluation points


		//Geometric data getters
		XYZ StartPosition() const { return _sNode; }
		XYZ EndPosition() const { return _eNode; }
		Vector3d Orientation() const { return _eo; }

		//Result outputs:
		//Section Forces
		std::vector<double> NormalForce() const { return _results._N; }
		std::vector<double> ShearForceZ() const { return _results._Vz; }
		std::vector<double> ShearForceY() const { return _results._Vy; }
		std::vector<double> MomentY() const { return _results._My; }
		std::vector<double> MomentZ() const { return _results._Mz; }
		std::vector<double> TorsionalForce() const { return _results._T; }

		//Displacements
		std::vector<double> DisplacementX() const { return _results._u; }
		std::vector<double> DisplacementY() const { return _results._v; }
		std::vector<double> DisplacementZ() const { return _results._w; }
		std::vector<double> DisplacementTorsion() const { return _results._fi; }

		//Location along the element
		std::vector<double> ResultPosition() const { return _results._pos; }

		//Utilization
		//TODO: Implement utilization calculations



	private:
		//void Init();				// Initialises class, call from all constructors
		//void SetEdof(vector<int>);	// Sets the element dofs
		
		void SetElementOrientation(Vector3d eo);

		//void SetElementOrientation(std::vector<double>);
		double CalcLength(XYZ sNode, XYZ eNode);	// Calculates and sets the element length

		arma::mat GetTransformationMatrix();		//12x12 big transformation matrix
		arma::mat GetSmallTransMatrix();			//3x3 small transformation matrix 


		arma::mat GetCMatrix();						//Used for section forces


 


	protected:
		int GetSize() { return 12; };
	};
}


