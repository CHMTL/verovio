/////////////////////////////////////////////////////////////////////////////
// Name:        label.cpp
// Author:      Laurent Pugin
// Created:     19/06/2017
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#include "label.h"

//----------------------------------------------------------------------------

#include <assert.h>

//----------------------------------------------------------------------------

#include "editorial.h"
#include "text.h"
#include "vrv.h"

namespace vrv {

//----------------------------------------------------------------------------
// Label
//----------------------------------------------------------------------------

Label::Label() : Object("label-"), TextListInterface()
{
    Reset();
}

Label::~Label()
{
}

void Label::Reset()
{
    Object::Reset();
}

void Label::AddChild(Object *child)
{
    if (child->IsTextElement()) {
        assert(dynamic_cast<TextElement *>(child));
    }
    else {
        LogError("Adding '%s' to a '%s'", child->GetClassName().c_str(), this->GetClassName().c_str());
        assert(false);
    }

    child->SetParent(this);
    m_children.push_back(child);
    Modify();
}

//----------------------------------------------------------------------------
// LabelAbbr
//----------------------------------------------------------------------------

LabelAbbr::LabelAbbr() : Object("labelAbbr-"), TextListInterface()
{
    Reset();
}

LabelAbbr::~LabelAbbr()
{
}

void LabelAbbr::Reset()
{
    Object::Reset();
}

void LabelAbbr::AddChild(Object *child)
{
    if (child->IsTextElement()) {
        assert(dynamic_cast<TextElement *>(child));
    }
    else {
        LogError("Adding '%s' to a '%s'", child->GetClassName().c_str(), this->GetClassName().c_str());
        assert(false);
    }

    child->SetParent(this);
    m_children.push_back(child);
    Modify();
}

//----------------------------------------------------------------------------
// Functor methods
//----------------------------------------------------------------------------

} // namespace vrv
