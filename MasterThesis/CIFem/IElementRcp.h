#pragma once
#include "CIFem_dll.h"
#include "IElement.h"
#include "Node3d.h"
#include <vector>
#include "IRelease.h"
#include "ElementProperty.h"

namespace CIFem
{
	class CIFEM_API IElementRcp
	{
	public:
		virtual ~IElementRcp();

		virtual std::vector<std::shared_ptr<CIFem::IElement>> CreateElement(std::vector<std::shared_ptr<INode>> & systemNodes) = 0;
		virtual std::string & GetXSecString() = 0;

		virtual const XYZ & GetStartPos() = 0;
		virtual const XYZ & GetEndPos() = 0;
	};
}

