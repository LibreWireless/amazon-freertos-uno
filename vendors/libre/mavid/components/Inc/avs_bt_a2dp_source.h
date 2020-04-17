/*******************************************************************************
**      BT A2DP Source Management                                             **
*******************************************************************************/

#include "FreeRTOS.h"
#include "cmsis_os.h"

#include "pf_trace.h"

#include "avs.h"
#include "btapp_interface.h"
#include "env_uid.h"
#include "bta_api.h"
#include "bta_av_api.h"
#include "features_list.h"
#include "btapp_dm.h"
#include "dspg_UsecaseHandler.h"
#include "btapp_int.h"

#define BTAPP_NUM_INQ_REM_DEVICE 10
#define SINK_SCAN_TIMEOUT       14000
#define SINK_CONNECT_TIMEOUT    8000
#define A2DP_SOURCE_SWITCH_TIMEOUT	10000

typedef enum {
  BT_A2DP_DISCOVERY_DONE=0,
  BT_A2DP_DISCOVERY_BEGIN,
} BT_A2DP_Soure_States_T;

typedef enum
{
  BT_A2DP_SINK = 0,
  BT_A2DP_SOURCE,
}BT_A2DP_Source;

typedef struct
{
  char                  uniqueDeviceId[BT_UUID_LENGTH+1];
  char                  FriendlyName[BTAPP_DEV_NAME_LENGTH+1];
  uint8_t               truncatedMacAddress[MAC_ADDR_LEN];
}discoveredDevices;

typedef struct
{
  bool          IsSinkConnected;
  bool          IsStreamingStarted;
  bool          IsA2DPSource;
  bool          IsInSanningMode;
  BT_A2DP_Source     BTA2DP_Type;
  discoveredDevicesItem        discoveredDevicesList[BTAPP_NUM_INQ_REM_DEVICE];
  BT_A2DP_Soure_States_T	BTA2DP_Curr_State;
  BT_A2DP_Soure_States_T	BTA2DP_Prev_State;
  discoveredDevicesItem        sink_dev;
  bool			isConnectDifferent;
  int sink_db_ind;
  int src_db_ind;
  int sink_search_done_event;
} btA2DPSource;


void Set_BT_A2DP_Discovery_State(BT_A2DP_Soure_States_T state);
BT_A2DP_Soure_States_T Get_BT_A2DP_Discovery_State(void);

BT_A2DP_Source BT_GetA2DP_Type(void);
void BT_SetA2DP_Type(BT_A2DP_Source bt_type);
void BT_SetSource_Type(char *type);
void BT_A2DP_SourceInit(void);
void BT_SearchA2DP_Sink_Devices(void);
void BtUpdateSinkScanResults(void);
void BtUpdateSinkConnectStatus(bool state);
void BT_ConnectSink_Device(char *uuid);
error_t getBT_SinkDevicesInfo(char* buf, int* len);
error_t getBT_SinkConnectStatus(char* buf, int* len);
