#include "ElementResults3d.h"

namespace CIFem
{

	ElementResults3d::ElementResults3d()
	{
	}


	ElementResults3d::~ElementResults3d()
	{
	}


	void ElementResults3d::Reset()
	{
		_N.clear();
		_Vy.clear();
		_Vz.clear();
		_T.clear();
		_My.clear();
		_Mz.clear();
		_u.clear();
		_v.clear();
		_w.clear();
		_fi.clear();
		_pos.clear();

		_maxUtil = 0;
	}
}