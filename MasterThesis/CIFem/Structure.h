#pragma once
#include "CIFem_dll.h"
#include <vector>
#include "INode.h"
#include "IElementRcp.h"
#include "IElement.h"
#include "DisplacementRestraint.h"

namespace CIFem
{
	class CIFEM_API Structure
	{
		std::vector<INode *> _nodes;
		std::vector<IElementRcp *> _elementRcps;
		std::vector<DisplacementRestraint> _displacementRestraints;

	public:
		Structure();
		~Structure();

		void AddNode(INode *);
		void AddNode(std::vector<INode *>);
		void AddElementRcp(IElementRcp *);
		void AddElementRcp(std::vector<IElementRcp *>);
		void AddDisplacementRestraint(DisplacementRestraint dispRest);

		void Solve();

	protected:
		std::vector<CIFem::IElement *> _elements;

	private:
		std::vector<IElement *> CreateElements(std::vector<IElementRcp *>, std::vector<INode *>);
		void BuildStructure();
		std::vector<std::shared_ptr<CIFem::DOF>> GetDofs(std::vector<INode *>);
		void SetDofKMatIndex(std::vector<std::shared_ptr<CIFem::DOF>>);
		arma::sp_mat AssembleStiffnessMatrix(std::vector<std::shared_ptr<CIFem::DOF>>);
		void AssembleElementsInKMat(arma::sp_mat & K, arma::mat & Ke, std::vector<std::shared_ptr<DOF>>);
		arma::colvec GetForceVector(std::vector<std::shared_ptr<DOF>>);
		arma::colvec GetDisplacementVector(std::vector<std::shared_ptr<DOF>>);
		void LinEqSolve(arma::sp_mat & K, arma::colvec & a, arma::colvec & f, std::vector<std::shared_ptr<DOF>>);
		void StoreResultsInDofs(arma::colvec a, arma::colvec f, std::vector<std::shared_ptr<DOF>>);
		arma::sp_mat AssembleStiffnessMatrix(std::vector<INode>, std::vector<DisplacementRestraint>);
	};
}

