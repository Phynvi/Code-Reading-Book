#	$NetBSD: Makefile,v 1.12.2.1 1997/11/20 09:06:41 mrg Exp $
#	@(#)Makefile	8.1 (Berkeley) 5/31/93

PROG=	phantasia
SRCS=	fight.c gamesupport.c interplayer.c io.c main.c misc.c phantglobs.c

DPADD=	${LIBM} ${LIBCURSES} ${LIBTERM} ${LIBCOMPAT}
LDADD=	-lm -lcurses -ltermlib -lcompat
HIDEGAME=hidegame
SETGIDGAME=yes
USETBL=
MAN=	phantasia.6
CLEANFILES+=map setup setup.o host_phantglobs.o

all: setup phantasia

setup: host_phantglobs.o setup.o monsters.asc ${LIBM} 
	${HOST_CC} host_phantglobs.o setup.o -o ${.TARGET} -lm

host_phantglobs.o: ${.CURDIR}/phantglobs.c
	${HOST_COMPILE.c} -o host_phantglobs.o ${.CURDIR}/phantglobs.c

setup.o: ${.CURDIR}/setup.c
	${HOST_COMPILE.c} ${.CURDIR}/setup.c

afterinstall: 
	./setup -m ${.CURDIR}/monsters.asc
	chown games:games ${DESTDIR}/var/games/phantasia/*

# Make Phantasia map.  Change the map commands reflect your installation.
# PLOTDEVICE is used for plotting the map.  Change as appropriate.

map: map.c
	${CC} -O ${.CURDIR}/map.c -lplot -o ${.TARGET}
	./map | plot > /dev/tty

.include <bsd.prog.mk>
