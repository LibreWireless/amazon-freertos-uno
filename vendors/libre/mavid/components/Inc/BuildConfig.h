#ifndef _BUILD_CONFIG_H_
#define _BUILD_CONFIG_H_
//#define DSPG_3D_MIC_NR
//#define DSPG_2D_MIC_NR
//#define ANALOG_MIC_ENABLE
//#define SONY_REQ

#ifdef IFLYOS_ENABLED

#else
	#define	CWWD_ENABLE
#endif

/* Common Definitions */
#define AAC_OPTIMIZE
// #define BUTTON_HANDLING_WO_QUEUE
// #define BUTTON_HANDLING_SCAN
#define LOCALE  "en-US"
#define MEMORY_OPTIMIZE_SSL
#define MULTI_NETWORK_PROFILES
#define BT_A2DP_SRC_ENABLE
#define USE_MAVID_CRYP

#ifndef VERISONIX_ENABLED
        #define ENABLE_BT_HFP
#endif
#ifdef 	ENABLE_BT_HFP
    #define DSPG_2D_MIC_VC
#endif // ENABLE_BT_HFP

/* DSPG, Codec, LED, Keypad, PowerSave, Battery */

#ifdef ECSV2_ENABLED
	#define DSPG_2D_MIC_NR
	#define DSPG_AMODEL_US 1
	#define CODEC_ALC5640
	#define HP_OUTPUT
	#define BATTERY_MGMT
	#define BUTTON_CONFIG_5_ECS
	#define LED_CONFIG_HDST
	#define AUDIO_EFFECTS_ALC5640_PROFILE_3
	#define WIFI_DEEPSLEEP
    #define PSM
	#define POWER_SHUT_DOWN
	//#define ENABLE_BT_HFP
	//#define HFP_THROUGH_PCM

#elif defined ETON_ENABLED
        #define BUTTON_UI_2
	#define DSPG_2D_MIC_NR
	#define DSPG_AMODEL_US 1
	#define CODEC_ALC5640
	#define HP_OUTPUT
	#define BATTERY_MGMT
	#define AUDIO_EFFECTS_ALC5640_PROFILE_3
	#define WIFI_DEEPSLEEP
        #define PSM
	#define POWER_SHUT_DOWN
        //#define ENABLE_BT_HFP
	#ifdef ENABLE_BT_HFP
		#define DSPG_2D_MIC_VC
	#endif

#elif defined LIBRE_EVB_ENABLED
    #define HOST_INTERFACE
    #define WIFI_DEEPSLEEP	
    #ifdef SONY_REQ
    #define LOW_POWER_STREAMING
    #define DSPG_2D_MIC_NR
    #define DEBUG_MENU
    #define AUDIOPLAYER_LOCALPLAYBACK
    #define HD_SUPPORT
	#define WAV_SUPPORT
    #undef MULTI_NETWORK_PROFILES
    #else
    #define DSPG_3D_MIC
    #define ANALOG_MIC_ENABLE
    #endif
    #define BUTTON_UI_2
    #define LED_CONFIG_V2
	#define DSPG_AMODEL_US 1
	#define CODEC_ALC5640
	#define HP_OUTPUT
	//#define BUTTON_CONFIG_BRAVEN_5
	#define LIBRE_GOLF_V2
    #define CUSTOMER_PP
#ifdef HD_SUPPORT
    #define FLAC_OPTIMIZATION
    #define USER_DEFINED_RING_BUF
    #define FLAC__NO_MD5
#else
	#define STEREO_TO_MONO_CONVERT
#endif
  //#define DSPG_AMODEL_IN 1
   #define AVS_BT_SOURCE_SWITCH
	#define HAS_LSE
	#define FACTORY_RESET_ENABLED
	#ifdef  HAS_LSE
	//#define PSM
	#define USE_VESPER_VAD
	#endif

#elif defined VERISONIX_ENABLED
    #ifdef SONY_REQ
    #define LOW_POWER_STREAMING
    #define DEBUG_MENU
    #define AUDIOPLAYER_LOCALPLAYBACK
    #define HD_SUPPORT
    #define WAV_SUPPORT
    #endif
    #define DSPG_2D_MIC_NR
    #define BUTTON_UI_2
	#define DSPG_AMODEL_US 1
	#define CODEC_ALC5640
	#define HP_OUTPUT
	#define AUX_SUPPORT
	#define BUTTON_CONFIG_BRAVEN_5
	#define LIBRE_GOLF_V2
    #define CUSTOMER_PP
