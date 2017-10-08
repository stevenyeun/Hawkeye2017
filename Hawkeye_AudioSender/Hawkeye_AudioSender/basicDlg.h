// basicDlg.h : header file
//

#if !defined(AFX_BASICDLG_H__636EEE50_1BDB_4954_BF53_29DA4D8F3533__INCLUDED_)
#define AFX_BASICDLG_H__636EEE50_1BDB_4954_BF53_29DA4D8F3533__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "videoDlg.h"
#include "DecodeDialog.h"
#include "IniIPSetup.h"
#include <afxcmn.h>

typedef struct _ST_RESOLUTION_
{
	TCHAR szResolution[128];
	int nValue;
}ST_RESOLUTION;

static ST_RESOLUTION gResolution[] = {
	{_T("720x480"), 0}, {_T("720x240"), 1}, {_T("352x480"), 2}, {_T("720x480"), 3}, {_T("720x576"), 4},
	{_T("720x288"), 5}, {_T("720x288"), 6}, {_T("352x576"), 7}, {_T("352x288"), 8}, {_T("640x480"), 9},
	{_T("800x600"), 9}, {_T("1024x768"), 10}, {_T("1280x960"), 11}, {_T("1280x1024"), 12}, {_T("1440x900"), 13},
	{_T("1600x900"), 14}, {_T("1680x1050"), 15}, {_T("1280x720"), 16}, {_T("1920x1080"), 17}, {_T("176x120"), 18},
	{_T("176x144"), 19}, 
	//{_T("320x288"), 20}, {_T("360x288"), 21}, {_T("320x240"), 22}, not used
	{_T("2048x1536"), 23}, {_T("2560x1600"), 24}, {_T("2592x1936"), 25}, {_T("1920x1056"), 26}, {_T("640x360"), 26},
	{_T("1440x540"), 27}
};


/////////////////////////////////////////////////////////////////////////////
// CBasicDlg dialog

class CBasicDlg : public CDialog
{
	friend class CVideoDlg;

    CString m_sIP;
    CString m_sPort;
    CString m_sLoginName;
	CString m_sPassword;

    long    m_Protocol;
	int		m_iSnapCnt;
    BOOL    m_bUseSS;
    BOOL    m_bUseAudio;
    BOOL	m_bHD;
	BOOL	m_bAutoSnap;

    long    m_Channel;
    long    m_Stream;

    CString m_sSSIP;
    CString m_sSSPort;
    CString m_sSSLoginName;
	CString m_sSSPassword;

	CSliderCtrl m_slider_latency;
	
	int m_latency_frames;

	int m_nCh;
	CIniIPSetup m_iniIPSetup;
	unsigned int message;
// Construction
public:
	CBasicDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CBasicDlg();

// Dialog Data
	//{{AFX_DATA(CBasicDlg)
	enum { IDD = IDD_BASIC_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBasicDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CVideoDlg m_dlgVideo;
	CDecodeDialog m_dlgDecode;

	CListCtrl m_log;

	CComboBox m_dataStreamType;
	CComboBox m_DeinterType;
	CComboBox m_Resolution;

	int m_nMTC;
	FILE *m_pDataStreamFile;
	CString	m_sDataStreamFileName;
	CListCtrl m_lvPreset;

	CEdit m_eavResync;
	CEdit m_eavABuffer;
	CEdit m_Bitrate;
public:
	CComboBox m_cbOutputFormat;

	LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);

	void AddToLog(LPCTSTR pText, ...);
	void OnButtonPtz(LPCTSTR pCmd);
	void Disconnect();
	void Pause();

	// Generated message map functions
	//{{AFX_MSG(CBasicDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonConnect();
	afx_msg void OnButtonPlay();
	afx_msg void OnButtonSnapshot();
	afx_msg void OnButtonTalking();
	afx_msg void OnButtonAlarm1Send();
	afx_msg void OnButtonAlarm2Send();
	afx_msg void OnButtonPtzUp();
	afx_msg void OnButtonPtzDown();
	afx_msg void OnButtonPtzLeft();
	afx_msg void OnButtonPtzRight();
	afx_msg void OnButtonPtzZoomin();
	afx_msg void OnButtonPtzZoomout();
	afx_msg void OnButtonPtzFocusnear();
	afx_msg void OnButtonPtzFocusfar();
	afx_msg void OnButtonPresetGoto();
	afx_msg void OnButtonDatastreamFilename();
	afx_msg void OnButtonSwrite();
	afx_msg void OnBtnDecStart();
	afx_msg void OnSelchangeComboOutformat();
	afx_msg void OnCheckFilew();
	afx_msg void OnBtnGetframe();
	afx_msg void OnRefreshPreset();
	afx_msg void OnButtonPlaywave();
	afx_msg void OnButtonScreenPtz();
	afx_msg void OnRadioAsbuffer();
	afx_msg void OnRadioAsfile();
	afx_msg void OnButtonGetPosition();
	afx_msg void OnSelchangeComboDeinter();
	afx_msg void OnButtonAutosnap();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonAvApply();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnServerResolutionGet();
	afx_msg void OnServerResolutionSet();
	afx_msg void OnServerBitrateGet();
	afx_msg void OnServerBitrateSet();
	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASICDLG_H__636EEE50_1BDB_4954_BF53_29DA4D8F3533__INCLUDED_)
