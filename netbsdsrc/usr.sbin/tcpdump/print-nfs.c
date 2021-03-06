/*	$NetBSD: print-nfs.c,v 1.8 1997/10/03 19:55:25 christos Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that: (1) source code distributions
 * retain the above copyright notice and this paragraph in its entirety, (2)
 * distributions including binary code include the above copyright notice and
 * this paragraph in its entirety in the documentation or other materials
 * provided with the distribution, and (3) all advertising materials mentioning
 * features or use of this software display the following acknowledgement:
 * ``This product includes software developed by the University of California,
 * Lawrence Berkeley Laboratory and its contributors.'' Neither the name of
 * the University nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior
 * written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#include <sys/cdefs.h>
#ifndef lint
#if 0
static const char rcsid[] =
    "@(#) Header: print-nfs.c,v 1.65 97/08/17 13:24:22 leres Exp  (LBL)";
#else
__RCSID("$NetBSD: print-nfs.c,v 1.8 1997/10/03 19:55:25 christos Exp $");
#endif
#endif

#include <sys/param.h>
#include <sys/time.h>
#include <sys/socket.h>

#if __STDC__
struct mbuf;
struct rtentry;
#endif
#include <net/if.h>

#ifdef __NetBSD__
#include <net/if_ether.h>
#else
#include <netinet/if_ether.h>
#endif
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>

#include <rpc/rpc.h>

#include <ctype.h>
#include <pcap.h>
#include <stdio.h>
#include <string.h>

#include "interface.h"
#include "addrtoname.h"

#include "nfs.h"
#include "nfsfh.h"

static void nfs_printfh(const u_int32_t *, const u_int);
static void xid_map_enter(const struct rpc_msg *, const struct ip *);
static int32_t xid_map_find(const struct rpc_msg *, const struct ip *,
			  u_int32_t *, u_int32_t *);
static void interp_reply(const struct rpc_msg *, u_int32_t, u_int32_t, int);
static const u_int32_t *parse_post_op_attr(const u_int32_t *, int);
static void print_sattr3(const struct nfsv3_sattr *sa3, int verbose);
static int print_int64(const u_int32_t *dp, int how);

/*
 * Mapping of old NFS Version 2 RPC numbers to generic numbers.
 */
u_int32_t nfsv3_procid[NFS_NPROCS] = {
	NFSPROC_NULL,
	NFSPROC_GETATTR,
	NFSPROC_SETATTR,
	NFSPROC_NOOP,
	NFSPROC_LOOKUP,
	NFSPROC_READLINK,
	NFSPROC_READ,
	NFSPROC_NOOP,
	NFSPROC_WRITE,
	NFSPROC_CREATE,
	NFSPROC_REMOVE,
	NFSPROC_RENAME,
	NFSPROC_LINK,
	NFSPROC_SYMLINK,
	NFSPROC_MKDIR,
	NFSPROC_RMDIR,
	NFSPROC_READDIR,
	NFSPROC_FSSTAT,
	NFSPROC_NOOP,
	NFSPROC_NOOP,
	NFSPROC_NOOP,
	NFSPROC_NOOP,
	NFSPROC_NOOP,
	NFSPROC_NOOP,
	NFSPROC_NOOP,
	NFSPROC_NOOP
};

const char *nfsv3_writemodes[NFSV3WRITE_NMODES] = {
	"unstable",
	"datasync",
	"filesync"
};

static struct tok type2str[] = {
	{ NFNON,	"NON" },
	{ NFREG,	"REG" },
	{ NFDIR,	"DIR" },
	{ NFBLK,	"BLK" },
	{ NFCHR,	"CHR" },
	{ NFLNK,	"LNK" },
	{ NFFIFO,	"FIFO" },
	{ 0,		NULL }
};

/*
 * Print out a 64-bit integer. This appears to be different on each system,
 * try to make the best of it. The integer stored as 2 consecutive XDR
 * encoded 32-bit integers, to which a pointer is passed.
 *
 * Assume that a system that has INT64_FORMAT defined, has a 64-bit
 * integer datatype and can print it.
 */ 

#define UNSIGNED 0
#define SIGNED   1
#define HEX      2

static int print_int64(const u_int32_t *dp, int how)
{
#ifdef INT64_FORMAT
	u_int64_t res;

	res = ((u_int64_t)ntohl(dp[0]) << 32) | (u_int64_t)ntohl(dp[1]);
	switch (how) {
	case SIGNED:
		printf(INT64_FORMAT, res);
		break;
	case UNSIGNED:
		printf(U_INT64_FORMAT, res);
		break;
	case HEX:
		printf(HEX_INT64_FORMAT, res);
		break;
	default:
		return (0);
	}
#else
#if 0
	int sign;
#endif
	/*
	 * XXX - throw upper 32 bits away.
	 * Could also go for hex: printf("0x%x%x", dp[0], dp[1]);
	 */
	if (sign)
		printf("%d", (int)dp[1]);
	else
		printf("%u", (unsigned int)dp[1]);
#endif
	return 1;
}

static const u_int32_t *
parse_sattr3(const u_int32_t *dp, struct nfsv3_sattr *sa3)
{
	register const u_int32_t *ep = (u_int32_t *)snapend;

	if (dp + 1 > ep)
		return (0);
	if ((sa3->sa_modeset = ntohl(*dp++))) {
		if (dp + 1 > ep)
			return (0);
		sa3->sa_mode = ntohl(*dp++);
	}

	if (dp + 1 > ep)
		return (0);
	if ((sa3->sa_uidset = ntohl(*dp++))) {
		if (dp + 1 > ep)
			return (0);
		sa3->sa_uid = ntohl(*dp++);
	}

	if (dp + 1 > ep)
		return (0);
	if ((sa3->sa_gidset = ntohl(*dp++))) {
		if (dp + 1 > ep)
			return (0);
		sa3->sa_gid = ntohl(*dp++);
	}

	if (dp + 1 > ep)
		return (0);
	if ((sa3->sa_sizeset = ntohl(*dp++))) {
		if (dp + 1 > ep)
			return (0);
		sa3->sa_size = ntohl(*dp++);
	}

	if (dp + 1 > ep)
		return (0);
	if ((sa3->sa_atimetype = ntohl(*dp++)) == NFSV3SATTRTIME_TOCLIENT) {
		if (dp + 2 > ep)
			return (0);
		sa3->sa_atime.nfsv3_sec = ntohl(*dp++);
		sa3->sa_atime.nfsv3_nsec = ntohl(*dp++);
	}

	if (dp + 1 > ep)
		return (0);
	if ((sa3->sa_mtimetype = ntohl(*dp++)) == NFSV3SATTRTIME_TOCLIENT) {
		if (dp + 2 > ep)
			return (0);
		sa3->sa_mtime.nfsv3_sec = ntohl(*dp++);
		sa3->sa_mtime.nfsv3_nsec = ntohl(*dp++);
	}

	return dp;
}
static int nfserr;		/* true if we error rather than trunc */

