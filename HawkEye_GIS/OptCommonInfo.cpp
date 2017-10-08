



#include "StdAfx.h"
#include "OptCommonInfo.h"
#include "MyFunc.h"

COptCommonInfo::COptCommonInfo(void)
{
	memset(&m_s, 0, sizeof(S_OPTION));

	m_strFile = GetProgramDir() + FILENAME_GIS_COMMON_INFO;
	Read();
}

COptCommonInfo::~COptCommonInfo(void)
{
	Write();
}

COptCommonInfo& COptCommonInfo::operator=(COptCommonInfo& Data)
{
	memcpy(&m_s, &Data.m_s, sizeof(S_OPTION));
	
	m_strFile = Data.m_strFile;

	return *this;
}

BOOL COptCommonInfo::Read(void)
{
	//1
	GPPC(_T("Common"), _T("CAMSTYLE_CLR"),			m_s.CamDirecStyle.clr, m_strFile);	
	GPPS(_T("Common"), _T("CAMSTYLE_SYMBOL"),		m_s.CamDirecStyle.uSymbol, m_strFile);
	GPPS(_T("Common"), _T("CAMSTYLE_PENSIZE"),		m_s.CamDirecStyle.uPenSize, m_strFile);
	GPPS(_T("Common"), _T("CAMSTYLE_SYMBOLSIZE"),	m_s.CamDirecStyle.uSymbolSize, m_strFile);
	GPPS(_T("Common"), _T("CAMSTYLE_OPACITY"),	m_s.CamDirecStyle.byOpacity, m_strFile);//  [3/30/2014 Yeun]

	GPPS(_T("Common"), _T("CAMSTYLE_DISPNUM"),		m_s.CamDirecStyle.bDispNum,  m_strFile);
	GPPS(_T("Common"), _T("CAMSTYLE_DISPNAME"),		m_s.CamDirecStyle.bDispName, m_strFile);

	//2
	GPPC(_T("Common"), _T("REFSTYLE_CLR"),			m_s.RefPointStyle.clr, m_strFile);	
	GPPS(_T("Common"), _T("REFSTYLE_SYMBOL"),		m_s.RefPointStyle.uSymbol, m_strFile);
	GPPS(_T("Common"), _T("REFSTYLE_PENSIZE"),		m_s.RefPointStyle.uPenSize, m_strFile);
	GPPS(_T("Common"), _T("REFSTYLE_SYMBOLSIZE"),	m_s.RefPointStyle.uSymbolSize, m_strFile);
	GPPS(_T("Common"), _T("REFSTYLE_OPACITY"),		m_s.RefPointStyle.byOpacity, m_strFile);//  [3/30/2014 Yeun]

	GPPS(_T("Common"), _T("REFSTYLE_DISPNUM"),		m_s.RefPointStyle.bDispNum,  m_strFile);
	GPPS(_T("Common"), _T("REFSTYLE_DISPNAME"),		m_s.RefPointStyle.bDispName, m_strFile);

	//3
	GPPC(_T("Common"), _T("TARSTYLE_CLR"),			m_s.TargetPointStyle.clr, m_strFile);	
	GPPS(_T("Common"), _T("TARSTYLE_SYMBOL"),		m_s.TargetPointStyle.uSymbol, m_strFile);
	GPPS(_T("Common"), _T("TARSTYLE_PENSSIZE"),		m_s.TargetPointStyle.uPenSize, m_strFile);
	GPPS(_T("Common"), _T("TARSTYLE_SYMBOLSIZE"),	m_s.TargetPointStyle.uSymbolSize, m_strFile);
	GPPS(_T("Common"), _T("TARSTYLE_OPACITY"),		m_s.TargetPointStyle.byOpacity, m_strFile);//  [3/30/2014 Yeun]

	GPPS(_T("Common"), _T("TARSTYLE_DISPNUM"),		m_s.TargetPointStyle.bDispNum,  m_strFile);
	GPPS(_T("Common"), _T("TARSTYLE_DISPNAME"),		m_s.TargetPointStyle.bDispName, m_strFile);

	//4
	GPPC(_T("Common"), _T("LINESTYLE_CLR"),			m_s.LineStyle.clr, m_strFile);	
	GPPS(_T("Common"), _T("LINESTYLE_SYMBOL"),		m_s.LineStyle.uSymbol, m_strFile);
	GPPS(_T("Common"), _T("LINESTYLE_PENSSIZE"),	m_s.LineStyle.uPenSize, m_strFile);
	GPPS(_T("Common"), _T("LINESTYLE_OPACITY"),		m_s.LineStyle.byOpacity, m_strFile);//  [3/30/2014 Yeun]



	GPPS(_T("Common"), _T("WINDOW_X"),				m_s.iX, m_strFile);
	GPPS(_T("Common"), _T("WINDOW_Y"),				m_s.iY, m_strFile);
	GPPS(_T("Common"), _T("WINDOW_WIDTH"),			m_s.iWidth, m_strFile);
	GPPS(_T("Common"), _T("WINDOW_HEIGHT"),			m_s.iHeight, m_strFile);




	GPPS(_T("COMMON"), _T("MAP_FILEPATH"), m_s.strMapFilePathName, MAX_PATH, m_strFile);

	return TRUE;
}

