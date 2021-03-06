/* -*- c++ -*- */
// be_constant.h,v 1.11 2000/09/20 21:09:16 parsons Exp

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    be_constant.h
//
// = DESCRIPTION
//    Extension of class AST_Constant that provides additional means for C++
//    mapping.
//
// = AUTHOR
//    Copyright 1994-1995 by Sun Microsystems, Inc.
//    and
//    Aniruddha Gokhale
//
// ============================================================================

#ifndef BE_CONSTANT_H
#define BE_CONSTANT_H

#include "be_decl.h"
#include "ast_constant.h"
#include "ast_expression.h"

class UTL_StrList;
class be_visitor;

class be_constant : public virtual AST_Constant, 
                    public virtual be_decl
{
public:
  be_constant (void);
  // Constructor.

  be_constant (AST_Expression::ExprType et,
               AST_Expression *v,
               UTL_ScopedName *n,
               UTL_StrList *p);
  // Constructor.

  const char *exprtype_to_string (void);
  // Returns the appropriate type.

  // Visiting.
  virtual int accept (be_visitor *visitor);

  // Narrowing.
  DEF_NARROW_METHODS2 (be_constant, AST_Constant, be_decl);
  DEF_NARROW_FROM_DECL (be_constant);

};

#endif // if !defined
