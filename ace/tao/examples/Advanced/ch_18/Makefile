#----------------------------------------------------------------------------
#
# Makefile,v 1.6 2001/03/07 19:36:38 irfan Exp
#
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
#	Local macros
#----------------------------------------------------------------------------

ifndef TAO_ROOT
  TAO_ROOT = $(ACE_ROOT)/TAO
endif

LDLIBS = -lTAO_CosNaming -lTAO -lTAO_PortableServer
IDL_FILES = CCS
IDL_SRC = CCSC.cpp CCSS.cpp
IDL_HDR = CCSC.h CCSS.h

PROG_SRCS = \
	client.cpp \
	server.cpp \
	icp.cpp

SRC = $(IDL_SRC) $(PROG_SRCS)

SIMPLE_CLT_OBJS = \
		CCSC.o \
		CCSS.o \
		client.o 

SIMPLE_SVR_OBJS = \
		CCSC.o \
		CCSS.o \
		server.o \
		icp.o


BIN2 = server \
      client

#### If the TAO orbsvcs library wasn't built with sufficient components,
#### don't try to build here.
TAO_ORBSVCS := $(shell sh $(ACE_ROOT)/bin/ace_components --orbsvcs)
ifeq (Naming,$(findstring Naming,$(TAO_ORBSVCS)))
  BIN = $(BIN2)
endif # Naming

BUILD = $(BIN)
VLDLIBS = $(LDLIBS:%=%$(VAR))
VBIN = $(BIN:%=%$(VAR))

#----------------------------------------------------------------------------
#	Include macros and targets
#----------------------------------------------------------------------------

include $(ACE_ROOT)/include/makeinclude/wrapper_macros.GNU
include $(ACE_ROOT)/include/makeinclude/macros.GNU
include $(TAO_ROOT)/rules.tao.GNU
include $(ACE_ROOT)/include/makeinclude/rules.common.GNU
include $(ACE_ROOT)/include/makeinclude/rules.nonested.GNU
include $(ACE_ROOT)/include/makeinclude/rules.local.GNU
include $(TAO_ROOT)/taoconfig.mk

#----------------------------------------------------------------------------
#	Local targets
#----------------------------------------------------------------------------
LDFLAGS += -L$(TAO_ROOT)/orbsvcs/orbsvcs -L$(TAO_ROOT)/tao -L$(ACE_ROOT)/ace
CPPFLAGS += -I$(TAO_ROOT)/orbsvcs

.PRECIOUS: CCSC.cpp CCSC.i CCSC.h
.PRECIOUS: CCSS.cpp CCSS.i CCSS.h
.PRECIOUS: CCSS_T.cpp CCSS_T.i CCSS_T.h

override TAO_IDLFLAGS += -Ge 0
CCFLAGS += -fimplicit-templates -frtti -O0

$(IDL_SRC): CCS.idl
server:	$(addprefix $(VDIR),$(SIMPLE_SVR_OBJS))
	$(LINK.cc) $(LDFLAGS) -o $@ $^ $(VLDLIBS) $(POSTLINK)

client:	$(addprefix $(VDIR),$(SIMPLE_CLT_OBJS))
	$(LINK.cc) $(LDFLAGS) -o $@ $^ $(VLDLIBS) $(POSTLINK)

realclean: clean
	-/bin/$(RM) -rf CCSC.* CCSS.* CCSS_T.* CCS.h

# DO NOT DELETE THIS LINE -- g++dep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.