static void
print_sattr3(const struct nfsv3_sattr *sa3, int verbose)
{
	if (sa3->sa_modeset)
		printf(" mode %o", sa3->sa_mode);
	if (sa3->sa_uidset)
		printf(" uid %u", sa3->sa_uid);
	if (sa3->sa_gidset)
		printf(" gid %u", sa3->sa_gid);
	if (verbose > 1) {
		if (sa3->sa_atimetype == NFSV3SATTRTIME_TOCLIENT)
			printf(" atime %u.%06u", sa3->sa_atime.nfsv3_sec,
			       sa3->sa_atime.nfsv3_nsec);
		if (sa3->sa_mtimetype == NFSV3SATTRTIME_TOCLIENT)
			printf(" mtime %u.%06u", sa3->sa_mtime.nfsv3_sec,
			       sa3->sa_mtime.nfsv3_nsec);
	}
}

void
nfsreply_print(register const u_char *bp, u_int length,
	       register const u_char *bp2)
{
	register const struct rpc_msg *rp;
	register const struct ip *ip;
	u_int32_t proc, vers;

	nfserr = 0;		/* assume no error */
	rp = (const struct rpc_msg *)bp;
	ip = (const struct ip *)bp2;

	if (!nflag)
		(void)printf("%s.nfs > %s.%u: reply %s %d",
			     ipaddr_string(&ip->ip_src),
			     ipaddr_string(&ip->ip_dst),
			     (u_int32_t)ntohl(rp->rm_xid),
			     ntohl(rp->rm_reply.rp_stat) == MSG_ACCEPTED?
				     "ok":"ERR",
			     length);
	else
		(void)printf("%s.%u > %s.%u: reply %s %d",
			     ipaddr_string(&ip->ip_src),
			     NFS_PORT,
			     ipaddr_string(&ip->ip_dst),
			     (u_int32_t)ntohl(rp->rm_xid),
			     ntohl(rp->rm_reply.rp_stat) == MSG_ACCEPTED?
			     	"ok":"ERR",
			     length);

	if (xid_map_find(rp, ip, &proc, &vers) >= 0)
		interp_reply(rp, proc, vers, length);
}

/*
 * Return a pointer to the first file handle in the packet.
 * If the packet was truncated, return 0.
 */
static const u_int32_t *
parsereq(register const struct rpc_msg *rp, register u_int length)
{
	register const u_int32_t *dp;
	register u_int len;

	/*
	 * find the start of the req data (if we captured it)
	 */
	dp = (u_int32_t *)&rp->rm_call.cb_cred;
	TCHECK(dp[1]);
	len = ntohl(dp[1]);
	if (len < length) {
		dp += (len + (2 * sizeof(*dp) + 3)) / sizeof(*dp);
		TCHECK(dp[1]);
		len = ntohl(dp[1]);
		if (len < length) {
			dp += (len + (2 * sizeof(*dp) + 3)) / sizeof(*dp);
			TCHECK2(dp[0], 0);
			return (dp);
		}
	}
trunc:
	return (NULL);
}

/*
 * Print out an NFS file handle and return a pointer to following word.
 * If packet was truncated, return 0.
 */
static const u_int32_t *
parsefh(register const u_int32_t *dp, int v3)
{
	int len;

	if (v3) {
		if (dp + 1 > (u_int32_t *)snapend)
			return (0);
		len = (int)ntohl(*dp) / 4;
		dp++;
	} else
		len = NFSX_V2FH / 4;

	if (dp + len <= (u_int32_t *)snapend) {
		nfs_printfh(dp, len);
		return (dp + len);
	}
	return (NULL);
}

/*
 * Print out a file name and return pointer to 32-bit word past it.
 * If packet was truncated, return 0.
 */
static const u_int32_t *
parsefn(register const u_int32_t *dp)
{
	register u_int32_t len;
	register const u_char *cp;

	/* Bail if we don't have the string length */
	if ((u_char *)dp > snapend - sizeof(*dp))
		return (NULL);

	/* Fetch string length; convert to host order */
	len = *dp++;
	NTOHL(len);

	cp = (u_char *)dp;
	/* Update 32-bit pointer (NFS filenames padded to 32-bit boundaries) */
	dp += ((len + 3) & ~3) / sizeof(*dp);
	if ((u_char *)dp > snapend)
		return (NULL);
	/* XXX seems like we should be checking the length */
	putchar('"');
	(void) fn_printn(cp, len, NULL);
	putchar('"');

	return (dp);
}

/*
 * Print out file handle and file name.
 * Return pointer to 32-bit word past file name.
 * If packet was truncated (or there was some other error), return 0.
 */
static const u_int32_t *
parsefhn(register const u_int32_t *dp, int v3)
{
	dp = parsefh(dp, v3);
	if (dp == NULL)
		return (NULL);
	putchar(' ');
	return (parsefn(dp));
}

