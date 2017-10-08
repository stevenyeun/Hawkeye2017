
#pragma once

#ifndef AUTHORITY_PACKET_DEFINE_H
#define AUTHORITY_PACKET_DEFINE_H

#include "CommonDefine.h"
//IDX
#define IDX_STX		 0
#define IDX_LEN		 1
#define IDX_SENDDEV  2
#define IDX_CMDGROUP 3
#define IDX_CMDTYPE	 4
#define IDX_CMDVAL1  5
#define IDX_CMDVAL2  6
#define IDX_ETX		 7

//Length
#define SRC_NAME_LEN 20
#define AUTHORITY_DATA_LEN 40
// Data Field Define
//
#define PROTO_STX 0x02
#define PROTO_ETX 0x03
typedef unsigned char BYTE;

typedef struct _AUTHORITY_DATA
{
	_AUTHORITY_DATA()
	{
		ZeroMemory(data, sizeof(data));
	}
	BYTE data[AUTHORITY_DATA_LEN];
}AUTHORITY_DATA;

typedef struct _SOURCE_NAME
{
	char name[SRC_NAME_LEN];
}SOURCE_NAME;

//제어권 서버 < -> 제어권 클라이언트 프로토콜 구조체
typedef struct _AUTHORITY_PACKET
{
	_AUTHORITY_PACKET(void)
	{
		bySTX = PROTO_STX;
		ZeroMemory(&srcName, sizeof(srcName));
		byCmdGroup = 0x00;
		byCmdType = 0x00;
		ZeroMemory(&authorityData, sizeof(authorityData));
		byETX = PROTO_ETX;

	}
	BYTE bySTX;
	SOURCE_NAME srcName;
	BYTE byCmdGroup;
	BYTE byCmdType;
	AUTHORITY_DATA authorityData;
	BYTE byETX;

}AUTHORITY_PACKET;

//접속자 리스트뷰에서 사용
typedef struct _AUTHORITY_CLIENT_INFO
{
	_AUTHORITY_CLIENT_INFO(void)
	{
		ZeroMemory(&connectioninfo, sizeof(connectioninfo));
		ZeroMemory(cstrSrcName, sizeof(cstrSrcName));
	}

	IP_PORT connectioninfo;
	char cstrSrcName[SRC_NAME_LEN];

}AUTHORITY_CLIENT_INFO;
//char to CString
//CString ParseAuthorityData(AUTHORITY_DATA authorityData);
CString ParseAuthorityData2(AUTHORITY_DATA authorityData);
int ParseAuthorityDataToInt(AUTHORITY_DATA authorityData);
double ParseAuthorityDataToDouble(AUTHORITY_DATA authorityData);

void MakeAuthorityData(int nData, AUTHORITY_DATA& authData);//int 변수를 제어권 데이터에 넣기
void MakeAuthorityData(double nData, AUTHORITY_DATA& authData);//double 변수를 제어권 데이터에 넣기
/////////////////////////////////////////////////////////////////////

//byCmdGroup
#define CMDGROUP_AUTHORITY 0x01

	#define CMDTYPE_AUTHORITY_LOGIN									1
	#define CMDTYPE_AUTHORITY_REQUEST								2
	#define CMDTYPE_AUTHORITY_AUTHORIZATION 						3
	#define CMDTYPE_AUTHORITY_DEPRIVATION							4
	#define CMDTYPE_AUTHORITY_TEMPAUTHORITY_USE_NOTIFICATION		5
	#define CMDTYPE_AUTHORITY_TEMPAUTHORITY_RETURN_NOTIFICATION		6
	#define CMDTYPE_AUTHORITY_TEMPAUTHORITY_INUSE_NOTIFICATION		7
//////////////////////////////////////////


