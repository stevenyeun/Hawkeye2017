

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Mon Dec 29 15:15:38 2014
 */
/* Compiler settings for .\TVS.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __TVS_h__
#define __TVS_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITVSLiveControl_FWD_DEFINED__
#define __ITVSLiveControl_FWD_DEFINED__
typedef interface ITVSLiveControl ITVSLiveControl;
#endif 	/* __ITVSLiveControl_FWD_DEFINED__ */


#ifndef __ITVSDecodeControl_FWD_DEFINED__
#define __ITVSDecodeControl_FWD_DEFINED__
typedef interface ITVSDecodeControl ITVSDecodeControl;
#endif 	/* __ITVSDecodeControl_FWD_DEFINED__ */


#ifndef __ITVSDecodeCallback_FWD_DEFINED__
#define __ITVSDecodeCallback_FWD_DEFINED__
typedef interface ITVSDecodeCallback ITVSDecodeCallback;
#endif 	/* __ITVSDecodeCallback_FWD_DEFINED__ */


#ifndef __ITVSDisplay_FWD_DEFINED__
#define __ITVSDisplay_FWD_DEFINED__
typedef interface ITVSDisplay ITVSDisplay;
#endif 	/* __ITVSDisplay_FWD_DEFINED__ */


#ifndef __ITVSPlaybackControl_FWD_DEFINED__
#define __ITVSPlaybackControl_FWD_DEFINED__
typedef interface ITVSPlaybackControl ITVSPlaybackControl;
#endif 	/* __ITVSPlaybackControl_FWD_DEFINED__ */


#ifndef __ITVSIVSControl_FWD_DEFINED__
#define __ITVSIVSControl_FWD_DEFINED__
typedef interface ITVSIVSControl ITVSIVSControl;
#endif 	/* __ITVSIVSControl_FWD_DEFINED__ */


#ifndef ___ITVSLiveControlEvents_FWD_DEFINED__
#define ___ITVSLiveControlEvents_FWD_DEFINED__
typedef interface _ITVSLiveControlEvents _ITVSLiveControlEvents;
#endif 	/* ___ITVSLiveControlEvents_FWD_DEFINED__ */


#ifndef __TVSLiveControl_FWD_DEFINED__
#define __TVSLiveControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVSLiveControl TVSLiveControl;
#else
typedef struct TVSLiveControl TVSLiveControl;
#endif /* __cplusplus */

#endif 	/* __TVSLiveControl_FWD_DEFINED__ */


#ifndef ___ITVSPlaybackControlEvents_FWD_DEFINED__
#define ___ITVSPlaybackControlEvents_FWD_DEFINED__
typedef interface _ITVSPlaybackControlEvents _ITVSPlaybackControlEvents;
#endif 	/* ___ITVSPlaybackControlEvents_FWD_DEFINED__ */


#ifndef __TVSPlaybackControl_FWD_DEFINED__
#define __TVSPlaybackControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVSPlaybackControl TVSPlaybackControl;
#else
typedef struct TVSPlaybackControl TVSPlaybackControl;
#endif /* __cplusplus */

#endif 	/* __TVSPlaybackControl_FWD_DEFINED__ */


#ifndef ___ITVSDecodeControlEvents_FWD_DEFINED__
#define ___ITVSDecodeControlEvents_FWD_DEFINED__
typedef interface _ITVSDecodeControlEvents _ITVSDecodeControlEvents;
#endif 	/* ___ITVSDecodeControlEvents_FWD_DEFINED__ */


#ifndef __TVSDecodeControl_FWD_DEFINED__
#define __TVSDecodeControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVSDecodeControl TVSDecodeControl;
#else
typedef struct TVSDecodeControl TVSDecodeControl;
#endif /* __cplusplus */

#endif 	/* __TVSDecodeControl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_TVS_0000_0000 */
/* [local] */ 

#define SERVER_TIME_DISPLAY "%SERVERTIME%"
#define FRAMERATE_DISPLAY "%FRAMERATE%"



#pragma pack(1)
typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0001
    {	TN_LCI_MAX_MONITOR	= 0,
	TN_LCI_MAX_DISPLAY_CHANNEL	= ( TN_LCI_MAX_MONITOR + 1 ) ,
	TN_LCI_MAX_RECORD_CHANNEL	= ( TN_LCI_MAX_DISPLAY_CHANNEL + 1 ) ,
	TN_LCI_MAX_RESOLUTION	= ( TN_LCI_MAX_RECORD_CHANNEL + 1 ) ,
	TN_LCI_MIC_VOL	= ( TN_LCI_MAX_RESOLUTION + 1 ) ,
	TN_LCI_SPEAKER_VOL	= ( TN_LCI_MIC_VOL + 1 ) ,
	TN_LCI_SNAPSHOT_FOLDER	= ( TN_LCI_SPEAKER_VOL + 1 ) ,
	TN_LCI_BUFFER_FRAMES	= ( TN_LCI_SNAPSHOT_FOLDER + 1 ) ,
	TN_LCI_SYNC_CONNECT	= ( TN_LCI_BUFFER_FRAMES + 1 ) ,
	TN_LCI_AUTO_PLAY	= ( TN_LCI_SYNC_CONNECT + 1 ) ,
	TN_LCI_PTZ_BASE	= ( TN_LCI_AUTO_PLAY + 1 ) ,
	TN_LCI_MAX_HD_CHANNEL	= ( TN_LCI_PTZ_BASE + 1 ) ,
	TN_LCI_DISPLAY_VIDEOLOSS_ON	= ( TN_LCI_MAX_HD_CHANNEL + 1 ) ,
	TN_LCI_DISPLAY_VIDEOLOSS_TEXT	= ( TN_LCI_DISPLAY_VIDEOLOSS_ON + 1 ) ,
	TN_LCI_DISPLAY_TEXT_FOREGROUND	= ( TN_LCI_DISPLAY_VIDEOLOSS_TEXT + 1 ) ,
	TN_LCI_DISPLAY_TEXT_BACKGROUND	= ( TN_LCI_DISPLAY_TEXT_FOREGROUND + 1 ) ,
	TN_LCI_DISPLAY_GRID_ON	= ( TN_LCI_DISPLAY_TEXT_BACKGROUND + 1 ) ,
	TN_LCI_DISPLAY_GRID_COLOR	= ( TN_LCI_DISPLAY_GRID_ON + 1 ) ,
	TN_LCI_DISPLAY_TRY_CONNECT_ON	= ( TN_LCI_DISPLAY_GRID_COLOR + 1 ) ,
	TN_LCI_DISPLAY_TRY_CONNECT_TEXT	= ( TN_LCI_DISPLAY_TRY_CONNECT_ON + 1 ) ,
	TN_LCI_DISPLAY_DISCONNECT_ON	= ( TN_LCI_DISPLAY_TRY_CONNECT_TEXT + 1 ) ,
	TN_LCI_DISPLAY_DISCONNECT_TEXT	= ( TN_LCI_DISPLAY_DISCONNECT_ON + 1 ) ,
	TN_LCI_DISPLAY_GRID_WIDTH	= ( TN_LCI_DISPLAY_DISCONNECT_TEXT + 1 ) ,
	TN_LCI_DISPLAY_STATISTICS	= ( TN_LCI_DISPLAY_GRID_WIDTH + 1 ) ,
	TN_LCI_OSD_MODE	= ( TN_LCI_DISPLAY_STATISTICS + 1 ) ,
	TN_LCI_CONNECTION_TIMEOUT	= ( TN_LCI_OSD_MODE + 1 ) ,
	TN_LCI_ONSCREEN_DIGITALZOOM	= ( TN_LCI_CONNECTION_TIMEOUT + 1 ) ,
	TN_LCI_D3D_RESOURCES	= ( TN_LCI_ONSCREEN_DIGITALZOOM + 1 ) ,
	TN_LCI_NATIVE_NOTIFICATIONS	= ( TN_LCI_D3D_RESOURCES + 1 ) ,
	TN_LCI_IVS_PRESENTED	= ( TN_LCI_NATIVE_NOTIFICATIONS + 1 ) ,
	TN_LCI_IVS_USE	= ( TN_LCI_IVS_PRESENTED + 1 ) ,
	TN_LCI_ENUM_SERVERS	= ( TN_LCI_IVS_USE + 1 ) ,
	TN_LCI_TCFID	= ( TN_LCI_ENUM_SERVERS + 1 ) ,
	TN_LCI_PLAYBACKTIME	= ( TN_LCI_TCFID + 1 ) ,
	TN_LCI_KEYFRAMES_ONLY_FF	= ( TN_LCI_PLAYBACKTIME + 1 ) ,
	TN_LCI_1X1_VIDEO_CHNL	= ( TN_LCI_KEYFRAMES_ONLY_FF + 1 ) ,
	TN_LCI_1X1_AUDIO_CHNL	= ( TN_LCI_1X1_VIDEO_CHNL + 1 ) ,
	TN_LCI_PLAYBACKTIME_FONTSIZE	= ( TN_LCI_1X1_AUDIO_CHNL + 1 ) ,
	TN_LCI_DISPLAY_OUTOFMEMORY_TEXT	= ( TN_LCI_PLAYBACKTIME_FONTSIZE + 1 ) ,
	TN_LCI_AVSYNC_ENABLE	= ( TN_LCI_DISPLAY_OUTOFMEMORY_TEXT + 1 ) ,
	TN_LCI_AVSYNC_RESYNC	= ( TN_LCI_AVSYNC_ENABLE + 1 ) ,
	TN_LCI_ABUFFER	= ( TN_LCI_AVSYNC_RESYNC + 1 ) ,
	TN_LCI_SNAPSHOT_ASPECTRATIO	= ( TN_LCI_ABUFFER + 1 ) ,
	TN_LCI_APPLICATION_ID	= ( TN_LCI_SNAPSHOT_ASPECTRATIO + 1 ) ,
	TN_LCI_AVIBACKUP_FILENAME_CHANGE_MESSAGE	= ( TN_LCI_APPLICATION_ID + 1 ) ,
	TN_LCI_AVIBACKUP_FILENAME_CHANGE_CAPTION	= ( TN_LCI_AVIBACKUP_FILENAME_CHANGE_MESSAGE + 1 ) ,
	TN_LCI_VIDEO_MEMORY_LIMIT	= ( TN_LCI_AVIBACKUP_FILENAME_CHANGE_CAPTION + 1 ) ,
	TN_LCI_DISPLAY_RESTRICTED_ON	= ( TN_LCI_VIDEO_MEMORY_LIMIT + 1 ) ,
	TN_LCI_DISPLAY_RESTRICTED_TEXT	= ( TN_LCI_DISPLAY_RESTRICTED_ON + 1 ) ,
	TN_LCI_DISPLAY_RESTRICTED_TEXT_BOX	= ( TN_LCI_DISPLAY_RESTRICTED_TEXT + 1 ) ,
	TN_LCI_DISPLAY_LIMIT_FRAMERATE	= ( TN_LCI_DISPLAY_RESTRICTED_TEXT_BOX + 1 ) ,
	TN_LCI_AUDIO_DISPLAY_POS	= ( TN_LCI_DISPLAY_LIMIT_FRAMERATE + 1 ) ,
	TN_LCI_DISPLAY_AUDIOLOSS_ON	= ( TN_LCI_AUDIO_DISPLAY_POS + 1 ) ,
	TN_LCI_DISPLAY_AUDIOLOSS_TEXT	= ( TN_LCI_DISPLAY_AUDIOLOSS_ON + 1 ) ,
	TN_LCI_WMVBACKUP_NODECODER_MESSAGE	= ( TN_LCI_DISPLAY_AUDIOLOSS_TEXT + 1 ) ,
	TN_LCI_WMVBACKUP_NODECODER_CAPTION	= ( TN_LCI_WMVBACKUP_NODECODER_MESSAGE + 1 ) ,
	TN_LCI_AUDIOLEVEL_SUPPORTED	= ( TN_LCI_WMVBACKUP_NODECODER_CAPTION + 1 ) ,
	TN_LCI_DECODINGTIME_SUPPORTED	= ( TN_LCI_AUDIOLEVEL_SUPPORTED + 1 ) ,
	TN_LCI_IFRAMEPLAYBACK_SUPPORTED	= ( TN_LCI_DECODINGTIME_SUPPORTED + 1 ) ,
	TN_LCI_GUID	= ( TN_LCI_IFRAMEPLAYBACK_SUPPORTED + 1 ) 
    } 	TN_LCI_TYPE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0002
    {	TN_SNC_NO_ERROR	= 0,
	TN_SNC_MEMORYLACK	= ( TN_SNC_NO_ERROR + 1 ) ,
	TN_SNC_CPUOVERLOAD	= ( TN_SNC_MEMORYLACK + 1 ) ,
	TN_SNC_CN_SERVER_UNREACHABLE	= 10,
	TN_SNC_CN_TOO_MANY_CONNECTION	= ( TN_SNC_CN_SERVER_UNREACHABLE + 1 ) ,
	TN_SNC_CN_PASSWORD_MISMATCH	= ( TN_SNC_CN_TOO_MANY_CONNECTION + 1 ) ,
	TN_SNC_CN_CONNECTION_DISABLED	= ( TN_SNC_CN_PASSWORD_MISMATCH + 1 ) ,
	TN_SNC_CN_ID_NOT_EXIST	= ( TN_SNC_CN_CONNECTION_DISABLED + 1 ) ,
	TN_SNC_CN_DOMAINNAME_UNKNOWN	= ( TN_SNC_CN_ID_NOT_EXIST + 1 ) ,
	TN_SNC_CN_PARAMETER_OUTOFRANGE	= ( TN_SNC_CN_DOMAINNAME_UNKNOWN + 1 ) ,
	TN_SNC_CN_DUPLICATE_CONNECT	= ( TN_SNC_CN_PARAMETER_OUTOFRANGE + 1 ) ,
	TN_SNC_CN_KEEPALIVE_FAILED	= ( TN_SNC_CN_DUPLICATE_CONNECT + 1 ) ,
	TN_SNC_CN_NO_AUTHORITY_OPERATION	= ( TN_SNC_CN_KEEPALIVE_FAILED + 1 ) ,
	TN_SNC_CN_OPERATION_FAILED	= ( TN_SNC_CN_NO_AUTHORITY_OPERATION + 1 ) ,
	TN_SNC_FAILED_INITIALIZE_DISPLAY	= ( TN_SNC_CN_OPERATION_FAILED + 1 ) ,
	TN_SNC_CN_INVALID_TCFID	= ( TN_SNC_FAILED_INITIALIZE_DISPLAY + 1 ) 
    } 	TN_SNC_TYPE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0003
    {	TN_RT_D1	= 0,
	TN_RT_CIF	= ( TN_RT_D1 + 1 ) ,
	TN_RT_HDF	= ( TN_RT_CIF + 1 ) ,
	TN_RT_2CIF	= ( TN_RT_HDF + 1 ) ,
	TN_RT_HALFD1	= ( TN_RT_2CIF + 1 ) ,
	TN_RT_XHDF	= ( TN_RT_HALFD1 + 1 ) 
    } 	TN_RT_TYPE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0004
    {	TN_MT_VIDEO	= 0,
	TN_MT_AUDIO	= ( TN_MT_VIDEO + 1 ) ,
	TN_MT_AUDIO_UP	= ( TN_MT_AUDIO + 1 ) 
    } 	TN_MT_TYPE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0005
    {	TN_MTC_UNKNOWN	= 0,
	TN_MTC_MPEG_1	= ( TN_MTC_UNKNOWN + 1 ) ,
	TN_MTC_MPEG_2	= ( TN_MTC_MPEG_1 + 1 ) ,
	TN_MTC_MPEG_4	= ( TN_MTC_MPEG_2 + 1 ) ,
	TN_MTC_JPEG	= ( TN_MTC_MPEG_4 + 1 ) ,
	TN_MTC_H_263	= ( TN_MTC_JPEG + 1 ) ,
	TN_MTC_H_264	= ( TN_MTC_H_263 + 1 ) ,
	TN_MTC_PCM	= ( TN_MTC_H_264 + 1 ) ,
	TN_MTC_G_711A	= ( TN_MTC_PCM + 1 ) ,
	TN_MTC_G_711U	= ( TN_MTC_G_711A + 1 ) ,
	TN_MTC_G_722	= ( TN_MTC_G_711U + 1 ) ,
	TN_MTC_G_723_1	= ( TN_MTC_G_722 + 1 ) ,
	TN_MTC_GSM	= ( TN_MTC_G_723_1 + 1 ) ,
	TN_MTC_SERIAL	= ( TN_MTC_GSM + 1 ) ,
	TN_MTC_MPEG1A2	= ( TN_MTC_SERIAL + 1 ) ,
	TN_MTC_MPEG1A3	= ( TN_MTC_MPEG1A2 + 1 ) ,
	TN_MTC_AAC	= ( TN_MTC_MPEG1A3 + 1 ) ,
	TN_MTC_RAW_YUV420	= 0x20,
	TN_MTC_RAW_YUV422	= ( TN_MTC_RAW_YUV420 + 1 ) ,
	TN_MTC_RAW_RGB32	= ( TN_MTC_RAW_YUV422 + 1 ) ,
	TN_MTC_RAW_RGB888	= ( TN_MTC_RAW_RGB32 + 1 ) 
    } 	TN_MTC_TYPE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0006
    {	TN_CS_CONNECTED	= 0x1,
	TN_CS_STREAMED	= 0x2,
	TN_CS_DECODED	= 0x4,
	TN_CS_DISPLAYED	= 0x8,
	TN_CS_RECORDED	= 0x10,
	TN_CS_TRY_CONNECT	= 0x20
    } 	TN_CS_TYPE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0007
    {	TN_ENCODED	= 0,
	TN_DECODED	= ( TN_ENCODED + 1 ) 
    } 	TN_FORMAT_TYPE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0008
    {	TN_LM_1X1	= 0,
	TN_LM_2X2	= ( TN_LM_1X1 + 1 ) ,
	TN_LM_3X3	= ( TN_LM_2X2 + 1 ) ,
	TN_LM_4X4	= ( TN_LM_3X3 + 1 ) ,
	TN_LM_1_12	= ( TN_LM_4X4 + 1 ) ,
	TN_LM_2_8	= ( TN_LM_1_12 + 1 ) ,
	TN_LM_1_5	= ( TN_LM_2_8 + 1 ) ,
	TN_LM_5X5	= ( TN_LM_1_5 + 1 ) ,
	TN_LM_6X6	= ( TN_LM_5X5 + 1 ) ,
	TN_LM_7X7	= ( TN_LM_6X6 + 1 ) ,
	TN_LM_8X8	= ( TN_LM_7X7 + 1 ) ,
	TN_LM_2X3	= ( TN_LM_8X8 + 1 ) ,
	TN_LM_ARBITRARY	= 0xff
    } 	TN_LM_MODE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0009
    {	TN_ET_DI	= 0,
	TN_ET_VIDEOLOSS	= ( TN_ET_DI + 1 ) ,
	TN_ET_MOTION	= ( TN_ET_VIDEOLOSS + 1 ) ,
	TN_ET_TIMECHANGED	= ( TN_ET_MOTION + 1 ) ,
	TN_ET_DO	= ( TN_ET_TIMECHANGED + 1 ) ,
	TN_ET_RECORD	= ( TN_ET_DO + 1 ) ,
	TN_ET_RESOLUTIONCHANGED	= ( TN_ET_RECORD + 1 ) ,
	TN_ET_AUDIO_SILENCE	= ( TN_ET_RESOLUTIONCHANGED + 1 ) ,
	TN_ET_IVS_EVENT	= ( TN_ET_AUDIO_SILENCE + 1 ) ,
	TN_ET_IVS_CONFIG_CHANGED	= ( TN_ET_IVS_EVENT + 1 ) 
    } 	TN_ET_TYPE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0010
    {	TN_ES_ERROR	= -1,
	TN_ES_OFF	= 0,
	TN_ES_ON	= 1
    } 	TN_ES_STATUS;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0011
    {	TN_PTZ_STOP	= 0,
	TN_PTZ_CONTINUE	= 0x1,
	TN_PTZ_LEFT	= 0x2,
	TN_PTZ_RIGHT	= 0x3,
	TN_PTZ_UP	= 0x4,
	TN_PTZ_DOWN	= 0x5,
	TN_PTZ_ZOOMIN	= 0x6,
	TN_PTZ_ZOOMOUT	= 0x7,
	TN_PTZ_FOCUSNEAR	= 0x8,
	TN_PTZ_FOCUSFAR	= 0x9,
	TN_PTZ_LEFTUP	= 0xa,
	TN_PTZ_LEFTDOWN	= 0xb,
	TN_PTZ_RIGHTUP	= 0xc,
	TN_PTZ_RIGHTDOWN	= 0xd,
	TN_PTZ_LIGHT_ON	= 0xe,
	TN_PTZ_LIGHT_OFF	= 0xf,
	TN_PTZ_POWER_ON	= 0x10,
	TN_PTZ_POWER_OFF	= 0x11,
	TN_PTZ_HOME	= 0x12,
	TN_PTZ_AUTOPANSTART	= 0x13,
	TN_PTZ_AUTOPANSTOP	= 0x14,
	TN_PTZ_IRISCLOSE	= 0x15,
	TN_PTZ_IRISOPEN	= 0x16,
	TN_PTZ_IRISAUTO	= 0x17,
	TN_PTZ_PATROLSTART	= 0x18,
	TN_PTZ_PATROLSTOP	= 0x19,
	TN_PTZ_CODE_WIPER_ON	= 0x1a,
	TN_PTZ_CODE_WIPER_OFF	= 0x1b,
	TN_PTZ_CODE_FOCUSAUTO	= 0x1c,
	TN_PTZ_CODE_MENU_ON	= 0x1d,
	TN_PTZ_CODE_MENU_OFF	= 0x1e,
	TN_PTZ_CODE_MENU_ENTER	= 0x1f,
	TN_PTZ_CODE_MENU_ESC	= 0x20,
	TN_PTZ_CODE_MENU_UP	= 0x60,
	TN_PTZ_CODE_MENU_DOWN	= 0x61,
	TN_PTZ_CODE_MENU_RIGHT	= 0x62,
	TN_PTZ_CODE_MENU_LEFT	= 0x63
    } 	TN_PTZ_CMD;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0012
    {	TN_OSD_TEXT	= 0,
	TN_OSD_BITMAP	= 1,
	TN_OSD_RECTANGLE	= 2,
	TN_OSD_EMPTY_RECTANGLE	= 3
    } 	TN_OSD_TYPE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0013
    {	TN_OSD_MODE_GDI	= 0,
	TN_OSD_MODE_D3D	= ( TN_OSD_MODE_GDI + 1 ) 
    } 	TN_OSD_MODE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0014
    {	TN_BTN_PLAYSTOP	= 0x1,
	TN_BTN_SNAPSHOT	= 0x2,
	TN_BTN_FULLSCREEN	= 0x4,
	TN_BTN_SPK_VOLUME	= 0x8,
	TN_BTN_MIC_VOLUME	= 0x10,
	TN_BTN_TALK	= 0x20,
	TN_BTN_MUTE	= 0x40,
	TN_BTN_RECORD	= 0x80,
	TN_BTN_ALL	= 0xffffffff
    } 	TN_TOOLBAR_BTN;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0015
    {	TN_ST_ENCODER	= 0,
	TN_ST_DECODER	= ( TN_ST_ENCODER + 1 ) ,
	TN_ST_DUPLEX	= ( TN_ST_DECODER + 1 ) ,
	TN_ST_DVR	= ( TN_ST_DUPLEX + 1 ) ,
	TN_ST_VIDEO_SERVER	= ( TN_ST_DVR + 1 ) ,
	TN_ST_CMS	= ( TN_ST_VIDEO_SERVER + 1 ) 
    } 	TN_SERVER_TYPE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0016
    {	TN_RM_720X480	= 0,
	TN_RM_720X240	= ( TN_RM_720X480 + 1 ) ,
	TN_RM_352X480	= ( TN_RM_720X240 + 1 ) ,
	TN_RM_352X240	= ( TN_RM_352X480 + 1 ) ,
	TN_RM_720x576	= ( TN_RM_352X240 + 1 ) ,
	TN_RM_720x288	= ( TN_RM_720x576 + 1 ) ,
	TN_RM_352x576	= ( TN_RM_720x288 + 1 ) ,
	TN_RM_352x288	= ( TN_RM_352x576 + 1 ) ,
	TN_RM_640x480	= ( TN_RM_352x288 + 1 ) ,
	TN_RM_800x600	= ( TN_RM_640x480 + 1 ) ,
	TN_RM_1024x768	= ( TN_RM_800x600 + 1 ) ,
	TN_RM_1280x960	= ( TN_RM_1024x768 + 1 ) ,
	TN_RM_1280x1024	= ( TN_RM_1280x960 + 1 ) ,
	TN_RM_1440x900	= ( TN_RM_1280x1024 + 1 ) ,
	TN_RM_1600x900	= ( TN_RM_1440x900 + 1 ) ,
	TN_RM_1680x1050	= ( TN_RM_1600x900 + 1 ) ,
	TN_RM_1280x720	= ( TN_RM_1680x1050 + 1 ) ,
	TN_RM_1920x1080	= ( TN_RM_1280x720 + 1 ) ,
	TN_RM_176x128	= ( TN_RM_1920x1080 + 1 ) ,
	TN_RM_176x144	= ( TN_RM_176x128 + 1 ) ,
	TN_RM_320X288	= ( TN_RM_176x144 + 1 ) ,
	TN_RM_360X288	= ( TN_RM_320X288 + 1 ) ,
	TN_RM_320X240	= ( TN_RM_360X288 + 1 ) ,
	TN_RM_2048X1536	= ( TN_RM_320X240 + 1 ) ,
	TN_RM_2560X1600	= ( TN_RM_2048X1536 + 1 ) ,
	TN_RM_2592X1936	= ( TN_RM_2560X1600 + 1 ) ,
	TN_RM_1920x1056	= ( TN_RM_2592X1936 + 1 ) ,
	TN_RM_640x360	= ( TN_RM_1920x1056 + 1 ) ,
	TN_RM_1440x540	= ( TN_RM_640x360 + 1 ) ,
	TN_RM_1792x1344	= ( TN_RM_1440x540 + 1 ) ,
	TN_RM_1440x1080	= ( TN_RM_1792x1344 + 1 ) ,
	TN_RM_160x90	= 31,
	TN_RM_160x100	= ( TN_RM_160x90 + 1 ) ,
	TN_RM_160x120	= ( TN_RM_160x100 + 1 ) ,
	TN_RM_180x120	= ( TN_RM_160x120 + 1 ) ,
	TN_RM_240x180	= ( TN_RM_180x120 + 1 ) ,
	TN_RM_320x180	= ( TN_RM_240x180 + 1 ) ,
	TN_RM_320x200	= ( TN_RM_320x180 + 1 ) ,
	TN_RM_360x244	= ( TN_RM_320x200 + 1 ) ,
	TN_RM_480x270	= ( TN_RM_360x244 + 1 ) ,
	TN_RM_480x300	= ( TN_RM_480x270 + 1 ) ,
	TN_RM_480x360	= ( TN_RM_480x300 + 1 ) ,
	TN_RM_640x400	= ( TN_RM_480x360 + 1 ) ,
	TN_RM_800x450	= ( TN_RM_640x400 + 1 ) ,
	TN_RM_800x500	= ( TN_RM_800x450 + 1 ) ,
	TN_RM_1024x640	= ( TN_RM_800x500 + 1 ) ,
	TN_RM_1280x800	= ( TN_RM_1024x640 + 1 ) ,
	TN_RM_1600x1200	= ( TN_RM_1280x800 + 1 ) ,
	TN_RM_1920x1200	= ( TN_RM_1600x1200 + 1 ) ,
	TN_RM_704X480	= ( TN_RM_1920x1200 + 1 ) ,
	TN_RM_3840x2160	= ( TN_RM_704X480 + 1 ) ,
	TN_RM_4096x2160	= ( TN_RM_3840x2160 + 1 ) ,
	TN_RM_4000x3000	= ( TN_RM_4096x2160 + 1 ) ,
	TN_RM_1280x768	= ( TN_RM_4000x3000 + 1 ) ,
	TN_RM_1152x864	= ( TN_RM_1280x768 + 1 ) ,
	TN_RM_1360x768	= ( TN_RM_1152x864 + 1 ) ,
	TN_RM_1400x1050	= ( TN_RM_1360x768 + 1 ) ,
	TN_RM_2048x2048	= ( TN_RM_1400x1050 + 1 ) ,
	TN_RM_FIRST	= TN_RM_720X480,
	TN_RM_LAST	= TN_RM_2048x2048
    } 	TN_RESOLUTION;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0017
    {	TN_FPS_30_25	= 0,
	TN_FPS_25_20	= ( TN_FPS_30_25 + 1 ) ,
	TN_FPS_20_16	= ( TN_FPS_25_20 + 1 ) ,
	TN_FPS_15_12	= ( TN_FPS_20_16 + 1 ) ,
	TN_FPS_10	= ( TN_FPS_15_12 + 1 ) ,
	TN_FPS_8	= ( TN_FPS_10 + 1 ) ,
	TN_FPS_6	= ( TN_FPS_8 + 1 ) ,
	TN_FPS_5	= ( TN_FPS_6 + 1 ) ,
	TN_FPS_4	= ( TN_FPS_5 + 1 ) ,
	TN_FPS_3	= ( TN_FPS_4 + 1 ) ,
	TN_FPS_2	= ( TN_FPS_3 + 1 ) ,
	TN_FPS_1	= ( TN_FPS_2 + 1 ) ,
	TN_FPS_06	= ( TN_FPS_1 + 1 ) ,
	TN_FPS_04	= ( TN_FPS_06 + 1 ) ,
	TN_FPS_02	= ( TN_FPS_04 + 1 ) 
    } 	TN_FRAMERATE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0018
    {	TN_REC_OFF	= 0,
	TN_REC_TIMELAPS	= 0x1,
	TN_REC_EVENT_SENSOR	= 0x4,
	TN_REC_EVENT_MOTION	= 0x8,
	TN_REC_EVENT_VIDEOLOSS	= 0x10
    } 	TN_RECORD_MODE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0019
    {	TN_NOTIFY_REC_ACTUAL_CHANGE	= 0,
	TN_NOTIFY_REC_MODE_CHANGE	= ( TN_NOTIFY_REC_ACTUAL_CHANGE + 1 ) ,
	TN_NOTIFY_REC_DISK_FULL	= ( TN_NOTIFY_REC_MODE_CHANGE + 1 ) ,
	TN_NOTIFY_REC_DISK_CHANGE	= ( TN_NOTIFY_REC_DISK_FULL + 1 ) ,
	TN_NOTIFY_REC_DISK_FORMATTING_PROGRESS	= ( TN_NOTIFY_REC_DISK_CHANGE + 1 ) ,
	TN_NOTIFY_REC_DISK_FORMAT_RESULT	= ( TN_NOTIFY_REC_DISK_FORMATTING_PROGRESS + 1 ) ,
	TN_NOTIFY_REC_DISK_FORMATTING_CANCEL	= ( TN_NOTIFY_REC_DISK_FORMAT_RESULT + 1 ) ,
	TN_NOTIFY_NO_DATA_REC	= ( TN_NOTIFY_REC_DISK_FORMATTING_CANCEL + 1 ) 
    } 	TN_RECORD_NOTIFY;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0020
    {	TN_FF_SIMPLE_FRAME	= 0,
	TN_FF_NOTIME	= 0x1,
	TN_FF_DISCONTINUITY	= 0x2,
	TN_FF_ENDOFSTREAM	= 0x4,
	TN_FF_KEYFRAME	= 0x200
    } 	TN_FRAME_FLAGS;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0021
    {	TN_RGN_OFF	= 0,
	TN_RGN_SET	= ( TN_RGN_OFF + 1 ) ,
	TN_RGN_ERASE	= ( TN_RGN_SET + 1 ) ,
	TN_RGN_APPLY	= ( TN_RGN_ERASE + 1 ) ,
	TN_RGN_ERASEALL	= ( TN_RGN_APPLY + 1 ) ,
	TN_RGN_SETALL	= ( TN_RGN_ERASEALL + 1 ) ,
	TN_RGN_SET2	= ( TN_RGN_SETALL + 1 ) ,
	TN_RGN_SET3	= ( TN_RGN_SET2 + 1 ) ,
	TN_RGN_SET3_APPLY	= ( TN_RGN_SET3 + 1 ) 
    } 	TN_MOTION_RGN;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0022
    {	TN_MVD_PAUSE	= 0,
	TN_MVD_KEYFRAME	= ( TN_MVD_PAUSE + 1 ) ,
	TN_MVD_LIVE	= ( TN_MVD_KEYFRAME + 1 ) 
    } 	TN_MOTION_VIDEO_MODE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0023
    {	TN_DISPLAY_OFF	= 0,
	TN_DISPLAY_LEFT	= 1,
	TN_DISPLAY_TOP	= 2,
	TN_DISPLAY_RIGHT	= 4,
	TN_DISPLAY_BOTTOM	= 8
    } 	TN_DISPLAY_POSITION;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0024
    {	TN_FILERECORD_START	= 0,
	TN_FILERECORD_STOP	= 1,
	TN_FILERECORD_VIDEO	= 0,
	TN_FILERECORD_VIDEO_AUDIO	= 1,
	TN_FILERECORD_SUBTITLES	= 2,
	TN_FILERECORD_SILENTMODE	= 0,
	TN_FILERECORD_ALERT	= 4
    } 	TN_FILERECORD_IOCTL;

