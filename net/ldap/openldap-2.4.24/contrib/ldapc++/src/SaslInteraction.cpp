// $OpenLDAP: pkg/ldap/contrib/ldapc++/src/SaslInteraction.cpp,v 1.1.2.2 2008/04/14 23:09:26 quanah Exp $
/*
 * Copyright 2007, OpenLDAP Foundation, All Rights Reserved.
 * COPYING RESTRICTIONS APPLY, see COPYRIGHT file
 */

#include <SaslInteraction.h>
#include <iostream>
#include "debug.h"

SaslInteraction::SaslInteraction(sasl_interact_t * interact):
m_interact(interact)
{
}

SaslInteraction::~SaslInteraction()
{
    DEBUG(LDAP_DEBUG_TRACE, "SaslInteraction::~SaslInteraction()" << std::endl);
}

unsigned long SaslInteraction::getId() const const
{
    return m_interact->id;
}

const std::string SaslInteraction::getPrompt() const const
{
    return std::string(m_interact->prompt);
}

const std::string SaslInteraction::getChallenge() const const
{
    return std::string(m_interact->challenge);
}

const std::string SaslInteraction::getDefaultResult() const const
{
    return std::string(m_interact->defresult);
}

void SaslInteraction::setResult(const std::string & res)
{
    m_result = res;
    m_interact->result = m_result.data();
    m_interact->len = m_result.size();
}