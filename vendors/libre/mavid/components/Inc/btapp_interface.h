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

#define MAX_NUM_BT_EVENTS_QUEUE    20
#define SUCCESS 1
#define FAIL    0

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
}MediaSrcType;

#ifdef BT_A2DP_SRC_ENABLE
typedef enum
{
  A2DP_SOURCE_IDLE = 0,
  A2DP_SOURCE_CONNECTING,
  A2DP_SOURCE_CONNECTED,
  A2DP_SOURCE_STREAMING,
  A2DP_SOURCE_PAUSED,
  A2DP_SOURCE_DISCONNECTING,
  A2DP_SOURCE_DISCONNECTED,
} A2DPState;

typedef struct
{
  A2DPState curA2DPState,prevA2DPState;
}A2DPContext;

typedef enum {
       A2DP_THREAD_NOT_RUNNING = 0,
       A2DP_THREAD_RUNNING = 1,
       A2DP_THREAD_EXITING = 2
}A2DPThreadState;
#endif

typedef enum{
  BT_OFF = 0,
  BT_ON
}BT_ON_OFF;

typedef enum
{
	BT_STATE_IDLE = 0,
	BT_STATE_PAIRING = 1,
	BT_STATE_CONNECTING =2,
	BT_STATE_CONNECTED=3,
	BT_STATE_DISCONNECTING=4,
    BT_STATE_PLAYING=5,
    BT_STATE_PAUSED=6
}BT_Common_States_T;

typedef enum
{
	BT_MODE_SINK = 0,
	BT_MODE_SOURCE,
}BT_Common_Modes_T;

typedef enum
{
    BT_MODE,
    ZIGBEE_MODE,
    WIFI_MODE
}Source_Mode;

typedef enum
{
  BT_EVT_IDLE = 0,
  BT_EVT_PAIR=1,
  BT_EVT_CONNECT=2,
  BT_EVT_CONNECTING=3,
  BT_EVT_CONNECTED=4,
  BT_EVT_CONNECTED_RESPONSE=5,
  BT_EVT_DISCONNECT=6,
  BT_EVT_DISCONNECTING=7,
  BT_EVT_DISCONNECTED=8,
  BT_EVT_DISCONNECTED_RESPONSE=9,
  BT_EVT_AUTOCON_FAILED=10,
  BT_EVT_PLAYBACK_PLAY=11,
  BT_EVT_PLAYBACK_PAUSE=12,
  BT_EVT_PLAYBACK_NEXT=13,
  BT_EVT_PLAYBACK_PREV=14,
  BT_EVT_PLAYBACK_STOP=15,
  BT_EVT_PLAYBACK_VOLUP=16,
  BT_EVT_PLAYBACK_VOLDOWN=17,
  BT_EVT_CALL_RINGING=18,
  BT_EVT_CALL_ANSWER=19,
  BT_EVT_CALL_REJECT=20,
  BT_EVT_CALL_MUTE=21,
  BT_EVT_CALL_UNMUTE=22,
  BT_EVT_PLAY_RESPONSE=23,
  BT_EVT_STOP_RESPONSE=24,
  BT_EVT_VOL_RESPONSE=25,
  BT_EVT_SCAN_DEVICE=26,
  BT_EVT_SCAN_DEVICE_RESPONSE=27,
  BT_EVT_DEVICE_INIT=28,
  BT_EVT_DEVICE_DEINIT=29,
  BT_EVT_DEVICE_START=30,
  BT_EVT_STREAMING_STARTED=31,
  BT_EVT_STREAMING_STOPPED=32,
  BT_EVT_PAIR_TIMEOUT=33,
}BT_Common_Events_T;

typedef enum
{
  BT_IDLE_HANDLER = 0,
  BT_PAIR_HANDLER,
  BT_CONNECT_HANDLER,
  BT_CONNECTING_HANDLER,
  BT_CONNECTED_HANDLER,
  BT_CONNECTED_RESPONSE_HANDLER,
  BT_DISCONNECT_HANDLER,
  BT_DISCONNECTING_HANDLER,
  BT_DISCONNECTED_HANDLER,
  BT_DISCONNECTED_RESPONSE_HANDLER,
  BT_AUTOCON_FAILED_HANDLER,
  BT_PLAYBACK_PLAY_HANDLER,
  BT_PLAYBACK_PAUSE_HANDLER,
  BT_PLAYBACK_NEXT_HANDLER,
  BT_PLAYBACK_PREV_HANDLER,
  BT_PLAYBACK_STOP_HANDLER,
  BT_PLAYBACK_VOLUP_HANDLER,
  BT_PLAYBACK_VOLDOWN_HANDLER,
  BT_CALL_RINGING_HANDLER,
  BT_CALL_ANSWER_HANDLER,
  BT_CALL_REJECT_HANDLER,
  BT_CALL_MUTE_HANDLER,
  BT_CALL_UNMUTE_HANDLER,
  BT_PLAY_RESPONSE_HANDLER,
  BT_STOP_RESPONSE_HANDLER,
  BT_VOL_RESPONSE_HANDLER,
  BT_SCAN_DEVICE_HANDLER,
  BT_SCAN_DEVICE_RESPONSE_HANDLER,
  BT_DEVICE_INIT_HANDLER,
  BT_DEVICE_DEINIT_HANDLER,
  BT_DEVICE_START_HANDLER,
  BT_STREAMING_STARTED_HANDLER,
  BT_STREAMING_STOPPED_HANDLER,
  BT_PAIR_TIMEOUT_HANDLER,
  BT_NONE_HANDLER, //34
}BT_Common_Evt_Handler_T;


