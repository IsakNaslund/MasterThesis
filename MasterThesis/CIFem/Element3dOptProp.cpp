#include "Element3dOptProp.h"



CIFem::Element3dOptProp::Element3dOptProp() : Element3dOptProp(Element3dChecks::BasicCheck())
{
}

CIFem::Element3dOptProp::Element3dOptProp(Element3dChecks checks) : Element3dOptProp(checks, false)
{
}

CIFem::Element3dOptProp::Element3dOptProp(bool allowRotation) : Element3dOptProp(Element3dChecks::BasicCheck(), allowRotation)
{
}

CIFem::Element3dOptProp::Element3dOptProp(Element3dChecks checks, bool allowRotation) : Element3dOptProp(checks, allowRotation, 0)
{
}

CIFem::Element3dOptProp::Element3dOptProp(bool allowRotation, int changeType) : Element3dOptProp(Element3dChecks::BasicCheck(), allowRotation, changeType)
{
}

CIFem::Element3dOptProp::Element3dOptProp(Element3dChecks checks, bool allowRotation, int changeType) : Element3dOptProp(checks, allowRotation, changeType, 0.7, 1)
{
}

CIFem::Element3dOptProp::Element3dOptProp(bool allowRotation, int changeType, double minUtil, double maxUtil):Element3dOptProp(Element3dChecks::BasicCheck(), allowRotation, changeType, minUtil, maxUtil)
{
}

CIFem::Element3dOptProp::Element3dOptProp(Element3dChecks checks, bool allowRotation, int changeType, double minUtil, double maxUtil)
{
	if (changeType > 4)
		changeType = 0;

	_checks = checks;
	_allowRotation = allowRotation;
	_sectionChangeType = (SectionChangeType)changeType;
	_minUtil = minUtil;
	_maxUtil = maxUtil;
}

CIFem::Element3dOptProp::~Element3dOptProp()
{
}

void CIFem::Element3dOptProp::Add(std::shared_ptr<CIFem::ICrossSection> crossSection)
{
	_crossSections.insert(crossSection);
}


bool CIFem::Element3dOptProp::UpdateCrossSection(std::shared_ptr<Material> mat, ElementResults3d & results, std::shared_ptr<CIFem::ICrossSection> & updatedCrossSection, bool overUtilized)
{
	switch (_sectionChangeType)
	{
	case CIFem::Element3dOptProp::CheckAll:
		return UpdateCrossSectionCheckAll(mat, results, updatedCrossSection);
	case CIFem::Element3dOptProp::CheckClose:
		return UpdateCrossSectionClosePosition(mat, results, updatedCrossSection);
	case CIFem::Element3dOptProp::StepUpOne:
		return UpdateCrossSectionStepOne(updatedCrossSection, overUtilized);
	case CIFem::Element3dOptProp::CheckAllFromClose:
		return UpdateCrossSectionCheckAllClose(mat, results, updatedCrossSection, overUtilized);
	default:
		break;
	}
	return false;
}


bool CIFem::Element3dOptProp::UpdateCrossSectionCheckAllClose(std::shared_ptr<Material> mat, ElementResults3d & results, std::shared_ptr<CIFem::ICrossSection>& updatedCrossSection, bool overUtilized)
{
	std::set<std::shared_ptr<CIFem::ICrossSection>>::iterator iter = _crossSections.lower_bound(updatedCrossSection);
	int n = 0;

	if (overUtilized)
	{
		while (!is_last(iter, _crossSections) & !_checks.CheckUtilUntilFail(*iter, mat, results))
		{
			iter++;
			n++;
		}
		updatedCrossSection = *iter;
	}
	else
	{
		while (iter!=_crossSections.begin() && _checks.CheckUtilUntilFail(*iter, mat, results))
		{
			iter--;
			n--;
		}

		iter++;
		n++;
		updatedCrossSection = *iter;
	}
	return n != 0;
}

bool CIFem::Element3dOptProp::UpdateCrossSectionCheckAll(std::shared_ptr<Material> mat, ElementResults3d & results, std::shared_ptr<CIFem::ICrossSection>& updatedCrossSection)
{
	for each (std::shared_ptr<CIFem::ICrossSection> xSec in _crossSections)
	{
		if (_checks.CheckUtilUntilFail(xSec, mat, results))
		{
			updatedCrossSection = xSec;
			return true;
		}
	}
	//No found that holds.Sets to last in set, assumeing thats the strongest one, which ofc is not neccecary true...
	updatedCrossSection = *_crossSections.rbegin();

	return false;
}

bool CIFem::Element3dOptProp::UpdateCrossSectionClosePosition(std::shared_ptr<Material> mat, ElementResults3d & results, std::shared_ptr<CIFem::ICrossSection>& updatedCrossSection)
{
	std::set<std::shared_ptr<CIFem::ICrossSection>>::iterator iter = _crossSections.lower_bound(updatedCrossSection);
	if(iter!=_crossSections.begin())
		iter--;
	int n = 0;

	while (n < 2)
	{
		if (_checks.CheckUtilUntilFail(*iter, mat, results))
		{
			updatedCrossSection = *iter;
			if (n == 1)
				return false;
			else
				return true;
		}

		n++;

		iter++;
		if (iter == _crossSections.end())
		{
			iter--;
			break;
		}
	}

	updatedCrossSection = *iter;

	return true;
}

bool CIFem::Element3dOptProp::UpdateCrossSectionStepOne(std::shared_ptr<CIFem::ICrossSection>& updatedCrossSection, bool overUtilizaed)
{
	if (!overUtilizaed)
		return false;

	//Step to next section in the sectionlist
	std::set<std::shared_ptr<CIFem::ICrossSection>>::iterator iter = _crossSections.lower_bound(updatedCrossSection);
	
	if(!is_last(iter, _crossSections))
		iter++;

	updatedCrossSection = *iter;
	return true;
}

bool CIFem::Element3dOptProp::UpdateCrossSection(std::shared_ptr<Material> mat, ElementResults3d & results, std::shared_ptr<CIFem::ICrossSection>& updatedCrossSection, std::string loadCase)
{
	for each (std::shared_ptr<CIFem::ICrossSection> xSec in _crossSections)
	{
		if (_checks.CheckUtilUntilFail(xSec, mat, results, loadCase))
		{
			updatedCrossSection = xSec;
			return true;
		}
	}
	//No found that holds.Sets to last in set, assumeing thats the strongest one, which ofc is not neccecary true...
	updatedCrossSection = *_crossSections.rbegin();

	return false;
}

bool CIFem::Element3dOptProp::UpdateCrossSection(double N, double Vy, double Vz, double My, double Mz, double T, double fu, std::shared_ptr<CIFem::ICrossSection> & updatedCrossSection)
{
	for each (std::shared_ptr<CIFem::ICrossSection> xSec in _crossSections)
	{
		if (abs(N) > xSec->_Nmax*fu)
			continue;
		if (abs(Vy) > xSec->_Vymax*fu)
			continue;
		if (abs(Vz) > xSec->_Vzmax*fu)
			continue;
		if (abs(My) > xSec->_Mymax*fu)
			continue;
		if (abs(Mz) > xSec->_Mzmax*fu)
			continue;
		
		if (fu < xSec->CheckCombAxialBending(N, My, Mz))
			continue;

		updatedCrossSection = xSec;
		return true;
	}

	//No found that holds.Sets to last in set, assumeing thats the strongest one, which ofc probably is not true...
	updatedCrossSection = *_crossSections.rbegin();

	return false;
}
