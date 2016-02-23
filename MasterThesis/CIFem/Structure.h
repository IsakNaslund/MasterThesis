#pragma once
#include "CIFem_dll.h"
#include <vector>
#include "INode.h"
#include "IElementRcp.h"
#include "IElement.h"

namespace CIFem
{
	class CIFEM_API Structure
	{
		std::vector<INode *> _nodes;
		std::vector<IElementRcp *> _elementRcps;

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
		std::vector<IElement *> CreateElements(std::vector<IElementRcp *>, std::vector<INode *>);
		void BuildStructure();
		void SortAndIndexDofs();
		arma::sp_mat AssembleStiffnessMatrix();
		void StoreResultsInDofs(arma::colvec, arma::colvec);
	};
}

