#include "StdAfx.h"
#include "IniIPSetup.h"
#include "MyFunc.h"

#define DEFAULT_SECTION _T("COMMON")

#define FILENAME _T("SystemIpAddrInfo.ini")

CIniIPSetup::CIniIPSetup(void)
{
	memset(&m_s, 0, sizeof(S_OPTION));
	CString str = GetProgramDir();
	//상위경로로 이동 ../
	str = str.Left(str.ReverseFind(_T('\\')));
	str = str.Left(str.ReverseFind(_T('\\')) + 1);
	m_strFile = str + FILENAME;
	Read();
}
CIniIPSetup::~CIniIPSetup(void)
{
	Write();
}

CIniIPSetup& CIniIPSetup::operator=(CIniIPSetup& Data)
{
	memcpy(&m_s, &Data.m_s, sizeof(S_OPTION));

	m_strFile = Data.m_strFile;

	return *this;
}

void CIniIPSetup::Read(void)
{	
	//1	
	CString strText;
	for (int i = 0; i < MAX_CHANNEL_NUM; i++) {
		strText.Format(_T("ch%02d"), i + 1);

		GPPS(strText, _T("ptzserver_ipaddrFirst"), m_s.tstrPTZServerIPAddrFirst[i], MAX_PATH, m_strFile);
		GPPS(strText, _T("ptzserver_ipaddrSencond"), m_s.tstrPTZServerIPAddrSecond[i], MAX_PATH, m_strFile);
		GPPS(strText, _T("ptzserver_ipaddrThird"), m_s.tstrPTZServerIPAddrThird[i], MAX_PATH, m_strFile);
		GPPS(strText, _T("ptzserver_ipaddrForth"), m_s.tstrPTZServerIPAddrForth[i], MAX_PATH, m_strFile);
		GPPS(strText, _T("ptzserver_port"), m_s.nArrPTZServerPort[i], m_strFile);


		GPPS(strText, _T("mic_ipaddrFirst"), m_s.tstrMICServerIPAddrFirst[i], MAX_PATH, m_strFile);
		GPPS(strText, _T("mic_ipaddrSencond"), m_s.tstrMICServerIPAddrSecond[i], MAX_PATH, m_strFile);
		GPPS(strText, _T("mic_ipaddrThird"), m_s.tstrMICServerIPAddrThird[i], MAX_PATH, m_strFile);
		GPPS(strText, _T("mic_ipaddrForth"), m_s.tstrMICServerIPAddrForth[i], MAX_PATH, m_strFile);

		GPPS(strText, _T("mic_id"), m_s.tstrMICServerID[i], MAX_PATH, m_strFile);
		GPPS(strText, _T("mic_pw"), m_s.tstrMICServerPW[i], MAX_PATH, m_strFile);

	
		

		/*
		GPPS(strText, _T("authorityserver_ipaddrFirst"), m_s.tstrPTZServerIPAddrFirst[i], 0, m_strFile);
		GPPS(strText, _T("authorityserver_ipaddrSencond"), m_s.tstrPTZServerIPAddrSecond[i], 0, m_strFile);
		GPPS(strText, _T("authorityserver_ipaddrThird"), m_s.tstrPTZServerIPAddrThird[i], 0, m_strFile);
		GPPS(strText, _T("authorityserver_ipaddrForth"), m_s.tstrPTZServerIPAddrForth[i], 0, m_strFile);
		*/
		GPPS(strText, _T("authorityserver_port"), m_s.nArrAuthorityServerPort[i], 0, m_strFile);
	}
	
}
void CIniIPSetup::Write(void)
{	
	//1
	CString strText;
	for (int i = 0; i < MAX_CHANNEL_NUM; i++) {
		strText.Format(_T("ch%02d"), i + 1);
		
	}

}
void CIniIPSetup::Write(int nCh)
{

	
}
