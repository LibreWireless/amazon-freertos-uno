/* BT AVS Run time source switch via console */
#ifndef _BT_ABS_SS_H
#define _BT_ABS_SS_H

#include "FreeRTOS.h"
#include "cmsis_os.h"

#include "pf_trace.h"
#include "bta_avk_api.h"
#ifdef AVS_BT_ENABLED
#include "avs_bluetooth.h"
#endif
#include "psm.h"
//#include "features_list.h"
#include "btapp_interface.h"

#define MAX_NUM_BT_EVENTS_QUEUE    20
typedef struct
{
   // test, trigger BT manually
   int testBTReq;

   int reqBT ;
   int reqBTMode;
   int curBTMode;
   int timeoutCnt;

}BTStartupCtrl;


typedef enum
{
  AVS_Source = 0,
  BT_Source,
  Unknown
}SrcType;

#define SUCCESS 1
#define FAIL    0

static bool BT_status;

extern BTStartupCtrl gBTCtrl;


#ifdef BT_A2DP_SRC_ENABLE
typedef enum
{
	A2DP_SOURCE_DISCONNECTED = 0,
	A2DP_SOURCE_CONNECTED,
    A2DP_SOURCE_STREAMING,
    A2DP_SOURCE_PAUSED
} A2DPState;

typedef struct
{
	A2DPState curA2DPState;
}A2DPContext;

typedef enum {
       A2DP_THREAD_NOT_RUNNING = 0,
       A2DP_THREAD_RUNNING = 1,
       A2DP_THREAD_EXITING = 2

}A2DPThreadState;
#endif

void setBTsource(void);
void setAVSsource(void);
SrcType getCurrentSource(void);
void avsBT(bool state);
void btAVS(bool status);
static bool BT_on_off_status(void){ return BT_status; };
bool isBTplaying(void);
void BT_ResponsePlayState(UINT8 bt_play_st);

void BtResumePlayback(bool);
void BtPausePlayback(bool);
void BtAVSExpectSpeechSet(void);
void BtAVSExpectSpeechClear(void);
void startBTEvent();

void BtPlayNext(void);
void BtPlayPrevious(void);
void BtPlayOrPause(bool);
void BtCallAnswerOrReject(void);

void BtVolumeUp(void);
void BtVolumeDown(void);
void BtAnswerCall(void);
void BtRejectCall(void);

void BT_CodecPlayState(bool state);
void BT_ConnectStateUpdate(tBT_CONNECTION_STATUS state);
void notifyBtConnectionState(void);

void BtEnterDiscoverymode(void);
void BtExitDiscoverymode(void);
void BtPairingTrigger(void);
void nofityAVScompleteToBT(bool);

void BtDeviceDisConnect(void);
void BtDeviceConnect(void);

#ifdef BT_A2DP_SRC_ENABLE
void BT_A2DP_Src_State_Change(A2DPState evt);
#endif

#ifdef PSM
int bt_psm(enum notification_event event);
#endif
typedef enum
{
  bt_DISCONNECT = 0,
  bt_CONNECT,
  bt_PLAY,
  bt_STOP,
  bt_PAUSE,
  bt_NEXT,
  bt_PREV,
  bt_VOL_UP,
  bt_VOL_DOWN,
  bt_ANSWER_CALL,
  bt_REJECT_CALL,
  bt_NOCMD,
  bt_CONNECT_RESPONSE,
  bt_DISCONNECT_RESPONSE,
  bt_PLAY_RESPONSE,
  bt_STOP_RESPONSE,
  bt_VOL_RESPONSE,
  bt_SCAN_DEVICE,
  bt_SCAN_DEVICE_RESPONSE,
} AVRCP_E;

typedef enum{
  BT_OFF = 0,
  BT_ON
}BT_ON_OFF;

typedef enum{
    PLAYSTATE_STOPPED=0,
    PLAYSTATE_PLAYING,
    PLAYSTATE_PAUSED,
    PLAYSTATE_FWD_SEEK,
    PLAYSTATE_REV_SEEK,
    PLAYSTATE_ERROR
}BT_PLAY_STATE;

typedef enum  {
	BT_CONNECTING,
	BT_CONNECTED,
	BT_DISCONNECTED,
	BT_PAIR_TRIGGER,
} BT_LED_EVT;

typedef struct
{
  bool play_status;
  bool A2DP_Audio_Play_status;
  bool A2DP_Speech_Play_status;
  bool bt_pause_resume;
  bool bt_expect_speech;
  bool bt_auto_connect;
  bool bt_attendcall_end;
  bool isAVS_started;
  bool isBT_connected;
  bool isAVS_BTPlay_received;
  bool isExternal_Pause;
  AVRCP_E avrcp_command;
  BT_ON_OFF bt_on_off;
  tBT_CONNECTION_STATUS bt_connect_state;
  osEvent bt_event;
  osMessageQId btCmdQueue;
  //BT_Common_States_T bt_curr_state;
  //BT_Common_States_T bt_prev_state;
  //BT_Common_Modes_T bt_curr_mode;  
}BT_ss_ctx;


extern void btapp_avk_send_rc_cmd (tBTA_AVK_RC rc_op_id);

#endif