typedef struct _BYTE_SIZEDARR_STM
    {
    ULONG cbSize;
    int eMediaType;
    int eDataFormat;
    int eDataResolution;
    int eFlags;
    ULONG pts;
    __int64 stime;
    int stride;
    unsigned long clSize;
    byte *pData;
    } 	BYTE_SIZEDARR_STM;

typedef struct _SERIAL_DATA
    {
    ULONG cbSize;
    unsigned long clSize;
    byte *pData;
    } 	SERIAL_DATA;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0025
    {	TN_DI_SENSOR_1	= 1,
	TN_DI_SENSOR_2	= 2
    } 	TN_DI_TYPE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0026
    {	TN_DO_BUZZER	= 0,
	TN_DO_RELAY_1	= 1,
	TN_DO_RELAY_2	= 2
    } 	TN_DO_TYPE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0027
    {	TN_COM_1	= 1,
	TN_COM_2	= 2
    } 	TN_COM_PORT;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0028
    {	TN_STAT_RECONNECT_COUNT	= 0,
	TN_STAT_VIDEO_BITRATE	= ( TN_STAT_RECONNECT_COUNT + 1 ) ,
	TN_STAT_VIDEO_FRAMERATE_DISPLAY	= ( TN_STAT_VIDEO_BITRATE + 1 ) ,
	TN_STAT_VIDEO_RESOLUTION	= ( TN_STAT_VIDEO_FRAMERATE_DISPLAY + 1 ) ,
	TN_STAT_AUDIO_BITRATE	= ( TN_STAT_VIDEO_RESOLUTION + 1 ) ,
	TN_STAT_VIDEO_FRAMERATE_RECORD	= ( TN_STAT_AUDIO_BITRATE + 1 ) ,
	TN_STAT_AUDIO_BACKWARD_LENGTH	= ( TN_STAT_VIDEO_FRAMERATE_RECORD + 1 ) ,
	TN_STAT_AUDIO_BACKWARD_CURPOS	= ( TN_STAT_AUDIO_BACKWARD_LENGTH + 1 ) 
    } 	TN_STAT_TYPE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0029
    {	TN_SC_VIDEO_BITRATE	= 0,
	TN_SC_VIDEO_FRAMERATE	= ( TN_SC_VIDEO_BITRATE + 1 ) ,
	TN_SC_VIDEO_RESOLUTION	= ( TN_SC_VIDEO_FRAMERATE + 1 ) ,
	TN_SC_VIDEO_BRIGHTNESS	= ( TN_SC_VIDEO_RESOLUTION + 1 ) ,
	TN_SC_VIDEO_CONTRAST	= ( TN_SC_VIDEO_BRIGHTNESS + 1 ) ,
	TN_SC_VIDEO_HUE	= ( TN_SC_VIDEO_CONTRAST + 1 ) ,
	TN_SC_VIDEO_SATURATION	= ( TN_SC_VIDEO_HUE + 1 ) ,
	TN_SC_VIDEO_RESOLUTION_SEC	= ( TN_SC_VIDEO_SATURATION + 1 ) ,
	TN_SC_VIDEO_STREAM	= ( TN_SC_VIDEO_RESOLUTION_SEC + 1 ) 
    } 	TN_SC_TYPE;

typedef struct tag_stConfig
    {
    int nItem;
    unsigned long cbSize;
    byte *pbData;
    } 	stConfig;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0030
    {	TN_PB_SPEED_R1X	= -1,
	TN_PB_SPEED_R2X	= -2,
	TN_PB_SPEED_R4X	= -4,
	TN_PB_SPEED_R8X	= -8,
	TN_PB_SPEED_R16X	= -16,
	TN_PB_SPEED_F1X	= 1,
	TN_PB_SPEED_F2X	= 2,
	TN_PB_SPEED_F4X	= 4,
	TN_PB_SPEED_F8X	= 8,
	TN_PB_SPEED_F16X	= 16
    } 	TN_PB_SPEED;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0031
    {	TN_PB_EVENT_SENSOR	= 0x4,
	TN_PB_EVENT_MOTION	= 0x8,
	TN_PB_EVENT_VIDEOLOSS	= 0x10
    } 	TN_PB_EVENT_TYPE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0032
    {	TN_PB_COMPRESSION_BMP	= 0,
	TN_PB_COMPRESSION_JPEG	= ( TN_PB_COMPRESSION_BMP + 1 ) 
    } 	TN_PB_COMPRESSION_TYPE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0033
    {	TN_PB_STATE_STOP	= 1,
	TN_PB_STATE_PAUSE	= ( TN_PB_STATE_STOP + 1 ) ,
	TN_PB_STATE_PLAY	= ( TN_PB_STATE_PAUSE + 1 ) 
    } 	TN_PB_STATES;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0034
    {	TN_PB_NOTIFY_ERROR	= 1,
	TN_PB_NOTIFY_ENDOFDATA	= ( TN_PB_NOTIFY_ERROR + 1 ) ,
	TN_PB_NOTIFY_STATECHANGED	= ( TN_PB_NOTIFY_ENDOFDATA + 1 ) ,
	TN_PB_NOTIFY_PLAYBACKTIME	= ( TN_PB_NOTIFY_STATECHANGED + 1 ) 
    } 	TN_PB_NOTIFY_CODES;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0035
    {	TN_RPB_LATENCY	= 0,
	TN_RPB_TIMEOUT	= ( TN_RPB_LATENCY + 1 ) ,
	TN_RPB_TZ	= ( TN_RPB_TIMEOUT + 1 ) ,
	TN_RPB_ENUM_CHNLS	= ( TN_RPB_TZ + 1 ) ,
	TN_RPB_CHNL_FPS	= ( TN_RPB_ENUM_CHNLS + 1 ) 
    } 	TN_RPB_CONFIG;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0036
    {	TN_PB_EX_STORAGE_FILE	= 0
    } 	TN_PB_EX_STORAGE_TYPE;

typedef struct tag_stVsnmCmd
    {
    int vCmd;
    unsigned long cbSize;
    byte *pbData;
    } 	stVsnmCmd;

typedef struct _matrix_ch
    {
    int switch_type;
    int switch_id;
    int switch_code;
    int switch_out;
    int switch2_type;
    int switch2_id;
    int switch2_code;
    int switch2_out;
    int ptz_type;
    int ptz_id;
    } 	matrix_ch_t;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0037
    {	TN_WAV_STOP	= 0,
	TN_WAV_START	= ( TN_WAV_STOP + 1 ) ,
	TN_WAV_FILE_NOT_FOUND	= ( TN_WAV_START + 1 ) ,
	TN_WAV_FILE_WRONG_FMT	= ( TN_WAV_FILE_NOT_FOUND + 1 ) ,
	TN_WAV_PROGRESS	= ( TN_WAV_FILE_WRONG_FMT + 1 ) 
    } 	TN_WAV_STATE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0038
    {	TN_DEC_DEINTERLACE	= 1,
	TN_DEC_SMP	= 2,
	TN_DEC_MAX_THREADS	= 3
    } 	TN_DEC_OPTION;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0039
    {	TN_DEINTERLACE_NONE	= 0,
	TN_DEINTERLACE_VERTICAL_SMOOTH	= 1,
	TN_DEINTERLACE_ONE_FIELD_INTERPOLATION	= 2,
	TN_DEINTERLACE_AUTO	= 4
    } 	TN_DEC_DEINTERLACE_VAL;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0040
    {	TN_OSD_NO_ALIGN	= 0,
	TN_OSD_CENTER	= 0x1,
	TN_OSD_TOP_LEFT	= 0x2,
	TN_OSD_BOTTOM_RIGHT	= 0x4
    } 	TN_OSD_ALIGN;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0041
    {	TN_ST_PRIMARY	= 1,
	TN_ST_SECONDARY_1	= ( TN_ST_PRIMARY + 1 ) ,
	TN_ST_SECONDARY_2	= ( TN_ST_SECONDARY_1 + 1 ) ,
	TN_ST_SECONDARY_3	= ( TN_ST_SECONDARY_2 + 1 ) 
    } 	TN_ST_TYPE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0042
    {	TN_TURN_OFF	= 0,
	TN_TURN_AXIS_X	= 1,
	TN_TURN_AXIS_Y	= 2,
	TN_TURN_AXIS_XY	= 3
    } 	TN_TURN_DIRECTION;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0043
    {	TN_SN_DISPLAY_RECONFIGURE_MEMORY	= 0
    } 	TN_SYSTEM_NOTIFY;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_TVS_0000_0000_0044
    {	TN_PVT_OFF	= 0,
	TN_PVT_SET	= ( TN_PVT_OFF + 1 ) ,
	TN_PVT_ERASE	= ( TN_PVT_SET + 1 ) ,
	TN_PVT_APPLY	= ( TN_PVT_ERASE + 1 ) 
    } 	TN_PVT_RGN;


#pragma pack()


extern RPC_IF_HANDLE __MIDL_itf_TVS_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_TVS_0000_0000_v0_0_s_ifspec;

#ifndef __ITVSLiveControl_INTERFACE_DEFINED__
#define __ITVSLiveControl_INTERFACE_DEFINED__