BOOL COptCommonInfo::Write(void)
{
	//1
	WPPC(_T("Common"), _T("CAMSTYLE_CLR"),			m_s.CamDirecStyle.clr, m_strFile);	
	WPPS(_T("Common"), _T("CAMSTYLE_SYMBOL"),		m_s.CamDirecStyle.uSymbol, m_strFile);
	WPPS(_T("Common"), _T("CAMSTYLE_PENSIZE"),		m_s.CamDirecStyle.uPenSize, m_strFile);
	WPPS(_T("Common"), _T("CAMSTYLE_SYMBOLSIZE"),	m_s.CamDirecStyle.uSymbolSize, m_strFile);
	WPPS(_T("Common"), _T("CAMSTYLE_OPACITY"),		m_s.CamDirecStyle.byOpacity, m_strFile);//  [3/30/2014 Yeun]

	WPPS(_T("Common"), _T("CAMSTYLE_DISPNUM"),		m_s.CamDirecStyle.bDispNum,  m_strFile);
	WPPS(_T("Common"), _T("CAMSTYLE_DISPNAME"),		m_s.CamDirecStyle.bDispName, m_strFile);

	//2
	WPPC(_T("Common"), _T("REFSTYLE_CLR"),			m_s.RefPointStyle.clr, m_strFile);	
	WPPS(_T("Common"), _T("REFSTYLE_SYMBOL"),		m_s.RefPointStyle.uSymbol, m_strFile);
	WPPS(_T("Common"), _T("REFSTYLE_PENSIZE"),		m_s.RefPointStyle.uPenSize, m_strFile);
	WPPS(_T("Common"), _T("REFSTYLE_SYMBOLSIZE"),	m_s.RefPointStyle.uSymbolSize, m_strFile);
	WPPS(_T("Common"), _T("REFSTYLE_OPACITY"),		m_s.CamDirecStyle.byOpacity, m_strFile);//  [3/30/2014 Yeun]

	WPPS(_T("Common"), _T("REFSTYLE_DISPNUM"),		m_s.RefPointStyle.bDispNum,  m_strFile);
	WPPS(_T("Common"), _T("REFSTYLE_DISPNAME"),		m_s.RefPointStyle.bDispName, m_strFile);

	//3
	WPPC(_T("Common"), _T("TARSTYLE_CLR"),			m_s.TargetPointStyle.clr, m_strFile);	
	WPPS(_T("Common"), _T("TARSTYLE_SYMBOL"),		m_s.TargetPointStyle.uSymbol, m_strFile);
	WPPS(_T("Common"), _T("TARSTYLE_PENSSIZE"),		m_s.TargetPointStyle.uPenSize, m_strFile);
	WPPS(_T("Common"), _T("TARSTYLE_SYMBOLSIZE"),	m_s.TargetPointStyle.uSymbolSize, m_strFile);
	WPPS(_T("Common"), _T("TARSTYLE_OPACITY"),		m_s.TargetPointStyle.byOpacity, m_strFile);//  [3/30/2014 Yeun]

	WPPS(_T("Common"), _T("TARSTYLE_DISPNUM"),		m_s.RefPointStyle.bDispNum,  m_strFile);
	WPPS(_T("Common"), _T("TARSTYLE_DISPNAME"),		m_s.RefPointStyle.bDispName, m_strFile);
	
	//4
	WPPC(_T("Common"), _T("LINESTYLE_CLR"),			m_s.LineStyle.clr, m_strFile);	
	WPPS(_T("Common"), _T("LINESTYLE_SYMBOL"),		m_s.LineStyle.uSymbol, m_strFile);
	WPPS(_T("Common"), _T("LINESTYLE_PENSSIZE"),	m_s.LineStyle.uPenSize, m_strFile);
	WPPS(_T("Common"), _T("LINESTYLE_OPACITY"),		m_s.LineStyle.byOpacity, m_strFile);//  [3/30/2014 Yeun]

	WPPS(_T("Common"), _T("WINDOW_X"),				m_s.iX, m_strFile);
	WPPS(_T("Common"), _T("WINDOW_Y"),				m_s.iY, m_strFile);
	WPPS(_T("Common"), _T("WINDOW_WIDTH"),			m_s.iWidth, m_strFile);
	WPPS(_T("Common"), _T("WINDOW_HEIGHT"),			m_s.iHeight, m_strFile);


	WPPS(_T("COMMON"), _T("MAP_FILEPATH"),	m_s.strMapFilePathName, m_strFile);	

	return TRUE;
}
