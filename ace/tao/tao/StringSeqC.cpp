// -*- C++ -*-
//
// StringSeqC.cpp,v 1.7 2001/03/07 07:49:42 othman Exp

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

#include "StringSeqC.h"

#if defined (__BORLANDC__)
#pragma option -w-rvl -w-rch -w-ccc -w-aus
#endif /* __BORLANDC__ */

#if !defined (__ACE_INLINE__)
#include "StringSeqC.i"
#endif /* !defined INLINE */

#include "Any.h"
#include "CDR.h"
#include "Typecode.h"

#if !defined (_CORBA_STRINGSEQ_CS_)
#define _CORBA_STRINGSEQ_CS_

// *************************************************************
// CORBA::StringSeq
// *************************************************************

CORBA_StringSeq::CORBA_StringSeq (void)
{}
CORBA_StringSeq::CORBA_StringSeq (CORBA::ULong max) // uses max size
  :
#if !defined (TAO_USE_SEQUENCE_TEMPLATES)
  TAO_Unbounded_String_Sequence
#else /* TAO_USE_SEQUENCE_TEMPLATES */
  TAO_Unbounded_String_Sequence
#endif /* !TAO_USE_SEQUENCE_TEMPLATES */
 (max)
{}
CORBA_StringSeq::CORBA_StringSeq (CORBA::ULong max, CORBA::ULong length, char * *buffer, CORBA::Boolean release)
  :
#if !defined (TAO_USE_SEQUENCE_TEMPLATES)
  TAO_Unbounded_String_Sequence
#else /* TAO_USE_SEQUENCE_TEMPLATES */
  TAO_Unbounded_String_Sequence
#endif /* !TAO_USE_SEQUENCE_TEMPLATES */
 (max, length, buffer, release)
{}
CORBA_StringSeq::CORBA_StringSeq (const CORBA_StringSeq &seq) // copy ctor
  :
#if !defined (TAO_USE_SEQUENCE_TEMPLATES)
  TAO_Unbounded_String_Sequence
#else /* TAO_USE_SEQUENCE_TEMPLATES */
  TAO_Unbounded_String_Sequence
#endif /* !TAO_USE_SEQUENCE_TEMPLATES */
 (seq)
{}
CORBA_StringSeq::~CORBA_StringSeq (void) // dtor
{}
void CORBA_StringSeq::_tao_any_destructor (void *x)
{
  CORBA_StringSeq *tmp = ACE_static_cast (CORBA_StringSeq*,x);
  delete tmp;
}


#endif /* end #if !defined */

static const CORBA::Long _oc_CORBA_StringSeq[] =
{
  TAO_ENCAP_BYTE_ORDER, // byte order
  32, ACE_NTOHL (0x49444c3a), ACE_NTOHL (0x6f6d672e), ACE_NTOHL (0x6f72672f), ACE_NTOHL (0x434f5242), ACE_NTOHL (0x412f5374), ACE_NTOHL (0x72696e67), ACE_NTOHL (0x5365713a), ACE_NTOHL (0x312e3000),  // repository ID = IDL:omg.org/CORBA/StringSeq:1.0
  10, ACE_NTOHL (0x53747269), ACE_NTOHL (0x6e675365), ACE_NTOHL (0x71000000),  // name = StringSeq
  CORBA::tk_sequence, // typecode kind
  16, // encapsulation length
    TAO_ENCAP_BYTE_ORDER, // byte order
    CORBA::tk_string,
    0U, // string length
    0U,

};
static CORBA::TypeCode _tc_TAO_tc_CORBA_StringSeq (CORBA::tk_alias, sizeof (_oc_CORBA_StringSeq), (char *) &_oc_CORBA_StringSeq, 0, sizeof (CORBA_StringSeq));
TAO_NAMESPACE_TYPE (CORBA::TypeCode_ptr)
TAO_NAMESPACE_BEGIN (CORBA)
TAO_NAMESPACE_DEFINE (CORBA::TypeCode_ptr, _tc_StringSeq, &_tc_TAO_tc_CORBA_StringSeq)
TAO_NAMESPACE_END

