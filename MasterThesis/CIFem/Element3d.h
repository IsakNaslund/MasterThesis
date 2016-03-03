#pragma once

#include "CIFem_dll.h"
#include "XYZ.h"
#include <vector>
#include "SectionProperties.h"
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
		XYZ _sNode, _eNode;		// Start and end node
		vector<int> _edof;		// Element degrees of freedom		
		double _length;			// Element length
		//ElementProperty _ep;	// Element property
		SectionProperties _secProp;
		Material _mat;
		std::vector<double> _eo;// Element orientation

	public:
		Element3d();
		//Element3d(XYZ, XYZ, vector<int>, ElementProperty);
		Element3d(XYZ sNode, XYZ eNode, vector<shared_ptr<DOF> > dof, SectionProperties secProp, Material mat);
		~Element3d();

		arma::Mat<double> GetStiffnessMatrix();	// Returns the element stiffness (in global coordinates)

		arma::Col<double> GravityLoad(Vector3d direction);


		void CalculateSectionForces();


	private:
		void Init();				// Initialises class, call from all constructors
		//void SetEdof(vector<int>);	// Sets the element dofs
		

		void SetElementOrientation(std::vector<double>);
		double CalcLength(XYZ sNode, XYZ eNode);	// Calculates and sets the element length
		arma::mat GetTransformationMatrix();
	protected:
		int GetSize() { return 12; };
	};
}


