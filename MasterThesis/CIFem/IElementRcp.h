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

		virtual std::vector<IElement*> CreateElement(std::vector<INode*> & systemNodes) = 0;
	};
}

