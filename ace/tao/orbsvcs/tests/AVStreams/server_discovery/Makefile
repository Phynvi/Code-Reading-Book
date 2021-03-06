#----------------------------------------------------------------------------
#	Makefile,v 1.15 2000/05/03 19:06:15 coryan Exp
#
#	Makefile for TAO
#----------------------------------------------------------------------------
shared_libs_only=1
MAKEFILE = Makefile
LIBNAME  = libavdemo
SHLIB2   = $(LIBNAME).$(SOEXT)

IDL_FILES= Video_Repository

IDL_SRC = \
	$(addsuffix S.cpp, $(IDL_FILES)) \
	$(addsuffix C.cpp, $(IDL_FILES))

SRCS =  Trader_Client \
	Server_Discovery

FILES	 = $(SRCS)

ifndef TAO_ROOT
TAO_ROOT = $(ACE_ROOT)/TAO
endif

MPEG_ROOT = $(TAO_ROOT)/orbsvcs/tests/AVStreams/mpeg/source
LSRC	= $(addsuffix .cpp,$(FILES)) $(IDL_SRC)

LDFLAGS += -L$(JAVA_ROOT)/jre/lib/sparc -L$(JAVA_ROOT)/jre/lib/sparc/native_threads -L$(MPEG_ROOT)/mpeg_shared

LDLIBS = -lTAO_CosNaming -lTAO -lACE -lmpeg_shared -lavdemo -ljava -ljvm
CPPFLAGS +=  -I$(JAVA_ROOT)/include-old -I$(JAVA_ROOT)/include-old/solaris \
	    -I$(TAO_ROOT)/orbsvcs -I$(MPEG_ROOT) -I$(TAO_ROOT) -I$(TAO_ROOT)/orbsvcs/orbsvcs

BIN2 = main

#----------------------------------------------------------------------------
#	Include macros and targets
#----------------------------------------------------------------------------

include	$(ACE_ROOT)/include/makeinclude/wrapper_macros.GNU

#### If the TAO orbsvcs library wasn't built with sufficient components,
#### don't try to build here.
TAO_ORBSVCS := $(shell sh $(ACE_ROOT)/bin/ace_components --orbsvcs)
ifeq (AV,$(findstring AV,$(TAO_ORBSVCS)))
  BUILD := TAO_VR.module $(BUILD)
  BIN = $(BIN2)
  SHLIB = $(SHLIB2)
else  # ! AV
  BUILD =
  override INSTALL =
endif # ! AV

include	$(ACE_ROOT)/include/makeinclude/macros.GNU
include $(TAO_ROOT)/rules.tao.GNU
include	$(ACE_ROOT)/include/makeinclude/rules.common.GNU
include	$(ACE_ROOT)/include/makeinclude/rules.nonested.GNU
include	$(ACE_ROOT)/include/makeinclude/rules.lib.GNU
include	$(ACE_ROOT)/include/makeinclude/rules.bin.GNU
include	$(ACE_ROOT)/include/makeinclude/rules.local.GNU
include $(TAO_ROOT)/taoconfig.mk

#----------------------------------------------------------------------------
#	Local targets (and local hacks)
#----------------------------------------------------------------------------

Video_Repository.idl: $(TAO_ROOT)/orbsvcs/tests/AVStreams/mpeg/source/server/Video_Repository.idl
	cp $(TAO_ROOT)/orbsvcs/tests/AVStreams/mpeg/source/server/Video_Repository.idl .

TAO_VR.module: Video_Repository.idl
	$(JAVA_ROOT)/bin/idltojava Video_Repository.idl
	touch TAO_VR.module

.PRECIOUS: $(foreach file, $(IDL_FILES), $(foreach ext, $(IDL_EXT), $(file)$(ext))))

realclean: clean
	-$(RM) $(foreach file, $(IDL_FILES), $(foreach ext, $(IDL_EXT), $(file)$(ext)))

#----------------------------------------------------------------------------
#	Dependencies
#----------------------------------------------------------------------------

# DO NOT DELETE THIS LINE -- g++dep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