void
nfsreq_print(register const u_char *bp, u_int length,
    register const u_char *bp2)
{
	register const struct rpc_msg *rp;
	register const struct ip *ip;
	register const u_int32_t *dp;
	nfstype type;
	int v3;
	u_int32_t proc;
	struct nfsv3_sattr sa3;

	nfserr = 0;		/* assume no error */
	rp = (const struct rpc_msg *)bp;
	ip = (const struct ip *)bp2;
	if (!nflag)
		(void)printf("%s.%u > %s.nfs: %d",
			     ipaddr_string(&ip->ip_src),
			     (u_int32_t)ntohl(rp->rm_xid),
			     ipaddr_string(&ip->ip_dst),
			     length);
	else
		(void)printf("%s.%u > %s.%u: %d",
			     ipaddr_string(&ip->ip_src),
			     (u_int32_t)ntohl(rp->rm_xid),
			     ipaddr_string(&ip->ip_dst),
			     NFS_PORT,
			     length);

	xid_map_enter(rp, ip);	/* record proc number for later on */

	v3 = (ntohl(rp->rm_call.cb_vers) == NFS_VER3);
	proc = ntohl(rp->rm_call.cb_proc);

	if (!v3 && proc < NFS_NPROCS)
		proc =  nfsv3_procid[proc];

	switch (proc) {
	case NFSPROC_NOOP:
		printf(" nop");
		return;
	case NFSPROC_NULL:
		printf(" null");
		return;

	case NFSPROC_GETATTR:
		printf(" getattr");
		if ((dp = parsereq(rp, length)) != NULL &&
		    parsefh(dp, v3) != NULL)
			return;
		break;

	case NFSPROC_SETATTR:
		printf(" setattr");
		if ((dp = parsereq(rp, length)) != NULL &&
		    parsefh(dp, v3) != NULL)
			return;
		break;

	case NFSPROC_LOOKUP:
		printf(" lookup");
		if ((dp = parsereq(rp, length)) != NULL &&
		    parsefhn(dp, v3) != NULL)
			return;
		break;

	case NFSPROC_ACCESS:
		printf(" access");
		if ((dp = parsereq(rp, length)) != NULL &&
		    (dp = parsefh(dp, v3)) != NULL) {
			TCHECK2(dp[0], 4);
			printf(" %04x", ntohl(dp[0]));
			return;
		}
		break;

	case NFSPROC_READLINK:
		printf(" readlink");
		if ((dp = parsereq(rp, length)) != NULL &&
		    parsefh(dp, v3) != NULL)
			return;
		break;

	case NFSPROC_READ:
		printf(" read");
		if ((dp = parsereq(rp, length)) != NULL &&
		    (dp = parsefh(dp, v3)) != NULL) {
			if (v3) {
				TCHECK2(dp[0], 3 * sizeof(*dp));
				printf(" %u bytes @ ",
				       (u_int32_t) ntohl(dp[2]));
				print_int64(dp, UNSIGNED);
			} else {
				TCHECK2(dp[0], 2 * sizeof(*dp));
				printf(" %u bytes @ %u",
				       (u_int32_t) ntohl(dp[1]),
				       (u_int32_t) ntohl(dp[0]));
			}
			return;
		}
		break;

	case NFSPROC_WRITE:
		printf(" write");
		if ((dp = parsereq(rp, length)) != NULL &&
		    (dp = parsefh(dp, v3)) != NULL) {
			if (v3) {
				TCHECK2(dp[0], 3 * sizeof(*dp));
				printf(" %u bytes @ ",
				    (u_int32_t) ntohl(dp[4]));
				print_int64(dp, UNSIGNED);
				if (vflag) {
					dp += 3;
					TCHECK2(dp[0], sizeof(*dp));
					printf(" <%s>",
					       nfsv3_writemodes[ntohl(*dp)]);
				}
			} else {
				TCHECK2(dp[0], 4 * sizeof(*dp));
				printf(" %u (%u) bytes @ %u (%u)",
				       (u_int32_t) ntohl(dp[3]),
				       (u_int32_t) ntohl(dp[2]),
				       (u_int32_t) ntohl(dp[1]),
				       (u_int32_t) ntohl(dp[0]));
			}
			return;
		}
		break;

	case NFSPROC_CREATE:
		printf(" create");
		if ((dp = parsereq(rp, length)) != NULL &&
		    parsefhn(dp, v3) != NULL)
			return;
		break;

	case NFSPROC_MKDIR:
		printf(" mkdir");
		if ((dp = parsereq(rp, length)) != 0 && parsefhn(dp, v3) != 0)
			return;
		break;

	case NFSPROC_SYMLINK:
		printf(" symlink");
		if ((dp = parsereq(rp, length)) != 0 &&
		    (dp = parsefhn(dp, v3)) != 0) {
			fputs(" -> ", stdout);
			if (v3 && (dp = parse_sattr3(dp, &sa3)) == 0)
				break;
			if (parsefn(dp) == 0)
				break;
			if (v3 && vflag)
				print_sattr3(&sa3, vflag);
			return;
		}
		break;

	case NFSPROC_MKNOD:
		printf(" mknod");
		if ((dp = parsereq(rp, length)) != 0 &&
		    (dp = parsefhn(dp, v3)) != 0) {
			if (dp + 1 > (u_int32_t *)snapend)
				break;
			type = (nfstype)ntohl(*dp++);
			if ((dp = parse_sattr3(dp, &sa3)) == 0)
				break;
			printf(" %s", tok2str(type2str, "unk-ft %d", type));
			if (vflag && (type == NFCHR || type == NFBLK)) {
				if (dp + 2 > (u_int32_t *)snapend)
					break;
				printf(" %u/%u", ntohl(dp[0]), ntohl(dp[1]));
				dp += 2;
			}
			if (vflag)
				print_sattr3(&sa3, vflag);
			return;
		}
		break;

	case NFSPROC_REMOVE:
		printf(" remove");
		if ((dp = parsereq(rp, length)) != NULL &&
		    parsefhn(dp, v3) != NULL)
			return;
		break;

	case NFSPROC_RMDIR:
		printf(" rmdir");
		if ((dp = parsereq(rp, length)) != NULL &&
		    parsefhn(dp, v3) != NULL)
			return;
		break;

	case NFSPROC_RENAME:
		printf(" rename");
		if ((dp = parsereq(rp, length)) != NULL &&
		    (dp = parsefhn(dp, v3)) != NULL) {
			fputs(" ->", stdout);
			if (parsefhn(dp, v3) != NULL)
				return;
		}
		break;

	case NFSPROC_LINK:
		printf(" link");
		if ((dp = parsereq(rp, length)) != NULL &&
		    (dp = parsefh(dp, v3)) != NULL) {
			fputs(" ->", stdout);
			if (parsefhn(dp, v3) != NULL)
				return;
		}
		break;

	case NFSPROC_READDIR:
		printf(" readdir");
		if ((dp = parsereq(rp, length)) != NULL &&
		    (dp = parsefh(dp, v3)) != NULL) {
			if (v3) {
				TCHECK2(dp[0], 20);
				/*
				 * We shouldn't really try to interpret the
				 * offset cookie here.
				 */
				printf(" %u bytes @ ",
				    (u_int32_t) ntohl(dp[4]));
				print_int64(dp, SIGNED);
				if (vflag)
					printf(" verf %08x%08x", dp[2],
					       dp[3]);
			} else {
				TCHECK2(dp[0], 2 * sizeof(*dp));
				/*
				 * Print the offset as signed, since -1 is
				 * common, but offsets > 2^31 aren't.
				 */
				printf(" %u bytes @ %d",
				       (u_int32_t)ntohl(dp[1]),
				       (u_int32_t)ntohl(dp[0]));
			}
			return;
		}
		break;

	case NFSPROC_READDIRPLUS:
		printf(" readdirplus");
		if ((dp = parsereq(rp, length)) != NULL &&
		    (dp = parsefh(dp, v3)) != NULL) {
			TCHECK2(dp[0], 20);
			/*
			 * We don't try to interpret the offset
			 * cookie here.
			 */
			printf(" %u bytes @ ", (u_int32_t) ntohl(dp[4]));
			print_int64(dp, SIGNED);
			if (vflag)
				printf(" max %u verf %08x%08x",
				       (u_int32_t) ntohl(dp[5]), dp[2], dp[3]);
			return;
		}
		break;

	case NFSPROC_FSSTAT:
		printf(" fsstat");
		if ((dp = parsereq(rp, length)) != NULL &&
		    parsefh(dp, v3) != NULL)
			return;
		break;

	case NFSPROC_FSINFO:
		printf(" fsinfo");
		break;

	case NFSPROC_PATHCONF:
		printf(" pathconf");
		break;

	case NFSPROC_COMMIT:
		printf(" commit");
		if ((dp = parsereq(rp, length)) != NULL &&
		    (dp = parsefh(dp, v3)) != NULL) {
			printf(" %u bytes @ ", (u_int32_t) ntohl(dp[2]));
			print_int64(dp, UNSIGNED);
			return;
		}
		break;

	default:
		printf(" proc-%u", (u_int32_t)ntohl(rp->rm_call.cb_proc));
		return;
	}
trunc:
	if (!nfserr)
		fputs(" [|nfs]", stdout);
}