#if !defined (_CORBA_WSTRINGSEQ_CS_)
#define _CORBA_WSTRINGSEQ_CS_

// *************************************************************
// CORBA::WStringSeq
// *************************************************************

CORBA_WStringSeq::CORBA_WStringSeq (void)
{}
CORBA_WStringSeq::CORBA_WStringSeq (CORBA::ULong max) // uses max size
  :
#if !defined (TAO_USE_SEQUENCE_TEMPLATES)
  TAO_Unbounded_WString_Sequence
#else /* TAO_USE_SEQUENCE_TEMPLATES */
  TAO_Unbounded_WString_Sequence
#endif /* !TAO_USE_SEQUENCE_TEMPLATES */
 (max)
{}
CORBA_WStringSeq::CORBA_WStringSeq (CORBA::ULong max, CORBA::ULong length, CORBA::WChar * *buffer, CORBA::Boolean release)
  :
#if !defined (TAO_USE_SEQUENCE_TEMPLATES)
  TAO_Unbounded_WString_Sequence
#else /* TAO_USE_SEQUENCE_TEMPLATES */
  TAO_Unbounded_WString_Sequence
#endif /* !TAO_USE_SEQUENCE_TEMPLATES */
 (max, length, buffer, release)
{}
CORBA_WStringSeq::CORBA_WStringSeq (const CORBA_WStringSeq &seq) // copy ctor
  :
#if !defined (TAO_USE_SEQUENCE_TEMPLATES)
  TAO_Unbounded_WString_Sequence
#else /* TAO_USE_SEQUENCE_TEMPLATES */
  TAO_Unbounded_WString_Sequence
#endif /* !TAO_USE_SEQUENCE_TEMPLATES */
 (seq)
{}
CORBA_WStringSeq::~CORBA_WStringSeq (void) // dtor
{}
void CORBA_WStringSeq::_tao_any_destructor (void *x)
{
  CORBA_WStringSeq *tmp = ACE_static_cast (CORBA_WStringSeq*,x);
  delete tmp;
}


#endif /* end #if !defined */

static const CORBA::Long _oc_CORBA_WStringSeq[] =
{
  TAO_ENCAP_BYTE_ORDER, // byte order
  33, ACE_NTOHL (0x49444c3a), ACE_NTOHL (0x6f6d672e), ACE_NTOHL (0x6f72672f), ACE_NTOHL (0x434f5242), ACE_NTOHL (0x412f5753), ACE_NTOHL (0x7472696e), ACE_NTOHL (0x67536571), ACE_NTOHL (0x3a312e30), ACE_NTOHL (0x0),  // repository ID = IDL:omg.org/CORBA/WStringSeq:1.0
  11, ACE_NTOHL (0x57537472), ACE_NTOHL (0x696e6753), ACE_NTOHL (0x65710000),  // name = WStringSeq
  CORBA::tk_sequence, // typecode kind
  16, // encapsulation length
    TAO_ENCAP_BYTE_ORDER, // byte order
    CORBA::tk_wstring,
    0U, // string length
    0U,

};
static CORBA::TypeCode _tc_TAO_tc_CORBA_WStringSeq (CORBA::tk_alias, sizeof (_oc_CORBA_WStringSeq), (char *) &_oc_CORBA_WStringSeq, 0, sizeof (CORBA_WStringSeq));
TAO_NAMESPACE_TYPE (CORBA::TypeCode_ptr)
TAO_NAMESPACE_BEGIN (CORBA)
TAO_NAMESPACE_DEFINE (CORBA::TypeCode_ptr, _tc_WStringSeq, &_tc_TAO_tc_CORBA_WStringSeq)
TAO_NAMESPACE_END

