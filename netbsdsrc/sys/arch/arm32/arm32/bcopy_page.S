/*	$NetBSD: bcopy_page.S,v 1.4 1997/10/14 09:54:31 mark Exp $	*/

/*
 * Copyright (c) 1995 Scott Stevens
 * All rights reserved.
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
 *	This product includes software developed by Scott Stevens.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * RiscBSD kernel project
 *
 * bcopy_page.S
 *
 * page optimised bcopy and bzero routines
 *
 * Created      : 08/04/95
 */

ip	.req	r12
sp	.req	r13
lr	.req	r14
pc	.req	r15

#include <machine/param.h>
#include <machine/asm.h>

/*
 * bcopy_page(src, dest)
 *
 * Optimised copy page routine.
 *
 * On entry:
 *   r0 - src address
 *   r1 - dest address
 *
 * Requires:
 *   number of bytes per page (NBPG) is a multiple of 512
 */

ENTRY(bcopy_page)
	stmfd	sp!, {r4-r10, lr}
	mov	r2, #(NBPG >> 9)

Lloopcopy:
	ldmia	r0!, {r3-r10}
	stmia	r1!, {r3-r10}
	ldmia	r0!, {r3-r10}
	stmia	r1!, {r3-r10}
	ldmia	r0!, {r3-r10}
	stmia	r1!, {r3-r10}
	ldmia	r0!, {r3-r10}
	stmia	r1!, {r3-r10}

	ldmia	r0!, {r3-r10}
	stmia	r1!, {r3-r10}
	ldmia	r0!, {r3-r10}
	stmia	r1!, {r3-r10}
	ldmia	r0!, {r3-r10}
	stmia	r1!, {r3-r10}
	ldmia	r0!, {r3-r10}
	stmia	r1!, {r3-r10}

	ldmia	r0!, {r3-r10}
	stmia	r1!, {r3-r10}
	ldmia	r0!, {r3-r10}
	stmia	r1!, {r3-r10}
	ldmia	r0!, {r3-r10}
	stmia	r1!, {r3-r10}
	ldmia	r0!, {r3-r10}
	stmia	r1!, {r3-r10}

	ldmia	r0!, {r3-r10}
	stmia	r1!, {r3-r10}
	ldmia	r0!, {r3-r10}
	stmia	r1!, {r3-r10}
	ldmia	r0!, {r3-r10}
	stmia	r1!, {r3-r10}
	ldmia	r0!, {r3-r10}
	stmia	r1!, {r3-r10}

	subs	r2, r2, #1
	bne	Lloopcopy

	ldmfd	sp!, {r4-r10, pc}

/*
 * bzero_page(dest)
 *
 * Optimised zero page routine.
 *
 * On entry:
 *   r0 - dest address
 *
 * Requires:
 *   number of bytes per page (NBPG) is a multiple of 512
 */

ENTRY(bzero_page)
	stmfd	sp!, {r4-r10, lr}
	mov	r2, #(NBPG >> 9)

	mov	r3, #0
	mov	r4, #0
	mov	r5, #0
	mov	r6, #0
	mov	r7, #0
	mov	r8, #0
	mov	r9, #0
	mov	r10, #0

Lloopzero:
	stmia	r0!, {r3-r10}
	stmia	r0!, {r3-r10}
	stmia	r0!, {r3-r10}
	stmia	r0!, {r3-r10}

	stmia	r0!, {r3-r10}
	stmia	r0!, {r3-r10}
	stmia	r0!, {r3-r10}
	stmia	r0!, {r3-r10}

	stmia	r0!, {r3-r10}
	stmia	r0!, {r3-r10}
	stmia	r0!, {r3-r10}
	stmia	r0!, {r3-r10}

	stmia	r0!, {r3-r10}
	stmia	r0!, {r3-r10}
	stmia	r0!, {r3-r10}
	stmia	r0!, {r3-r10}

	subs	r2, r2, #1
	bne	Lloopzero

	ldmfd	sp!, {r4-r10, pc}
