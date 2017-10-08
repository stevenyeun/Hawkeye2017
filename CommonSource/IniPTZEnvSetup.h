#pragma once




#include "CommonDefine.h"

class CIniPTZEnvSetup
{
public:
	typedef struct tagOption{
		
		int latitudeDegrees[MAX_CHANNEL_NUM];
		int latitudeMinute[MAX_CHANNEL_NUM];
		int latitudeSecond[MAX_CHANNEL_NUM];
		int latitudeSecondDot[MAX_CHANNEL_NUM];

		int longitudeDegrees[MAX_CHANNEL_NUM];
		int longitudeMinute[MAX_CHANNEL_NUM];
		int longitudeSecond[MAX_CHANNEL_NUM];
		int longitudeSecondDot[MAX_CHANNEL_NUM];

		double panOffset[MAX_CHANNEL_NUM];
		double tiltOffset[MAX_CHANNEL_NUM];		
	
		int	rangeSurveillance[MAX_CHANNEL_NUM];
		TCHAR areaName[MAX_CHANNEL_NUM][MAX_PATH];

	} S_OPTION, *LPS_OPTION;
	S_OPTION m_s;

	CString m_strFile;

	CIniPTZEnvSetup(void);	
	~CIniPTZEnvSetup(void);
	CIniPTZEnvSetup&		operator=(CIniPTZEnvSetup& Data);
	void Read(void);	
	void Read(int nCh);
	void Write(void);
	void Write(int nCh);
};