/* interface ITVSLiveControl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVSLiveControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EC99D4D7-15E4-49DB-97C2-80EB35FDB3EC")
    ITVSLiveControl : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDisplay( 
            /* [retval][out] */ ITVSDisplay **ppDisplay) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalConfig( 
            /* [in] */ long eItem,
            /* [retval][out] */ VARIANT *vValue) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LocalConfig( 
            /* [in] */ long eItem,
            /* [in] */ VARIANT vValue) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Protocol( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ BSTR *sProtocol) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Address( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ BSTR *sAddress) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Port( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ short *iPort) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LoginName( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ BSTR *sName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoIndex( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ short *nIndex) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioIndex( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ short *nIndex) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaType( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *lType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CameraName( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ BSTR *sName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsEnabled( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *lEnabled) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PTZtype( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *lType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AutoReconnect( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bReconnect) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AutoReconnect( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bReconnect) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConnectionTimeOut( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *lTimeout) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConnectionTimeOut( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lTimeout) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReconnectionWait( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *lWait) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReconnectionWait( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lWait) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IOReadWriteTimeOut( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ short *iTimeout) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IOReadWriteTimeOut( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ short iTimeout) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect( 
            /* [in] */ BSTR pAddress,
            /* [in] */ BSTR pLoginName,
            /* [in] */ BSTR pPassword,
            /* [retval][out] */ INT_PTR *lChID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Disconnect( 
            /* [in] */ INT_PTR lChID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Play( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Pause( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartTalking( 
            /* [in] */ INT_PTR lChID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopTalking( 
            /* [in] */ INT_PTR lChID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Snapshot( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lCompression,
            /* [in] */ VARIANT_BOOL bAutoSave) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PreviewSnapshot( 
            /* [in] */ INT_PTR lChID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveSnapshot( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lCompression,
            /* [in] */ BSTR pFilename) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartStreamDataEvent( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long eFormat) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopStreamDataEvent( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long eFormat) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDO( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ short nIndex,
            /* [in] */ long pValue,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDI( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ short nIndex,
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDO( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ short nIndex,
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMotion( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoLoss( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRecord( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendSerialData( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ short nIndex,
            /* [in] */ VARIANT vData,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendPTZCommand( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long eCmd,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPTZControlSpeed( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ short nType,
            /* [in] */ long lSpeed,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPTZPresetList( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT *pvData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPTZPreset( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT vPresetID,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPTZPosition( 
            /* [in] */ INT_PTR lChID,
            /* [out] */ long *plPan,
            /* [out] */ long *plTilt,
            /* [out] */ long *plZoom,
            /* [out] */ long *plFocus,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPTZPosition( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lPan,
            /* [in] */ long lTilt,
            /* [in] */ long lZoom,
            /* [in] */ long lFocus,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearPTZPreset( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT vPresetID,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GoToPTZPreset( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT vPresetID,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Deinterlacing( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bDeinterlace) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Deinterlacing( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bDeinterlace) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_KeepAspectRatio( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bAspect) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_KeepAspectRatio( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bAspect) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ViewKeyFrameOnly( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bKeyOnly) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ViewKeyFrameOnly( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bKeyOnly) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DecodeVisibleChannelOnly( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bVisible) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DecodeVisibleChannelOnly( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bVisible) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Statistics( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long eParam,
            /* [retval][out] */ VARIANT *vValue) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ServerConfig( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long eParam,
            /* [retval][out] */ VARIANT *vValue) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ServerConfig( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long eParam,
            /* [in] */ VARIANT vValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMotionRegionEdit( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lMode,
            /* [in] */ long lVideoMode,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConfigCameraModule( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lCode,
            /* [in] */ long lState,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ServerName( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ BSTR *sName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ServerName( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ BSTR sName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ServerType( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *eType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoChnls( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *cVideo) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioChnls( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *cAudio) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DIChnls( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *cDI) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DOChnls( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *cDO) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoCodec( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *eVideo) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioCodec( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *eAudio) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ServerTime( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *tTime) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ServerTimeZone( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *tZone) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LogEvent( 
            /* [retval][out] */ VARIANT_BOOL *bLog) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LogEvent( 
            /* [in] */ VARIANT_BOOL bLog) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StorageRecycle( 
            /* [retval][out] */ long *lRecycle) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StorageRecycle( 
            /* [in] */ long lRecycle) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PreEventTime( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *tPreEvent) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PreEventTime( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long tPreEvent) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PostEventTime( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *tPostEvent) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PostEventTime( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long tPostEvent) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AllocSize( 
            /* [in] */ BSTR pPath,
            /* [retval][out] */ VARIANT *vAlloc) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UsedSize( 
            /* [in] */ BSTR pPath,
            /* [retval][out] */ VARIANT *vUsed) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RecordDuration( 
            /* [in] */ BSTR pPath,
            /* [out] */ VARIANT *pvBegin,
            /* [out] */ VARIANT *pvEnd,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetStorageList( 
            /* [retval][out] */ VARIANT *pvData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AllocStorage( 
            /* [in] */ BSTR pPath,
            /* [in] */ long mbSize,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AllocStorageFast( 
            /* [in] */ BSTR pPath,
            /* [in] */ long mbSize,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CancelAllocStorage( 
            /* [in] */ BSTR pPath,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDiskList( 
            VARIANT *pvData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect2( 
            /* [in] */ BSTR pAddress,
            /* [in] */ BSTR pLoginName,
            /* [in] */ BSTR pPassword,
            /* [in] */ BSTR pSSAddress,
            /* [in] */ BSTR pSSLoginName,
            /* [in] */ BSTR pSSPassword,
            /* [retval][out] */ INT_PTR *lChID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoOn( 
            INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoOn( 
            INT_PTR lChID,
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FreeStorage( 
            /* [in] */ BSTR pPath,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddStorage( 
            /* [in] */ BSTR pPath,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DropStorage( 
            /* [in] */ BSTR pPath,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FreeRecordPeriod( 
            /* [in] */ BSTR pPath,
            /* [in] */ VARIANT vBegin,
            /* [in] */ VARIANT vEnd,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Formatting( 
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FormatResult( 
            /* [retval][out] */ VARIANT *vResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetServerConfig( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ int cItems,
            /* [size_is][in] */ stConfig *vItems,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetServerConfig( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ int cItems,
            /* [size_is][out][in] */ stConfig *vItems,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEventForChannelRecord( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long eEventType,
            /* [out] */ long *pEventMap,
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEventForChannelRecord( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long eEventType,
            /* [in] */ long lEventMap,
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RecordingMode( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *eMode) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RecordingMode( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long eMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartRecord( 
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopRecord( 
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Recording( 
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartFileRecord( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lFlags,
            /* [in] */ BSTR pPath,
            /* [retval][out] */ long *phrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopFileRecord( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ChannelState( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *lState) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMute( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bMute) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMute( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bMuted) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RecordingOrder( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lOrder) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendVSNMCommand( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ stVsnmCmd *vCmd,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PlayWaveToServer( 
            INT_PTR lChID,
            BSTR pPath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopWaveToServer( 
            INT_PTR lChID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartOnScreenPTZ( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopOnScreenPTZ( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOsdRectangle( 
            INT_PTR lChID,
            long lColor,
            long lWidth,
            long lOffset) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveOsdRectangle( 
            INT_PTR lChID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DecodingOption( 
            /* [in] */ long param,
            /* [retval][out] */ long *value) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DecodingOption( 
            /* [in] */ long param,
            /* [in] */ long value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSnapshot( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lCompression,
            /* [in] */ long xWidth,
            /* [in] */ long yHeight,
            /* [out] */ VARIANT *data,
            /* [out] */ long *size) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RenamePTZPreset( 
            INT_PTR lChID,
            VARIANT vPresetID,
            BSTR pName,
            VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddIVSFilter( 
            /* [in] */ INT_PTR lChID,
            IUnknown **ppIVSFlt) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveIVSFilter( 
            /* [in] */ INT_PTR lChID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetIVSFilter( 
            /* [in] */ INT_PTR lChID,
            IUnknown **ppIVSFlt) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartIVSProcess( 
            /* [in] */ INT_PTR lChID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopIVSProcess( 
            /* [in] */ INT_PTR lChID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPTZPosition2( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lPan,
            /* [in] */ long lTilt,
            /* [in] */ long lZoom,
            /* [in] */ long lFocus,
            /* [in] */ long lMode,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StreamType( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetLocalConfig( 
            /* [in] */ long eItem,
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLocalConfig( 
            /* [in] */ long eItem,
            /* [retval][out] */ VARIANT *vValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSnapshotAspectRatio( 
            /* [in] */ long nAspect) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAutoReconnect( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bReconnect) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAutoReconnect( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bReconnect) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDecodingOption( 
            /* [in] */ long param,
            /* [in] */ long value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDecodingOption( 
            /* [in] */ long param,
            /* [retval][out] */ long *value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindLocation( 
            /* [in] */ BSTR begin,
            /* [retval][out] */ BSTR *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTiltPosition( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RunElevatedWeb( 
            /* [in] */ BSTR szURL) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NeedElevation( 
            /* [retval][out] */ long *value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearPTZPresetString( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT vPresetID,
            /* [in] */ BSTR strName,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GoToPTZPresetString( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT vPresetID,
            /* [in] */ BSTR strName,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPTZPresetString( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT vPresetID,
            /* [in] */ BSTR strName,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMotionRegionEdit2( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lRegion,
            /* [in] */ long lMode,
            /* [in] */ long lVideoMode,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPrivacyRegionEdit( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lRegion,
            /* [in] */ long lMode,
            /* [in] */ long lVideoMode,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFullScreen( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long mode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFullScreen( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *mode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDecoder( 
            /* [in] */ DWORD decoder) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDecoder( 
            /* [retval][out] */ DWORD *decoder) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAvailableDecoders( 
            /* [retval][out] */ DWORD *decoders) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSoftMute( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bMute) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioOn( 
            INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AudioOn( 
            INT_PTR lChID,
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetScaleEnable( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lMode,
            /* [in] */ long lID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetScaleEdit( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lID,
            /* [in] */ long lStartX,
            /* [in] */ long lStartY,
            /* [in] */ long lWidth,
            /* [in] */ long lHeight,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetScaleX( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lID,
            /* [retval][out] */ long *lVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetScaleY( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lID,
            /* [retval][out] */ long *lVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetScaleWidth( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lID,
            /* [retval][out] */ long *lVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetScaleHeight( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lID,
            /* [retval][out] */ long *lVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetIVSControl( 
            /* [retval][out] */ ITVSIVSControl **ppIVSControl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCropEnable( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lMode,
            /* [in] */ long lID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCropEdit( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lID,
            /* [in] */ long lStartX,
            /* [in] */ long lStartY,
            /* [in] */ long lWidth,
            /* [in] */ long lHeight,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCropX( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lID,
            /* [retval][out] */ long *lVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCropY( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lID,
            /* [retval][out] */ long *lVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCropWidth( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lID,
            /* [retval][out] */ long *lVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCropHeight( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lID,
            /* [retval][out] */ long *lVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StatShowTrigger( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVSLiveControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVSLiveControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVSLiveControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVSLiveControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVSLiveControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVSLiveControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVSLiveControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVSLiveControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDisplay )( 
            ITVSLiveControl * This,
            /* [retval][out] */ ITVSDisplay **ppDisplay);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LocalConfig )( 
            ITVSLiveControl * This,
            /* [in] */ long eItem,
            /* [retval][out] */ VARIANT *vValue);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LocalConfig )( 
            ITVSLiveControl * This,
            /* [in] */ long eItem,
            /* [in] */ VARIANT vValue);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Protocol )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ BSTR *sProtocol);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Address )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ BSTR *sAddress);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Port )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ short *iPort);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoginName )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ BSTR *sName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoIndex )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ short *nIndex);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudioIndex )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ short *nIndex);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaType )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *lType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CameraName )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ BSTR *sName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsEnabled )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *lEnabled);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PTZtype )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *lType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AutoReconnect )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bReconnect);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AutoReconnect )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bReconnect);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConnectionTimeOut )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *lTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ConnectionTimeOut )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lTimeout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ReconnectionWait )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *lWait);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReconnectionWait )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lWait);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IOReadWriteTimeOut )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ short *iTimeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IOReadWriteTimeOut )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ short iTimeout);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Connect )( 
            ITVSLiveControl * This,
            /* [in] */ BSTR pAddress,
            /* [in] */ BSTR pLoginName,
            /* [in] */ BSTR pPassword,
            /* [retval][out] */ INT_PTR *lChID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Play )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Pause )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartTalking )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopTalking )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Snapshot )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lCompression,
            /* [in] */ VARIANT_BOOL bAutoSave);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PreviewSnapshot )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveSnapshot )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lCompression,
            /* [in] */ BSTR pFilename);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartStreamDataEvent )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long eFormat);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopStreamDataEvent )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long eFormat);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDO )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ short nIndex,
            /* [in] */ long pValue,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDI )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ short nIndex,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDO )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ short nIndex,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMotion )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoLoss )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRecord )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SendSerialData )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ short nIndex,
            /* [in] */ VARIANT vData,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SendPTZCommand )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long eCmd,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPTZControlSpeed )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ short nType,
            /* [in] */ long lSpeed,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPTZPresetList )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT *pvData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPTZPreset )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT vPresetID,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPTZPosition )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [out] */ long *plPan,
            /* [out] */ long *plTilt,
            /* [out] */ long *plZoom,
            /* [out] */ long *plFocus,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPTZPosition )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lPan,
            /* [in] */ long lTilt,
            /* [in] */ long lZoom,
            /* [in] */ long lFocus,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClearPTZPreset )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT vPresetID,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GoToPTZPreset )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT vPresetID,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Deinterlacing )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bDeinterlace);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Deinterlacing )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bDeinterlace);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_KeepAspectRatio )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bAspect);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_KeepAspectRatio )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bAspect);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ViewKeyFrameOnly )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bKeyOnly);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ViewKeyFrameOnly )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bKeyOnly);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DecodeVisibleChannelOnly )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bVisible);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DecodeVisibleChannelOnly )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bVisible);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Statistics )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long eParam,
            /* [retval][out] */ VARIANT *vValue);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ServerConfig )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long eParam,
            /* [retval][out] */ VARIANT *vValue);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ServerConfig )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long eParam,
            /* [in] */ VARIANT vValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMotionRegionEdit )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lMode,
            /* [in] */ long lVideoMode,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConfigCameraModule )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lCode,
            /* [in] */ long lState,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ServerName )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ BSTR *sName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ServerName )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ BSTR sName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ServerType )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *eType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoChnls )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *cVideo);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudioChnls )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *cAudio);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DIChnls )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *cDI);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DOChnls )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *cDO);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoCodec )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *eVideo);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudioCodec )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *eAudio);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ServerTime )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *tTime);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ServerTimeZone )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *tZone);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LogEvent )( 
            ITVSLiveControl * This,
            /* [retval][out] */ VARIANT_BOOL *bLog);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LogEvent )( 
            ITVSLiveControl * This,
            /* [in] */ VARIANT_BOOL bLog);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StorageRecycle )( 
            ITVSLiveControl * This,
            /* [retval][out] */ long *lRecycle);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StorageRecycle )( 
            ITVSLiveControl * This,
            /* [in] */ long lRecycle);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PreEventTime )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *tPreEvent);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PreEventTime )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long tPreEvent);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PostEventTime )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *tPostEvent);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PostEventTime )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long tPostEvent);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AllocSize )( 
            ITVSLiveControl * This,
            /* [in] */ BSTR pPath,
            /* [retval][out] */ VARIANT *vAlloc);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UsedSize )( 
            ITVSLiveControl * This,
            /* [in] */ BSTR pPath,
            /* [retval][out] */ VARIANT *vUsed);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RecordDuration )( 
            ITVSLiveControl * This,
            /* [in] */ BSTR pPath,
            /* [out] */ VARIANT *pvBegin,
            /* [out] */ VARIANT *pvEnd,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetStorageList )( 
            ITVSLiveControl * This,
            /* [retval][out] */ VARIANT *pvData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AllocStorage )( 
            ITVSLiveControl * This,
            /* [in] */ BSTR pPath,
            /* [in] */ long mbSize,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AllocStorageFast )( 
            ITVSLiveControl * This,
            /* [in] */ BSTR pPath,
            /* [in] */ long mbSize,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CancelAllocStorage )( 
            ITVSLiveControl * This,
            /* [in] */ BSTR pPath,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDiskList )( 
            ITVSLiveControl * This,
            VARIANT *pvData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Connect2 )( 
            ITVSLiveControl * This,
            /* [in] */ BSTR pAddress,
            /* [in] */ BSTR pLoginName,
            /* [in] */ BSTR pPassword,
            /* [in] */ BSTR pSSAddress,
            /* [in] */ BSTR pSSLoginName,
            /* [in] */ BSTR pSSPassword,
            /* [retval][out] */ INT_PTR *lChID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoOn )( 
            ITVSLiveControl * This,
            INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VideoOn )( 
            ITVSLiveControl * This,
            INT_PTR lChID,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FreeStorage )( 
            ITVSLiveControl * This,
            /* [in] */ BSTR pPath,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddStorage )( 
            ITVSLiveControl * This,
            /* [in] */ BSTR pPath,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DropStorage )( 
            ITVSLiveControl * This,
            /* [in] */ BSTR pPath,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FreeRecordPeriod )( 
            ITVSLiveControl * This,
            /* [in] */ BSTR pPath,
            /* [in] */ VARIANT vBegin,
            /* [in] */ VARIANT vEnd,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Formatting )( 
            ITVSLiveControl * This,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FormatResult )( 
            ITVSLiveControl * This,
            /* [retval][out] */ VARIANT *vResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetServerConfig )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ int cItems,
            /* [size_is][in] */ stConfig *vItems,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetServerConfig )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ int cItems,
            /* [size_is][out][in] */ stConfig *vItems,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEventForChannelRecord )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long eEventType,
            /* [out] */ long *pEventMap,
            /* [retval][out] */ long *lResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEventForChannelRecord )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long eEventType,
            /* [in] */ long lEventMap,
            /* [retval][out] */ long *lResult);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RecordingMode )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *eMode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RecordingMode )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long eMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartRecord )( 
            ITVSLiveControl * This,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopRecord )( 
            ITVSLiveControl * This,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Recording )( 
            ITVSLiveControl * This,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartFileRecord )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lFlags,
            /* [in] */ BSTR pPath,
            /* [retval][out] */ long *phrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopFileRecord )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ChannelState )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *lState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMute )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bMute);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMute )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bMuted);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RecordingOrder )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lOrder);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SendVSNMCommand )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ stVsnmCmd *vCmd,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PlayWaveToServer )( 
            ITVSLiveControl * This,
            INT_PTR lChID,
            BSTR pPath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopWaveToServer )( 
            ITVSLiveControl * This,
            INT_PTR lChID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartOnScreenPTZ )( 
            ITVSLiveControl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopOnScreenPTZ )( 
            ITVSLiveControl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetOsdRectangle )( 
            ITVSLiveControl * This,
            INT_PTR lChID,
            long lColor,
            long lWidth,
            long lOffset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveOsdRectangle )( 
            ITVSLiveControl * This,
            INT_PTR lChID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DecodingOption )( 
            ITVSLiveControl * This,
            /* [in] */ long param,
            /* [retval][out] */ long *value);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DecodingOption )( 
            ITVSLiveControl * This,
            /* [in] */ long param,
            /* [in] */ long value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSnapshot )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lCompression,
            /* [in] */ long xWidth,
            /* [in] */ long yHeight,
            /* [out] */ VARIANT *data,
            /* [out] */ long *size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RenamePTZPreset )( 
            ITVSLiveControl * This,
            INT_PTR lChID,
            VARIANT vPresetID,
            BSTR pName,
            VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddIVSFilter )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            IUnknown **ppIVSFlt);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveIVSFilter )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetIVSFilter )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            IUnknown **ppIVSFlt);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartIVSProcess )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopIVSProcess )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPTZPosition2 )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lPan,
            /* [in] */ long lTilt,
            /* [in] */ long lZoom,
            /* [in] */ long lFocus,
            /* [in] */ long lMode,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StreamType )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ short *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetLocalConfig )( 
            ITVSLiveControl * This,
            /* [in] */ long eItem,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLocalConfig )( 
            ITVSLiveControl * This,
            /* [in] */ long eItem,
            /* [retval][out] */ VARIANT *vValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSnapshotAspectRatio )( 
            ITVSLiveControl * This,
            /* [in] */ long nAspect);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAutoReconnect )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bReconnect);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAutoReconnect )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bReconnect);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDecodingOption )( 
            ITVSLiveControl * This,
            /* [in] */ long param,
            /* [in] */ long value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDecodingOption )( 
            ITVSLiveControl * This,
            /* [in] */ long param,
            /* [retval][out] */ long *value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindLocation )( 
            ITVSLiveControl * This,
            /* [in] */ BSTR begin,
            /* [retval][out] */ BSTR *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTiltPosition )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RunElevatedWeb )( 
            ITVSLiveControl * This,
            /* [in] */ BSTR szURL);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NeedElevation )( 
            ITVSLiveControl * This,
            /* [retval][out] */ long *value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClearPTZPresetString )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT vPresetID,
            /* [in] */ BSTR strName,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GoToPTZPresetString )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT vPresetID,
            /* [in] */ BSTR strName,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPTZPresetString )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT vPresetID,
            /* [in] */ BSTR strName,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMotionRegionEdit2 )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lRegion,
            /* [in] */ long lMode,
            /* [in] */ long lVideoMode,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPrivacyRegionEdit )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lRegion,
            /* [in] */ long lMode,
            /* [in] */ long lVideoMode,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetFullScreen )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long mode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFullScreen )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *mode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDecoder )( 
            ITVSLiveControl * This,
            /* [in] */ DWORD decoder);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDecoder )( 
            ITVSLiveControl * This,
            /* [retval][out] */ DWORD *decoder);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAvailableDecoders )( 
            ITVSLiveControl * This,
            /* [retval][out] */ DWORD *decoders);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSoftMute )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bMute);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudioOn )( 
            ITVSLiveControl * This,
            INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AudioOn )( 
            ITVSLiveControl * This,
            INT_PTR lChID,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetScaleEnable )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lMode,
            /* [in] */ long lID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetScaleEdit )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lID,
            /* [in] */ long lStartX,
            /* [in] */ long lStartY,
            /* [in] */ long lWidth,
            /* [in] */ long lHeight,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetScaleX )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lID,
            /* [retval][out] */ long *lVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetScaleY )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lID,
            /* [retval][out] */ long *lVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetScaleWidth )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lID,
            /* [retval][out] */ long *lVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetScaleHeight )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lID,
            /* [retval][out] */ long *lVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetIVSControl )( 
            ITVSLiveControl * This,
            /* [retval][out] */ ITVSIVSControl **ppIVSControl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCropEnable )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lMode,
            /* [in] */ long lID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCropEdit )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lID,
            /* [in] */ long lStartX,
            /* [in] */ long lStartY,
            /* [in] */ long lWidth,
            /* [in] */ long lHeight,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCropX )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lID,
            /* [retval][out] */ long *lVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCropY )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lID,
            /* [retval][out] */ long *lVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCropWidth )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lID,
            /* [retval][out] */ long *lVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCropHeight )( 
            ITVSLiveControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lID,
            /* [retval][out] */ long *lVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StatShowTrigger )( 
            ITVSLiveControl * This);
        
        END_INTERFACE
    } ITVSLiveControlVtbl;

    interface ITVSLiveControl
    {
        CONST_VTBL struct ITVSLiveControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVSLiveControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITVSLiveControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITVSLiveControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITVSLiveControl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITVSLiveControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITVSLiveControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITVSLiveControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ITVSLiveControl_GetDisplay(This,ppDisplay)	\
    ( (This)->lpVtbl -> GetDisplay(This,ppDisplay) ) 

#define ITVSLiveControl_get_LocalConfig(This,eItem,vValue)	\
    ( (This)->lpVtbl -> get_LocalConfig(This,eItem,vValue) ) 

#define ITVSLiveControl_put_LocalConfig(This,eItem,vValue)	\
    ( (This)->lpVtbl -> put_LocalConfig(This,eItem,vValue) ) 

#define ITVSLiveControl_get_Protocol(This,lChID,sProtocol)	\
    ( (This)->lpVtbl -> get_Protocol(This,lChID,sProtocol) ) 

#define ITVSLiveControl_get_Address(This,lChID,sAddress)	\
    ( (This)->lpVtbl -> get_Address(This,lChID,sAddress) ) 

#define ITVSLiveControl_get_Port(This,lChID,iPort)	\
    ( (This)->lpVtbl -> get_Port(This,lChID,iPort) ) 

#define ITVSLiveControl_get_LoginName(This,lChID,sName)	\
    ( (This)->lpVtbl -> get_LoginName(This,lChID,sName) ) 

#define ITVSLiveControl_get_VideoIndex(This,lChID,nIndex)	\
    ( (This)->lpVtbl -> get_VideoIndex(This,lChID,nIndex) ) 

#define ITVSLiveControl_get_AudioIndex(This,lChID,nIndex)	\
    ( (This)->lpVtbl -> get_AudioIndex(This,lChID,nIndex) ) 

#define ITVSLiveControl_get_MediaType(This,lChID,lType)	\
    ( (This)->lpVtbl -> get_MediaType(This,lChID,lType) ) 

#define ITVSLiveControl_get_CameraName(This,lChID,sName)	\
    ( (This)->lpVtbl -> get_CameraName(This,lChID,sName) ) 

#define ITVSLiveControl_get_IsEnabled(This,lChID,lEnabled)	\
    ( (This)->lpVtbl -> get_IsEnabled(This,lChID,lEnabled) ) 

#define ITVSLiveControl_get_PTZtype(This,lChID,lType)	\
    ( (This)->lpVtbl -> get_PTZtype(This,lChID,lType) ) 

#define ITVSLiveControl_get_AutoReconnect(This,lChID,bReconnect)	\
    ( (This)->lpVtbl -> get_AutoReconnect(This,lChID,bReconnect) ) 

#define ITVSLiveControl_put_AutoReconnect(This,lChID,bReconnect)	\
    ( (This)->lpVtbl -> put_AutoReconnect(This,lChID,bReconnect) ) 

#define ITVSLiveControl_get_ConnectionTimeOut(This,lChID,lTimeout)	\
    ( (This)->lpVtbl -> get_ConnectionTimeOut(This,lChID,lTimeout) ) 

#define ITVSLiveControl_put_ConnectionTimeOut(This,lChID,lTimeout)	\
    ( (This)->lpVtbl -> put_ConnectionTimeOut(This,lChID,lTimeout) ) 

#define ITVSLiveControl_get_ReconnectionWait(This,lChID,lWait)	\
    ( (This)->lpVtbl -> get_ReconnectionWait(This,lChID,lWait) ) 

#define ITVSLiveControl_put_ReconnectionWait(This,lChID,lWait)	\
    ( (This)->lpVtbl -> put_ReconnectionWait(This,lChID,lWait) ) 

#define ITVSLiveControl_get_IOReadWriteTimeOut(This,lChID,iTimeout)	\
    ( (This)->lpVtbl -> get_IOReadWriteTimeOut(This,lChID,iTimeout) ) 

#define ITVSLiveControl_put_IOReadWriteTimeOut(This,lChID,iTimeout)	\
    ( (This)->lpVtbl -> put_IOReadWriteTimeOut(This,lChID,iTimeout) ) 

#define ITVSLiveControl_Connect(This,pAddress,pLoginName,pPassword,lChID)	\
    ( (This)->lpVtbl -> Connect(This,pAddress,pLoginName,pPassword,lChID) ) 

#define ITVSLiveControl_Disconnect(This,lChID)	\
    ( (This)->lpVtbl -> Disconnect(This,lChID) ) 

#define ITVSLiveControl_Play(This,lChID,bResult)	\
    ( (This)->lpVtbl -> Play(This,lChID,bResult) ) 

#define ITVSLiveControl_Pause(This,lChID,bResult)	\
    ( (This)->lpVtbl -> Pause(This,lChID,bResult) ) 

#define ITVSLiveControl_StartTalking(This,lChID)	\
    ( (This)->lpVtbl -> StartTalking(This,lChID) ) 

#define ITVSLiveControl_StopTalking(This,lChID)	\
    ( (This)->lpVtbl -> StopTalking(This,lChID) ) 

#define ITVSLiveControl_Snapshot(This,lChID,lCompression,bAutoSave)	\
    ( (This)->lpVtbl -> Snapshot(This,lChID,lCompression,bAutoSave) ) 

#define ITVSLiveControl_PreviewSnapshot(This,lChID)	\
    ( (This)->lpVtbl -> PreviewSnapshot(This,lChID) ) 

#define ITVSLiveControl_SaveSnapshot(This,lChID,lCompression,pFilename)	\
    ( (This)->lpVtbl -> SaveSnapshot(This,lChID,lCompression,pFilename) ) 

#define ITVSLiveControl_StartStreamDataEvent(This,lChID,eFormat)	\
    ( (This)->lpVtbl -> StartStreamDataEvent(This,lChID,eFormat) ) 

#define ITVSLiveControl_StopStreamDataEvent(This,lChID,eFormat)	\
    ( (This)->lpVtbl -> StopStreamDataEvent(This,lChID,eFormat) ) 

#define ITVSLiveControl_SetDO(This,lChID,nIndex,pValue,bResult)	\
    ( (This)->lpVtbl -> SetDO(This,lChID,nIndex,pValue,bResult) ) 

#define ITVSLiveControl_GetDI(This,lChID,nIndex,pVal)	\
    ( (This)->lpVtbl -> GetDI(This,lChID,nIndex,pVal) ) 

#define ITVSLiveControl_GetDO(This,lChID,nIndex,pVal)	\
    ( (This)->lpVtbl -> GetDO(This,lChID,nIndex,pVal) ) 

#define ITVSLiveControl_GetMotion(This,lChID,pVal)	\
    ( (This)->lpVtbl -> GetMotion(This,lChID,pVal) ) 

#define ITVSLiveControl_GetVideoLoss(This,lChID,pVal)	\
    ( (This)->lpVtbl -> GetVideoLoss(This,lChID,pVal) ) 

#define ITVSLiveControl_GetRecord(This,lChID,pVal)	\
    ( (This)->lpVtbl -> GetRecord(This,lChID,pVal) ) 

#define ITVSLiveControl_SendSerialData(This,lChID,nIndex,vData,bResult)	\
    ( (This)->lpVtbl -> SendSerialData(This,lChID,nIndex,vData,bResult) ) 

#define ITVSLiveControl_SendPTZCommand(This,lChID,eCmd,bResult)	\
    ( (This)->lpVtbl -> SendPTZCommand(This,lChID,eCmd,bResult) ) 

#define ITVSLiveControl_SetPTZControlSpeed(This,lChID,nType,lSpeed,bResult)	\
    ( (This)->lpVtbl -> SetPTZControlSpeed(This,lChID,nType,lSpeed,bResult) ) 

#define ITVSLiveControl_GetPTZPresetList(This,lChID,pvData)	\
    ( (This)->lpVtbl -> GetPTZPresetList(This,lChID,pvData) ) 

#define ITVSLiveControl_SetPTZPreset(This,lChID,vPresetID,bResult)	\
    ( (This)->lpVtbl -> SetPTZPreset(This,lChID,vPresetID,bResult) ) 

#define ITVSLiveControl_GetPTZPosition(This,lChID,plPan,plTilt,plZoom,plFocus,bResult)	\
    ( (This)->lpVtbl -> GetPTZPosition(This,lChID,plPan,plTilt,plZoom,plFocus,bResult) ) 

#define ITVSLiveControl_SetPTZPosition(This,lChID,lPan,lTilt,lZoom,lFocus,bResult)	\
    ( (This)->lpVtbl -> SetPTZPosition(This,lChID,lPan,lTilt,lZoom,lFocus,bResult) ) 

#define ITVSLiveControl_ClearPTZPreset(This,lChID,vPresetID,bResult)	\
    ( (This)->lpVtbl -> ClearPTZPreset(This,lChID,vPresetID,bResult) ) 

#define ITVSLiveControl_GoToPTZPreset(This,lChID,vPresetID,bResult)	\
    ( (This)->lpVtbl -> GoToPTZPreset(This,lChID,vPresetID,bResult) ) 

#define ITVSLiveControl_get_Deinterlacing(This,lChID,bDeinterlace)	\
    ( (This)->lpVtbl -> get_Deinterlacing(This,lChID,bDeinterlace) ) 

#define ITVSLiveControl_put_Deinterlacing(This,lChID,bDeinterlace)	\
    ( (This)->lpVtbl -> put_Deinterlacing(This,lChID,bDeinterlace) ) 

#define ITVSLiveControl_get_KeepAspectRatio(This,lChID,bAspect)	\
    ( (This)->lpVtbl -> get_KeepAspectRatio(This,lChID,bAspect) ) 

#define ITVSLiveControl_put_KeepAspectRatio(This,lChID,bAspect)	\
    ( (This)->lpVtbl -> put_KeepAspectRatio(This,lChID,bAspect) ) 

#define ITVSLiveControl_get_ViewKeyFrameOnly(This,lChID,bKeyOnly)	\
    ( (This)->lpVtbl -> get_ViewKeyFrameOnly(This,lChID,bKeyOnly) ) 

#define ITVSLiveControl_put_ViewKeyFrameOnly(This,lChID,bKeyOnly)	\
    ( (This)->lpVtbl -> put_ViewKeyFrameOnly(This,lChID,bKeyOnly) ) 

#define ITVSLiveControl_get_DecodeVisibleChannelOnly(This,lChID,bVisible)	\
    ( (This)->lpVtbl -> get_DecodeVisibleChannelOnly(This,lChID,bVisible) ) 

#define ITVSLiveControl_put_DecodeVisibleChannelOnly(This,lChID,bVisible)	\
    ( (This)->lpVtbl -> put_DecodeVisibleChannelOnly(This,lChID,bVisible) ) 

#define ITVSLiveControl_get_Statistics(This,lChID,eParam,vValue)	\
    ( (This)->lpVtbl -> get_Statistics(This,lChID,eParam,vValue) ) 

#define ITVSLiveControl_get_ServerConfig(This,lChID,eParam,vValue)	\
    ( (This)->lpVtbl -> get_ServerConfig(This,lChID,eParam,vValue) ) 

#define ITVSLiveControl_put_ServerConfig(This,lChID,eParam,vValue)	\
    ( (This)->lpVtbl -> put_ServerConfig(This,lChID,eParam,vValue) ) 

#define ITVSLiveControl_SetMotionRegionEdit(This,lChID,lMode,lVideoMode,pVal)	\
    ( (This)->lpVtbl -> SetMotionRegionEdit(This,lChID,lMode,lVideoMode,pVal) ) 

#define ITVSLiveControl_ConfigCameraModule(This,lChID,lCode,lState,pVal)	\
    ( (This)->lpVtbl -> ConfigCameraModule(This,lChID,lCode,lState,pVal) ) 

#define ITVSLiveControl_get_ServerName(This,lChID,sName)	\
    ( (This)->lpVtbl -> get_ServerName(This,lChID,sName) ) 

#define ITVSLiveControl_put_ServerName(This,lChID,sName)	\
    ( (This)->lpVtbl -> put_ServerName(This,lChID,sName) ) 

#define ITVSLiveControl_get_ServerType(This,lChID,eType)	\
    ( (This)->lpVtbl -> get_ServerType(This,lChID,eType) ) 

#define ITVSLiveControl_get_VideoChnls(This,lChID,cVideo)	\
    ( (This)->lpVtbl -> get_VideoChnls(This,lChID,cVideo) ) 

#define ITVSLiveControl_get_AudioChnls(This,lChID,cAudio)	\
    ( (This)->lpVtbl -> get_AudioChnls(This,lChID,cAudio) ) 

#define ITVSLiveControl_get_DIChnls(This,lChID,cDI)	\
    ( (This)->lpVtbl -> get_DIChnls(This,lChID,cDI) ) 

#define ITVSLiveControl_get_DOChnls(This,lChID,cDO)	\
    ( (This)->lpVtbl -> get_DOChnls(This,lChID,cDO) ) 

#define ITVSLiveControl_get_VideoCodec(This,lChID,eVideo)	\
    ( (This)->lpVtbl -> get_VideoCodec(This,lChID,eVideo) ) 

#define ITVSLiveControl_get_AudioCodec(This,lChID,eAudio)	\
    ( (This)->lpVtbl -> get_AudioCodec(This,lChID,eAudio) ) 

#define ITVSLiveControl_get_ServerTime(This,lChID,tTime)	\
    ( (This)->lpVtbl -> get_ServerTime(This,lChID,tTime) ) 

#define ITVSLiveControl_get_ServerTimeZone(This,lChID,tZone)	\
    ( (This)->lpVtbl -> get_ServerTimeZone(This,lChID,tZone) ) 

#define ITVSLiveControl_get_LogEvent(This,bLog)	\
    ( (This)->lpVtbl -> get_LogEvent(This,bLog) ) 

#define ITVSLiveControl_put_LogEvent(This,bLog)	\
    ( (This)->lpVtbl -> put_LogEvent(This,bLog) ) 

#define ITVSLiveControl_get_StorageRecycle(This,lRecycle)	\
    ( (This)->lpVtbl -> get_StorageRecycle(This,lRecycle) ) 

#define ITVSLiveControl_put_StorageRecycle(This,lRecycle)	\
    ( (This)->lpVtbl -> put_StorageRecycle(This,lRecycle) ) 

#define ITVSLiveControl_get_PreEventTime(This,lChID,tPreEvent)	\
    ( (This)->lpVtbl -> get_PreEventTime(This,lChID,tPreEvent) ) 

#define ITVSLiveControl_put_PreEventTime(This,lChID,tPreEvent)	\
    ( (This)->lpVtbl -> put_PreEventTime(This,lChID,tPreEvent) ) 

#define ITVSLiveControl_get_PostEventTime(This,lChID,tPostEvent)	\
    ( (This)->lpVtbl -> get_PostEventTime(This,lChID,tPostEvent) ) 

#define ITVSLiveControl_put_PostEventTime(This,lChID,tPostEvent)	\
    ( (This)->lpVtbl -> put_PostEventTime(This,lChID,tPostEvent) ) 

#define ITVSLiveControl_get_AllocSize(This,pPath,vAlloc)	\
    ( (This)->lpVtbl -> get_AllocSize(This,pPath,vAlloc) ) 

#define ITVSLiveControl_get_UsedSize(This,pPath,vUsed)	\
    ( (This)->lpVtbl -> get_UsedSize(This,pPath,vUsed) ) 

#define ITVSLiveControl_RecordDuration(This,pPath,pvBegin,pvEnd,bResult)	\
    ( (This)->lpVtbl -> RecordDuration(This,pPath,pvBegin,pvEnd,bResult) ) 

#define ITVSLiveControl_GetStorageList(This,pvData)	\
    ( (This)->lpVtbl -> GetStorageList(This,pvData) ) 

#define ITVSLiveControl_AllocStorage(This,pPath,mbSize,bResult)	\
    ( (This)->lpVtbl -> AllocStorage(This,pPath,mbSize,bResult) ) 

#define ITVSLiveControl_AllocStorageFast(This,pPath,mbSize,bResult)	\
    ( (This)->lpVtbl -> AllocStorageFast(This,pPath,mbSize,bResult) ) 

#define ITVSLiveControl_CancelAllocStorage(This,pPath,bResult)	\
    ( (This)->lpVtbl -> CancelAllocStorage(This,pPath,bResult) ) 

#define ITVSLiveControl_GetDiskList(This,pvData)	\
    ( (This)->lpVtbl -> GetDiskList(This,pvData) ) 

#define ITVSLiveControl_Connect2(This,pAddress,pLoginName,pPassword,pSSAddress,pSSLoginName,pSSPassword,lChID)	\
    ( (This)->lpVtbl -> Connect2(This,pAddress,pLoginName,pPassword,pSSAddress,pSSLoginName,pSSPassword,lChID) ) 

#define ITVSLiveControl_get_VideoOn(This,lChID,pVal)	\
    ( (This)->lpVtbl -> get_VideoOn(This,lChID,pVal) ) 

#define ITVSLiveControl_put_VideoOn(This,lChID,newVal)	\
    ( (This)->lpVtbl -> put_VideoOn(This,lChID,newVal) ) 

#define ITVSLiveControl_FreeStorage(This,pPath,bResult)	\
    ( (This)->lpVtbl -> FreeStorage(This,pPath,bResult) ) 

#define ITVSLiveControl_AddStorage(This,pPath,bResult)	\
    ( (This)->lpVtbl -> AddStorage(This,pPath,bResult) ) 

#define ITVSLiveControl_DropStorage(This,pPath,bResult)	\
    ( (This)->lpVtbl -> DropStorage(This,pPath,bResult) ) 

#define ITVSLiveControl_FreeRecordPeriod(This,pPath,vBegin,vEnd,bResult)	\
    ( (This)->lpVtbl -> FreeRecordPeriod(This,pPath,vBegin,vEnd,bResult) ) 

#define ITVSLiveControl_get_Formatting(This,bResult)	\
    ( (This)->lpVtbl -> get_Formatting(This,bResult) ) 

#define ITVSLiveControl_get_FormatResult(This,vResult)	\
    ( (This)->lpVtbl -> get_FormatResult(This,vResult) ) 

#define ITVSLiveControl_SetServerConfig(This,lChID,cItems,vItems,bResult)	\
    ( (This)->lpVtbl -> SetServerConfig(This,lChID,cItems,vItems,bResult) ) 

#define ITVSLiveControl_GetServerConfig(This,lChID,cItems,vItems,bResult)	\
    ( (This)->lpVtbl -> GetServerConfig(This,lChID,cItems,vItems,bResult) ) 

#define ITVSLiveControl_GetEventForChannelRecord(This,lChID,eEventType,pEventMap,lResult)	\
    ( (This)->lpVtbl -> GetEventForChannelRecord(This,lChID,eEventType,pEventMap,lResult) ) 

#define ITVSLiveControl_SetEventForChannelRecord(This,lChID,eEventType,lEventMap,lResult)	\
    ( (This)->lpVtbl -> SetEventForChannelRecord(This,lChID,eEventType,lEventMap,lResult) ) 

#define ITVSLiveControl_get_RecordingMode(This,lChID,eMode)	\
    ( (This)->lpVtbl -> get_RecordingMode(This,lChID,eMode) ) 

#define ITVSLiveControl_put_RecordingMode(This,lChID,eMode)	\
    ( (This)->lpVtbl -> put_RecordingMode(This,lChID,eMode) ) 

#define ITVSLiveControl_StartRecord(This,bResult)	\
    ( (This)->lpVtbl -> StartRecord(This,bResult) ) 

#define ITVSLiveControl_StopRecord(This,bResult)	\
    ( (This)->lpVtbl -> StopRecord(This,bResult) ) 

#define ITVSLiveControl_get_Recording(This,bResult)	\
    ( (This)->lpVtbl -> get_Recording(This,bResult) ) 

#define ITVSLiveControl_StartFileRecord(This,lChID,lFlags,pPath,phrResult)	\
    ( (This)->lpVtbl -> StartFileRecord(This,lChID,lFlags,pPath,phrResult) ) 

#define ITVSLiveControl_StopFileRecord(This,lChID,bResult)	\
    ( (This)->lpVtbl -> StopFileRecord(This,lChID,bResult) ) 

#define ITVSLiveControl_get_ChannelState(This,lChID,lState)	\
    ( (This)->lpVtbl -> get_ChannelState(This,lChID,lState) ) 

#define ITVSLiveControl_SetMute(This,lChID,bMute)	\
    ( (This)->lpVtbl -> SetMute(This,lChID,bMute) ) 

#define ITVSLiveControl_GetMute(This,lChID,bMuted)	\
    ( (This)->lpVtbl -> GetMute(This,lChID,bMuted) ) 

#define ITVSLiveControl_put_RecordingOrder(This,lChID,lOrder)	\
    ( (This)->lpVtbl -> put_RecordingOrder(This,lChID,lOrder) ) 

#define ITVSLiveControl_SendVSNMCommand(This,lChID,vCmd,bResult)	\
    ( (This)->lpVtbl -> SendVSNMCommand(This,lChID,vCmd,bResult) ) 

#define ITVSLiveControl_PlayWaveToServer(This,lChID,pPath)	\
    ( (This)->lpVtbl -> PlayWaveToServer(This,lChID,pPath) ) 

#define ITVSLiveControl_StopWaveToServer(This,lChID)	\
    ( (This)->lpVtbl -> StopWaveToServer(This,lChID) ) 

#define ITVSLiveControl_StartOnScreenPTZ(This)	\
    ( (This)->lpVtbl -> StartOnScreenPTZ(This) ) 

#define ITVSLiveControl_StopOnScreenPTZ(This)	\
    ( (This)->lpVtbl -> StopOnScreenPTZ(This) ) 

#define ITVSLiveControl_SetOsdRectangle(This,lChID,lColor,lWidth,lOffset)	\
    ( (This)->lpVtbl -> SetOsdRectangle(This,lChID,lColor,lWidth,lOffset) ) 

#define ITVSLiveControl_RemoveOsdRectangle(This,lChID)	\
    ( (This)->lpVtbl -> RemoveOsdRectangle(This,lChID) ) 

#define ITVSLiveControl_get_DecodingOption(This,param,value)	\
    ( (This)->lpVtbl -> get_DecodingOption(This,param,value) ) 

#define ITVSLiveControl_put_DecodingOption(This,param,value)	\
    ( (This)->lpVtbl -> put_DecodingOption(This,param,value) ) 

#define ITVSLiveControl_GetSnapshot(This,lChID,lCompression,xWidth,yHeight,data,size)	\
    ( (This)->lpVtbl -> GetSnapshot(This,lChID,lCompression,xWidth,yHeight,data,size) ) 

#define ITVSLiveControl_RenamePTZPreset(This,lChID,vPresetID,pName,pVal)	\
    ( (This)->lpVtbl -> RenamePTZPreset(This,lChID,vPresetID,pName,pVal) ) 

#define ITVSLiveControl_AddIVSFilter(This,lChID,ppIVSFlt)	\
    ( (This)->lpVtbl -> AddIVSFilter(This,lChID,ppIVSFlt) ) 

#define ITVSLiveControl_RemoveIVSFilter(This,lChID)	\
    ( (This)->lpVtbl -> RemoveIVSFilter(This,lChID) ) 

#define ITVSLiveControl_GetIVSFilter(This,lChID,ppIVSFlt)	\
    ( (This)->lpVtbl -> GetIVSFilter(This,lChID,ppIVSFlt) ) 

#define ITVSLiveControl_StartIVSProcess(This,lChID)	\
    ( (This)->lpVtbl -> StartIVSProcess(This,lChID) ) 

#define ITVSLiveControl_StopIVSProcess(This,lChID)	\
    ( (This)->lpVtbl -> StopIVSProcess(This,lChID) ) 

#define ITVSLiveControl_SetPTZPosition2(This,lChID,lPan,lTilt,lZoom,lFocus,lMode,bResult)	\
    ( (This)->lpVtbl -> SetPTZPosition2(This,lChID,lPan,lTilt,lZoom,lFocus,lMode,bResult) ) 

#define ITVSLiveControl_get_StreamType(This,lChID,pVal)	\
    ( (This)->lpVtbl -> get_StreamType(This,lChID,pVal) ) 

#define ITVSLiveControl_SetLocalConfig(This,eItem,newVal)	\
    ( (This)->lpVtbl -> SetLocalConfig(This,eItem,newVal) ) 

#define ITVSLiveControl_GetLocalConfig(This,eItem,vValue)	\
    ( (This)->lpVtbl -> GetLocalConfig(This,eItem,vValue) ) 

#define ITVSLiveControl_SetSnapshotAspectRatio(This,nAspect)	\
    ( (This)->lpVtbl -> SetSnapshotAspectRatio(This,nAspect) ) 

#define ITVSLiveControl_SetAutoReconnect(This,lChID,bReconnect)	\
    ( (This)->lpVtbl -> SetAutoReconnect(This,lChID,bReconnect) ) 

#define ITVSLiveControl_GetAutoReconnect(This,lChID,bReconnect)	\
    ( (This)->lpVtbl -> GetAutoReconnect(This,lChID,bReconnect) ) 

#define ITVSLiveControl_SetDecodingOption(This,param,value)	\
    ( (This)->lpVtbl -> SetDecodingOption(This,param,value) ) 

#define ITVSLiveControl_GetDecodingOption(This,param,value)	\
    ( (This)->lpVtbl -> GetDecodingOption(This,param,value) ) 

#define ITVSLiveControl_FindLocation(This,begin,bResult)	\
    ( (This)->lpVtbl -> FindLocation(This,begin,bResult) ) 

#define ITVSLiveControl_GetTiltPosition(This,lChID,value)	\
    ( (This)->lpVtbl -> GetTiltPosition(This,lChID,value) ) 

#define ITVSLiveControl_RunElevatedWeb(This,szURL)	\
    ( (This)->lpVtbl -> RunElevatedWeb(This,szURL) ) 

#define ITVSLiveControl_NeedElevation(This,value)	\
    ( (This)->lpVtbl -> NeedElevation(This,value) ) 

#define ITVSLiveControl_ClearPTZPresetString(This,lChID,vPresetID,strName,bResult)	\
    ( (This)->lpVtbl -> ClearPTZPresetString(This,lChID,vPresetID,strName,bResult) ) 

#define ITVSLiveControl_GoToPTZPresetString(This,lChID,vPresetID,strName,bResult)	\
    ( (This)->lpVtbl -> GoToPTZPresetString(This,lChID,vPresetID,strName,bResult) ) 

#define ITVSLiveControl_SetPTZPresetString(This,lChID,vPresetID,strName,pVal)	\
    ( (This)->lpVtbl -> SetPTZPresetString(This,lChID,vPresetID,strName,pVal) ) 

#define ITVSLiveControl_SetMotionRegionEdit2(This,lChID,lRegion,lMode,lVideoMode,pVal)	\
    ( (This)->lpVtbl -> SetMotionRegionEdit2(This,lChID,lRegion,lMode,lVideoMode,pVal) ) 

#define ITVSLiveControl_SetPrivacyRegionEdit(This,lChID,lRegion,lMode,lVideoMode,pVal)	\
    ( (This)->lpVtbl -> SetPrivacyRegionEdit(This,lChID,lRegion,lMode,lVideoMode,pVal) ) 

#define ITVSLiveControl_SetFullScreen(This,lChID,mode)	\
    ( (This)->lpVtbl -> SetFullScreen(This,lChID,mode) ) 

#define ITVSLiveControl_GetFullScreen(This,lChID,mode)	\
    ( (This)->lpVtbl -> GetFullScreen(This,lChID,mode) ) 

#define ITVSLiveControl_SetDecoder(This,decoder)	\
    ( (This)->lpVtbl -> SetDecoder(This,decoder) ) 

#define ITVSLiveControl_GetDecoder(This,decoder)	\
    ( (This)->lpVtbl -> GetDecoder(This,decoder) ) 

#define ITVSLiveControl_GetAvailableDecoders(This,decoders)	\
    ( (This)->lpVtbl -> GetAvailableDecoders(This,decoders) ) 

#define ITVSLiveControl_SetSoftMute(This,lChID,bMute)	\
    ( (This)->lpVtbl -> SetSoftMute(This,lChID,bMute) ) 

#define ITVSLiveControl_get_AudioOn(This,lChID,pVal)	\
    ( (This)->lpVtbl -> get_AudioOn(This,lChID,pVal) ) 

#define ITVSLiveControl_put_AudioOn(This,lChID,newVal)	\
    ( (This)->lpVtbl -> put_AudioOn(This,lChID,newVal) ) 

#define ITVSLiveControl_SetScaleEnable(This,lChID,lMode,lID)	\
    ( (This)->lpVtbl -> SetScaleEnable(This,lChID,lMode,lID) ) 

#define ITVSLiveControl_SetScaleEdit(This,lChID,lID,lStartX,lStartY,lWidth,lHeight,pVal)	\
    ( (This)->lpVtbl -> SetScaleEdit(This,lChID,lID,lStartX,lStartY,lWidth,lHeight,pVal) ) 

#define ITVSLiveControl_GetScaleX(This,lChID,lID,lVal)	\
    ( (This)->lpVtbl -> GetScaleX(This,lChID,lID,lVal) ) 

#define ITVSLiveControl_GetScaleY(This,lChID,lID,lVal)	\
    ( (This)->lpVtbl -> GetScaleY(This,lChID,lID,lVal) ) 

#define ITVSLiveControl_GetScaleWidth(This,lChID,lID,lVal)	\
    ( (This)->lpVtbl -> GetScaleWidth(This,lChID,lID,lVal) ) 

#define ITVSLiveControl_GetScaleHeight(This,lChID,lID,lVal)	\
    ( (This)->lpVtbl -> GetScaleHeight(This,lChID,lID,lVal) ) 

#define ITVSLiveControl_GetIVSControl(This,ppIVSControl)	\
    ( (This)->lpVtbl -> GetIVSControl(This,ppIVSControl) ) 

#define ITVSLiveControl_SetCropEnable(This,lChID,lMode,lID)	\
    ( (This)->lpVtbl -> SetCropEnable(This,lChID,lMode,lID) ) 

#define ITVSLiveControl_SetCropEdit(This,lChID,lID,lStartX,lStartY,lWidth,lHeight,pVal)	\
    ( (This)->lpVtbl -> SetCropEdit(This,lChID,lID,lStartX,lStartY,lWidth,lHeight,pVal) ) 

#define ITVSLiveControl_GetCropX(This,lChID,lID,lVal)	\
    ( (This)->lpVtbl -> GetCropX(This,lChID,lID,lVal) ) 

#define ITVSLiveControl_GetCropY(This,lChID,lID,lVal)	\
    ( (This)->lpVtbl -> GetCropY(This,lChID,lID,lVal) ) 

#define ITVSLiveControl_GetCropWidth(This,lChID,lID,lVal)	\
    ( (This)->lpVtbl -> GetCropWidth(This,lChID,lID,lVal) ) 

#define ITVSLiveControl_GetCropHeight(This,lChID,lID,lVal)	\
    ( (This)->lpVtbl -> GetCropHeight(This,lChID,lID,lVal) ) 

#define ITVSLiveControl_StatShowTrigger(This)	\
    ( (This)->lpVtbl -> StatShowTrigger(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_RenamePTZPreset_Proxy( 
    ITVSLiveControl * This,
    INT_PTR lChID,
    VARIANT vPresetID,
    BSTR pName,
    VARIANT_BOOL *pVal);


void __RPC_STUB ITVSLiveControl_RenamePTZPreset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_AddIVSFilter_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    IUnknown **ppIVSFlt);


void __RPC_STUB ITVSLiveControl_AddIVSFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_RemoveIVSFilter_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID);


void __RPC_STUB ITVSLiveControl_RemoveIVSFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_GetIVSFilter_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    IUnknown **ppIVSFlt);


