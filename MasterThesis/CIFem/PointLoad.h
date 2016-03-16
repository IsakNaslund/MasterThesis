#pragma once


#include "CIFem_dll.h"
#include "Vector3d.h"


namespace CIFem
{
	class CIFEM_API PointLoad
	{
		Vector3d _force;
		Vector3d _moment;
		XYZ _pos;
	public:
		PointLoad();
		PointLoad(Vector3d force, Vector3d moment, XYZ pos);
		~PointLoad();

		const XYZ & Pos() const { return _pos; }
		const Vector3d & Force() const { return _force; }
		const Vector3d & Moment() const { return _moment; }
	};

}