/*
 * Print out an NFS file handle.
 * We assume packet was not truncated before the end of the
 * file handle pointed to by dp.
 *
 * Note: new version (using portable file-handle parser) doesn't produce
 * generation number.  It probably could be made to do that, with some
 * additional hacking on the parser code.
 */
static void
nfs_printfh(register const u_int32_t *dp, const u_int len)
{
	my_fsid fsid;
	ino_t ino;
	char *sfsname = NULL;

	Parse_fh((caddr_t*)dp, len, &fsid, &ino, NULL, &sfsname, 0);

	if (sfsname) {
	    /* file system ID is ASCII, not numeric, for this server OS */
	    static char temp[NFSX_V3FHMAX+1];

	    /* Make sure string is null-terminated */
	    strncpy(temp, sfsname, NFSX_V3FHMAX);
	    /* Remove trailing spaces */
	    sfsname = strchr(temp, ' ');
	    if (sfsname)
		*sfsname = 0;

	    (void)printf(" fh %s/%ld", temp, (long) ino);
	}
	else {
	    (void)printf(" fh %d,%d/%ld",
			fsid.Fsid_dev.Major, fsid.Fsid_dev.Minor,
			(long) ino);
	}
}

/*
 * Maintain a small cache of recent client.XID.server/proc pairs, to allow
 * us to match up replies with requests and thus to know how to parse
 * the reply.
 */

struct xid_map_entry {
	u_int32_t		xid;	/* transaction ID (net order) */
	struct in_addr	client;		/* client IP address (net order) */
	struct in_addr	server;		/* server IP address (net order) */
	u_int32_t		proc;	/* call proc number (host order) */
	u_int32_t		vers;	/* program version (host order) */
};

/*
 * Map entries are kept in an array that we manage as a ring;
 * new entries are always added at the tail of the ring.  Initially,
 * all the entries are zero and hence don't match anything.
 */

#define	XIDMAPSIZE	64

struct xid_map_entry xid_map[XIDMAPSIZE];

int	xid_map_next = 0;
int	xid_map_hint = 0;

static void
xid_map_enter(const struct rpc_msg *rp, const struct ip *ip)
{
	struct xid_map_entry *xmep;

	xmep = &xid_map[xid_map_next];

	if (++xid_map_next >= XIDMAPSIZE)
		xid_map_next = 0;

	xmep->xid = rp->rm_xid;
	xmep->client = ip->ip_src;
	xmep->server = ip->ip_dst;
	xmep->proc = ntohl(rp->rm_call.cb_proc);
	xmep->vers = ntohl(rp->rm_call.cb_vers);
}

