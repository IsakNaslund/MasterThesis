#pragma once
#include "CIFem_dll.h"
#include <vector>
#include "INode.h"
#include "IElementRcp.h"
#include "IElement.h"
#include "Plane.h"

namespace CIFem
{
	class CIFEM_API Structure
	{
		std::vector<INode *> _nodes;
		std::vector<IElementRcp *> _elementRcps;
		Plane _structureOrientation;

	public:
		Structure();
		~Structure();

		void AddNode(INode *);
		void AddNode(std::vector<INode *>);
		void AddElementRcp(IElementRcp *);
		void AddElementRcp(std::vector<IElementRcp *>);

		void Solve();

	protected:
		std::vector<CIFem::IElement *> _elements;

	private:
		std::vector<IElement *> CreateElements();
		void BuildStructure();
		std::vector<std::shared_ptr<CIFem::DOF>> GetDofs(const std::vector<INode *>, const std::vector<IElement *>);
		void SetDofKMatIndex(std::vector<std::shared_ptr<CIFem::DOF>>);
		arma::sp_mat AssembleStiffnessMatrix(std::vector<std::shared_ptr<CIFem::DOF>>);
		void AssembleElementsInKMat(arma::sp_mat & K, arma::mat & Ke, std::vector<std::shared_ptr<DOF>>);
		arma::colvec GetForceVector(std::vector<std::shared_ptr<DOF>>);
		arma::colvec GetDisplacementVector(std::vector<std::shared_ptr<DOF>>);
		void LinEqSolve(
			arma::sp_mat & K, arma::colvec & a, arma::colvec & f, arma::mat & C, std::vector<std::shared_ptr<DOF>>);
		void StoreResultsInDofs(arma::colvec a, arma::colvec f, std::vector<std::shared_ptr<DOF>>);
		arma::mat GetCMatrix(std::vector<INode *>);
	};
}

