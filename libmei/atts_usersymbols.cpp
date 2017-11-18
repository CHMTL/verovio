/////////////////////////////////////////////////////////////////////////////
// Authors:     Laurent Pugin and Rodolfo Zitellini
// Created:     2014
// Copyright (c) Authors and others. All rights reserved.
//
// Code generated using a modified version of libmei
// by Andrew Hankinson, Alastair Porter, and Others
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// NOTE: this file was generated with the Verovio libmei version and
// should not be edited because changes will be lost.
/////////////////////////////////////////////////////////////////////////////

#include "atts_usersymbols.h"

//----------------------------------------------------------------------------

#include <assert.h>

//----------------------------------------------------------------------------

#include "object.h"

/* #include_block */

namespace vrv {

//----------------------------------------------------------------------------
// AttAltSym
//----------------------------------------------------------------------------

AttAltSym::AttAltSym() : Att()
{
    ResetAltSym();
}

AttAltSym::~AttAltSym()
{
}

void AttAltSym::ResetAltSym()
{
    m_altsym = "";
}

bool AttAltSym::ReadAltSym(pugi::xml_node element)
{
    bool hasAttribute = false;
    if (element.attribute("altsym")) {
        this->SetAltsym(StrToStr(element.attribute("altsym").value()));
        element.remove_attribute("altsym");
        hasAttribute = true;
    }
    return hasAttribute;
}

bool AttAltSym::WriteAltSym(pugi::xml_node element)
{
    bool wroteAttribute = false;
    if (this->HasAltsym()) {
        element.append_attribute("altsym") = StrToStr(this->GetAltsym()).c_str();
        wroteAttribute = true;
    }
    return wroteAttribute;
}

bool AttAltSym::HasAltsym() const
{
    return (m_altsym != "");
}

/* include <attaltsym> */

bool Att::SetUsersymbols(Object *element, std::string attrType, std::string attrValue)
{
    if (element->HasAttClass(ATT_ALTSYM)) {
        AttAltSym *att = dynamic_cast<AttAltSym *>(element);
        assert(att);
        if (attrType == "altsym") {
            att->SetAltsym(att->StrToStr(attrValue));
            return true;
        }
    }

    return false;
}

void Att::GetUsersymbols(const Object *element, ArrayOfStrAttr *attributes)
{
    if (element->HasAttClass(ATT_ALTSYM)) {
        const AttAltSym *att = dynamic_cast<const AttAltSym *>(element);
        assert(att);
        if (att->HasAltsym()) {
            attributes->push_back(std::make_pair("altsym", att->StrToStr(att->GetAltsym())));
        }
    }
}

} // vrv namespace
