#ifndef _wlioctl_ext_h_
#define    _wlioctl_ext_h_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define VHT_CAP_MCS_MAP_NSS_MAX                 8
typedef struct wl_rateset_args {
	uint32_t	count;			/* # rates in this set */
	uint8_t	rates[WL_MAXRATES_IN_SET];	/* rates in 500kbps units w/hi bit set if basic */
	uint8_t   mcs[MCSSET_LEN];        /* supported mcs index bit map */
	uint16_t vht_mcs[VHT_CAP_MCS_MAP_NSS_MAX]; /* supported mcs index bit map per nss */
} wl_rateset_args_t;

#define IOVAR_STR_AP                      "ap"
#define IOVAR_STR_RX_GLOM                "bus:rxglom"
#define IOVAR_STR_MAX_ASSOC              "maxassoc"
#define IOVAR_STR_MPC                    "mpc"

#define NREINITREASONCOUNT	8
typedef struct {
	uint16_t	version;	/* see definition of WL_CNT_T_VERSION */
	uint16_t	length;		/* length of entire structure */

	/* transmit stat counters */
	uint32_t	txframe;	/* tx data frames */
	uint32_t	txbyte;		/* tx data bytes */
	uint32_t	txretrans;	/* tx mac retransmits */
	uint32_t	txerror;	/* tx data errors (derived: sum of others) */
	uint32_t	txctl;		/* tx management frames */
	uint32_t	txprshort;	/* tx short preamble frames */
	uint32_t	txserr;		/* tx status errors */
	uint32_t	txnobuf;	/* tx out of buffers errors */
	uint32_t	txnoassoc;	/* tx discard because we're not associated */
	uint32_t	txrunt;		/* tx runt frames */
	uint32_t	txchit;		/* tx header cache hit (fastpath) */
	uint32_t	txcmiss;	/* tx header cache miss (slowpath) */

	/* transmit chip error counters */
	uint32_t	txuflo;		/* tx fifo underflows */
	uint32_t	txphyerr;	/* tx phy errors (indicated in tx status) */
	uint32_t	txphycrs;	/* PR8861/8963 counter */

	/* receive stat counters */
	uint32_t	rxframe;	/* rx data frames */
	uint32_t	rxbyte;		/* rx data bytes */
	uint32_t	rxerror;	/* rx data errors (derived: sum of others) */
	uint32_t	rxctl;		/* rx management frames */
	uint32_t	rxnobuf;	/* rx out of buffers errors */
	uint32_t	rxnondata;	/* rx non data frames in the data channel errors */
	uint32_t	rxbadds;	/* rx bad DS errors */
	uint32_t	rxbadcm;	/* rx bad control or management frames */
	uint32_t	rxfragerr;	/* rx fragmentation errors */
	uint32_t	rxrunt;		/* rx runt frames */
	uint32_t	rxgiant;	/* rx giant frames */
	uint32_t	rxnoscb;	/* rx no scb error */
	uint32_t	rxbadproto;	/* rx invalid frames */
	uint32_t	rxbadsrcmac;	/* rx frames with Invalid Src Mac */
	uint32_t	rxbadda;	/* rx frames tossed for invalid da */
	uint32_t	rxfilter;	/* rx frames filtered out */

	/* receive chip error counters */
	uint32_t	rxoflo;		/* rx fifo overflow errors */
	uint32_t	rxuflo[NFIFO];	/* rx dma descriptor underflow errors */

	uint32_t	d11cnt_txrts_off;	/* d11cnt txrts value when reset d11cnt */
	uint32_t	d11cnt_rxcrc_off;	/* d11cnt rxcrc value when reset d11cnt */
	uint32_t	d11cnt_txnocts_off;	/* d11cnt txnocts value when reset d11cnt */

	/* misc counters */
	uint32_t	dmade;		/* tx/rx dma descriptor errors */
	uint32_t	dmada;		/* tx/rx dma data errors */
	uint32_t	dmape;		/* tx/rx dma descriptor protocol errors */
	uint32_t	reset;		/* reset count */
	uint32_t	tbtt;		/* cnts the TBTT int's */
	uint32_t	txdmawar;	/* # occurrences of PR15420 workaround */
	uint32_t	pkt_callback_reg_fail;	/* callbacks register failure */

	/* MAC counters: 32-bit version of d11.h's macstat_t */
	uint32_t	txallfrm;	/* total number of frames sent, incl. Data, ACK, RTS, CTS,
				 * Control Management (includes retransmissions)
				 */
	uint32_t	txrtsfrm;	/* number of RTS sent out by the MAC */
	uint32_t	txctsfrm;	/* number of CTS sent out by the MAC */
	uint32_t	txackfrm;	/* number of ACK frames sent out */
	uint32_t	txdnlfrm;	/* Not used */
	uint32_t	txbcnfrm;	/* beacons transmitted */
	uint32_t	txfunfl[6];	/* per-fifo tx underflows */
	uint32_t	rxtoolate;	/* receive too late */
	uint32_t  txfbw;		/* transmit at fallback bw (dynamic bw) */
	uint32_t	txtplunfl;	/* Template underflows (mac was too slow to transmit ACK/CTS
				 * or BCN)
				 */
	uint32_t	txphyerror;	/* Transmit phy error, type of error is reported in tx-status for
				 * driver enqueued frames
				 */
	uint32_t	rxfrmtoolong;	/* Received frame longer than legal limit (2346 bytes) */
	uint32_t	rxfrmtooshrt;	/* Received frame did not contain enough bytes for its frame type */
	uint32_t	rxinvmachdr;	/* Either the protocol version != 0 or frame type not
				 * data/control/management
				 */
	uint32_t	rxbadfcs;	/* number of frames for which the CRC check failed in the MAC */
	uint32_t	rxbadplcp;	/* parity check of the PLCP header failed */
	uint32_t	rxcrsglitch;	/* PHY was able to correlate the preamble but not the header */
	uint32_t	rxstrt;		/* Number of received frames with a good PLCP
				 * (i.e. passing parity check)
				 */
	uint32_t	rxdfrmucastmbss; /* Number of received DATA frames with good FCS and matching RA */
	uint32_t	rxmfrmucastmbss; /* number of received mgmt frames with good FCS and matching RA */
	uint32_t	rxcfrmucast;	/* number of received CNTRL frames with good FCS and matching RA */
	uint32_t	rxrtsucast;	/* number of unicast RTS addressed to the MAC (good FCS) */
	uint32_t	rxctsucast;	/* number of unicast CTS addressed to the MAC (good FCS) */
	uint32_t	rxackucast;	/* number of ucast ACKS received (good FCS) */
	uint32_t	rxdfrmocast;	/* number of received DATA frames (good FCS and not matching RA) */
	uint32_t	rxmfrmocast;	/* number of received MGMT frames (good FCS and not matching RA) */
	uint32_t	rxcfrmocast;	/* number of received CNTRL frame (good FCS and not matching RA) */
	uint32_t	rxrtsocast;	/* number of received RTS not addressed to the MAC */
	uint32_t	rxctsocast;	/* number of received CTS not addressed to the MAC */
	uint32_t	rxdfrmmcast;	/* number of RX Data multicast frames received by the MAC */
	uint32_t	rxmfrmmcast;	/* number of RX Management multicast frames received by the MAC */
	uint32_t	rxcfrmmcast;	/* number of RX Control multicast frames received by the MAC
				 * (unlikely to see these)
				 */
	uint32_t	rxbeaconmbss;	/* beacons received from member of BSS */
	uint32_t	rxdfrmucastobss; /* number of unicast frames addressed to the MAC from
				  * other BSS (WDS FRAME)
				  */
	uint32_t	rxbeaconobss;	/* beacons received from other BSS */
	uint32_t	rxrsptmout;	/* Number of response timeouts for transmitted frames
				 * expecting a response
				 */
	uint32_t	bcntxcancl;	/* transmit beacons canceled due to receipt of beacon (IBSS) */
	uint32_t	rxf0ovfl;	/* Number of receive fifo 0 overflows */
	uint32_t	rxf1ovfl;	/* Number of receive fifo 1 overflows (obsolete) */
	uint32_t	rxf2ovfl;	/* Number of receive fifo 2 overflows (obsolete) */
	uint32_t	txsfovfl;	/* Number of transmit status fifo overflows (obsolete) */
	uint32_t	pmqovfl;	/* Number of PMQ overflows */
	uint32_t	rxcgprqfrm;	/* Number of received Probe requests that made it into
				 * the PRQ fifo
				 */
	uint32_t	rxcgprsqovfl;	/* Rx Probe Request Que overflow in the AP */
	uint32_t	txcgprsfail;	/* Tx Probe Response Fail. AP sent probe response but did
				 * not get ACK
				 */
	uint32_t	txcgprssuc;	/* Tx Probe Response Success (ACK was received) */
	uint32_t	prs_timeout;	/* Number of probe requests that were dropped from the PRQ
				 * fifo because a probe response could not be sent out within
				 * the time limit defined in M_PRS_MAXTIME
				 */
	uint32_t	rxnack;		/* obsolete */
	uint32_t	frmscons;	/* obsolete */
	uint32_t  txnack;		/* obsolete */
	uint32_t	rxback;		/* blockack rxcnt */
	uint32_t	txback;		/* blockack txcnt */

	/* 802.11 MIB counters, pp. 614 of 802.11 reaff doc. */
	uint32_t	txfrag;		/* dot11TransmittedFragmentCount */
	uint32_t	txmulti;	/* dot11MulticastTransmittedFrameCount */
	uint32_t	txfail;		/* dot11FailedCount */
	uint32_t	txretry;	/* dot11RetryCount */
	uint32_t	txretrie;	/* dot11MultipleRetryCount */
	uint32_t	rxdup;		/* dot11FrameduplicateCount */
	uint32_t	txrts;		/* dot11RTSSuccessCount */
	uint32_t	txnocts;	/* dot11RTSFailureCount */
	uint32_t	txnoack;	/* dot11ACKFailureCount */
	uint32_t	rxfrag;		/* dot11ReceivedFragmentCount */
	uint32_t	rxmulti;	/* dot11MulticastReceivedFrameCount */
	uint32_t	rxcrc;		/* dot11FCSErrorCount */
	uint32_t	txfrmsnt;	/* dot11TransmittedFrameCount (bogus MIB?) */
	uint32_t	rxundec;	/* dot11WEPUndecryptableCount */

	/* WPA2 counters (see rxundec for DecryptFailureCount) */
	uint32_t	tkipmicfaill;	/* TKIPLocalMICFailures */
	uint32_t	tkipcntrmsr;	/* TKIPCounterMeasuresInvoked */
	uint32_t	tkipreplay;	/* TKIPReplays */
	uint32_t	ccmpfmterr;	/* CCMPFormatErrors */
	uint32_t	ccmpreplay;	/* CCMPReplays */
	uint32_t	ccmpundec;	/* CCMPDecryptErrors */
	uint32_t	fourwayfail;	/* FourWayHandshakeFailures */
	uint32_t	wepundec;	/* dot11WEPUndecryptableCount */
	uint32_t	wepicverr;	/* dot11WEPICVErrorCount */
	uint32_t	decsuccess;	/* DecryptSuccessCount */
	uint32_t	tkipicverr;	/* TKIPICVErrorCount */
	uint32_t	wepexcluded;	/* dot11WEPExcludedCount */

	uint32_t	txchanrej;	/* Tx frames suppressed due to channel rejection */
	uint32_t	psmwds;		/* Count PSM watchdogs */
	uint32_t	phywatchdog;	/* Count Phy watchdogs (triggered by ucode) */

	/* MBSS counters, AP only */
	uint32_t	prq_entries_handled;	/* PRQ entries read in */
	uint32_t	prq_undirected_entries;	/*    which were bcast bss & ssid */
	uint32_t	prq_bad_entries;	/*    which could not be translated to info */
	uint32_t	atim_suppress_count;	/* TX suppressions on ATIM fifo */
	uint32_t	bcn_template_not_ready;	/* Template marked in use on send bcn ... */
	uint32_t	bcn_template_not_ready_done; /* ...but "DMA done" interrupt rcvd */
	uint32_t	late_tbtt_dpc;	/* TBTT DPC did not happen in time */

	/* per-rate receive stat counters */
	uint32_t  rx1mbps;	/* packets rx at 1Mbps */
	uint32_t  rx2mbps;	/* packets rx at 2Mbps */
	uint32_t  rx5mbps5;	/* packets rx at 5.5Mbps */
	uint32_t  rx6mbps;	/* packets rx at 6Mbps */
	uint32_t  rx9mbps;	/* packets rx at 9Mbps */
	uint32_t  rx11mbps;	/* packets rx at 11Mbps */
	uint32_t  rx12mbps;	/* packets rx at 12Mbps */
	uint32_t  rx18mbps;	/* packets rx at 18Mbps */
	uint32_t  rx24mbps;	/* packets rx at 24Mbps */
	uint32_t  rx36mbps;	/* packets rx at 36Mbps */
	uint32_t  rx48mbps;	/* packets rx at 48Mbps */
	uint32_t  rx54mbps;	/* packets rx at 54Mbps */
	uint32_t  rx108mbps;	/* packets rx at 108mbps */
	uint32_t  rx162mbps;	/* packets rx at 162mbps */
	uint32_t  rx216mbps;	/* packets rx at 216 mbps */
	uint32_t  rx270mbps;	/* packets rx at 270 mbps */
	uint32_t  rx324mbps;	/* packets rx at 324 mbps */
	uint32_t  rx378mbps;	/* packets rx at 378 mbps */
	uint32_t  rx432mbps;	/* packets rx at 432 mbps */
	uint32_t  rx486mbps;	/* packets rx at 486 mbps */
	uint32_t  rx540mbps;	/* packets rx at 540 mbps */

	/* pkteng rx frame stats */
	uint32_t	pktengrxducast; /* unicast frames rxed by the pkteng code */
	uint32_t	pktengrxdmcast; /* multicast frames rxed by the pkteng code */

	uint32_t	rfdisable;	/* count of radio disables */
	uint32_t	bphy_rxcrsglitch;	/* PHY count of bphy glitches */
	uint32_t   bphy_badplcp;

	uint32_t	txexptime;	/* Tx frames suppressed due to timer expiration */

	uint32_t	txmpdu_sgi;	/* count for sgi transmit */
	uint32_t	rxmpdu_sgi;	/* count for sgi received */
	uint32_t	txmpdu_stbc;	/* count for stbc transmit */
	uint32_t	rxmpdu_stbc;	/* count for stbc received */

	uint32_t	rxundec_mcst;	/* dot11WEPUndecryptableCount */

	/* WPA2 counters (see rxundec for DecryptFailureCount) */
	uint32_t	tkipmicfaill_mcst;	/* TKIPLocalMICFailures */
	uint32_t	tkipcntrmsr_mcst;	/* TKIPCounterMeasuresInvoked */
	uint32_t	tkipreplay_mcst;	/* TKIPReplays */
	uint32_t	ccmpfmterr_mcst;	/* CCMPFormatErrors */
	uint32_t	ccmpreplay_mcst;	/* CCMPReplays */
	uint32_t	ccmpundec_mcst;	/* CCMPDecryptErrors */
	uint32_t	fourwayfail_mcst;	/* FourWayHandshakeFailures */
	uint32_t	wepundec_mcst;	/* dot11WEPUndecryptableCount */
	uint32_t	wepicverr_mcst;	/* dot11WEPICVErrorCount */
	uint32_t	decsuccess_mcst;	/* DecryptSuccessCount */
	uint32_t	tkipicverr_mcst;	/* TKIPICVErrorCount */
	uint32_t	wepexcluded_mcst;	/* dot11WEPExcludedCount */

	uint32_t	dma_hang;	/* count for dma hang */
	uint32_t	reinit;		/* count for reinit */

	uint32_t  pstatxucast;	/* count of ucast frames xmitted on all psta assoc */
	uint32_t  pstatxnoassoc;	/* count of txnoassoc frames xmitted on all psta assoc */
	uint32_t  pstarxucast;	/* count of ucast frames received on all psta assoc */
	uint32_t  pstarxbcmc;	/* count of bcmc frames received on all psta */
	uint32_t  pstatxbcmc;	/* count of bcmc frames transmitted on all psta */

	uint32_t  cso_passthrough; /* hw cso required but passthrough */
	uint32_t	cso_normal;	/* hw cso hdr for normal process */
	uint32_t	chained;	/* number of frames chained */
	uint32_t	chainedsz1;	/* number of chain size 1 frames */
	uint32_t	unchained;	/* number of frames not chained */
	uint32_t	maxchainsz;	/* max chain size so far */
	uint32_t	currchainsz;	/* current chain size */
	uint32_t	rxdrop20s;	/* drop secondary cnt */
	uint32_t	pciereset;	/* Secondary Bus Reset issued by driver */
	uint32_t	cfgrestore;	/* configspace restore by driver */
	uint32_t	reinitreason[NREINITREASONCOUNT]; /* reinitreason counters; 0: Unknown reason */
	uint32_t  rxrtry;		/* num of received packets with retry bit on */
} wl_cnt_ver_ten_t;

#define WL_WOWL_GTK_FAILURE     (1 << 10)
#define WL_WOWL_TCP_KEEPALIVE (1 << 17)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