.obj/Video_RepositoryS.o .obj/Video_RepositoryS.so .shobj/Video_RepositoryS.o .shobj/Video_RepositoryS.so: Video_RepositoryS.cpp Video_RepositoryS.h \
 Video_RepositoryC.h $(TAO_ROOT)/tao/corba.h \
 $(TAO_ROOT)/tao/orbconf.h \
 $(ACE_ROOT)/ace/OS.h \
 $(ACE_ROOT)/ace/inc_user_config.h \
 $(ACE_ROOT)/ace/config.h \
 $(ACE_ROOT)/ace/config-g++-common.h \
 $(ACE_ROOT)/ace/streams.h \
 $(ACE_ROOT)/ace/Basic_Types.h \
 $(ACE_ROOT)/ace/Basic_Types.i \
 $(ACE_ROOT)/ace/OS.i \
 $(ACE_ROOT)/ace/Trace.h \
 $(ACE_ROOT)/ace/Log_Msg.h \
 $(ACE_ROOT)/ace/Log_Record.h \
 $(ACE_ROOT)/ace/ACE.h \
 $(ACE_ROOT)/ace/ACE.i \
 $(ACE_ROOT)/ace/Log_Priority.h \
 $(ACE_ROOT)/ace/Log_Record.i \
 $(ACE_ROOT)/ace/Get_Opt.h \
 $(ACE_ROOT)/ace/Get_Opt.i \
 $(ACE_ROOT)/ace/SOCK_Stream.h \
 $(ACE_ROOT)/ace/SOCK_IO.h \
 $(ACE_ROOT)/ace/SOCK.h \
 $(ACE_ROOT)/ace/Addr.h \
 $(ACE_ROOT)/ace/Addr.i \
 $(ACE_ROOT)/ace/IPC_SAP.h \
 $(ACE_ROOT)/ace/IPC_SAP.i \
 $(ACE_ROOT)/ace/SOCK.i \
 $(ACE_ROOT)/ace/SOCK_IO.i \
 $(ACE_ROOT)/ace/INET_Addr.h \
 $(ACE_ROOT)/ace/INET_Addr.i \
 $(ACE_ROOT)/ace/SOCK_Stream.i \
 $(ACE_ROOT)/ace/Synch_T.h \
 $(ACE_ROOT)/ace/Event_Handler.h \
 $(ACE_ROOT)/ace/Event_Handler.i \
 $(ACE_ROOT)/ace/Synch.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Complex.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Simple.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Simple.i \
 $(ACE_ROOT)/ace/SV_Semaphore_Complex.i \
 $(ACE_ROOT)/ace/Synch.i \
 $(ACE_ROOT)/ace/Synch_T.i \
 $(ACE_ROOT)/ace/Thread.h \
 $(ACE_ROOT)/ace/Thread.i \
 $(ACE_ROOT)/ace/Atomic_Op.i \
 $(ACE_ROOT)/ace/Synch_T.cpp \
 $(ACE_ROOT)/ace/Hash_Map_Manager.h \
 $(ACE_ROOT)/ace/Hash_Map_Manager.cpp \
 $(ACE_ROOT)/ace/Service_Config.h \
 $(ACE_ROOT)/ace/Service_Object.h \
 $(ACE_ROOT)/ace/Shared_Object.h \
 $(ACE_ROOT)/ace/Shared_Object.i \
 $(ACE_ROOT)/ace/Service_Object.i \
 $(ACE_ROOT)/ace/Signal.h \
 $(ACE_ROOT)/ace/Containers.h \
 $(ACE_ROOT)/ace/Containers.i \
 $(ACE_ROOT)/ace/Containers_T.h \
 $(ACE_ROOT)/ace/Containers_T.i \
 $(ACE_ROOT)/ace/Containers_T.cpp \
 $(ACE_ROOT)/ace/Malloc.h \
 $(ACE_ROOT)/ace/Malloc_Base.h \
 $(ACE_ROOT)/ace/Malloc.i \
 $(ACE_ROOT)/ace/Malloc_T.h \
 $(ACE_ROOT)/ace/Free_List.h \
 $(ACE_ROOT)/ace/Free_List.i \
 $(ACE_ROOT)/ace/Free_List.cpp \
 $(ACE_ROOT)/ace/Malloc_T.i \
 $(ACE_ROOT)/ace/Malloc_T.cpp \
 $(ACE_ROOT)/ace/Memory_Pool.h \
 $(ACE_ROOT)/ace/Mem_Map.h \
 $(ACE_ROOT)/ace/Mem_Map.i \
 $(ACE_ROOT)/ace/Memory_Pool.i \
 $(ACE_ROOT)/ace/Signal.i \
 $(ACE_ROOT)/ace/Object_Manager.h \
 $(ACE_ROOT)/ace/Object_Manager.i \
 $(ACE_ROOT)/ace/Managed_Object.h \
 $(ACE_ROOT)/ace/Managed_Object.i \
 $(ACE_ROOT)/ace/Managed_Object.cpp \
 $(ACE_ROOT)/ace/SString.h \
 $(ACE_ROOT)/ace/SString.i \
 $(ACE_ROOT)/ace/Service_Config.i \
 $(ACE_ROOT)/ace/Reactor.h \
 $(ACE_ROOT)/ace/Handle_Set.h \
 $(ACE_ROOT)/ace/Handle_Set.i \
 $(ACE_ROOT)/ace/Timer_Queue.h \
 $(ACE_ROOT)/ace/Timer_Queue_T.h \
 $(ACE_ROOT)/ace/Timer_Queue_T.i \
 $(ACE_ROOT)/ace/Timer_Queue_T.cpp \
 $(ACE_ROOT)/ace/Reactor.i \
 $(ACE_ROOT)/ace/Reactor_Impl.h \
 $(ACE_ROOT)/ace/Svc_Conf_Tokens.h \
 $(ACE_ROOT)/ace/SOCK_Acceptor.h \
 $(ACE_ROOT)/ace/Time_Value.h \
 $(ACE_ROOT)/ace/SOCK_Acceptor.i \
 $(ACE_ROOT)/ace/SOCK_Connector.h \
 $(ACE_ROOT)/ace/SOCK_Connector.i \
 $(ACE_ROOT)/ace/Strategies.h \
 $(ACE_ROOT)/ace/Strategies_T.h \
 $(ACE_ROOT)/ace/Synch_Options.h \
 $(ACE_ROOT)/ace/Synch_Options.i \
 $(ACE_ROOT)/ace/Thread_Manager.h \
 $(ACE_ROOT)/ace/Thread_Manager.i \
 $(ACE_ROOT)/ace/Strategies_T.i \
 $(ACE_ROOT)/ace/Strategies_T.cpp \
 $(ACE_ROOT)/ace/Service_Repository.h \
 $(ACE_ROOT)/ace/Service_Types.h \
 $(ACE_ROOT)/ace/Service_Types.i \
 $(ACE_ROOT)/ace/Service_Repository.i \
 $(ACE_ROOT)/ace/WFMO_Reactor.h \
 $(ACE_ROOT)/ace/Message_Queue.h \
 $(ACE_ROOT)/ace/Message_Block.h \
 $(ACE_ROOT)/ace/Message_Block.i \
 $(ACE_ROOT)/ace/Message_Block_T.h \
 $(ACE_ROOT)/ace/Message_Block_T.i \
 $(ACE_ROOT)/ace/Message_Block_T.cpp \
 $(ACE_ROOT)/ace/IO_Cntl_Msg.h \
 $(ACE_ROOT)/ace/Message_Queue_T.h \
 $(ACE_ROOT)/ace/Message_Queue_T.i \
 $(ACE_ROOT)/ace/Message_Queue_T.cpp \
 $(ACE_ROOT)/ace/Message_Queue.i \
 $(ACE_ROOT)/ace/WFMO_Reactor.i \
 $(ACE_ROOT)/ace/Strategies.i \
 $(ACE_ROOT)/ace/Connector.h \
 $(ACE_ROOT)/ace/Map_Manager.h \
 $(ACE_ROOT)/ace/Map_Manager.i \
 $(ACE_ROOT)/ace/Map_Manager.cpp \
 $(ACE_ROOT)/ace/Svc_Handler.h \
 $(ACE_ROOT)/ace/Task.h \
 $(ACE_ROOT)/ace/Task.i \
 $(ACE_ROOT)/ace/Task_T.h \
 $(ACE_ROOT)/ace/Task_T.i \
 $(ACE_ROOT)/ace/Task_T.cpp \
 $(ACE_ROOT)/ace/Module.h \
 $(ACE_ROOT)/ace/Module.i \
 $(ACE_ROOT)/ace/Module.cpp \
 $(ACE_ROOT)/ace/Stream_Modules.h \
 $(ACE_ROOT)/ace/Stream_Modules.i \
 $(ACE_ROOT)/ace/Stream_Modules.cpp \
 $(ACE_ROOT)/ace/Svc_Handler.i \
 $(ACE_ROOT)/ace/Svc_Handler.cpp \
 $(ACE_ROOT)/ace/Dynamic.h \
 $(ACE_ROOT)/ace/Singleton.h \
 $(ACE_ROOT)/ace/Singleton.i \
 $(ACE_ROOT)/ace/Singleton.cpp \
 $(ACE_ROOT)/ace/Dynamic.i \
 $(ACE_ROOT)/ace/Connector.i \
 $(ACE_ROOT)/ace/Connector.cpp \
 $(ACE_ROOT)/ace/Acceptor.h \
 $(ACE_ROOT)/ace/Acceptor.i \
 $(ACE_ROOT)/ace/Acceptor.cpp \
 $(TAO_ROOT)/tao/Align.h \
 $(TAO_ROOT)/tao/Environment.h \
 $(TAO_ROOT)/tao/Environment.i \
 $(TAO_ROOT)/tao/ORB.h \
 $(TAO_ROOT)/tao/Sequence.h \
 $(TAO_ROOT)/tao/Sequence.i \
 $(TAO_ROOT)/tao/Sequence_T.h \
 $(TAO_ROOT)/tao/Sequence_T.i \
 $(TAO_ROOT)/tao/Sequence_T.cpp \
 $(TAO_ROOT)/tao/Object_KeyC.h \
 $(TAO_ROOT)/tao/Object_KeyC.i \
 $(TAO_ROOT)/tao/Union.h \
 $(TAO_ROOT)/tao/ORB.i \
 $(TAO_ROOT)/tao/try_macros.h \
 $(TAO_ROOT)/tao/Exception.h \
 $(TAO_ROOT)/tao/Exception.i \
 $(TAO_ROOT)/tao/Any.h \
 $(TAO_ROOT)/tao/Any.i \
 $(TAO_ROOT)/tao/NVList.h \
 $(TAO_ROOT)/tao/NVList.i \
 $(TAO_ROOT)/tao/Principal.h \
 $(TAO_ROOT)/tao/Principal.i \
 $(TAO_ROOT)/tao/Request.h \
 $(TAO_ROOT)/tao/Request.i \
 $(TAO_ROOT)/tao/Stub.h \
 $(TAO_ROOT)/tao/Stub.i \
 $(TAO_ROOT)/tao/Object.h \
 $(TAO_ROOT)/tao/Object.i \
 $(TAO_ROOT)/tao/varout.h \
 $(TAO_ROOT)/tao/varout.i \
 $(TAO_ROOT)/tao/varout.cpp \
 $(TAO_ROOT)/tao/Typecode.h \
 $(TAO_ROOT)/tao/Typecode.i \
 $(TAO_ROOT)/tao/Marshal.h \
 $(TAO_ROOT)/tao/Marshal.i \
 $(TAO_ROOT)/tao/singletons.h \
 $(TAO_ROOT)/tao/CDR.h \
 $(TAO_ROOT)/tao/CDR.i \
 $(TAO_ROOT)/tao/PolicyC.h \
 $(TAO_ROOT)/tao/PolicyC.i \
 $(TAO_ROOT)/tao/CurrentC.h \
 $(TAO_ROOT)/tao/CurrentC.i \
 $(TAO_ROOT)/tao/POA.h \
 $(TAO_ROOT)/tao/POAC.h \
 $(TAO_ROOT)/tao/POAC.i \
 $(TAO_ROOT)/tao/Servant_Base.h \
 $(TAO_ROOT)/tao/POAS.h \
 $(TAO_ROOT)/tao/POA_CORBA.h \
 $(TAO_ROOT)/tao/DynAnyC.h \
 $(TAO_ROOT)/tao/DynAnyC.i \
 $(TAO_ROOT)/tao/POAS.i \
 $(TAO_ROOT)/tao/Active_Object_Map.h \
 $(TAO_ROOT)/tao/Active_Object_Map.i \
 $(TAO_ROOT)/tao/POA.i \
 $(TAO_ROOT)/tao/poa_macros.h \
 $(TAO_ROOT)/tao/params.h \
 $(TAO_ROOT)/tao/params.i \
 $(TAO_ROOT)/tao/Connect.h \
 $(TAO_ROOT)/tao/Connect.i \
 $(TAO_ROOT)/tao/ORB_Core.h \
 $(TAO_ROOT)/tao/ORB_Core.i \
 $(ACE_ROOT)/ace/Dynamic_Service.h \
 $(ACE_ROOT)/ace/Dynamic_Service.cpp \
 $(TAO_ROOT)/tao/Operation_Table.h \
 $(TAO_ROOT)/tao/debug.h \
 $(TAO_ROOT)/tao/Client_Strategy_Factory.h \
 $(TAO_ROOT)/tao/Server_Strategy_Factory.h \
 $(TAO_ROOT)/tao/default_client.h \
 $(TAO_ROOT)/tao/default_client.i \
 $(TAO_ROOT)/tao/default_server.h \
 $(TAO_ROOT)/tao/ORB_Strategies_T.h \
 $(TAO_ROOT)/tao/ORB_Strategies_T.i \
 $(TAO_ROOT)/tao/ORB_Strategies_T.cpp \
 $(TAO_ROOT)/tao/default_server.i \
 $(TAO_ROOT)/tao/IIOP_Object.h \
 $(TAO_ROOT)/tao/IIOP_Object.i \
 $(TAO_ROOT)/tao/IIOP_ORB.h \
 $(TAO_ROOT)/tao/IIOP_ORB.i \
 $(TAO_ROOT)/tao/CDR_Interpreter.h \
 $(TAO_ROOT)/tao/GIOP.h \
 $(TAO_ROOT)/tao/GIOP.i \
 $(TAO_ROOT)/tao/Invocation.h \
 $(TAO_ROOT)/tao/Invocation.i \
 $(TAO_ROOT)/tao/Server_Request.h \
 $(TAO_ROOT)/tao/Server_Request.i \
 $(TAO_ROOT)/tao/InconsistentTypeCodeC.h \
 $(TAO_ROOT)/tao/DynAny_i.h \
 Video_RepositoryC.i Video_RepositoryS_T.h Video_RepositoryS_T.i \
 Video_RepositoryS_T.cpp Video_RepositoryS.i
