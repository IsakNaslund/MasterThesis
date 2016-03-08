#pragma once

#include "WR_XYZ.h"
#include "IElement.h"
#include "m_shared_ptr.h"

public ref class WR_IElement
{
	// Keep separate references to specific element types in subclasses!
	//m_shared_ptr<CIFem::IElement> _element;

public:
	WR_IElement();
	WR_IElement(std::shared_ptr<CIFem::IElement> const& element);
};

