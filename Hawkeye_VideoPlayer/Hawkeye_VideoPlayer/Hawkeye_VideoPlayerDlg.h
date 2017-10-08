
// Hawkeye_VideoPlayerDlg.h : header file
//

#pragma once


// CHawkeye_VideoPlayerDlg dialog
class CHawkeye_VideoPlayerDlg : public CDialogEx
{
// Construction
public:
	CHawkeye_VideoPlayerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HAWKEYE_VIDEOPLAYER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