/* Returns NFSPROC_xxx or -1 on failure */
static int
xid_map_find(const struct rpc_msg *rp, const struct ip *ip, u_int32_t *proc,
	     u_int32_t *vers)
{
	int i;
	struct xid_map_entry *xmep;
	u_int32_t xid = rp->rm_xid;
	u_int32_t clip = ip->ip_dst.s_addr;
	u_int32_t sip = ip->ip_src.s_addr;

	/* Start searching from where we last left off */
	i = xid_map_hint;
	do {
		xmep = &xid_map[i];
		if (xmep->xid == xid && xmep->client.s_addr == clip &&
		    xmep->server.s_addr == sip) {
			/* match */
			xid_map_hint = i;
			*proc = xmep->proc;
			*vers = xmep->vers;
			return 1;
		}
		if (++i >= XIDMAPSIZE)
			i = 0;
	} while (i != xid_map_hint);

	/* search failed */
	return (0);
}

/*
 * Routines for parsing reply packets
 */

/*
 * Return a pointer to the beginning of the actual results.
 * If the packet was truncated, return 0.
 */
static const u_int32_t *
parserep(register const struct rpc_msg *rp, register u_int length)
{
	register const u_int32_t *dp;
	u_int len;
	enum accept_stat astat;

	/*
	 * Portability note:
	 * Here we find the address of the ar_verf credentials.
	 * Originally, this calculation was
	 *	dp = (u_int32_t *)&rp->rm_reply.rp_acpt.ar_verf
	 * On the wire, the rp_acpt field starts immediately after
	 * the (32 bit) rp_stat field.  However, rp_acpt (which is a
	 * "struct accepted_reply") contains a "struct opaque_auth",
	 * whose internal representation contains a pointer, so on a
	 * 64-bit machine the compiler inserts 32 bits of padding
	 * before rp->rm_reply.rp_acpt.ar_verf.  So, we cannot use
	 * the internal representation to parse the on-the-wire
	 * representation.  Instead, we skip past the rp_stat field,
	 * which is an "enum" and so occupies one 32-bit word.
	 */
	dp = ((const u_int32_t *)&rp->rm_reply) + 1;
	TCHECK2(dp[0], 1);
	len = ntohl(dp[1]);
	if (len >= length)
		return (NULL);
	/*
	 * skip past the ar_verf credentials.
	 */
	dp += (len + (2*sizeof(u_int32_t) + 3)) / sizeof(u_int32_t);
	TCHECK2(dp[0], 0);

	/*
	 * now we can check the ar_stat field
	 */
	astat = ntohl(*(enum accept_stat *)dp);
	switch (astat) {

	case SUCCESS:
		break;

	case PROG_UNAVAIL:
		printf(" PROG_UNAVAIL");
		nfserr = 1;		/* suppress trunc string */
		return (NULL);

	case PROG_MISMATCH:
		printf(" PROG_MISMATCH");
		nfserr = 1;		/* suppress trunc string */
		return (NULL);

	case PROC_UNAVAIL:
		printf(" PROC_UNAVAIL");
		nfserr = 1;		/* suppress trunc string */
		return (NULL);

	case GARBAGE_ARGS:
		printf(" GARBAGE_ARGS");
		nfserr = 1;		/* suppress trunc string */
		return (NULL);

	case SYSTEM_ERR:
		printf(" SYSTEM_ERR");
		nfserr = 1;		/* suppress trunc string */
		return (NULL);

	default:
		printf(" ar_stat %d", astat);
		nfserr = 1;		/* suppress trunc string */
		return (NULL);
	}
	/* successful return */
	if ((sizeof(astat) + ((u_char *)dp)) < snapend)
		return ((u_int32_t *) (sizeof(astat) + ((char *)dp)));
trunc:
	return (0);
}

#define T2CHECK(p, l) if ((u_char *)(p) > ((u_char *)snapend) - l) return(0)

/*
 * Not all systems have strerror().
 */
static char *
strerr(int errno)
{
	return (strerror(errno));
}

static const u_int32_t *
parsestatus(const u_int32_t *dp, int *er)
{
	int errno;
	T2CHECK(dp, 4);

	errno = ntohl(dp[0]);
	if (er)
		*er = errno;
	if (errno != 0 && !qflag) {
		char *errmsg;

		errmsg = strerr(errno);
		if (errmsg)
			printf(" ERROR: '%s'", errmsg);
		else
			printf(" ERROR: %d", errno);
	}
	return (dp + 1);
}

static const u_int32_t *
parsefattr(const u_int32_t *dp, int verbose, int v3)
{
	const struct nfs_fattr *fap;

	T2CHECK(dp,  5 * sizeof(*dp));

	fap = (const struct nfs_fattr *)dp;
	if (verbose) {
		printf(" %s %o ids %d/%d",
		    tok2str(type2str, "unk-ft %d ",
		    (u_int32_t) ntohl(fap->fa_type)),
		    (u_int32_t) ntohl(fap->fa_mode),
		    (u_int32_t) ntohl(fap->fa_uid),
		    (u_int32_t) ntohl(fap->fa_gid));
		if (v3) {
			T2CHECK(dp,  7 * sizeof(*dp));
			printf(" sz ");
			print_int64((u_int32_t *)&fap->fa3_size, UNSIGNED);
			putchar(' ');
		}
		else {
			T2CHECK(dp,  6 * sizeof(*dp));
			printf(" sz %d ", (u_int32_t) ntohl(fap->fa2_size));
		}
	}
	/* print lots more stuff */
	if (verbose > 1) {
		if (v3) {
			T2CHECK(dp, 64);
			printf("nlink %d rdev %d/%d ",
			       (u_int32_t) ntohl(fap->fa_nlink),
			       (u_int32_t) ntohl(fap->fa3_rdev.specdata1),
			       (u_int32_t) ntohl(fap->fa3_rdev.specdata2));
			printf("fsid ");
			print_int64((u_int32_t *)&fap->fa2_fsid, HEX);
			printf(" nodeid ");
			print_int64((u_int32_t *)&fap->fa2_fileid, HEX);
			printf(" a/m/ctime %u.%06u ",
			       (u_int32_t) ntohl(fap->fa3_atime.nfsv3_sec),
			       (u_int32_t) ntohl(fap->fa3_atime.nfsv3_nsec));
			printf("%u.%06u ",
			       (u_int32_t) ntohl(fap->fa3_mtime.nfsv3_sec),
			       (u_int32_t) ntohl(fap->fa3_mtime.nfsv3_nsec));
			printf("%u.%06u ",
			       (u_int32_t) ntohl(fap->fa3_ctime.nfsv3_sec),
			       (u_int32_t) ntohl(fap->fa3_ctime.nfsv3_nsec));
		} else {
			T2CHECK(dp, 48);
			printf("nlink %d rdev %x fsid %x nodeid %x a/m/ctime ",
			       (u_int32_t) ntohl(fap->fa_nlink),
			       (u_int32_t) ntohl(fap->fa2_rdev),
			       (u_int32_t) ntohl(fap->fa2_fsid),
			       (u_int32_t) ntohl(fap->fa2_fileid));
			printf("%u.%06u ",
			       (u_int32_t) ntohl(fap->fa2_atime.nfsv2_sec),
			       (u_int32_t) ntohl(fap->fa2_atime.nfsv2_usec));
			printf("%u.%06u ",
			       (u_int32_t) ntohl(fap->fa2_mtime.nfsv2_sec),
			       (u_int32_t) ntohl(fap->fa2_mtime.nfsv2_usec));
			printf("%u.%06u ",
			       (u_int32_t) ntohl(fap->fa2_ctime.nfsv2_sec),
			       (u_int32_t) ntohl(fap->fa2_ctime.nfsv2_usec));
		}
	}
	return ((const u_int32_t *)((unsigned char *)dp +
		(v3 ? NFSX_V3FATTR : NFSX_V2FATTR)));
}