void __RPC_STUB ITVSLiveControl_GetIVSFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_StartIVSProcess_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID);


void __RPC_STUB ITVSLiveControl_StartIVSProcess_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_StopIVSProcess_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID);


void __RPC_STUB ITVSLiveControl_StopIVSProcess_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_SetPTZPosition2_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [in] */ long lPan,
    /* [in] */ long lTilt,
    /* [in] */ long lZoom,
    /* [in] */ long lFocus,
    /* [in] */ long lMode,
    /* [retval][out] */ VARIANT_BOOL *bResult);


void __RPC_STUB ITVSLiveControl_SetPTZPosition2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_get_StreamType_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [retval][out] */ short *pVal);


void __RPC_STUB ITVSLiveControl_get_StreamType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_SetLocalConfig_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ long eItem,
    /* [in] */ VARIANT newVal);


void __RPC_STUB ITVSLiveControl_SetLocalConfig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_GetLocalConfig_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ long eItem,
    /* [retval][out] */ VARIANT *vValue);


void __RPC_STUB ITVSLiveControl_GetLocalConfig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_SetSnapshotAspectRatio_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ long nAspect);


void __RPC_STUB ITVSLiveControl_SetSnapshotAspectRatio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_SetAutoReconnect_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [in] */ VARIANT_BOOL bReconnect);


