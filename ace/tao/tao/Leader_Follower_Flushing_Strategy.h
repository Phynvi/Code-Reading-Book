// -*- C++ -*-

//=============================================================================
/**
 *  @file Leader_Follower_Flushing_Strategy.h
 *
 *  Leader_Follower_Flushing_Strategy.h,v 1.2 2001/08/01 23:39:47 coryan Exp
 *
 *  @author Carlos O'Ryan <coryan@uci.edu>
 */
//=============================================================================

#ifndef TAO_LEADER_FOLLOWER_FLUSHING_STRATEGY_H
#define TAO_LEADER_FOLLOWER_FLUSHING_STRATEGY_H
#include "ace/pre.h"

#include "Flushing_Strategy.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

/**
 * @class TAO_Leader_Follower_Flushing_Strategy
 *
 * @brief Implement a flushing strategy that uses the Leader/Follower
 *        set.
 */
class TAO_Export TAO_Leader_Follower_Flushing_Strategy : public TAO_Flushing_Strategy
{
public:
  virtual int schedule_output (TAO_Transport *transport);
  virtual int cancel_output (TAO_Transport *transport);
  virtual int flush_message (TAO_Transport *transport,
                             TAO_Queued_Message *msg,
                             ACE_Time_Value *max_wait_time);
  virtual int flush_transport (TAO_Transport *transport);
};

#include "ace/post.h"
#endif  /* TAO_LEADER_FOLLOWER_FLUSHING_STRATEGY_H */
