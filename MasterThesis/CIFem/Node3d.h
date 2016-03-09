#pragma once

#include "XYZ.h"
#include "CIFem_dll.h"
#include "DOF.h"
#include <memory>
#include <vector>
#include "INode.h"

namespace CIFem
{
	class CIFEM_API Node3d : public INode
	{
		XYZ _location;
		std::vector<std::shared_ptr<DOF>> _dof;
		Restraint _restraint;
		Vector3d _ptLoad, _ptMoment;
		

	public:
		Node3d();
		Node3d(const XYZ location);
		Node3d(const XYZ location, unsigned int startindex);
		Node3d(const XYZ location, Restraint restraint);
		Node3d(const XYZ location, Vector3d pointLoad, Vector3d pointMoment);
		Node3d(const XYZ location, Restraint restraint, Vector3d pointLoad, Vector3d pointMoment);
		~Node3d();

		std::vector<std::shared_ptr<DOF>> GetDofs();
		std::vector<std::shared_ptr<DOF>> GetTranslationDofs();
		std::vector<std::shared_ptr<DOF>> GetRotationDofs();

		double DistanceTo(const Node3d* other) const;
		double DistanceTo(const INode* other) const;
		double DistanceTo(const XYZ& otherPt) const;

		virtual bool GetNodeCMatrix(Plane, arma::mat &);

		void ApplyPointLoads();

	private:
		void InitNewDofs(int);
		void SetRestraint(Restraint r);
	};

}