void __RPC_STUB ITVSLiveControl_SetAutoReconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_GetAutoReconnect_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [retval][out] */ VARIANT_BOOL *bReconnect);


void __RPC_STUB ITVSLiveControl_GetAutoReconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_SetDecodingOption_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ long param,
    /* [in] */ long value);


void __RPC_STUB ITVSLiveControl_SetDecodingOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_GetDecodingOption_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ long param,
    /* [retval][out] */ long *value);


void __RPC_STUB ITVSLiveControl_GetDecodingOption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_FindLocation_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ BSTR begin,
    /* [retval][out] */ BSTR *bResult);


void __RPC_STUB ITVSLiveControl_FindLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_GetTiltPosition_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [retval][out] */ long *value);


void __RPC_STUB ITVSLiveControl_GetTiltPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_RunElevatedWeb_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ BSTR szURL);


void __RPC_STUB ITVSLiveControl_RunElevatedWeb_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_NeedElevation_Proxy( 
    ITVSLiveControl * This,
    /* [retval][out] */ long *value);


void __RPC_STUB ITVSLiveControl_NeedElevation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_ClearPTZPresetString_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [in] */ VARIANT vPresetID,
    /* [in] */ BSTR strName,
    /* [retval][out] */ VARIANT_BOOL *bResult);


void __RPC_STUB ITVSLiveControl_ClearPTZPresetString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_GoToPTZPresetString_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [in] */ VARIANT vPresetID,
    /* [in] */ BSTR strName,
    /* [retval][out] */ VARIANT_BOOL *bResult);


void __RPC_STUB ITVSLiveControl_GoToPTZPresetString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_SetPTZPresetString_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [in] */ VARIANT vPresetID,
    /* [in] */ BSTR strName,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITVSLiveControl_SetPTZPresetString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_SetMotionRegionEdit2_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [in] */ long lRegion,
    /* [in] */ long lMode,
    /* [in] */ long lVideoMode,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITVSLiveControl_SetMotionRegionEdit2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_SetPrivacyRegionEdit_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [in] */ long lRegion,
    /* [in] */ long lMode,
    /* [in] */ long lVideoMode,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITVSLiveControl_SetPrivacyRegionEdit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_SetFullScreen_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [in] */ long mode);


void __RPC_STUB ITVSLiveControl_SetFullScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_GetFullScreen_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [retval][out] */ long *mode);


void __RPC_STUB ITVSLiveControl_GetFullScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_SetDecoder_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ DWORD decoder);


void __RPC_STUB ITVSLiveControl_SetDecoder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_GetDecoder_Proxy( 
    ITVSLiveControl * This,
    /* [retval][out] */ DWORD *decoder);


void __RPC_STUB ITVSLiveControl_GetDecoder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_GetAvailableDecoders_Proxy( 
    ITVSLiveControl * This,
    /* [retval][out] */ DWORD *decoders);


void __RPC_STUB ITVSLiveControl_GetAvailableDecoders_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_SetSoftMute_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [in] */ VARIANT_BOOL bMute);


void __RPC_STUB ITVSLiveControl_SetSoftMute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_get_AudioOn_Proxy( 
    ITVSLiveControl * This,
    INT_PTR lChID,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITVSLiveControl_get_AudioOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_put_AudioOn_Proxy( 
    ITVSLiveControl * This,
    INT_PTR lChID,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ITVSLiveControl_put_AudioOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_SetScaleEnable_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [in] */ long lMode,
    /* [in] */ long lID);


void __RPC_STUB ITVSLiveControl_SetScaleEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_SetScaleEdit_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [in] */ long lID,
    /* [in] */ long lStartX,
    /* [in] */ long lStartY,
    /* [in] */ long lWidth,
    /* [in] */ long lHeight,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITVSLiveControl_SetScaleEdit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_GetScaleX_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [in] */ long lID,
    /* [retval][out] */ long *lVal);


void __RPC_STUB ITVSLiveControl_GetScaleX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_GetScaleY_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [in] */ long lID,
    /* [retval][out] */ long *lVal);


void __RPC_STUB ITVSLiveControl_GetScaleY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_GetScaleWidth_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [in] */ long lID,
    /* [retval][out] */ long *lVal);


void __RPC_STUB ITVSLiveControl_GetScaleWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_GetScaleHeight_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [in] */ long lID,
    /* [retval][out] */ long *lVal);


void __RPC_STUB ITVSLiveControl_GetScaleHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_GetIVSControl_Proxy( 
    ITVSLiveControl * This,
    /* [retval][out] */ ITVSIVSControl **ppIVSControl);


void __RPC_STUB ITVSLiveControl_GetIVSControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_SetCropEnable_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [in] */ long lMode,
    /* [in] */ long lID);


void __RPC_STUB ITVSLiveControl_SetCropEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_SetCropEdit_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [in] */ long lID,
    /* [in] */ long lStartX,
    /* [in] */ long lStartY,
    /* [in] */ long lWidth,
    /* [in] */ long lHeight,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITVSLiveControl_SetCropEdit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_GetCropX_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [in] */ long lID,
    /* [retval][out] */ long *lVal);


void __RPC_STUB ITVSLiveControl_GetCropX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_GetCropY_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [in] */ long lID,
    /* [retval][out] */ long *lVal);


void __RPC_STUB ITVSLiveControl_GetCropY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_GetCropWidth_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [in] */ long lID,
    /* [retval][out] */ long *lVal);


void __RPC_STUB ITVSLiveControl_GetCropWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_GetCropHeight_Proxy( 
    ITVSLiveControl * This,
    /* [in] */ INT_PTR lChID,
    /* [in] */ long lID,
    /* [retval][out] */ long *lVal);


void __RPC_STUB ITVSLiveControl_GetCropHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITVSLiveControl_StatShowTrigger_Proxy( 
    ITVSLiveControl * This);


void __RPC_STUB ITVSLiveControl_StatShowTrigger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITVSLiveControl_INTERFACE_DEFINED__ */


#ifndef __ITVSDecodeControl_INTERFACE_DEFINED__
#define __ITVSDecodeControl_INTERFACE_DEFINED__

