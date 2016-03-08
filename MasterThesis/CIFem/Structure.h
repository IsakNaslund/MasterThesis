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
		std::vector<std::shared_ptr<IElementRcp>> _elementRcps;
		Plane _structureOrientation;

	public:
		Structure();
		~Structure();

		void AddNode(std::shared_ptr<INode>);
		void AddNode(std::vector<std::shared_ptr<INode>>);
		void AddElementRcp(std::shared_ptr<IElementRcp>);
		void AddElementRcp(std::vector<std::shared_ptr<IElementRcp>>);

		// Not implemented!
		Structure Copy();
		void Solve();

		std::vector<std::shared_ptr<CIFem::IElement>> GetElements();

	protected:
		std::vector<std::shared_ptr<CIFem::IElement>> _elements;

	private:
		std::vector<std::shared_ptr<CIFem::IElement>> CreateElements();
		void BuildStructure();
		std::set<std::shared_ptr<CIFem::DOF>> GetDofs();
		void GetNodeDofs(std::set<std::shared_ptr<CIFem::DOF>> & dofs);
		void GetUniqueElementDofs(std::set<std::shared_ptr<CIFem::DOF>> & dofs);

		void SetDofKMatIndex(std::set<std::shared_ptr<CIFem::DOF>>&);
		arma::sp_mat AssembleStiffnessMatrix(std::set<std::shared_ptr<CIFem::DOF>>);
		void AssembleElementsInKMat(arma::sp_mat & K, arma::mat & Ke, const std::vector<std::shared_ptr<DOF>>&);
		arma::colvec GetForceVector(std::set<std::shared_ptr<DOF>>);
		arma::colvec GetDisplacementVector(std::set<std::shared_ptr<DOF>>);
		void LinEqSolve(arma::sp_mat & K, arma::colvec & a, arma::colvec & f, arma::mat & C, std::set<std::shared_ptr<DOF>>, arma::colvec & s);

		void EigenSolve(arma::sp_mat & K, arma::colvec & a, arma::colvec & f, arma::mat & C, std::set<std::shared_ptr<DOF>> spDofs, arma::colvec & s);

		void StoreResultsInDofs(arma::colvec a, arma::colvec f, std::set<std::shared_ptr<DOF>>);
		arma::mat GetCMatrix();
		void CalculateElemetForces();

	};
}

