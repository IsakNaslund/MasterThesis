#pragma once
#include "CIFem_dll.h"
#include <vector>
#include "INode.h"
#include "IElementRcp.h"
#include "IElement.h"
#include "Plane.h"
#include <memory>
#include <set>

namespace CIFem
{
	class CIFEM_API Structure
	{
		std::vector<std::shared_ptr<INode>> _nodes;
		std::vector<std::shared_ptr<CIFem::IElement>> _elements;
		//std::vector<std::shared_ptr<IElementRcp>> _elementRcps;
		Plane _structureOrientation;
		bool _validForLinearSolve;

	public:
		Structure();
		~Structure();

		void AddNode(std::shared_ptr<INode>);
		void AddNode(std::vector<std::shared_ptr<INode>>);
		void AddElementRcp(std::shared_ptr<IElementRcp>);
		void AddElementRcp(std::vector<std::shared_ptr<IElementRcp>>);


		double GetWeight() const;
		int NodeCount();
		int ElementCount();

		// Not implemented, probably shouldnt be either....?
		Structure Copy();

		const std::vector<std::shared_ptr<CIFem::IElement>> & GetElements();
		const std::vector<std::shared_ptr<INode>> & GetNodes();

		void ResetStructure();
		void ResetStructrualForces();

		std::set<std::shared_ptr<CIFem::DOF>> GetDofs();

		void ApplyGravityToElements(Vector3d gravField);
		void ApplyNodalForces();

		arma::mat AssembleStiffnessMatrix(int size);

		arma::mat GetCMatrix();

		void CalculateElementSectionForces(std::string resultName);
		
		// Sets the flag if the structure is valid to true
		void SetValidForLinearCalculation() { _validForLinearSolve = true; };

		// Returns a boolean that indicates if the structure is valid for linear solve
		bool IsValidForLinearCalculation() { return _validForLinearSolve; };

	private:		
		void GetNodeDofs(std::set<std::shared_ptr<CIFem::DOF>> & dofs);
		void GetUniqueElementDofs(std::set<std::shared_ptr<CIFem::DOF>> & dofs);

		void AssembleElementsInKMat(arma::mat & K, arma::mat & Ke, const std::vector<std::shared_ptr<DOF>>&);

		////////////////////////////////////////////////////////////
		////////Old stuff. Saved for reference if needed////////////
		////////////////////////////////////////////////////////////


		//void SetDofKMatIndex(std::set<std::shared_ptr<CIFem::DOF>>&);
		
		
		//arma::colvec GetForceVector(std::set<std::shared_ptr<DOF>>);
		//arma::colvec GetDisplacementVector(std::set<std::shared_ptr<DOF>>);


		//void LinEqSolve(arma::sp_mat & K, arma::colvec & a, arma::colvec & f, arma::mat & C, std::set<std::shared_ptr<DOF>>, arma::colvec & s);
		//double EigenSolve(arma::sp_mat & K, arma::colvec & am, arma::mat & C, std::set<std::shared_ptr<DOF>> spDofs, arma::colvec & s, int mode);

		//void StoreResultsInDofs(arma::colvec a, arma::colvec f, std::set<std::shared_ptr<DOF>>);

		//void CalculateElemetForces();
		//

	};
}