.obj/Video_RepositoryC.o .obj/Video_RepositoryC.so .shobj/Video_RepositoryC.o .shobj/Video_RepositoryC.so: Video_RepositoryC.cpp Video_RepositoryC.h \
 $(TAO_ROOT)/tao/corba.h \
 $(TAO_ROOT)/tao/orbconf.h \
 $(ACE_ROOT)/ace/OS.h \
 $(ACE_ROOT)/ace/inc_user_config.h \
 $(ACE_ROOT)/ace/config.h \
 $(ACE_ROOT)/ace/config-g++-common.h \
 $(ACE_ROOT)/ace/streams.h \
 $(ACE_ROOT)/ace/Basic_Types.h \
 $(ACE_ROOT)/ace/Basic_Types.i \
 $(ACE_ROOT)/ace/OS.i \
 $(ACE_ROOT)/ace/Trace.h \
 $(ACE_ROOT)/ace/Log_Msg.h \
 $(ACE_ROOT)/ace/Log_Record.h \
 $(ACE_ROOT)/ace/ACE.h \
 $(ACE_ROOT)/ace/ACE.i \
 $(ACE_ROOT)/ace/Log_Priority.h \
 $(ACE_ROOT)/ace/Log_Record.i \
 $(ACE_ROOT)/ace/Get_Opt.h \
 $(ACE_ROOT)/ace/Get_Opt.i \
 $(ACE_ROOT)/ace/SOCK_Stream.h \
 $(ACE_ROOT)/ace/SOCK_IO.h \
 $(ACE_ROOT)/ace/SOCK.h \
 $(ACE_ROOT)/ace/Addr.h \
 $(ACE_ROOT)/ace/Addr.i \
 $(ACE_ROOT)/ace/IPC_SAP.h \
 $(ACE_ROOT)/ace/IPC_SAP.i \
 $(ACE_ROOT)/ace/SOCK.i \
 $(ACE_ROOT)/ace/SOCK_IO.i \
 $(ACE_ROOT)/ace/INET_Addr.h \
 $(ACE_ROOT)/ace/INET_Addr.i \
 $(ACE_ROOT)/ace/SOCK_Stream.i \
 $(ACE_ROOT)/ace/Synch_T.h \
 $(ACE_ROOT)/ace/Event_Handler.h \
 $(ACE_ROOT)/ace/Event_Handler.i \
 $(ACE_ROOT)/ace/Synch.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Complex.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Simple.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Simple.i \
 $(ACE_ROOT)/ace/SV_Semaphore_Complex.i \
 $(ACE_ROOT)/ace/Synch.i \
 $(ACE_ROOT)/ace/Synch_T.i \
 $(ACE_ROOT)/ace/Thread.h \
 $(ACE_ROOT)/ace/Thread.i \
 $(ACE_ROOT)/ace/Atomic_Op.i \
 $(ACE_ROOT)/ace/Synch_T.cpp \
 $(ACE_ROOT)/ace/Hash_Map_Manager.h \
 $(ACE_ROOT)/ace/Hash_Map_Manager.cpp \
 $(ACE_ROOT)/ace/Service_Config.h \
 $(ACE_ROOT)/ace/Service_Object.h \
 $(ACE_ROOT)/ace/Shared_Object.h \
 $(ACE_ROOT)/ace/Shared_Object.i \
 $(ACE_ROOT)/ace/Service_Object.i \
 $(ACE_ROOT)/ace/Signal.h \
 $(ACE_ROOT)/ace/Containers.h \
 $(ACE_ROOT)/ace/Containers.i \
 $(ACE_ROOT)/ace/Containers_T.h \
 $(ACE_ROOT)/ace/Containers_T.i \
 $(ACE_ROOT)/ace/Containers_T.cpp \
 $(ACE_ROOT)/ace/Malloc.h \
 $(ACE_ROOT)/ace/Malloc_Base.h \
 $(ACE_ROOT)/ace/Malloc.i \
 $(ACE_ROOT)/ace/Malloc_T.h \
 $(ACE_ROOT)/ace/Free_List.h \
 $(ACE_ROOT)/ace/Free_List.i \
 $(ACE_ROOT)/ace/Free_List.cpp \
 $(ACE_ROOT)/ace/Malloc_T.i \
 $(ACE_ROOT)/ace/Malloc_T.cpp \
 $(ACE_ROOT)/ace/Memory_Pool.h \
 $(ACE_ROOT)/ace/Mem_Map.h \
 $(ACE_ROOT)/ace/Mem_Map.i \
 $(ACE_ROOT)/ace/Memory_Pool.i \
 $(ACE_ROOT)/ace/Signal.i \
 $(ACE_ROOT)/ace/Object_Manager.h \
 $(ACE_ROOT)/ace/Object_Manager.i \
 $(ACE_ROOT)/ace/Managed_Object.h \
 $(ACE_ROOT)/ace/Managed_Object.i \
 $(ACE_ROOT)/ace/Managed_Object.cpp \
 $(ACE_ROOT)/ace/SString.h \
 $(ACE_ROOT)/ace/SString.i \
 $(ACE_ROOT)/ace/Service_Config.i \
 $(ACE_ROOT)/ace/Reactor.h \
 $(ACE_ROOT)/ace/Handle_Set.h \
 $(ACE_ROOT)/ace/Handle_Set.i \
 $(ACE_ROOT)/ace/Timer_Queue.h \
 $(ACE_ROOT)/ace/Timer_Queue_T.h \
 $(ACE_ROOT)/ace/Timer_Queue_T.i \
 $(ACE_ROOT)/ace/Timer_Queue_T.cpp \
 $(ACE_ROOT)/ace/Reactor.i \
 $(ACE_ROOT)/ace/Reactor_Impl.h \
 $(ACE_ROOT)/ace/Svc_Conf_Tokens.h \
 $(ACE_ROOT)/ace/SOCK_Acceptor.h \
 $(ACE_ROOT)/ace/Time_Value.h \
 $(ACE_ROOT)/ace/SOCK_Acceptor.i \
 $(ACE_ROOT)/ace/SOCK_Connector.h \
 $(ACE_ROOT)/ace/SOCK_Connector.i \
 $(ACE_ROOT)/ace/Strategies.h \
 $(ACE_ROOT)/ace/Strategies_T.h \
 $(ACE_ROOT)/ace/Synch_Options.h \
 $(ACE_ROOT)/ace/Synch_Options.i \
 $(ACE_ROOT)/ace/Thread_Manager.h \
 $(ACE_ROOT)/ace/Thread_Manager.i \
 $(ACE_ROOT)/ace/Strategies_T.i \
 $(ACE_ROOT)/ace/Strategies_T.cpp \
 $(ACE_ROOT)/ace/Service_Repository.h \
 $(ACE_ROOT)/ace/Service_Types.h \
 $(ACE_ROOT)/ace/Service_Types.i \
 $(ACE_ROOT)/ace/Service_Repository.i \
 $(ACE_ROOT)/ace/WFMO_Reactor.h \
 $(ACE_ROOT)/ace/Message_Queue.h \
 $(ACE_ROOT)/ace/Message_Block.h \
 $(ACE_ROOT)/ace/Message_Block.i \
 $(ACE_ROOT)/ace/Message_Block_T.h \
 $(ACE_ROOT)/ace/Message_Block_T.i \
 $(ACE_ROOT)/ace/Message_Block_T.cpp \
 $(ACE_ROOT)/ace/IO_Cntl_Msg.h \
 $(ACE_ROOT)/ace/Message_Queue_T.h \
 $(ACE_ROOT)/ace/Message_Queue_T.i \
 $(ACE_ROOT)/ace/Message_Queue_T.cpp \
 $(ACE_ROOT)/ace/Message_Queue.i \
 $(ACE_ROOT)/ace/WFMO_Reactor.i \
 $(ACE_ROOT)/ace/Strategies.i \
 $(ACE_ROOT)/ace/Connector.h \
 $(ACE_ROOT)/ace/Map_Manager.h \
 $(ACE_ROOT)/ace/Map_Manager.i \
 $(ACE_ROOT)/ace/Map_Manager.cpp \
 $(ACE_ROOT)/ace/Svc_Handler.h \
 $(ACE_ROOT)/ace/Task.h \
 $(ACE_ROOT)/ace/Task.i \
 $(ACE_ROOT)/ace/Task_T.h \
 $(ACE_ROOT)/ace/Task_T.i \
 $(ACE_ROOT)/ace/Task_T.cpp \
 $(ACE_ROOT)/ace/Module.h \
 $(ACE_ROOT)/ace/Module.i \
 $(ACE_ROOT)/ace/Module.cpp \
 $(ACE_ROOT)/ace/Stream_Modules.h \
 $(ACE_ROOT)/ace/Stream_Modules.i \
 $(ACE_ROOT)/ace/Stream_Modules.cpp \
 $(ACE_ROOT)/ace/Svc_Handler.i \
 $(ACE_ROOT)/ace/Svc_Handler.cpp \
 $(ACE_ROOT)/ace/Dynamic.h \
 $(ACE_ROOT)/ace/Singleton.h \
 $(ACE_ROOT)/ace/Singleton.i \
 $(ACE_ROOT)/ace/Singleton.cpp \
 $(ACE_ROOT)/ace/Dynamic.i \
 $(ACE_ROOT)/ace/Connector.i \
 $(ACE_ROOT)/ace/Connector.cpp \
 $(ACE_ROOT)/ace/Acceptor.h \
 $(ACE_ROOT)/ace/Acceptor.i \
 $(ACE_ROOT)/ace/Acceptor.cpp \
 $(TAO_ROOT)/tao/Align.h \
 $(TAO_ROOT)/tao/Environment.h \
 $(TAO_ROOT)/tao/Environment.i \
 $(TAO_ROOT)/tao/ORB.h \
 $(TAO_ROOT)/tao/Sequence.h \
 $(TAO_ROOT)/tao/Sequence.i \
 $(TAO_ROOT)/tao/Sequence_T.h \
 $(TAO_ROOT)/tao/Sequence_T.i \
 $(TAO_ROOT)/tao/Sequence_T.cpp \
 $(TAO_ROOT)/tao/Object_KeyC.h \
 $(TAO_ROOT)/tao/Object_KeyC.i \
 $(TAO_ROOT)/tao/Union.h \
 $(TAO_ROOT)/tao/ORB.i \
 $(TAO_ROOT)/tao/try_macros.h \
 $(TAO_ROOT)/tao/Exception.h \
 $(TAO_ROOT)/tao/Exception.i \
 $(TAO_ROOT)/tao/Any.h \
 $(TAO_ROOT)/tao/Any.i \
 $(TAO_ROOT)/tao/NVList.h \
 $(TAO_ROOT)/tao/NVList.i \
 $(TAO_ROOT)/tao/Principal.h \
 $(TAO_ROOT)/tao/Principal.i \
 $(TAO_ROOT)/tao/Request.h \
 $(TAO_ROOT)/tao/Request.i \
 $(TAO_ROOT)/tao/Stub.h \
 $(TAO_ROOT)/tao/Stub.i \
 $(TAO_ROOT)/tao/Object.h \
 $(TAO_ROOT)/tao/Object.i \
 $(TAO_ROOT)/tao/varout.h \
 $(TAO_ROOT)/tao/varout.i \
 $(TAO_ROOT)/tao/varout.cpp \
 $(TAO_ROOT)/tao/Typecode.h \
 $(TAO_ROOT)/tao/Typecode.i \
 $(TAO_ROOT)/tao/Marshal.h \
 $(TAO_ROOT)/tao/Marshal.i \
 $(TAO_ROOT)/tao/singletons.h \
 $(TAO_ROOT)/tao/CDR.h \
 $(TAO_ROOT)/tao/CDR.i \
 $(TAO_ROOT)/tao/PolicyC.h \
 $(TAO_ROOT)/tao/PolicyC.i \
 $(TAO_ROOT)/tao/CurrentC.h \
 $(TAO_ROOT)/tao/CurrentC.i \
 $(TAO_ROOT)/tao/POA.h \
 $(TAO_ROOT)/tao/POAC.h \
 $(TAO_ROOT)/tao/POAC.i \
 $(TAO_ROOT)/tao/Servant_Base.h \
 $(TAO_ROOT)/tao/POAS.h \
 $(TAO_ROOT)/tao/POA_CORBA.h \
 $(TAO_ROOT)/tao/DynAnyC.h \
 $(TAO_ROOT)/tao/DynAnyC.i \
 $(TAO_ROOT)/tao/POAS.i \
 $(TAO_ROOT)/tao/Active_Object_Map.h \
 $(TAO_ROOT)/tao/Active_Object_Map.i \
 $(TAO_ROOT)/tao/POA.i \
 $(TAO_ROOT)/tao/poa_macros.h \
 $(TAO_ROOT)/tao/params.h \
 $(TAO_ROOT)/tao/params.i \
 $(TAO_ROOT)/tao/Connect.h \
 $(TAO_ROOT)/tao/Connect.i \
 $(TAO_ROOT)/tao/ORB_Core.h \
 $(TAO_ROOT)/tao/ORB_Core.i \
 $(ACE_ROOT)/ace/Dynamic_Service.h \
 $(ACE_ROOT)/ace/Dynamic_Service.cpp \
 $(TAO_ROOT)/tao/Operation_Table.h \
 $(TAO_ROOT)/tao/debug.h \
 $(TAO_ROOT)/tao/Client_Strategy_Factory.h \
 $(TAO_ROOT)/tao/Server_Strategy_Factory.h \
 $(TAO_ROOT)/tao/default_client.h \
 $(TAO_ROOT)/tao/default_client.i \
 $(TAO_ROOT)/tao/default_server.h \
 $(TAO_ROOT)/tao/ORB_Strategies_T.h \
 $(TAO_ROOT)/tao/ORB_Strategies_T.i \
 $(TAO_ROOT)/tao/ORB_Strategies_T.cpp \
 $(TAO_ROOT)/tao/default_server.i \
 $(TAO_ROOT)/tao/IIOP_Object.h \
 $(TAO_ROOT)/tao/IIOP_Object.i \
 $(TAO_ROOT)/tao/IIOP_ORB.h \
 $(TAO_ROOT)/tao/IIOP_ORB.i \
 $(TAO_ROOT)/tao/CDR_Interpreter.h \
 $(TAO_ROOT)/tao/GIOP.h \
 $(TAO_ROOT)/tao/GIOP.i \
 $(TAO_ROOT)/tao/Invocation.h \
 $(TAO_ROOT)/tao/Invocation.i \
 $(TAO_ROOT)/tao/Server_Request.h \
 $(TAO_ROOT)/tao/Server_Request.i \
 $(TAO_ROOT)/tao/InconsistentTypeCodeC.h \
 $(TAO_ROOT)/tao/DynAny_i.h \
 Video_RepositoryC.i Video_RepositoryS.h Video_RepositoryS_T.h \
 Video_RepositoryS_T.i Video_RepositoryS_T.cpp Video_RepositoryS.i