void operator<<= (
    CORBA::Any &_tao_any,
    const CORBA_StringSeq &_tao_elem
  ) // copying
{
  TAO_OutputCDR stream;
  if (stream << _tao_elem)
  {
    _tao_any._tao_replace (
        CORBA::_tc_StringSeq,
        TAO_ENCAP_BYTE_ORDER,
        stream.begin ()
      );
  }
}

void operator<<= (CORBA::Any &_tao_any, CORBA_StringSeq *_tao_elem) // non copying
{
  TAO_OutputCDR stream;
  stream << *_tao_elem;
  _tao_any._tao_replace (
      CORBA::_tc_StringSeq,
      TAO_ENCAP_BYTE_ORDER,
      stream.begin (),
      1,
      _tao_elem,
      CORBA_StringSeq::_tao_any_destructor
    );
}

CORBA::Boolean operator>>= (const CORBA::Any &_tao_any, CORBA_StringSeq *&_tao_elem)
{
  return _tao_any >>= ACE_const_cast(
      const CORBA_StringSeq*&,
      _tao_elem
    );
}

CORBA::Boolean operator>>= (const CORBA::Any &_tao_any, const CORBA_StringSeq *&_tao_elem)
{
  _tao_elem = 0;
  ACE_TRY_NEW_ENV
  {
    CORBA::TypeCode_var type = _tao_any.type ();
    CORBA::Boolean result =
      type->equivalent (CORBA::_tc_StringSeq, ACE_TRY_ENV);
    ACE_TRY_CHECK;

    if (!result)
      {
        return 0;
      }

    if (_tao_any.any_owns_data ())
    {
      _tao_elem = ACE_static_cast(
          const CORBA_StringSeq*,
          _tao_any.value ()
        );
      return 1;
    }
    else
    {
      CORBA_StringSeq *tmp;
      ACE_NEW_RETURN (tmp, CORBA_StringSeq, 0);
      TAO_InputCDR stream (
          _tao_any._tao_get_cdr (),
          _tao_any._tao_byte_order ()
        );
      if (stream >> *tmp)
      {
        ((CORBA::Any *)&_tao_any)->_tao_replace (
            CORBA::_tc_StringSeq,
            1,
            ACE_static_cast (void *, tmp),
            CORBA_StringSeq::_tao_any_destructor
          );
        _tao_elem = tmp;
        return 1;
      }
      else
      {
        delete tmp;
      }
    }
  }
  ACE_CATCHANY
  {
  }
  ACE_ENDTRY;
  return 0;
}

void operator<<= (
    CORBA::Any &_tao_any,
    const CORBA_WStringSeq &_tao_elem
  ) // copying
{
  TAO_OutputCDR stream;
  if (stream << _tao_elem)
  {
    _tao_any._tao_replace (
        CORBA::_tc_WStringSeq,
        TAO_ENCAP_BYTE_ORDER,
        stream.begin ()
      );
  }
}

void operator<<= (CORBA::Any &_tao_any, CORBA_WStringSeq *_tao_elem) // non copying
{
  TAO_OutputCDR stream;
  stream << *_tao_elem;
  _tao_any._tao_replace (
      CORBA::_tc_WStringSeq,
      TAO_ENCAP_BYTE_ORDER,
      stream.begin (),
      1,
      _tao_elem,
      CORBA_WStringSeq::_tao_any_destructor
    );
}

CORBA::Boolean operator>>= (const CORBA::Any &_tao_any, CORBA_WStringSeq *&_tao_elem)
{
  return _tao_any >>= ACE_const_cast(
      const CORBA_WStringSeq*&,
      _tao_elem
    );
}

