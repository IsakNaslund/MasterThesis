#include "Element3dState.h"



CIFem::Element3dState::Element3dState()
{
}

CIFem::Element3dState::Element3dState(std::shared_ptr<Material> mat, Vector3d eo, std::shared_ptr<ICrossSection> crossSec)
{
	_mat = mat;
	_eo = eo;
	_crossSection = crossSec;
}


CIFem::Element3dState::~Element3dState()
{
}