static int
parseattrstat(const u_int32_t *dp, int verbose, int v3)
{
	int er;

	dp = parsestatus(dp, &er);
	if (dp == NULL || er)
		return (0);

	return (parsefattr(dp, verbose, v3) != NULL);
}

static int
parsediropres(const u_int32_t *dp)
{
	int er;

	if (!(dp = parsestatus(dp, &er)) || er)
		return (0);

	dp = parsefh(dp, 0);
	if (dp == NULL)
		return (0);

	return (parsefattr(dp, vflag, 0) != NULL);
}

static int
parselinkres(const u_int32_t *dp, int v3)
{
	int er;

	dp = parsestatus(dp, &er);
	if (dp == NULL || er)
		return(0);
	if (v3 && !(dp = parse_post_op_attr(dp, vflag)))
		return (0);
	putchar(' ');
	return (parsefn(dp) != NULL);
}

static int
parsestatfs(const u_int32_t *dp, int v3)
{
	const struct nfs_statfs *sfsp;
	int er;

	dp = parsestatus(dp, &er);
	if (dp == NULL || (!v3 && er))
		return(0);

	if (qflag)
		return(1);

	if (v3) {
		if (vflag)
			printf(" POST:");
		if (!(dp = parse_post_op_attr(dp, vflag)))
			return (0);
	}

	T2CHECK(dp, (v3 ? NFSX_V3STATFS : NFSX_V2STATFS));

	sfsp = (const struct nfs_statfs *)dp;

	if (v3) {
		printf(" tbytes ");
		print_int64((u_int32_t *)&sfsp->sf_tbytes, UNSIGNED);
		printf(" fbytes ");
		print_int64((u_int32_t *)&sfsp->sf_fbytes, UNSIGNED);
		printf(" abytes ");
		print_int64((u_int32_t *)&sfsp->sf_abytes, UNSIGNED);
		if (vflag) {
			printf(" tfiles ");
			print_int64((u_int32_t *)&sfsp->sf_tfiles, UNSIGNED);
			printf(" ffiles ");
			print_int64((u_int32_t *)&sfsp->sf_ffiles, UNSIGNED);
			printf(" afiles ");
			print_int64((u_int32_t *)&sfsp->sf_afiles, UNSIGNED);
			printf(" invar %u",
			       (u_int32_t) ntohl(sfsp->sf_invarsec));
		}
	} else {
		printf(" tsize %d bsize %d blocks %d bfree %d bavail %d",
		       (u_int32_t) ntohl(sfsp->sf_tsize),
		       (u_int32_t) ntohl(sfsp->sf_bsize),
		       (u_int32_t) ntohl(sfsp->sf_blocks),
		       (u_int32_t) ntohl(sfsp->sf_bfree),
		       (u_int32_t) ntohl(sfsp->sf_bavail));
	}

	return (1);
}

static int
parserddires(const u_int32_t *dp)
{
	int er;

	dp = parsestatus(dp, &er);
	if (dp == 0 || er)
		return (0);
	if (qflag)
		return (1);

	T2CHECK(dp, 12);
	printf(" offset %x size %d ", ntohl(dp[0]), ntohl(dp[1]));
	if (dp[2] != 0)
		printf("eof");

	return (1);
}

static const u_int32_t *
parse_wcc_attr(const u_int32_t *dp)
{
	printf(" sz ");
	print_int64(dp, UNSIGNED);
	printf(" mtime %u.%06u ctime %u.%06u", ntohl(dp[2]), ntohl(dp[3]),
	       ntohl(dp[4]), ntohl(dp[5]));
	return (dp + 6);
}

/*
 * Pre operation attributes. Print only if vflag > 1.
 */
static const u_int32_t *
parse_pre_op_attr(const u_int32_t *dp, int verbose)
{
	T2CHECK(dp, 4);
	if (!ntohl(dp[0]))
		return (dp + 1);
	dp++;
	T2CHECK(dp, 24);
	if (verbose > 1) {
		return parse_wcc_attr(dp);
	} else {
		/* If not verbose enough, just skip over wcc_attr */
		return (dp + 6);
	}
}

/*
 * Post operation attributes are printed if vflag >= 1
 */
static const u_int32_t *
parse_post_op_attr(const u_int32_t *dp, int verbose)
{
	T2CHECK(dp, 4);
	if (!ntohl(dp[0]))
		return (dp + 1);
	dp++;
	if (verbose) {
		return parsefattr(dp, verbose, 1);
	} else
		return (dp + (NFSX_V3FATTR / sizeof (u_int32_t)));
}

