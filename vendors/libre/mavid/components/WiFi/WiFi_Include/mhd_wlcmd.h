#ifndef INCLUDED_MHD_WLCMD_H_
#define INCLUDED_MHD_WLCMD_H_

#ifdef __cplusplus
extern "C" {
#endif
  
  
#include "mhd_wlioctl.h"  
  
//#####################
// MACRO
//#####################
#define USAGE_ERROR  -1		/* Error code for Usage */
#define IOCTL_ERROR  -2		/* Error code for Ioctl failure */
#define BAD_PARAM -3 /* Error code for bad params, but don't dump cmd_help */
#define CMD_DEPRECATED -4 /* Commands that are functionally deprecated or don't provide
			   * a useful value to a specific OS port of wl
			   */

#define BCME_OK				0	/* Success */
#define BCME_ERROR			-1	/* Error generic */
#define BCME_BADARG			-2	/* Bad Argument */
#define BCME_BADOPTION			-3	/* Bad option */
#define BCME_NOTUP			-4	/* Not up */
#define BCME_NOTDOWN			-5	/* Not down */
#define BCME_NOTAP			-6	/* Not AP */
#define BCME_NOTSTA			-7	/* Not STA  */
#define BCME_BADKEYIDX			-8	/* BAD Key Index */
#define BCME_RADIOOFF 			-9	/* Radio Off */
#define BCME_NOTBANDLOCKED		-10	/* Not  band locked */
#define BCME_NOCLK			-11	/* No Clock */
#define BCME_BADRATESET			-12	/* BAD Rate valueset */
#define BCME_BADBAND			-13	/* BAD Band */
#define BCME_BUFTOOSHORT		-14	/* Buffer too short */
#define BCME_BUFTOOLONG			-15	/* Buffer too long */
#define BCME_BUSY			-16	/* Busy */
#define BCME_NOTASSOCIATED		-17	/* Not Associated */
#define BCME_BADSSIDLEN			-18	/* Bad SSID len */
#define BCME_OUTOFRANGECHAN		-19	/* Out of Range Channel */
#define BCME_BADCHAN			-20	/* Bad Channel */
#define BCME_BADADDR			-21	/* Bad Address */
#define BCME_NORESOURCE			-22	/* Not Enough Resources */
#define BCME_UNSUPPORTED		-23	/* Unsupported */
#define BCME_BADLEN			-24	/* Bad length */
#define BCME_NOTREADY			-25	/* Not Ready */
#define BCME_EPERM			-26	/* Not Permitted */
#define BCME_NOMEM			-27	/* No Memory */
#define BCME_ASSOCIATED			-28	/* Associated */
#define BCME_RANGE			-29	/* Not In Range */
#define BCME_NOTFOUND			-30	/* Not Found */
#define BCME_WME_NOT_ENABLED		-31	/* WME Not Enabled */
#define BCME_TSPEC_NOTFOUND		-32	/* TSPEC Not Found */
#define BCME_ACM_NOTSUPPORTED		-33	/* ACM Not Supported */
#define BCME_NOT_WME_ASSOCIATION	-34	/* Not WME Association */
#define BCME_SDIO_ERROR			-35	/* SDIO Bus Error */
#define BCME_DONGLE_DOWN		-36	/* Dongle Not Accessible */
#define BCME_VERSION			-37 	/* Incorrect version */
#define BCME_TXFAIL			-38 	/* TX failure */
#define BCME_RXFAIL			-39	/* RX failure */
#define BCME_NODEVICE			-40 	/* Device not present */
#define BCME_NMODE_DISABLED		-41 	/* NMODE disabled */
#define BCME_NONRESIDENT		-42 /* access to nonresident overlay */
#define BCME_SCANREJECT			-43 	/* reject scan request */
#define BCME_USAGE_ERROR                -44     /* WLCMD usage error */
#define BCME_IOCTL_ERROR                -45     /* WLCMD ioctl error */
#define BCME_SERIAL_PORT_ERR            -46     /* RWL serial port error */
#define BCME_DISABLED                   -47     /* Disabled in this build */
#define BCME_DECERR				-48		/* Decrypt error */
#define BCME_ENCERR				-49		/* Encrypt error */
#define BCME_MICERR				-50		/* Integrity/MIC error */
#define BCME_REPLAY				-51		/* Replay */
#define BCME_IE_NOTFOUND		-52		/* IE not found */
#define BCME_LAST			BCME_IE_NOTFOUND

//#####################
// CHANNEL
//#####################
#define CH_20MHZ_APART			4
#define CH_10MHZ_APART			2
#define CH_5MHZ_APART			1	/* 2G band channels are 5 Mhz apart */

#define CH_MAX_2G_CHANNEL		14	/* Max channel in 2G band */
#define MAXCHANNEL				224	/* max # supported channels. The max channel no is 216*/


#define CH_MIN_5G_UNII1			36
#define CH_MAX_5G_UNII1			48
#define CH_MIN_5G_UNII2			52
#define CH_MAX_5G_UNII2			64
#define CH_MIN_5G_UNII2_EXT		100
#define CH_MAX_5G_UNII2_EXT		144
#define CH_MIN_5G_UNII3			149
#define CH_MAX_5G_UNII3			161




#define CHANSPEC_STR_LEN    			8

#define INVCHANSPEC			255

//#####################
// PHY
//#####################
#define	WLC_PHY_TYPE_HT		7
#define	WLC_PHY_TYPE_LCN40	10
#define WLC_PHY_TYPE_AC		11

//#####################
// IE
//#####################
#define VNDR_IE_HDR_LEN     2   /* id + len field */
#define VNDR_IE_MIN_LEN     3   /* size of the oui field */

#define MAX_DATA_COLS	16	/* MAX data cols */

#define DOT11_MNG_PROPR_ID          221 /* xxx d11 management proprietary id */

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef uint8_t uchar;
typedef uint16_t ushort;
#if defined(__ICCARM__)
typedef uint32_t uint;
#endif
#ifndef TYPEDEF_UINTPTR
typedef unsigned int	uintptr;
#endif

struct dot11_assoc_req {
	uint16			capability;	/* capability information */
	uint16			listen;		/* listen interval */
};

struct dot11_assoc_resp {
	uint16			capability;	/* capability information */
	uint16			status;		/* status code */
	uint16			aid;		/* association ID */
};

/** Vendor IE structure */
struct vndr_ie {
    uint8 id;
    uint8 len;
    uint8 oui [3];
    uint8 data [1];     /* Variable size data */
};
typedef struct vndr_ie vndr_ie_t;

typedef struct {
	uint32 pktflag;		/* bitmask indicating which packet(s) contain this IE */
	uint8 id;		/* IE type */
} ie_getbuf_t;


#ifndef TRUE
#define TRUE	1  /* TRUE */
#endif
#ifndef FALSE
#define FALSE	0  /* FALSE */
#endif

#ifndef OFFSETOF
#ifdef __ARMCC_VERSION
/*
 * The ARM RVCT compiler complains when using OFFSETOF where a constant
 * expression is expected, such as an initializer for a static object.
 * offsetof from the runtime library doesn't have that problem.
 */
#include <stddef.h>
#define	OFFSETOF(type, member)	offsetof(type, member)
#elif __GNUC__ >= 4
/* New versions of GCC are also complaining if the usual macro is used */
#define OFFSETOF(type, member)  __builtin_offsetof(type, member)
#else
#define	OFFSETOF(type, member)	((uint)(uintptr)&((type *)0)->member)
#endif /* __ARMCC_VERSION */
#endif /* OFFSETOF */

extern int mhd_wl_cmd( int argc, char **argv );
extern int wlu_var_setbuf(void *wl, const char *iovar, void *param, int param_len);
extern int
wlu_iovar_getbuf(void* wl, const char *iovar,
	void *param, int paramlen, void *bufptr, int buflen);
extern int
wlu_iovar_setbuf(void* wl, const char *iovar,
	void *param, int paramlen, void *bufptr, int buflen);
extern int
wlu_var_getbuf_sm(void *wl, const char *iovar, void *param, int param_len, void **bufptr);
extern int
wlu_var_getbuf_med(void *wl, const char *iovar, void *param, int param_len, void **bufptr);
extern void
wl_printlasterror(void *wl);
extern int
wlu_var_getbuf(void *wl, const char *iovar, void *param, int param_len, void **bufptr);

#define uint uint32

extern void
dump_rateset(uint8 *rates, uint count);

extern void
dump_bss_info(wl_bss_info_t *bi);

#ifdef __cplusplus
	}
#endif

#endif /* INCLUDED_MHD_WLCMD_H_ */
