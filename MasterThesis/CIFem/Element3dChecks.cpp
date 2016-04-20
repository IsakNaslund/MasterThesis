#include "Element3dChecks.h"



CIFem::Element3dChecks::Element3dChecks()
{
}


CIFem::Element3dChecks::~Element3dChecks()
{
}

void CIFem::Element3dChecks::AddCheck(std::shared_ptr<IUtilCheck3d> check)
{
	_checks.push_back(check);
}

void CIFem::Element3dChecks::CheckElementUtilisations(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results, std::string resName)
{
	for (int i = 0; i < results.Utilisations()[resName].size(); i++)
	{
		for each (std::shared_ptr<IUtilCheck3d> check in _checks)
		{
			// Do checks, update element utilisation
			results._util[resName].Update(check->CheckElementUtilisations(xSec, mat, results, resName, i), check->_checkName, i);
		}
	}
}

bool CIFem::Element3dChecks::CheckUtilUntilFail(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results)
{
	//This could be done better.Maybe save the highest sectional forces and use them only to do the check?
	for each (std::pair<std::string, std::vector<double>> pair in results.N())
	{
		for each (std::shared_ptr<IUtilCheck3d> check in _checks)
		{
			for (int i = 0; i < results.Utilisations()[pair.first].size(); i++)
			{
				if (abs(check->CheckElementUtilisations(xSec, mat, results, pair.first, i)) > 1)
					return false;
			}
		}
	}

	return true;
}

CIFem::Element3dChecks CIFem::Element3dChecks::BasicCheck()
{
	Element3dChecks check;
	check.AddCheck(std::shared_ptr<IUtilCheck3d>(new AxialCheck()));
	check.AddCheck(std::shared_ptr<IUtilCheck3d>(new CombAxialBendingCheck));
	check.AddCheck(std::shared_ptr<IUtilCheck3d>(new ShearYCheck()));
	check.AddCheck(std::shared_ptr<IUtilCheck3d>(new ShearZCheck()));
	return check;
}

std::shared_ptr<CIFem::Element3dChecks> CIFem::Element3dChecks::BasicCheckSharedPtr()
{
	std::shared_ptr<CIFem::Element3dChecks> check(new Element3dChecks());
	check->AddCheck(std::shared_ptr<IUtilCheck3d>(new AxialCheck()));
	check->AddCheck(std::shared_ptr<IUtilCheck3d>(new CombAxialBendingCheck));
	check->AddCheck(std::shared_ptr<IUtilCheck3d>(new ShearYCheck()));
	check->AddCheck(std::shared_ptr<IUtilCheck3d>(new ShearZCheck()));
	return check;
}
