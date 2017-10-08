
#include "StdAfx.h"
#include "ProtoFlirTau2.h"
#include "crc16.h"
#include <math.h>


double round( double value, int pos )
{
	double temp;
	temp = value * pow( 10, (double)pos );  // 원하는 소수점 자리수만큼 10의 누승을 함
	temp = floor( temp + 0.5 );          // 0.5를 더한후 버림하면 반올림이 됨
	temp *= pow( 10, (double)-pos );           // 다시 원래 소수점 자리수로
	return temp;
}

CProtoFlirTau2::CProtoFlirTau2(void)
{
}

CProtoFlirTau2::~CProtoFlirTau2(void)
{
}

int CProtoFlirTau2::SetDigitalZoom(BYTE* pBuf, double dZoom)
{
	//0x0001: Set zoom width to specified value

	//Bytes 2-3: Specified value
	//줌 배율값 commented by yeun
	WORD wWidthPixel = (WORD)round( 640 / dZoom, 0 );

	return SetCommand( pBuf, FUNC_DZOOM, FUNC_DZOOM_ARGU_LEN, 0x0001, wWidthPixel );

	//test 
	/*
	DWORD word;
	word = MAKEWORD(0x80, 0x02);//1x = 640
	word = MAKEWORD(0x46, 0x02);//1.1x = 640/1.1 = 581.81(calc value) = 582(flir sw value by round)
	word = MAKEWORD(0x15, 0x02);//1.2x = 640/1.2 = 533.33(calc value) = 533(flir sw value by round)
	*/		
}
int CProtoFlirTau2::ReqDigitalZoom(BYTE* pBuf)
{
	return SetCommand( pBuf, FUNC_DZOOM );
}
double CProtoFlirTau2::ParseDigitalZoomPacket(BYTE* pBuf)
{
	DWORD word;
	//1x = 640
	word = MAKEWORD(pBuf[PROTO_IDX_ARGUMENT_START+1], pBuf[PROTO_IDX_ARGUMENT_START]);
	return (double) (640.0 / word);
}

int CProtoFlirTau2::SetVideoPalette(BYTE* pBuf, WORD wPaletteNumber)
{
	return SetCommand( pBuf, FUNC_VIDEOPALETTE, FUNC_VIDEOPALETTE_ARGU_LEN, wPaletteNumber );
}

int CProtoFlirTau2::SetAGCMode(BYTE * pBuf, WORD wAGCMode)
{
	
	return SetCommand(pBuf, FUNC_SET_AGCTYPE, FUNC_SET_AGCTYPE_ARGU_LEN, wAGCMode);
}

int CProtoFlirTau2::SetContrast(BYTE * pBuf, WORD wContrast)
{
	return SetCommand(pBuf, FUNC_SET_CONTRAST, FUNC_SET_CONTRAST_ARGU_LEN, wContrast);
}

int CProtoFlirTau2::ReqContrast(BYTE * pBuf)
{
	return SetCommand(pBuf, FUNC_SET_CONTRAST, 0, 0);
}

int CProtoFlirTau2::SetBrightness(BYTE * pBuf, WORD wBrightness)
{
	return SetCommand(pBuf, FUNC_SET_BRIGHTNESS, FUNC_SET_BRIGHTNESS_ARGU_LEN, wBrightness);
}

int CProtoFlirTau2::ReqBrightness(BYTE * pBuf)
{
	return SetCommand(pBuf, FUNC_SET_BRIGHTNESS, 0, 0);
}

int CProtoFlirTau2::SetBaudRate(BYTE* pBuf, int iBaud)
{
	WORD wArgu = 0x0000;
	if( iBaud == 0 )
		wArgu = 0x0000;
	else if(iBaud == 9600)
		wArgu = 0x0001;
	else if(iBaud == 19200)
		wArgu = 0x0002;
	else if(iBaud == 28800)
		wArgu = 0x0003;
	else if(iBaud == 57600)
		wArgu = 0x0004;
	else if(iBaud == 115200)
		wArgu = 0x0005;
	else if(iBaud == 460800)
		wArgu = 0x0006;
	else if(iBaud == 921600)
		wArgu = 0x0007;

	return SetCommand( pBuf, FUNC_BAUD, FUNC_SETBAUD_ARGU_LEN, wArgu );

	//SetCommand1(pBuf, FUNC_SETBAUD, FUNC_SETBAUD_ARGU_LEN);
	
	/*
	0x0000: Auto baud
	0x0001: 9600 baud
	0x0002: 19200 baud
	0x0003: 28800 baud
	0x0004: 57600 baud
	0x0005: 115200 baud
	0x0006: 460800 baud
	0x0007: 921600 baud
	*/

	/*

	pBuf[PROTO_IDX_ARGUMENT_START]		= HIBYTE(wArgu);
	pBuf[PROTO_IDX_ARGUMENT_START+1]	= LOBYTE(wArgu);

	DWORD wCRC = 0;
	wCRC = crc16_ccitt(pBuf, PROTO_IDX_ARGUMENT_START + FUNC_SETBAUD_ARGU_LEN );

	pBuf[PROTO_IDX_ARGUMENT_START + FUNC_SETBAUD_ARGU_LEN]	= HIBYTE(wCRC);
	pBuf[PROTO_IDX_ARGUMENT_START + FUNC_SETBAUD_ARGU_LEN+1]= LOBYTE(wCRC);


	return FUNC_SETBAUD_PROTO_LEN;
	*/
}
int CProtoFlirTau2::ReqBaudRate(BYTE* pBuf)
{
	//6E 00 00 07 00 00 5A 2B 00 00
	return SetCommand(pBuf, FUNC_BAUD, FUNC_GETBAUD_ARGU_LEN);
	//recv format
	//baud 9600 : 6E 00 00 07 00 02 7A 69 00 01 10 21
}
int CProtoFlirTau2::SaveSettings(BYTE* pBuf)
{	
	//6E 00 00 C4 00 00 25 8C 00 00 
	return SetCommand(pBuf, FUNC_MEMSTATUS, FUNC_MEMSTATUS_ARGU_LEN);
}