.obj/Trader_Client.o .obj/Trader_Client.so .shobj/Trader_Client.o .shobj/Trader_Client.so: Trader_Client.cpp Trader_Client.h \
 $(TAO_ROOT)/tao/TAO.h \
 $(TAO_ROOT)/tao/corba.h \
 $(TAO_ROOT)/tao/orbconf.h \
 $(ACE_ROOT)/ace/OS.h \
 $(ACE_ROOT)/ace/inc_user_config.h \
 $(ACE_ROOT)/ace/config.h \
 $(ACE_ROOT)/ace/config-g++-common.h \
 $(ACE_ROOT)/ace/streams.h \
 $(ACE_ROOT)/ace/Basic_Types.h \
 $(ACE_ROOT)/ace/Basic_Types.i \
 $(ACE_ROOT)/ace/OS.i \
 $(ACE_ROOT)/ace/Trace.h \
 $(ACE_ROOT)/ace/Log_Msg.h \
 $(ACE_ROOT)/ace/Log_Record.h \
 $(ACE_ROOT)/ace/ACE.h \
 $(ACE_ROOT)/ace/ACE.i \
 $(ACE_ROOT)/ace/Log_Priority.h \
 $(ACE_ROOT)/ace/Log_Record.i \
 $(ACE_ROOT)/ace/Get_Opt.h \
 $(ACE_ROOT)/ace/Get_Opt.i \
 $(ACE_ROOT)/ace/SOCK_Stream.h \
 $(ACE_ROOT)/ace/SOCK_IO.h \
 $(ACE_ROOT)/ace/SOCK.h \
 $(ACE_ROOT)/ace/Addr.h \
 $(ACE_ROOT)/ace/Addr.i \
 $(ACE_ROOT)/ace/IPC_SAP.h \
 $(ACE_ROOT)/ace/IPC_SAP.i \
 $(ACE_ROOT)/ace/SOCK.i \
 $(ACE_ROOT)/ace/SOCK_IO.i \
 $(ACE_ROOT)/ace/INET_Addr.h \
 $(ACE_ROOT)/ace/INET_Addr.i \
 $(ACE_ROOT)/ace/SOCK_Stream.i \
 $(ACE_ROOT)/ace/Synch_T.h \
 $(ACE_ROOT)/ace/Event_Handler.h \
 $(ACE_ROOT)/ace/Event_Handler.i \
 $(ACE_ROOT)/ace/Synch.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Complex.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Simple.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Simple.i \
 $(ACE_ROOT)/ace/SV_Semaphore_Complex.i \
 $(ACE_ROOT)/ace/Synch.i \
 $(ACE_ROOT)/ace/Synch_T.i \
 $(ACE_ROOT)/ace/Thread.h \
 $(ACE_ROOT)/ace/Thread.i \
 $(ACE_ROOT)/ace/Atomic_Op.i \
 $(ACE_ROOT)/ace/Synch_T.cpp \
 $(ACE_ROOT)/ace/Hash_Map_Manager.h \
 $(ACE_ROOT)/ace/Hash_Map_Manager.cpp \
 $(ACE_ROOT)/ace/Service_Config.h \
 $(ACE_ROOT)/ace/Service_Object.h \
 $(ACE_ROOT)/ace/Shared_Object.h \
 $(ACE_ROOT)/ace/Shared_Object.i \
 $(ACE_ROOT)/ace/Service_Object.i \
 $(ACE_ROOT)/ace/Signal.h \
 $(ACE_ROOT)/ace/Containers.h \
 $(ACE_ROOT)/ace/Containers.i \
 $(ACE_ROOT)/ace/Containers_T.h \
 $(ACE_ROOT)/ace/Containers_T.i \
 $(ACE_ROOT)/ace/Containers_T.cpp \
 $(ACE_ROOT)/ace/Malloc.h \
 $(ACE_ROOT)/ace/Malloc_Base.h \
 $(ACE_ROOT)/ace/Malloc.i \
 $(ACE_ROOT)/ace/Malloc_T.h \
 $(ACE_ROOT)/ace/Free_List.h \
 $(ACE_ROOT)/ace/Free_List.i \
 $(ACE_ROOT)/ace/Free_List.cpp \
 $(ACE_ROOT)/ace/Malloc_T.i \
 $(ACE_ROOT)/ace/Malloc_T.cpp \
 $(ACE_ROOT)/ace/Memory_Pool.h \
 $(ACE_ROOT)/ace/Mem_Map.h \
 $(ACE_ROOT)/ace/Mem_Map.i \
 $(ACE_ROOT)/ace/Memory_Pool.i \
 $(ACE_ROOT)/ace/Signal.i \
 $(ACE_ROOT)/ace/Object_Manager.h \
 $(ACE_ROOT)/ace/Object_Manager.i \
 $(ACE_ROOT)/ace/Managed_Object.h \
 $(ACE_ROOT)/ace/Managed_Object.i \
 $(ACE_ROOT)/ace/Managed_Object.cpp \
 $(ACE_ROOT)/ace/SString.h \
 $(ACE_ROOT)/ace/SString.i \
 $(ACE_ROOT)/ace/Service_Config.i \
 $(ACE_ROOT)/ace/Reactor.h \
 $(ACE_ROOT)/ace/Handle_Set.h \
 $(ACE_ROOT)/ace/Handle_Set.i \
 $(ACE_ROOT)/ace/Timer_Queue.h \
 $(ACE_ROOT)/ace/Timer_Queue_T.h \
 $(ACE_ROOT)/ace/Timer_Queue_T.i \
 $(ACE_ROOT)/ace/Timer_Queue_T.cpp \
 $(ACE_ROOT)/ace/Reactor.i \
 $(ACE_ROOT)/ace/Reactor_Impl.h \
 $(ACE_ROOT)/ace/Svc_Conf_Tokens.h \
 $(ACE_ROOT)/ace/SOCK_Acceptor.h \
 $(ACE_ROOT)/ace/Time_Value.h \
 $(ACE_ROOT)/ace/SOCK_Acceptor.i \
 $(ACE_ROOT)/ace/SOCK_Connector.h \
 $(ACE_ROOT)/ace/SOCK_Connector.i \
 $(ACE_ROOT)/ace/Strategies.h \
 $(ACE_ROOT)/ace/Strategies_T.h \
 $(ACE_ROOT)/ace/Synch_Options.h \
 $(ACE_ROOT)/ace/Synch_Options.i \
 $(ACE_ROOT)/ace/Thread_Manager.h \
 $(ACE_ROOT)/ace/Thread_Manager.i \
 $(ACE_ROOT)/ace/Strategies_T.i \
 $(ACE_ROOT)/ace/Strategies_T.cpp \
 $(ACE_ROOT)/ace/Service_Repository.h \
 $(ACE_ROOT)/ace/Service_Types.h \
 $(ACE_ROOT)/ace/Service_Types.i \
 $(ACE_ROOT)/ace/Service_Repository.i \
 $(ACE_ROOT)/ace/WFMO_Reactor.h \
 $(ACE_ROOT)/ace/Message_Queue.h \
 $(ACE_ROOT)/ace/Message_Block.h \
 $(ACE_ROOT)/ace/Message_Block.i \
 $(ACE_ROOT)/ace/Message_Block_T.h \
 $(ACE_ROOT)/ace/Message_Block_T.i \
 $(ACE_ROOT)/ace/Message_Block_T.cpp \
 $(ACE_ROOT)/ace/IO_Cntl_Msg.h \
 $(ACE_ROOT)/ace/Message_Queue_T.h \
 $(ACE_ROOT)/ace/Message_Queue_T.i \
 $(ACE_ROOT)/ace/Message_Queue_T.cpp \
 $(ACE_ROOT)/ace/Message_Queue.i \
 $(ACE_ROOT)/ace/WFMO_Reactor.i \
 $(ACE_ROOT)/ace/Strategies.i \
 $(ACE_ROOT)/ace/Connector.h \
 $(ACE_ROOT)/ace/Map_Manager.h \
 $(ACE_ROOT)/ace/Map_Manager.i \
 $(ACE_ROOT)/ace/Map_Manager.cpp \
 $(ACE_ROOT)/ace/Svc_Handler.h \
 $(ACE_ROOT)/ace/Task.h \
 $(ACE_ROOT)/ace/Task.i \
 $(ACE_ROOT)/ace/Task_T.h \
 $(ACE_ROOT)/ace/Task_T.i \
 $(ACE_ROOT)/ace/Task_T.cpp \
 $(ACE_ROOT)/ace/Module.h \
 $(ACE_ROOT)/ace/Module.i \
 $(ACE_ROOT)/ace/Module.cpp \
 $(ACE_ROOT)/ace/Stream_Modules.h \
 $(ACE_ROOT)/ace/Stream_Modules.i \
 $(ACE_ROOT)/ace/Stream_Modules.cpp \
 $(ACE_ROOT)/ace/Svc_Handler.i \
 $(ACE_ROOT)/ace/Svc_Handler.cpp \
 $(ACE_ROOT)/ace/Dynamic.h \
 $(ACE_ROOT)/ace/Singleton.h \
 $(ACE_ROOT)/ace/Singleton.i \
 $(ACE_ROOT)/ace/Singleton.cpp \
 $(ACE_ROOT)/ace/Dynamic.i \
 $(ACE_ROOT)/ace/Connector.i \
 $(ACE_ROOT)/ace/Connector.cpp \
 $(ACE_ROOT)/ace/Acceptor.h \
 $(ACE_ROOT)/ace/Acceptor.i \
 $(ACE_ROOT)/ace/Acceptor.cpp \
 $(TAO_ROOT)/tao/Align.h \
 $(TAO_ROOT)/tao/Environment.h \
 $(TAO_ROOT)/tao/Environment.i \
 $(TAO_ROOT)/tao/ORB.h \
 $(TAO_ROOT)/tao/Sequence.h \
 $(TAO_ROOT)/tao/Sequence.i \
 $(TAO_ROOT)/tao/Sequence_T.h \
 $(TAO_ROOT)/tao/Sequence_T.i \
 $(TAO_ROOT)/tao/Sequence_T.cpp \
 $(TAO_ROOT)/tao/Object_KeyC.h \
 $(TAO_ROOT)/tao/Object_KeyC.i \
 $(TAO_ROOT)/tao/Union.h \
 $(TAO_ROOT)/tao/ORB.i \
 $(TAO_ROOT)/tao/try_macros.h \
 $(TAO_ROOT)/tao/Exception.h \
 $(TAO_ROOT)/tao/Exception.i \
 $(TAO_ROOT)/tao/Any.h \
 $(TAO_ROOT)/tao/Any.i \
 $(TAO_ROOT)/tao/NVList.h \
 $(TAO_ROOT)/tao/NVList.i \
 $(TAO_ROOT)/tao/Principal.h \
 $(TAO_ROOT)/tao/Principal.i \
 $(TAO_ROOT)/tao/Request.h \
 $(TAO_ROOT)/tao/Request.i \
 $(TAO_ROOT)/tao/Stub.h \
 $(TAO_ROOT)/tao/Stub.i \
 $(TAO_ROOT)/tao/Object.h \
 $(TAO_ROOT)/tao/Object.i \
 $(TAO_ROOT)/tao/varout.h \
 $(TAO_ROOT)/tao/varout.i \
 $(TAO_ROOT)/tao/varout.cpp \
 $(TAO_ROOT)/tao/Typecode.h \
 $(TAO_ROOT)/tao/Typecode.i \
 $(TAO_ROOT)/tao/Marshal.h \
 $(TAO_ROOT)/tao/Marshal.i \
 $(TAO_ROOT)/tao/singletons.h \
 $(TAO_ROOT)/tao/CDR.h \
 $(TAO_ROOT)/tao/CDR.i \
 $(TAO_ROOT)/tao/PolicyC.h \
 $(TAO_ROOT)/tao/PolicyC.i \
 $(TAO_ROOT)/tao/CurrentC.h \
 $(TAO_ROOT)/tao/CurrentC.i \
 $(TAO_ROOT)/tao/POA.h \
 $(TAO_ROOT)/tao/POAC.h \
 $(TAO_ROOT)/tao/POAC.i \
 $(TAO_ROOT)/tao/Servant_Base.h \
 $(TAO_ROOT)/tao/POAS.h \
 $(TAO_ROOT)/tao/POA_CORBA.h \
 $(TAO_ROOT)/tao/DynAnyC.h \
 $(TAO_ROOT)/tao/DynAnyC.i \
 $(TAO_ROOT)/tao/POAS.i \
 $(TAO_ROOT)/tao/Active_Object_Map.h \
 $(TAO_ROOT)/tao/Active_Object_Map.i \
 $(TAO_ROOT)/tao/POA.i \
 $(TAO_ROOT)/tao/poa_macros.h \
 $(TAO_ROOT)/tao/params.h \
 $(TAO_ROOT)/tao/params.i \
 $(TAO_ROOT)/tao/Connect.h \
 $(TAO_ROOT)/tao/Connect.i \
 $(TAO_ROOT)/tao/ORB_Core.h \
 $(TAO_ROOT)/tao/ORB_Core.i \
 $(ACE_ROOT)/ace/Dynamic_Service.h \
 $(ACE_ROOT)/ace/Dynamic_Service.cpp \
 $(TAO_ROOT)/tao/Operation_Table.h \
 $(TAO_ROOT)/tao/debug.h \
 $(TAO_ROOT)/tao/Client_Strategy_Factory.h \
 $(TAO_ROOT)/tao/Server_Strategy_Factory.h \
 $(TAO_ROOT)/tao/default_client.h \
 $(TAO_ROOT)/tao/default_client.i \
 $(TAO_ROOT)/tao/default_server.h \
 $(TAO_ROOT)/tao/ORB_Strategies_T.h \
 $(TAO_ROOT)/tao/ORB_Strategies_T.i \
 $(TAO_ROOT)/tao/ORB_Strategies_T.cpp \
 $(TAO_ROOT)/tao/default_server.i \
 $(TAO_ROOT)/tao/IIOP_Object.h \
 $(TAO_ROOT)/tao/IIOP_Object.i \
 $(TAO_ROOT)/tao/IIOP_ORB.h \
 $(TAO_ROOT)/tao/IIOP_ORB.i \
 $(TAO_ROOT)/tao/CDR_Interpreter.h \
 $(TAO_ROOT)/tao/GIOP.h \
 $(TAO_ROOT)/tao/GIOP.i \
 $(TAO_ROOT)/tao/Invocation.h \
 $(TAO_ROOT)/tao/Invocation.i \
 $(TAO_ROOT)/tao/Server_Request.h \
 $(TAO_ROOT)/tao/Server_Request.i \
 $(TAO_ROOT)/tao/InconsistentTypeCodeC.h \
 $(TAO_ROOT)/tao/DynAny_i.h \
 Video_RepositoryC.h Video_RepositoryC.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Trader/Trader.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosTradingS.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosTradingC.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/orbsvcs_export.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosTradingC.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosTradingS_T.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosTradingS_T.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosTradingS_T.cpp \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosTradingS.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Trader/Trader_Utils.h \
 $(TAO_ROOT)/orbsvcs/tests/AVStreams/mpeg/source/mpeg_shared/ReceiverC.h \
 $(TAO_ROOT)/orbsvcs/tests/AVStreams/mpeg/source/mpeg_shared/ReceiverC.i \
 $(TAO_ROOT)/orbsvcs/tests/AVStreams/mpeg/source/mpeg_shared/MMDevice_ExporterC.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosPropertyServiceC.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosPropertyServiceC.i \
 $(TAO_ROOT)/orbsvcs/tests/AVStreams/mpeg/source/mpeg_shared/MMDevice_ExporterC.i
