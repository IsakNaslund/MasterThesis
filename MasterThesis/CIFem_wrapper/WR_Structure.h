#pragma once

#include "Structure.h"
#include "WR_INode.h"
#include "WR_IElemRcp.h"
#include "m_shared_ptr.h"
#include "WR_IElement.h"
#include "WR_Element3d.h"
#include "Spring.h"

namespace CIFem_wrapper
{
	public ref class WR_Structure
	{
		m_shared_ptr<CIFem::Structure> _structure;
	public:
		WR_Structure();
		~WR_Structure();

		void AddNode(WR_INode^ wrNode);
		//void AddNode(std::vector<WR_INode> wrNodeList);
		void AddElementRcp(WR_IElemRcp^ wrRcp);
		//void AddElementRcp(std::vector<IElementRcp *>);
		System::Collections::Generic::List<WR_IElement^>^ GetAllElements();
		System::Collections::Generic::List<WR_XYZ^>^ GetAllPoints();
		//System::Collections::Generic::List<WR_Element3d^>^ GetElements3d();

		std::shared_ptr<CIFem::Structure> GetStructure();


		double GetWeight();
		
		void SetValidForLinearSolver();
		bool IsValidForLinearSolver() { return _structure.operator std::shared_ptr<CIFem::Structure>()->IsValidForLinearCalculation(); };

		property double NodeCount {double get() { return _structure.operator std::shared_ptr<CIFem::Structure>()->NodeCount(); }}
		property double ElementCount {double get() { return _structure.operator std::shared_ptr<CIFem::Structure>()->ElementCount(); }}
		//void Solve();

		//double EigenSolve(int mode);

	private:
		
	};
}