static const u_int32_t *
parse_wcc_data(const u_int32_t *dp, int verbose)
{
	if (verbose > 1)
		printf(" PRE:");
	if (!(dp = parse_pre_op_attr(dp, verbose)))
		return (0);

	if (verbose)
		printf(" POST:");
	return parse_post_op_attr(dp, verbose);
}

static const u_int32_t *
parsecreateopres(const u_int32_t *dp, int verbose)
{
	int er;

	if (!(dp = parsestatus(dp, &er)))
		return (0);
	if (er)
		dp = parse_wcc_data(dp, verbose);
	else {
		T2CHECK(dp, 4);
		if (!ntohl(dp[0]))
			return (dp + 1);
		dp++;
		if (!(dp = parsefh(dp, 1)))
			return (0);
		if (verbose) {
			if (!(dp = parse_post_op_attr(dp, verbose)))
				return (0);
			if (vflag > 1) {
				printf("dir attr:");
				dp = parse_wcc_data(dp, verbose);
			}
		}
	}
	return (dp);
}

static int
parsewccres(const u_int32_t *dp, int verbose)
{
	int er;

	if (!(dp = parsestatus(dp, &er)))
		return (0);
	return parse_wcc_data(dp, verbose) != 0;
}

static const u_int32_t *
parsev3rddirres(const u_int32_t *dp, int verbose)
{
	int er;

	if (!(dp = parsestatus(dp, &er)))
		return (0);
	if (vflag)
		printf(" POST:");
	if (!(dp = parse_post_op_attr(dp, verbose)))
		return (0);
	if (er)
		return dp;
	if (vflag) {
		T2CHECK(dp, 8);
		printf(" verf %08x%08x", dp[0], dp[1]);
		dp += 2;
	}
	return dp;
}

static int
parsefsinfo(const u_int32_t *dp)
{
	struct nfsv3_fsinfo *sfp;
	int er;

	if (!(dp = parsestatus(dp, &er)))
		return (0);
	if (vflag)
		printf(" POST:");
	if (!(dp = parse_post_op_attr(dp, vflag)))
		return (0);
	if (er)
		return (1);

	T2CHECK(dp, sizeof (struct nfsv3_fsinfo));

	sfp = (struct nfsv3_fsinfo *)dp;
	printf(" rtmax %u rtpref %u wtmax %u wtpref %u dtpref %u",
	       (u_int32_t) ntohl(sfp->fs_rtmax),
	       (u_int32_t) ntohl(sfp->fs_rtpref),
	       (u_int32_t) ntohl(sfp->fs_wtmax),
	       (u_int32_t) ntohl(sfp->fs_wtpref),
	       (u_int32_t) ntohl(sfp->fs_dtpref));
	if (vflag) {
		printf(" rtmult %u wtmult %u maxfsz ",
		       (u_int32_t) ntohl(sfp->fs_rtmult),
		       (u_int32_t) ntohl(sfp->fs_wtmult));
		print_int64((u_int32_t *)&sfp->fs_maxfilesize, UNSIGNED);
		printf(" delta %u.%06u ",
		       (u_int32_t) ntohl(sfp->fs_timedelta.nfsv3_sec),
		       (u_int32_t) ntohl(sfp->fs_timedelta.nfsv3_nsec));
	}
	return (1);
}

static int
parsepathconf(const u_int32_t *dp)
{
	int er;
	struct nfsv3_pathconf *spp;

	if (!(dp = parsestatus(dp, &er)))
		return (0);
	if (vflag)
		printf(" POST:");
	if (!(dp = parse_post_op_attr(dp, vflag)))
		return (0);
	if (er)
		return (1);

	T2CHECK(dp, sizeof (struct nfsv3_pathconf));

	spp = (struct nfsv3_pathconf *)dp;

	printf(" linkmax %u namemax %u %s %s %s %s",
	       (u_int32_t) ntohl(spp->pc_linkmax),
	       (u_int32_t) ntohl(spp->pc_namemax),
	       ntohl(spp->pc_notrunc) ? "notrunc" : "",
	       ntohl(spp->pc_chownrestricted) ? "chownres" : "",
	       ntohl(spp->pc_caseinsensitive) ? "igncase" : "",
	       ntohl(spp->pc_casepreserving) ? "keepcase" : "");
	return (0);
}
				