#ifdef HD_SUPPORT
    #define FLAC_OPTIMIZATION
    #define USER_DEFINED_RING_BUF
    #define FLAC__NO_MD5
#else
	#define STEREO_TO_MONO_CONVERT
#endif
  //#define DSPG_AMODEL_IN 1
   #define AVS_BT_SOURCE_SWITCH
	#define HAS_LSE
	#define FACTORY_RESET_ENABLED
	#ifdef  HAS_LSE
	#define PSM
	#define USE_VESPER_VAD
	#endif

#elif defined WISTRON_ENABLED
	#define DSPG_3D_MIC
	#define CODEC_ALC5640
	#define MONO_OUTPUT
	#define BUTTON_CONFIG_2

#elif defined LIBRE_EVK_ENABLED
	#define DSPG_3D_MIC
	#define CODEC_WM8904
	#define BUTTON_CONFIG_5_EVB

#elif defined BBS_ENABLED
	#define DSPG_3D_MIC
	#define DSPG_AMODEL_US 1
	#define ANALOG_MIC_ENABLE
	#define CODEC_ALC5640
	#define LIBRE_GOLF_V2
	#define STEREO_OUTPUT
	#define STEREO_TO_MONO_CONVERT
	#define BATTERY_MGMT
	#define  BUTTON_CONFIG_3
	#define AUDIO_EFFECTS_ALC5640_PROFILE_2
	#define FACTORY_RESET_ENABLED
	#define HAS_LSE
	#ifdef HAS_LSE
		#define PSM
		#define USE_VESPER_VAD
	#endif

#elif defined PICO_ENABLED
	#define DSPG_2D_MIC
	#define DSPG_AMODEL_US 1
    //    #define DSPG_2D_MIC_NR
	//#define ANALOG_MIC_ENABLE
	#define CODEC_ALC5640
	#define LIBRE_GOLF_V2
	#define STEREO_OUTPUT
	#define STEREO_TO_MONO_CONVERT
	#define BATTERY_MGMT
	#define BUTTON_CONFIG_3
	#define AUDIO_EFFECTS_ALC5640_PROFILE_8A_TEST
	#define AVS_BT_SOURCE_SWITCH
	#define HAS_LSE
   // #define WLAN_PROFILES
    #define FACTORY_RESET_ENABLED
	//#define ENABLE_BT_HFP
	#ifdef ENABLE_BT_HFP
		#define DSPG_2D_MIC_VC
	#endif
	#ifdef HAS_LSE
		#define PSM
		//#define USE_VESPER_VAD
	#endif

#elif defined BINATONE_ENABLED
	#define DSPG_2D_MIC
	#define CODEC_ALC5640
	#define LIBRE_GOLF_V2
	#define MONO_OUTPUT
	#define BATTERY_MGMT
	#define BUTTON_CONFIG_3
	//#define AUDIO_EFFECTS_ALC5640_PROFILE_7
	#define AUDIO_EFFECTS_ALC5640_PROFILE_10
	#define HAS_LSE
		#ifdef HAS_LSE
			#define PSM
		#endif

#elif defined HANSONG_ENABLED
	#define DSPG_2D_MIC
	#define CODEC_TLV320DAC
	#define BUTTON_CONFIG_2
	#define LED_WO_QUEUE

#elif defined HANSONG_MICRODOT_ENABLED
    #define BUTTON_UI_2
    #define LED_CONFIG_V2
	#define DSPG_3D_MIC
	#define DSPG_AMODEL_US 1
	#define ANALOG_MIC_ENABLE
	#define CODEC_ALC5640
	#define LIBRE_GOLF_V2
	#define STEREO_OUTPUT
	#define STEREO_TO_MONO_CONVERT
	#define BATTERY_MGMT
	//#define BUTTON_CONFIG_3
	#define AUDIO_EFFECTS_ALC5640_PROFILE_MICRODOT
        #define FACTORY_RESET_ENABLED
	#define HAS_LSE
	#ifdef HAS_LSE
		#define PSM
		#define USE_VESPER_VAD
	#endif
	#define AVS_BT_SOURCE_SWITCH
	#define BLE_MAVID_APP
    #define MULTI_NETWORK_PROFILES