.obj/Server_Discovery.o .obj/Server_Discovery.so .shobj/Server_Discovery.o .shobj/Server_Discovery.so: Server_Discovery.cpp \
 Server_0005fDiscovery_0005fUtil.h Trader_Client.h \
 $(TAO_ROOT)/tao/TAO.h \
 $(TAO_ROOT)/tao/corba.h \
 $(TAO_ROOT)/tao/orbconf.h \
 $(ACE_ROOT)/ace/OS.h \
 $(ACE_ROOT)/ace/inc_user_config.h \
 $(ACE_ROOT)/ace/config.h \
 $(ACE_ROOT)/ace/config-g++-common.h \
 $(ACE_ROOT)/ace/streams.h \
 $(ACE_ROOT)/ace/Basic_Types.h \
 $(ACE_ROOT)/ace/Basic_Types.i \
 $(ACE_ROOT)/ace/OS.i \
 $(ACE_ROOT)/ace/Trace.h \
 $(ACE_ROOT)/ace/Log_Msg.h \
 $(ACE_ROOT)/ace/Log_Record.h \
 $(ACE_ROOT)/ace/ACE.h \
 $(ACE_ROOT)/ace/ACE.i \
 $(ACE_ROOT)/ace/Log_Priority.h \
 $(ACE_ROOT)/ace/Log_Record.i \
 $(ACE_ROOT)/ace/Get_Opt.h \
 $(ACE_ROOT)/ace/Get_Opt.i \
 $(ACE_ROOT)/ace/SOCK_Stream.h \
 $(ACE_ROOT)/ace/SOCK_IO.h \
 $(ACE_ROOT)/ace/SOCK.h \
 $(ACE_ROOT)/ace/Addr.h \
 $(ACE_ROOT)/ace/Addr.i \
 $(ACE_ROOT)/ace/IPC_SAP.h \
 $(ACE_ROOT)/ace/IPC_SAP.i \
 $(ACE_ROOT)/ace/SOCK.i \
 $(ACE_ROOT)/ace/SOCK_IO.i \
 $(ACE_ROOT)/ace/INET_Addr.h \
 $(ACE_ROOT)/ace/INET_Addr.i \
 $(ACE_ROOT)/ace/SOCK_Stream.i \
 $(ACE_ROOT)/ace/Synch_T.h \
 $(ACE_ROOT)/ace/Event_Handler.h \
 $(ACE_ROOT)/ace/Event_Handler.i \
 $(ACE_ROOT)/ace/Synch.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Complex.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Simple.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Simple.i \
 $(ACE_ROOT)/ace/SV_Semaphore_Complex.i \
 $(ACE_ROOT)/ace/Synch.i \
 $(ACE_ROOT)/ace/Synch_T.i \
 $(ACE_ROOT)/ace/Thread.h \
 $(ACE_ROOT)/ace/Thread.i \
 $(ACE_ROOT)/ace/Atomic_Op.i \
 $(ACE_ROOT)/ace/Synch_T.cpp \
 $(ACE_ROOT)/ace/Hash_Map_Manager.h \
 $(ACE_ROOT)/ace/Hash_Map_Manager.cpp \
 $(ACE_ROOT)/ace/Service_Config.h \
 $(ACE_ROOT)/ace/Service_Object.h \
 $(ACE_ROOT)/ace/Shared_Object.h \
 $(ACE_ROOT)/ace/Shared_Object.i \
 $(ACE_ROOT)/ace/Service_Object.i \
 $(ACE_ROOT)/ace/Signal.h \
 $(ACE_ROOT)/ace/Containers.h \
 $(ACE_ROOT)/ace/Containers.i \
 $(ACE_ROOT)/ace/Containers_T.h \
 $(ACE_ROOT)/ace/Containers_T.i \
 $(ACE_ROOT)/ace/Containers_T.cpp \
 $(ACE_ROOT)/ace/Malloc.h \
 $(ACE_ROOT)/ace/Malloc_Base.h \
 $(ACE_ROOT)/ace/Malloc.i \
 $(ACE_ROOT)/ace/Malloc_T.h \
 $(ACE_ROOT)/ace/Free_List.h \
 $(ACE_ROOT)/ace/Free_List.i \
 $(ACE_ROOT)/ace/Free_List.cpp \
 $(ACE_ROOT)/ace/Malloc_T.i \
 $(ACE_ROOT)/ace/Malloc_T.cpp \
 $(ACE_ROOT)/ace/Memory_Pool.h \
 $(ACE_ROOT)/ace/Mem_Map.h \
 $(ACE_ROOT)/ace/Mem_Map.i \
 $(ACE_ROOT)/ace/Memory_Pool.i \
 $(ACE_ROOT)/ace/Signal.i \
 $(ACE_ROOT)/ace/Object_Manager.h \
 $(ACE_ROOT)/ace/Object_Manager.i \
 $(ACE_ROOT)/ace/Managed_Object.h \
 $(ACE_ROOT)/ace/Managed_Object.i \
 $(ACE_ROOT)/ace/Managed_Object.cpp \
 $(ACE_ROOT)/ace/SString.h \
 $(ACE_ROOT)/ace/SString.i \
 $(ACE_ROOT)/ace/Service_Config.i \
 $(ACE_ROOT)/ace/Reactor.h \
 $(ACE_ROOT)/ace/Handle_Set.h \
 $(ACE_ROOT)/ace/Handle_Set.i \
 $(ACE_ROOT)/ace/Timer_Queue.h \
 $(ACE_ROOT)/ace/Timer_Queue_T.h \
 $(ACE_ROOT)/ace/Timer_Queue_T.i \
 $(ACE_ROOT)/ace/Timer_Queue_T.cpp \
 $(ACE_ROOT)/ace/Reactor.i \
 $(ACE_ROOT)/ace/Reactor_Impl.h \
 $(ACE_ROOT)/ace/Svc_Conf_Tokens.h \
 $(ACE_ROOT)/ace/SOCK_Acceptor.h \
 $(ACE_ROOT)/ace/Time_Value.h \
 $(ACE_ROOT)/ace/SOCK_Acceptor.i \
 $(ACE_ROOT)/ace/SOCK_Connector.h \
 $(ACE_ROOT)/ace/SOCK_Connector.i \
 $(ACE_ROOT)/ace/Strategies.h \
 $(ACE_ROOT)/ace/Strategies_T.h \
 $(ACE_ROOT)/ace/Synch_Options.h \
 $(ACE_ROOT)/ace/Synch_Options.i \
 $(ACE_ROOT)/ace/Thread_Manager.h \
 $(ACE_ROOT)/ace/Thread_Manager.i \
 $(ACE_ROOT)/ace/Strategies_T.i \
 $(ACE_ROOT)/ace/Strategies_T.cpp \
 $(ACE_ROOT)/ace/Service_Repository.h \
 $(ACE_ROOT)/ace/Service_Types.h \
 $(ACE_ROOT)/ace/Service_Types.i \
 $(ACE_ROOT)/ace/Service_Repository.i \
 $(ACE_ROOT)/ace/WFMO_Reactor.h \
 $(ACE_ROOT)/ace/Message_Queue.h \
 $(ACE_ROOT)/ace/Message_Block.h \
 $(ACE_ROOT)/ace/Message_Block.i \
 $(ACE_ROOT)/ace/Message_Block_T.h \
 $(ACE_ROOT)/ace/Message_Block_T.i \
 $(ACE_ROOT)/ace/Message_Block_T.cpp \
 $(ACE_ROOT)/ace/IO_Cntl_Msg.h \
 $(ACE_ROOT)/ace/Message_Queue_T.h \
 $(ACE_ROOT)/ace/Message_Queue_T.i \
 $(ACE_ROOT)/ace/Message_Queue_T.cpp \
 $(ACE_ROOT)/ace/Message_Queue.i \
 $(ACE_ROOT)/ace/WFMO_Reactor.i \
 $(ACE_ROOT)/ace/Strategies.i \
 $(ACE_ROOT)/ace/Connector.h \
 $(ACE_ROOT)/ace/Map_Manager.h \
 $(ACE_ROOT)/ace/Map_Manager.i \
 $(ACE_ROOT)/ace/Map_Manager.cpp \
 $(ACE_ROOT)/ace/Svc_Handler.h \
 $(ACE_ROOT)/ace/Task.h \
 $(ACE_ROOT)/ace/Task.i \
 $(ACE_ROOT)/ace/Task_T.h \
 $(ACE_ROOT)/ace/Task_T.i \
 $(ACE_ROOT)/ace/Task_T.cpp \
 $(ACE_ROOT)/ace/Module.h \
 $(ACE_ROOT)/ace/Module.i \
 $(ACE_ROOT)/ace/Module.cpp \
 $(ACE_ROOT)/ace/Stream_Modules.h \
 $(ACE_ROOT)/ace/Stream_Modules.i \
 $(ACE_ROOT)/ace/Stream_Modules.cpp \
 $(ACE_ROOT)/ace/Svc_Handler.i \
 $(ACE_ROOT)/ace/Svc_Handler.cpp \
 $(ACE_ROOT)/ace/Dynamic.h \
 $(ACE_ROOT)/ace/Singleton.h \
 $(ACE_ROOT)/ace/Singleton.i \
 $(ACE_ROOT)/ace/Singleton.cpp \
 $(ACE_ROOT)/ace/Dynamic.i \
 $(ACE_ROOT)/ace/Connector.i \
 $(ACE_ROOT)/ace/Connector.cpp \
 $(ACE_ROOT)/ace/Acceptor.h \
 $(ACE_ROOT)/ace/Acceptor.i \
 $(ACE_ROOT)/ace/Acceptor.cpp \
 $(TAO_ROOT)/tao/Align.h \
 $(TAO_ROOT)/tao/Environment.h \
 $(TAO_ROOT)/tao/Environment.i \
 $(TAO_ROOT)/tao/ORB.h \
 $(TAO_ROOT)/tao/Sequence.h \
 $(TAO_ROOT)/tao/Sequence.i \
 $(TAO_ROOT)/tao/Sequence_T.h \
 $(TAO_ROOT)/tao/Sequence_T.i \
 $(TAO_ROOT)/tao/Sequence_T.cpp \
 $(TAO_ROOT)/tao/Object_KeyC.h \
 $(TAO_ROOT)/tao/Object_KeyC.i \
 $(TAO_ROOT)/tao/Union.h \
 $(TAO_ROOT)/tao/ORB.i \
 $(TAO_ROOT)/tao/try_macros.h \
 $(TAO_ROOT)/tao/Exception.h \
 $(TAO_ROOT)/tao/Exception.i \
 $(TAO_ROOT)/tao/Any.h \
 $(TAO_ROOT)/tao/Any.i \
 $(TAO_ROOT)/tao/NVList.h \
 $(TAO_ROOT)/tao/NVList.i \
 $(TAO_ROOT)/tao/Principal.h \
 $(TAO_ROOT)/tao/Principal.i \
 $(TAO_ROOT)/tao/Request.h \
 $(TAO_ROOT)/tao/Request.i \
 $(TAO_ROOT)/tao/Stub.h \
 $(TAO_ROOT)/tao/Stub.i \
 $(TAO_ROOT)/tao/Object.h \
 $(TAO_ROOT)/tao/Object.i \
 $(TAO_ROOT)/tao/varout.h \
 $(TAO_ROOT)/tao/varout.i \
 $(TAO_ROOT)/tao/varout.cpp \
 $(TAO_ROOT)/tao/Typecode.h \
 $(TAO_ROOT)/tao/Typecode.i \
 $(TAO_ROOT)/tao/Marshal.h \
 $(TAO_ROOT)/tao/Marshal.i \
 $(TAO_ROOT)/tao/singletons.h \
 $(TAO_ROOT)/tao/CDR.h \
 $(TAO_ROOT)/tao/CDR.i \
 $(TAO_ROOT)/tao/PolicyC.h \
 $(TAO_ROOT)/tao/PolicyC.i \
 $(TAO_ROOT)/tao/CurrentC.h \
 $(TAO_ROOT)/tao/CurrentC.i \
 $(TAO_ROOT)/tao/POA.h \
 $(TAO_ROOT)/tao/POAC.h \
 $(TAO_ROOT)/tao/POAC.i \
 $(TAO_ROOT)/tao/Servant_Base.h \
 $(TAO_ROOT)/tao/POAS.h \
 $(TAO_ROOT)/tao/POA_CORBA.h \
 $(TAO_ROOT)/tao/DynAnyC.h \
 $(TAO_ROOT)/tao/DynAnyC.i \
 $(TAO_ROOT)/tao/POAS.i \
 $(TAO_ROOT)/tao/Active_Object_Map.h \
 $(TAO_ROOT)/tao/Active_Object_Map.i \
 $(TAO_ROOT)/tao/POA.i \
 $(TAO_ROOT)/tao/poa_macros.h \
 $(TAO_ROOT)/tao/params.h \
 $(TAO_ROOT)/tao/params.i \
 $(TAO_ROOT)/tao/Connect.h \
 $(TAO_ROOT)/tao/Connect.i \
 $(TAO_ROOT)/tao/ORB_Core.h \
 $(TAO_ROOT)/tao/ORB_Core.i \
 $(ACE_ROOT)/ace/Dynamic_Service.h \
 $(ACE_ROOT)/ace/Dynamic_Service.cpp \
 $(TAO_ROOT)/tao/Operation_Table.h \
 $(TAO_ROOT)/tao/debug.h \
 $(TAO_ROOT)/tao/Client_Strategy_Factory.h \
 $(TAO_ROOT)/tao/Server_Strategy_Factory.h \
 $(TAO_ROOT)/tao/default_client.h \
 $(TAO_ROOT)/tao/default_client.i \
 $(TAO_ROOT)/tao/default_server.h \
 $(TAO_ROOT)/tao/ORB_Strategies_T.h \
 $(TAO_ROOT)/tao/ORB_Strategies_T.i \
 $(TAO_ROOT)/tao/ORB_Strategies_T.cpp \
 $(TAO_ROOT)/tao/default_server.i \
 $(TAO_ROOT)/tao/IIOP_Object.h \
 $(TAO_ROOT)/tao/IIOP_Object.i \
 $(TAO_ROOT)/tao/IIOP_ORB.h \
 $(TAO_ROOT)/tao/IIOP_ORB.i \
 $(TAO_ROOT)/tao/CDR_Interpreter.h \
 $(TAO_ROOT)/tao/GIOP.h \
 $(TAO_ROOT)/tao/GIOP.i \
 $(TAO_ROOT)/tao/Invocation.h \
 $(TAO_ROOT)/tao/Invocation.i \
 $(TAO_ROOT)/tao/Server_Request.h \
 $(TAO_ROOT)/tao/Server_Request.i \
 $(TAO_ROOT)/tao/InconsistentTypeCodeC.h \
 $(TAO_ROOT)/tao/DynAny_i.h \
 Video_RepositoryC.h Video_RepositoryC.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Trader/Trader.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosTradingS.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosTradingC.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/orbsvcs_export.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosTradingC.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosTradingS_T.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosTradingS_T.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosTradingS_T.cpp \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosTradingS.i \
 $(TAO_ROOT)/orbsvcs/orbsvcs/Trader/Trader_Utils.h \
 $(TAO_ROOT)/orbsvcs/tests/AVStreams/mpeg/source/mpeg_shared/ReceiverC.h \
 $(TAO_ROOT)/orbsvcs/tests/AVStreams/mpeg/source/mpeg_shared/ReceiverC.i \
 $(TAO_ROOT)/orbsvcs/tests/AVStreams/mpeg/source/mpeg_shared/MMDevice_ExporterC.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosPropertyServiceC.h \
 $(TAO_ROOT)/orbsvcs/orbsvcs/CosPropertyServiceC.i \
 $(TAO_ROOT)/orbsvcs/tests/AVStreams/mpeg/source/mpeg_shared/MMDevice_ExporterC.i

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
