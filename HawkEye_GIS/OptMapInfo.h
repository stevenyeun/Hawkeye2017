#pragma once


typedef struct _MAPPING
{
	int iLatDeg;
	int iLatMin;
	double dLatSec;
	int iRefPointPixelY;

	int iLongDeg;
	int iLongMin;
	double dLongSec;
	int iRefPointPixelX;

}MAPPING;

class COptMapInfo
{
public:
	typedef struct tagOption{

		MAPPING RefPoint1;
		MAPPING RefPoint2;

	} S_OPTION, *LPS_OPTION;
	S_OPTION m_s;

	CString m_strFile;

	COptMapInfo(CString strFileName);
	~COptMapInfo(void);
	COptMapInfo&		operator=(COptMapInfo& Data);
	BOOL Read(void);
	BOOL Write(void);
};
