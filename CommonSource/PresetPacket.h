
#pragma once
#ifndef PRESET_PACKET_DEFINE_H
#define PRESET_PACKET_DEFINE_H


#define PROTO_STX  0x02
#define PROTO_ETX  0x03
#define PRESET_NAME_LEN 30

typedef struct _PRESET_PACKET
{
	_PRESET_PACKET(void)
	{
		bySTX = PROTO_STX;

		nNo = 0;
		ZeroMemory(&cstrSrcName, sizeof(cstrSrcName));
		nPresetTourStayTime = 0;

		dRelativePan = 0;
		dAbsolutePan = 0;
		dRelativeTilt = 0;
		dAbsoluteTilt = 0;

		nAbsHighMagnifZoomMotor = 0;
		nAbsHighMagnifFocusMotor = 0;

		bBeginning = FALSE;
		bEnd = FALSE;

		byETX = PROTO_ETX;
	}

	BYTE bySTX;

#if 1
	int nNo;
	char cstrSrcName[PRESET_NAME_LEN];
	int nPresetTourStayTime;
	double dRelativePan;
	double dAbsolutePan;
	double dRelativeTilt;
	double dAbsoluteTilt;

	int nAbsHighMagnifZoomMotor;
	int nAbsHighMagnifFocusMotor;

	BOOL bBeginning;
	BOOL bEnd;
#endif

	BYTE byETX;

}PRESET_PACKET;

#endif