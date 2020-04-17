/*
 * Command line options parser.
 *
 * Copyright (C) 2011, Broadcom Corporation
 * All Rights Reserved.
 * 
 * THIS SOFTWARE IS OFFERED "AS IS", AND BROADCOM GRANTS NO WARRANTIES OF ANY
 * KIND, EXPRESS OR IMPLIED, BY STATUTE, COMMUNICATION OR OTHERWISE. BROADCOM
 * SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A SPECIFIC PURPOSE OR NONINFRINGEMENT CONCERNING THIS SOFTWARE.
 * $Id: miniopt.h,v 1.3 2009-01-15 00:06:54 nvalji Exp $
 */


#ifndef INCLUDED_MHD_WLOPT_H_
#define INCLUDED_MHD_WLOPT_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MINIOPT_MAXKEY	128	/* Max options */

typedef struct miniopt {

	/* These are persistent after miniopt_init() */
	const char* name;		/* name for prompt in error strings */
	const char* flags;		/* option chars that take no args */
	host_bool_t longflags;	/* long options may be flags */
	host_bool_t opt_end;	/* at end of options (passed a "--") */

	/* These are per-call to miniopt() */

	int consumed;		/* number of argv entries cosumed in
				 * the most recent call to miniopt()
				 */
	host_bool_t positional;
	host_bool_t good_int;		/* 'val' member is the result of a sucessful
				 * strtol conversion of the option value
				 */
	char opt;
	char key[MINIOPT_MAXKEY];
	char* valstr;		/* positional param, or value for the option,
				 * or null if the option had
				 * no accompanying value
				 */
	uint32_t uval;		/* strtol translation of valstr */
	int  val;		/* strtol translation of valstr */
} miniopt_t;

void miniopt_init(miniopt_t *t, const char* name, const char* flags, host_bool_t longflags);
int miniopt(miniopt_t *t, char **argv);

#ifdef __cplusplus
	}
#endif

#endif  /* INCLUDED_MHD_WLOPT_H_  */
