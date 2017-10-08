#include "StdAfx.h"
#include "U2SRProtoParser.h"


//yeun 20140130
#include "U2SRProtoDef.h"
//
//#include "MultiSensorComm.h"




CU2SRProtoParser::CU2SRProtoParser()
{
	//  [4/6/2014 Yeun]
/*
	m_iProtoThermCam = THERMCAM_CANTRONIC;
	m_iProtoHighCam = BOXCAM_HITACHI*/

}

CU2SRProtoParser::~CU2SRProtoParser()
{
}

int CU2SRProtoParser::GetCmd( LPBYTE lpData, CString& strParsedCmd)
{
	

	if(lpData[IDX0_STA_CODE] == START_CODE)
	{
		if( lpData[IDX1_SRC_ID] == SRC_ID )
		{
			if( lpData[IDX2_DEV_ID] == DEV_ID )
			{
				//if( lpData[IDX3_ASK_FRM] == SET_OK || lpData[IDX3_ASK_FRM] == GET_OK )
				//{
					CString wcslen;
					wcslen.Format(_T("%c%c"), lpData[IDX4_CMD_LEN], lpData[IDX5_CMD_LEN]);
					
					
#if 0
					int iLen = atoi(wcslen);
#else
					int iLen = _wtoi(wcslen);
#endif

					for ( int i=0; i<iLen; i++ )
					{
						strParsedCmd +=lpData[IDX6_CMD_DATA+i];
					}
					const char chData[1] = { lpData[IDX3_ASK_FRM] };
					return atoi(chData);
				//}
				//else//에러일때
				//{
				//	strParsedCmd.Format( _T("%c"), lpData[IDX3_ASK_FRM] );
				//}
			}
		}
	}



	return -1;
}
void CU2SRProtoParser::FillHeader( BYTE* pbyBuffer )
{
	memset( pbyBuffer, 0x00, PROTO_BUFFER_SIZE );
}
int CU2SRProtoParser::FillTail( BYTE* pbyBuffer, int iDataLen )
{
	ASSERT(iDataLen>=2);
	memset(pbyBuffer+iDataLen, 0x0D, 1);
	return 0;
}



////////////////////////////////////////////////////////////////////////////////
// 1. Pan/Tilt Motor Speed Step 설정
////////////////////////////////////////////////////////////////////////////////
int CU2SRProtoParser::SetAngleSpeed(BYTE* pbyBuffer, int nSpeed)
{
#if UNICODE
	CString str;
	str.Format(CMD_SET_ANGLE_SPEED_FOR_S, nSpeed);
	int iLen = wcslen(str);
	WideCharToMultiByte(CP_ACP, NULL, str, -1, (LPSTR)pbyBuffer, iLen, NULL, FALSE);
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
	return iLen;
#else
	CString str;
	str.Format(CMD_SET_ANGLE_SPEED_FOR_S, nSpeed);

	FillHeader(pbyBuffer);
	memcpy(pbyBuffer+0, str, str.GetLength());
	FillTail(pbyBuffer, str.GetLength());

	return str.GetLength()+1;
#endif
}
int CU2SRProtoParser::SetAnglePresetSpeedVal(BYTE* pbyBuffer, int nSpeed)
{

	CString str;
	str.Format(CMD_SET_ANGLE_PRESETSPEED_FOR, nSpeed);
	int iLen = wcslen(str);
	WideCharToMultiByte(CP_ACP, NULL, str, -1, (LPSTR)pbyBuffer, iLen, NULL, FALSE);
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
	return iLen;

}


////////////////////////////////////////////////////////////////////////////////
// 2. Pan/Tilt 구동명령
////////////////////////////////////////////////////////////////////////////////
// CMD_MOVE_LEFT
int CU2SRProtoParser::MoveLeft( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_MOVE_LEFT);
	WideCharToMultiByte(CP_ACP, NULL, CMD_MOVE_LEFT, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_MOVE_LEFT);
	memcpy(pbyBuffer+0, CMD_MOVE_LEFT, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;

}

// CMD_MOVE_RIGHT
int CU2SRProtoParser::MoveRight( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_MOVE_RIGHT);
	WideCharToMultiByte(CP_ACP, NULL, CMD_MOVE_RIGHT, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_MOVE_RIGHT);
	memcpy(pbyBuffer+0, CMD_MOVE_RIGHT, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;

}

// CMD_QUIT_LEFT
int CU2SRProtoParser::QuitLeft( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_QUIT_LEFT);
	WideCharToMultiByte(CP_ACP, NULL, CMD_QUIT_LEFT, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_QUIT_LEFT);
	memcpy(pbyBuffer+0, CMD_QUIT_LEFT, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;

}