#elif defined HANSONG_WAVEXD_PRO_ENABLED
    #define BUTTON_UI_2
    #define LED_CONFIG_V2
	#define DSPG_3D_MIC
	#define DSPG_AMODEL_US 1
	#define ANALOG_MIC_ENABLE
	#define CODEC_ALC5640
	#define LIBRE_GOLF_V2
	#define STEREO_OUTPUT
	#define STEREO_TO_MONO_CONVERT
	#define BATTERY_MGMT
	#define AWS_IOT_SUPPORT
	#define AUDIOPLAYER_LOCALPLAYBACK
    #define FACTORY_RESET_ENABLED
	#define HAS_LSE
	#ifdef HAS_LSE
		#define PSM
		#define USE_VESPER_VAD
	#endif
	#define AVS_BT_SOURCE_SWITCH
	#define BLE_MAVID_APP
    #define MULTI_NETWORK_PROFILES

#elif defined HANSONG_WALLE_ENABLED
    #define HOST_INTERFACE
    #define BUTTON_UI_2
    #define LED_CONFIG_V2
	#define DSPG_3D_MIC
	#define DSPG_AMODEL_US 1
	#define ANALOG_MIC_ENABLE
	#define CODEC_ALC5640
	#define LIBRE_GOLF_V2
	#define HP_OUTPUT
	#define BATTERY_MGMT
        #define FACTORY_RESET_ENABLED
	#define HAS_LSE
	#ifdef HAS_LSE
		#define PSM
		#define USE_VESPER_VAD
	#endif
	#define AVS_BT_SOURCE_SWITCH
	#define BLE_MAVID_APP
    #define MULTI_NETWORK_PROFILES

#elif defined CANDYBAR_ENABLED
    #define AWS_IOT_SUPPORT
    #define BUTTON_UI_2
    #define LED_CONFIG_V2
	#define DSPG_3D_MIC
	#define DSPG_AMODEL_US 1
	#define ANALOG_MIC_ENABLE
	#define CODEC_ALC5640
	#define LIBRE_GOLF_V2
	#define STEREO_OUTPUT
	#define STEREO_TO_MONO_CONVERT
	#define BATTERY_MGMT
	#define AUDIO_EFFECTS_ALC5640_PROFILE_MICRODOT
    #define FACTORY_RESET_ENABLED
    #define HAS_LSE
	#ifdef HAS_LSE
		#define PSM
		#define USE_VESPER_VAD
	#endif
	#define AVS_BT_SOURCE_SWITCH
	#define BLE_MAVID_APP
    #define MULTI_NETWORK_PROFILES

#elif defined  HANSONG_WAVE_ENABLED
	#define DSPG_2D_MIC_NR
	#define DSPG_AMODEL_US 1
	#define ANALOG_MIC_ENABLE
	#define CODEC_ALC5640
	#define HP_OUTPUT
	#define STEREO_TO_MONO_CONVERT

	#define BATTERY_MGMT
    #define BUTTON_UI_2
    #define LED_CONFIG_V2
	//#define BUTTON_CONFIG_HANSONG_WAVE
	#define AUDIO_EFFECTS_ALC5640_PROFILE_3

	#define HAS_LSE
	#ifdef HAS_LSE
		#define PSM
	//	#define USE_VESPER_VAD
	#endif
	#define AVS_BT_SOURCE_SWITCH
	#define FACTORY_RESET_ENABLED
	#define BLE_MAVID_APP
        #define MULTI_NETWORK_PROFILES

#elif defined  HANSONG_WAVEXD_ENABLED
	#define HOST_INTERFACE
	#define AWS_IOT_SUPPORT
	#define DSPG_2D_MIC_NR
	#define DSPG_AMODEL_US 1
	#define ANALOG_MIC_ENABLE
	#define CODEC_ALC5640
	#define LIBRE_GOLF_V2
	#define STEREO_OUTPUT
	#define STEREO_TO_MONO_CONVERT
	#define BATTERY_MGMT
	#define BUTTON_UI_2
	#define LED_CONFIG_V2
	#define AUDIO_EFFECTS_ALC5640_PROFILE_MICRODOT
	#define HAS_LSE
	#ifdef HAS_LSE
		#define PSM
	//	#define USE_VESPER_VAD
	#endif
	#define AVS_BT_SOURCE_SWITCH
	#define FACTORY_RESET_ENABLED
	#define BLE_MAVID_APP
        #define MULTI_NETWORK_PROFILES

