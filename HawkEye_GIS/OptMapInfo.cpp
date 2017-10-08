



#include "StdAfx.h"
#include "OptMapInfo.h"
#include "MyFunc.h"

COptMapInfo::COptMapInfo(CString strFileName)
{
	memset(&m_s, 0, sizeof(S_OPTION));

	//m_strFile = GetProgramDir() + strFileName;
	m_strFile = strFileName;
	Read();
}

COptMapInfo::~COptMapInfo(void)
{
	Write();
}

COptMapInfo& COptMapInfo::operator=(COptMapInfo& Data)
{
	memcpy(&m_s, &Data.m_s, sizeof(S_OPTION));
	
	m_strFile = Data.m_strFile;

	return *this;
}

BOOL COptMapInfo::Read(void)
{
	GPPS(_T("Ref1"), _T("LAT_DEG"),					m_s.RefPoint1.iLatDeg, m_strFile);
	GPPS(_T("Ref1"), _T("LAT_MIN"),					m_s.RefPoint1.iLatMin, m_strFile);
	GPPS(_T("Ref1"), _T("LAT_SEC"),					m_s.RefPoint1.dLatSec, m_strFile);

	GPPS(_T("Ref1"), _T("PIXEL_Y_SEC"),				m_s.RefPoint1.iRefPointPixelY, m_strFile);

	GPPS(_T("Ref1"), _T("LONG_DEG"),				m_s.RefPoint1.iLongDeg, m_strFile);
	GPPS(_T("Ref1"), _T("LONG_MIN"),				m_s.RefPoint1.iLongMin, m_strFile);
	GPPS(_T("Ref1"), _T("LONG_SEC"),				m_s.RefPoint1.dLongSec, m_strFile);	

	GPPS(_T("Ref1"), _T("PIXEL_X_SEC"),				m_s.RefPoint1.iRefPointPixelX, m_strFile);


	GPPS(_T("Ref2"), _T("LAT_DEG"),					m_s.RefPoint2.iLatDeg, m_strFile);
	GPPS(_T("Ref2"), _T("LAT_MIN"),					m_s.RefPoint2.iLatMin, m_strFile);
	GPPS(_T("Ref2"), _T("LAT_SEC"),					m_s.RefPoint2.dLatSec, m_strFile);

	GPPS(_T("Ref2"), _T("PIXEL_Y_SEC"),				m_s.RefPoint2.iRefPointPixelY, m_strFile);

	GPPS(_T("Ref2"), _T("LONG_DEG"),				m_s.RefPoint2.iLongDeg, m_strFile);
	GPPS(_T("Ref2"), _T("LONG_MIN"),				m_s.RefPoint2.iLongMin, m_strFile);
	GPPS(_T("Ref2"), _T("LONG_SEC"),				m_s.RefPoint2.dLongSec, m_strFile);	

	GPPS(_T("Ref2"), _T("PIXEL_X_SEC"),				m_s.RefPoint2.iRefPointPixelX, m_strFile);

	return TRUE;
}

BOOL COptMapInfo::Write(void)
{
	WPPS(_T("Ref1"), _T("LAT_DEG"),					m_s.RefPoint1.iLatDeg, m_strFile);
	WPPS(_T("Ref1"), _T("LAT_MIN"),					m_s.RefPoint1.iLatMin, m_strFile);
	WPPS(_T("Ref1"), _T("LAT_SEC"),					m_s.RefPoint1.dLatSec, m_strFile);

	WPPS(_T("Ref1"), _T("PIXEL_Y_SEC"),				m_s.RefPoint1.iRefPointPixelY, m_strFile);

	WPPS(_T("Ref1"), _T("LONG_DEG"),				m_s.RefPoint1.iLongDeg, m_strFile);
	WPPS(_T("Ref1"), _T("LONG_MIN"),				m_s.RefPoint1.iLongMin, m_strFile);
	WPPS(_T("Ref1"), _T("LONG_SEC"),				m_s.RefPoint1.dLongSec, m_strFile);	

	WPPS(_T("Ref1"), _T("PIXEL_X_SEC"),				m_s.RefPoint1.iRefPointPixelX, m_strFile);


	WPPS(_T("Ref2"), _T("LAT_DEG"),					m_s.RefPoint2.iLatDeg, m_strFile);
	WPPS(_T("Ref2"), _T("LAT_MIN"),					m_s.RefPoint2.iLatMin, m_strFile);
	WPPS(_T("Ref2"), _T("LAT_SEC"),					m_s.RefPoint2.dLatSec, m_strFile);

	WPPS(_T("Ref2"), _T("PIXEL_Y_SEC"),				m_s.RefPoint2.iRefPointPixelY, m_strFile);

	WPPS(_T("Ref2"), _T("LONG_DEG"),				m_s.RefPoint2.iLongDeg, m_strFile);
	WPPS(_T("Ref2"), _T("LONG_MIN"),				m_s.RefPoint2.iLongMin, m_strFile);
	WPPS(_T("Ref2"), _T("LONG_SEC"),				m_s.RefPoint2.dLongSec, m_strFile);	

	WPPS(_T("Ref2"), _T("PIXEL_X_SEC"),				m_s.RefPoint2.iRefPointPixelX, m_strFile);

	return TRUE;
}