#define CMDGROUP_PTZCTRL 0x02
//Control Client -> Control Server
	#define CMDTYPE_PTZCTRL_PAN_LEFT			1
	#define CMDTYPE_PTZCTRL_PAN_RIGHT			2
	#define CMDTYPE_PTZCTRL_TILT_UP				3
	#define CMDTYPE_PTZCTRL_TILT_DOWN			4
	#define CMDTYPE_PTZCTRL_PT_LU				5
	#define CMDTYPE_PTZCTRL_PT_RU				6
	#define CMDTYPE_PTZCTRL_PT_LD				7
	#define CMDTYPE_PTZCTRL_PT_RD				8
	#define CMDTYPE_PTZCTRL_PAN_STOP			9
	#define CMDTYPE_PTZCTRL_TILT_STOP			10
	#define CMDTYPE_PTZCTRL_PT_STOP				11

	#define CMDTYPE_PTZCTRL_ZOOM_TELE			12
	#define CMDTYPE_PTZCTRL_ZOOM_WIDE			13
	#define CMDTYPE_PTZCTRL_ZOOM_STOP			14
	#define CMDTYPE_PTZCTRL_FOCUS_NEAR			15
	#define CMDTYPE_PTZCTRL_FOCUS_FAR			16
	#define CMDTYPE_PTZCTRL_FOCUS_STOP			17

	#define CMDTYPE_PTZCTRL_PT_SPEED			18
	#define CMDTYPE_PTZCTRL_ZOOM_SPEED			19
	#define CMDTYPE_PTZCTRL_FOCUS_SPEED			20
	#define CMDTYPE_PTZCTRL_PRESET_SPEED		21
//////////////////////////////////////////

#define CMDGROUP_PTZREQ 0x03
	#define CMDTYPE_PTZREQ_PANTILT_POS_REQ		1
	#define CMDTYPE_PTZREQ_PANTILT_POS_RESP		2

	#define CMDTYPE_PTZREQ_DAYZF_POS_REQ		3
	#define CMDTYPE_PTZREQ_DAYZF_POS_RESP		4

	#define CMDTYPE_PTZREQ_PAN_MOTORSTATUS_REQ	5
	#define CMDTYPE_PTZREQ_PAN_INITSTATUS_RESP	6
	#define CMDTYPE_PTZREQ_PAN_MOVESTATUS_RESP	7

	#define CMDTYPE_PTZREQ_TILT_STATUS_REQ		8
	#define CMDTYPE_PTZREQ_TILT_STATUS_RESP		9

	#define CMDTYPE_PTZREQ_ZF_STATUS_REQ		10
	#define CMDTYPE_PTZREQ_ZF_STATUS_RESP		11

	#define CMDTYPE_PTZREQ_MAINBOARD_STATUS_RESP	12
#if 0
Day Zoom Pos Req
Day Zoom Pos Resp
Day Focus Pos Req
Day Focus Pos Resp
Pan Status Req
Pan Status Resp
Tilt Status Req
Tilt Status Resp
Day Z / F Status Req
Day Z / F Status Resp
#endif
//////////////////////////////////////////

#define CMDGROUP_DAYCAM 0x04
#define CMDTYPE_DAYCAM_EXTENDTER 1
#define CMDTYPE_DAYCAM_IRIS 2
//#define CMDTYPE_DAYCAM_COLOR_MODE 1
//#define CMDTYPE_DAYCAM_BW_MODE 2
//////////////////////////////////////////

//Thermal Camera
#define CMDGROUP_THERMCAM 0x05
#define CMDTYPE_THERMCAM_WHITE_HOT 1
#define CMDTYPE_THERMCAM_BLACK_HOT 2

#define CMDTYPE_THERMCAM_COLOR 3

#define CMDTYPE_THERMCAM_DZOOM 4
#define CMDTYPE_THERMCAM_DZOOM_REQ 5
#define CMDTYPE_THERMCAM_DZOOM_RESP 6

#define CMDTYPE_THERMCAM_NUC 7

#define CMDTYPE_THERMCAM_AGCMODE 8
#define CMDTYPE_THERMCAM_AGCMODE_REQ 9
#define CMDTYPE_THERMCAM_AGCMODE_RESP 10

