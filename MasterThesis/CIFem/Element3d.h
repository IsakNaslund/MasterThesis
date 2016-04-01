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
#include <map>


using namespace std;
using namespace CIFem;

namespace CIFem
{
	class CIFEM_API Element3d : public IElement
	{
		XYZ _sNode, _eNode;		// Start and end node	
		double _length;			// Element length
		
		std::shared_ptr<Material> _mat;
		Vector3d _eo;			// Element orientation
		ElementResults3d _results;
		//ElementResults3d _results;
		std::shared_ptr<IUtilCheck3d> _utilCheck;
		std::shared_ptr<ICrossSection> _crossSection;

		//Distributed loads
		double _qx, _qy, _qz, _qw;

		//Stiffness matrix
		arma::mat::fixed<12,12> _Ke;

	public:
		Element3d();
		Element3d(const CIFem::XYZ sNode, const CIFem::XYZ eNode, std::vector<std::shared_ptr<DOF>> dof, std::shared_ptr<ICrossSection> crossSec, std::shared_ptr<Material> mat, Vector3d normal);
		Element3d(const CIFem::XYZ sNode, const CIFem::XYZ eNode, std::vector<std::shared_ptr<DOF>> dof, std::shared_ptr<ICrossSection> crossSec, std::shared_ptr<Material> mat, Vector3d normal, std::shared_ptr<IUtilCheck3d> checktype);
		~Element3d();

		double Weight() const;

		void ResetElementForces() { ResetLineLoads(); }

		void ResetLineLoads();

		void UpdateStiffnessMatrix();


		const arma::Mat<double> & GetStiffnessMatrix();	// Returns the element stiffness (in global coordinates)

		arma::Col<double> GravityLoad(Vector3d direction);


		void CalculateSectionForces(string resultName) {  CalculateSectionForces(11, resultName); }
		void CalculateSectionForces(int n, string resultName);   //n is the number of evaluation points


		//Update functions to be used by optimizers to update diffrent beam properties
		void UpdateCrossSection(std::shared_ptr<ICrossSection> newCrossSection);
		std::shared_ptr<ICrossSection> GetCrossSection() const;
		void UpdateMaterial(std::shared_ptr<Material> newMat);
		void UpdateNormal(Vector3d newNormal);



		// Geometric data getters
		XYZ StartPosition() const { return _sNode; }
		XYZ EndPosition() const { return _eNode; }
		Vector3d Orientation() const { return _eo; }

		//Result outputs:
		//Section Forces
		std::vector<double> NormalForce(std::string res);
		std::vector<double> ShearForceZ(std::string res);
		std::vector<double> ShearForceY(std::string res);
		std::vector<double> MomentY(std::string res);
		std::vector<double> MomentZ(std::string res);
		std::vector<double> TorsionalForce(std::string res);

		//Displacements
		std::vector<double> DisplacementX(std::string res);
		std::vector<double> DisplacementY(std::string res);
		std::vector<double> DisplacementZ(std::string res);
		std::vector<double> DisplacementTorsion(std::string res);

		//Location along the element
		std::vector<double> ResultPosition();

		//Utilisations
		std::vector<std::shared_ptr<Utilisation>> Utilisations(std::string res);

		//Calc and get max utilisation
		Utilisation CalcAndGetMaxUtil();

		//Result outputs:
		//Section Forces
		const std::map<std::string, std::vector<double>> & AllNormalForce() const;
		const std::map<std::string, std::vector<double>> & AllShearForceZ() const;
		const std::map<std::string, std::vector<double>> & AllShearForceY() const;
		const std::map<std::string, std::vector<double>> & AllMomentY() const;
		const std::map<std::string, std::vector<double>> & AllMomentZ() const;
		const std::map<std::string, std::vector<double>> & AllTorsionalForce() const;

		//Displacements
		const std::map<std::string, std::vector<double>> & AllDisplacementX() const;
		const std::map<std::string, std::vector<double>> & AllDisplacementY() const;
		const std::map<std::string, std::vector<double>> & AllDisplacementZ() const;
		const std::map<std::string, std::vector<double>> & AllDisplacementTorsion() const;

		const std::map<std::string, std::vector<std::shared_ptr<Utilisation>>> & AllUtilisation() const;

	private:
		//void Init();				// Initialises class, call from all constructors
		//void SetEdof(vector<int>);	// Sets the element dofs
		
		void SetElementOrientation(Vector3d eo);

		//void SetElementOrientation(std::vector<double>);
		double CalcLength(XYZ sNode, XYZ eNode);	// Calculates and sets the element length

		arma::mat GetTransformationMatrix();		//12x12 big transformation matrix
		arma::mat GetSmallTransMatrix();			//3x3 small transformation matrix 


		arma::mat GetCMatrix();						//Used for section forces

		// Results
		//ElementResults3d & GetResult(std::string resultName);
 
		

	protected:

		void DoSectionChecks(std::string resultName);
		int GetSize() { return 12; };
	};
}


