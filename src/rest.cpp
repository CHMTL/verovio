/////////////////////////////////////////////////////////////////////////////
// Name:        rest.cpp
// Author:      Laurent Pugin
// Created:     2011
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#include "rest.h"

namespace vrv {

//----------------------------------------------------------------------------
// Rest
//----------------------------------------------------------------------------

Rest::Rest() : LayerElement("rest-"), DurationInterface(), PositionInterface(), AttColor()
    // , AttRestVisMensural()
{
    RegisterInterface(DurationInterface::GetAttClasses(), DurationInterface::IsInterface());
    RegisterInterface(PositionInterface::GetAttClasses(), PositionInterface::IsInterface());
    RegisterAttClass(ATT_COLOR);
    //RegisterAttClass(ATT_RESTVISMENSURAL);
    Reset();
}

Rest::~Rest()
{
}

void Rest::Reset()
{
    LayerElement::Reset();
    DurationInterface::Reset();
    PositionInterface::Reset();
    ResetColor();
}

} // namespace vrv
