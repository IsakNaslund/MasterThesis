#pragma once

#include "CIFem_dll.h"
#include "XYZ.h"
#include <vector>
#include <memory>
#include "DOF.h"
#include "Restraint.h"



namespace CIFem
{
	class CIFEM_API INode
	{
	public:
		virtual ~INode() {};

		virtual double DistanceTo(const INode* other) const = 0;
		virtual std::vector<std::shared_ptr<DOF> > GetDofs() = 0;
		virtual std::vector<std::shared_ptr<DOF> > GetTranslationDofs() = 0;
		virtual std::vector<std::shared_ptr<DOF> > GetRotationDofs() = 0;
		virtual double DistanceTo(const XYZ other) const;

		virtual bool GetNodeCMatrix(Plane, arma::mat &) { return false; };
	};

}