/* interface ITVSDecodeControl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVSDecodeControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7154F7B1-FD89-43a5-850F-6731A1CE93F3")
    ITVSDecodeControl : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDisplay( 
            /* [retval][out] */ ITVSDisplay **ppDisplay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ VARIANT_BOOL bDisplay,
            /* [in] */ VARIANT_BOOL bEvent,
            /* [in] */ IUnknown *pCallback,
            /* [retval][out] */ INT_PTR *lChID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PutData( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT vData,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartDecoding( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopDecoding( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOutputFormat( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ int eDataFormat,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DecodingOption( 
            /* [in] */ long param,
            /* [retval][out] */ long *value) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DecodingOption( 
            /* [in] */ long param,
            /* [in] */ long value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVSDecodeControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVSDecodeControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVSDecodeControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVSDecodeControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVSDecodeControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVSDecodeControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVSDecodeControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVSDecodeControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDisplay )( 
            ITVSDecodeControl * This,
            /* [retval][out] */ ITVSDisplay **ppDisplay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Open )( 
            ITVSDecodeControl * This,
            /* [in] */ VARIANT_BOOL bDisplay,
            /* [in] */ VARIANT_BOOL bEvent,
            /* [in] */ IUnknown *pCallback,
            /* [retval][out] */ INT_PTR *lChID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            ITVSDecodeControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PutData )( 
            ITVSDecodeControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT vData,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartDecoding )( 
            ITVSDecodeControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopDecoding )( 
            ITVSDecodeControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetOutputFormat )( 
            ITVSDecodeControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ int eDataFormat,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DecodingOption )( 
            ITVSDecodeControl * This,
            /* [in] */ long param,
            /* [retval][out] */ long *value);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DecodingOption )( 
            ITVSDecodeControl * This,
            /* [in] */ long param,
            /* [in] */ long value);
        
        END_INTERFACE
    } ITVSDecodeControlVtbl;

    interface ITVSDecodeControl
    {
        CONST_VTBL struct ITVSDecodeControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVSDecodeControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITVSDecodeControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITVSDecodeControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITVSDecodeControl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITVSDecodeControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITVSDecodeControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITVSDecodeControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ITVSDecodeControl_GetDisplay(This,ppDisplay)	\
    ( (This)->lpVtbl -> GetDisplay(This,ppDisplay) ) 

#define ITVSDecodeControl_Open(This,bDisplay,bEvent,pCallback,lChID)	\
    ( (This)->lpVtbl -> Open(This,bDisplay,bEvent,pCallback,lChID) ) 

#define ITVSDecodeControl_Close(This,lChID,bResult)	\
    ( (This)->lpVtbl -> Close(This,lChID,bResult) ) 

#define ITVSDecodeControl_PutData(This,lChID,vData,bResult)	\
    ( (This)->lpVtbl -> PutData(This,lChID,vData,bResult) ) 

#define ITVSDecodeControl_StartDecoding(This,lChID,bResult)	\
    ( (This)->lpVtbl -> StartDecoding(This,lChID,bResult) ) 

#define ITVSDecodeControl_StopDecoding(This,lChID,bResult)	\
    ( (This)->lpVtbl -> StopDecoding(This,lChID,bResult) ) 

#define ITVSDecodeControl_SetOutputFormat(This,lChID,eDataFormat,bResult)	\
    ( (This)->lpVtbl -> SetOutputFormat(This,lChID,eDataFormat,bResult) ) 

#define ITVSDecodeControl_get_DecodingOption(This,param,value)	\
    ( (This)->lpVtbl -> get_DecodingOption(This,param,value) ) 

#define ITVSDecodeControl_put_DecodingOption(This,param,value)	\
    ( (This)->lpVtbl -> put_DecodingOption(This,param,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITVSDecodeControl_INTERFACE_DEFINED__ */


#ifndef __ITVSDecodeCallback_INTERFACE_DEFINED__
#define __ITVSDecodeCallback_INTERFACE_DEFINED__

/* interface ITVSDecodeCallback */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVSDecodeCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C0967DFC-ABA0-40d5-9CBB-5E5B12170937")
    ITVSDecodeCallback : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnDataReceive( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT vData,
            /* [in] */ long lError) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVSDecodeCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVSDecodeCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVSDecodeCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVSDecodeCallback * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnDataReceive )( 
            ITVSDecodeCallback * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT vData,
            /* [in] */ long lError);
        
        END_INTERFACE
    } ITVSDecodeCallbackVtbl;

    interface ITVSDecodeCallback
    {
        CONST_VTBL struct ITVSDecodeCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVSDecodeCallback_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITVSDecodeCallback_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITVSDecodeCallback_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITVSDecodeCallback_OnDataReceive(This,lChID,vData,lError)	\
    ( (This)->lpVtbl -> OnDataReceive(This,lChID,vData,lError) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITVSDecodeCallback_INTERFACE_DEFINED__ */


#ifndef __ITVSDisplay_INTERFACE_DEFINED__
#define __ITVSDisplay_INTERFACE_DEFINED__

/* interface ITVSDisplay */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVSDisplay;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("234BDCD3-2720-4876-A2F0-DE9A715BF21A")
    ITVSDisplay : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MonitorCount( 
            /* [retval][out] */ short *cMonitor) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LayoutMode( 
            /* [in] */ short nMonitor,
            /* [retval][out] */ long *eLayout) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LayoutMode( 
            /* [in] */ short nMonitor,
            /* [in] */ long eLayout) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DUCount( 
            /* [in] */ short nMonitor,
            /* [retval][out] */ long *cCount) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DUCount( 
            /* [in] */ short nMonitor,
            /* [in] */ long nCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MapChannel( 
            /* [in] */ short nMonitor,
            /* [in] */ long nDU,
            /* [retval][out] */ INT_PTR *lChID) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MapChannel( 
            /* [in] */ short nMonitor,
            /* [in] */ long nDU,
            /* [in] */ INT_PTR lChID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDURect( 
            /* [in] */ short nMonitor,
            /* [in] */ long nDU,
            /* [in] */ short nLeft,
            /* [in] */ short nTop,
            /* [in] */ short nRight,
            /* [in] */ short nBottom,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDURect( 
            /* [in] */ short nMonitor,
            /* [in] */ long nDU,
            /* [out] */ short *pnLeft,
            /* [out] */ short *pnTop,
            /* [out] */ short *pnRight,
            /* [out] */ short *pnBottom,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ShowToolbar( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bToolbar) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ShowToolbar( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bToolbar) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ToolbarConfig( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *eConfig) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ToolbarConfig( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long eConfig) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddOsdArea( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ short nLeft,
            /* [in] */ short nTop,
            /* [in] */ short nRight,
            /* [in] */ short nBottom,
            /* [in] */ short nType,
            /* [retval][out] */ INT_PTR *pOSDID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveOsdArea( 
            /* [in] */ INT_PTR lOSDID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateOsdArea( 
            /* [in] */ INT_PTR lOSDID,
            /* [in] */ VARIANT vData) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OsdType( 
            /* [in] */ INT_PTR lOSDID,
            /* [retval][out] */ short *eType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OsdForeColor( 
            /* [in] */ INT_PTR lOSDID,
            /* [retval][out] */ long *clrFore) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OsdForeColor( 
            /* [in] */ INT_PTR lOSDID,
            /* [in] */ long clrFore) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OsdBackColor( 
            /* [in] */ INT_PTR lOSDID,
            /* [retval][out] */ long *clrBack) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OsdBackColor( 
            /* [in] */ INT_PTR lOSDID,
            /* [in] */ long clrBack) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OsdTransparency( 
            /* [in] */ INT_PTR lOSDID,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OsdTransparency( 
            /* [in] */ INT_PTR lOSDID,
            /* [in] */ VARIANT_BOOL bResult) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OsdFontName( 
            /* [in] */ INT_PTR lOSDID,
            /* [retval][out] */ BSTR *sName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OsdFontName( 
            /* [in] */ INT_PTR lOSDID,
            /* [in] */ BSTR sName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OsdFontSize( 
            /* [in] */ INT_PTR lOSDID,
            /* [retval][out] */ short *iSize) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OsdFontSize( 
            /* [in] */ INT_PTR lOSDID,
            /* [in] */ short iSize) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDigitalZoom( 
            INT_PTR lChID,
            long lZoom,
            long xStart,
            long yStart) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDigitalZoom( 
            INT_PTR lChID,
            long *lZoom,
            long *xStart,
            long *yStart) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DUMaximize( 
            short nMonitor,
            long nDU,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DUMaximize( 
            short nMonitor,
            long nDU,
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PopupWindow( 
            /* [in] */ short nMonitor,
            /* [in] */ INT_PTR lChID,
            /* [in] */ INT_PTR lOwnerWnd,
            /* [in] */ short nLeft,
            /* [in] */ short nTop,
            /* [in] */ short nRight,
            /* [in] */ short nBottom,
            /* [in] */ ULONG dwStyles,
            /* [retval][out] */ INT_PTR *lVideoWnd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AlignOsd( 
            INT_PTR lOSDID,
            long lVert,
            long lHorz) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoScale( 
            short nMonitor,
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoScale( 
            short nMonitor,
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoResolution( 
            INT_PTR lChID,
            long *width,
            long *height) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GraphUnmap( 
            /* [in] */ INT_PTR lChID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOsdFontSize( 
            /* [in] */ INT_PTR lOSDID,
            /* [in] */ short iSize) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOsdFontSize( 
            /* [in] */ INT_PTR lOSDID,
            /* [retval][out] */ short *iSize) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ChannelFlip( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *lMode) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ChannelFlip( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMapChannel( 
            /* [in] */ short nMonitor,
            /* [in] */ long nDU,
            /* [retval][out] */ INT_PTR *lChID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMapChannel( 
            /* [in] */ short nMonitor,
            /* [in] */ long nDU,
            /* [in] */ INT_PTR lChID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAudioDisplayPos( 
            /* [in] */ long lPos) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAudioDisplayHwnd( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ INT_PTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDURect2( 
            /* [in] */ short nMonitor,
            /* [in] */ VARIANT vDU,
            /* [in] */ VARIANT vRect,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentIntraPage( 
            /* [in] */ short nMonitor,
            /* [retval][out] */ long *lIndex) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CurrentIntraPage( 
            /* [in] */ short nMonitor,
            /* [in] */ long lIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetIntraPageCountMax( 
            /* [in] */ short nMonitor,
            /* [retval][out] */ long *lCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsDUVisible( 
            /* [in] */ long lGlobalDUIndex,
            /* [in] */ long lIntraPage,
            /* [in] */ long lMaximizedDU,
            /* [in] */ long lDUsPerPage,
            /* [in] */ VARIANT_BOOL vtbArbitraryMode,
            /* [retval][out] */ VARIANT_BOOL *vtbVisible) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVSDisplayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVSDisplay * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVSDisplay * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVSDisplay * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVSDisplay * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVSDisplay * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVSDisplay * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVSDisplay * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MonitorCount )( 
            ITVSDisplay * This,
            /* [retval][out] */ short *cMonitor);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LayoutMode )( 
            ITVSDisplay * This,
            /* [in] */ short nMonitor,
            /* [retval][out] */ long *eLayout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LayoutMode )( 
            ITVSDisplay * This,
            /* [in] */ short nMonitor,
            /* [in] */ long eLayout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DUCount )( 
            ITVSDisplay * This,
            /* [in] */ short nMonitor,
            /* [retval][out] */ long *cCount);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DUCount )( 
            ITVSDisplay * This,
            /* [in] */ short nMonitor,
            /* [in] */ long nCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MapChannel )( 
            ITVSDisplay * This,
            /* [in] */ short nMonitor,
            /* [in] */ long nDU,
            /* [retval][out] */ INT_PTR *lChID);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MapChannel )( 
            ITVSDisplay * This,
            /* [in] */ short nMonitor,
            /* [in] */ long nDU,
            /* [in] */ INT_PTR lChID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDURect )( 
            ITVSDisplay * This,
            /* [in] */ short nMonitor,
            /* [in] */ long nDU,
            /* [in] */ short nLeft,
            /* [in] */ short nTop,
            /* [in] */ short nRight,
            /* [in] */ short nBottom,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDURect )( 
            ITVSDisplay * This,
            /* [in] */ short nMonitor,
            /* [in] */ long nDU,
            /* [out] */ short *pnLeft,
            /* [out] */ short *pnTop,
            /* [out] */ short *pnRight,
            /* [out] */ short *pnBottom,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShowToolbar )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bToolbar);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ShowToolbar )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bToolbar);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ToolbarConfig )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *eConfig);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ToolbarConfig )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long eConfig);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddOsdArea )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ short nLeft,
            /* [in] */ short nTop,
            /* [in] */ short nRight,
            /* [in] */ short nBottom,
            /* [in] */ short nType,
            /* [retval][out] */ INT_PTR *pOSDID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveOsdArea )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lOSDID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateOsdArea )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lOSDID,
            /* [in] */ VARIANT vData);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OsdType )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lOSDID,
            /* [retval][out] */ short *eType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OsdForeColor )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lOSDID,
            /* [retval][out] */ long *clrFore);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OsdForeColor )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lOSDID,
            /* [in] */ long clrFore);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OsdBackColor )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lOSDID,
            /* [retval][out] */ long *clrBack);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OsdBackColor )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lOSDID,
            /* [in] */ long clrBack);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OsdTransparency )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lOSDID,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OsdTransparency )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lOSDID,
            /* [in] */ VARIANT_BOOL bResult);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OsdFontName )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lOSDID,
            /* [retval][out] */ BSTR *sName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OsdFontName )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lOSDID,
            /* [in] */ BSTR sName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OsdFontSize )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lOSDID,
            /* [retval][out] */ short *iSize);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OsdFontSize )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lOSDID,
            /* [in] */ short iSize);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDigitalZoom )( 
            ITVSDisplay * This,
            INT_PTR lChID,
            long lZoom,
            long xStart,
            long yStart);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDigitalZoom )( 
            ITVSDisplay * This,
            INT_PTR lChID,
            long *lZoom,
            long *xStart,
            long *yStart);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DUMaximize )( 
            ITVSDisplay * This,
            short nMonitor,
            long nDU,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DUMaximize )( 
            ITVSDisplay * This,
            short nMonitor,
            long nDU,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PopupWindow )( 
            ITVSDisplay * This,
            /* [in] */ short nMonitor,
            /* [in] */ INT_PTR lChID,
            /* [in] */ INT_PTR lOwnerWnd,
            /* [in] */ short nLeft,
            /* [in] */ short nTop,
            /* [in] */ short nRight,
            /* [in] */ short nBottom,
            /* [in] */ ULONG dwStyles,
            /* [retval][out] */ INT_PTR *lVideoWnd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AlignOsd )( 
            ITVSDisplay * This,
            INT_PTR lOSDID,
            long lVert,
            long lHorz);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoScale )( 
            ITVSDisplay * This,
            short nMonitor,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VideoScale )( 
            ITVSDisplay * This,
            short nMonitor,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoResolution )( 
            ITVSDisplay * This,
            INT_PTR lChID,
            long *width,
            long *height);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GraphUnmap )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lChID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetOsdFontSize )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lOSDID,
            /* [in] */ short iSize);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetOsdFontSize )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lOSDID,
            /* [retval][out] */ short *iSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ChannelFlip )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ long *lMode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ChannelFlip )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMapChannel )( 
            ITVSDisplay * This,
            /* [in] */ short nMonitor,
            /* [in] */ long nDU,
            /* [retval][out] */ INT_PTR *lChID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMapChannel )( 
            ITVSDisplay * This,
            /* [in] */ short nMonitor,
            /* [in] */ long nDU,
            /* [in] */ INT_PTR lChID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAudioDisplayPos )( 
            ITVSDisplay * This,
            /* [in] */ long lPos);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAudioDisplayHwnd )( 
            ITVSDisplay * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ INT_PTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDURect2 )( 
            ITVSDisplay * This,
            /* [in] */ short nMonitor,
            /* [in] */ VARIANT vDU,
            /* [in] */ VARIANT vRect,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentIntraPage )( 
            ITVSDisplay * This,
            /* [in] */ short nMonitor,
            /* [retval][out] */ long *lIndex);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CurrentIntraPage )( 
            ITVSDisplay * This,
            /* [in] */ short nMonitor,
            /* [in] */ long lIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetIntraPageCountMax )( 
            ITVSDisplay * This,
            /* [in] */ short nMonitor,
            /* [retval][out] */ long *lCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsDUVisible )( 
            ITVSDisplay * This,
            /* [in] */ long lGlobalDUIndex,
            /* [in] */ long lIntraPage,
            /* [in] */ long lMaximizedDU,
            /* [in] */ long lDUsPerPage,
            /* [in] */ VARIANT_BOOL vtbArbitraryMode,
            /* [retval][out] */ VARIANT_BOOL *vtbVisible);
        
        END_INTERFACE
    } ITVSDisplayVtbl;

    interface ITVSDisplay
    {
        CONST_VTBL struct ITVSDisplayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVSDisplay_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITVSDisplay_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITVSDisplay_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITVSDisplay_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITVSDisplay_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITVSDisplay_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITVSDisplay_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ITVSDisplay_get_MonitorCount(This,cMonitor)	\
    ( (This)->lpVtbl -> get_MonitorCount(This,cMonitor) ) 

#define ITVSDisplay_get_LayoutMode(This,nMonitor,eLayout)	\
    ( (This)->lpVtbl -> get_LayoutMode(This,nMonitor,eLayout) ) 

#define ITVSDisplay_put_LayoutMode(This,nMonitor,eLayout)	\
    ( (This)->lpVtbl -> put_LayoutMode(This,nMonitor,eLayout) ) 

#define ITVSDisplay_get_DUCount(This,nMonitor,cCount)	\
    ( (This)->lpVtbl -> get_DUCount(This,nMonitor,cCount) ) 

#define ITVSDisplay_put_DUCount(This,nMonitor,nCount)	\
    ( (This)->lpVtbl -> put_DUCount(This,nMonitor,nCount) ) 

#define ITVSDisplay_get_MapChannel(This,nMonitor,nDU,lChID)	\
    ( (This)->lpVtbl -> get_MapChannel(This,nMonitor,nDU,lChID) ) 

#define ITVSDisplay_put_MapChannel(This,nMonitor,nDU,lChID)	\
    ( (This)->lpVtbl -> put_MapChannel(This,nMonitor,nDU,lChID) ) 

#define ITVSDisplay_SetDURect(This,nMonitor,nDU,nLeft,nTop,nRight,nBottom,bResult)	\
    ( (This)->lpVtbl -> SetDURect(This,nMonitor,nDU,nLeft,nTop,nRight,nBottom,bResult) ) 

#define ITVSDisplay_GetDURect(This,nMonitor,nDU,pnLeft,pnTop,pnRight,pnBottom,bResult)	\
    ( (This)->lpVtbl -> GetDURect(This,nMonitor,nDU,pnLeft,pnTop,pnRight,pnBottom,bResult) ) 

#define ITVSDisplay_get_ShowToolbar(This,lChID,bToolbar)	\
    ( (This)->lpVtbl -> get_ShowToolbar(This,lChID,bToolbar) ) 

#define ITVSDisplay_put_ShowToolbar(This,lChID,bToolbar)	\
    ( (This)->lpVtbl -> put_ShowToolbar(This,lChID,bToolbar) ) 

#define ITVSDisplay_get_ToolbarConfig(This,lChID,eConfig)	\
    ( (This)->lpVtbl -> get_ToolbarConfig(This,lChID,eConfig) ) 

#define ITVSDisplay_put_ToolbarConfig(This,lChID,eConfig)	\
    ( (This)->lpVtbl -> put_ToolbarConfig(This,lChID,eConfig) ) 

#define ITVSDisplay_AddOsdArea(This,lChID,nLeft,nTop,nRight,nBottom,nType,pOSDID)	\
    ( (This)->lpVtbl -> AddOsdArea(This,lChID,nLeft,nTop,nRight,nBottom,nType,pOSDID) ) 

#define ITVSDisplay_RemoveOsdArea(This,lOSDID)	\
    ( (This)->lpVtbl -> RemoveOsdArea(This,lOSDID) ) 

#define ITVSDisplay_UpdateOsdArea(This,lOSDID,vData)	\
    ( (This)->lpVtbl -> UpdateOsdArea(This,lOSDID,vData) ) 

#define ITVSDisplay_get_OsdType(This,lOSDID,eType)	\
    ( (This)->lpVtbl -> get_OsdType(This,lOSDID,eType) ) 

#define ITVSDisplay_get_OsdForeColor(This,lOSDID,clrFore)	\
    ( (This)->lpVtbl -> get_OsdForeColor(This,lOSDID,clrFore) ) 

#define ITVSDisplay_put_OsdForeColor(This,lOSDID,clrFore)	\
    ( (This)->lpVtbl -> put_OsdForeColor(This,lOSDID,clrFore) ) 

#define ITVSDisplay_get_OsdBackColor(This,lOSDID,clrBack)	\
    ( (This)->lpVtbl -> get_OsdBackColor(This,lOSDID,clrBack) ) 

#define ITVSDisplay_put_OsdBackColor(This,lOSDID,clrBack)	\
    ( (This)->lpVtbl -> put_OsdBackColor(This,lOSDID,clrBack) ) 

#define ITVSDisplay_get_OsdTransparency(This,lOSDID,bResult)	\
    ( (This)->lpVtbl -> get_OsdTransparency(This,lOSDID,bResult) ) 

#define ITVSDisplay_put_OsdTransparency(This,lOSDID,bResult)	\
    ( (This)->lpVtbl -> put_OsdTransparency(This,lOSDID,bResult) ) 

#define ITVSDisplay_get_OsdFontName(This,lOSDID,sName)	\
    ( (This)->lpVtbl -> get_OsdFontName(This,lOSDID,sName) ) 

#define ITVSDisplay_put_OsdFontName(This,lOSDID,sName)	\
    ( (This)->lpVtbl -> put_OsdFontName(This,lOSDID,sName) ) 

#define ITVSDisplay_get_OsdFontSize(This,lOSDID,iSize)	\
    ( (This)->lpVtbl -> get_OsdFontSize(This,lOSDID,iSize) ) 

#define ITVSDisplay_put_OsdFontSize(This,lOSDID,iSize)	\
    ( (This)->lpVtbl -> put_OsdFontSize(This,lOSDID,iSize) ) 

#define ITVSDisplay_SetDigitalZoom(This,lChID,lZoom,xStart,yStart)	\
    ( (This)->lpVtbl -> SetDigitalZoom(This,lChID,lZoom,xStart,yStart) ) 

#define ITVSDisplay_GetDigitalZoom(This,lChID,lZoom,xStart,yStart)	\
    ( (This)->lpVtbl -> GetDigitalZoom(This,lChID,lZoom,xStart,yStart) ) 

#define ITVSDisplay_get_DUMaximize(This,nMonitor,nDU,pVal)	\
    ( (This)->lpVtbl -> get_DUMaximize(This,nMonitor,nDU,pVal) ) 

#define ITVSDisplay_put_DUMaximize(This,nMonitor,nDU,newVal)	\
    ( (This)->lpVtbl -> put_DUMaximize(This,nMonitor,nDU,newVal) ) 

#define ITVSDisplay_PopupWindow(This,nMonitor,lChID,lOwnerWnd,nLeft,nTop,nRight,nBottom,dwStyles,lVideoWnd)	\
    ( (This)->lpVtbl -> PopupWindow(This,nMonitor,lChID,lOwnerWnd,nLeft,nTop,nRight,nBottom,dwStyles,lVideoWnd) ) 

#define ITVSDisplay_AlignOsd(This,lOSDID,lVert,lHorz)	\
    ( (This)->lpVtbl -> AlignOsd(This,lOSDID,lVert,lHorz) ) 

#define ITVSDisplay_get_VideoScale(This,nMonitor,pVal)	\
    ( (This)->lpVtbl -> get_VideoScale(This,nMonitor,pVal) ) 

#define ITVSDisplay_put_VideoScale(This,nMonitor,newVal)	\
    ( (This)->lpVtbl -> put_VideoScale(This,nMonitor,newVal) ) 

#define ITVSDisplay_GetVideoResolution(This,lChID,width,height)	\
    ( (This)->lpVtbl -> GetVideoResolution(This,lChID,width,height) ) 

#define ITVSDisplay_GraphUnmap(This,lChID)	\
    ( (This)->lpVtbl -> GraphUnmap(This,lChID) ) 

#define ITVSDisplay_SetOsdFontSize(This,lOSDID,iSize)	\
    ( (This)->lpVtbl -> SetOsdFontSize(This,lOSDID,iSize) ) 

#define ITVSDisplay_GetOsdFontSize(This,lOSDID,iSize)	\
    ( (This)->lpVtbl -> GetOsdFontSize(This,lOSDID,iSize) ) 

#define ITVSDisplay_get_ChannelFlip(This,lChID,lMode)	\
    ( (This)->lpVtbl -> get_ChannelFlip(This,lChID,lMode) ) 

#define ITVSDisplay_put_ChannelFlip(This,lChID,lMode)	\
    ( (This)->lpVtbl -> put_ChannelFlip(This,lChID,lMode) ) 

#define ITVSDisplay_GetMapChannel(This,nMonitor,nDU,lChID)	\
    ( (This)->lpVtbl -> GetMapChannel(This,nMonitor,nDU,lChID) ) 

#define ITVSDisplay_SetMapChannel(This,nMonitor,nDU,lChID)	\
    ( (This)->lpVtbl -> SetMapChannel(This,nMonitor,nDU,lChID) ) 

#define ITVSDisplay_SetAudioDisplayPos(This,lPos)	\
    ( (This)->lpVtbl -> SetAudioDisplayPos(This,lPos) ) 

#define ITVSDisplay_SetAudioDisplayHwnd(This,lChID,newVal)	\
    ( (This)->lpVtbl -> SetAudioDisplayHwnd(This,lChID,newVal) ) 

#define ITVSDisplay_SetDURect2(This,nMonitor,vDU,vRect,bResult)	\
    ( (This)->lpVtbl -> SetDURect2(This,nMonitor,vDU,vRect,bResult) ) 

#define ITVSDisplay_get_CurrentIntraPage(This,nMonitor,lIndex)	\
    ( (This)->lpVtbl -> get_CurrentIntraPage(This,nMonitor,lIndex) ) 

#define ITVSDisplay_put_CurrentIntraPage(This,nMonitor,lIndex)	\
    ( (This)->lpVtbl -> put_CurrentIntraPage(This,nMonitor,lIndex) ) 

#define ITVSDisplay_GetIntraPageCountMax(This,nMonitor,lCount)	\
    ( (This)->lpVtbl -> GetIntraPageCountMax(This,nMonitor,lCount) ) 

#define ITVSDisplay_IsDUVisible(This,lGlobalDUIndex,lIntraPage,lMaximizedDU,lDUsPerPage,vtbArbitraryMode,vtbVisible)	\
    ( (This)->lpVtbl -> IsDUVisible(This,lGlobalDUIndex,lIntraPage,lMaximizedDU,lDUsPerPage,vtbArbitraryMode,vtbVisible) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITVSDisplay_INTERFACE_DEFINED__ */


#ifndef __ITVSPlaybackControl_INTERFACE_DEFINED__
#define __ITVSPlaybackControl_INTERFACE_DEFINED__

/* interface ITVSPlaybackControl */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVSPlaybackControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("10998A2A-E955-4931-A9E4-83258B6E4BAC")
    ITVSPlaybackControl : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDisplay( 
            /* [retval][out] */ ITVSDisplay **ppDisplay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRecordedDays( 
            /* [in] */ VARIANT dMonth,
            /* [out] */ LONG *bitDays,
            /* [in] */ BOOL bForce,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRecordedChannels( 
            /* [in] */ VARIANT dDay,
            /* [out] */ VARIANT *vvGlobalIDs,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetChannelInfo( 
            /* [in] */ VARIANT vGlobalId,
            /* [out] */ BSTR *sName,
            /* [out] */ BSTR *sServer,
            /* [out] */ long *lVideoType,
            /* [out] */ long *lAudioType,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTimelineData( 
            /* [in] */ VARIANT vGlobalId,
            /* [in] */ VARIANT dDay,
            /* [retval][out] */ VARIANT *vvTimeline) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRecordDuration( 
            /* [out] */ VARIANT *pvBegin,
            /* [out] */ VARIANT *pvEnd,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEventList( 
            /* [in] */ VARIANT vGlobalId,
            /* [in] */ VARIANT vBegin,
            /* [in] */ VARIANT vEnd,
            /* [in] */ long lEventMask,
            /* [in] */ long cEventRequired,
            /* [retval][out] */ long *cEventFound) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEventInfo( 
            /* [in] */ long lNumber,
            /* [out] */ long *lMask,
            /* [out] */ VARIANT *dTime,
            /* [out] */ VARIANT *vvGlobalIDs,
            /* [out] */ long *lParam,
            /* [retval][out] */ VARIANT_BOOL *bRes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenChannel( 
            /* [in] */ VARIANT vGlobalId,
            /* [retval][out] */ INT_PTR *lChID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseChannel( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bRes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Play( 
            /* [in] */ long lSpeed,
            /* [retval][out] */ VARIANT_BOOL *bRes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Pause( 
            /* [retval][out] */ VARIANT_BOOL *bRes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Stop( 
            /* [retval][out] */ VARIANT_BOOL *bRes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Step( 
            /* [in] */ long lStep,
            /* [retval][out] */ VARIANT_BOOL *bRes) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CurrentTime( 
            /* [in] */ VARIANT dTime) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentTime( 
            /* [retval][out] */ VARIANT *dTime) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartAVIBackup( 
            /* [in] */ VARIANT vGlobalId,
            /* [in] */ long lFlags,
            /* [in] */ BSTR sPath,
            /* [in] */ VARIANT vBegin,
            /* [in] */ VARIANT vEnd,
            /* [out] */ long *lDuration,
            /* [out] */ VARIANT *vSize,
            /* [retval][out] */ VARIANT_BOOL *bRes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopAVIBackup( 
            /* [in] */ VARIANT vGlobalId,
            /* [retval][out] */ VARIANT_BOOL *bRes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PictureExport( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ BSTR sPath,
            /* [in] */ long lCompression,
            /* [retval][out] */ VARIANT_BOOL *bRes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMute( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bMute) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMute( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bMuted) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DecodingOption( 
            /* [in] */ long param,
            /* [retval][out] */ long *value) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DecodingOption( 
            /* [in] */ long param,
            /* [in] */ long value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect( 
            BSTR bsAddr,
            long lPort,
            BSTR bsLogin,
            BSTR bsPass) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Config( 
            long eItem,
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Config( 
            long eItem,
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalConfig( 
            long eItem,
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LocalConfig( 
            long eItem,
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Disconnect( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Snapshot( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lCompression,
            /* [in] */ VARIANT_BOOL bAutoSave) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PreviewSnapshot( 
            /* [in] */ INT_PTR lChID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveSnapshot( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lCompression,
            /* [in] */ BSTR pFilename) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSnapshot( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lCompression,
            /* [in] */ long xWidth,
            /* [in] */ long yHeight,
            /* [out] */ VARIANT *data,
            /* [out] */ long *size) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOsdRectangle( 
            INT_PTR lChID,
            long lColor,
            long lWidth,
            long lOffset) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveOsdRectangle( 
            INT_PTR lChID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_KeepAspectRatio( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bAspect) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_KeepAspectRatio( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bAspect) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetChannelDuration( 
            /* [in] */ VARIANT vGlobalId,
            /* [in] */ VARIANT vBegin,
            /* [in] */ VARIANT vEnd,
            /* [out] */ long *value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetBackupSpeed( 
            /* [in] */ long value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAVIEstimatedSize( 
            /* [in] */ VARIANT vGlobalId,
            /* [in] */ long lFlags,
            /* [in] */ BSTR sPath,
            /* [in] */ VARIANT vBegin,
            /* [in] */ VARIANT vEnd,
            /* [out] */ long *lDuration,
            /* [out] */ VARIANT *vSize,
            /* [retval][out] */ VARIANT_BOOL *bRes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAVIFileInfo( 
            /* [in] */ INT_PTR ChnlID,
            /* [in] */ BSTR pInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartNativeBackup( 
            /* [in] */ VARIANT vGlobalId,
            /* [in] */ long lFlags,
            /* [in] */ BSTR sPath,
            /* [in] */ VARIANT vBegin,
            /* [in] */ VARIANT vEnd,
            /* [out] */ long *lDuration,
            /* [out] */ VARIANT *vSize,
            /* [retval][out] */ VARIANT_BOOL *bRes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopNativeBackup( 
            /* [in] */ VARIANT vGlobalId,
            /* [retval][out] */ VARIANT_BOOL *bRes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNativeEstimatedSize( 
            /* [in] */ VARIANT vGlobalId,
            /* [in] */ long lFlags,
            /* [in] */ BSTR sPath,
            /* [in] */ VARIANT vBegin,
            /* [in] */ VARIANT vEnd,
            /* [out] */ VARIANT *vSize,
            /* [retval][out] */ VARIANT_BOOL *bRes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenExternalStorage( 
            /* [in] */ BSTR sPath,
            /* [in] */ LPARAM lParam,
            /* [retval][out] */ VARIANT_BOOL *bRes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseExternalStorage( 
            /* [retval][out] */ VARIANT_BOOL *bRes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsDisplayInitialized( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRecordedChannelsForDuration( 
            /* [in] */ VARIANT dStartDate,
            /* [in] */ VARIANT dStopDate,
            /* [out] */ VARIANT *vvGlobalIDs,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenChannelWithAddress( 
            /* [in] */ BSTR bsAddr,
            /* [in] */ long lPort,
            /* [retval][out] */ INT_PTR *lChID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindChannelByAddress( 
            /* [in] */ BSTR bsAddr,
            /* [in] */ long lPort,
            /* [retval][out] */ LONGLONG *llChID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCurrentTime( 
            /* [in] */ VARIANT year,
            /* [in] */ VARIANT month,
            /* [in] */ VARIANT day,
            /* [in] */ VARIANT hour,
            /* [in] */ VARIANT minute,
            /* [in] */ VARIANT second) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRecordedChannels2( 
            /* [in] */ VARIANT year,
            /* [in] */ VARIANT month,
            /* [in] */ VARIANT day,
            /* [out] */ VARIANT *vvGlobalIDs,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowPlaybackTime( 
            /* [in] */ VARIANT show,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDecoder( 
            /* [in] */ DWORD decoder) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDecoder( 
            /* [retval][out] */ DWORD *decoder) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAvailableDecoders( 
            /* [retval][out] */ DWORD *decoders) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadNetworkDrives( 
            /* [in] */ BSTR szConfig) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDecodingTime( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT *dTime) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMaxGopSize( 
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ int *size) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PlayIFrame( 
            /* [in] */ VARIANT dTime) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopIFramePlayback( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetChnlDescOldestLatestTime( 
            /* [in] */ VARIANT vGlobalId,
            /* [in] */ VARIANT dDay,
            /* [out] */ VARIANT *vvTimes,
            /* [retval][out] */ VARIANT_BOOL *bRes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PutCurrentTimeDirection( 
            /* [in] */ VARIANT vDirection,
            /* [retval][out] */ VARIANT_BOOL *bRes) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVSPlaybackControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVSPlaybackControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVSPlaybackControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVSPlaybackControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVSPlaybackControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVSPlaybackControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVSPlaybackControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVSPlaybackControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDisplay )( 
            ITVSPlaybackControl * This,
            /* [retval][out] */ ITVSDisplay **ppDisplay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRecordedDays )( 
            ITVSPlaybackControl * This,
            /* [in] */ VARIANT dMonth,
            /* [out] */ LONG *bitDays,
            /* [in] */ BOOL bForce,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRecordedChannels )( 
            ITVSPlaybackControl * This,
            /* [in] */ VARIANT dDay,
            /* [out] */ VARIANT *vvGlobalIDs,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetChannelInfo )( 
            ITVSPlaybackControl * This,
            /* [in] */ VARIANT vGlobalId,
            /* [out] */ BSTR *sName,
            /* [out] */ BSTR *sServer,
            /* [out] */ long *lVideoType,
            /* [out] */ long *lAudioType,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTimelineData )( 
            ITVSPlaybackControl * This,
            /* [in] */ VARIANT vGlobalId,
            /* [in] */ VARIANT dDay,
            /* [retval][out] */ VARIANT *vvTimeline);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRecordDuration )( 
            ITVSPlaybackControl * This,
            /* [out] */ VARIANT *pvBegin,
            /* [out] */ VARIANT *pvEnd,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEventList )( 
            ITVSPlaybackControl * This,
            /* [in] */ VARIANT vGlobalId,
            /* [in] */ VARIANT vBegin,
            /* [in] */ VARIANT vEnd,
            /* [in] */ long lEventMask,
            /* [in] */ long cEventRequired,
            /* [retval][out] */ long *cEventFound);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEventInfo )( 
            ITVSPlaybackControl * This,
            /* [in] */ long lNumber,
            /* [out] */ long *lMask,
            /* [out] */ VARIANT *dTime,
            /* [out] */ VARIANT *vvGlobalIDs,
            /* [out] */ long *lParam,
            /* [retval][out] */ VARIANT_BOOL *bRes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenChannel )( 
            ITVSPlaybackControl * This,
            /* [in] */ VARIANT vGlobalId,
            /* [retval][out] */ INT_PTR *lChID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CloseChannel )( 
            ITVSPlaybackControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bRes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Play )( 
            ITVSPlaybackControl * This,
            /* [in] */ long lSpeed,
            /* [retval][out] */ VARIANT_BOOL *bRes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Pause )( 
            ITVSPlaybackControl * This,
            /* [retval][out] */ VARIANT_BOOL *bRes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Stop )( 
            ITVSPlaybackControl * This,
            /* [retval][out] */ VARIANT_BOOL *bRes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Step )( 
            ITVSPlaybackControl * This,
            /* [in] */ long lStep,
            /* [retval][out] */ VARIANT_BOOL *bRes);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CurrentTime )( 
            ITVSPlaybackControl * This,
            /* [in] */ VARIANT dTime);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentTime )( 
            ITVSPlaybackControl * This,
            /* [retval][out] */ VARIANT *dTime);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartAVIBackup )( 
            ITVSPlaybackControl * This,
            /* [in] */ VARIANT vGlobalId,
            /* [in] */ long lFlags,
            /* [in] */ BSTR sPath,
            /* [in] */ VARIANT vBegin,
            /* [in] */ VARIANT vEnd,
            /* [out] */ long *lDuration,
            /* [out] */ VARIANT *vSize,
            /* [retval][out] */ VARIANT_BOOL *bRes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopAVIBackup )( 
            ITVSPlaybackControl * This,
            /* [in] */ VARIANT vGlobalId,
            /* [retval][out] */ VARIANT_BOOL *bRes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PictureExport )( 
            ITVSPlaybackControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ BSTR sPath,
            /* [in] */ long lCompression,
            /* [retval][out] */ VARIANT_BOOL *bRes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMute )( 
            ITVSPlaybackControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bMute);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMute )( 
            ITVSPlaybackControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bMuted);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DecodingOption )( 
            ITVSPlaybackControl * This,
            /* [in] */ long param,
            /* [retval][out] */ long *value);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DecodingOption )( 
            ITVSPlaybackControl * This,
            /* [in] */ long param,
            /* [in] */ long value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Connect )( 
            ITVSPlaybackControl * This,
            BSTR bsAddr,
            long lPort,
            BSTR bsLogin,
            BSTR bsPass);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Config )( 
            ITVSPlaybackControl * This,
            long eItem,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Config )( 
            ITVSPlaybackControl * This,
            long eItem,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LocalConfig )( 
            ITVSPlaybackControl * This,
            long eItem,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LocalConfig )( 
            ITVSPlaybackControl * This,
            long eItem,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            ITVSPlaybackControl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Snapshot )( 
            ITVSPlaybackControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lCompression,
            /* [in] */ VARIANT_BOOL bAutoSave);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PreviewSnapshot )( 
            ITVSPlaybackControl * This,
            /* [in] */ INT_PTR lChID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveSnapshot )( 
            ITVSPlaybackControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lCompression,
            /* [in] */ BSTR pFilename);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSnapshot )( 
            ITVSPlaybackControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ long lCompression,
            /* [in] */ long xWidth,
            /* [in] */ long yHeight,
            /* [out] */ VARIANT *data,
            /* [out] */ long *size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetOsdRectangle )( 
            ITVSPlaybackControl * This,
            INT_PTR lChID,
            long lColor,
            long lWidth,
            long lOffset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveOsdRectangle )( 
            ITVSPlaybackControl * This,
            INT_PTR lChID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_KeepAspectRatio )( 
            ITVSPlaybackControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT_BOOL *bAspect);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_KeepAspectRatio )( 
            ITVSPlaybackControl * This,
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT_BOOL bAspect);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetChannelDuration )( 
            ITVSPlaybackControl * This,
            /* [in] */ VARIANT vGlobalId,
            /* [in] */ VARIANT vBegin,
            /* [in] */ VARIANT vEnd,
            /* [out] */ long *value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetBackupSpeed )( 
            ITVSPlaybackControl * This,
            /* [in] */ long value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAVIEstimatedSize )( 
            ITVSPlaybackControl * This,
            /* [in] */ VARIANT vGlobalId,
            /* [in] */ long lFlags,
            /* [in] */ BSTR sPath,
            /* [in] */ VARIANT vBegin,
            /* [in] */ VARIANT vEnd,
            /* [out] */ long *lDuration,
            /* [out] */ VARIANT *vSize,
            /* [retval][out] */ VARIANT_BOOL *bRes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAVIFileInfo )( 
            ITVSPlaybackControl * This,
            /* [in] */ INT_PTR ChnlID,
            /* [in] */ BSTR pInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartNativeBackup )( 
            ITVSPlaybackControl * This,
            /* [in] */ VARIANT vGlobalId,
            /* [in] */ long lFlags,
            /* [in] */ BSTR sPath,
            /* [in] */ VARIANT vBegin,
            /* [in] */ VARIANT vEnd,
            /* [out] */ long *lDuration,
            /* [out] */ VARIANT *vSize,
            /* [retval][out] */ VARIANT_BOOL *bRes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopNativeBackup )( 
            ITVSPlaybackControl * This,
            /* [in] */ VARIANT vGlobalId,
            /* [retval][out] */ VARIANT_BOOL *bRes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetNativeEstimatedSize )( 
            ITVSPlaybackControl * This,
            /* [in] */ VARIANT vGlobalId,
            /* [in] */ long lFlags,
            /* [in] */ BSTR sPath,
            /* [in] */ VARIANT vBegin,
            /* [in] */ VARIANT vEnd,
            /* [out] */ VARIANT *vSize,
            /* [retval][out] */ VARIANT_BOOL *bRes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenExternalStorage )( 
            ITVSPlaybackControl * This,
            /* [in] */ BSTR sPath,
            /* [in] */ LPARAM lParam,
            /* [retval][out] */ VARIANT_BOOL *bRes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CloseExternalStorage )( 
            ITVSPlaybackControl * This,
            /* [retval][out] */ VARIANT_BOOL *bRes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsDisplayInitialized )( 
            ITVSPlaybackControl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRecordedChannelsForDuration )( 
            ITVSPlaybackControl * This,
            /* [in] */ VARIANT dStartDate,
            /* [in] */ VARIANT dStopDate,
            /* [out] */ VARIANT *vvGlobalIDs,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenChannelWithAddress )( 
            ITVSPlaybackControl * This,
            /* [in] */ BSTR bsAddr,
            /* [in] */ long lPort,
            /* [retval][out] */ INT_PTR *lChID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindChannelByAddress )( 
            ITVSPlaybackControl * This,
            /* [in] */ BSTR bsAddr,
            /* [in] */ long lPort,
            /* [retval][out] */ LONGLONG *llChID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCurrentTime )( 
            ITVSPlaybackControl * This,
            /* [in] */ VARIANT year,
            /* [in] */ VARIANT month,
            /* [in] */ VARIANT day,
            /* [in] */ VARIANT hour,
            /* [in] */ VARIANT minute,
            /* [in] */ VARIANT second);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRecordedChannels2 )( 
            ITVSPlaybackControl * This,
            /* [in] */ VARIANT year,
            /* [in] */ VARIANT month,
            /* [in] */ VARIANT day,
            /* [out] */ VARIANT *vvGlobalIDs,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ShowPlaybackTime )( 
            ITVSPlaybackControl * This,
            /* [in] */ VARIANT show,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDecoder )( 
            ITVSPlaybackControl * This,
            /* [in] */ DWORD decoder);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDecoder )( 
            ITVSPlaybackControl * This,
            /* [retval][out] */ DWORD *decoder);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAvailableDecoders )( 
            ITVSPlaybackControl * This,
            /* [retval][out] */ DWORD *decoders);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadNetworkDrives )( 
            ITVSPlaybackControl * This,
            /* [in] */ BSTR szConfig);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDecodingTime )( 
            ITVSPlaybackControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ VARIANT *dTime);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMaxGopSize )( 
            ITVSPlaybackControl * This,
            /* [in] */ INT_PTR lChID,
            /* [retval][out] */ int *size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PlayIFrame )( 
            ITVSPlaybackControl * This,
            /* [in] */ VARIANT dTime);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopIFramePlayback )( 
            ITVSPlaybackControl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetChnlDescOldestLatestTime )( 
            ITVSPlaybackControl * This,
            /* [in] */ VARIANT vGlobalId,
            /* [in] */ VARIANT dDay,
            /* [out] */ VARIANT *vvTimes,
            /* [retval][out] */ VARIANT_BOOL *bRes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PutCurrentTimeDirection )( 
            ITVSPlaybackControl * This,
            /* [in] */ VARIANT vDirection,
            /* [retval][out] */ VARIANT_BOOL *bRes);
        
        END_INTERFACE
    } ITVSPlaybackControlVtbl;

    interface ITVSPlaybackControl
    {
        CONST_VTBL struct ITVSPlaybackControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVSPlaybackControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITVSPlaybackControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITVSPlaybackControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITVSPlaybackControl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITVSPlaybackControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITVSPlaybackControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITVSPlaybackControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ITVSPlaybackControl_GetDisplay(This,ppDisplay)	\
    ( (This)->lpVtbl -> GetDisplay(This,ppDisplay) ) 

#define ITVSPlaybackControl_GetRecordedDays(This,dMonth,bitDays,bForce,bResult)	\
    ( (This)->lpVtbl -> GetRecordedDays(This,dMonth,bitDays,bForce,bResult) ) 

#define ITVSPlaybackControl_GetRecordedChannels(This,dDay,vvGlobalIDs,bResult)	\
    ( (This)->lpVtbl -> GetRecordedChannels(This,dDay,vvGlobalIDs,bResult) ) 

#define ITVSPlaybackControl_GetChannelInfo(This,vGlobalId,sName,sServer,lVideoType,lAudioType,bResult)	\
    ( (This)->lpVtbl -> GetChannelInfo(This,vGlobalId,sName,sServer,lVideoType,lAudioType,bResult) ) 

#define ITVSPlaybackControl_GetTimelineData(This,vGlobalId,dDay,vvTimeline)	\
    ( (This)->lpVtbl -> GetTimelineData(This,vGlobalId,dDay,vvTimeline) ) 

#define ITVSPlaybackControl_GetRecordDuration(This,pvBegin,pvEnd,bResult)	\
    ( (This)->lpVtbl -> GetRecordDuration(This,pvBegin,pvEnd,bResult) ) 

#define ITVSPlaybackControl_GetEventList(This,vGlobalId,vBegin,vEnd,lEventMask,cEventRequired,cEventFound)	\
    ( (This)->lpVtbl -> GetEventList(This,vGlobalId,vBegin,vEnd,lEventMask,cEventRequired,cEventFound) ) 

#define ITVSPlaybackControl_GetEventInfo(This,lNumber,lMask,dTime,vvGlobalIDs,lParam,bRes)	\
    ( (This)->lpVtbl -> GetEventInfo(This,lNumber,lMask,dTime,vvGlobalIDs,lParam,bRes) ) 

#define ITVSPlaybackControl_OpenChannel(This,vGlobalId,lChID)	\
    ( (This)->lpVtbl -> OpenChannel(This,vGlobalId,lChID) ) 

#define ITVSPlaybackControl_CloseChannel(This,lChID,bRes)	\
    ( (This)->lpVtbl -> CloseChannel(This,lChID,bRes) ) 

#define ITVSPlaybackControl_Play(This,lSpeed,bRes)	\
    ( (This)->lpVtbl -> Play(This,lSpeed,bRes) ) 

#define ITVSPlaybackControl_Pause(This,bRes)	\
    ( (This)->lpVtbl -> Pause(This,bRes) ) 

#define ITVSPlaybackControl_Stop(This,bRes)	\
    ( (This)->lpVtbl -> Stop(This,bRes) ) 

#define ITVSPlaybackControl_Step(This,lStep,bRes)	\
    ( (This)->lpVtbl -> Step(This,lStep,bRes) ) 

#define ITVSPlaybackControl_put_CurrentTime(This,dTime)	\
    ( (This)->lpVtbl -> put_CurrentTime(This,dTime) ) 

#define ITVSPlaybackControl_get_CurrentTime(This,dTime)	\
    ( (This)->lpVtbl -> get_CurrentTime(This,dTime) ) 

#define ITVSPlaybackControl_StartAVIBackup(This,vGlobalId,lFlags,sPath,vBegin,vEnd,lDuration,vSize,bRes)	\
    ( (This)->lpVtbl -> StartAVIBackup(This,vGlobalId,lFlags,sPath,vBegin,vEnd,lDuration,vSize,bRes) ) 

#define ITVSPlaybackControl_StopAVIBackup(This,vGlobalId,bRes)	\
    ( (This)->lpVtbl -> StopAVIBackup(This,vGlobalId,bRes) ) 

#define ITVSPlaybackControl_PictureExport(This,lChID,sPath,lCompression,bRes)	\
    ( (This)->lpVtbl -> PictureExport(This,lChID,sPath,lCompression,bRes) ) 

#define ITVSPlaybackControl_SetMute(This,lChID,bMute)	\
    ( (This)->lpVtbl -> SetMute(This,lChID,bMute) ) 

#define ITVSPlaybackControl_GetMute(This,lChID,bMuted)	\
    ( (This)->lpVtbl -> GetMute(This,lChID,bMuted) ) 

#define ITVSPlaybackControl_get_DecodingOption(This,param,value)	\
    ( (This)->lpVtbl -> get_DecodingOption(This,param,value) ) 

#define ITVSPlaybackControl_put_DecodingOption(This,param,value)	\
    ( (This)->lpVtbl -> put_DecodingOption(This,param,value) ) 

#define ITVSPlaybackControl_Connect(This,bsAddr,lPort,bsLogin,bsPass)	\
    ( (This)->lpVtbl -> Connect(This,bsAddr,lPort,bsLogin,bsPass) ) 

#define ITVSPlaybackControl_get_Config(This,eItem,pVal)	\
    ( (This)->lpVtbl -> get_Config(This,eItem,pVal) ) 

#define ITVSPlaybackControl_put_Config(This,eItem,newVal)	\
    ( (This)->lpVtbl -> put_Config(This,eItem,newVal) ) 

#define ITVSPlaybackControl_get_LocalConfig(This,eItem,pVal)	\
    ( (This)->lpVtbl -> get_LocalConfig(This,eItem,pVal) ) 

#define ITVSPlaybackControl_put_LocalConfig(This,eItem,newVal)	\
    ( (This)->lpVtbl -> put_LocalConfig(This,eItem,newVal) ) 

#define ITVSPlaybackControl_Disconnect(This)	\
    ( (This)->lpVtbl -> Disconnect(This) ) 

#define ITVSPlaybackControl_Snapshot(This,lChID,lCompression,bAutoSave)	\
    ( (This)->lpVtbl -> Snapshot(This,lChID,lCompression,bAutoSave) ) 

#define ITVSPlaybackControl_PreviewSnapshot(This,lChID)	\
    ( (This)->lpVtbl -> PreviewSnapshot(This,lChID) ) 

#define ITVSPlaybackControl_SaveSnapshot(This,lChID,lCompression,pFilename)	\
    ( (This)->lpVtbl -> SaveSnapshot(This,lChID,lCompression,pFilename) ) 

#define ITVSPlaybackControl_GetSnapshot(This,lChID,lCompression,xWidth,yHeight,data,size)	\
    ( (This)->lpVtbl -> GetSnapshot(This,lChID,lCompression,xWidth,yHeight,data,size) ) 

#define ITVSPlaybackControl_SetOsdRectangle(This,lChID,lColor,lWidth,lOffset)	\
    ( (This)->lpVtbl -> SetOsdRectangle(This,lChID,lColor,lWidth,lOffset) ) 

#define ITVSPlaybackControl_RemoveOsdRectangle(This,lChID)	\
    ( (This)->lpVtbl -> RemoveOsdRectangle(This,lChID) ) 

#define ITVSPlaybackControl_get_KeepAspectRatio(This,lChID,bAspect)	\
    ( (This)->lpVtbl -> get_KeepAspectRatio(This,lChID,bAspect) ) 

#define ITVSPlaybackControl_put_KeepAspectRatio(This,lChID,bAspect)	\
    ( (This)->lpVtbl -> put_KeepAspectRatio(This,lChID,bAspect) ) 

#define ITVSPlaybackControl_GetChannelDuration(This,vGlobalId,vBegin,vEnd,value)	\
    ( (This)->lpVtbl -> GetChannelDuration(This,vGlobalId,vBegin,vEnd,value) ) 

#define ITVSPlaybackControl_SetBackupSpeed(This,value)	\
    ( (This)->lpVtbl -> SetBackupSpeed(This,value) ) 

#define ITVSPlaybackControl_GetAVIEstimatedSize(This,vGlobalId,lFlags,sPath,vBegin,vEnd,lDuration,vSize,bRes)	\
    ( (This)->lpVtbl -> GetAVIEstimatedSize(This,vGlobalId,lFlags,sPath,vBegin,vEnd,lDuration,vSize,bRes) ) 

#define ITVSPlaybackControl_SetAVIFileInfo(This,ChnlID,pInfo)	\
    ( (This)->lpVtbl -> SetAVIFileInfo(This,ChnlID,pInfo) ) 

#define ITVSPlaybackControl_StartNativeBackup(This,vGlobalId,lFlags,sPath,vBegin,vEnd,lDuration,vSize,bRes)	\
    ( (This)->lpVtbl -> StartNativeBackup(This,vGlobalId,lFlags,sPath,vBegin,vEnd,lDuration,vSize,bRes) ) 

#define ITVSPlaybackControl_StopNativeBackup(This,vGlobalId,bRes)	\
    ( (This)->lpVtbl -> StopNativeBackup(This,vGlobalId,bRes) ) 

#define ITVSPlaybackControl_GetNativeEstimatedSize(This,vGlobalId,lFlags,sPath,vBegin,vEnd,vSize,bRes)	\
    ( (This)->lpVtbl -> GetNativeEstimatedSize(This,vGlobalId,lFlags,sPath,vBegin,vEnd,vSize,bRes) ) 

#define ITVSPlaybackControl_OpenExternalStorage(This,sPath,lParam,bRes)	\
    ( (This)->lpVtbl -> OpenExternalStorage(This,sPath,lParam,bRes) ) 

#define ITVSPlaybackControl_CloseExternalStorage(This,bRes)	\
    ( (This)->lpVtbl -> CloseExternalStorage(This,bRes) ) 

#define ITVSPlaybackControl_IsDisplayInitialized(This)	\
    ( (This)->lpVtbl -> IsDisplayInitialized(This) ) 

#define ITVSPlaybackControl_GetRecordedChannelsForDuration(This,dStartDate,dStopDate,vvGlobalIDs,bResult)	\
    ( (This)->lpVtbl -> GetRecordedChannelsForDuration(This,dStartDate,dStopDate,vvGlobalIDs,bResult) ) 

#define ITVSPlaybackControl_OpenChannelWithAddress(This,bsAddr,lPort,lChID)	\
    ( (This)->lpVtbl -> OpenChannelWithAddress(This,bsAddr,lPort,lChID) ) 

#define ITVSPlaybackControl_FindChannelByAddress(This,bsAddr,lPort,llChID)	\
    ( (This)->lpVtbl -> FindChannelByAddress(This,bsAddr,lPort,llChID) ) 

#define ITVSPlaybackControl_SetCurrentTime(This,year,month,day,hour,minute,second)	\
    ( (This)->lpVtbl -> SetCurrentTime(This,year,month,day,hour,minute,second) ) 

#define ITVSPlaybackControl_GetRecordedChannels2(This,year,month,day,vvGlobalIDs,bResult)	\
    ( (This)->lpVtbl -> GetRecordedChannels2(This,year,month,day,vvGlobalIDs,bResult) ) 

#define ITVSPlaybackControl_ShowPlaybackTime(This,show,bResult)	\
    ( (This)->lpVtbl -> ShowPlaybackTime(This,show,bResult) ) 

#define ITVSPlaybackControl_SetDecoder(This,decoder)	\
    ( (This)->lpVtbl -> SetDecoder(This,decoder) ) 

#define ITVSPlaybackControl_GetDecoder(This,decoder)	\
    ( (This)->lpVtbl -> GetDecoder(This,decoder) ) 

#define ITVSPlaybackControl_GetAvailableDecoders(This,decoders)	\
    ( (This)->lpVtbl -> GetAvailableDecoders(This,decoders) ) 

#define ITVSPlaybackControl_LoadNetworkDrives(This,szConfig)	\
    ( (This)->lpVtbl -> LoadNetworkDrives(This,szConfig) ) 

#define ITVSPlaybackControl_GetDecodingTime(This,lChID,dTime)	\
    ( (This)->lpVtbl -> GetDecodingTime(This,lChID,dTime) ) 

#define ITVSPlaybackControl_GetMaxGopSize(This,lChID,size)	\
    ( (This)->lpVtbl -> GetMaxGopSize(This,lChID,size) ) 

#define ITVSPlaybackControl_PlayIFrame(This,dTime)	\
    ( (This)->lpVtbl -> PlayIFrame(This,dTime) ) 

#define ITVSPlaybackControl_StopIFramePlayback(This)	\
    ( (This)->lpVtbl -> StopIFramePlayback(This) ) 

#define ITVSPlaybackControl_GetChnlDescOldestLatestTime(This,vGlobalId,dDay,vvTimes,bRes)	\
    ( (This)->lpVtbl -> GetChnlDescOldestLatestTime(This,vGlobalId,dDay,vvTimes,bRes) ) 

#define ITVSPlaybackControl_PutCurrentTimeDirection(This,vDirection,bRes)	\
    ( (This)->lpVtbl -> PutCurrentTimeDirection(This,vDirection,bRes) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITVSPlaybackControl_INTERFACE_DEFINED__ */


#ifndef __ITVSIVSControl_INTERFACE_DEFINED__
#define __ITVSIVSControl_INTERFACE_DEFINED__

/* interface ITVSIVSControl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITVSIVSControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2F88F0C6-1126-4b65-ABBC-A5AE99AC5A43")
    ITVSIVSControl : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetLineCounter( 
            /* [in] */ INT_PTR lChnlID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RelearnBackground( 
            /* [in] */ INT_PTR lChnlID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartCellEdit( 
            /* [in] */ INT_PTR lChnlID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCellEditMode( 
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ BOOL bMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCellEditMode( 
            /* [in] */ INT_PTR lChnlID,
            /* [out] */ BOOL *pbMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCellEditColor( 
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ DWORD clrGrid,
            /* [in] */ DWORD clrCell) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCellEditColor( 
            /* [in] */ INT_PTR lChnlID,
            /* [out] */ DWORD *pclrGrid,
            /* [out] */ DWORD *pclrCell) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCellCount( 
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ DWORD dwRowsCount,
            /* [in] */ DWORD dwColumnsCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCellCount( 
            /* [in] */ INT_PTR lChnlID,
            /* [out] */ DWORD *pdwRowsCount,
            /* [out] */ DWORD *pdwColumnsCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCellData( 
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ DWORD dwRowsCount,
            /* [in] */ DWORD dwColumnsCount,
            /* [in] */ VARIANT vtarrbtAreaData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCellData( 
            /* [in] */ INT_PTR lChnlID,
            /* [out] */ DWORD *pdwRowsCount,
            /* [out] */ DWORD *pdwColumnsCount,
            /* [out] */ VARIANT *pvtarrbtAreaData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopCellEdit( 
            /* [in] */ INT_PTR lChnlID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCellData2( 
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ DWORD dwRowsCount,
            /* [in] */ DWORD dwColumnsCount,
            /* [in] */ BSTR bsAreaData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCellData2( 
            /* [in] */ INT_PTR lChnlID,
            /* [retval][out] */ VARIANT *pvtarrbtAreaData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartLineEdit( 
            /* [in] */ INT_PTR lChnlID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetLineEditColor( 
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ DWORD clrLine) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLineEditColor( 
            /* [in] */ INT_PTR lChnlID,
            /* [out] */ DWORD *pclrLine) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetLineEditEntryDirection( 
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ BOOL bUseDirection) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLineEditEntryDirection( 
            /* [in] */ INT_PTR lChnlID,
            /* [out] */ BOOL *pbUseDirection) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetLineData( 
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ DWORD dwPointCount,
            /* [in] */ VARIANT vtarrptLineData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLineData( 
            /* [in] */ INT_PTR lChnlID,
            /* [out] */ DWORD *pdwPointCount,
            /* [out] */ VARIANT *pvtarrptLineData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopLineEdit( 
            /* [in] */ INT_PTR lChnlID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetLineData2( 
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ long lStartX,
            /* [in] */ long lStartY,
            /* [in] */ long lEndX,
            /* [in] */ long lEndY) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLineData2( 
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ long type,
            /* [retval][out] */ long *lValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartAreaDisplay( 
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ BOOL bShowGrid,
            /* [in] */ DWORD clrGrid,
            /* [in] */ DWORD dwRowsCount,
            /* [in] */ DWORD dwColumnsCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddAreaDisplay( 
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ DWORD clrArea,
            /* [in] */ DWORD dwRowsCount,
            /* [in] */ DWORD dwColumnsCount,
            /* [in] */ VARIANT vtarrbtAreaData,
            /* [retval][out] */ LONG *plAreaID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAreaDisplay( 
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ LONG lAreaID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopAreaDisplay( 
            /* [in] */ INT_PTR lChnlID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartLineDisplay( 
            /* [in] */ INT_PTR lChnlID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddLineDisplay( 
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ DWORD clrLine,
            /* [in] */ float fThickness,
            /* [in] */ DWORD dwUseDirection,
            /* [in] */ DWORD dwPointCount,
            /* [in] */ VARIANT vtarrptLineData,
            /* [retval][out] */ LONG *plLineID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveLineDisplay( 
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ LONG lLineID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopLineDisplay( 
            /* [in] */ INT_PTR lChnlID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartIVSObjectDisplay( 
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ DWORD dwObjectMode,
            /* [in] */ DWORD clrObject,
            /* [in] */ DWORD clrDetectedObject,
            /* [in] */ BOOL bDrawTrail,
            /* [in] */ DWORD clrTrail) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopIVSObjectDisplay( 
            /* [in] */ INT_PTR lChnlID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartIVSCounterDisplay( 
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ DWORD dwFontSize,
            /* [in] */ DWORD clrFont,
            /* [in] */ DWORD dwPosition) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopIVSCounterDisplay( 
            /* [in] */ INT_PTR lChnlID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCellEditWidth( 
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ float fThickness) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetLineEditWidth( 
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ float fThickness) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITVSIVSControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITVSIVSControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITVSIVSControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITVSIVSControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITVSIVSControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITVSIVSControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITVSIVSControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITVSIVSControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ResetLineCounter )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RelearnBackground )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartCellEdit )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCellEditMode )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ BOOL bMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCellEditMode )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [out] */ BOOL *pbMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCellEditColor )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ DWORD clrGrid,
            /* [in] */ DWORD clrCell);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCellEditColor )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [out] */ DWORD *pclrGrid,
            /* [out] */ DWORD *pclrCell);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCellCount )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ DWORD dwRowsCount,
            /* [in] */ DWORD dwColumnsCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCellCount )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [out] */ DWORD *pdwRowsCount,
            /* [out] */ DWORD *pdwColumnsCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCellData )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ DWORD dwRowsCount,
            /* [in] */ DWORD dwColumnsCount,
            /* [in] */ VARIANT vtarrbtAreaData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCellData )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [out] */ DWORD *pdwRowsCount,
            /* [out] */ DWORD *pdwColumnsCount,
            /* [out] */ VARIANT *pvtarrbtAreaData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopCellEdit )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCellData2 )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ DWORD dwRowsCount,
            /* [in] */ DWORD dwColumnsCount,
            /* [in] */ BSTR bsAreaData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCellData2 )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [retval][out] */ VARIANT *pvtarrbtAreaData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartLineEdit )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetLineEditColor )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ DWORD clrLine);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLineEditColor )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [out] */ DWORD *pclrLine);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetLineEditEntryDirection )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ BOOL bUseDirection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLineEditEntryDirection )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [out] */ BOOL *pbUseDirection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetLineData )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ DWORD dwPointCount,
            /* [in] */ VARIANT vtarrptLineData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLineData )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [out] */ DWORD *pdwPointCount,
            /* [out] */ VARIANT *pvtarrptLineData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopLineEdit )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetLineData2 )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ long lStartX,
            /* [in] */ long lStartY,
            /* [in] */ long lEndX,
            /* [in] */ long lEndY);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLineData2 )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ long type,
            /* [retval][out] */ long *lValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartAreaDisplay )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ BOOL bShowGrid,
            /* [in] */ DWORD clrGrid,
            /* [in] */ DWORD dwRowsCount,
            /* [in] */ DWORD dwColumnsCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddAreaDisplay )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ DWORD clrArea,
            /* [in] */ DWORD dwRowsCount,
            /* [in] */ DWORD dwColumnsCount,
            /* [in] */ VARIANT vtarrbtAreaData,
            /* [retval][out] */ LONG *plAreaID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAreaDisplay )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ LONG lAreaID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopAreaDisplay )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartLineDisplay )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddLineDisplay )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ DWORD clrLine,
            /* [in] */ float fThickness,
            /* [in] */ DWORD dwUseDirection,
            /* [in] */ DWORD dwPointCount,
            /* [in] */ VARIANT vtarrptLineData,
            /* [retval][out] */ LONG *plLineID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveLineDisplay )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ LONG lLineID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopLineDisplay )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartIVSObjectDisplay )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ DWORD dwObjectMode,
            /* [in] */ DWORD clrObject,
            /* [in] */ DWORD clrDetectedObject,
            /* [in] */ BOOL bDrawTrail,
            /* [in] */ DWORD clrTrail);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopIVSObjectDisplay )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartIVSCounterDisplay )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ DWORD dwFontSize,
            /* [in] */ DWORD clrFont,
            /* [in] */ DWORD dwPosition);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopIVSCounterDisplay )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCellEditWidth )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ float fThickness);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetLineEditWidth )( 
            ITVSIVSControl * This,
            /* [in] */ INT_PTR lChnlID,
            /* [in] */ float fThickness);
        
        END_INTERFACE
    } ITVSIVSControlVtbl;

    interface ITVSIVSControl
    {
        CONST_VTBL struct ITVSIVSControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITVSIVSControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITVSIVSControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITVSIVSControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITVSIVSControl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITVSIVSControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITVSIVSControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITVSIVSControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ITVSIVSControl_ResetLineCounter(This,lChnlID)	\
    ( (This)->lpVtbl -> ResetLineCounter(This,lChnlID) ) 

#define ITVSIVSControl_RelearnBackground(This,lChnlID)	\
    ( (This)->lpVtbl -> RelearnBackground(This,lChnlID) ) 

#define ITVSIVSControl_StartCellEdit(This,lChnlID)	\
    ( (This)->lpVtbl -> StartCellEdit(This,lChnlID) ) 

#define ITVSIVSControl_SetCellEditMode(This,lChnlID,bMode)	\
    ( (This)->lpVtbl -> SetCellEditMode(This,lChnlID,bMode) ) 

#define ITVSIVSControl_GetCellEditMode(This,lChnlID,pbMode)	\
    ( (This)->lpVtbl -> GetCellEditMode(This,lChnlID,pbMode) ) 

#define ITVSIVSControl_SetCellEditColor(This,lChnlID,clrGrid,clrCell)	\
    ( (This)->lpVtbl -> SetCellEditColor(This,lChnlID,clrGrid,clrCell) ) 

#define ITVSIVSControl_GetCellEditColor(This,lChnlID,pclrGrid,pclrCell)	\
    ( (This)->lpVtbl -> GetCellEditColor(This,lChnlID,pclrGrid,pclrCell) ) 

#define ITVSIVSControl_SetCellCount(This,lChnlID,dwRowsCount,dwColumnsCount)	\
    ( (This)->lpVtbl -> SetCellCount(This,lChnlID,dwRowsCount,dwColumnsCount) ) 

#define ITVSIVSControl_GetCellCount(This,lChnlID,pdwRowsCount,pdwColumnsCount)	\
    ( (This)->lpVtbl -> GetCellCount(This,lChnlID,pdwRowsCount,pdwColumnsCount) ) 

#define ITVSIVSControl_SetCellData(This,lChnlID,dwRowsCount,dwColumnsCount,vtarrbtAreaData)	\
    ( (This)->lpVtbl -> SetCellData(This,lChnlID,dwRowsCount,dwColumnsCount,vtarrbtAreaData) ) 

#define ITVSIVSControl_GetCellData(This,lChnlID,pdwRowsCount,pdwColumnsCount,pvtarrbtAreaData)	\
    ( (This)->lpVtbl -> GetCellData(This,lChnlID,pdwRowsCount,pdwColumnsCount,pvtarrbtAreaData) ) 

#define ITVSIVSControl_StopCellEdit(This,lChnlID)	\
    ( (This)->lpVtbl -> StopCellEdit(This,lChnlID) ) 

#define ITVSIVSControl_SetCellData2(This,lChnlID,dwRowsCount,dwColumnsCount,bsAreaData)	\
    ( (This)->lpVtbl -> SetCellData2(This,lChnlID,dwRowsCount,dwColumnsCount,bsAreaData) ) 

#define ITVSIVSControl_GetCellData2(This,lChnlID,pvtarrbtAreaData)	\
    ( (This)->lpVtbl -> GetCellData2(This,lChnlID,pvtarrbtAreaData) ) 

#define ITVSIVSControl_StartLineEdit(This,lChnlID)	\
    ( (This)->lpVtbl -> StartLineEdit(This,lChnlID) ) 

#define ITVSIVSControl_SetLineEditColor(This,lChnlID,clrLine)	\
    ( (This)->lpVtbl -> SetLineEditColor(This,lChnlID,clrLine) ) 

#define ITVSIVSControl_GetLineEditColor(This,lChnlID,pclrLine)	\
    ( (This)->lpVtbl -> GetLineEditColor(This,lChnlID,pclrLine) ) 

#define ITVSIVSControl_SetLineEditEntryDirection(This,lChnlID,bUseDirection)	\
    ( (This)->lpVtbl -> SetLineEditEntryDirection(This,lChnlID,bUseDirection) ) 

#define ITVSIVSControl_GetLineEditEntryDirection(This,lChnlID,pbUseDirection)	\
    ( (This)->lpVtbl -> GetLineEditEntryDirection(This,lChnlID,pbUseDirection) ) 

#define ITVSIVSControl_SetLineData(This,lChnlID,dwPointCount,vtarrptLineData)	\
    ( (This)->lpVtbl -> SetLineData(This,lChnlID,dwPointCount,vtarrptLineData) ) 

#define ITVSIVSControl_GetLineData(This,lChnlID,pdwPointCount,pvtarrptLineData)	\
    ( (This)->lpVtbl -> GetLineData(This,lChnlID,pdwPointCount,pvtarrptLineData) ) 

#define ITVSIVSControl_StopLineEdit(This,lChnlID)	\
    ( (This)->lpVtbl -> StopLineEdit(This,lChnlID) ) 

#define ITVSIVSControl_SetLineData2(This,lChnlID,lStartX,lStartY,lEndX,lEndY)	\
    ( (This)->lpVtbl -> SetLineData2(This,lChnlID,lStartX,lStartY,lEndX,lEndY) ) 

#define ITVSIVSControl_GetLineData2(This,lChnlID,type,lValue)	\
    ( (This)->lpVtbl -> GetLineData2(This,lChnlID,type,lValue) ) 

#define ITVSIVSControl_StartAreaDisplay(This,lChnlID,bShowGrid,clrGrid,dwRowsCount,dwColumnsCount)	\
    ( (This)->lpVtbl -> StartAreaDisplay(This,lChnlID,bShowGrid,clrGrid,dwRowsCount,dwColumnsCount) ) 

#define ITVSIVSControl_AddAreaDisplay(This,lChnlID,clrArea,dwRowsCount,dwColumnsCount,vtarrbtAreaData,plAreaID)	\
    ( (This)->lpVtbl -> AddAreaDisplay(This,lChnlID,clrArea,dwRowsCount,dwColumnsCount,vtarrbtAreaData,plAreaID) ) 

#define ITVSIVSControl_RemoveAreaDisplay(This,lChnlID,lAreaID)	\
    ( (This)->lpVtbl -> RemoveAreaDisplay(This,lChnlID,lAreaID) ) 

#define ITVSIVSControl_StopAreaDisplay(This,lChnlID)	\
    ( (This)->lpVtbl -> StopAreaDisplay(This,lChnlID) ) 

#define ITVSIVSControl_StartLineDisplay(This,lChnlID)	\
    ( (This)->lpVtbl -> StartLineDisplay(This,lChnlID) ) 

#define ITVSIVSControl_AddLineDisplay(This,lChnlID,clrLine,fThickness,dwUseDirection,dwPointCount,vtarrptLineData,plLineID)	\
    ( (This)->lpVtbl -> AddLineDisplay(This,lChnlID,clrLine,fThickness,dwUseDirection,dwPointCount,vtarrptLineData,plLineID) ) 

#define ITVSIVSControl_RemoveLineDisplay(This,lChnlID,lLineID)	\
    ( (This)->lpVtbl -> RemoveLineDisplay(This,lChnlID,lLineID) ) 

#define ITVSIVSControl_StopLineDisplay(This,lChnlID)	\
    ( (This)->lpVtbl -> StopLineDisplay(This,lChnlID) ) 

#define ITVSIVSControl_StartIVSObjectDisplay(This,lChnlID,dwObjectMode,clrObject,clrDetectedObject,bDrawTrail,clrTrail)	\
    ( (This)->lpVtbl -> StartIVSObjectDisplay(This,lChnlID,dwObjectMode,clrObject,clrDetectedObject,bDrawTrail,clrTrail) ) 

#define ITVSIVSControl_StopIVSObjectDisplay(This,lChnlID)	\
    ( (This)->lpVtbl -> StopIVSObjectDisplay(This,lChnlID) ) 

#define ITVSIVSControl_StartIVSCounterDisplay(This,lChnlID,dwFontSize,clrFont,dwPosition)	\
    ( (This)->lpVtbl -> StartIVSCounterDisplay(This,lChnlID,dwFontSize,clrFont,dwPosition) ) 

#define ITVSIVSControl_StopIVSCounterDisplay(This,lChnlID)	\
    ( (This)->lpVtbl -> StopIVSCounterDisplay(This,lChnlID) ) 

#define ITVSIVSControl_SetCellEditWidth(This,lChnlID,fThickness)	\
    ( (This)->lpVtbl -> SetCellEditWidth(This,lChnlID,fThickness) ) 

#define ITVSIVSControl_SetLineEditWidth(This,lChnlID,fThickness)	\
    ( (This)->lpVtbl -> SetLineEditWidth(This,lChnlID,fThickness) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITVSIVSControl_INTERFACE_DEFINED__ */



#ifndef __TVSLib_LIBRARY_DEFINED__
#define __TVSLib_LIBRARY_DEFINED__

/* library TVSLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_TVSLib;

#ifndef ___ITVSLiveControlEvents_DISPINTERFACE_DEFINED__
#define ___ITVSLiveControlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ITVSLiveControlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ITVSLiveControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C3555312-A0C9-449C-A4CD-83C515F65DFB")
    _ITVSLiveControlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ITVSLiveControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ITVSLiveControlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ITVSLiveControlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ITVSLiveControlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ITVSLiveControlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ITVSLiveControlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ITVSLiveControlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ITVSLiveControlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ITVSLiveControlEventsVtbl;

    interface _ITVSLiveControlEvents
    {
        CONST_VTBL struct _ITVSLiveControlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ITVSLiveControlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _ITVSLiveControlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _ITVSLiveControlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _ITVSLiveControlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _ITVSLiveControlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _ITVSLiveControlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _ITVSLiveControlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ITVSLiveControlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TVSLiveControl;

#ifdef __cplusplus

class DECLSPEC_UUID("575A6BF1-1460-4907-9157-BECB7DCAC655")
TVSLiveControl;
#endif

#ifndef ___ITVSPlaybackControlEvents_DISPINTERFACE_DEFINED__
#define ___ITVSPlaybackControlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ITVSPlaybackControlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ITVSPlaybackControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0530937B-3487-4FC1-9030-9ABB6CFA53BA")
    _ITVSPlaybackControlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ITVSPlaybackControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ITVSPlaybackControlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ITVSPlaybackControlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ITVSPlaybackControlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ITVSPlaybackControlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ITVSPlaybackControlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ITVSPlaybackControlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ITVSPlaybackControlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ITVSPlaybackControlEventsVtbl;

    interface _ITVSPlaybackControlEvents
    {
        CONST_VTBL struct _ITVSPlaybackControlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ITVSPlaybackControlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _ITVSPlaybackControlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _ITVSPlaybackControlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _ITVSPlaybackControlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _ITVSPlaybackControlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _ITVSPlaybackControlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _ITVSPlaybackControlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ITVSPlaybackControlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TVSPlaybackControl;

#ifdef __cplusplus

class DECLSPEC_UUID("6E1B300A-119E-461D-9653-D6CBEF00B3E5")
TVSPlaybackControl;
#endif

#ifndef ___ITVSDecodeControlEvents_DISPINTERFACE_DEFINED__
#define ___ITVSDecodeControlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ITVSDecodeControlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ITVSDecodeControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("770BD7DB-5024-4c28-9BBA-520B284EF508")
    _ITVSDecodeControlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ITVSDecodeControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ITVSDecodeControlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ITVSDecodeControlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ITVSDecodeControlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ITVSDecodeControlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ITVSDecodeControlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ITVSDecodeControlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ITVSDecodeControlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ITVSDecodeControlEventsVtbl;

    interface _ITVSDecodeControlEvents
    {
        CONST_VTBL struct _ITVSDecodeControlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ITVSDecodeControlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _ITVSDecodeControlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _ITVSDecodeControlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _ITVSDecodeControlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _ITVSDecodeControlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _ITVSDecodeControlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _ITVSDecodeControlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ITVSDecodeControlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TVSDecodeControl;

#ifdef __cplusplus

class DECLSPEC_UUID("CA1B836A-156F-40bd-A2F5-F7AABEFAD692")
TVSDecodeControl;
#endif
#endif /* __TVSLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


