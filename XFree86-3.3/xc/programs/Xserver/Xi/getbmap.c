/* $XConsortium: getbmap.c,v 1.6 94/04/17 20:33:09 rws Exp $ */
/* $XFree86: xc/programs/Xserver/Xi/getbmap.c,v 3.0 1996/03/29 22:13:14 dawes Exp $ */

/************************************************************

Copyright (c) 1989  X Consortium

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from the X Consortium.

Copyright (c) 1989 by Hewlett-Packard Company, Palo Alto, California.

			All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the name of Hewlett-Packard not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.

HEWLETT-PACKARD DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
HEWLETT-PACKARD BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

********************************************************/

/***********************************************************************
 *
 * Extension function to return the version of the extension.
 *
 */

#define	 NEED_EVENTS
#define	 NEED_REPLIES
#include "X.h"				/* for inputstr.h    */
#include "Xproto.h"			/* Request macro     */
#include "inputstr.h"			/* DeviceIntPtr	     */
#include "XI.h"
#include "XIproto.h"
#include "extnsionst.h"
#include "extinit.h"			/* LookupDeviceIntRec */
#include "exglobals.h"

#include "getbmap.h"

/***********************************************************************
 *
 * This procedure gets the button mapping for the specified device.
 *
 */

int
SProcXGetDeviceButtonMapping(client)
    register ClientPtr client;
    {
    register char n;

    REQUEST(xGetDeviceButtonMappingReq);
    swaps(&stuff->length, n);
    return(ProcXGetDeviceButtonMapping(client));
    }

/***********************************************************************
 *
 * This procedure gets the button mapping for the specified device.
 *
 */

int
ProcXGetDeviceButtonMapping (client)
    register ClientPtr client;
    {
    DeviceIntPtr	dev;
    xGetDeviceButtonMappingReply	rep;
    ButtonClassPtr	b;

    REQUEST(xGetDeviceButtonMappingReq);
    REQUEST_SIZE_MATCH(xGetDeviceButtonMappingReq);

    rep.repType = X_Reply;
    rep.RepType = X_GetDeviceButtonMapping;
    rep.nElts = 0;
    rep.length = 0;
    rep.sequenceNumber = client->sequence;

    dev = LookupDeviceIntRec (stuff->deviceid);
    if (dev == NULL)
	{
	SendErrorToClient(client, IReqCode, X_GetDeviceButtonMapping, 0, 
		BadDevice);
	return Success;
	}

    b = dev->button;
    if (b == NULL)
	{
	SendErrorToClient(client, IReqCode, X_GetDeviceButtonMapping, 0, 
		BadMatch);
	return Success;
	}
    rep.nElts = b->numButtons;
    rep.length = (rep.nElts + (4-1))/4;
    WriteReplyToClient (client, sizeof (xGetDeviceButtonMappingReply), &rep);
    (void)WriteToClient(client, rep.nElts,
			(char *)&b->map[1]);
    return Success;
    }

/***********************************************************************
 *
 * This procedure writes the reply for the XGetDeviceButtonMapping function,
 * if the client and server have a different byte ordering.
 *
 */

void
SRepXGetDeviceButtonMapping (client, size, rep)
    ClientPtr	client;
    int		size;
    xGetDeviceButtonMappingReply	*rep;
    {
    register char n;

    swaps(&rep->sequenceNumber, n);
    swapl(&rep->length, n);
    WriteToClient(client, size, (char *)rep);
    }
