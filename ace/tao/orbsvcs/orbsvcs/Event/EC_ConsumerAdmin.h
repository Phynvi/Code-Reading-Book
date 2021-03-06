/* -*- C++ -*- */
/**
 *  @file   EC_ConsumerAdmin.h
 *
 *  EC_ConsumerAdmin.h,v 1.24 2000/10/31 03:11:12 coryan Exp
 *
 *  @author Carlos O'Ryan (coryan@cs.wustl.edu)
 *
 * Based on previous work by Tim Harrison (harrison@cs.wustl.edu) and
 * other members of the DOC group. More details can be found in:
 *
 * http://doc.ece.uci.edu/~coryan/EC/index.html
 */

#ifndef TAO_EC_CONSUMERADMIN_H
#define TAO_EC_CONSUMERADMIN_H
#include "ace/pre.h"

#include "EC_ProxySupplier.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "orbsvcs/ESF/ESF_Peer_Admin.h"
#include "event_export.h"

class TAO_EC_Event_Channel;
class TAO_EC_ProxyPushConsumer;


/**
 * @class TAO_EC_ConsumerAdmin
 *
 * @brief Implements the ConsumerAdmin interface, i.e. the factory for
 * TAO_EC_ProxyPushSupplier objects.
 *
 * <H2> Memory Management</H2>
 * It does not assume ownership of the TAO_EC_Event_Channel object;
 * but it *does* assume ownership of the TAO_EC_ProxyPushSupplier_Set
 * object. 
 *
 * <H2>Locking</H2>
 * No provisions for locking, access must be serialized externally.
 */
class TAO_RTEvent_Export TAO_EC_ConsumerAdmin
  : public POA_RtecEventChannelAdmin::ConsumerAdmin
  , public TAO_ESF_Peer_Admin<TAO_EC_Event_Channel,TAO_EC_ProxyPushSupplier,RtecEventChannelAdmin::ProxyPushSupplier,TAO_EC_ProxyPushConsumer>
{
public:
  /**
   * constructor. If <supplier_set> is nil then it builds one using
   * the <event_channel> argument.
   * In any case it assumes ownership.
   */
  TAO_EC_ConsumerAdmin (TAO_EC_Event_Channel* event_channel);

  /// destructor...
  virtual ~TAO_EC_ConsumerAdmin (void);

  // = The RtecEventChannelAdmin::ConsumerAdmin methods...
  virtual RtecEventChannelAdmin::ProxyPushSupplier_ptr
      obtain_push_supplier (CORBA::Environment &)
          ACE_THROW_SPEC ((CORBA::SystemException));

  // = The PortableServer::ServantBase methods
  virtual PortableServer::POA_ptr _default_POA (CORBA::Environment& env);

private:
  /// Store the default POA.
  PortableServer::POA_var default_POA_;
};

#if defined (__ACE_INLINE__)
#include "EC_ConsumerAdmin.i"
#endif /* __ACE_INLINE__ */

#include "ace/post.h"
#endif /* TAO_EC_CONSUMERADMIN_H */
