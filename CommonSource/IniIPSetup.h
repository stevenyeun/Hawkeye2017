#pragma once




#include "CommonDefine.h"

class CIniIPSetup
{
public:
	typedef struct tagOption{	

		//CString strURL[MAX_CH];
		//CString m_strCamName[MAX_CH];
		
		TCHAR tstrPTZServerIPAddrFirst[MAX_CHANNEL_NUM][MAX_PATH];
		TCHAR tstrPTZServerIPAddrSecond[MAX_CHANNEL_NUM][MAX_PATH];
		TCHAR tstrPTZServerIPAddrThird[MAX_CHANNEL_NUM][MAX_PATH];
		TCHAR tstrPTZServerIPAddrForth[MAX_CHANNEL_NUM][MAX_PATH];
		int nArrPTZServerPort[MAX_CHANNEL_NUM];

		//TCHAR tstrAuthorityServerIPAddrFirst[MAX_CHANNEL_NUM][MAX_PATH];
		//TCHAR tstrAuthorityServerIPAddrSecond[MAX_CHANNEL_NUM][MAX_PATH];
		//TCHAR tstrAuthorityServerIPAddrThird[MAX_CHANNEL_NUM][MAX_PATH];
		//TCHAR tstrAuthorityServerIPAddrForth[MAX_CHANNEL_NUM][MAX_PATH];
		int nArrAuthorityServerPort[MAX_CHANNEL_NUM];

		TCHAR tstrMICServerIPAddrFirst[MAX_CHANNEL_NUM][MAX_PATH];
		TCHAR tstrMICServerIPAddrSecond[MAX_CHANNEL_NUM][MAX_PATH];
		TCHAR tstrMICServerIPAddrThird[MAX_CHANNEL_NUM][MAX_PATH];
		TCHAR tstrMICServerIPAddrForth[MAX_CHANNEL_NUM][MAX_PATH];

		TCHAR tstrMICServerID[MAX_CHANNEL_NUM][MAX_PATH];
		TCHAR tstrMICServerPW[MAX_CHANNEL_NUM][MAX_PATH];

		
	
	} S_OPTION, *LPS_OPTION;
	S_OPTION m_s;

	CString m_strFile;

	CIniIPSetup(void);
	~CIniIPSetup(void);
	CIniIPSetup&		operator=(CIniIPSetup& Data);
	void Read(void);	
	void Write(void);
	void Write(int nCh);
};