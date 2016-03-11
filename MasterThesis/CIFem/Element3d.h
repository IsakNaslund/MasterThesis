#pragma once

#include "CIFem_dll.h"
#include "XYZ.h"
#include <vector>
#include "Material.h"
#include "include\armadillo"
#include "IElement.h"
#include <memory>
#include "IUtilCheck3d.h"
#include "ElementResults3d.h"
#include "UtilCheck3dBasic.h"


using namespace std;
using namespace CIFem;

namespace CIFem
{
	class CIFEM_API Element3d : public IElement
	{
		XYZ _sNode, _eNode;		// Start and end node	
		double _length;			// Element length
		
		Material _mat;
		Vector3d _eo;			// Element orientation
		ElementResults3d _results;
		std::shared_ptr<IUtilCheck3d> _utilCheck;

		//Distributed loads
		double _qx, _qy, _qz, _qw;

		//Stiffness matrix
		arma::mat::fixed<12,12> _Ke;

	public:
		Element3d();
		Element3d(const CIFem::XYZ sNode, const CIFem::XYZ eNode, std::vector<std::shared_ptr<DOF>> dof, std::shared_ptr<ICrossSection> crossSec, Material mat, Vector3d normal);
		Element3d(const CIFem::XYZ sNode, const CIFem::XYZ eNode, std::vector<std::shared_ptr<DOF>> dof, std::shared_ptr<ICrossSection> crossSec, Material mat, Vector3d normal, std::shared_ptr<IUtilCheck3d> checktype);
		~Element3d();



		void UpdateStiffnessMatrix();
		void DoSectionChecks();
		void UpdateUtilisation(double u);

		const arma::Mat<double> & GetStiffnessMatrix();	// Returns the element stiffness (in global coordinates)

		arma::Col<double> GravityLoad(Vector3d direction);


		void CalculateSectionForces() {  CalculateSectionForces(11); }
		void CalculateSectionForces(int n);   //n is the number of evaluation points


		// Geometric data getters
		XYZ StartPosition() const { return _sNode; }
		XYZ EndPosition() const { return _eNode; }
		Vector3d Orientation() const { return _eo; }

		//Result outputs:
		//Section Forces
		std::vector<double> NormalForce() const;
		std::vector<double> ShearForceZ() const;
		std::vector<double> ShearForceY() const;
		std::vector<double> MomentY() const;
		std::vector<double> MomentZ() const;
		std::vector<double> TorsionalForce() const;

		//Displacements
		std::vector<double> DisplacementX() const;
		std::vector<double> DisplacementY() const;
		std::vector<double> DisplacementZ() const;
		std::vector<double> DisplacementTorsion() const;

		//Location along the element
		std::vector<double> ResultPosition() const;


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


