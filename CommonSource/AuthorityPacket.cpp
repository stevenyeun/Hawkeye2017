
#include "stdafx.h"
#include "AuthorityPacket.h"

/*
CString ParseAuthorityData(AUTHORITY_DATA authorityData)
{

	int nParsingLen = 1;
	WCHAR wstrData[AUTHORITY_DATA_LEN] = { 0, };
	char	strMultibyte[AUTHORITY_DATA_LEN] = { 0, };
	strMultibyte[0] = authorityData.data[AUTHORITY_DATA_LEN - 1];

#ifdef _UNICODE
	MultiByteToWideChar(CP_ACP, 0, strMultibyte, -1, wstrData, nParsingLen);
#else
	strncpy(_tsz, sz, nLen);
#endif

	CString strData;  strData.Format(_T("%d"), wstrData[0]);

	return strData;

}
*/
int ParseAuthorityDataToInt(AUTHORITY_DATA authorityData)
{
#ifdef _UNICODE
	WCHAR wstrData[AUTHORITY_DATA_LEN] = { 0, };
	char	strMultibyte[AUTHORITY_DATA_LEN] = { 0, };
	memcpy(strMultibyte, authorityData.data, sizeof(strMultibyte));
	
	MultiByteToWideChar(CP_ACP, 0, strMultibyte, -1, wstrData, sizeof(strMultibyte));
	
	CString strData;  strData.Format(_T("%s"), wstrData);

	return _wtoi(strData);
#else//steven 170404
		
	CString strData;  strData.Format("%s", authorityData.data);

	return atoi(strData);
#endif
}
double ParseAuthorityDataToDouble(AUTHORITY_DATA authorityData)
{
#ifdef _UNICODE
	WCHAR wstrData[AUTHORITY_DATA_LEN] = { 0, };
	char	strMultibyte[AUTHORITY_DATA_LEN] = { 0, };
	memcpy(strMultibyte, authorityData.data, sizeof(strMultibyte));

	MultiByteToWideChar(CP_ACP, 0, strMultibyte, -1, wstrData, sizeof(strMultibyte));

	CString strData;  strData.Format(_T("%s"), wstrData);

	return _wtof(strData);
#else//steven 170404

	CString strData;  strData.Format("%s", authorityData.data);

	return atoi(strData);
#endif
}

