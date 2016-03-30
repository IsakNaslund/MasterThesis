#include "SectionGroup.h"



CIFem::SectionGroup::SectionGroup()
{
}


CIFem::SectionGroup::~SectionGroup()
{
}

void CIFem::SectionGroup::Add(std::shared_ptr<CIFem::ICrossSection> crossSection)
{
	_crossSections.insert(crossSection);
}

bool CIFem::SectionGroup::UpdateCrossSection(double N, double Vy, double Vz, double My, double Mz, double T, double fu, std::shared_ptr<CIFem::ICrossSection> & updatedCrossSection)
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
