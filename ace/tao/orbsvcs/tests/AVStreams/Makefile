#----------------------------------------------------------------------------
#
# Makefile,v 1.19 2001/03/27 11:40:59 irfan Exp
#
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
#	Local macros
#----------------------------------------------------------------------------

DIRS =	Component_Switching \
	Simple_Two_Stage \
	Simple_Three_Stage \
	Asynch_Three_Stage \
	Latency \
	Pluggable \
	Full_Profile \
	Multicast \
	Multicast_Full_Profile 

# mpeg server_discovery

ifndef TAO_ROOT
  TAO_ROOT = $(ACE_ROOT)/TAO
endif

#----------------------------------------------------------------------------
#	Include macros and targets
#----------------------------------------------------------------------------

include	$(ACE_ROOT)/include/makeinclude/wrapper_macros.GNU
include	$(ACE_ROOT)/include/makeinclude/macros.GNU
include $(TAO_ROOT)/rules.tao.GNU
include	$(ACE_ROOT)/include/makeinclude/rules.common.GNU
include	$(ACE_ROOT)/include/makeinclude/rules.nested.GNU
include	$(ACE_ROOT)/include/makeinclude/rules.nolocal.GNU
