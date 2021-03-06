// Servant_Activator.h,v 1.1 2000/10/25 05:03:40 irfan Exp

// ================================================================
//
// = LIBRARY
//     TAO/examples/POA/Forwarding
//
// = FILENAME
//     Servant_Activator.h
//
// = DESCRIPTION
//     Defines a MyFooServantActivator class, used with a POA having a
//     RETAIN policy
//
// = AUTHOR
//     Irfan Pyarali
//     Michael Kircher
//
// ================================================================

#ifndef SERVANT_ACTIVATOR_H
#define SERVANT_ACTIVATOR_H

#include "tao/corba.h"
#include "tao/PortableServer/PortableServer.h"

class MyFooServantActivator : public PortableServer::ServantActivator
{
  // = TITLE
  //   This class is used by a POA with USE_SERVANT_MANAGER and
  //   RETAIN policy.
public:
  MyFooServantActivator (CORBA::ORB_ptr orb,
                         CORBA::Object_ptr forward_to);

  virtual PortableServer::Servant incarnate (const PortableServer::ObjectId & oid,
                                             PortableServer::POA_ptr adapter
                                             TAO_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableServer::ForwardRequest));

  virtual void etherealize (const PortableServer::ObjectId & oid,
                            PortableServer::POA_ptr adapter,
                            PortableServer::Servant serv,
                            CORBA::Boolean cleanup_in_progress,
                            CORBA::Boolean remaining_activations
                            TAO_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException));

  void forward_requests (CORBA::Environment &env);
  // Object should be forwarded from now on.

private:
  CORBA::ORB_var orb_;

  CORBA::Object_var forward_to_;
  // Location to forward to
};

#endif /* SERVANT_ACTIVATOR_H */