typedef enum{
    PLAYSTATE_STOPPED=0,
    PLAYSTATE_PLAYING,
    PLAYSTATE_PAUSED,
    PLAYSTATE_FWD_SEEK,
    PLAYSTATE_REV_SEEK,
    PLAYSTATE_ERROR
}BT_PLAY_STATE;

typedef enum  {
	BT_IDLE,
	BT_CONNECTING,
	BT_CONNECTED,
	BT_DISCONNECTED,
	BT_PAIR_TRIGGER,
    BT_PLAYING,
    BT_PAUSED,

} BT_LED_EVT;


typedef struct
{
  bool BT_Evt_Ready;
  bool isExternalPause;
  bool A2DP_Audio_Play_status;
  bool A2DP_Speech_Play_status;
  bool bt_pause_resume;
  bool bt_expect_speech;
  bool bt_auto_connect;
  bool bt_attendcall_end;
  bool isAVS_started;
  bool isBT_connected;
  bool isAVS_BTPlay_received;
  bool isAVS_BTStop_received;
  bool AVS_started_buffer_cleared;
  bool button_play_pause;
  tBT_CONNECTION_STATUS bt_connect_state;
  osEvent bt_event;
  osMessageQId btCmdQueue;
  BT_Common_States_T bt_curr_state;
  BT_Common_States_T bt_prev_state;
  BT_Common_Modes_T bt_curr_mode;
  BT_Common_States_T bt_switch_trigger_state;
}BT_ss_ctx;



void setBTsource(void);
void setAVSsource(void);
MediaSrcType getCurrentSource(void);
int isBTplaying(void);
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
void Notify_Evts_To_BT(BT_Common_Events_T evt);
void Update_BT_State(BT_Common_States_T state);
typedef void (*btLED_evt_cb)(BT_LED_EVT evt);
void subscribe_for_btLED_evts(btLED_evt_cb cb);
void unsubscribe_for_btLED_evts(btLED_evt_cb cb);
BT_Common_States_T Get_Curr_BT_State();
BT_Common_States_T Get_Prev_BT_State();
BT_Common_Modes_T Get_BT_Current_Mode(void);
void Set_BT_Current_Mode(BT_Common_Modes_T);

void PrintRunTimeTaskStats(void);


#ifdef BT_A2DP_SRC_ENABLE
void BT_A2DP_Src_State_Change(A2DPState evt);
#endif

#ifdef PSM
int bt_psm(enum notification_event event);
#endif
extern void btapp_avk_send_rc_cmd (tBTA_AVK_RC rc_op_id);

/************* Event Handler's ***************/
void BTEvt_Idle_Handler();
static void BTEvt_Pair_Handler();
static void BTEvt_Connect_Handler();
static void BTEvt_Connecting_Handler();
static void BTEvt_Connected_Handler();
static void BTEvt_Connected_Response_Handler();
static void BTEvt_DisConnect_Handler();
static void BTEvt_DisConnected_Handler();
static void BTEvt_DISConnected_Response_Handler();
static void BTEvt_DISConnecting_Handler();
static void BTEvt_autccon_failed_Handler();
static void BTEvt_Play_Handler();
static void BTEvt_Pause_Handler();
static void BTEvt_Next_Handler();
static void BTEvt_Prev_Handler();
static void BTEvt_Stop_Handler();
static void BTEvt_VolUP_Handler();
static void BTEvt_VolDown_Handler();
static void BTEvt_Call_Ringing_Handler();
static void BTEvt_Call_Answer_Handler();
static void BTEvt_Call_Reject_Handler();
static void BTEvt_Call_Mute_Handler();
static void BTEvt_Call_Unmute_Handler();
static void BTEvt_Play_Response_Handler();
static void BTEvt_Stop_Response_Handler();
static void BTEvt_Vol_Response_Handler();
static void BTEvt_Scan_Device_Handler();
static void BTEvt_Scan_Device_Response_Handler();
void BTEvt_Device_Init_Handler();
static void BTEvt_Device_DeInit_Handler();
static void BTEvt_Device_Start_Handler();
static void BTEvt_Stream_Started_Handler();
static void BTEvt_Stream_Stopped_Handler();
static void BTEvt_Pair_Timeout_Handler();
static void BTEvt_None_Handler();

/********************************************/

void BT_A2DP_SourceInit(void);
/********************************************/

#endif
