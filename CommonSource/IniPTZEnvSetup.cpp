#include "StdAfx.h"
#include "IniPTZEnvSetup.h"
#include "MyFunc.h"

#define DEFAULT_SECTION _T("COMMON")

#define FILENAME _T("PTZEnvSetup.ini")

CIniPTZEnvSetup::CIniPTZEnvSetup(void)
{
	memset(&m_s, 0, sizeof(S_OPTION));
	CString str = GetProgramDir();
	//상위경로로 이동 ../
	str = str.Left(str.ReverseFind(_T('\\')));
	str = str.Left(str.ReverseFind(_T('\\')) + 1);
	m_strFile = str + FILENAME;
	Read();
}
CIniPTZEnvSetup::~CIniPTZEnvSetup(void)
{
	Write();
}

CIniPTZEnvSetup& CIniPTZEnvSetup::operator=(CIniPTZEnvSetup& Data)
{
	memcpy(&m_s, &Data.m_s, sizeof(S_OPTION));

	m_strFile = Data.m_strFile;

	return *this;
}

void CIniPTZEnvSetup::Read(void)
{	
	//1	
	CString strText;
	for (int i = 0; i < MAX_CHANNEL_NUM; i++) {
		strText.Format(_T("ch%02d"), i + 1);

		GPPS(strText, _T("latitudeDegrees"), m_s.latitudeDegrees[i], m_strFile);
		GPPS(strText, _T("latitudeMinute"), m_s.latitudeMinute[i], m_strFile);
		GPPS(strText, _T("latitudeSecond"), m_s.latitudeSecond[i], m_strFile);
		GPPS(strText, _T("latitudeSecondDot"), m_s.latitudeSecondDot[i], m_strFile);
		
		GPPS(strText, _T("longitudeDegrees"), m_s.longitudeDegrees[i], m_strFile);
		GPPS(strText, _T("longitudeMinute"), m_s.longitudeMinute[i], m_strFile);
		GPPS(strText, _T("longitudeSecond"), m_s.longitudeSecond[i], m_strFile);
		GPPS(strText, _T("longitudeSecondDot"), m_s.longitudeSecondDot[i], m_strFile);

		GPPS(strText, _T("azimuth"), m_s.panOffset[i], m_strFile);
		GPPS(strText, _T("angleOfElevation"), m_s.tiltOffset[i], m_strFile);

		GPPS(strText, _T("rangeSurveillance"), m_s.rangeSurveillance[i], m_strFile);
		
		GPPS(strText, _T("area"), m_s.areaName[i], MAX_PATH, m_strFile);

	
	}
	
}
void CIniPTZEnvSetup::Read(int nCh)
{
	//1	
	CString strText;

	strText.Format(_T("ch%02d"), nCh);

	GPPS(strText, _T("latitudeDegrees"), m_s.latitudeDegrees[nCh-1], m_strFile);
	GPPS(strText, _T("latitudeMinute"), m_s.latitudeMinute[nCh - 1], m_strFile);
	GPPS(strText, _T("latitudeSecond"), m_s.latitudeSecond[nCh - 1], m_strFile);
	GPPS(strText, _T("latitudeSecondDot"), m_s.latitudeSecondDot[nCh - 1], m_strFile);

	GPPS(strText, _T("longitudeDegrees"), m_s.longitudeDegrees[nCh - 1], m_strFile);
	GPPS(strText, _T("longitudeMinute"), m_s.longitudeMinute[nCh - 1], m_strFile);
	GPPS(strText, _T("longitudeSecond"), m_s.longitudeSecond[nCh - 1], m_strFile);
	GPPS(strText, _T("longitudeSecondDot"), m_s.longitudeSecondDot[nCh - 1], m_strFile);

	GPPS(strText, _T("azimuth"), m_s.panOffset[nCh - 1], m_strFile);
	GPPS(strText, _T("angleOfElevation"), m_s.tiltOffset[nCh - 1], m_strFile);

	GPPS(strText, _T("rangeSurveillance"), m_s.rangeSurveillance[nCh - 1], m_strFile);

	GPPS(strText, _T("area"), m_s.areaName[nCh - 1], MAX_PATH, m_strFile);




}
void CIniPTZEnvSetup::Write(void)
{	
	//1
	CString strText;
	for (int i = 0; i < MAX_CHANNEL_NUM; i++) {
		strText.Format(_T("ch%02d"), i + 1);
		
	}

}
void CIniPTZEnvSetup::Write(int nCh)
{

	
}