int CProtoFlirTau2::SetDefault(BYTE* pBuf)
{
	//6E 00 00 01 00 00 E8 8B 00 00 
	return SetCommand(pBuf, FUNC_SETDEFAULT, FUNC_SETDEFAULT_ARGU_LEN);	
}

int CProtoFlirTau2::SetDdeMode( BYTE* pBuf, WORD word )
{
	return SetCommand(pBuf, FUNC_SETDDEMODE, FUNC_SETDDEMODE_ARGU_LEN, word);
}

int CProtoFlirTau2::SetDdeThreshold( BYTE* pBuf, WORD word )
{
	//return SetCommand(pBuf, FUNC_SETDDETHRESHOLD, FUNC_SETDDETHRESHOLD_ARGU_LEN, word);
	return SetCommand(pBuf, FUNC_SETDDEMODE, FUNC_SETDDETHRESHOLD_ARGU_LEN, word);
}

int CProtoFlirTau2::SetDdeGain( BYTE* pBuf, WORD word )
{
	return SetCommand(pBuf, FUNC_SETDDEGAIN, FUNC_SETDDEGAIN_ARGU_LEN, word);
}
int CProtoFlirTau2::SetCommand(BYTE* pBuf, int iCmd, int iArguLen, WORD wArgu1, WORD wArgu2)
{
	SetCommand1( pBuf, iCmd, iArguLen);
	return SetCommand2( pBuf, wArgu1, wArgu2 );
}
void CProtoFlirTau2::SetCommand1(BYTE* pBuf, int iCmd, int iArguLen)
{
	pBuf[PROTO_IDX_PROCESSCODE] 	= PROCESSCODE;
	pBuf[PROTO_IDX_STATUS]			= STATUS_CAMOK;
	pBuf[PROTO_IDX_RESERVED]		= RESERVED;

	pBuf[PROTO_IDX_FUNCTION]		= iCmd;//command

	pBuf[PROTO_IDX_BYTECOUNT_M] 	= HIBYTE( iArguLen );
	pBuf[PROTO_IDX_BYTECOUNT_L] 	= LOBYTE( iArguLen );

	WORD wCRC = crc16_ccitt(pBuf, CRC1_PART_LEN);

	pBuf[PROTO_IDX_CRC1_M] 	= HIBYTE( wCRC );
	pBuf[PROTO_IDX_CRC1_L] 	= LOBYTE( wCRC );
}
int CProtoFlirTau2::SetCommand2(BYTE* pBuf, WORD wArgu1, WORD wArgu2)
{
	int iIdx = 0;

	if( wArgu1 != MAXWORD )
	{
		pBuf[PROTO_IDX_ARGUMENT_START + iIdx++]	= HIBYTE(wArgu1);
		pBuf[PROTO_IDX_ARGUMENT_START + iIdx++]	= LOBYTE(wArgu1);
	}
	if( wArgu2 != MAXWORD )
	{
		pBuf[PROTO_IDX_ARGUMENT_START + iIdx++]	= HIBYTE(wArgu2);
		pBuf[PROTO_IDX_ARGUMENT_START + iIdx++]	= LOBYTE(wArgu2);
	}

	WORD wCRC = 0;
	wCRC = crc16_ccitt(pBuf, PROTO_IDX_ARGUMENT_START + iIdx );

	pBuf[PROTO_IDX_ARGUMENT_START + iIdx++]	= HIBYTE(wCRC);
	pBuf[PROTO_IDX_ARGUMENT_START + iIdx++]	= LOBYTE(wCRC);

	return PROTO_IDX_ARGUMENT_START+iIdx;
}
