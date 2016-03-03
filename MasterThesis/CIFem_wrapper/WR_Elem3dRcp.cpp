#include "stdafx.h"
#include "WR_Elem3dRcp.h"

using namespace CIFem_wrapper;

CIFem_wrapper::WR_Elem3dRcp::WR_Elem3dRcp(Element3dRcp elem)
{
	_eleRcp = gcnew m_shared_ptr<CIFem::Element3dRcp>(&elem);
}

CIFem_wrapper::WR_Elem3dRcp::WR_Elem3dRcp(std::shared_ptr<Element3dRcp> elem)
{
	_eleRcp = gcnew m_shared_ptr<CIFem::Element3dRcp>(elem);
}

WR_Elem3dRcp::WR_Elem3dRcp()
{
	_eleRcp = gcnew m_shared_ptr<CIFem::Element3dRcp>();
}

WR_Elem3dRcp::~WR_Elem3dRcp()
{

}

WR_Elem3dRcp::WR_Elem3dRcp(XYZ stPos, XYZ enPos, ReleaseBeam3d stRel, ReleaseBeam3d enRel, std::shared_ptr<ICrossSection> xSec, double matStiff, double poisonRatio, std::vector<double> normal)
{
	_eleRcp = gcnew m_shared_ptr<CIFem::Element3dRcp>(new Element3dRcp( stPos,  enPos,  stRel,  enRel,  xSec,  matStiff,  poisonRatio,  normal));
}

CIFem_wrapper::WR_Elem3dRcp::WR_Elem3dRcp(WR_XYZ^ stPos, WR_XYZ^ enPos, WR_ReleaseBeam3d^ stRel, WR_ReleaseBeam3d^ enRel, WR_IXSec^ xSec, double matStiff, double poisonRatio, WR_Vector^ normal)
{
	_eleRcp = gcnew m_shared_ptr<CIFem::Element3dRcp>(new Element3dRcp(*stPos->GetPos(), *enPos->GetPos(), *stRel->GetRelease(), *enRel->GetRelease(), xSec->GetCrossSection(), matStiff, poisonRatio, normal->GetAsCppVector()));
}

CIFem_wrapper::WR_Elem3dRcp::WR_Elem3dRcp(WR_XYZ ^ stPos, WR_XYZ ^ enPos, WR_ReleaseBeam3d ^ stRel, WR_ReleaseBeam3d ^ enRel, WR_IXSec ^ xSec, WR_Material ^ mat, WR_Vector ^ normal)
{
	_eleRcp = gcnew m_shared_ptr<CIFem::Element3dRcp>(new Element3dRcp(*stPos->GetPos(), *enPos->GetPos(), *stRel->GetRelease(), *enRel->GetRelease(), xSec->GetCrossSection(), *mat->GetMaterial(), normal->GetAsCppVector()));
}

WR_Elem3dRcp^ CIFem_wrapper::WR_Elem3dRcp::Copy()
{
	return gcnew WR_Elem3dRcp(std::shared_ptr<Element3dRcp>(new Element3dRcp(*_eleRcp.share())));
}

std::shared_ptr<CIFem::IElementRcp> CIFem_wrapper::WR_Elem3dRcp::GetRecipe()
{
	return *_eleRcp.share();
}


