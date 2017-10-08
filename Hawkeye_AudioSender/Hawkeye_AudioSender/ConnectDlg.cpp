// ConnectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "basic.h"
#include "ConnectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg dialog


CConnectDlg::CConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConnectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConnectDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnectDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnectDlg, CDialog)
	//{{AFX_MSG_MAP(CConnectDlg)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECK_USE_SS, OnUseSS)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg message handlers

BOOL CConnectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_IPADDRESS_IP)->SetWindowText(m_sIP);
	GetDlgItem(IDC_EDIT_PORT)->SetWindowText(m_sPort);
	GetDlgItem(IDC_EDIT_LOGIN_NAME)->SetWindowText(m_sLoginName);
	GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowText(m_sPassword);
	GetDlgItem(IDC_CH_AUDIO)->SendMessage(BM_SETCHECK, m_bAudio?BST_CHECKED:BST_UNCHECKED, 0);
//	GetDlgItem(IDC_CH_SECONDARY_CHNL)->SendMessage(BM_SETCHECK, m_bSChnl?BST_CHECKED:BST_UNCHECKED, 0);
	GetDlgItem(IDC_CH_HD)->SendMessage(BM_SETCHECK, m_bHD?BST_CHECKED:BST_UNCHECKED, 0);

	m_chUseSS.Attach(GetDlgItem(IDC_CHECK_USE_SS)->GetSafeHwnd());
	m_chUseSS.SetCheck(m_nUseSS);
	GetDlgItem(IDC_IPADDRESS_SS)->EnableWindow(m_nUseSS);
	GetDlgItem(IDC_EDIT_SS_PORT)->EnableWindow(m_nUseSS);
	GetDlgItem(IDC_EDIT_SS_LOGIN)->EnableWindow(m_nUseSS);
	GetDlgItem(IDC_EDIT_SS_PASS)->EnableWindow(m_nUseSS);

	m_cbProtocol.Attach(GetDlgItem(IDC_COMBO_PROTOCOL)->GetSafeHwnd());
	m_cbProtocol.AddString(_T("TCP"));
	m_cbProtocol.AddString(_T("Multicast"));
	m_cbProtocol.AddString(_T("UDP"));
	m_cbProtocol.SetCurSel(m_nProtocol);
	
	GetDlgItem(IDC_IPADDRESS_SS)->SetWindowText(m_sIPSS);
	GetDlgItem(IDC_EDIT_SS_PORT)->SetWindowText(m_sPortSS);
	GetDlgItem(IDC_EDIT_SS_LOGIN)->SetWindowText(m_sLoginSS);
	GetDlgItem(IDC_EDIT_SS_PASS)->SetWindowText(m_sPasswordSS);

    GetDlgItem(IDC_COMBO_CHANNEL)->SendMessage(CB_ADDSTRING, 0, (long) _T("1"));
    GetDlgItem(IDC_COMBO_CHANNEL)->SendMessage(CB_ADDSTRING, 0, (long) _T("2"));
    GetDlgItem(IDC_COMBO_CHANNEL)->SendMessage(CB_ADDSTRING, 0, (long) _T("3"));
    GetDlgItem(IDC_COMBO_CHANNEL)->SendMessage(CB_ADDSTRING, 0, (long) _T("4"));
    GetDlgItem(IDC_COMBO_CHANNEL)->SendMessage(CB_SETCURSEL, m_nChannel-1, 0);
    
    GetDlgItem(IDC_COMBO_STREAM)->SendMessage(CB_ADDSTRING, 0, (long) _T("Primary"));
    GetDlgItem(IDC_COMBO_STREAM)->SendMessage(CB_ADDSTRING, 0, (long) _T("Secondary"));
    GetDlgItem(IDC_COMBO_STREAM)->SendMessage(CB_SETCURSEL, m_bSChnl, 0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConnectDlg::OnOK() 
{
	// TODO: Add extra validation here
	GetDlgItem(IDC_IPADDRESS_IP)->GetWindowText(m_sIP);
	GetDlgItem(IDC_EDIT_PORT)->GetWindowText(m_sPort);
	GetDlgItem(IDC_EDIT_LOGIN_NAME)->GetWindowText(m_sLoginName);
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(m_sPassword);
	m_bAudio = GetDlgItem(IDC_CH_AUDIO)->SendMessage(BM_GETCHECK, 0, 0);
//	m_bSChnl = GetDlgItem(IDC_CH_SECONDARY_CHNL)->SendMessage(BM_GETCHECK, 0, 0);
	m_bHD	 = GetDlgItem(IDC_CH_HD)->SendMessage(BM_GETCHECK, 0, 0);
    m_bSChnl = GetDlgItem(IDC_COMBO_STREAM)->SendMessage(CB_GETCURSEL, 0, 0);

    m_nChannel= GetDlgItem(IDC_COMBO_CHANNEL)->SendMessage(CB_GETCURSEL, 0, 0)+1;

	m_nProtocol = m_cbProtocol.GetCurSel();
	m_nUseSS = m_chUseSS.GetCheck();

	GetDlgItem(IDC_IPADDRESS_SS)->GetWindowText(m_sIPSS);
	GetDlgItem(IDC_EDIT_SS_PORT)->GetWindowText(m_sPortSS);
	GetDlgItem(IDC_EDIT_SS_LOGIN)->GetWindowText(m_sLoginSS);
	GetDlgItem(IDC_EDIT_SS_PASS)->GetWindowText(m_sPasswordSS);

	CDialog::OnOK();
}

void CConnectDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	m_cbProtocol.Detach();
	m_chUseSS.Detach();
}

void CConnectDlg::OnUseSS() 
{
	BOOL bEnable = m_chUseSS.GetCheck();
	GetDlgItem(IDC_IPADDRESS_SS)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_SS_PORT)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_SS_LOGIN)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_SS_PASS)->EnableWindow(bEnable);
}
