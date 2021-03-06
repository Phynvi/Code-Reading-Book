//
// interceptors_sh.cpp,v 1.12 2001/04/03 18:05:55 coryan Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    operation_interceptors_sh.cpp
//
// = DESCRIPTION
//    Visitor generating code for Operation node in the server header.
//
// = AUTHOR
//    Kirthika Parameswaran  <kirthika@cs.wustl.edu>
//
// ============================================================================

#include        "idl.h"
#include        "idl_extern.h"
#include        "be.h"

#include "be_visitor_operation.h"

ACE_RCSID(be_visitor_operation, operation_interceptors_sh, "interceptors_sh.cpp,v 1.12 2001/04/03 18:05:55 coryan Exp")


  // ******************************************************
  // primary visitor for "operation" in server header
  // ******************************************************

  be_visitor_operation_interceptors_sh::be_visitor_operation_interceptors_sh (be_visitor_context *ctx)
    : be_visitor_operation (ctx)
{
}

be_visitor_operation_interceptors_sh::~be_visitor_operation_interceptors_sh (void)
{
}

int
be_visitor_operation_interceptors_sh::visit_operation (be_operation *)
{
  return 0;
}