static void
interp_reply(const struct rpc_msg *rp, u_int32_t proc, u_int32_t vers, int length)
{
	register const u_int32_t *dp;
	register int v3;
	int er;

	v3 = (vers == NFS_VER3);

	if (!v3 && proc < NFS_NPROCS)
		proc = nfsv3_procid[proc];

	switch (proc) {

	case NFSPROC_NOOP:
		printf(" nop");
		return;

	case NFSPROC_NULL:
		printf(" null");
		return;

	case NFSPROC_GETATTR:
		printf(" getattr");
		dp = parserep(rp, length);
		if (dp != NULL && parseattrstat(dp, !qflag, v3) != 0)
			return;
		break;

	case NFSPROC_SETATTR:
		printf(" setattr");
		if (!(dp = parserep(rp, length)))
			return;
		if (v3) {
			if (parsewccres(dp, vflag))
				return;
		} else {
			if (parseattrstat(dp, !qflag, 0) != 0)
				return;
		}
		break;

	case NFSPROC_LOOKUP:
		printf(" lookup");
		if (!(dp = parserep(rp, length)))
			break;
		if (v3) {
			if (!(dp = parsestatus(dp, &er)))
				break;
			if (er) {
				if (vflag > 1) {
					printf(" post dattr:");
					dp = parse_post_op_attr(dp, vflag);
				}
			} else {
				if (!(dp = parsefh(dp, v3)))
					break;
				if ((dp = parse_post_op_attr(dp, vflag)) &&
				    vflag > 1) {
					printf(" post dattr:");
					dp = parse_post_op_attr(dp, vflag);
				}
			}
			if (dp)
				return;
		} else {
			if (parsediropres(dp) != 0)
				return;
		}
		break;

	case NFSPROC_ACCESS:
		printf(" access");
		dp = parserep(rp, length);
		if (!(dp = parsestatus(dp, &er)))
			break;
		if (vflag)
			printf(" attr:");
		if (!(dp = parse_post_op_attr(dp, vflag)))
			break;
		if (!er)
			printf(" c %04x", ntohl(dp[0]));
		return;

	case NFSPROC_READLINK:
		printf(" readlink");
		dp = parserep(rp, length);
		if (dp != NULL && parselinkres(dp, v3) != 0)
			return;
		break;

	case NFSPROC_READ:
		printf(" read");
		if (!(dp = parserep(rp, length)))
			break;
		if (v3) {
			if (!(dp = parsestatus(dp, &er)))
				break;
			if (!(dp = parse_post_op_attr(dp, vflag)))
				break;
			if (er)
				return;
			if (vflag) {
				TCHECK2(dp[0], 8);
				printf("%u bytes", (u_int32_t) ntohl(dp[0]));
				if (ntohl(dp[1]))
					printf(" EOF");
			}
			return;
		} else {
			if (parseattrstat(dp, vflag, 0) != 0)
				return;
		}
		break;

	case NFSPROC_WRITE:
		printf(" write");
		if (!(dp = parserep(rp, length)))
			break;
		if (v3) {
			if (!(dp = parsestatus(dp, &er)))
				break;
			if (!(dp = parse_wcc_data(dp, vflag)))
				break;
			if (er)
				return;
			if (vflag) {
				TCHECK2(dp[0], 4);
				printf("%u bytes", (u_int32_t) ntohl(dp[0]));
				if (vflag > 1) {
					TCHECK2(dp[0], 4);
					printf(" <%s>",
					       nfsv3_writemodes[ntohl(dp[1])]);
				}
				return;
			}
		} else {
			if (parseattrstat(dp, vflag, v3) != 0)
				return;
		}
		break;

	case NFSPROC_CREATE:
		printf(" create");
		if (!(dp = parserep(rp, length)))
			break;
		if (v3) {
			if (parsecreateopres(dp, vflag) != 0)
				return;
		} else {
			if (parsediropres(dp) != 0)
				return;
		}
		break;

	case NFSPROC_MKDIR:
		printf(" mkdir");
		if (!(dp = parserep(rp, length)))
			break;
		if (v3) {
			if (parsecreateopres(dp, vflag) != 0)
				return;
		} else {
			if (parsediropres(dp) != 0)
				return;
		}
		break;

	case NFSPROC_SYMLINK:
		printf(" symlink");
		if (!(dp = parserep(rp, length)))
			break;
		if (v3) {
			if (parsecreateopres(dp, vflag) != 0)
				return;
		} else {
			if (parsestatus(dp, &er) != 0)
				return;
		}
		break;

	case NFSPROC_MKNOD:
		printf(" mknod");
		if (!(dp = parserep(rp, length)))
			break;
		if (parsecreateopres(dp, vflag) != 0)
			return;
		break;

	case NFSPROC_REMOVE:
		printf(" remove");
		if (!(dp = parserep(rp, length)))
			break;
		if (v3) {
			if (parsewccres(dp, vflag))
				return;
		} else {
			if (parsestatus(dp, &er) != 0)
				return;
		}
		break;

	case NFSPROC_RMDIR:
		printf(" rmdir");
		if (!(dp = parserep(rp, length)))
			break;
		if (v3) {
			if (parsewccres(dp, vflag))
				return;
		} else {
			if (parsestatus(dp, &er) != 0)
				return;
		}
		break;

	case NFSPROC_RENAME:
		printf(" rename");
		if (!(dp = parserep(rp, length)))
			break;
		if (v3) {
			if (!(dp = parsestatus(dp, &er)))
				break;
			if (vflag) {
				printf(" from:");
				if (!(dp = parse_wcc_data(dp, vflag)))
					break;
				printf(" to:");
				if (!(dp = parse_wcc_data(dp, vflag)))
					break;
			}
			return;
		} else {
			if (parsestatus(dp, &er) != 0)
				return;
		}
		break;

	case NFSPROC_LINK:
		printf(" link");
		if (!(dp = parserep(rp, length)))
			break;
		if (v3) {
			if (!(dp = parsestatus(dp, &er)))
				break;
			if (vflag) {
				printf(" file POST:");
				if (!(dp = parse_post_op_attr(dp, vflag)))
					break;
				printf(" dir:");
				if (!(dp = parse_wcc_data(dp, vflag)))
					break;
				return;
			}
		} else {
			if (parsestatus(dp, &er) != 0)
				return;
		}
		break;

	case NFSPROC_READDIR:
		printf(" readdir");
		if (!(dp = parserep(rp, length)))
			break;
		if (v3) {
			if (parsev3rddirres(dp, vflag))
				return;
		} else {
			if (parserddires(dp) != 0)
				return;
		}
		break;

	case NFSPROC_READDIRPLUS:
		printf(" readdirplus");
		if (!(dp = parserep(rp, length)))
			break;
		if (parsev3rddirres(dp, vflag))
			return;
		break;

	case NFSPROC_FSSTAT:
		printf(" fsstat");
		dp = parserep(rp, length);
		if (dp != NULL && parsestatfs(dp, v3) != 0)
			return;
		break;

	case NFSPROC_FSINFO:
		printf(" fsinfo");
		dp = parserep(rp, length);
		if (dp != NULL && parsefsinfo(dp) != 0)
			return;
		break;

	case NFSPROC_PATHCONF:
		printf(" pathconf");
		dp = parserep(rp, length);
		if (dp != NULL && parsepathconf(dp) != 0)
			return;
		break;

	case NFSPROC_COMMIT:
		printf(" commit");
		dp = parserep(rp, length);
		if (dp != NULL && parsewccres(dp, vflag) != 0)
			return;
		break;

	default:
		printf(" proc-%u", proc);
		return;
	}
	if (!nfserr)
		fputs(" [|nfs]", stdout);
trunc:
}
