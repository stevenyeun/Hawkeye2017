#if !defined(AFX_CONNECTDLG_H__42C42F72_ECF5_49B9_BED5_5C54761A1C43__INCLUDED_)
#define AFX_CONNECTDLG_H__42C42F72_ECF5_49B9_BED5_5C54761A1C43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConnectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg dialog

class CConnectDlg : public CDialog
{
// Construction
public:
	CConnectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConnectDlg)
	enum { IDD = IDD_DIALOG_CONNECT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConnectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
public:
	CComboBox	m_cbProtocol;
	CButton		m_chUseSS;

	CString	m_sIPSS;
	CString	m_sPortSS;
	CString	m_sLoginSS;
	CString	m_sPasswordSS;

	CString m_sIP;
	CString m_sPort;
	CString m_sLoginName;
	CString m_sPassword;
	BOOL    m_bAudio;
	BOOL    m_bSChnl; //secondary
	BOOL	m_bHD;
	int		m_nProtocol;
	int		m_nUseSS;
    int     m_nChannel;

	// Generated message map functions
	//{{AFX_MSG(CConnectDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDestroy();
	afx_msg void OnUseSS();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNECTDLG_H__42C42F72_ECF5_49B9_BED5_5C54761A1C43__INCLUDED_)
