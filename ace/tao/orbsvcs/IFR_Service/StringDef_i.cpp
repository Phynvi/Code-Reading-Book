/* -*- C++ -*- */
// StringDef_i.cpp,v 1.4 2001/03/30 16:43:24 parsons Exp

#include "Repository_i.h"
#include "StringDef_i.h"

ACE_RCSID(IFR_Service, StringDef_i, "StringDef_i.cpp,v 1.4 2001/03/30 16:43:24 parsons Exp")

TAO_StringDef_i::TAO_StringDef_i (TAO_Repository_i *repo,
                                  ACE_Configuration_Section_Key section_key)
  : TAO_IRObject_i (repo, section_key),
    TAO_IDLType_i (repo, section_key)
{
}

TAO_StringDef_i::~TAO_StringDef_i (void)
{
}

CORBA::DefinitionKind
TAO_StringDef_i::def_kind (CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  return CORBA::dk_String;
}

void 
TAO_StringDef_i::destroy (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  TAO_IFR_WRITE_GUARD;

  this->destroy_i (ACE_TRY_ENV);
}

void 
TAO_StringDef_i::destroy_i (CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_TString name;
  this->repo_->config ()->get_string_value (this->section_key_,
                                            "name",
                                            name);

  this->repo_->config ()->remove_section (this->repo_->strings_key (),
                                          name.c_str (),
                                          0);
}

CORBA::TypeCode_ptr 
TAO_StringDef_i::type (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  TAO_IFR_READ_GUARD_RETURN (CORBA::TypeCode::_nil ());

  return this->type_i (ACE_TRY_ENV);
}

CORBA::TypeCode_ptr 
TAO_StringDef_i::type_i (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  CORBA::ULong bound = this->bound_i (ACE_TRY_ENV);
  ACE_CHECK_RETURN (CORBA::TypeCode::_nil ());

  return this->repo_->tc_factory ()->create_string_tc (
                                         bound,
                                         ACE_TRY_ENV
                                       );
}

CORBA::ULong 
TAO_StringDef_i::bound (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  TAO_IFR_READ_GUARD_RETURN (0);

  return this->bound_i (ACE_TRY_ENV);
}

CORBA::ULong 
TAO_StringDef_i::bound_i (CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  u_int retval = 0;
  this->repo_->config ()->get_integer_value (this->section_key_,
                                             "bound",
                                             retval);

  return ACE_static_cast (CORBA::ULong, retval);
}

void 
TAO_StringDef_i::bound (CORBA::ULong bound,
                        CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  TAO_IFR_WRITE_GUARD;

  this->bound_i (bound,
                 ACE_TRY_ENV);
}

void 
TAO_StringDef_i::bound_i (CORBA::ULong bound,
                          CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  this->repo_->config ()->set_integer_value (this->section_key_,
                                             "bound",
                                             bound);
}

