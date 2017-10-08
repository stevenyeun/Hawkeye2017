#ifndef IPCDEFINE_H
#define IPCDEFINE_H

//HwakeyePG -> HWAKEYE_MANAGER
#define TO_IPC_HWAKEEYEMANAGERPG_CAMINFO		1
#define TO_IPC_HWAKEEYEMANAGERPG_TARGETINFO		2
#define TO_IPC_HWAKEEYEMANAGERPG_SHOWWINDOW		3

//HWAKEYE_MANAGER -> HwakeyePG
#define TO_IPC_HWAKEEYEPG_CMDAUTHSTATUS			1
#define TO_IPC_HWAKEEYEPG_CONTROLCMD			2

//HWAKEYE_MANAGER -> HWAKEYE_GIS 
#define TO_IPC_HWAKEEYEGIS_CAMINFO		1
#define TO_IPC_HWAKEEYEGIS_TARGETINFO	2


//COORD : coordinates : 좌표 : x, y, z 
#define EAST_BYTE 0x00
#define WEST_BYTE 0x01

#define NORTH_BYTE 0x00
#define SOUTH_BYTE 0x01

typedef struct _IPC_COORDINFO
{
	_IPC_COORDINFO(void)
	{
		byLongSign=0x00;	// E
		byLongDeg=0x00;
		byLongMin=0x00;
		byLongSec=0x00;
		byLongSecFrac=0x00;

		byLatSign =0x00;     // N
		byLatDeg=0x00;
		byLatMin=0x00;
		byLatSec=0x00;
		byLatSecFrac=0x00;
		uAltitude = 0x00; //고도값  0   해수면의 높이 
		uDistance=0;
	}
	BYTE byLongSign;//0 ==>”E” , 1 ==>“W”
	BYTE byLongDeg;//도
	BYTE byLongMin;//분
	BYTE byLongSec;//초
	BYTE byLongSecFrac;//초 단위 소수

	BYTE byLatSign; //0 ==>”N” , 1 ==>“S”
	BYTE byLatDeg;
	BYTE byLatMin;
	BYTE byLatSec;
	BYTE byLatSecFrac;

	UINT uAltitude;
	UINT uDistance;//카메라부터와의거리
}IPC_COORDINFO;


typedef struct _IPC_CAMINFO
{
	_IPC_CAMINFO(void)
	{
		byCamType = 0x00;
		fPan=0;
		fTilt=0;
		fFovW=0;		
		uSuvailRange=0;
		fSpd=0;

		ZeroMemory(&coordinfo,sizeof(IPC_COORDINFO));	
	}
	IPC_COORDINFO coordinfo;//위치 정보

	BYTE byCamType;//0x01:고배율, 0x02:저배율, 0x03:열영상 
	float fPan;
	float fTilt;
	float fFovW;
	UINT  uSuvailRange;
	float fSpd;

}IPC_CAMINFO;

#endif