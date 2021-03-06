/////////////////////////////////////////////////////////////////////////////
// Name:        section.h
// Author:      Laurent Pugin
// Created:     24/08/2016
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#include "section.h"

//----------------------------------------------------------------------------

#include <assert.h>

//----------------------------------------------------------------------------

#include "doc.h"
#include "editorial.h"
#include "ending.h"
#include "functorparams.h"
#include "measure.h"
#include "page.h"
#include "scoredef.h"
#include "system.h"
#include "vrv.h"

namespace vrv {

//----------------------------------------------------------------------------
// Section
//----------------------------------------------------------------------------

Section::Section() : SystemElement("section-"), BoundaryStartInterface(), AttNNumberLike()
{
    RegisterAttClass(ATT_NNUMBERLIKE);

    Reset();
}

Section::~Section()
{
}

void Section::Reset()
{
    SystemElement::Reset();
    BoundaryStartInterface::Reset();
    ResetNNumberLike();
}

void Section::AddChild(Object *child)
{
    if (child->Is(MEASURE)) {
        assert(dynamic_cast<Measure *>(child));
    }
    else if (child->Is(SCOREDEF)) {
        assert(dynamic_cast<ScoreDef *>(child));
    }
    else if (child->IsSystemElement()) {
        assert(dynamic_cast<SystemElement *>(child));
    }
    else if (child->IsEditorialElement()) {
        assert(dynamic_cast<EditorialElement *>(child));
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
// Pb
//----------------------------------------------------------------------------

Pb::Pb() : SystemElement("pb-"), AttNNumberLike()
{
    RegisterAttClass(ATT_NNUMBERLIKE);

    Reset();
}

Pb::~Pb()
{
}

void Pb::Reset()
{
    SystemElement::Reset();
    ResetNNumberLike();
}

//----------------------------------------------------------------------------
// Sb
//----------------------------------------------------------------------------

Sb::Sb() : SystemElement("sb-"), AttNNumberLike()
{
    RegisterAttClass(ATT_NNUMBERLIKE);

    Reset();
}

Sb::~Sb()
{
}

void Sb::Reset()
{
    SystemElement::Reset();
    ResetNNumberLike();
}

//----------------------------------------------------------------------------
// Section functor methods
//----------------------------------------------------------------------------

int Section::ConvertToPageBased(FunctorParams *functorParams)
{
    ConvertToPageBasedParams *params = dynamic_cast<ConvertToPageBasedParams *>(functorParams);
    assert(params);

    this->MoveItselfTo(params->m_pageBasedSystem);

    return FUNCTOR_CONTINUE;
}

int Section::ConvertToPageBasedEnd(FunctorParams *functorParams)
{
    ConvertToPageBasedParams *params = dynamic_cast<ConvertToPageBasedParams *>(functorParams);
    assert(params);

    ConvertToPageBasedBoundary(this, params->m_pageBasedSystem);

    return FUNCTOR_CONTINUE;
}

int Section::PrepareBoundaries(FunctorParams *functorParams)
{
    if (this->IsBoundary()) {
        this->BoundaryStartInterface::InterfacePrepareBoundaries(functorParams);
    }

    return FUNCTOR_CONTINUE;
}

int Section::ResetDrawing(FunctorParams *functorParams)
{
    FloatingObject::ResetDrawing(functorParams);

    if (this->IsBoundary()) {
        this->BoundaryStartInterface::InterfaceResetDrawing(functorParams);
    }

    return FUNCTOR_CONTINUE;
};

//----------------------------------------------------------------------------
// Pb functor methods
//----------------------------------------------------------------------------

int Pb::CastOffEncoding(FunctorParams *functorParams)
{
    CastOffEncodingParams *params = dynamic_cast<CastOffEncodingParams *>(functorParams);
    assert(params);

    if (!params->m_firstPbProcessed) {
        params->m_firstPbProcessed = true;
    }
    else {
        params->m_currentPage = new Page();
        params->m_doc->AddChild(params->m_currentPage);
        params->m_currentSystem = new System();
        params->m_currentPage->AddChild(params->m_currentSystem);
    }

    MoveItselfTo(params->m_currentSystem);

    return FUNCTOR_SIBLINGS;
}

//----------------------------------------------------------------------------
// Sb functor methods
//----------------------------------------------------------------------------

int Sb::CastOffEncoding(FunctorParams *functorParams)
{
    CastOffEncodingParams *params = dynamic_cast<CastOffEncodingParams *>(functorParams);
    assert(params);

    params->m_currentSystem = new System();
    params->m_currentPage->AddChild(params->m_currentSystem);

    MoveItselfTo(params->m_currentSystem);

    return FUNCTOR_SIBLINGS;
}

} // namespace vrv
