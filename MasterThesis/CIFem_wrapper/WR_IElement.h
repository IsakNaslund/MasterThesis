#pragma once

#include "IElement.h"
#include "m_shared_ptr.h"

ref class WR_IElement
{
	// Keep separate references to specific element types in subclasses!
	//m_shared_ptr<CIFem::IElement> _element;

public:
	WR_IElement();

};

