/*

   p0f - fingerprint entry
   -----------------------

   No servicable parts inside.

   Copyright (C) 2003-2006 by Michal Zalewski <lcamtuf@coredump.cx>

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
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.

*/

#ifndef _HAVE_FPENTRY_H
#define _HAVE_FPENTRY_H

#include "types.h"
#include "p0f-config.h"

#define MOD_NONE	0
#define MOD_CONST	1
#define MOD_MSS		2
#define MOD_MTU		3

#define QUIRK_PAST      0x00000001 /* P */
#define QUIRK_ZEROID	0x00000002 /* Z */
#define QUIRK_IPOPT	0x00000004 /* I */
#define QUIRK_URG	0x00000008 /* U */ 
#define QUIRK_X2	0x00000010 /* X */ 
#define QUIRK_ACK	0x00000020 /* A */ 
#define QUIRK_T2	0x00000040 /* T */
#define QUIRK_FLAGS	0x00000080 /* F */
#define QUIRK_DATA	0x00000100 /* D */
#define QUIRK_BROKEN	0x00000200 /* ! */
#define QUIRK_RSTACK	0x00000400 /* K */
#define QUIRK_SEQEQ	0x00000800 /* Q */
#define QUIRK_SEQ0      0x00001000 /* 0 */

struct fp_entry {
  _u8* os;		/* OS genre */
  _u8* desc;		/* OS description */
  _u8  no_detail;	/* Disable guesstimates */
  _u8  generic;		/* Generic hit */
  _u8  userland;	/* Userland stack */
  _u16 wsize;		/* window size */
  _u8  wsize_mod;	/* MOD_* for wsize */
  _u8  ttl,df;		/* TTL and don't fragment bit */
  _u8  zero_stamp;	/* timestamp option but zero value? */
  _u16 size;		/* packet size */
  _u8  optcnt;		/* option count */
  _u8  opt[MAXOPT];	/* TCPOPT_* */
  _u16 wsc,mss;		/* value for WSCALE and MSS options */
  _u8  wsc_mod,mss_mod;	/* modulo for WSCALE and MSS (NONE or CONST) */
  _u32 quirks;		/* packet quirks and bugs */
  _u32 line;		/* config file line */
  struct fp_entry* next;
};

#ifdef IGNORE_ZEROID
#  undef QUIRK_ZEROID
#  define QUIRK_ZEROID	0
#endif /* IGNORE_ZEROID */

#endif /* ! _HAVE_FPENTRY_H */