CString ParseAuthorityData2(AUTHORITY_DATA authorityData)
{
#ifdef _UNICODE
	WCHAR wstrData[AUTHORITY_DATA_LEN] = { 0, };
	char	strMultibyte[AUTHORITY_DATA_LEN] = { 0, };
	memcpy(strMultibyte, authorityData.data, sizeof(strMultibyte));

	MultiByteToWideChar(CP_ACP, 0, strMultibyte, -1, wstrData, sizeof(strMultibyte));

	CString strData;  strData.Format(_T("%s"), wstrData);

	return strData;
#else
	CString strData;  strData.Format("%s", authorityData.data);

	return strData;
#endif

	
}
void MakeAuthorityData(int nData, AUTHORITY_DATA& authData)
{
	char chStrData[AUTHORITY_DATA_LEN] = { 0, };

	sprintf(chStrData, "%d", nData);

	memcpy(authData.data, chStrData, sizeof(chStrData));

}
void MakeAuthorityData(double nData, AUTHORITY_DATA& authData)//double 변수를 제어권 데이터에 넣기
{
	char chStrData[AUTHORITY_DATA_LEN] = { 0, };

	sprintf(chStrData, "%02.1lf", nData);

	memcpy(authData.data, chStrData, sizeof(chStrData));
}
CString ConvertAuthorityPacketToString(const AUTHORITY_PACKET * pAuthorityPacket)
{
	CString strText;
	CString strData = ParseAuthorityData2(pAuthorityPacket->authorityData);

	switch (pAuthorityPacket->byCmdGroup)
	{
	case CMDGROUP_AUTHORITY:
	{
		switch (pAuthorityPacket->byCmdType)
		{
		case CMDTYPE_AUTHORITY_LOGIN:
			strText = _T("CMDTYPE_AUTHORITY_LOGIN = ") + strData;
			break;
		case CMDTYPE_AUTHORITY_REQUEST:
			strText = _T("CMDTYPE_AUTHORITY_REQUEST = ") + strData;
			break;
		case CMDTYPE_AUTHORITY_AUTHORIZATION:
			strText = _T("CMDTYPE_AUTHORITY_AUTHORIZATION = ") + strData;
			break;
		case CMDTYPE_AUTHORITY_DEPRIVATION:
			strText = _T("CMDTYPE_AUTHORITY_DEPRIVATION = ") + strData;
			break;
		case CMDTYPE_AUTHORITY_TEMPAUTHORITY_USE_NOTIFICATION:
			strText = _T("CMDTYPE_AUTHORITY_TEMPAUTHORITY_USE_NOTIFICATION = ") + strData;
			break;
		case CMDTYPE_AUTHORITY_TEMPAUTHORITY_RETURN_NOTIFICATION:
			strText = _T("CMDTYPE_AUTHORITY_TEMPAUTHORITY_RETURN_NOTIFICATION = ") + strData;
			break;
		case CMDTYPE_AUTHORITY_TEMPAUTHORITY_INUSE_NOTIFICATION:
			strText = _T("CMDTYPE_AUTHORITY_TEMPAUTHORITY_INUSE_NOTIFICATION = ") + strData;
			break;
		default:
			ASSERT(FALSE);
			break;
		}

	}
	break;
	case CMDGROUP_PTZCTRL:
	{
		switch (pAuthorityPacket->byCmdType)
		{
		case CMDTYPE_PTZCTRL_PAN_LEFT:
			strText = _T("CMDTYPE_PTZCTRL_PAN_LEFT = ") + strData;
			break;
		case CMDTYPE_PTZCTRL_PAN_RIGHT:
			strText = _T("CMDTYPE_PTZCTRL_PAN_RIGHT = ") + strData;
			break;
		case CMDTYPE_PTZCTRL_TILT_UP:
			strText = _T("CMDTYPE_PTZCTRL_TILT_UP = ") + strData;
			break;
		case CMDTYPE_PTZCTRL_TILT_DOWN:
			strText = _T("CMDTYPE_PTZCTRL_TILT_DOWN = ") + strData;
			break;
		case CMDTYPE_PTZCTRL_PT_LU:
			strText = _T("CMDTYPE_PTZCTRL_PT_LU = ") + strData;
			break;
		case CMDTYPE_PTZCTRL_PT_RU:
			strText = _T("CMDTYPE_PTZCTRL_PT_RU = ") + strData;
			break;
		case CMDTYPE_PTZCTRL_PT_LD:
			strText = _T("CMDTYPE_PTZCTRL_PT_LD = ") + strData;
			break;
		case CMDTYPE_PTZCTRL_PT_RD:
			strText = _T("CMDTYPE_PTZCTRL_PT_RD = ") + strData;
			break;
		case CMDTYPE_PTZCTRL_PAN_STOP:
			strText = _T("CMDTYPE_PTZCTRL_PAN_STOP = ") + strData;
			break;
		case CMDTYPE_PTZCTRL_TILT_STOP:
			strText = _T("CMDTYPE_PTZCTRL_TILT_STOP = ") + strData;
			break;
		case CMDTYPE_PTZCTRL_PT_STOP:
			strText = _T("CMDTYPE_PTZCTRL_PT_STOP = ") + strData;
			break;
		case CMDTYPE_PTZCTRL_ZOOM_TELE:
			strText = _T("CMDTYPE_PTZCTRL_ZOOM_TELE = ") + strData;
			break;
		case CMDTYPE_PTZCTRL_ZOOM_WIDE:
			strText = _T("CMDTYPE_PTZCTRL_ZOOM_WIDE = ") + strData;
			break;
		case CMDTYPE_PTZCTRL_ZOOM_STOP:
			strText = _T("CMDTYPE_PTZCTRL_ZOOM_STOP = ") + strData;
			break;
		case CMDTYPE_PTZCTRL_FOCUS_NEAR:
			strText = _T("CMDTYPE_PTZCTRL_FOCUS_NEAR = ") + strData;
			break;
		case CMDTYPE_PTZCTRL_FOCUS_FAR:
			strText = _T("CMDTYPE_PTZCTRL_FOCUS_FAR = ") + strData;
			break;
		case CMDTYPE_PTZCTRL_FOCUS_STOP:
			strText = _T("CMDTYPE_PTZCTRL_FOCUS_STOP = ") + strData;
			break;

		case CMDTYPE_PTZCTRL_PT_SPEED:
			strText = _T("CMDTYPE_PTZCTRL_PT_SPEED = ") + strData;
			break;
		case CMDTYPE_PTZCTRL_ZOOM_SPEED:
			strText = _T("CMDTYPE_PTZCTRL_ZOOM_SPEED = ") + strData;
			break;
		case CMDTYPE_PTZCTRL_FOCUS_SPEED:
			strText = _T("CMDTYPE_PTZCTRL_FOCUS_SPEED = ") + strData;
			break;
		case CMDTYPE_PTZCTRL_PRESET_SPEED:
			strText = _T("CMDTYPE_PTZCTRL_PRESET_SPEED = ") + strData;
			break;
		default:
			break;
		}
	}
	break;
	case CMDGROUP_PTZREQ:
	{
		switch (pAuthorityPacket->byCmdType)
		{
		case CMDTYPE_PTZREQ_PANTILT_POS_REQ:
			strText = _T("CMDTYPE_PTZREQ_PANTILT_POS_REQ = ") + strData;
			break;
		case CMDTYPE_PTZREQ_PANTILT_POS_RESP:
			strText = _T("CMDTYPE_PTZREQ_PANTILT_POS_RESP = ") + strData;
			break;
		case CMDTYPE_PTZREQ_DAYZF_POS_REQ:
			strText = _T("CMDTYPE_PTZREQ_DAYZF_POS_REQ = ") + strData;
			break;
		case CMDTYPE_PTZREQ_DAYZF_POS_RESP:
			strText = _T("CMDTYPE_PTZREQ_DAYZF_POS_RESP = ") + strData;
			break;		
		case CMDTYPE_PTZREQ_PAN_MOTORSTATUS_REQ:
			strText = _T("CMDTYPE_PTZREQ_PAN_MOTORSTATUS_REQ = ") + strData;
			break;
		case CMDTYPE_PTZREQ_PAN_INITSTATUS_RESP:
			strText = _T("CMDTYPE_PTZREQ_PAN_INITSTATUS_RESP = ") + strData;
			break;
		case CMDTYPE_PTZREQ_TILT_STATUS_REQ:
			strText = _T("CMDTYPE_PTZREQ_TILT_STATUS_REQ = ") + strData;
			break;
		case CMDTYPE_PTZREQ_TILT_STATUS_RESP:
			strText = _T("CMDTYPE_PTZREQ_TILT_STATUS_RESP = ") + strData;
			break;
		case CMDTYPE_PTZREQ_ZF_STATUS_REQ:
			strText = _T("CMDTYPE_PTZREQ_ZF_STATUS_REQ = ") + strData;
			break;
		case CMDTYPE_PTZREQ_ZF_STATUS_RESP:
			strText = _T("CMDTYPE_PTZREQ_ZF_STATUS_RESP = ") + strData;
			break;
		case CMDTYPE_PTZREQ_MAINBOARD_STATUS_RESP:
			strText = _T("CMDTYPE_PTZREQ_MAINBOARD_STATUS_RESP = ") + strData;
		default:
			break;
		}

	}
	break;
	case CMDGROUP_DAYCAM:
	{
		switch (pAuthorityPacket->byCmdType)
		{
		case CMDTYPE_DAYCAM_EXTENDTER:
			strText = _T("CMDTYPE_DAYCAM_EXTENDTER = ") + strData;
			break;
			/*
		case CMDTYPE_DAYCAM_COLOR_MODE:
			strText = _T("CMDTYPE_DAYCAM_COLOR_MODE = ") + strData;
			break;
		case CMDTYPE_DAYCAM_BW_MODE:
			strText = _T("CMDTYPE_DAYCAM_BW_MODE = ") + strData;
			break;
			*/

		default:
			break;
		}

	}
	break;
	case CMDGROUP_THERMCAM:
	{
		switch (pAuthorityPacket->byCmdType)
		{
		case CMDTYPE_THERMCAM_WHITE_HOT:
			strText = _T("CMDTYPE_THERMCAM_WHITE_HOT = ") + strData;
			break;
		case CMDTYPE_THERMCAM_BLACK_HOT:
			strText = _T("CMDTYPE_THERMCAM_BLACK_HOT = ") + strData;
			break;
			
		case CMDTYPE_THERMCAM_COLOR:
			strText = _T("CMDTYPE_THERMCAM_COLOR = ") + strData;
			break;

		case CMDTYPE_THERMCAM_DZOOM:
			strText = _T("CMDTYPE_THERMCAM_DZOOM = ") + strData;
			break;

		case CMDTYPE_THERMCAM_DZOOM_REQ:
			strText = _T("CMDTYPE_THERMCAM_DZOOM_REQ = ") + strData;
			break;
		case CMDTYPE_THERMCAM_DZOOM_RESP:
			strText = _T("CMDTYPE_THERMCAM_DZOOM_RESP = ") + strData;
			break;
		case CMDTYPE_THERMCAM_NUC:
			strText = _T("CMDTYPE_THERMCAM_NUC = ") + strData;
			break;
		case CMDTYPE_THERMCAM_AGCMODE:
			strText = _T("CMDTYPE_THERMCAM_AGCMODE = ") + strData;
			break;
		case CMDTYPE_THERMCAM_AGCMODE_REQ:
			strText = _T("CMDTYPE_THERMCAM_AGCMODE_REQ = ") + strData;
			break;
		case CMDTYPE_THERMCAM_AGCMODE_RESP:
			strText = _T("CMDTYPE_THERMCAM_AGCMODE_RESP = ") + strData;
			break;
		case CMDTYPE_THERMCAM_CONTRAST:
			strText = _T("CMDTYPE_THERMCAM_CONTRAST = ") + strData;
			break;
		case CMDTYPE_THERMCAM_CONTRAST_REQ:
			strText = _T("CMDTYPE_THERMCAM_CONTRAST_REQ = ") + strData;
			break;
		case CMDTYPE_THERMCAM_CONTRAST_RESP:
			strText = _T("CMDTYPE_THERMCAM_CONTRAST_RESP = ") + strData;
			break;

		case CMDTYPE_THERMCAM_BRIGHTNESS:
			strText = _T("CMDTYPE_THERMCAM_BRIGHTNESS = ") + strData;
			break;
		case CMDTYPE_THERMCAM_BRIGHTNESS_REQ:
			strText = _T("CMDTYPE_THERMCAM_BRIGHTNESS_REQ = ") + strData;
			break;
		case CMDTYPE_THERMCAM_BRIGHTNESS_RESP:
			strText = _T("CMDTYPE_THERMCAM_BRIGHTNESS_RESP = ") + strData;
			break;

		case CMDTYPE_THERMCAM_DDE:
			strText = _T("CMDTYPE_THERMCAM_DDE = ") + strData;
			break;
		case CMDTYPE_THERMCAM_DDE_REQ:
			strText = _T("CMDTYPE_THERMCAM_DDE_REQ = ") + strData;
			break;
		case CMDTYPE_THERMCAM_DDE_RESP:
			strText = _T("CMDTYPE_THERMCAM_DDE_RESP = ") + strData;
			break;
		case CMDTYPE_THERMCAM_ACE:
			strText = _T("CMDTYPE_THERMCAM_ACE = ") + strData;
			break;
		case CMDTYPE_THERMCAM_ACE_REQ:
			strText = _T("CMDTYPE_THERMCAM_ACE_REQ = ") + strData;
			break;

		case CMDTYPE_THERMCAM_SSO:
			strText = _T("CMDTYPE_THERMCAM_SSO = ") + strData;
			break;
		case CMDTYPE_THERMCAM_SSO_REQ:
			strText = _T("CMDTYPE_THERMCAM_SSO_REQ = ") + strData;
			break;
		case CMDTYPE_THERMCAM_SSO_RESP:
			strText = _T("CMDTYPE_THERMCAM_SSO_RESP = ") + strData;
			break;
		default:
			break;
		}

	}
	break;


	case CMDGROUP_POWERMGT:
	{
		switch (pAuthorityPacket->byCmdType)
		{
		case CMDTYPE_POWERMGT_SYS_PWR_CTL:
			strText = _T("CMDTYPE_POWERMGT_SYS_PWR_CTL = ") + strData;
			break;
		case CMDTYPE_POWERMGT_SYS_PWR_STATUS:
			strText = _T("CMDTYPE_POWERMGT_SYS_PWR_STATUS = ") + strData;
			break;
		case CMDTYPE_POWERMGT_THERMCAM_PWR_CTL:
			strText = _T("CMDTYPE_POWERMGT_THERMCAM_PWR_CTL = ") + strData;
			break;
		case CMDTYPE_POWERMGT_THERMCAM_STATUS:
			strText = _T("CMDTYPE_POWERMGT_THERMCAM_STATUS = ") + strData;
			break;
		default:
			break;
		}
		break;
	}
	case CMDGROUP_PANTILTINIT:
	{
		switch (pAuthorityPacket->byCmdType)
		{
		case CMDTYPE_PANTILTINIT_MOVE_HOMEPOS:
			strText = _T("CMDTYPE_PANTILTINIT_MOVE_HOMEPOS = ") + strData;
			break;
		case CMDTYPE_PANTILTINIT_REQ_HOMEPOS:
			strText = _T("CMDTYPE_PANTILTINIT_REQ_HOMEPOS = ") + strData;
			break;
		case CMDTYPE_PANTILTINIT_RESP_HOMEPOS:
			strText = _T("CMDTYPE_PANTILTINIT_RESP_HOMEPOS = ") + strData;
			break;
		case CMDTYPE_PANTILTINIT_SYNC_HOMEPOS:
			strText = _T("CMDTYPE_PANTILTINIT_SYNC_HOMEPOS = ") + strData;
			break;
		default:
			break;
		}
		break;
	}

	case CMDGROUP_PTZFABSMOVE:
	{
		switch (pAuthorityPacket->byCmdType)
		{
			
		case CMDTYPE_PTZFABSMOVE_MOVE:
			strText = _T("CMDTYPE_PTZFABSMOVE_MOVE = ") + strData;
			break;
		case CMDTYPE_PTZFABSMOVE_SAVE_POS:
			strText = _T("CMDTYPE_PTZFABSMOVE_SAVE_POS = ") + strData;
			break;
		case CMDTYPE_PTZFABSMOVE_MOVE_SAVEPOS:
			strText = _T("CMDTYPE_PTZFABSMOVE_MOVE_SAVEPOS = ") + strData;
			break;
		case CMDTYPE_PTZFABSMOVE_REQ_SAVEPOS:
			strText = _T("CMDTYPE_PTZFABSMOVE_REQ_SAVEPOS = ") + strData;
			break;
		case CMDTYPE_PTZFABSMOVE_RESP_SAVEPOS:
			strText = _T("CMDTYPE_PTZFABSMOVE_RESP_SAVEPOS = ") + strData;
			break;
		}
	}
	break;

	case CMDGROUP_ETCFUNC:
	{

		switch (pAuthorityPacket->byCmdType)
		{
		case CMDTYPE_ETCFUNC_PANTILT_INIT:
			strText = _T("CMDTYPE_ETCFUNC_PANTILT_INIT = ") + strData;
			break;
		case CMDTYPE_ETCFUNC_PANTILT_INIT_STATUS:
			strText = _T("CMDTYPE_ETCFUNC_PANTILT_INIT_STATUS = ") + strData;
			break;
		case CMDTYPE_ETCFUNC_PANTILT_MOTOR_ADJUSTMENT_STATUS:
			strText = _T("CMDTYPE_ETCFUNC_PANTILT_MOTOR_ADJUSTMENT_STATUS = ") + strData;
			break;
		case CMDTYPE_ETCFUNC_PRESET_CTL:
			strText = _T("CMDTYPE_ETCFUNC_PRESET_CTL = ") + strData;
			break;
		case CMDTYPE_ETCFUNC_PRESET_STATUS:
			strText = _T("CMDTYPE_ETCFUNC_PRESET_STATUS = ") + strData;
			break;
		case CMDTYPE_ETCFUNC_SET_PAN_OFFSET:
			strText = _T("CMDTYPE_ETCFUNC_SET_PAN_OFFSET = ") + strData;
			break;
		case CMDTYPE_ETCFUNC_SET_TILT_OFFSET:
			strText = _T("CMDTYPE_ETCFUNC_SET_TILT_OFFSET = ") + strData;
			break;
		case CMDTYPE_ETCFUNC_REQ_GPS_VAL:
			strText = _T("CMDTYPE_ETCFUNC_REQ_GPS_VAL = ") + strData;
			break;
		case CMDTYPE_ETCFUNC_REQ_GPS_LAT:
			strText = _T("CMDTYPE_ETCFUNC_REQ_GPS_LAT = ") + strData;
			break;
		case CMDTYPE_ETCFUNC_REQ_GPS_LONG:
			strText = _T("CMDTYPE_ETCFUNC_REQ_GPS_LONG = ") + strData;
			break;
		case CMDTYPE_ETCFUNC_SET_LAT_POS:
			strText = _T("CMDTYPE_ETCFUNC_SET_LAT_POS = ") + strData;
			break;
		case CMDTYPE_ETCFUNC_SET_LONG_POS:
			strText = _T("CMDTYPE_ETCFUNC_SET_LONG_POS = ") + strData;
			break;
		default:
			break;
		}

	}
	break;

	case CMDGROUP_ETC_DEVICE:
	{
		switch (pAuthorityPacket->byCmdType)
		{
			
		case CMDTYPE_ETC_HIGHLENS_FILTER:
			strText = _T("CMDTYPE_ETC_HIGHLENS_FILTER = ") + strData;
			break;
			
		default:
			break;
		}

	}
	break;

	default:
		break;
	}
	/*
	case CMDGROUP_ETC_LINK:

		break;
	}
	*/



	return strText;
}