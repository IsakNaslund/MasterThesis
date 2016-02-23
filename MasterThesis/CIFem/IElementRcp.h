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
		IElementRcp(Node3d, Node3d, std::vector<IRelease>, std::vector<IRelease>, ElementProperty);
		~IElementRcp();

		virtual IElement* CreateElement() = 0;
	};
}

