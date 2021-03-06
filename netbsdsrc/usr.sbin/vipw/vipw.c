/*	$NetBSD: vipw.c,v 1.5 1997/10/17 14:31:13 lukem Exp $	*/

/*
 * Copyright (c) 1987, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#ifndef lint
__COPYRIGHT("@(#) Copyright (c) 1987, 1993, 1994\n\
	The Regents of the University of California.  All rights reserved.\n");
#endif /* not lint */

#ifndef lint
#if 0
static char sccsid[] = "@(#)vipw.c	8.3 (Berkeley) 4/2/94";
#else
__RCSID("$NetBSD: vipw.c,v 1.5 1997/10/17 14:31:13 lukem Exp $");
#endif
#endif /* not lint */

#include <sys/types.h>
#include <sys/stat.h>

#include <err.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <util.h>

void	copyfile __P((int, int));
int	main __P((int, char **));
void	usage __P((void));

int
main(argc, argv)
	int argc;
	char *argv[];
{
	int pfd, tfd;
	struct stat begin, end;
	int ch;

	while ((ch = getopt(argc, argv, "")) != -1) {
		switch (ch) {
		case '?':
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc != 0)
		usage();

	pw_init();
	tfd = pw_lock(0);
	if (tfd < 0)
		errx(1, "the passwd file is busy.");
	pfd = open(_PATH_MASTERPASSWD, O_RDONLY, 0);
	if (pfd < 0)
		pw_error(_PATH_MASTERPASSWD, 1, 1);
	copyfile(pfd, tfd);
	(void)close(tfd);

	for (;;) {
		if (stat(_PATH_MASTERPASSWD_LOCK, &begin))
			pw_error(_PATH_MASTERPASSWD_LOCK, 1, 1);
		pw_edit(0, NULL);
		if (stat(_PATH_MASTERPASSWD_LOCK, &end))
			pw_error(_PATH_MASTERPASSWD_LOCK, 1, 1);
		if (begin.st_mtime == end.st_mtime) {
			warnx("no changes made");
			pw_error((char *)NULL, 0, 0);
		}
		if (pw_mkdb() == 0)
			break;
		pw_prompt();
	}
	exit(0);
}

void
copyfile(from, to)
	int from, to;
{
	int nr, nw, off;
	char buf[8*1024];
	
	while ((nr = read(from, buf, sizeof(buf))) > 0)
		for (off = 0; off < nr; nr -= nw, off += nw)
			if ((nw = write(to, buf + off, nr)) < 0)
				pw_error(_PATH_MASTERPASSWD_LOCK, 1, 1);
	if (nr < 0)
		pw_error(_PATH_MASTERPASSWD, 1, 1);
}

void
usage()
{

	(void)fprintf(stderr, "usage: vipw\n");
	exit(1);
}
