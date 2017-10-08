#pragma once

#include <windef.h>

#define PROTO_IDX_PROCESSCODE 0
#define PROTO_IDX_STATUS 1
/*
0x00 CAM_OK Message received
0x03 CAM _RANGE_ERROR Argument out of range
0x04 CAM _CHECKSUM_ERROR Header or message-body checksum error
0x05 CAM _UNDEFINED_PROCESS_ERROR Unknown process code
0x06 CAM _UNDEFINED_FUNCTION_ERROR Unknown function code
0x07 CAM _TIMEOUT_ERROR Timeout executing serial command
0x09 CAM _BYTE_COUNT_ERROR BYTE count incorrect for the function code
0x0A CAM _FEATURE_NOT_ENABLED Function code not enabled in the current configuration
*/
#define PROTO_IDX_RESERVED 2
#define PROTO_IDX_FUNCTION 3
#define PROTO_IDX_BYTECOUNT_M 4
#define PROTO_IDX_BYTECOUNT_L 5
#define PROTO_IDX_CRC1_M 6
#define PROTO_IDX_CRC1_L 7
#define PROTO_IDX_ARGUMENT_START 8



#define CRC1_PART_LEN 6// array index 0~5


//BYTE code list
#define PROCESSCODE 0x6E

//status BYTE list
#define STATUS_CAMOK 0x00

//reseved BYTE
#define RESERVED 0x00

//function BYTE list

//digital zoom
#define FUNC_DZOOM 0x32
#define FUNC_DZOOM_ARGU_LEN 0x0004
//#define FUNC_DZOOM_PROTO_LEN 14
//

//setbaud zoom
#define FUNC_BAUD 0x07

#define FUNC_SETBAUD_ARGU_LEN 0x0002
#define FUNC_GETBAUD_ARGU_LEN 0x0000

//#define FUNC_SETBAUD_PROTO_LEN 12
//#define FUNC_GETBAUD_PROTO_LEN 10
//

//video palette
#define FUNC_VIDEOPALETTE 0x10
#define FUNC_VIDEOPALETTE_ARGU_LEN 0x0002
//

//memory status(save setting)
#define FUNC_MEMSTATUS 0xC4
#define FUNC_MEMSTATUS_ARGU_LEN 0x0000
//#define FUNC_MEMSTATUS_PROTO_LEN 10


//setDefault
#define FUNC_SETDEFAULT 0x01
#define FUNC_SETDEFAULT_ARGU_LEN 0x0000
//#define FUNC_SETDEFAULT_PROTO_LEN 12

//  [4/7/2014 Yeun]
//DDE
#define FUNC_SETDDEMODE 0xE3
#define FUNC_SETDDEMODE_ARGU_LEN 0x0002

#define FUNC_SETDDEGAIN 0x2C/*Note: Set capability has no effect in automatic DDE mode. (See SPATIAL_THRESHOLD, 0xE3.)*/
#define FUNC_SETDDEGAIN_ARGU_LEN 0x0002

#define FUNC_SETDDETHRESHOLD 0xE2//0~255
#define FUNC_SETDDETHRESHOLD_ARGU_LEN 0x0002
//

//steven 170411
#define FUNC_SET_AGCTYPE 0x13 
#define FUNC_SET_AGCTYPE_ARGU_LEN 0x0002 

#define FUNC_SET_CONTRAST 0x14
#define FUNC_SET_CONTRAST_ARGU_LEN 0x0002

#define FUNC_SET_BRIGHTNESS 0x15
#define FUNC_SET_BRIGHTNESS_ARGU_LEN 0x0002

class CProtoFlirTau2
{
public:
	CProtoFlirTau2(void);
	~CProtoFlirTau2(void);
public:
	static int SetDigitalZoom(BYTE* pBuf, double wZoom);
	static int ReqDigitalZoom(BYTE* pBuf);
	static double ParseDigitalZoomPacket(BYTE* pBuf);
	static int SetVideoPalette(BYTE* pBuf, WORD wPaletteNumber);//0x0000 (Palette 0 = white hot)

	static int SetAGCMode(BYTE* pBuf, WORD wAGCMode);//Steven 170411
	
	
	static int SetContrast(BYTE* pBuf, WORD wContrast);//Steven 170411
	static int ReqContrast(BYTE* pBuf);//Steven 170411
	static int SetBrightness(BYTE* pBuf, WORD wBrightness);//Steven 170411
	static int ReqBrightness(BYTE* pBuf);//Steven 170411

	static int SetDdeMode(BYTE* pBuf, WORD word);
	static int SetDdeThreshold(BYTE* pBuf, WORD word);
	static int SetDdeGain(BYTE* pBuf, WORD word);
public:
	static int SetBaudRate(BYTE* pBuf, int iBaud = 0);
	static int ReqBaudRate(BYTE* pBuf);
	static int SetDefault(BYTE* pBuf);
	static int SaveSettings(BYTE* pBuf);
	
	static int SetCommand(BYTE* pBuf, int iCmd, int iArguLen=0, WORD wArgu1=MAXWORD, WORD wArgu2=MAXWORD);
private:
	static void SetCommand1(BYTE* pBuf, int iCmd, int iArguLen);//CRC1까지 설정
	static int SetCommand2(BYTE* pBuf, WORD wArgu1=MAXWORD, WORD wArgu2=MAXWORD);//CRC2까지 설정
};