#elif defined ZYLUX_HP_ENABLED
    #define DSPG_3D_MIC
	#define DSPG_AMODEL_US 1
	#define ANALOG_MIC_ENABLE
	#define CODEC_ALC5640
	#define HP_OUTPUT
	#define STEREO_TO_MONO_CONVERT
	#define BATTERY_MGMT
	#define BUTTON_CONFIG_BRAVEN_5
	#define AUDIO_EFFECTS_ALC5640_PROFILE_3
	#define AVS_BT_SOURCE_SWITCH
	#define HAS_LSE
	#define FACTORY_RESET_ENABLED
	#define LED_CONFIG_HDST
	#ifdef HAS_LSE
		#define PSM
		#define USE_VESPER_VAD
	#endif


#elif defined ZYLUX_STEREO_ENABLED
	#define DSPG_3D_MIC
	#define ANALOG_MIC_ENABLE
	#define CODEC_ALC5640
	#define STEREO_OUTPUT
	#define AUDIO_EFFECTS_ALC5640_PROFILE_2
	#define BUTTON_CONFIG_5_EVB
	#define BATTERY_MGMT
	#define HAS_LSE
		#ifdef HAS_LSE
			#define PSM
		#endif

#elif defined BRAVEN_ENABLED
	#define DSPG_3D_MIC
	#define DSPG_AMODEL_US 1
	#define ANALOG_MIC_ENABLE
	#define CODEC_ALC5640
	#define LIBRE_GOLF_V2
	#define STEREO_OUTPUT
	#define STEREO_TO_MONO_CONVERT
	#define BATTERY_MGMT
	#define BUTTON_CONFIG_BRAVEN_5
	#define AUDIO_EFFECTS_ALC5640_PROFILE_BRAVEN
	#define FACTORY_RESET_ENABLED
	//#define HAS_LSE
	#ifdef HAS_LSE
		#define PSM
		#define USE_VESPER_VAD
	#endif
#elif defined HAMA_HOME_PLUG
#ifdef VODAFONE_ENABLED
#define AUDIOPLAYER_LOCALPLAYBACK
#define TTS_DEVICE_VOLUME_ENABLE
#endif
    #define LED_CONFIG_V2
    #define BUTTON_UI_2
        #define ZIGBEE_FEATURE
        #define AWS_IOT_SUPPORT
	#define DSPG_3D_MIC
	#define ANALOG_MIC_ENABLE
	#define DSPG_AMODEL_US 1
	#define CODEC_ALC5640
    #define HP_OUTPUT
	#define STEREO_TO_MONO_CONVERT
	#define BUTTON_CONFIG_HAMA_HOMEPLUG
	#define HAMA_HOME_PLUG_AUDIO_EQ
	#define LIBRE_GOLF_V2
	#define HAS_LSE

	#ifdef HAS_LSE
	#define PSM
	#define USE_VESPER_VAD
	#endif

/*#elif defined VODAFONE_ENABLED
    #define LED_CONFIG_V2
    #define BUTTON_UI_2
	#define DSPG_3D_MIC
	#define ANALOG_MIC_ENABLE
	#define DSPG_AMODEL_US 1
	#define CODEC_ALC5640
    #define HP_OUTPUT
	#define STEREO_TO_MONO_CONVERT
	#define BUTTON_CONFIG_HAMA_HOMEPLUG
	#define LIBRE_GOLF_V2
	#define HAS_LSE

	#ifdef HAS_LSE
	#define PSM
	#define USE_VESPER_VAD
	#endif*/

#elif defined TATUNG_ENABLED
	#define DSPG_2D_MIC_NR
	#define DSPG_AMODEL_US 1
	#define CODEC_ALC5640
	#define HP_OUTPUT
	#define BATTERY_MGMT
        #define LED_CONFIG_V2
        #define BUTTON_UI_2
	#define AUDIO_EFFECTS_ALC5640_PROFILE_3
	#define WIFI_DEEPSLEEP
	#define PSM
	#define POWER_SHUT_DOWN

#elif defined PLATIN_AMIGO_ENABLED
        #define LED_CONFIG_V2
        #define BUTTON_UI_2
	#define DSPG_3D_MIC
	#define ANALOG_MIC_ENABLE
	#define DSPG_AMODEL_US 1
	#define CODEC_ALC5640
        #define HP_OUTPUT
        #define LIBRE_GOLF_V2
	#define HAS_LSE
	#define BATTERY_MGMT

	#ifdef HAS_LSE
	#define PSM
	#define USE_VESPER_VAD
	#endif

#endif

/* Memory related */
#ifdef MAVID_DEMOSPEAKER
	#define DYNAMIC_SRC
	#define	MAVID_DEMO1
	#define MAVID_DEMOSPEAKER_REUSE_AAC

#else
	#define HAS_SDRAM
	#define LPSDRAM_16MB

#endif

#endif