CORBA::Boolean operator>>= (const CORBA::Any &_tao_any, const CORBA_WStringSeq *&_tao_elem)
{
  _tao_elem = 0;
  ACE_TRY_NEW_ENV
  {
    CORBA::TypeCode_var type = _tao_any.type ();
    CORBA::Boolean result =
      type->equivalent (CORBA::_tc_WStringSeq, ACE_TRY_ENV);
    ACE_TRY_CHECK;

    if (!result)
      {
        return 0;
      }

    if (_tao_any.any_owns_data ())
    {
      _tao_elem = ACE_static_cast(
          const CORBA_WStringSeq*,
          _tao_any.value ()
        );
      return 1;
    }
    else
    {
      CORBA_WStringSeq *tmp;
      ACE_NEW_RETURN (tmp, CORBA_WStringSeq, 0);
      TAO_InputCDR stream (
          _tao_any._tao_get_cdr (),
          _tao_any._tao_byte_order ()
        );
      if (stream >> *tmp)
      {
        ((CORBA::Any *)&_tao_any)->_tao_replace (
            CORBA::_tc_WStringSeq,
            1,
            ACE_static_cast (void *, tmp),
            CORBA_WStringSeq::_tao_any_destructor
          );
        _tao_elem = tmp;
        return 1;
      }
      else
      {
        delete tmp;
      }
    }
  }
  ACE_CATCHANY
  {
  }
  ACE_ENDTRY;
  return 0;
}

CORBA::Boolean operator<< (
    TAO_OutputCDR &strm,
    const CORBA_StringSeq &_tao_sequence
  )
{
  if (strm << _tao_sequence.length ())
  {
    // encode all elements
    CORBA::Boolean _tao_marshal_flag = 1;
    for (CORBA::ULong i = 0; i < _tao_sequence.length () && _tao_marshal_flag; i++)
    {
      _tao_marshal_flag = (strm << _tao_sequence[i].in ());
    }
    return _tao_marshal_flag;
  }
  return 0; // error
}

CORBA::Boolean operator>> (
    TAO_InputCDR &strm,
    CORBA_StringSeq &_tao_sequence
  )
{
  CORBA::ULong _tao_seq_len;
  if (strm >> _tao_seq_len)
  {
    // set the length of the sequence
    _tao_sequence.length (_tao_seq_len);
    // If length is 0 we return true.
    if (0 >= _tao_seq_len)
      return 1;
    // retrieve all the elements
    CORBA::Boolean _tao_marshal_flag = 1;
    for (CORBA::ULong i = 0; i < _tao_sequence.length () && _tao_marshal_flag; i++)
    {
      _tao_marshal_flag = (strm >> _tao_sequence[i].out ());
    }
    return _tao_marshal_flag;
  }
  return 0; // error
}

CORBA::Boolean operator<< (
    TAO_OutputCDR &strm,
    const CORBA_WStringSeq &_tao_sequence
  )
{
  if (strm << _tao_sequence.length ())
  {
    // encode all elements
    CORBA::Boolean _tao_marshal_flag = 1;
    for (CORBA::ULong i = 0; i < _tao_sequence.length () && _tao_marshal_flag; i++)
    {
      _tao_marshal_flag = (strm << _tao_sequence[i].in ());
    }
    return _tao_marshal_flag;
  }
  return 0; // error
}

CORBA::Boolean operator>> (
    TAO_InputCDR &strm,
    CORBA_WStringSeq &_tao_sequence
  )
{
  CORBA::ULong _tao_seq_len;
  if (strm >> _tao_seq_len)
  {
    // set the length of the sequence
    _tao_sequence.length (_tao_seq_len);
    // If length is 0 we return true.
    if (0 >= _tao_seq_len)
      return 1;
    // retrieve all the elements
    CORBA::Boolean _tao_marshal_flag = 1;
    for (CORBA::ULong i = 0; i < _tao_sequence.length () && _tao_marshal_flag; i++)
    {
      _tao_marshal_flag = (strm >> _tao_sequence[i].out ());
    }
    return _tao_marshal_flag;
  }
  return 0; // error
}
