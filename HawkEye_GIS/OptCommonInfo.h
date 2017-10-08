#pragma once


#define FILENAME_GIS_COMMON_INFO _T("GIS_COMMON.ini")


typedef struct _DRAWINGSTYLE
{
	_DRAWINGSTYLE(void)	
	{
		clr=RGB(255, 0, 0);
		uPenSize=0;
		uSymbolSize=0;
		uSymbol=0;
		byOpacity = 0x00;
	}
	COLORREF clr;
	UINT uPenSize;
	UINT uSymbolSize;
	UINT uSymbol;
	BYTE byOpacity;//  [3/30/2014 Yeun]
	BOOL bDispNum;
	BOOL bDispName;
}DRAWINGSTYLE;

class COptCommonInfo
{
public:
	typedef struct tagOption{
		char strMapFilePathName[MAX_PATH];

		DRAWINGSTYLE CamDirecStyle;
		DRAWINGSTYLE RefPointStyle;
		DRAWINGSTYLE TargetPointStyle;
		DRAWINGSTYLE LineStyle;
		
		int iX;
		int iY;
		int iWidth;
		int iHeight;
	} S_OPTION, *LPS_OPTION;

	S_OPTION m_s;

	CString m_strFile;

	COptCommonInfo(void);
	~COptCommonInfo(void);
	COptCommonInfo&		operator=(COptCommonInfo& Data);
	BOOL Read(void);
	BOOL Write(void);
};
