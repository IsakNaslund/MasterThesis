#include "LoadCombination.h"


CIFem::LoadCombination::LoadCombination(std::string name)
{
	_name = name;
	_gravityOn = false;
	_gravField = Vector3d(0, 0, 0);
}

CIFem::LoadCombination::LoadCombination(std::string name, Vector3d gravField)
{
	_name = name;
	_gravityOn = true;
	_gravField = gravField;
}

CIFem::LoadCombination::LoadCombination(std::string name, bool gravityOn)
{
	_name = name;
	_gravityOn = gravityOn;
	if (_gravityOn)
		_gravField = Vector3d(0, 0, -9.82);
	else
		_gravField = Vector3d(0, 0, 0);
}

CIFem::LoadCombination::~LoadCombination()
{
}

void CIFem::LoadCombination::AddPointLoad(CIFem::PointLoad ptL)
{
	_pointLoads.push_back(ptL);
}

void CIFem::LoadCombination::AddPointLoad(Vector3d force, Vector3d moment, XYZ pos)
{
	_pointLoads.push_back(PointLoad(force, moment, pos));
}

void CIFem::LoadCombination::SetGravity(Vector3d gravField)
{
	_gravityOn = true;
	_gravField = gravField;
}

void CIFem::LoadCombination::SetGravity(bool gravityOn)
{
	_gravityOn = gravityOn;
	if (_gravityOn)
		_gravField = Vector3d(0, 0, -9.82);
	else
		_gravField = Vector3d(0, 0, 0);
}