// CMD_QUIT_RIGHT
int CU2SRProtoParser::QuitRight( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_QUIT_RIGHT);
	WideCharToMultiByte(CP_ACP, NULL, CMD_QUIT_RIGHT, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_QUIT_RIGHT);
	memcpy(pbyBuffer+0, CMD_QUIT_RIGHT, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_MOVE_UP
int CU2SRProtoParser::MoveUp( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_MOVE_UP);
	WideCharToMultiByte(CP_ACP, NULL, CMD_MOVE_UP, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_MOVE_UP);
	memcpy(pbyBuffer+0, CMD_MOVE_UP, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;

}

// CMD_MOVE_DOWN
int CU2SRProtoParser::MoveDown( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_MOVE_DOWN);
	WideCharToMultiByte(CP_ACP, NULL, CMD_MOVE_DOWN, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_MOVE_DOWN);
	memcpy(pbyBuffer+0, CMD_MOVE_DOWN, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_QUIT_UP
int CU2SRProtoParser::QuitUp( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_QUIT_UP);
	WideCharToMultiByte(CP_ACP, NULL, CMD_QUIT_UP, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_QUIT_UP);
	memcpy(pbyBuffer+0, CMD_QUIT_UP, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_QUIT_DOWN
int CU2SRProtoParser::QuitDown( BYTE* pbyBuffer)
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_QUIT_DOWN);
	WideCharToMultiByte(CP_ACP, NULL, CMD_QUIT_DOWN, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_QUIT_DOWN);
	memcpy(pbyBuffer+0, CMD_QUIT_DOWN, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

int CU2SRProtoParser::LRFMoveLeft( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_MOVE_LRF_LEFT);
	WideCharToMultiByte(CP_ACP, NULL, CMD_MOVE_LRF_LEFT, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_MOVE_LRF_LEFT);
	memcpy(pbyBuffer+0, CMD_MOVE_LRF_LEFT, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;


}	
int CU2SRProtoParser::LRFMoveRight( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_MOVE_LRF_RIGHT);
	WideCharToMultiByte(CP_ACP, NULL, CMD_MOVE_LRF_RIGHT, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_MOVE_LRF_RIGHT);
	memcpy(pbyBuffer+0, CMD_MOVE_LRF_RIGHT, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;


}
int CU2SRProtoParser::LRFMoveUp( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_MOVE_LRF_UP);
	WideCharToMultiByte(CP_ACP, NULL, CMD_MOVE_LRF_UP, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_MOVE_LRF_UP);
	memcpy(pbyBuffer+0, CMD_MOVE_LRF_UP, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}
int CU2SRProtoParser::LRFMoveDown( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_MOVE_LRF_DOWN);
	WideCharToMultiByte(CP_ACP, NULL, CMD_MOVE_LRF_DOWN, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_MOVE_LRF_DOWN);
	memcpy(pbyBuffer+0, CMD_MOVE_LRF_DOWN, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}
int CU2SRProtoParser::LRFMoveStop( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_MOVE_LRF_STOP);
	WideCharToMultiByte(CP_ACP, NULL, CMD_MOVE_LRF_STOP, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_MOVE_LRF_STOP);
	memcpy(pbyBuffer+0, CMD_MOVE_LRF_STOP, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;

}

int CU2SRProtoParser::GetLRFPwr( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_GET_LRFPWR);
	WideCharToMultiByte(CP_ACP, NULL, CMD_GET_LRFPWR, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_GET_LRFPWR);
	memcpy(pbyBuffer+0, CMD_GET_LRFPWR, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;

}
int CU2SRProtoParser::SetLRFPwr(BYTE* pbyBuffer, BOOL bOn)
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	if( bOn ){
		iLen = wcslen(CMD_SET_LRFPWR_ON);
		WideCharToMultiByte(CP_ACP, NULL, CMD_SET_LRFPWR_ON, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	}
	else{
		iLen = wcslen(CMD_SET_LRFPWR_OFF);
		WideCharToMultiByte(CP_ACP, NULL, CMD_SET_LRFPWR_OFF, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	}
	pbyBuffer[iLen++] = 0x0d;
#else
	if( bOn ){
		iLen = wcslen(CMD_SET_LRFPWR_ON);
		memcpy(pbyBuffer+0, CMD_SET_LRFPWR_ON, iLen);	
	}
	else{
		iLen = wcslen(CMD_SET_LRFPWR_OFF);
		memcpy(pbyBuffer+0, CMD_SET_LRFPWR_OFF, iLen);	
	}
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

int CU2SRProtoParser::GetHighCamHWFilter( BYTE* pbyBuffer )
{
	FillHeader(pbyBuffer);
#ifdef UNICODE
	memcpy(pbyBuffer+__PHS__, CMD_GET_HIGHCAM_HWFILTER, wcslen(CMD_GET_HIGHCAM_HWFILTER));	
#else
	memcpy(pbyBuffer+__PHS__, CMD_GET_HIGHCAM_HWFILTER, wcslen(CMD_GET_HIGHCAM_HWFILTER));
#endif
	FillTail(pbyBuffer);

	return 0;
}
int CU2SRProtoParser::SetHighCamHWFilter( BYTE* pbyBuffer, BOOL bOn)
{
	FillHeader(pbyBuffer);
#ifdef UNICODE
	if(bOn)
		memcpy(pbyBuffer+0, CMD_SET_HIGHCAM_HWFILTER_ON, wcslen(CMD_SET_HIGHCAM_HWFILTER_ON));
	else
		memcpy(pbyBuffer+0, CMD_SET_HIGHCAM_HWFILTER_OFF, wcslen(CMD_SET_HIGHCAM_HWFILTER_OFF));
#else
	if(bOn)
		memcpy(pbyBuffer+0, CMD_SET_HIGHCAM_HWFILTER_ON, wcslen(CMD_SET_HIGHCAM_HWFILTER_ON));
	else
		memcpy(pbyBuffer+0, CMD_SET_HIGHCAM_HWFILTER_OFF, wcslen(CMD_SET_HIGHCAM_HWFILTER_OFF));
#endif
	

	FillTail(pbyBuffer);

	return 0;
}
int CU2SRProtoParser::ReqLrfDistance( BYTE* pbyBuffer )
{
	CString str;
	str.Format(_T("%s"), "LC=?:0203");
	FillHeader(pbyBuffer);
	memcpy(pbyBuffer+__PHS__, str, str.GetLength());	
	FillTail(pbyBuffer, str.GetLength());

	return str.GetLength();
}

UINT CU2SRProtoParser::ParsingLRFRangeCmd(CString strRecvedCmd)
{
	if( strRecvedCmd == _T("") )
		return 10;//empty buff == 10

	WORD wRange;
	WORD wRange2;

	//CString csMSB = strRecvedCmd.Mid(2,2);
	//CString csLSB = strRecvedCmd.Mid(4,2);
	TRACE("recved lrf data =%s\r\n", strRecvedCmd);
	CString statusByte = strRecvedCmd.Left(2);
	TRACE("status byte=%s\r\n", statusByte);
	CString csMSB = strRecvedCmd.Mid(2,2);
	CString csLSB = strRecvedCmd.Mid(4,2);


	BYTE MSB = StringHexaToAscii(csMSB);
	BYTE LSB = StringHexaToAscii(csLSB);

	MSB = MSB&0x7F;		
	wRange = MSB;		
	wRange = wRange<<8;		
	wRange = wRange+LSB;
	TRACE("FirstRange = %d\r\n", wRange);

	//Second
	CString csMSB2 = strRecvedCmd.Mid(6,2);
	CString csLSB2 = strRecvedCmd.Mid(8,2);

	BYTE MSB2 = StringHexaToAscii(csMSB2);
	BYTE LSB2 = StringHexaToAscii(csLSB2);

	MSB2 = MSB2&0x7F;
	wRange2 = MSB2;	
	wRange2 = wRange2<<8;
	wRange2 = wRange2+LSB2;
	TRACE("SecondRange = %d\r\n", wRange2);

	return (UINT)wRange;
}


int CU2SRProtoParser::HighCamMenuUp( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_HIGHCAMMENU_UP);
	WideCharToMultiByte(CP_ACP, NULL, CMD_HIGHCAMMENU_UP, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_HIGHCAMMENU_UP);
	memcpy(pbyBuffer+0, CMD_HIGHCAMMENU_UP, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;



/*
	FillHeader(pbyBuffer);
#ifdef UNICODE
	memcpy(pbyBuffer+0, CMD_HIGHCAMMENU_UP, wcslen(CMD_HIGHCAMMENU_UP));

#else
	memcpy(pbyBuffer+0, CMD_HIGHCAMMENU_UP, wcslen(CMD_HIGHCAMMENU_UP));

#endif
	FillTail(pbyBuffer);

	return 0;*/

}
int CU2SRProtoParser::HighCamMenuDown( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_HIGHCAMMENU_DOWN);
	WideCharToMultiByte(CP_ACP, NULL, CMD_HIGHCAMMENU_DOWN, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_HIGHCAMMENU_DOWN);
	memcpy(pbyBuffer+0, CMD_HIGHCAMMENU_DOWN, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;

}
int CU2SRProtoParser::HighCamMenuLeft( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_HIGHCAMMENU_LEFT);
	WideCharToMultiByte(CP_ACP, NULL, CMD_HIGHCAMMENU_LEFT, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_HIGHCAMMENU_LEFT);
	memcpy(pbyBuffer+0, CMD_HIGHCAMMENU_LEFT, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}
int CU2SRProtoParser::HighCamMenuRight( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_HIGHCAMMENU_RIGHT);
	WideCharToMultiByte(CP_ACP, NULL, CMD_HIGHCAMMENU_RIGHT, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_HIGHCAMMENU_RIGHT);
	memcpy(pbyBuffer+0, CMD_HIGHCAMMENU_RIGHT, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;

}
int CU2SRProtoParser::HighCamMenuEnter( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_HIGHCAMMENU_ENTER);
	WideCharToMultiByte(CP_ACP, NULL, CMD_HIGHCAMMENU_ENTER, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_HIGHCAMMENU_ENTER);
	memcpy(pbyBuffer+0, CMD_HIGHCAMMENU_ENTER, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;

}
int CU2SRProtoParser::HighCamMenuOpen( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_HIGHCAMMENU_OPEN);
	WideCharToMultiByte(CP_ACP, NULL, CMD_HIGHCAMMENU_OPEN, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_HIGHCAMMENU_OPEN);
	memcpy(pbyBuffer+0, CMD_HIGHCAMMENU_OPEN, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

int CU2SRProtoParser::LowCamMenuUp( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_LOWCAMMENU_UP);
	WideCharToMultiByte(CP_ACP, NULL, CMD_LOWCAMMENU_UP, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_LOWCAMMENU_UP);
	memcpy(pbyBuffer+0, CMD_LOWCAMMENU_UP, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}
int CU2SRProtoParser::LowCamMenuDown(BYTE* pbyBuffer)
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_LOWCAMMENU_DOWN);
	WideCharToMultiByte(CP_ACP, NULL, CMD_LOWCAMMENU_DOWN, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_LOWCAMMENU_DOWN);
	memcpy(pbyBuffer+0, CMD_HIGHCAMMENU_DOWN, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}
int CU2SRProtoParser::LowCamMenuLeft( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_LOWCAMMENU_LEFT);
	WideCharToMultiByte(CP_ACP, NULL, CMD_LOWCAMMENU_LEFT, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_LOWCAMMENU_LEFT);
	memcpy(pbyBuffer+0, CMD_LOWCAMMENU_LEFT, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}
int CU2SRProtoParser::LowCamMenuRight( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_LOWCAMMENU_RIGHT);
	WideCharToMultiByte(CP_ACP, NULL, CMD_LOWCAMMENU_RIGHT, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_LOWCAMMENU_RIGHT);
	memcpy(pbyBuffer+0, CMD_LOWCAMMENU_RIGHT, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}
int CU2SRProtoParser::LowCamMenuEnter( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_LOWCAMMENU_ENTER);
	WideCharToMultiByte(CP_ACP, NULL, CMD_LOWCAMMENU_ENTER, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_LOWCAMMENU_ENTER);
	memcpy(pbyBuffer+0, CMD_LOWCAMMENU_ENTER, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}
int CU2SRProtoParser::LowCamMenuOpen( BYTE* pbyBuffer )
{
	//  [3/16/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_LOWCAMMENU_OPEN);
	WideCharToMultiByte(CP_ACP, NULL, CMD_LOWCAMMENU_OPEN, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_LOWCAMMENU_OPEN);
	memcpy(pbyBuffer+0, CMD_LOWCAMMENU_OPEN, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

void CU2SRProtoParser::ConvertByteToHexa(BYTE * pByData, int iLength, CString &strHexa)
{
	for (int i=0; i<iLength; i++)
	{
		CString str;
		str.Format(_T("%02X"), pByData[i]);
		strHexa+=str;
	}
}
void CU2SRProtoParser::StringHexaToByteHexa(byte* pSrc, byte* pDest, int iDestLen)
{
	CString str;
	str.Format(_T("%s"), pSrc);

	int iStrJumpGap=0;
	for (int i=0; i<iDestLen; i++)
	{
		CString strTempHexa = str.Mid(iStrJumpGap, 2);
		iStrJumpGap+=2;

		BYTE byTemp = StringHexaToAscii( strTempHexa );
		pDest[i] = byTemp;

		CString strTemp;
		strTemp.Format( _T("%02X "), byTemp );
		TRACE( strTemp );
	}
	TRACE(_T("\n\n"));
}
void CU2SRProtoParser::StringHexaToByteHexa(CString strSrc, byte* pDest, int iDestLen)
{
	CString str = strSrc;


	int iStrJumpGap = 0;
	for (int i = 0; i<iDestLen; i++)
	{
		CString strTempHexa = str.Mid(iStrJumpGap, 2);
		iStrJumpGap += 2;

		BYTE byTemp = StringHexaToAscii(strTempHexa);
		pDest[i] = byTemp;

		CString strTemp;
		strTemp.Format(_T("%02X "), byTemp);
		TRACE(strTemp);
	}
	TRACE(_T("\n\n"));
}
void CU2SRProtoParser::String2Ascii(char *pArr, CString strSrc, int nLen)
{
	//TCHAR tchStr[1];
	WCHAR tchStr[1];

	int nCount = nLen;
	if(nLen > strSrc.GetLength())
		nCount = strSrc.GetLength();

	for(int i=0; i<nCount; i++)
	{
		tchStr[0] = strSrc.GetAt(i);

		if(' ' == tchStr[0])
			pArr[i] = 0x00;
		else
			wcstombs(pArr+i, tchStr, 1);
	}
}

BYTE CU2SRProtoParser::Code2Ascii(char cData)
{
	BYTE Ascii;

	//--> '0' ~ '9' => 0 ~ 9
	if( ('0' <= cData) && (cData <= '9') )
	{
		Ascii = cData - '0';
	} //--> 'A' ~ 'F' => 10 ~ 15
	else if( ('A' <= cData) && (cData <= 'F') )
	{
		Ascii = (cData - 'A') + 10;
	} //--> 'a' ~ 'f' => 10 ~ 15
	else if( ('a' <= cData) && (cData <= 'f') )
	{
		Ascii = (cData - 'a') + 10;
	}
	else 
	{
		Ascii = 0;
	}
	return Ascii;	
}
BYTE CU2SRProtoParser::Code2Ascii(wchar_t cData)
{
	BYTE Ascii;

	//--> '0' ~ '9' => 0 ~ 9
	if( ('0' <= cData) && (cData <= '9') )
	{
		Ascii = cData - '0';
	} //--> 'A' ~ 'F' => 10 ~ 15
	else if( ('A' <= cData) && (cData <= 'F') )
	{
		Ascii = (cData - 'A') + 10;
	} //--> 'a' ~ 'f' => 10 ~ 15
	else if( ('a' <= cData) && (cData <= 'f') )
	{
		Ascii = (cData - 'a') + 10;
	}
	else 
	{
		Ascii = 0;
	}
	return Ascii;	
}
BYTE CU2SRProtoParser::StringHexaToAscii(CString csHexa)
{
	CString strData = _T(""),strSnd = _T("2"); //전송명령어
	CString aa = csHexa; //입력 스트링 16진수
	BYTE byHigh,byLow;
	BYTE bySendBuf[2];
	memset(bySendBuf, 0x00, sizeof(bySendBuf));
	int nBufPos = 0;

	int nwcslength = aa.GetLength();


	for(int i=0; (i + 1)<nwcslength; i+=3 )
	{
		byHigh = Code2Ascii( aa[i] );
		byLow  = Code2Ascii( aa[i + 1] );

		bySendBuf[nBufPos++] = (byHigh << 4) | byLow; 
		//해당문자값을구한다.
	}

	strData.Format(_T("%s"), bySendBuf); //구한값을 String에 저장
	strSnd += strData; //명령문에 입력값을 더한다.

	return  bySendBuf[0];
}

//yeun 20131130
BYTE CU2SRProtoParser::StringHexaToAscii_Rev(CString csHexa)
{
	CString strData = _T(""),strSnd = _T("2"); //전송명령어
	CString aa = csHexa; //입력 스트링 16진수
	BYTE byHigh,byLow;
	BYTE bySendBuf[2];
	memset(bySendBuf, 0x00, sizeof(bySendBuf));
	int nBufPos = 0;

	int nwcslength = aa.GetLength();


	for(int i=0; (i + 1)<nwcslength; i+=3 )
	{
		byHigh = Code2Ascii( aa[i] );
		byLow  = Code2Ascii( aa[i + 1] );

		bySendBuf[nBufPos++] = (byHigh << 4) | byLow; 
		//해당문자값을구한다.
	}

	strData.Format(_T("%s"), bySendBuf); //구한값을 String에 저장
	strSnd += strData; //명령문에 입력값을 더한다.

	return  bySendBuf[0];
}

////////////////////////////////////////////////////////////////////////////////
// 3. 현재상태의 방위각/고저각 값 읽기
////////////////////////////////////////////////////////////////////////////////
// CMD_GET_VAL_P
int CU2SRProtoParser::PanGetValue( BYTE* pbyBuffer )
{
// hschoi 주석처리함 (동기화 방위각 변경에 사용해야 함)
//	ASSERT(FALSE);		// GetAngleValue(pbyBuffer) 사용하는게 좋을 듯

	FillHeader(pbyBuffer);
#ifdef UNICODE
	memcpy(pbyBuffer+0, CMD_GET_VAL_P, wcslen(CMD_GET_VAL_P));
#else
	memcpy(pbyBuffer+0, CMD_GET_VAL_P, wcslen(CMD_GET_VAL_P));
#endif
	
	FillTail(pbyBuffer);

	return 0;
}

// CMD_GET_VAL_T
int CU2SRProtoParser::Com03_TiltGetValue( BYTE* pbyBuffer )
{
	ASSERT(FALSE);		// GetAngleValue(pbyBuffer) 사용하는게 좋을 듯

	FillHeader(pbyBuffer);
#ifdef UNICODE
		memcpy(pbyBuffer+0, CMD_GET_VAL_T, wcslen(CMD_GET_VAL_T));
#else
		memcpy(pbyBuffer+0, CMD_GET_VAL_T, wcslen(CMD_GET_VAL_T));
#endif

	FillTail(pbyBuffer);

	return 0;

}


// CMD_GET_VAL_DMC
int CU2SRProtoParser::GetDMCValue( BYTE* pbyBuffer )
{
	FillHeader(pbyBuffer);
	int iLen = 0;
	iLen = wcslen(CMD_GET_VAL_DMC);
	memcpy(pbyBuffer+0, CMD_GET_VAL_DMC, iLen);	
	pbyBuffer[iLen++] = 0x0d;

	return iLen;
}

// CMD_GET_VAL_GPS
int CU2SRProtoParser::GPSGetValue( BYTE* pbyBuffer )
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_GET_VAL_GPS);
	WideCharToMultiByte(CP_ACP, NULL, CMD_GET_VAL_GPS, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_GET_VAL_GPS);
	memcpy(pbyBuffer+0, CMD_GET_VAL_GPS, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}
//  [9/10/2014 Yeun] 
int CU2SRProtoParser::ReqMainBoardVersion( BYTE* pbyBuffer )
{
	int iLen = wcslen(_T("stat"));
	memcpy(pbyBuffer+0, "stat", iLen);	
	pbyBuffer[iLen++] = 0x0d;

	return iLen;
}

// CMD_GET_PMETER_M
int CU2SRProtoParser::MLense_GetPMeter( BYTE* pbyBuffer )
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_GET_PMETER_M);
	WideCharToMultiByte(CP_ACP, NULL, CMD_GET_PMETER_M, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;

#else
	iLen = wcslen(CMD_GET_STATUS_P);
	memcpy(pbyBuffer+0, CMD_GET_PMETER_M, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_GET_ANGLE
int CU2SRProtoParser::AngleGetValue( BYTE* pbyBuffer )
{
	FillHeader(pbyBuffer);
#ifdef UNICODE
	memcpy(pbyBuffer+0, CMD_GET_ANGLE, wcslen(CMD_GET_ANGLE));
#else
	memcpy(pbyBuffer+0, CMD_GET_ANGLE, wcslen(CMD_GET_ANGLE));
#endif
	
	FillTail(pbyBuffer);

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
// 4. BIT용 상태표시
////////////////////////////////////////////////////////////////////////////////
// CMD_GET_STATUS_P
int CU2SRProtoParser::PanGetStatus( BYTE* pbyBuffer )
{
/*
	FillHeader(pbyBuffer);
	
#ifdef UNICODE
	memcpy(pbyBuffer+0, CMD_GET_STATUS_P, wcslen(CMD_GET_STATUS_P));
#else
	memcpy(pbyBuffer+0, CMD_GET_STATUS_P, wcslen(CMD_GET_STATUS_P));
#endif
	FillTail(pbyBuffer);

	return 0;*/



	//  [3/14/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_GET_STATUS_P);
	WideCharToMultiByte(CP_ACP, NULL, CMD_GET_STATUS_P, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_GET_STATUS_P);
	memcpy(pbyBuffer+0, CMD_GET_STATUS_P, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_GET_STATUS_T
int CU2SRProtoParser::TiltGetStatus( BYTE* pbyBuffer )
{
/*
	FillHeader(pbyBuffer);
	
#ifdef UNICODE
	memcpy(pbyBuffer+0, CMD_GET_STATUS_T, wcslen(CMD_GET_STATUS_T));
#else
	memcpy(pbyBuffer+0, CMD_GET_STATUS_T, wcslen(CMD_GET_STATUS_T));
#endif
	FillTail(pbyBuffer);

	return 0;*/



	//  [3/14/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_GET_STATUS_T);
	WideCharToMultiByte(CP_ACP, NULL, CMD_GET_STATUS_T, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_GET_STATUS_T);
	memcpy(pbyBuffer+0, CMD_GET_STATUS_T, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_GET_STATUS_M
int CU2SRProtoParser::MLense_GetStatus( BYTE* pbyBuffer )
{
	FillHeader(pbyBuffer);
	
#ifdef UNICODE
	memcpy(pbyBuffer+0, CMD_GET_STATUS_M, wcslen(CMD_GET_STATUS_M));
#else
	memcpy(pbyBuffer+0, CMD_GET_STATUS_M, wcslen(CMD_GET_STATUS_M));
#endif
	FillTail(pbyBuffer);

	return 0;
}

// CMD_GET_STATUS_A
int CU2SRProtoParser::ALense_GetStatus( BYTE* pbyBuffer )
{
	FillHeader(pbyBuffer);	
#ifdef UNICODE
	memcpy(pbyBuffer+0, CMD_GET_STATUS_A, wcslen(CMD_GET_STATUS_A));
#else
	memcpy(pbyBuffer+0, CMD_GET_STATUS_A, wcslen(CMD_GET_STATUS_A));
#endif
	FillTail(pbyBuffer);

	return 0;

}

////////////////////////////////////////////////////////////////////////////////
// 5. Video Control
////////////////////////////////////////////////////////////////////////////////
// CMD_SET_VO_V1C1
int CU2SRProtoParser::SetVideoConnect1( BYTE* pbyBuffer )
{
	FillHeader(pbyBuffer);

#ifdef UNICODE
		memcpy(pbyBuffer+0, CMD_SET_VO_V1C1, wcslen(CMD_SET_VO_V1C1));
#else
		memcpy(pbyBuffer+0, CMD_SET_VO_V1C1, wcslen(CMD_SET_VO_V1C1));
#endif
	FillTail(pbyBuffer);

	return 0;
}

// CMD_SET_VO_V1C2
int CU2SRProtoParser::SetVideoConnect2( BYTE* pbyBuffer )
{
	FillHeader(pbyBuffer);
#ifdef UNICODE
	memcpy(pbyBuffer+0, CMD_SET_VO_V1C2, wcslen(CMD_SET_VO_V1C2));

#else
	memcpy(pbyBuffer+0, CMD_SET_VO_V1C2, wcslen(CMD_SET_VO_V1C2));

#endif
	FillTail(pbyBuffer);

	return 0;
}

// CMD_GET_VO_V1CQ
int CU2SRProtoParser::GetVideoConnect( BYTE* pbyBuffer )
{
	FillHeader(pbyBuffer);
#ifdef UNICODE
	memcpy(pbyBuffer+0, CMD_GET_VO_V1CQ, wcslen(CMD_GET_VO_V1CQ));
#else
	memcpy(pbyBuffer+0, CMD_GET_VO_V1CQ, wcslen(CMD_GET_VO_V1CQ));
#endif
	FillTail(pbyBuffer);

	return 0;
}

// CMD_SET_VM_S
int CU2SRProtoParser::SetHighColor( BYTE* pbyBuffer)
{
	int nLen = 0;
#ifdef UNICODE
	nLen = wcslen(CMD_SET_VM_S);
	WideCharToMultiByte(CP_ACP, NULL, CMD_SET_VM_S, -1, (LPSTR)pbyBuffer, nLen, NULL, FALSE);
	FillTail(pbyBuffer, nLen);
	pbyBuffer[nLen] = 0x00;
#else	
	int iLen = wcslen(CMD_SET_VM_S);
	memcpy(pbyBuffer+0, CMD_SET_VM_S, wcslen(CMD_SET_VM_S));
	pbyBuffer[iLen++] = 0x0d;
#endif
	return nLen;
}

int CU2SRProtoParser::SetHighExtender(BYTE * pbyBuffer, BOOL bOn)
{
	int i = 0;
	pbyBuffer[i++] = 'F';
	pbyBuffer[i++] = 'X';
	pbyBuffer[i++] = '=';
	if(bOn)
		pbyBuffer[i++] = '2';//임시바꿈
	else
		pbyBuffer[i++] = '1';
	pbyBuffer[i++] = 0x0d;
	pbyBuffer[i] = 0x00;

	return i;
}
int CU2SRProtoParser::SetHighIris(BYTE* pbyBuffer, BOOL bOn)
{
	/*
	[VI = O] 고배율 렌즈의 IRIS 를 open 한다
		[VI = C] 고배율 렌즈의 IRIS 를 close 한다
		[VI = Q] 고배율 렌즈의 IRIS 를 open / close 동작을
		중지 한다
		*/

	int i = 0;
	pbyBuffer[i++] = 'V';
	pbyBuffer[i++] = 'I';
	pbyBuffer[i++] = '=';
	if (bOn)
		pbyBuffer[i++] = 'C';
	else
		pbyBuffer[i++] = 'Q';
	pbyBuffer[i++] = 0x0d;
	pbyBuffer[i] = 0x00;

	return i;
}

// CMD_SET_VM_D
int CU2SRProtoParser::SetHighBW( BYTE* pbyBuffer )
{
	int nLen=0;
#ifdef UNICODE
	nLen = wcslen(CMD_SET_VM_D);
	WideCharToMultiByte(CP_ACP, NULL, CMD_SET_VM_D, -1, (LPSTR)pbyBuffer, nLen, NULL, FALSE);
	FillTail(pbyBuffer, nLen);
	pbyBuffer[nLen] = 0x00;
#else	
	int iLen = wcslen(CMD_SET_VM_D);
	memcpy(pbyBuffer+0, CMD_SET_VM_D, wcslen(CMD_SET_VM_D));
	pbyBuffer[iLen++] = 0x0d;
#endif
	return nLen;
}

// CMD_GET_VM_Q
int CU2SRProtoParser::GetHigh( BYTE* pbyBuffer )
{
	FillHeader(pbyBuffer);
#ifdef UNICODE
	memcpy(pbyBuffer+0, CMD_GET_VM_Q, wcslen(CMD_GET_VM_Q));
#else
	memcpy(pbyBuffer+0, CMD_GET_VM_Q, wcslen(CMD_GET_VM_Q));
#endif

	FillTail(pbyBuffer);

	return 0;
}

// CMD_SET_VA_S
int CU2SRProtoParser::SetLowColor( BYTE* pbyBuffer )
{
	FillHeader(pbyBuffer);
#ifdef UNICODE
	memcpy(pbyBuffer+0, CMD_SET_VA_S, wcslen(CMD_SET_VA_S));
#else
	memcpy(pbyBuffer+0, CMD_SET_VA_S, wcslen(CMD_SET_VA_S));
#endif
	FillTail(pbyBuffer);

	return 0;
}

// CMD_SET_VA_D
int CU2SRProtoParser::SetLowBW( BYTE* pbyBuffer )
{
	FillHeader(pbyBuffer);
#ifdef UNICODE
	memcpy(pbyBuffer+0, CMD_SET_VA_D, wcslen(CMD_SET_VA_D));
#else
	memcpy(pbyBuffer+0, CMD_SET_VA_D, wcslen(CMD_SET_VA_D));
#endif
	FillTail(pbyBuffer);

	return 0;
}

// CMD_GET_VA_Q
int CU2SRProtoParser::GetLow( BYTE* pbyBuffer )
{
	FillHeader(pbyBuffer);
#ifdef UNICODE
	memcpy(pbyBuffer+0, CMD_GET_VA_Q, wcslen(CMD_GET_VA_Q));
#else
	memcpy(pbyBuffer+0, CMD_GET_VA_Q, wcslen(CMD_GET_VA_Q));
#endif

	FillTail(pbyBuffer);

	return 0;
}

// CMD_SET_V1_M
int CU2SRProtoParser::SetCH1High( BYTE* pbyBuffer )
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_SET_V1_M);
	WideCharToMultiByte(CP_ACP, NULL, CMD_SET_V1_M, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_SET_V1_M);
	memcpy(pbyBuffer+0, CMD_SET_V1_M, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return wcslen(CMD_SET_V1_M);
}

// CMD_SET_V1_A
int CU2SRProtoParser::SetCH1Low( BYTE* pbyBuffer )
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_SET_V1_A);
	WideCharToMultiByte(CP_ACP, NULL, CMD_SET_V1_A, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_SET_V1_A);
	memcpy(pbyBuffer+0, CMD_SET_V1_A, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_SET_V1_R
int CU2SRProtoParser::SetCH1Thermal( BYTE* pbyBuffer )
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_SET_V1_R);
	WideCharToMultiByte(CP_ACP, NULL, CMD_SET_V1_R, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_SET_V1_R);
	memcpy(pbyBuffer+0, CMD_SET_V1_R, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_SET_V1_X
int CU2SRProtoParser::SetCH1Free( BYTE* pbyBuffer )
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_SET_V1_X);
	WideCharToMultiByte(CP_ACP, NULL, CMD_SET_V1_X, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_SET_V1_X);
	memcpy(pbyBuffer+0, CMD_SET_V1_X, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_GET_V1_Q
int CU2SRProtoParser::GetCH1( BYTE* pbyBuffer )
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_GET_V1_Q);
	WideCharToMultiByte(CP_ACP, NULL, CMD_GET_V1_Q, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_GET_V1_Q);
	memcpy(pbyBuffer+0, CMD_GET_V1_Q, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_SET_V2_M
int CU2SRProtoParser::SetCH2High( BYTE* pbyBuffer )
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_SET_V2_M);
	WideCharToMultiByte(CP_ACP, NULL, CMD_SET_V2_M, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_SET_V2_M);
	memcpy(pbyBuffer+0, CMD_SET_V2_M, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_SET_V2_A
int CU2SRProtoParser::SetCH2Low( BYTE* pbyBuffer )
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_SET_V2_A);
	WideCharToMultiByte(CP_ACP, NULL, CMD_SET_V2_A, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_SET_V2_M);
	memcpy(pbyBuffer+0, CMD_SET_V2_A, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_SET_V2_R
int CU2SRProtoParser::SetCH2Thermal( BYTE* pbyBuffer )
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_SET_V2_R);
	WideCharToMultiByte(CP_ACP, NULL, CMD_SET_V2_R, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_SET_V2_R);
	memcpy(pbyBuffer+0, CMD_SET_V2_R, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_SET_V2_X
int CU2SRProtoParser::SetCH2Free( BYTE* pbyBuffer )
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_SET_V2_X);
	WideCharToMultiByte(CP_ACP, NULL, CMD_SET_V2_X, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_SET_V2_R);
	memcpy(pbyBuffer+0, CMD_SET_V2_X, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_GET_V2_Q
int CU2SRProtoParser::GetCH2( BYTE* pbyBuffer )
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_GET_V2_Q);
	WideCharToMultiByte(CP_ACP, NULL, CMD_GET_V2_Q, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_GET_V2_Q);
	memcpy(pbyBuffer+0, CMD_GET_V2_Q, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

////////////////////////////////////////////////////////////////////////////////
// 6. 고배율 Lense control
////////////////////////////////////////////////////////////////////////////////
// CMD_M_LENSE_FOCUS_IN
int CU2SRProtoParser::MLense_FocusInStart( BYTE* pbyBuffer )
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_M_LENSE_FOCUS_IN);
	WideCharToMultiByte(CP_ACP, NULL, CMD_M_LENSE_FOCUS_IN, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_M_LENSE_FOCUS_IN);
	memcpy(pbyBuffer+0, CMD_M_LENSE_FOCUS_IN, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_M_LENSE_FOCUS_OUT
int CU2SRProtoParser::MLense_FocusOutStart( BYTE* pbyBuffer )
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_M_LENSE_FOCUS_OUT);
	WideCharToMultiByte(CP_ACP, NULL, CMD_M_LENSE_FOCUS_OUT, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_M_LENSE_FOCUS_OUT);
	memcpy(pbyBuffer+0, CMD_M_LENSE_FOCUS_OUT, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_M_LENSE_FOCUS_STOP
int CU2SRProtoParser::MLense_FocusStop( BYTE* pbyBuffer )
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_M_LENSE_FOCUS_STOP);
	WideCharToMultiByte(CP_ACP, NULL, CMD_M_LENSE_FOCUS_STOP, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_M_LENSE_FOCUS_STOP);
	memcpy(pbyBuffer+0, CMD_M_LENSE_FOCUS_STOP, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}


// CMD_M_LENSE_MOVE_PFOCUS
int CU2SRProtoParser::MLense_PFocusMoveTo(BYTE* pbyBuffer, int nPosition)
{
	CString str;
	str.Format(CMD_M_LENSE_MOVE_PFOCUS, nPosition);
	TRACE("PFocus command = %s\n",str);

	FillHeader(pbyBuffer);
	memcpy(pbyBuffer+0, str, str.GetLength());
	FillTail(pbyBuffer);

	return 0;
}

// CMD_M_LENSE_SET_FOCUS_SPEED
int CU2SRProtoParser::MLense_FocusSetSpeed(BYTE* pbyBuffer, int iSpeed)
{

	int iLen = 0;
#ifdef UNICODE	
	CString str;
	str.Format(CMD_M_LENSE_SET_FOCUS_SPEED, iSpeed);
	iLen = wcslen(str);
	WideCharToMultiByte(CP_ACP, NULL, str, -1, (LPSTR)pbyBuffer, iLen, NULL, FALSE);
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00; 
#else
	CString str;
	str.Format(CMD_M_LENSE_SET_FOCUS_SPEED, iSpeed);
	iLen =  str.GetLength();
#endif

	return iLen;
}

// CMD_M_LENSE_ZOOM _TELE
int CU2SRProtoParser::MLense_ZoomTeleStart(BYTE* pbyBuffer)
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_M_LENSE_ZOOM_TELE);
	WideCharToMultiByte(CP_ACP, NULL, CMD_M_LENSE_ZOOM_TELE, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_M_LENSE_ZOOM_TELE);
	memcpy(pbyBuffer+0, CMD_M_LENSE_ZOOM_TELE, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_M_LENSE_ZOOM_WIDE
int CU2SRProtoParser::MLense_ZoomWideStart(BYTE* pbyBuffer)
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_M_LENSE_ZOOM_WIDE);
	WideCharToMultiByte(CP_ACP, NULL, CMD_M_LENSE_ZOOM_WIDE, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_M_LENSE_ZOOM_WIDE);
	memcpy(pbyBuffer+0, CMD_M_LENSE_ZOOM_WIDE, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_M_LENSE_ZOOM_STOP
int CU2SRProtoParser::MLense_ZoomStop(BYTE* pbyBuffer)
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_M_LENSE_ZOOM_STOP);
	WideCharToMultiByte(CP_ACP, NULL, CMD_M_LENSE_ZOOM_STOP, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_M_LENSE_ZOOM_STOP);
	memcpy(pbyBuffer+0, CMD_M_LENSE_ZOOM_STOP, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

int CU2SRProtoParser::MLense_AutoFocus(BYTE* pbyBuffer)
{
	CString strCmd = _T("Fb");
	int iLen = wcslen(strCmd);
	memcpy(pbyBuffer+0, strCmd, iLen);	
	pbyBuffer[iLen++] = 0x0d;
	return iLen;
}

int CU2SRProtoParser::MLense_LensFilter( BYTE* pbyBuffer, int nFilterNum )
{
	CString strCmd;
	if( nFilterNum == 0 )
	{
		strCmd = _T("VF=R");
		
	}
	else if( nFilterNum == 1 )
	{
		strCmd = _T("VF=1");
	}
	else if( nFilterNum == 2 )
	{
		strCmd = _T("VF=2");
	}
	else if( nFilterNum == 3 )
	{
		strCmd = _T("VF=3");
	}
	else if( nFilterNum == 4 )//filter togle
	{
		strCmd = _T("VF=0");
	}
	
	int iLen = wcslen(strCmd);
	//memcpy(pbyBuffer+0, strCmd, iLen);	
	WideCharToMultiByte(CP_ACP, NULL, strCmd, -1, (LPSTR)pbyBuffer, iLen, NULL, FALSE);
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
	return iLen;
}

// CMD_M_LENSE_MOVE_PZOOM
int CU2SRProtoParser::MLense_PZoomMoveTo(BYTE* pbyBuffer, int nPosition)
{
	//Fb
	CString str;
	str.Format(CMD_M_LENSE_MOVE_PZOOM, nPosition);
	TRACE("PZoom command = %s\n",str);

	FillHeader(pbyBuffer);
	memcpy(pbyBuffer+0, str, str.GetLength());
	FillTail(pbyBuffer);

	return 0;
}


// CMD_M_LENSE_SET_ZOOM_SPEED
int CU2SRProtoParser::MLense_ZoomSetSpeed(BYTE* pbyBuffer, int iSpeed)
{
	int iLen = 0;
#ifdef UNICODE
	CString str;
	str.Format(CMD_M_LENSE_SET_ZOOM_SPEED, iSpeed);
	iLen = wcslen(str);
	WideCharToMultiByte(CP_ACP, NULL, str, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	CString str;
	str.Format(CMD_M_LENSE_SET_ZOOM_SPEED, iSpeed);
	iLen =  str.GetLength();
#endif

	return iLen;

}

////////////////////////////////////////////////////////////////////////////////
// 7. 저배율 Lense control
////////////////////////////////////////////////////////////////////////////////
// CMD_A_LENSE_FOCUS_IN
int CU2SRProtoParser::ALense_FocusInStart( BYTE* pbyBuffer )
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_A_LENSE_FOCUS_IN);
	WideCharToMultiByte(CP_ACP, NULL, CMD_A_LENSE_FOCUS_IN, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_A_LENSE_FOCUS_IN);
	memcpy(pbyBuffer+0, CMD_A_LENSE_FOCUS_IN, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_A_LENSE_FOCUS_OUT
int CU2SRProtoParser::ALense_FocusOutStart( BYTE* pbyBuffer )
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_A_LENSE_FOCUS_OUT);
	WideCharToMultiByte(CP_ACP, NULL, CMD_A_LENSE_FOCUS_OUT, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_A_LENSE_FOCUS_OUT);
	memcpy(pbyBuffer+0, CMD_A_LENSE_FOCUS_OUT, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_A_LENSE_ZOOM_TELE
int CU2SRProtoParser::ALense_ZoomTeleStart( BYTE* pbyBuffer )
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_A_LENSE_ZOOM_TELE);
	WideCharToMultiByte(CP_ACP, NULL, CMD_A_LENSE_ZOOM_TELE, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_A_LENSE_ZOOM_TELE);
	memcpy(pbyBuffer+0, CMD_A_LENSE_ZOOM_TELE, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_A_LENSE_ZOOM_WIDE
int CU2SRProtoParser::ALense_ZoomWideStart( BYTE* pbyBuffer )
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_A_LENSE_ZOOM_WIDE);
	WideCharToMultiByte(CP_ACP, NULL, CMD_A_LENSE_ZOOM_WIDE, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_A_LENSE_ZOOM_WIDE);
	memcpy(pbyBuffer+0, CMD_A_LENSE_ZOOM_WIDE, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_A_LENSE_STOP_FOCUS_ZOOM
int CU2SRProtoParser::ALense_ZFStop( BYTE* pbyBuffer )
{
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_A_LENSE_STOP_FOCUS_ZOOM);
	WideCharToMultiByte(CP_ACP, NULL, CMD_A_LENSE_STOP_FOCUS_ZOOM, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_A_LENSE_STOP_FOCUS_ZOOM);
	memcpy(pbyBuffer+0, CMD_A_LENSE_STOP_FOCUS_ZOOM, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_A_LENSE_MOVE_ZOOM
int CU2SRProtoParser::ALense_ZoomMoveTo(BYTE* pbyBuffer, DARR_PARAM dArrParam)
{
	CString str;
	str.Format(_T("Az=%04d\r"), (int)dArrParam[0]);
	int iLen =  str.GetLength();
#ifdef UNICODE
	WideCharToMultiByte(CP_ACP, NULL, str, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
#else
	memcpy(pbyBuffer+0, str, str.GetLength());	
#endif
	return iLen;
}

/////////////////////////////////////////////////
// 7-1.
// CMD_A_LENSE_BYPASS_CMD
BOOL CU2SRProtoParser::ALense_CmdByPass(BYTE* pCmd, int nLen, BYTE* pRecvBuf, int nRecvLen)
{
	ASSERT(pCmd && pRecvBuf);

	int iLen = 0;
#ifdef UNICODE
	int cLen = wcslen(CMD_A_LENSE_BYPASS_CMD);
#else
	int cLen = wcslen(CMD_A_LENSE_BYPASS_CMD);
#endif
	

	FillHeader(pCmd);
	iLen += 0;

	memcpy(pCmd+iLen, CMD_A_LENSE_BYPASS_CMD, cLen);
	iLen += cLen;

	memcpy(pCmd+iLen, pCmd, nLen);
	iLen += nLen;

	//yeun 20140201 FillTail(iLen);
	iLen += 1;

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
// 8. 열영상 Lense control
////////////////////////////////////////////////////////////////////////////////
// CMD_T_LENSE_FOCUS_IN
int CU2SRProtoParser::TLense_FocusIn( BYTE* pbyBuffer )
{
	//전압 제어 
	int iLen = wcslen(CMD_T_LENSE_FOCUS_NEAR);
	WideCharToMultiByte(CP_ACP, NULL, CMD_T_LENSE_FOCUS_NEAR, -1, (LPSTR)pbyBuffer, iLen, NULL, FALSE);
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
	return iLen;
/*
		
			switch (m_iProtoThermCam)
				{
				case THERMCAM_CANTRONIC:
					{
						return CProtoCantronic::SetFocusNear( pbyBuffer );
		
					}
					break;
				case THERMCAM_OPGAL:
					{
					
		
					}
					break;
				case THERMCAM_FLIR:
					{
						
					}
				default:
					break;
				}*/
		


	return 0;

}

// CMD_T_LENSE_FOCUS_OUT
int CU2SRProtoParser::TLense_FocusOut( BYTE* pbyBuffer )
{

	//전압 제어 
	int iLen = wcslen(CMD_T_LENSE_FOCUS_FAR);
	WideCharToMultiByte(CP_ACP, NULL, CMD_T_LENSE_FOCUS_FAR, -1, (LPSTR)pbyBuffer, iLen, NULL, FALSE);
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;

	return iLen;
/*
	
		switch (m_iProtoThermCam)
		{
		case THERMCAM_CANTRONIC:
			{
				return CProtoCantronic::SetFocusFar( pbyBuffer );
			}
			break;
		case THERMCAM_OPGAL:
			{
				//전압 제어 
				int iLen = wcslen(CMD_T_LENSE_FOCUS_FAR);
				memcpy(pbyBuffer+0, CMD_T_LENSE_FOCUS_FAR, iLen);	
				pbyBuffer[iLen++] = 0x0d;
				return iLen;
			}
			break;
		case THERMCAM_FLIR:
			{
	
			}
		default:
			break;
		}
	
		return 0;*/
	

}
int CU2SRProtoParser::TLense_FocusStop( BYTE* pbyBuffer )
{
	//전압 제어 
	int iLen = wcslen(CMD_T_LENSE_FOCUS_STOP);
	WideCharToMultiByte(CP_ACP, NULL, CMD_T_LENSE_FOCUS_STOP, -1, (LPSTR)pbyBuffer, iLen, NULL, FALSE);
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;

	return iLen;			
/*
	
			switch (m_iProtoThermCam)
			{
			case THERMCAM_CANTRONIC:
				{
					return 0;
				}
			case THERMCAM_OPGAL:
				{
						
				}
				break;
			default:
				break;
			}
	
	
		return 0;*/
	
}
// CMD_T_LENSE_FOCUS_FINE_IN
int CU2SRProtoParser::TLense_FocusFineIn( BYTE* pbyBuffer )
{

	/*
	switch (m_iProtoThermCam)
		{
		case THERMCAM_CANTRONIC:
			return CProtoCantronic::SetFocusFineNear( pbyBuffer );
		default:
			return 0;
		}*/
	
	return 0;
}

// CMD_T_LENSE_FOCUS_FINE_OUT
int CU2SRProtoParser::TLense_FocusFineOut( BYTE* pbyBuffer )
{
	/*
					switch (m_iProtoThermCam)
								{
								case THERMCAM_CANTRONIC:
									return CProtoCantronic::SetFocusFineFar( pbyBuffer );
								default:
									return 0;
								}*/
				
				return 0;
	
}


int CU2SRProtoParser::TLense_GetDZoom( BYTE* pbyBuffer )
{

	/*
			switch (m_iProtoThermCam)
				{
				case THERMCAM_CANTRONIC:
					{
						return CProtoCantronic::ReqDZoom( pbyBuffer );
		
						/ *
						FillHeader(pbyBuffer);
										memcpy(pbyBuffer+0, CMD_T_LENSE_ZOOM_GET, wcslen(CMD_T_LENSE_ZOOM_GET));
										FillTail(pbyBuffer);
										return pbyBuffer[7];* /
						
					}
					break;
				case THERMCAM_OPGAL:
					{
					/ *
							BYTE byCmd[5];
										CString strHexa, str;
							
										//m_protoOpgal.GetZoom(byCmd);
										
										ConvertByteToHexa(byCmd, 5, strHexa);
										str.Format("TC=?:%s", strHexa);
										FillHeader(pbyBuffer);
										memcpy(pbyBuffer+__PHS__, str, str.GetLength(pbyBuffer));
										FillTail(pbyBuffer);
										return pbyBuffer[15];* /
						
					}
					break;
				case THERMCAM_FLIR:
					/ *
					{
									BYTE byCmd[PROTO_BUFFER_SIZE];
									CString strHexa, str;
						
									int iLen = m_protoFlirTau2.ReqDigitalZoom(byCmd);
						
									ConvertByteToHexa(byCmd, iLen, strHexa);
									str.Format("TC=?:%s", strHexa);
									FillHeader(pbyBuffer);
									memcpy(pbyBuffer+__PHS__, str, str.GetLength(pbyBuffer));
									FillTail(pbyBuffer);
									SendRecv(pbyBuffer, str.GetLength(pbyBuffer)+(__PHS__+__PTS__), NULL, 24+6 );
						
									byte pBuf[PROTO_BUFFER_SIZE] = {0x00, };
									StringHexaToByteHexa(&pbyBuffer[6], pBuf, iLen+2);
									double dZoom = m_protoFlirTau2.ParseDigitalZoomPacket(pBuf);
									
									CString strZoom;
									strZoom.Format("%d", (int)dZoom);
									return strZoom.GetAt(0);
								}* /
					
					break;
				default:		
					ASSERT(FALSE);
					break;
				}*/
		


	return 0;
}

int CU2SRProtoParser::TLense_SetDZoom( BYTE* pbyBuffer, int iDZoom )
{
	

	//  [4/6/2014 Yeun]
	/*
	switch (m_iProtoThermCam)
		{
		case THERMCAM_CANTRONIC:
			{
				return CProtoCantronic::SetDZoom( pbyBuffer, iDZoom );
			}
			break;
		case THERMCAM_OPGAL:
			{
				/ *
				BYTE byCmd[5];
				CString strHexa, str;
	
				//m_protoOpgal.GetZoom(byCmd);
	
				ConvertByteToHexa(byCmd, 5, strHexa);
				str.Format("TC=?:%s", strHexa);
				FillHeader(pbyBuffer);
				memcpy(pbyBuffer+__PHS__, str, str.GetLength(pbyBuffer));
				FillTail(pbyBuffer);
				return pbyBuffer[15];* /
	
			}
			break;
		case THERMCAM_FLIR:
			/ *
			{
			BYTE byCmd[PROTO_BUFFER_SIZE];
			CString strHexa, str;
	
			int iLen = m_protoFlirTau2.ReqDigitalZoom(byCmd);
	
			ConvertByteToHexa(byCmd, iLen, strHexa);
			str.Format("TC=?:%s", strHexa);
			FillHeader(pbyBuffer);
			memcpy(pbyBuffer+__PHS__, str, str.GetLength(pbyBuffer));
			FillTail(pbyBuffer);
			SendRecv(pbyBuffer, str.GetLength(pbyBuffer)+(__PHS__+__PTS__), NULL, 24+6 );
	
			byte pBuf[PROTO_BUFFER_SIZE] = {0x00, };
			StringHexaToByteHexa(&pbyBuffer[6], pBuf, iLen+2);
			double dZoom = m_protoFlirTau2.ParseDigitalZoomPacket(pBuf);
	
			CString strZoom;
			strZoom.Format("%d", (int)dZoom);
			return strZoom.GetAt(0);
			}* /
	
			break;
		default:		
			ASSERT(FALSE);
			break;
		}*/
	


	return 0;
}
// CMD_T_LENSE_ZOOM_TELE
int CU2SRProtoParser::TLense_ZoomTele( BYTE* pbyBuffer )
{
	//  [4/6/2014 Yeun]

	/*
			switch (m_iProtoThermCam)
				{
				case THERMCAM_CANTRONIC:
					{
						//디지털 줌만 존재
						return 0;				
		
						/ *
						char szCurZoom = TLense_GetZoom(pbyBuffer);
							
										FillHeader(pbyBuffer);
										if(szCurZoom == '1')
											memcpy(pbyBuffer+0, CMD_T_LENSE_ZOOM_2, wcslen(CMD_T_LENSE_ZOOM_2));
										else if(szCurZoom == '2')
											memcpy(pbyBuffer+0, CMD_T_LENSE_ZOOM_4, wcslen(CMD_T_LENSE_ZOOM_4));
										else 
											return;
							
										FillTail(pbyBuffer);* /
						
					}
					break;
				case THERMCAM_OPGAL:
					{
						/ *
						BYTE byCmd[5];
										BYTE byCurZoom = TLense_GetZoom(pbyBuffer);
										
										if(byCurZoom == '0')
											m_protoOpgal.SetZoom(byCmd, 1);
										else if(byCurZoom == '1')
											m_protoOpgal.SetZoom(byCmd, 2);
										else if(byCurZoom == '2')
											return;
										else
										{
											ASSERT(FALSE);
											return;
										}
										CString strHexa, str;
										ConvertByteToHexa(byCmd, 5, strHexa);
										str.Format("TC=S:%s", strHexa);
										FillHeader(pbyBuffer);
										memcpy(pbyBuffer+__PHS__, str, str.GetLength(pbyBuffer));
										FillTail(pbyBuffer);* /
						
					}
					break;
				case THERMCAM_FLIR:
					{
						/ *
						BYTE byCmd[BUFSIZ];
										char chCurZoom = TLense_GetZoom(pbyBuffer);
										chCurZoom+=1;
							
										if( chCurZoom >= '9')
											chCurZoom = '8';
							
										chCurZoom -= '0';
										DWORD dWord = chCurZoom;
										int iLen = m_protoFlirTau2.SetDigitalZoom( byCmd, dWord );
							
										CString strHexa, str;
										ConvertByteToHexa(byCmd, iLen, strHexa);
										str.Format("TC=S:%s", strHexa);
										FillHeader(pbyBuffer);
										memcpy(pbyBuffer+__PHS__, str, str.GetLength(pbyBuffer));
										FillTail(pbyBuffer);* /
						
					}
					break;
				default:
					ASSERT(FALSE);
					break;
				}*/
		


	return 0;
}

// CMD_T_LENSE_ZOOM_WIDE
int CU2SRProtoParser::TLense_ZoomWide( BYTE* pbyBuffer )
{
/*
		switch (m_iProtoThermCam)
		{
		case THERMCAM_CANTRONIC:
			{
				char szCurZoom = TLense_GetZoom(pbyBuffer);
	
				FillHeader(pbyBuffer);
				if(szCurZoom == '4')
					memcpy(pbyBuffer+0, CMD_T_LENSE_ZOOM_2, wcslen(CMD_T_LENSE_ZOOM_2));
				else if(szCurZoom == '2')
					memcpy(pbyBuffer+0, CMD_T_LENSE_ZOOM_1, wcslen(CMD_T_LENSE_ZOOM_1));
				else 
					return;
	
				FillTail(pbyBuffer);
				SendRecv(pbyBuffer, wcslen(CMD_T_LENSE_ZOOM_1)+(0+1), NULL, 0);
			}
			break;
		case THERMCAM_OPGAL:
			{
				BYTE byCmd[5];
				BYTE byCurZoom = TLense_GetZoom(pbyBuffer);
	
				if(byCurZoom == '0')
					return;
				else if(byCurZoom == '1')
					m_protoOpgal.SetZoom(byCmd, 0);
				else if(byCurZoom == '2')
					m_protoOpgal.SetZoom(byCmd, 1);
				else
				{
					ASSERT(FALSE);
					return;
				}
		
				CString strHexa, str;
				ConvertByteToHexa(byCmd, 5, strHexa);
				str.Format("TC=S:%s", strHexa);
				FillHeader(pbyBuffer);
				memcpy(pbyBuffer+__PHS__, str, str.GetLength(pbyBuffer));
				FillTail(pbyBuffer);
				SendRecv(pbyBuffer, str.GetLength(pbyBuffer)+(__PHS__+__PTS__), NULL, 0);
			}
			break;
		case THERMCAM_FLIR:
			{
				BYTE byCmd[BUFSIZ];
				char chCurZoom = TLense_GetZoom(pbyBuffer);
				chCurZoom-=1;
	
				if( chCurZoom <= '0')
					chCurZoom = '1';
	
				DWORD dWord = chCurZoom - '0';
				int iLen = m_protoFlirTau2.SetDigitalZoom( byCmd, dWord );
	
				CString strHexa, str;
				ConvertByteToHexa(byCmd, iLen, strHexa);
				str.Format("TC=S:%s", strHexa);
				FillHeader(pbyBuffer);
				memcpy(pbyBuffer+__PHS__, str, str.GetLength(pbyBuffer));
				FillTail(pbyBuffer);
				SendRecv(pbyBuffer, str.GetLength(pbyBuffer)+(__PHS__+__PTS__), NULL, 0);
			}
			break;
		default:
			ASSERT(FALSE);
			break;
		}*/


	return 0;
}

int CU2SRProtoParser::TLense_ZoomStop( BYTE* pbyBuffer )
{
	return 0;
}

int CU2SRProtoParser::TLense_GetPolarity( BYTE* pbyBuffer )
{
	//  [4/6/2014 Yeun]
	/*
switch(m_iProtoThermCam)
	{
	case THERMCAM_CANTRONIC:
		{			
			return CProtoCantronic::ReqPolarity(pbyBuffer);
		}
		break;
	case THERMCAM_OPGAL:
		{		

		}
		break;
	case THERMCAM_FLIR:
		{		

		}
		break;
	default:
		ASSERT(FALSE);
		break;
	}


	FillHeader(pbyBuffer);
#ifdef UNICODE
	memcpy(pbyBuffer+0, CMD_T_LENSE_POL_GET, wcslen(CMD_T_LENSE_POL_GET));
#else
	memcpy(pbyBuffer+0, CMD_T_LENSE_POL_GET, wcslen(CMD_T_LENSE_POL_GET));
#endif

	FillTail(pbyBuffer);

	char szRet[3] = {pbyBuffer[8],pbyBuffer[9],0};
	
	//return (char)strtoul(szRet, NULL, 16);	// bw, wb 의 각 뒷자리를 의미한다.

*/


	return 0;
}

int CU2SRProtoParser::TLense_Polarity_Change( BYTE* pbyBuffer )
{
	/*
	switch (m_iProtoThermCam)
		{
		case THERMCAM_CANTRONIC:
			{
				char szCurPol = TLense_GetPolarity(pbyBuffer);
	
				FillHeader(pbyBuffer);
				if(szCurPol == 'w')
					memcpy(pbyBuffer+0, CMD_T_LENSE_POL_WB, wcslen(CMD_T_LENSE_POL_WB));
				else if(szCurPol == 'b')
					memcpy(pbyBuffer+0, CMD_T_LENSE_POL_BW, wcslen(CMD_T_LENSE_POL_BW));
				else 
					return;
	
				FillTail(pbyBuffer);
			}
			break;
		default:
			ASSERT(FALSE);
			break;
		}*/


	return 0;

}

int CU2SRProtoParser::TLense_SetPolarity(BYTE* pbyBuffer, int iBlackHot)// 1-White hot, 0-Black hot
{
	//  [4/6/2014 Yeun]
#if 0
	switch (m_iProtoThermCam)
	{
	case THERMCAM_CANTRONIC:
	{
#if 0
		if (iBlackHot == 1)
			return CProtoCantronic::SetWhiteHot(pbyBuffer);
		else
			return CProtoCantronic::SetBlackHot(pbyBuffer);
#endif
	}
	break;
	case THERMCAM_OPGAL:
	{
#if 0

		/ *
			BYTE byCmd[5];
		//BYTE byReturn[5];

		m_protoOpgal.SetPolarity(byCmd, iBlackHot);

		CString strHexa, str;
		ConvertByteToHexa(byCmd, 5, strHexa);
		str.Format("TC=S:%s", strHexa);
		FillHeader(pbyBuffer);
		memcpy(pbyBuffer + __PHS__, str, str.GetLength(pbyBuffer));
		FillTail(pbyBuffer);
		SendRecv(pbyBuffer, str.GetLength(pbyBuffer) + (__PHS__ + __PTS__), NULL, 0); */
#endif
	}
	break;
	case THERMCAM_FLIR:
	{
#if 0
		BYTE byCmd[BUFSIZ];

		int iLen = 0;
		if (iBlackHot == 1)//white hot
			iLen = m_protoFlirTau2.SetVideoPalette(byCmd, 0);
		else if (iBlackHot == 0)
			iLen = m_protoFlirTau2.SetVideoPalette(byCmd, 1);

		CString strHexa, str;
		ConvertByteToHexa(byCmd, iLen, strHexa);
		str.Format("TC=S:%s", strHexa);
		FillHeader(pbyBuffer);
		memcpy(pbyBuffer + __PHS__, str, str.GetLength(pbyBuffer));
		FillTail(pbyBuffer);
		SendRecv(pbyBuffer, str.GetLength(pbyBuffer) + (__PHS__ + __PTS__), NULL, 0); */
#endif
	}
	break;
	default:
		ASSERT(FALSE);
		break;
	}

#endif


	return 0;
}
int CU2SRProtoParser::TLense_Power_ON( BYTE* pbyBuffer )
{
	int iLen = wcslen(CMD_T_LENSE_POWER_ON);
	WideCharToMultiByte(CP_ACP, NULL, CMD_T_LENSE_POWER_ON, -1, (LPSTR)pbyBuffer, iLen, NULL, FALSE);
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
	return iLen;
}

int CU2SRProtoParser::TLense_Power_OFF(BYTE* pbyBuffer)
{
	int iLen = wcslen(CMD_T_LENSE_POWER_OFF);
	WideCharToMultiByte(CP_ACP, NULL, CMD_T_LENSE_POWER_OFF, -1, (LPSTR)pbyBuffer, iLen, NULL, FALSE);
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
	return iLen;
}


/////////////////////////////////////////////////
// 8-1.
// CMD_T_LENSE_BYPASS_CMD
BOOL CU2SRProtoParser::TLense_CmdByPass(BYTE* pCmd, int nLen, BYTE* pRecvBuf, int nRecvLen)
{
	ASSERT(pCmd && pRecvBuf);
	
	int iLen = 0;
#ifdef UNICODE
	int cLen = wcslen(CMD_T_LENSE_BYPASS_CMD);
#else
	int cLen = wcslen(CMD_T_LENSE_BYPASS_CMD);
#endif

	FillHeader(pCmd);
	iLen += 0;

	memcpy(pCmd+iLen, CMD_T_LENSE_BYPASS_CMD, cLen);
	iLen += cLen;

	memcpy(pCmd+iLen, pCmd, nLen);
	iLen += nLen;

	FillTail(pCmd);
	iLen += 1;

	memcpy(pRecvBuf, pCmd, nRecvLen);
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
// 9. 기타 Command
////////////////////////////////////////////////////////////////////////////////
// CMD_POWER_ON
BOOL CU2SRProtoParser::PowerOn( BYTE* pbyBuffer )
{
	int i=0;
	pbyBuffer[i++] = 'P';
	pbyBuffer[i++] = 'W';
	pbyBuffer[i++] = '=';
	pbyBuffer[i++] = 'O';
	pbyBuffer[i++] = 0x0d;
	pbyBuffer[i] = 0x00;
	return i;
}

// CMD_POWER_OFF
int CU2SRProtoParser::PowerOff( BYTE* pbyBuffer )
{

	//  [3/14/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_POWER_OFF);
	WideCharToMultiByte(CP_ACP, NULL, CMD_POWER_OFF, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_POWER_OFF);
	memcpy(pbyBuffer+0, CMD_POWER_OFF, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;

}

// CMD_POWER_Q
int CU2SRProtoParser::GetPower( BYTE* pbyBuffer )
{

	//  [3/15/2014 Yeun]
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_POWER_Q);
	WideCharToMultiByte(CP_ACP, NULL, CMD_POWER_Q, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_POWER_Q);
	memcpy(pbyBuffer+0, CMD_POWER_Q, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;


/*
	FillHeader(pbyBuffer);
#ifdef UNICODE
	memcpy(pbyBuffer+0, CMD_POWER_Q, wcslen(CMD_POWER_Q));
#else
	memcpy(pbyBuffer+0, CMD_POWER_Q, wcslen(CMD_POWER_Q));
#endif

	FillTail(pbyBuffer);
*/
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
// 10. Target Preset 및 Auto Focusing 운용
////////////////////////////////////////////////////////////////////////////////
// CMD_PS_POINT_HOME_PAN
int CU2SRProtoParser::MovePanTiltHome( BYTE* pbyBuffer )
{
	int i=0;
	pbyBuffer[i++] = 'H';
	pbyBuffer[i++] = 'M';
	pbyBuffer[i++] = '=';
	pbyBuffer[i++] = 'C';
	pbyBuffer[i++] = 0x0d;
	pbyBuffer[i] = 0x00;
	return i;
}


int CU2SRProtoParser::SetPanTiltZeroPos( BYTE* pbyBuffer )
{
	FillHeader(pbyBuffer);
#ifdef UNICODE
	memcpy(pbyBuffer+0, CMD_PS_POINT_SET_ZEROPOS, wcslen(CMD_PS_POINT_SET_ZEROPOS));
#else
	memcpy(pbyBuffer+0, CMD_PS_POINT_SET_ZEROPOS, wcslen(CMD_PS_POINT_SET_ZEROPOS));
#endif
	FillTail(pbyBuffer);

	return 0;
}

int CU2SRProtoParser::ReadPanTiltHome_Status( BYTE* pbyBuffer )
{
	int i=0;
	pbyBuffer[i++] = 'H';
	pbyBuffer[i++] = 'M';
	pbyBuffer[i++] = '=';
	pbyBuffer[i++] = '?';
	pbyBuffer[i++] = 0x0d;
	pbyBuffer[i] = 0x00;
	return i;
}

int CU2SRProtoParser::MovePanTiltZeroPos( BYTE* pbyBuffer )
{
	FillHeader(pbyBuffer);
#ifdef UNICODE
	memcpy(pbyBuffer+0, CMD_PS_POINT_HOME_ZEROPOS, wcslen(CMD_PS_POINT_HOME_ZEROPOS));
#else
	memcpy(pbyBuffer+0, CMD_PS_POINT_HOME_ZEROPOS, wcslen(CMD_PS_POINT_HOME_ZEROPOS));
#endif
	FillTail(pbyBuffer);

	return 0;
}



// CMD_PS_POINT_LINK
BOOL CU2SRProtoParser::LinkPreset(BYTE* pbyBuffer, int nPoint)
{
	CString str;
	str.Format(CMD_PS_POINT_LINK, nPoint);

	FillHeader(pbyBuffer);
	memcpy(pbyBuffer+0, str, str.GetLength());
	
	FillTail(pbyBuffer);

	return 0;
}

int CU2SRProtoParser::LinkPreset( BYTE* pbyBuffer, DARR_PARAM dArrParam )
{
	CString strEditPoint;
	strEditPoint.Format(_T("PL=%03d\r"), (int)dArrParam[0]);

	int iLen =  strEditPoint.GetLength();
#ifdef UNICODE
	WideCharToMultiByte(CP_ACP, NULL, strEditPoint, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen] = 0x00;
#else
	memcpy(pbyBuffer+0, strEditPoint, strEditPoint.GetLength());	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}
// CMD_PS_POINT_SET
BOOL CU2SRProtoParser::SetPreset(BYTE* pbyBuffer, int nPoint)
{
	CString str;
	str.Format(CMD_PS_POINT_SET, nPoint);

	FillHeader(pbyBuffer);

	memcpy(pbyBuffer+0, str, str.GetLength());
	FillTail(pbyBuffer);

	return 0;
}
int CU2SRProtoParser::GetPreset(BYTE* pbyBuffer, DARR_PARAM dArrParam)
{
	CString strEditPoint;
	strEditPoint.Format(_T("PG=%03d\r"), (int)dArrParam[0]);

	int iLen = strEditPoint.GetLength();
#ifdef UNICODE
	WideCharToMultiByte(CP_ACP, NULL, strEditPoint, -1, (LPSTR)pbyBuffer, iLen, NULL, FALSE);
	pbyBuffer[iLen] = 0x00;
#else
	//iLen = wcslen(CMD_PS_POINT_ZONE);
	memcpy(pbyBuffer + 0, strEditPoint, strEditPoint.GetLength());
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_PS_POINT_PUT
BOOL CU2SRProtoParser::PutPreset(BYTE* pbyBuffer, int nPoint, CString strAngle)
{
	CString strEditPoint;
	strEditPoint.Format(CMD_PS_POINT_PUT, nPoint, strAngle);

	FillHeader(pbyBuffer);
	memcpy(pbyBuffer+0, strEditPoint, strEditPoint.GetLength());
	FillTail(pbyBuffer);

	return 0;
	
}

int CU2SRProtoParser::PutPreset( BYTE* pbyBuffer, DARR_PARAM dArrParam )
{
	CString strEditPoint;
	strEditPoint.Format(_T("PP=%03d:%08.04lf,%+08.04lf,%05d,%05d\r"), (int)dArrParam[0], dArrParam[1], dArrParam[2], (int)dArrParam[4], (int)dArrParam[3]);

	int iLen =  strEditPoint.GetLength();
#ifdef UNICODE
	WideCharToMultiByte(CP_ACP, NULL, strEditPoint, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen] = 0x00;
#else
	//iLen = wcslen(CMD_PS_POINT_ZONE);
	memcpy(pbyBuffer+0, strEditPoint, strEditPoint.GetLength());
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}


// CMD_PS_POINT_MOVE
BOOL CU2SRProtoParser::MovePreset( BYTE* pbyBuffer )
{
	/*
	FillHeader(pbyBuffer);
	#ifdef UNICODE
		memcpy(pbyBuffer+0, CMD_PS_POINT_MOVE, wcslen(CMD_PS_POINT_MOVE));
	#else
		memcpy(pbyBuffer+0, CMD_PS_POINT_MOVE, wcslen(CMD_PS_POINT_MOVE));
	#endif
		
		FillTail(pbyBuffer);
	
		return 0;
		TRACE("MovePreset\r\n");*/
	
	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_PS_POINT_MOVE);
	WideCharToMultiByte(CP_ACP, NULL, CMD_PS_POINT_MOVE, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
#else
	iLen = wcslen(CMD_PS_POINT_ZONE);
	memcpy(pbyBuffer+0, CMD_PS_POINT_MOVE, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;
}

// CMD_PS_POINT_ZONE
int CU2SRProtoParser::SyncPreset( BYTE* pbyBuffer )
{
/*
	FillHeader(pbyBuffer);
#ifdef UNICODE
	memcpy(pbyBuffer+0, CMD_PS_POINT_ZONE, wcslen(CMD_PS_POINT_ZONE));
#else
	memcpy(pbyBuffer+0, CMD_PS_POINT_ZONE, wcslen(CMD_PS_POINT_ZONE));
#endif
	
	FillTail(pbyBuffer);*/


	int iLen = 0;
#ifdef UNICODE
	iLen = wcslen(CMD_PS_POINT_ZONE);
	WideCharToMultiByte(CP_ACP, NULL, CMD_PS_POINT_ZONE, -1, (LPSTR)pbyBuffer,  iLen, NULL, FALSE);	
	pbyBuffer[iLen++] = 0x0d;
	pbyBuffer[iLen] = 0x00;
#else
	iLen = wcslen(CMD_PS_POINT_ZONE);
	memcpy(pbyBuffer+0, CMD_PS_POINT_ZONE, iLen);	
	pbyBuffer[iLen++] = 0x0d;
#endif
	return iLen;

}

// CMD_PS_POINT_HOME_TILT
int CU2SRProtoParser::MoveTiltHome( BYTE* pbyBuffer )
{
	FillHeader(pbyBuffer);
#ifdef UNICODE
	memcpy(pbyBuffer+0, CMD_PS_POINT_HOME_TILT, wcslen(CMD_PS_POINT_HOME_TILT));
#else
	memcpy(pbyBuffer+0, CMD_PS_POINT_HOME_TILT, wcslen(CMD_PS_POINT_HOME_TILT));
#endif
	
	FillTail(pbyBuffer);
	return 0;

}

////////////////////////////////////////////////////////////////////////////////
// 99. miscellaneous
////////////////////////////////////////////////////////////////////////////////
// 현재좌표
BOOL CU2SRProtoParser::GetAngle(BYTE* pbyBuffer)
{
	int i=0;
	pbyBuffer[i++] = 'G';
	pbyBuffer[i++] = 'C';
	pbyBuffer[i++] = '=';
	pbyBuffer[i++] = 'L';
	pbyBuffer[i++] = 0x0d;
	pbyBuffer[i] = 0x00;
	return i;
/*
	strAngle.Format("%s", this->AngleGetValue(pbyBuffer));

	TRACE("CU2SRProtoParser::GetAngle(%s)\r\n", strAngle);

	strAngle.Replace(",", " ");

	if (!strAngle.Compare(CST_ERR_ANGLE))
		return FALSE;
*/
	return TRUE;
}

int CU2SRProtoParser::GetAngleFocusZoom( BYTE* pbyBuffer )
{
	FillHeader(pbyBuffer);
#ifdef UNICODE
	memcpy(pbyBuffer+0, CMD_GET_ANGLE_F_Z, wcslen(CMD_GET_ANGLE_F_Z));
#else
	memcpy(pbyBuffer+0, CMD_GET_ANGLE_F_Z, wcslen(CMD_GET_ANGLE_F_Z));
#endif
	
	FillTail(pbyBuffer);

	return 0;
}

// 초기화
BOOL CU2SRProtoParser::PresetSync(BYTE* pbyBuffer, CString strAngle, int nPoint)
{
	BOOL bRet[3] = { FALSE, FALSE, FALSE };

	bRet[0] = this->PutPreset(pbyBuffer, nPoint, strAngle);
	
	if (bRet[0])
	{
		Sleep(150);
		bRet[1] = this->LinkPreset(pbyBuffer, nPoint);

		if (bRet[1])
		{
			Sleep(150);
			bRet[2] = this->SyncPreset(pbyBuffer);
		}
	}

	return (bRet[0] && bRet[1] && bRet[2]);
}

// 표적이동
BOOL CU2SRProtoParser::MoveToTarget(BYTE* pbyBuffer, int nPoint)
{
	BOOL bRet[2] = { FALSE, FALSE };

	bRet[0] = this->LinkPreset(pbyBuffer, nPoint);
	
	if (bRet[0])
	{
		Sleep(150);
		bRet[1] = this->MovePreset(pbyBuffer);
	}
	
	return (bRet[0] && bRet[1]);
}

BOOL CU2SRProtoParser::AutoTrackingON( BYTE* pbyBuffer )
{
	CString str;
	str.Format(CMD_TRACKING_ON);
	
	FillHeader(pbyBuffer);
	memcpy(pbyBuffer+0, str, str.GetLength());
	FillTail(pbyBuffer);
	return TRUE;
}

BOOL CU2SRProtoParser::AutoTrackingOFF( BYTE* pbyBuffer )
{
	CString str;
	str.Format(CMD_TRACKING_OFF);
	
	FillHeader(pbyBuffer);
	memcpy(pbyBuffer+0, str, str.GetLength());
	FillTail(pbyBuffer);
	return TRUE;
}

BOOL CU2SRProtoParser::AutoTILTMove(BYTE* pbyBuffer, int Direction, int Speed)
{
	CString str;
	if(Direction == -1)
		str.Format(CMD_TILT_MOVEAUTO, "-", Speed);
	if(Direction == 1)
		str.Format(CMD_TILT_MOVEAUTO, "+", Speed);
	
	FillHeader(pbyBuffer);
	memcpy(pbyBuffer+0, str, str.GetLength());
	FillTail(pbyBuffer);
	return TRUE;
}

BOOL CU2SRProtoParser::AutoPANMove(BYTE* pbyBuffer, int Direction, int Speed)
{
	CString str;
	if(Direction == -1)
		str.Format(CMD_PAN_MOVEAUTO, "-", Speed);
	if(Direction == 1)
		str.Format(CMD_PAN_MOVEAUTO, "+", Speed);
	
	
	FillHeader(pbyBuffer);
	memcpy(pbyBuffer+0, str, str.GetLength());
	FillTail(pbyBuffer);
	return TRUE;
}
CString CU2SRProtoParser::Util_ConvertAscii2Hexa(CString csValue)
{
	char c1 = csValue.GetAt(0);
	char c2 = csValue.GetAt(1);

	int i1 = CU2SRProtoParser::Util_GetDecimalValue(c1);
	int i2 = CU2SRProtoParser::Util_GetDecimalValue(c2);

	CString csHexa;
	int iHexa = i1* 16 + i2;
	csHexa.Format(_T("%d"), iHexa);
	return csHexa;
}
// Util_GetDecimalValue
int CU2SRProtoParser::Util_GetDecimalValue(char c)
{
	int i10 = toupper(c);

	if (i10 >= 'A')
		i10 = i10 - 'A' + 10;
	else
		i10 = i10 - '0';

	return i10;
}
// Util_GetBinaryData
CString CU2SRProtoParser::Util_GetBinaryData(CString csValue)
{
#ifdef UNICODE
	int nValue = _wtoi(csValue);
#else
	int nValue = atoi(csValue);
#endif
	CString csBinary;
	int nBuff[8];
	int nNmg = nValue; // 나머지.
	int nStopPos = -1;

	//--> 원하는 진법으로 나누어 그 나머지를 넣는다.
	for( int i=0; i<8; i++ )
	{
		nBuff[i] = (nNmg % 2);		//<== 2 로 나눈 나머지..
		nNmg >>= 1;					//<== 좌측으로 1비트 쉬프트..2로 나눈 효과..

		//--> 더이상 나눌값이 없음.
		if( nNmg == 0 )
		{
			nStopPos = i;
			break;
		}
	}

	char cBinData[12];
	memset(cBinData, 0, 12);

	char cChangeCode;
	//	BOOL bChangeError = FALSE;

	int nInPos = 0;

	//--> 따로 받아놓은 나머지 값을.. 꺼꾸로 출력하기 위해..
	for( int i=nStopPos; i>=0; i-- )
	{
		//--> Value를 2진수 문자로 변환.
		cChangeCode = nBuff[i] + '0';
		//		cChangeCode = cBin2Ascii( nBuff[i] );

		cBinData[nInPos++] = cChangeCode;
	}

	//--> 문자열의 끝 지정..
	cBinData[nInPos] = NULL;

	//--> 변환된 문자열 전달..
	int iFillCnt;
	CString csFillStr;
	iFillCnt = 8-nStopPos-1;
	for(int i=0; i<iFillCnt;++i)
		csFillStr.Insert(i, '0');

#ifdef UNICODE
	
#if 1
	WCHAR wstrData[10] = { 0, };	
	//MTOW(cBinData, wstrData, sizeof(wstrData));
	MultiByteToWideChar(CP_ACP, 0, cBinData, -1, wstrData, sizeof(wstrData));
	CString strBinData;  strBinData.Format(_T("%s"), wstrData);
	csBinary.Format( L"%s%s", csFillStr, strBinData);	
#endif

#else
	csBinary.Format( "%s%s", csFillStr, cBinData );
#endif
	// from LSB.
	//  [3/14/2014 Yeun]
	//protocol document 대로 하기 위해 문자열 뒤집지 않음 수정
	//csBinary.MakeReverse(); 

	// [16] => [00001000]
	// [32] => [00000100]

	return csBinary;
}
CString CU2SRProtoParser::Multi2Wide( char *pszSrc )
{	
	ASSERT(FALSE);
	/*
	if ( NULL == pszSrc )
			return CString ( _T("") );
		int        nLen = 0;
		TCHAR *ptzBuff = NULL;
		CString    strRet = _T("");
		if ( 0 < ( nLen = MultiByteToWideChar ( CP_ACP, 0, pszSrc, -1, NULL, 0 ) ) )
		{
			ptzBuff = new TCHAR[nLen];
			memset ( ptzBuff, 0x00, nLen * sizeof TCHAR );
			MultiByteToWideChar ( CP_ACP, 0, pszSrc, -1, ptzBuff, nLen );
			strRet = ptzBuff;
			delete[] ptzBuff;
		}
		else
			return CString ( _T("") );
		return strRet;*/
	return CString ( _T("") );
	
}

void CU2SRProtoParser::SetCurDZoom( int iZoom )
{
	//m_iDZoom = iZoom;
}

int CU2SRProtoParser::GetCurDZoom()
{
	return 0;//return m_iDZoom;
}

int CU2SRProtoParser::SetWrappingThermProto( BYTE* pbyBuffer, int iSrcLen, BOOL bRecv )
{
	CString strHexa;
	ConvertByteToHexa(pbyBuffer, iSrcLen, strHexa);

	CString str;
	if(bRecv)
		str.Format( _T("TC=?:%s\r"), strHexa );
	else
		str.Format( _T("TC=S:%s\r"), strHexa );

	int nLen = 0;
#ifdef UNICODE
	nLen = wcslen(str);
	WideCharToMultiByte(CP_ACP, NULL, str, -1, (LPSTR)pbyBuffer, nLen, NULL, FALSE);
	pbyBuffer[nLen] = 0x00;

#else
	memcpy(pbyBuffer, str, str.GetLength());
#endif
	return str.GetLength();
}

int CU2SRProtoParser::SetWrappingHighProto( BYTE* pbyBuffer, int iSrcLen )
{
	CString strHexa;
	ConvertByteToHexa(pbyBuffer, iSrcLen, strHexa);

	CString str;
	str.Format( _T("VC=S:%s\r"), strHexa );

	memcpy(pbyBuffer, str, str.GetLength());

	return str.GetLength();
}

int CU2SRProtoParser::SetWrappingLrfProto( BYTE* pbyBuffer, int iSrcLen, BOOL bRecv  )
{
	CString strHexa;
	ConvertByteToHexa(pbyBuffer, iSrcLen, strHexa);

	CString str;
	if(bRecv)
		str.Format( _T("LC=?:%s\r"), strHexa );
	else
		str.Format( _T("LC=S:%s\r"), strHexa );


	memcpy(pbyBuffer, str, str.GetLength());

	return str.GetLength();
}

