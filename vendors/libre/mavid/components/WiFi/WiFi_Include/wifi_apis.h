#ifndef __wifi_apis__
#define __wifi_apis__

/* Need to change these values for better power
consumption */
#define IDLE_SLEEP_SLOW     900
#define IDLE_SLEEP_QUICK    200
#define IDLE_SLEEP_VQUICK   100
#define IDLE_SLEEP_AGRSIV   10 

typedef enum wifisecurity {
  OPEN,
  WPA_PSK_AES,     // WPA-PSK AES
  WPA2_PSK_AES,    // WPA2-PSK AES
  WEP_OPEN,        // WEP+OPEN
  WEP_SHARED,      // WEP+SHARE
  WPA_PSK_TKIP,    // WPA-PSK TKIP
  WPA_PSK_MIXED,   // WPA-PSK AES & TKIP MIXED
  WPA2_PSK_TKIP,   // WPA2-PSK TKIP
  WPA2_PSK_MIXED,   // WPA2-PSK AES & TKIP MIXED
} wifisecurity_t;

typedef enum {
  SLOW,     //500ms of idle to sleep
  QUICK,    // 200ms of idle to sleep
  VERYQUICK, //80ms of idle to sleep
  AGRESSIVE  //10ms of idle to sleep
}SleepFreq;


typedef enum wifimsgtype
{
  WAKEMSG = 0xFF,
  WIFI_OFF = 0,
  WIFI_ON,
  WIFISCAN,  
  WIFI_CONNECT,
  WIFI_DISCONNECT,
  WIFI_APMODE,
  WIFI_STAMODE,
  WIFI_CONF_AP,
  MAX_MSG,           //8
}wifimsgtype;

typedef enum {
  WIFI_SSID_NAME,
  WIFI_LINK_STATUS,
  WIFI_MODE,
  WIFI_ERROR_INFO
}eWifiInfo;

typedef enum {
  eStation,
  eAccespoint
}ewifimode_t;

typedef union {
  char ssid[33];
  uint32_t linkstat;
  uint8_t  mode;
  //Tp do
}wifiinfo_t;


typedef struct wifitrlmsg
{
  bool bfreeparam;
  wifimsgtype type;
  uint32_t apiwaittime;
  void *param;
  uint32_t len;  
}wifitrlmsg;

typedef struct connectparam
{
  char ssid[33];
  char password[64];
  uint8_t ssidlen;
  uint8_t pwdlen;
}connectparam;

typedef struct stamodeparam
{
  bool bneedconnect;
  bool isSACtimeout;
  int  connectprofile;
}stamodeparam_t;

typedef struct ap_info {
  char ssid[32];
  char bssid[6];
  uint32_t channel;
  uint32_t security;
  uint32_t rssi;
} ap_info_t;

typedef enum
{
  eOPEN,
  eWEP,  	
  eWPA,
  eWPA2,
  eUNKNWN,
} security_t;

typedef struct
{
  char  pcSSID[32];
  uint8_t     ucSSIDLength;
  char  pcPassword[64];
  uint8_t      ucPasswordLength;
  security_t Security;
  int8_t cChannel;
} apconfig_t;


typedef struct scan_result_info
{
  int res_len;
  ap_info_t scanptr[0];
}scan_result_info_t;


wifitrlmsg* create_ctrlmsg(wifimsgtype type, 
                           void *param, uint32_t len, 
                           bool bfreeparam, uint32_t apiwaittime);
int postmsg_wifi(void *msg);
uint32_t get_ip_address();
void get_sta_macid(char *macid);
int set_wifi_deepsleep(int bsleep);
int get_drv_scan_results(void *scan_results, int *len );
int get_wifi_info(eWifiInfo infoId, wifiinfo_t *wlinfo );
int stop_access_point(int activeprofile, bool bconnect, bool isTimeout);

#ifdef PSM        
enum notification_event;        
int notifywifiOnstandby(enum notification_event);        
#endif
#endif