#define CMDTYPE_THERMCAM_CONTRAST 11
#define CMDTYPE_THERMCAM_CONTRAST_REQ 12
#define CMDTYPE_THERMCAM_CONTRAST_RESP 13

#define CMDTYPE_THERMCAM_BRIGHTNESS 14
#define CMDTYPE_THERMCAM_BRIGHTNESS_REQ 15
#define CMDTYPE_THERMCAM_BRIGHTNESS_RESP 16

#define CMDTYPE_THERMCAM_DDE 17
#define CMDTYPE_THERMCAM_DDE_REQ 18
#define CMDTYPE_THERMCAM_DDE_RESP 19

#define CMDTYPE_THERMCAM_ACE 20
#define CMDTYPE_THERMCAM_ACE_REQ 21
#define CMDTYPE_THERMCAM_ACE_RESP 22

#define CMDTYPE_THERMCAM_SSO 23
#define CMDTYPE_THERMCAM_SSO_REQ 24
#define CMDTYPE_THERMCAM_SSO_RESP 25
//////////////////////////////////////////

//Power Mgt
#define CMDGROUP_POWERMGT  0x06
#define CMDTYPE_POWERMGT_SYS_PWR_CTL  1
#define CMDTYPE_POWERMGT_SYS_PWR_STATUS  2
#define CMDTYPE_POWERMGT_THERMCAM_PWR_CTL  3
#define CMDTYPE_POWERMGT_THERMCAM_STATUS  4

//PanTilt Init
#define CMDGROUP_PANTILTINIT 0x07
#define CMDTYPE_PANTILTINIT_MOVE_HOMEPOS 1
#define CMDTYPE_PANTILTINIT_REQ_HOMEPOS 2
#define CMDTYPE_PANTILTINIT_RESP_HOMEPOS 3
#define CMDTYPE_PANTILTINIT_SYNC_HOMEPOS 4

//PTZ AbsMove
#define CMDGROUP_PTZFABSMOVE 0x08
#define CMDTYPE_PTZFABSMOVE_MOVE 1
#define CMDTYPE_PTZFABSMOVE_SAVE_POS  2
#define CMDTYPE_PTZFABSMOVE_MOVE_SAVEPOS 3
#define CMDTYPE_PTZFABSMOVE_REQ_SAVEPOS 4
#define CMDTYPE_PTZFABSMOVE_RESP_SAVEPOS 5

//기타기능
//////////////////////////////////////////
#define CMDGROUP_ETCFUNC 0x09

#define CMDTYPE_ETCFUNC_PANTILT_INIT 1
#define CMDTYPE_ETCFUNC_PANTILT_INIT_STATUS 2
#define CMDTYPE_ETCFUNC_PANTILT_MOTOR_ADJUSTMENT_STATUS 3
#define CMDTYPE_ETCFUNC_PRESET_CTL 4
#define CMDTYPE_ETCFUNC_PRESET_STATUS 5
#define CMDTYPE_ETCFUNC_SET_PAN_OFFSET 6
#define CMDTYPE_ETCFUNC_SET_TILT_OFFSET 7
#define CMDTYPE_ETCFUNC_REQ_GPS_VAL 8
#define CMDTYPE_ETCFUNC_REQ_GPS_LAT 9
#define CMDTYPE_ETCFUNC_REQ_GPS_LONG 10
#define CMDTYPE_ETCFUNC_SET_LAT_POS 11
#define CMDTYPE_ETCFUNC_SET_LONG_POS 12

//////////////////////////////////////////


//ETC Device
#define CMDGROUP_ETC_DEVICE 0x0A
#define CMDTYPE_ETC_HIGHLENS_FILTER 1
//////////////////////////////////////////


/*
#define CMDGROUP_ETC_LINK 0x08
//////////////////////////////////////////

//cmdval1
#define CMDVAL_CONTROLING	0x01
#define CMDVAL_WAITING		0x02
*/


//Command Authority Client -> Command Authority Server




//Control Server - > Control Client





CString ConvertAuthorityPacketToString(const AUTHORITY_PACKET * pAuthorityPacket);


#endif