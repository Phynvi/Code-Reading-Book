/* -*- C++ -*- */
// Shutdown.h,v 1.2 2000/05/13 03:51:45 coryan Exp
//
// ============================================================================
//
// = LIBRARY
//   ORBSVCS Real-time Event Channel testsuite
//
// = FILENAME
//   Shutdown
//
// = AUTHOR
//   Carlos O'Ryan (coryan@cs.wustl.edu)
//
// ============================================================================

#ifndef EC_SHUTDOWN_H
#define EC_SHUTDOWN_H

#include "Driver.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class EC_Shutdown : public EC_Driver
{
  //
  // = TITLE
  //   Test the EC shutdown features
  //
  // = DESCRIPTION
  //   The EC must inform its suppliers and consumers on the event of
  //   its destruction.
  //   This test exercises that feature of the EC.
  //
public:
  EC_Shutdown (void);
  // Constructor

  // = The EC_Driver methods
  void execute_test (CORBA::Environment& ACE_TRY_ENV);
  // Don't run the suppliers just create the EC and then destroy it.

  void dump_results (void);
  // Don't dump the EC_Driver results, they are meaningless.

  virtual void consumer_disconnect (void* consumer_cookie,
                                    CORBA::Environment& ACE_TRY_ENV);
  // One of the consumers in the test has been disconnected from the EC

  virtual void supplier_disconnect (void* supplier_cookie,
                                    CORBA::Environment& ACE_TRY_ENV);
  // One of the suppliers in the test has been disconnected from the EC


private:
  int consumer_disconnects_;
  int supplier_disconnects_;
  // Number of consumer and supplier disconnect messages.
};

#endif /* EC_SHUTDOWN_H */
