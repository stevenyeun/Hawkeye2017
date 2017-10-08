// basicDlg.cpp : implementation file
//

#include "stdafx.h"
#include "basic.h"
#include "basicDlg.h"
#include "ConnectDlg.h"
#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBasicDlg dialog

CBasicDlg::CBasicDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBasicDlg::IDD, pParent), m_bAutoSnap(FALSE), m_iSnapCnt(0)
{
	//{{AFX_DATA_INIT(CBasicDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pDataStreamFile = NULL;

	m_latency_frames = 8;

	m_nCh = 1;

	// 메시지 등록
	message = RegisterWindowMessage(_T("Hawkeye_AudioBroadcast"));
}
CBasicDlg::~CBasicDlg()
{
}

void CBasicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBasicDlg)
	//}}AFX_DATA_MAP
}
#define WM_TRAY_NOTIFICATION WM_APP + 1

BEGIN_MESSAGE_MAP(CBasicDlg, CDialog)
	//{{AFX_MSG_MAP(CBasicDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_SNAPSHOT, OnButtonSnapshot)
	ON_BN_CLICKED(IDC_BUTTON_TALKING, OnButtonTalking)
	ON_BN_CLICKED(IDC_BUTTON_ALARM1_SEND, OnButtonAlarm1Send)
	ON_BN_CLICKED(IDC_BUTTON_ALARM2_SEND, OnButtonAlarm2Send)
	ON_BN_CLICKED(IDC_BUTTON_PTZ_UP, OnButtonPtzUp)
	ON_BN_CLICKED(IDC_BUTTON_PTZ_DOWN, OnButtonPtzDown)
	ON_BN_CLICKED(IDC_BUTTON_PTZ_LEFT, OnButtonPtzLeft)
	ON_BN_CLICKED(IDC_BUTTON_PTZ_RIGHT, OnButtonPtzRight)
	ON_BN_CLICKED(IDC_BUTTON_PTZ_ZOOMIN, OnButtonPtzZoomin)
	ON_BN_CLICKED(IDC_BUTTON_PTZ_ZOOMOUT, OnButtonPtzZoomout)
	ON_BN_CLICKED(IDC_BUTTON_PTZ_FOCUSNEAR, OnButtonPtzFocusnear)
	ON_BN_CLICKED(IDC_BUTTON_PTZ_FOCUSFAR, OnButtonPtzFocusfar)
	ON_BN_CLICKED(IDC_BUTTON_PRESET_GOTO, OnButtonPresetGoto)
	ON_BN_CLICKED(IDC_BUTTON_DATASTREAM_FILENAME, OnButtonDatastreamFilename)
	ON_BN_CLICKED(IDC_BUTTON_SWRITE, OnButtonSwrite)
	ON_BN_CLICKED(IDC_BTN_DEC_START, OnBtnDecStart)
	ON_CBN_SELCHANGE(IDC_COMBO_OUTFORMAT, OnSelchangeComboOutformat)
	ON_BN_CLICKED(IDC_CHECK_FILEW, OnCheckFilew)
	ON_BN_CLICKED(IDC_BTN_GETFRAME, OnBtnGetframe)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnRefreshPreset)
	ON_BN_CLICKED(IDC_BUTTON_PLAYWAVE, OnButtonPlaywave)
	ON_BN_CLICKED(IDC_BUTTON_SCREEN_PTZ, OnButtonScreenPtz)
	ON_BN_CLICKED(IDC_RADIO_ASBUFFER, OnRadioAsbuffer)
	ON_BN_CLICKED(IDC_RADIO_ASFILE, OnRadioAsfile)
	ON_BN_CLICKED(IDC_BUTTON_GET_POSITION, OnButtonGetPosition)
	ON_CBN_SELCHANGE(IDC_COMBO_DEINTER, OnSelchangeComboDeinter)
	ON_BN_CLICKED(IDC_BUTTON_AUTOSNAP, OnButtonAutosnap)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_AV_APPLY, OnButtonAvApply)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_SERVER_GET, OnServerResolutionGet)
	ON_BN_CLICKED(IDC_SERVER_SET, OnServerResolutionSet)
	ON_BN_CLICKED(IDC_SERVER_GET2, OnServerBitrateGet)
	ON_BN_CLICKED(IDC_SERVER_SET2, OnServerBitrateSet)
	ON_MESSAGE(WM_TRAY_NOTIFICATION, OnTrayNotification)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


LRESULT CBasicDlg::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	switch (lParam)
	{
	case WM_RBUTTONDOWN:
	{
		CPoint ptMouse;
		::GetCursorPos(&ptMouse);

		CMenu menu;
		menu.LoadMenu(IDR_MAINFRAME);
		CMenu *pMenu = menu.GetSubMenu(0); //활성화 할 메뉴 지정
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
			ptMouse.x, ptMouse.y, AfxGetMainWnd());
	}
	break;

	case WM_LBUTTONDBLCLK:
	{
		NOTIFYICONDATA nid;
		ZeroMemory(&nid, sizeof(nid));
		nid.cbSize = sizeof(nid);
		nid.uID = 0;
		nid.hWnd = GetSafeHwnd();

		BOOL bRet = ::Shell_NotifyIcon(NIM_DELETE, &nid); //트레이아이콘 제거
		if (!bRet)
		{
			AfxMessageBox(_T("트레이 아이콘 제거 실패"));
			return -1;
		}
		AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOW); //윈도우 활성화
		AfxGetApp()->m_pMainWnd->ShowWindow(SW_NORMAL); 
	}
	break;
	}
	return 1;
}


void CBasicDlg::AddToLog(LPCTSTR pFormat, ...)
{
	//return;
	TCHAR pBuf[512];
	va_list pParams;
	va_start(pParams, pFormat);
	_vsntprintf(pBuf, 512, pFormat, pParams);
	va_end(pParams);

	if (!::IsWindow(m_log.GetSafeHwnd()) || !::IsWindowVisible(m_log.GetSafeHwnd()))
		return;

	int nIx = m_log.GetItemCount();
	m_log.InsertItem(nIx, pBuf);
	m_log.EnsureVisible(nIx, FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CBasicDlg message handlers

#include "CommonMFCFunc.h"
BOOL CBasicDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	

	

	int iCnt = __argc;                                   // 4
														 //LPCTSTR pszParam1 = __targv[0];         // d:\TEMP\CmdTest\Debug\CmdTest.exe
														 //LPCTSTR pszParam2 = __targv[1];        // abc
														 //LPCTSTR pszParam3 = __targv[2];        // test
														 //LPCTSTR pszParam4 = __targv[3];        // 123
														 //CString str1(__targv[0]);                       // d:\TEMP\CmdTest\Debug\CmdTest.exe
	CString str2(__targv[1]);                       // abc
													//CString str3(__targv[2]);                       // test
													//CString str4(__targv[3]);                       // 123

													//argv로 채널 번호를 넘겨줌
	int nCh = _wtoi(str2);
	if (nCh == 0)
		nCh = 1;

	CString strCh; strCh.Format(_T("채널 %d"), nCh);
	SetWindowText(strCh);

	m_nCh = nCh;
	int nIndexOfCh = m_nCh - 1;
	CString ServerIP;
	ServerIP.Format(
		_T("%s.%s.%s.%s"), m_iniIPSetup.m_s.tstrMICServerIPAddrFirst[nIndexOfCh],
		m_iniIPSetup.m_s.tstrMICServerIPAddrSecond[nIndexOfCh],
		m_iniIPSetup.m_s.tstrMICServerIPAddrThird[nIndexOfCh],
		m_iniIPSetup.m_s.tstrMICServerIPAddrForth[nIndexOfCh]
	);

	CString strID = m_iniIPSetup.m_s.tstrMICServerID[nIndexOfCh];
	CString strPW = m_iniIPSetup.m_s.tstrMICServerPW[nIndexOfCh];
#if 0
    m_sIP           = _T("192.168.10.102");
    m_sPort         = _T("2222");
    m_sLoginName    = _T("admin");
    m_sPassword     = _T("1234");
#else
	m_sIP = ServerIP;
	m_sPort = _T("2222");
	m_sLoginName = strID;
	m_sPassword = strPW;
#endif
    m_Protocol      = 0;
    m_bUseSS        = FALSE;
    m_bUseAudio     = TRUE;
    m_bHD           = FALSE;
    
    m_Channel       = 1;
    m_Stream        = 0; // primary
    

    m_sSSIP         = _T("192.168.10.175");
    m_sSSPort       = _T("2222");
    m_sSSLoginName  = _T("admin");
	m_sSSPassword   = _T("1234");

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_dlgVideo.Create(this);
	m_dlgDecode.Create(this);

	VARIANT var; var.vt = VT_I4;
	var.lVal = 1;
	m_dlgVideo.m_tvsLive.SetLocalConfig(TN_LCI_MAX_DISPLAY_CHANNEL, var);

	var.vt = VT_I4;
	var.lVal = 1;
	m_dlgVideo.m_tvsLive.SetLocalConfig(TN_LCI_SNAPSHOT_ASPECTRATIO, var);


#if 1 //To support 4, 5Mpixel resolution. With default setting in TVS(TN_RT_XDHF), up to 3Mpixel is supported
	var.vt = VT_I4;
	var.lVal = TN_RT_XHDF;
	m_dlgVideo.m_tvsLive.SetLocalConfig(TN_LCI_MAX_RESOLUTION, var);
#endif 

	m_log.Attach(GetDlgItem(IDC_LIST_LOG)->GetSafeHwnd());
	m_log.InsertColumn(0, _T("Log"), LVCFMT_LEFT, 500);


	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	pSlider->SetRange(1, 100);
	pSlider->SetPos(20);

	GetDlgItem(IDC_RADIO_AUTO_RECONNECT_ON)->SendMessage(BM_SETCHECK, BST_CHECKED, 0);
	GetDlgItem(IDC_RADIO_AUTO_RECONNECT_OFF)->SendMessage(BM_SETCHECK, BST_UNCHECKED, 0);
	GetDlgItem(IDC_RADIO_ASBUFFER)->SendMessage(BM_SETCHECK, BST_CHECKED, 0);
	GetDlgItem(IDC_RADIO_ASFILE)->SendMessage(BM_SETCHECK, BST_UNCHECKED, 0);

	GetDlgItem(IDC_BUTTON_TALKING)->SetWindowText(_T("Start Talking"));

	GetDlgItem(IDC_RADIO_ALARM1_ON)->SendMessage(BM_SETCHECK, BST_CHECKED, 0);
	GetDlgItem(IDC_RADIO_ALARM1_OFF)->SendMessage(BM_SETCHECK, BST_UNCHECKED, 0);
	GetDlgItem(IDC_RADIO_ALARM2_ON)->SendMessage(BM_SETCHECK, BST_CHECKED, 0);
	GetDlgItem(IDC_RADIO_ALARM2_OFF)->SendMessage(BM_SETCHECK, BST_UNCHECKED, 0);

	GetDlgItem(IDC_RADIO_ON_DATASTREAM_ON)->SendMessage(BM_SETCHECK, BST_CHECKED, 0);
	GetDlgItem(IDC_RADIO_ON_DATASTREAM_OFF)->SendMessage(BM_SETCHECK, BST_UNCHECKED, 0);

	m_dataStreamType.Attach(GetDlgItem(IDC_COMBO_DATASTREAM_TYPE)->GetSafeHwnd());
	m_dataStreamType.AddString(_T("Encoded"));
	m_dataStreamType.AddString(_T("Decoded"));
	m_dataStreamType.SetCurSel(0);
	m_nMTC = TN_ENCODED;

	m_DeinterType.Attach(GetDlgItem(IDC_COMBO_DEINTER)->GetSafeHwnd());
	m_DeinterType.AddString(_T("None"));	m_DeinterType.SetItemData(0, TN_DEINTERLACE_NONE);
	m_DeinterType.AddString(_T("Vertical filter")); m_DeinterType.SetItemData(1, TN_DEINTERLACE_VERTICAL_SMOOTH);
	m_DeinterType.AddString(_T("One field interpolation")); m_DeinterType.SetItemData(2, TN_DEINTERLACE_ONE_FIELD_INTERPOLATION);
	m_DeinterType.AddString(_T("Auto")); m_DeinterType.SetItemData(3, TN_DEINTERLACE_AUTO);
	m_DeinterType.SetCurSel(1);

	m_sDataStreamFileName = _T("c:\\datastream.raw");
	GetDlgItem(IDC_EDIT_DATASTREAM_FILENAME)->SetWindowText(m_sDataStreamFileName);

	m_lvPreset.Attach(GetDlgItem(IDC_LIST_PRESET)->GetSafeHwnd());
	m_lvPreset.InsertColumn(0,_T("No"), 0, 60, 0);
	m_lvPreset.InsertColumn(1,_T("Name"), 0, 120, 0);
	m_lvPreset.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_cbOutputFormat.Attach(GetDlgItem(IDC_COMBO_OUTFORMAT)->GetSafeHwnd());
	m_cbOutputFormat.AddString(_T("Default"));
	m_cbOutputFormat.AddString(_T("RGB24"));
	m_cbOutputFormat.AddString(_T("RGB32"));
	m_cbOutputFormat.AddString(_T("YUY2"));
	m_cbOutputFormat.SetCurSel(0);

	m_Bitrate.Attach(GetDlgItem(IDC_EDIT_BITRATE)->GetSafeHwnd());
	m_Resolution.Attach(GetDlgItem(IDC_COMBO_RESOLUTION)->GetSafeHwnd());

	int nCnt = sizeof(gResolution)/sizeof(gResolution[0]);
	for(int i=0; i<nCnt; i++)
	{
		m_Resolution.InsertString(i, gResolution[i].szResolution);
	}
	m_Resolution.SetCurSel(-1);

	TCHAR strAV[100]; strAV[0] = '\0';
	CComVariant varAV = m_dlgVideo.m_tvsLive.GetLocalConfig(TN_LCI_AVSYNC_ENABLE);
	GetDlgItem(IDC_CHECK_AVENABLE)->SendMessage(BM_SETCHECK, (varAV.boolVal == VARIANT_TRUE) ?  BST_CHECKED:BST_UNCHECKED, 0);

	m_eavResync.Attach(GetDlgItem(IDC_EDIT_AVR)->GetSafeHwnd());
	varAV = m_dlgVideo.m_tvsLive.GetLocalConfig(TN_LCI_AVSYNC_RESYNC);
	_itot(varAV.lVal, strAV, 10);
	m_eavResync.SetWindowText(strAV);

	m_eavABuffer.Attach(GetDlgItem(IDC_EDIT_AVA)->GetSafeHwnd());
	varAV = m_dlgVideo.m_tvsLive.GetLocalConfig(TN_LCI_ABUFFER);
	_itot(varAV.lVal, strAV, 10);
	m_eavABuffer.SetWindowText(strAV);

	m_latency_frames = 8;
	m_slider_latency.Attach(GetDlgItem(IDC_SLIDER_LATENCY)->GetSafeHwnd());
	m_slider_latency.SetRange(0, 30);
	m_slider_latency.SetPos(m_latency_frames);
	SetDlgItemText(IDC_STATIC_FR, _T("8 Frames"));
	varAV.vt = VT_I4;
	varAV = m_latency_frames;
	m_dlgVideo.m_tvsLive.SetLocalConfig(TN_LCI_BUFFER_FRAMES, varAV);


	//m_log.SendMessage(EM_EXLIMITTEXT, 0, 1024);

	CCommonMFCFunc::HideIconFromTaskbar();
	/////////////////////////////////////////////////////////////////////////////
#if 0
	NOTIFYICONDATA nid;
	ZeroMemory(&nid, sizeof(nid));
	nid.cbSize = sizeof(nid);
	nid.uID = 0;
	nid.hWnd = AfxGetApp()->m_pMainWnd->GetSafeHwnd();

	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	lstrcpy(nid.szTip, _T("HotKey Control"));
	nid.uCallbackMessage = WM_TRAY_NOTIFICATION;

	BOOL bRet = ::Shell_NotifyIcon(NIM_ADD, &nid); //트레이 아이콘 등록
	AfxGetApp()->m_pMainWnd->ShowWindow(SW_MINIMIZE); //윈도우 감추기
#endif
	////////////////////////////////////////////////////////////////////////////////
	
	
	PostMessage(WM_SHOWWINDOW, FALSE, SW_OTHERUNZOOM);
	OnButtonConnect();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBasicDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
		
	if(nSBCode == TB_ENDTRACK){
		if(pScrollBar->m_hWnd == m_slider_latency.m_hWnd)
		{
			VARIANT var; var.vt = VT_I4; 
			var.lVal = m_slider_latency.GetPos();
			m_dlgVideo.m_tvsLive.SetLocalConfig(TN_LCI_BUFFER_FRAMES, var);
			
			TCHAR sz[255];
			_stprintf(sz,_T("%i Frames"), var.lVal);
			SetDlgItemText(IDC_STATIC_FR, sz);
		}
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CBasicDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_pDataStreamFile)
	{
		fclose(m_pDataStreamFile);
		m_pDataStreamFile = NULL;
	}

	m_dataStreamType.Detach();
	m_DeinterType.Detach();

	m_lvPreset.Detach();

	m_cbOutputFormat.Detach();

	m_dlgVideo.DestroyWindow();

	m_log.Detach();

	m_eavResync.Detach();
	m_eavABuffer.Detach();
	m_slider_latency.Detach();
	m_Bitrate.Detach();
	m_Resolution.Detach();
}

void CBasicDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBasicDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBasicDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBasicDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CBasicDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CBasicDlg::Disconnect() 
{
	m_dlgVideo.m_tvsLive.Disconnect(m_dlgVideo.m_lCurChID);
	m_dlgVideo.m_lCurChID = 0;

	GetDlgItem(IDC_BUTTON_TALKING)->SetWindowText(_T("Start Talking"));
	
	m_lvPreset.DeleteAllItems();

	GetDlgItem(IDC_BUTTON_CONNECT)->SetWindowText(_T("Connect"));
	GetDlgItem(IDC_BUTTON_PLAY)->SetWindowText(_T("Play"));

	GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SNAPSHOT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_AUTOSNAP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TALKING)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ALARM1_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ALARM2_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PTZ_UP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PTZ_DOWN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PTZ_LEFT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PTZ_RIGHT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PTZ_ZOOMIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PTZ_ZOOMOUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PTZ_FOCUSNEAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PTZ_FOCUSFAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PRESET_GOTO)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIST_PRESET)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_PLAYWAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SCREEN_PTZ)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTON_GET_POSITION)->EnableWindow(FALSE);
	GetDlgItem(IDC_SERVER_GET)->EnableWindow(FALSE);
	GetDlgItem(IDC_SERVER_SET)->EnableWindow(FALSE);
	GetDlgItem(IDC_SERVER_GET2)->EnableWindow(FALSE);
	GetDlgItem(IDC_SERVER_SET2)->EnableWindow(FALSE);
}

void CBasicDlg::OnButtonConnect() 
{
#if 0
	VARIANT var; 
	if (m_dlgVideo.m_lCurChID <= 0)
	{
		CConnectDlg dlg;
        dlg.m_sIP           = m_sIP;
        dlg.m_sPort         = m_sPort;
        dlg.m_sLoginName    = m_sLoginName;
        dlg.m_sPassword     = m_sPassword;
        dlg.m_bAudio        = m_bUseAudio;
        dlg.m_bSChnl        = m_Stream;
        dlg.m_bHD           = m_bHD;
        dlg.m_nChannel      = m_Channel;

        dlg.m_nProtocol     = m_Protocol;
        dlg.m_nUseSS        = m_bUseSS;

        dlg.m_sIPSS         = m_sSSIP;
        dlg.m_sPortSS       = m_sSSPort;
        dlg.m_sLoginSS      = m_sSSLoginName;
        dlg.m_sPasswordSS   = m_sSSPassword;

		if (dlg.DoModal() != IDOK)
		{
			return;
		}

        m_sIP           = dlg.m_sIP;
        m_sPort         = dlg.m_sPort;
        m_sLoginName    = dlg.m_sLoginName;
        m_sPassword     = dlg.m_sPassword;
        m_bUseAudio     = dlg.m_bAudio;
        m_Stream        = dlg.m_bSChnl;
        m_bHD           = dlg.m_bHD;
        m_Channel       = dlg.m_nChannel;

        m_Protocol      = dlg.m_nProtocol;
        m_bUseSS        = dlg.m_nUseSS;

        m_sSSIP         = dlg.m_sIPSS;
        m_sSSPort       = dlg.m_sPortSS;
        m_sSSLoginName  = dlg.m_sLoginSS;
		m_sSSPassword   = dlg.m_sPasswordSS;

		CString sAddress;
        CString sAudio = _T("");
        if (dlg.m_bAudio)
        {
            sAudio.Format(_T("+audio%d"), dlg.m_nChannel);
        }

		if(dlg.m_nProtocol==0)
		{
			// tcp
            sAddress.Format(_T("vsnm://%s:%s//video%d%s%s"), dlg.m_sIP, dlg.m_sPort, dlg.m_nChannel, dlg.m_bSChnl?_T("s"):_T(""), sAudio);
		}
		else if(dlg.m_nProtocol==1)
			// multicast
            sAddress.Format(_T("vsnm-multicast://%s:%s//video%d%s%s"), dlg.m_sIP, dlg.m_sPort, dlg.m_nChannel, dlg.m_bSChnl?_T("s"):_T(""), sAudio);
		else{
			// udp
            sAddress.Format(_T("vsnm-udp://%s:%s//video%d%s%s"), dlg.m_sIP, dlg.m_sPort, dlg.m_nChannel, dlg.m_bSChnl?_T("s"):_T(""), sAudio);
		}

        var.vt = VT_I4;
		var.lVal = dlg.m_bHD ? 1 : 0;
		m_dlgVideo.m_tvsLive.SetLocalConfig(TN_LCI_MAX_HD_CHANNEL, var);


		/*var.vt = VT_I4;
		var.iVal = 20;
		m_dlgVideo.m_tvsLive.SetLocalConfig(TN_LCI_BUFFER_FRAMES, var);*/

//        sAddress += _T("&SS=192.168.0.33:2222");

		if(dlg.m_nUseSS)
		{
			CString sAddressSS;
			sAddressSS = dlg.m_sIPSS + _T(":") + dlg.m_sPortSS;
			m_dlgVideo.m_lCurChID = m_dlgVideo.m_tvsLive.Connect2(sAddress, dlg.m_sLoginName, dlg.m_sPassword, sAddressSS, dlg.m_sLoginSS, dlg.m_sPasswordSS);
		}
		else{
			m_dlgVideo.m_lCurChID = m_dlgVideo.m_tvsLive.Connect(sAddress, dlg.m_sLoginName, dlg.m_sPassword);
		}

		if (m_dlgVideo.m_lCurChID <= 0)
		{
			AddToLog(_T("Connection error(%d)\r\n"), m_dlgVideo.m_lCurChID);
			MessageBox(_T("Connection Fail"));
			return;
		}

		m_dlgVideo.m_tvsDisplay.SetMapChannel(0, 0, m_dlgVideo.m_lCurChID);

		GetDlgItem(IDC_BUTTON_CONNECT)->SetWindowText(_T("Disconnect"));

		GetDlgItem(IDC_BUTTON_TALKING)->SetWindowText(_T("Start Talking"));

		if (GetDlgItem(IDC_RADIO_AUTO_RECONNECT_ON)->SendMessage(BM_GETCHECK, 0, 0))
		{
			m_dlgVideo.m_tvsLive.SetAutoReconnect(m_dlgVideo.m_lCurChID, TRUE);
		}
		else
		{
			m_dlgVideo.m_tvsLive.SetAutoReconnect(m_dlgVideo.m_lCurChID, FALSE);
		}
		m_lvPreset.DeleteAllItems();


	USES_CONVERSION;		
	var = m_dlgVideo.m_tvsLive.GetPTZPresetList(m_dlgVideo.m_lCurChID);

	int nSize = 0;

	SAFEARRAY *psa = (var.vt & VT_ARRAY)?var.parray:NULL;
	if (psa && (nSize = SafeArrayGetElemsize(psa)))
	{
			m_lvPreset.EnableWindow(TRUE);
			long ix = 0;
			for (unsigned int i=0;i<nSize;i++)
			{
				ix = i;
				VARIANT vItem;
				VariantInit(&vItem);
				HRESULT hr = SafeArrayGetElement(psa, &ix, (PVOID)&vItem); 

				char szItem[255];
				if (hr == S_OK && vItem.vt == VT_BSTR && vItem.bstrVal && lstrlen(OLE2T(vItem.bstrVal))>8)
				{
					int id=0;
					strcpy(szItem, OLE2A(vItem.bstrVal));
					sscanf(szItem, "%08x", &id);
					int nItem = m_lvPreset.InsertItem(i, A2T(&szItem[8]));
					m_lvPreset.SetItemData(nItem, id);
				}
			}
			//SafeArrayDestroy(psa);
	}else{
		//m_lvPreset.AddString(_T("No presets"));
		//m_lvPreset.SetCurSel(0);
		m_lvPreset.EnableWindow(FALSE);
	}
	VariantClear(&var);

		GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow();
		GetDlgItem(IDC_BUTTON_SNAPSHOT)->EnableWindow();
		GetDlgItem(IDC_BUTTON_AUTOSNAP)->EnableWindow();
		GetDlgItem(IDC_BUTTON_TALKING)->EnableWindow();
		GetDlgItem(IDC_BUTTON_ALARM1_SEND)->EnableWindow();
		GetDlgItem(IDC_BUTTON_ALARM2_SEND)->EnableWindow();
		GetDlgItem(IDC_BUTTON_PTZ_UP)->EnableWindow();
		GetDlgItem(IDC_BUTTON_PTZ_DOWN)->EnableWindow();
		GetDlgItem(IDC_BUTTON_PTZ_LEFT)->EnableWindow();
		GetDlgItem(IDC_BUTTON_PTZ_RIGHT)->EnableWindow();
		GetDlgItem(IDC_BUTTON_PTZ_ZOOMIN)->EnableWindow();
		GetDlgItem(IDC_BUTTON_PTZ_ZOOMOUT)->EnableWindow();
		GetDlgItem(IDC_BUTTON_PTZ_FOCUSNEAR)->EnableWindow();
		GetDlgItem(IDC_BUTTON_PTZ_FOCUSFAR)->EnableWindow();
		GetDlgItem(IDC_BUTTON_PRESET_GOTO)->EnableWindow();
		GetDlgItem(IDC_LIST_PRESET)->EnableWindow();
        GetDlgItem(IDC_BUTTON_PLAYWAVE)->EnableWindow();
		GetDlgItem(IDC_BUTTON_SCREEN_PTZ)->EnableWindow();
		GetDlgItem(IDC_BUTTON_GET_POSITION)->EnableWindow();
		GetDlgItem(IDC_SERVER_GET)->EnableWindow();
		GetDlgItem(IDC_SERVER_SET)->EnableWindow();
		GetDlgItem(IDC_SERVER_GET2)->EnableWindow();
		GetDlgItem(IDC_SERVER_SET2)->EnableWindow();
	
	}
	else
	{
		Disconnect();
	}
#else

VARIANT var;
if (m_dlgVideo.m_lCurChID <= 0)
{
	CConnectDlg dlg;
	dlg.m_sIP = m_sIP;
	dlg.m_sPort = m_sPort;
	dlg.m_sLoginName = m_sLoginName;
	dlg.m_sPassword = m_sPassword;
	dlg.m_bAudio = m_bUseAudio;
	dlg.m_bSChnl = m_Stream;
	dlg.m_bHD = m_bHD;
	dlg.m_nChannel = m_Channel;

	dlg.m_nProtocol = m_Protocol;
	dlg.m_nUseSS = m_bUseSS;

	dlg.m_sIPSS = m_sSSIP;
	dlg.m_sPortSS = m_sSSPort;
	dlg.m_sLoginSS = m_sSSLoginName;
	dlg.m_sPasswordSS = m_sSSPassword;

	//if (dlg.DoModal() != IDOK)
	//{
	//	return;
	//}

	m_sIP = dlg.m_sIP;
	m_sPort = dlg.m_sPort;
	m_sLoginName = dlg.m_sLoginName;
	m_sPassword = dlg.m_sPassword;
	m_bUseAudio = dlg.m_bAudio;
	m_Stream = dlg.m_bSChnl;
	m_bHD = dlg.m_bHD;
	m_Channel = dlg.m_nChannel;

	m_Protocol = dlg.m_nProtocol;
	m_bUseSS = dlg.m_nUseSS;

	m_sSSIP = dlg.m_sIPSS;
	m_sSSPort = dlg.m_sPortSS;
	m_sSSLoginName = dlg.m_sLoginSS;
	m_sSSPassword = dlg.m_sPasswordSS;

	CString sAddress;
	CString sAudio = _T("");
	if (dlg.m_bAudio)
	{
		sAudio.Format(_T("+audio%d"), dlg.m_nChannel);
	}

	if (dlg.m_nProtocol == 0)
	{
		// tcp
		sAddress.Format(_T("vsnm://%s:%s//video%d%s%s"), dlg.m_sIP, dlg.m_sPort, dlg.m_nChannel, dlg.m_bSChnl ? _T("s") : _T(""), sAudio);
	}
	else if (dlg.m_nProtocol == 1)
		// multicast
		sAddress.Format(_T("vsnm-multicast://%s:%s//video%d%s%s"), dlg.m_sIP, dlg.m_sPort, dlg.m_nChannel, dlg.m_bSChnl ? _T("s") : _T(""), sAudio);
	else {
		// udp
		sAddress.Format(_T("vsnm-udp://%s:%s//video%d%s%s"), dlg.m_sIP, dlg.m_sPort, dlg.m_nChannel, dlg.m_bSChnl ? _T("s") : _T(""), sAudio);
	}

	var.vt = VT_I4;
	var.lVal = dlg.m_bHD ? 1 : 0;
	m_dlgVideo.m_tvsLive.SetLocalConfig(TN_LCI_MAX_HD_CHANNEL, var);


	/*var.vt = VT_I4;
	var.iVal = 20;
	m_dlgVideo.m_tvsLive.SetLocalConfig(TN_LCI_BUFFER_FRAMES, var);*/

	//        sAddress += _T("&SS=192.168.0.33:2222");

	if (dlg.m_nUseSS)
	{
		CString sAddressSS;
		sAddressSS = dlg.m_sIPSS + _T(":") + dlg.m_sPortSS;
		m_dlgVideo.m_lCurChID = m_dlgVideo.m_tvsLive.Connect2(sAddress, dlg.m_sLoginName, dlg.m_sPassword, sAddressSS, dlg.m_sLoginSS, dlg.m_sPasswordSS);
	}
	else {
		m_dlgVideo.m_lCurChID = m_dlgVideo.m_tvsLive.Connect(sAddress, dlg.m_sLoginName, dlg.m_sPassword);
	}

	if (m_dlgVideo.m_lCurChID <= 0)
	{
		AddToLog(_T("Connection error(%d)\r\n"), m_dlgVideo.m_lCurChID);
		MessageBox(_T("Connection Fail"));
		return;
	}

	m_dlgVideo.m_tvsDisplay.SetMapChannel(0, 0, m_dlgVideo.m_lCurChID);

	GetDlgItem(IDC_BUTTON_CONNECT)->SetWindowText(_T("Disconnect"));

	GetDlgItem(IDC_BUTTON_TALKING)->SetWindowText(_T("Start Talking"));

	if (GetDlgItem(IDC_RADIO_AUTO_RECONNECT_ON)->SendMessage(BM_GETCHECK, 0, 0))
	{
		m_dlgVideo.m_tvsLive.SetAutoReconnect(m_dlgVideo.m_lCurChID, TRUE);
	}
	else
	{
		m_dlgVideo.m_tvsLive.SetAutoReconnect(m_dlgVideo.m_lCurChID, FALSE);
	}
	m_lvPreset.DeleteAllItems();


	USES_CONVERSION;
	var = m_dlgVideo.m_tvsLive.GetPTZPresetList(m_dlgVideo.m_lCurChID);

	int nSize = 0;

	SAFEARRAY *psa = (var.vt & VT_ARRAY) ? var.parray : NULL;
	if (psa && (nSize = SafeArrayGetElemsize(psa)))
	{
		m_lvPreset.EnableWindow(TRUE);
		long ix = 0;
		for (unsigned int i = 0; i < nSize; i++)
		{
			ix = i;
			VARIANT vItem;
			VariantInit(&vItem);
			HRESULT hr = SafeArrayGetElement(psa, &ix, (PVOID)&vItem);

			char szItem[255];
			if (hr == S_OK && vItem.vt == VT_BSTR && vItem.bstrVal && lstrlen(OLE2T(vItem.bstrVal)) > 8)
			{
				int id = 0;
				strcpy(szItem, OLE2A(vItem.bstrVal));
				sscanf(szItem, "%08x", &id);
				int nItem = m_lvPreset.InsertItem(i, A2T(&szItem[8]));
				m_lvPreset.SetItemData(nItem, id);
			}
		}
		//SafeArrayDestroy(psa);
	}
	else {
		//m_lvPreset.AddString(_T("No presets"));
		//m_lvPreset.SetCurSel(0);
		m_lvPreset.EnableWindow(FALSE);
	}
	VariantClear(&var);

	GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow();
	GetDlgItem(IDC_BUTTON_SNAPSHOT)->EnableWindow();
	GetDlgItem(IDC_BUTTON_AUTOSNAP)->EnableWindow();
	GetDlgItem(IDC_BUTTON_TALKING)->EnableWindow();
	GetDlgItem(IDC_BUTTON_ALARM1_SEND)->EnableWindow();
	GetDlgItem(IDC_BUTTON_ALARM2_SEND)->EnableWindow();
	GetDlgItem(IDC_BUTTON_PTZ_UP)->EnableWindow();
	GetDlgItem(IDC_BUTTON_PTZ_DOWN)->EnableWindow();
	GetDlgItem(IDC_BUTTON_PTZ_LEFT)->EnableWindow();
	GetDlgItem(IDC_BUTTON_PTZ_RIGHT)->EnableWindow();
	GetDlgItem(IDC_BUTTON_PTZ_ZOOMIN)->EnableWindow();
	GetDlgItem(IDC_BUTTON_PTZ_ZOOMOUT)->EnableWindow();
	GetDlgItem(IDC_BUTTON_PTZ_FOCUSNEAR)->EnableWindow();
	GetDlgItem(IDC_BUTTON_PTZ_FOCUSFAR)->EnableWindow();
	GetDlgItem(IDC_BUTTON_PRESET_GOTO)->EnableWindow();
	GetDlgItem(IDC_LIST_PRESET)->EnableWindow();
	GetDlgItem(IDC_BUTTON_PLAYWAVE)->EnableWindow();
	GetDlgItem(IDC_BUTTON_SCREEN_PTZ)->EnableWindow();
	GetDlgItem(IDC_BUTTON_GET_POSITION)->EnableWindow();
	GetDlgItem(IDC_SERVER_GET)->EnableWindow();
	GetDlgItem(IDC_SERVER_SET)->EnableWindow();
	GetDlgItem(IDC_SERVER_GET2)->EnableWindow();
	GetDlgItem(IDC_SERVER_SET2)->EnableWindow();

}
else
{
	Disconnect();
}
#endif


}

void CBasicDlg::Pause() 
{
	if (GetDlgItem(IDC_RADIO_ON_DATASTREAM_ON)->SendMessage(BM_GETCHECK, 0, 0))
	{
		/*m_dlgVideo.m_tvsLive.StopStreamDataEvent(m_dlgVideo.m_lCurChID, m_nMTC);

		if (m_pDataStreamFile)
		{
			fclose(m_pDataStreamFile);
			m_pDataStreamFile = NULL;
		}*/
	}
	/*m_dataStreamType.EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_ON_DATASTREAM_ON)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_ON_DATASTREAM_OFF)->EnableWindow(TRUE);*/
	
	//Remove osd area when paused by YI
	m_dlgVideo.m_tvsDisplay.RemoveOsdArea(m_dlgVideo.m_lOsdID);
	m_dlgVideo.m_tvsDisplay.RemoveOsdArea(m_dlgVideo.m_lOsdID2);
	m_dlgVideo.m_lOsdID = -1;
	m_dlgVideo.m_lOsdID2 = -1;

	if (m_dlgVideo.m_tvsLive.Pause(m_dlgVideo.m_lCurChID))
	{

		m_dlgVideo.m_tvsLive.SetMute(m_dlgVideo.m_lCurChID, TRUE);
		GetDlgItem(IDC_BUTTON_PLAY)->SetWindowText(_T("Play"));

	}
}

void CBasicDlg::OnButtonPlay()
{
	// TODO: Add your control notification handler code here
	if (!(m_dlgVideo.m_tvsLive.GetChannelState(m_dlgVideo.m_lCurChID) & TN_CS_DISPLAYED))
	{
		if (m_dlgVideo.m_tvsLive.Play(m_dlgVideo.m_lCurChID))
		{
			m_dlgVideo.m_tvsLive.SetMute(m_dlgVideo.m_lCurChID, FALSE);

			GetDlgItem(IDC_BUTTON_PLAY)->SetWindowText(_T("Pause"));

			//using OSDID to add osd area by YI
			m_dlgVideo.m_lOsdID = m_dlgVideo.m_tvsDisplay.AddOsdArea(m_dlgVideo.m_lCurChID, 10, 10, 500, 40, 0);
			m_dlgVideo.m_tvsDisplay.SetOsdFontSize(m_dlgVideo.m_lOsdID, 14);
			VARIANT var;
			VariantInit(&var);
			var.vt = VT_BSTR;
			var.bstrVal = new WCHAR[256];
			CString str = m_dlgVideo.m_tvsLive.GetAddress(m_dlgVideo.m_lCurChID);
	
			memset(var.bstrVal, 0, 256*2);
#ifndef _UNICODE
			mbstowcs(var.bstrVal, (LPCTSTR)str, str.GetLength());
#else
			_tcscpy(var.bstrVal, (LPCTSTR)str);
#endif
			m_dlgVideo.m_tvsDisplay.UpdateOsdArea(m_dlgVideo.m_lOsdID, var);
			delete [] var.bstrVal;

			int mt = m_dlgVideo.m_tvsLive.GetMediaType(m_dlgVideo.m_lCurChID);
			VARIANT resolution = m_Stream ?
                m_dlgVideo.m_tvsLive.GetServerConfig(m_dlgVideo.m_lCurChID, TN_SC_VIDEO_RESOLUTION_SEC) :
                m_dlgVideo.m_tvsLive.GetServerConfig(m_dlgVideo.m_lCurChID, TN_SC_VIDEO_RESOLUTION);

			CString szTitle; 
			switch(mt){
			case TN_MTC_MPEG_4:
				szTitle = _T("MPEG4: ");
				break;
//			case TN_MTC_H_264_JPEG:
//				szTitle = _T("JPEG: ");
//				break;
			case TN_MTC_H_264:
				szTitle = _T("H.264: ");
				break;
			default:
				szTitle = _T("UNKNOWN: ");
				break;
			}

			switch(resolution.lVal){
			case 0:
				szTitle += _T("720x480");
				break;
			case 1:
				szTitle += _T("720x240");
				break;
			case 2:
				szTitle += _T("352x480");
				break;
			case 3:
				szTitle += _T("352x240");
				break;  
			case 4: 
				szTitle += _T("720x576");
				break;
			case 5: 
				szTitle += _T("720x288");
				break;
			case 6: 
				szTitle += _T("352x576");
				break;
			case 7: 
				szTitle += _T("352x288");
				break;
			case 8: 
				szTitle += _T("640x480");
				break;	
			case 9: 
				szTitle += _T("800x600");
				break;
			case 10: 
				szTitle += _T("1024x768");
				break;
			case 11: 
				szTitle += _T("1280x960");
				break;
			case 12: 
				szTitle += _T("1280x1024");
				break;
			case 13: 
				szTitle += _T("1440x900");
				break;
			case 14: 
				szTitle += _T("1600x900");
				break;
			case 15: 
				szTitle += _T("1680x1050");
				break;
			case 16:
				szTitle += _T("1280x720");
				break;
			case 17:
				szTitle += _T("1920x1080");
				break;
			case 18:
				szTitle += _T("176x128");
				break;
			case 19:
				szTitle += _T("176x144");
				break;
			case 20:
				szTitle += _T("320x288");
				break;
			case 21:
				szTitle += _T("360x288");
				break;
			case 22:
				szTitle += _T("320x240");
				break;
			case 23:
				szTitle += _T("2048x1536");
				break;
			case 24:
				szTitle += _T("2560x1600");
				break;
			case 25:
				szTitle += _T("2592x1936");
				break;
			case 26:
				szTitle += _T("1920x1056");
				break;
			case 27:
				szTitle += _T("640x360");
				break;
			}

			CComVariant vars;
			vars = szTitle;
			m_dlgVideo.m_lOsdID2 = m_dlgVideo.m_tvsDisplay.AddOsdArea(m_dlgVideo.m_lCurChID, 10, 50, 250, 100, 0);
			m_dlgVideo.m_tvsDisplay.SetOsdFontSize(m_dlgVideo.m_lOsdID2, 14);
			m_dlgVideo.m_tvsDisplay.UpdateOsdArea(m_dlgVideo.m_lOsdID2, vars);

			OnServerResolutionGet();
			OnServerBitrateGet();
		}
		else
		{
			AddToLog(_T("Failed to Play\r\n"));
		}
	}
	else
	{
		Pause();
	}
}

void CBasicDlg::OnButtonSnapshot() 
{
#if 1
	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	long lCompression = pSlider->GetPos();

	m_dlgVideo.m_tvsLive.Snapshot(m_dlgVideo.m_lCurChID, 0, VARIANT_FALSE);
    m_dlgVideo.m_tvsLive.PreviewSnapshot(m_dlgVideo.m_lCurChID);

	if (GetDlgItem(IDC_RADIO_ASFILE)->SendMessage(BM_GETCHECK, 0, 0))
		m_dlgVideo.m_tvsLive.SaveSnapshot(m_dlgVideo.m_lCurChID, lCompression, _T("C:\\temp\\test_asfile.jpg"));
	else
	{
//		BYTE *buf;
		long bufSize;
		int width, height;
		VARIANT var;

		TCHAR tc[32];
		::GetWindowText(GetDlgItem(IDC_EDIT_RESOL_X)->m_hWnd, tc, 12);
		width = _ttoi(tc);
		::GetWindowText(GetDlgItem(IDC_EDIT_RESOL_Y)->m_hWnd, tc, 12);
		height = _ttoi(tc);

		m_dlgVideo.m_tvsLive.GetSnapshot(m_dlgVideo.m_lCurChID, lCompression, width, height, &var, &bufSize);

		CFile oWrFile;
		oWrFile.Open(_T("C:\\temp\\test_asbuffer.jpg"), CFile::modeCreate | 
			CFile::modeReadWrite);

		oWrFile.Write(var.pbVal, bufSize);
		oWrFile.Close();
		CoTaskMemFree(var.pbVal);
	}

#else
	m_dlgVideo.m_tvsLive.Snapshot(m_dlgVideo.m_lCurChID, 0, VARIANT_FALSE);
	m_dlgVideo.m_tvsLive.PreviewSnapshot(m_dlgVideo.m_lCurChID);
	m_dlgVideo.m_tvsLive.SaveSnapshot(m_dlgVideo.m_lCurChID, 1, _T("C:\\temp\\test.jpg"));
#endif
}

void CBasicDlg::OnButtonAutosnap() 
{
	m_bAutoSnap = !m_bAutoSnap;
	GetDlgItem(IDC_BUTTON_AUTOSNAP)->SetWindowText(m_bAutoSnap ? _T("Stop") :_T("Start!"));

	if(m_bAutoSnap)
		SetTimer(10, 100, NULL);
	else
		KillTimer(10);
}

void CBasicDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == 10)
	{
		m_iSnapCnt++;
		CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
		long lCompression = pSlider->GetPos();

		m_dlgVideo.m_tvsLive.Snapshot(m_dlgVideo.m_lCurChID, 0, VARIANT_FALSE);
		TCHAR tcPath[255], tcCnt[64];
		_tcscpy(tcPath, _T("C:\\temp\\auto_"));
		_itot(m_iSnapCnt, tcCnt, 10);
		_tcscat(tcPath, tcCnt);
		_tcscat(tcPath, _T(".jpg"));
		m_dlgVideo.m_tvsLive.SaveSnapshot(m_dlgVideo.m_lCurChID, lCompression, tcPath);
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CBasicDlg::OnButtonTalking() 
{
	// TODO: Add your control notification handler code here
	CString sText;
	GetDlgItem(IDC_BUTTON_TALKING)->GetWindowText(sText);
	if (!sText.Compare(_T("Start Talking")))
	{
		m_dlgVideo.m_tvsLive.StartTalking(m_dlgVideo.m_lCurChID);
		GetDlgItem(IDC_BUTTON_TALKING)->SetWindowText(_T("Stop Talking"));
	}
	else
	{
		m_dlgVideo.m_tvsLive.StopTalking(m_dlgVideo.m_lCurChID);
		GetDlgItem(IDC_BUTTON_TALKING)->SetWindowText(_T("Start Talking"));
	}
}

void CBasicDlg::OnButtonAlarm1Send() 
{
	// TODO: Add your control notification handler code here
	//try 
	//{
		if (GetDlgItem(IDC_RADIO_ALARM1_ON)->SendMessage(BM_GETCHECK, 0, 0))
		{
			m_dlgVideo.m_tvsLive.SetDO(m_dlgVideo.m_lCurChID, TN_DO_RELAY_1, TN_ES_ON);
		}
		else
		{
			m_dlgVideo.m_tvsLive.SetDO(m_dlgVideo.m_lCurChID, TN_DO_RELAY_1, TN_ES_OFF);
		}
	//}
	//catch (CException e)
	//{
	//	TCHAR pErrorText[256];
	//	e.GetErrorMessage(pErrorText, 256);
	//	AfxMessageBox(pErrorText);
	//}
}

void CBasicDlg::OnButtonAlarm2Send() 
{
	// TODO: Add your control notification handler code here
	if (GetDlgItem(IDC_RADIO_ALARM2_ON)->SendMessage(BM_GETCHECK, 0, 0))
	{
		m_dlgVideo.m_tvsLive.SetDO(m_dlgVideo.m_lCurChID, TN_DO_RELAY_2, TN_ES_ON);
	}
	else
	{
		m_dlgVideo.m_tvsLive.SetDO(m_dlgVideo.m_lCurChID, TN_DO_RELAY_2, TN_ES_OFF);
	}
}

void CBasicDlg::OnButtonPtz(LPCTSTR pCmd) 
{
	// TODO: Add your control notification handler code here
	if (!_tcscmp(pCmd, _T("Up")))
	{
		m_dlgVideo.m_tvsLive.SendPTZCommand(m_dlgVideo.m_lCurChID, TN_PTZ_UP);
	}
	else if (!_tcscmp(pCmd, _T("Down")))
	{
		m_dlgVideo.m_tvsLive.SendPTZCommand(m_dlgVideo.m_lCurChID, TN_PTZ_DOWN);
	}
	else if (!_tcscmp(pCmd, _T("Left")))
	{
		m_dlgVideo.m_tvsLive.SendPTZCommand(m_dlgVideo.m_lCurChID, TN_PTZ_LEFT);
	}
	else if (!_tcscmp(pCmd, _T("Right")))
	{
		m_dlgVideo.m_tvsLive.SendPTZCommand(m_dlgVideo.m_lCurChID, TN_PTZ_RIGHT);
	}
	else if (!_tcscmp(pCmd, _T("ZoomIn")))
	{
		m_dlgVideo.m_tvsLive.SendPTZCommand(m_dlgVideo.m_lCurChID, TN_PTZ_ZOOMIN);
	}
	else if (!_tcscmp(pCmd, _T("ZoomOut")))
	{
		m_dlgVideo.m_tvsLive.SendPTZCommand(m_dlgVideo.m_lCurChID, TN_PTZ_ZOOMOUT);
	}
	else if (!_tcscmp(pCmd, _T("FocusNear")))
	{
		m_dlgVideo.m_tvsLive.SendPTZCommand(m_dlgVideo.m_lCurChID, TN_PTZ_FOCUSNEAR);
	}
	else if (!_tcscmp(pCmd, _T("FocusFar")))
	{
		m_dlgVideo.m_tvsLive.SendPTZCommand(m_dlgVideo.m_lCurChID, TN_PTZ_FOCUSFAR);
	}
}

void CBasicDlg::OnButtonPtzUp() 
{
	// TODO: Add your control notification handler code here
	OnButtonPtz(_T("Up"));
}

void CBasicDlg::OnButtonPtzDown() 
{
	// TODO: Add your control notification handler code here
	OnButtonPtz(_T("Down"));
}

void CBasicDlg::OnButtonPtzLeft() 
{
	// TODO: Add your control notification handler code here
	OnButtonPtz(_T("Left"));
}

void CBasicDlg::OnButtonPtzRight() 
{
	// TODO: Add your control notification handler code here
	OnButtonPtz(_T("Right"));
}

void CBasicDlg::OnButtonPtzZoomin() 
{
	// TODO: Add your control notification handler code here
	OnButtonPtz(_T("ZoomIn"));
}

void CBasicDlg::OnButtonPtzZoomout() 
{
	// TODO: Add your control notification handler code here
	OnButtonPtz(_T("ZoomOut"));
}

void CBasicDlg::OnButtonPtzFocusnear() 
{
	// TODO: Add your control notification handler code here
	OnButtonPtz(_T("FocusNear"));
}

void CBasicDlg::OnButtonPtzFocusfar() 
{
	// TODO: Add your control notification handler code here
	OnButtonPtz(_T("FocusFar"));
}

void CBasicDlg::OnButtonScreenPtz() 
{
	// TODO: Add your control notification handler code here
	CString sText;
	GetDlgItem(IDC_BUTTON_SCREEN_PTZ)->GetWindowText(sText);
	if (!sText.Compare(_T("Start PTZ on Screen")))
	{
		m_dlgVideo.m_tvsLive.StartOnScreenPTZ();
		GetDlgItem(IDC_BUTTON_SCREEN_PTZ)->SetWindowText(_T("Stop PTZ on Screen"));
	}
	else
	{
		m_dlgVideo.m_tvsLive.StopOnScreenPTZ();	
		GetDlgItem(IDC_BUTTON_SCREEN_PTZ)->SetWindowText(_T("Start PTZ on Screen"));
	}
}

void CBasicDlg::OnRefreshPreset() 
{
	VARIANT var; 
	m_lvPreset.DeleteAllItems();
	
	USES_CONVERSION;		
	var = m_dlgVideo.m_tvsLive.GetPTZPresetList(m_dlgVideo.m_lCurChID);
	
	int nSize = 0;
	
	SAFEARRAY *psa = (var.vt & VT_ARRAY)?var.parray:NULL;
	if (psa && (nSize = SafeArrayGetElemsize(psa)))
	{
		m_lvPreset.EnableWindow(TRUE);
		long ix = 0;
		for (unsigned int i=0;i<nSize;i++)
		{
			ix = i;
			VARIANT vItem;
			VariantInit(&vItem);
			HRESULT hr = SafeArrayGetElement(psa, &ix, (PVOID)&vItem); 
			
			char szItem[255];
			if (hr == S_OK && vItem.vt == VT_BSTR && vItem.bstrVal && lstrlen(OLE2T(vItem.bstrVal))>8)
			{
				int id=0;
				strcpy(szItem, OLE2A(vItem.bstrVal));
				sscanf(szItem, "%08x", &id);
				int nItem = m_lvPreset.InsertItem(i, A2T(&szItem[8]));
				m_lvPreset.SetItemData(nItem, id);
			}
		}
		//SafeArrayDestroy(psa);
	}else{
		//m_lvPreset.AddString(_T("No presets"));
		//m_lvPreset.SetCurSel(0);
		m_lvPreset.EnableWindow(FALSE);
	}
	VariantClear(&var);
	
}

void CBasicDlg::OnButtonPresetGoto() 
{
	static int nPresetID = 0;
	
	VARIANT var;
	var.vt = VT_I2;
	var.iVal = nPresetID++ % 4;
	//m_dlgVideo.m_tvsLive.SetPTZPreset(m_dlgVideo.m_lCurChID, var);

	int nIndex = m_lvPreset.GetSelectionMark();
	VARIANT vr;
	vr.vt = VT_I4;
	vr.lVal = m_lvPreset.GetItemData(nIndex);
	m_dlgVideo.m_tvsLive.GoToPTZPreset(m_dlgVideo.m_lCurChID, vr);

/*	// TODO: Add your control notification handler code here
	static long lPan, lTilt, lZoom, lFocus;
	m_dlgVideo.m_tvsLive.GetPTZPosition(m_dlgVideo.m_lCurChID, &lPan, &lTilt, &lZoom, &lFocus);

	m_dlgVideo.m_tvsLive.SetPTZPosition(m_dlgVideo.m_lCurChID, lPan, lTilt, lZoom, lFocus);

	m_dlgVideo.m_tvsLive.SetPTZControlSpeed(m_dlgVideo.m_lCurChID, 0, 10);

	POSITION pos = m_lvPreset.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
//		return;
	}
	
	VARIANT var;
	var.vt = VT_I2;
//	var.iVal = m_lvPreset.GetNextSelectedItem(pos);
	var.iVal = 0;
	m_dlgVideo.m_tvsLive.SetPTZPreset(m_dlgVideo.m_lCurChID, var);*/
}

void CBasicDlg::OnButtonDatastreamFilename() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(FALSE, _T("raw"), NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, _T("Stream Data Files  (*.raw)|*.raw|All Files (*.*)|*.*||"));

	_tcscpy(dlg.m_ofn.lpstrFile, m_sDataStreamFileName);
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	m_sDataStreamFileName = dlg.m_ofn.lpstrFile;
	GetDlgItem(IDC_EDIT_DATASTREAM_FILENAME)->SetWindowText(m_sDataStreamFileName);
}

void CBasicDlg::OnButtonSwrite() 
{
	m_dlgVideo.m_nFrmIdx = 0;

	int is_streamed = m_dlgVideo.m_tvsLive.GetChannelState(m_dlgVideo.m_lCurChID) & TN_CS_STREAMED;
	switch (m_dataStreamType.GetCurSel())
	{
	case 0:
		m_nMTC = TN_ENCODED;
		break;
	case 1:
		m_nMTC = TN_DECODED;
		break;
	}
	
	
	if (!is_streamed){
		if (m_pDataStreamFile)
		{
			fclose(m_pDataStreamFile);
			m_pDataStreamFile = NULL;
		}
		
		if (GetDlgItem(IDC_RADIO_ON_DATASTREAM_ON)->SendMessage(BM_GETCHECK, 0, 0))
		{
			if(GetDlgItem(IDC_CHECK_FILEW)->SendMessage(BM_GETCHECK, 0, 0))
				m_pDataStreamFile = _tfopen(m_sDataStreamFileName.GetBuffer(0), _T("wb"));
			
			m_dlgVideo.m_tvsLive.StartStreamDataEvent(m_dlgVideo.m_lCurChID, m_nMTC);
		}
	}else{
		m_dlgVideo.m_tvsLive.StopStreamDataEvent(m_dlgVideo.m_lCurChID, m_nMTC);

		if (m_pDataStreamFile)
		{
			fclose(m_pDataStreamFile);
			m_pDataStreamFile = NULL;
		}
	}


	is_streamed = m_dlgVideo.m_tvsLive.GetChannelState(m_dlgVideo.m_lCurChID) & TN_CS_STREAMED;

	GetDlgItem(IDC_RADIO_ON_DATASTREAM_ON)->EnableWindow(!is_streamed);
	GetDlgItem(IDC_RADIO_ON_DATASTREAM_OFF)->EnableWindow(!is_streamed);
	GetDlgItem(IDC_CHECK_FILEW)->EnableWindow(!is_streamed);
	m_dataStreamType.EnableWindow(!is_streamed);
	if(is_streamed){
		GetDlgItem(IDC_BUTTON_SWRITE)->SetWindowText(_T("Stop"));
	}else{
		GetDlgItem(IDC_BUTTON_SWRITE)->SetWindowText(_T("Start"));
	}

}


void CBasicDlg::OnBtnDecStart() 
{
	m_dlgDecode.m_nDecFrmIdx = 0;

	if(m_dlgDecode.IsStarted())
		m_dlgDecode.StopDecode();
	else
		m_dlgDecode.StartDecode();
}

void CBasicDlg::OnSelchangeComboOutformat() 
{
	if(m_dlgDecode.IsStarted()){

		long eFormat = 0;
		int sel = m_cbOutputFormat.GetCurSel();
		switch(sel){
		case 1:
			eFormat = TN_MTC_RAW_RGB888;
			break;
		case 2:
			eFormat = TN_MTC_RAW_RGB32;
			break;
		case 3:
			eFormat = TN_MTC_RAW_YUV422;
			break;
		}
		m_dlgDecode.m_tvsdecode.SetOutputFormat(m_dlgDecode.m_lChID, eFormat);
	}
	
}

void CBasicDlg::OnCheckFilew() 
{
	
}

void CBasicDlg::OnBtnGetframe() 
{
	m_dlgVideo.GetFrame();
}

#include "MyFunc.h"

void CBasicDlg::OnButtonPlaywave() 
{
#if 0
    CString sBtnText;
    GetDlgItemText(IDC_BUTTON_PLAYWAVE, sBtnText);

    if (sBtnText.Compare(_T("Play Wave")) == 0)
    {
        // start playing
        CFileDialog dlg(TRUE, _T("wav"), NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, _T("Wave Files (*.wav)|*.wav|All Files (*.*)|*.*||"));

        if (dlg.DoModal() != IDOK)
        {
            return;
        }

        GetDlgItem(IDC_BUTTON_PLAYWAVE)->SetWindowText(_T("Stop Playing"));

        m_dlgVideo.m_tvsLive.PlayWaveToServer(m_dlgVideo.m_lCurChID, dlg.m_ofn.lpstrFile);
    }
    else
    {
        // stop playing
        m_dlgVideo.m_tvsLive.StopWaveToServer(m_dlgVideo.m_lCurChID);

        GetDlgItem(IDC_BUTTON_PLAYWAVE)->SetWindowText(_T("Play Wave"));
    }
#else
	CString sBtnText;
	GetDlgItemText(IDC_BUTTON_PLAYWAVE, sBtnText);

	if (sBtnText.Compare(_T("Play Wave")) == 0)
	{
		// start playing
		//CFileDialog dlg(TRUE, _T("wav"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Wave Files (*.wav)|*.wav|All Files (*.*)|*.*||"));

		//if (dlg.DoModal() != IDOK)
		//{
		//	return;
		//}

		GetDlgItem(IDC_BUTTON_PLAYWAVE)->SetWindowText(_T("Stop Playing"));


		//오디오파일명읽어오기
		CString strText;
		strText.Format(_T("ch%02d"), m_nCh);
	
		CString str = GetProgramDir();
		//상위경로로 이동 ../
		str = str.Left(str.ReverseFind(_T('\\')));
		str = str.Left(str.ReverseFind(_T('\\')) + 1);
		CString strFile = str + "AudioFile.ini";
		
		CString strAudioFilePath;
		GPPS(strText, _T("fileName"), strAudioFilePath, strFile);

		m_dlgVideo.m_tvsLive.PlayWaveToServer(m_dlgVideo.m_lCurChID, strAudioFilePath);
	}
	else
	{
		// stop playing
		m_dlgVideo.m_tvsLive.StopWaveToServer(m_dlgVideo.m_lCurChID);

		GetDlgItem(IDC_BUTTON_PLAYWAVE)->SetWindowText(_T("Play Wave"));
	}
#endif
}

void CBasicDlg::OnRadioAsbuffer() 
{
	GetDlgItem(IDC_EDIT_RESOL_X)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_RESOL_Y)->EnableWindow(TRUE);
}

void CBasicDlg::OnRadioAsfile() 
{
	GetDlgItem(IDC_EDIT_RESOL_X)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_RESOL_Y)->EnableWindow(FALSE);
}

void CBasicDlg::OnButtonGetPosition() 
{
	long pan, tilt, zoom, focus;

	m_dlgVideo.m_tvsLive.GetPTZPosition(m_dlgVideo.m_lCurChID, &pan, &tilt, &zoom, &focus);

	CString tmp_str, output_str;
	tmp_str.Format(_T("%d"), pan);
	output_str = _T("PAN : ") + tmp_str;
	tmp_str.Format(_T("%d"), tilt);
	output_str += _T(" / TILT : ") + tmp_str;
	tmp_str.Format(_T("%d"), zoom);
	output_str += _T(" / ZOOM : ") + tmp_str;
	tmp_str.Format(_T("%d"), focus);
	output_str += _T(" / FOCUS : ") + tmp_str;

	AddToLog(output_str);
}

void CBasicDlg::OnSelchangeComboDeinter() 
{
	int isel = m_DeinterType.GetCurSel();
	
	if(isel>=0)
		m_dlgVideo.m_tvsLive.put_DecodingOption(1, m_DeinterType.GetItemData(isel));

	long val = 0;
	m_dlgVideo.m_tvsLive.get_DecodingOption(1, &val);
}

void CBasicDlg::OnButtonAvApply() 
{
	// TODO: Add your control notification handler code here

	CComVariant var;
	var.vt = VT_BOOL;
	var.boolVal = GetDlgItem(IDC_CHECK_AVENABLE)->SendMessage(BM_GETCHECK, 0, 0) ? VARIANT_TRUE:VARIANT_FALSE;
	m_dlgVideo.m_tvsLive.SetLocalConfig(TN_LCI_AVSYNC_ENABLE, var);

	var.vt = VT_I4;
	TCHAR tc[32];
	::GetWindowText(GetDlgItem(IDC_EDIT_AVR)->m_hWnd, tc, 12);
	var.lVal = _ttoi(tc);
	m_dlgVideo.m_tvsLive.SetLocalConfig(TN_LCI_AVSYNC_RESYNC, var);
		
	::GetWindowText(GetDlgItem(IDC_EDIT_AVA)->m_hWnd, tc, 12);
	var.lVal = _ttoi(tc);
	m_dlgVideo.m_tvsLive.SetLocalConfig(TN_LCI_ABUFFER, var);
}


void CBasicDlg::OnServerResolutionGet() 
{
	// TODO: Add your control notification handler code here
	CComPtr<ITVSLiveControl> ptr;

	BYTE Resolution = 0;
	int size = sizeof(Resolution);
	stConfig sConf[1]={0};
	CComVariant vars;
	CString str;

	m_dlgVideo.m_tvsLive.GetControlUnknown()->QueryInterface(IID_ITVSLiveControl, (void **)&ptr);
	if(ptr)
	{
		//for Resolution
	    sConf[0].nItem = 0x0202;  //Defined in "Configuration Parameters" document
		sConf[0].cbSize = size;
		sConf[0].pbData = (BYTE *)&Resolution;

		int items = 1;
		VARIANT_BOOL b;
		ptr->GetServerConfig(m_dlgVideo.m_lCurChID, items, sConf, &b); 

		if(b)
		{
			int nCnt = sizeof(gResolution)/sizeof(gResolution[0]);
			for(int i=0; i<nCnt; i++)
			{
				if((int)Resolution == gResolution[i].nValue)
				{
					int nComboCnt = m_Resolution.GetCount();
					for(int j=0; i<nComboCnt; j++)
					{
						CString szText;
						m_Resolution.GetLBText(j, szText);
						if(!_tcscmp(szText, gResolution[i].szResolution))
						{
							m_Resolution.SetCurSel(j);
							break;
						}
					}
					break;
				}
			}

			m_dlgVideo.m_tvsDisplay.RemoveOsdArea(m_dlgVideo.m_lOsdID2);
			m_Resolution.GetWindowText(str);
			vars = str;
			m_dlgVideo.m_lOsdID2 = m_dlgVideo.m_tvsDisplay.AddOsdArea(m_dlgVideo.m_lCurChID, 10, 50, 250, 100, 0);
			m_dlgVideo.m_tvsDisplay.SetOsdFontSize(m_dlgVideo.m_lOsdID, 14);
			m_dlgVideo.m_tvsDisplay.UpdateOsdArea(m_dlgVideo.m_lOsdID2, vars);
		}
	
	}
}

void CBasicDlg::OnServerResolutionSet() 
{
	// TODO: Add your control notification handler code here
	CComPtr<ITVSLiveControl> ptr;
	m_dlgVideo.m_tvsLive.GetControlUnknown()->QueryInterface(IID_ITVSLiveControl, (void **)&ptr);
	if(ptr){
		BYTE Resolution = 0;

		Resolution = m_Resolution.GetCurSel();
		int size = sizeof(Resolution);
		stConfig sConf[1]={0};

		//for Resolution
	    sConf[0].nItem = 0x0202;  //Defined in "Configuration Parameters" document
		sConf[0].cbSize = size;
		sConf[0].pbData = (BYTE *)&Resolution;

		VARIANT_BOOL b;
	    ptr->SetServerConfig(m_dlgVideo.m_lCurChID, 1, sConf, &b);
		OnServerResolutionGet(); 
	}
}

void CBasicDlg::OnServerBitrateGet() 
{
	// TODO: Add your control notification handler code here
	CComPtr<ITVSLiveControl> ptr;

	unsigned short Bitrate = 0;
	int size = sizeof(Bitrate);
	stConfig sConf[1]={0};
	CComVariant vars;
	CString str;

	m_dlgVideo.m_tvsLive.GetControlUnknown()->QueryInterface(IID_ITVSLiveControl, (void **)&ptr);
	if(ptr)
	{
		//for Bitrate
	    sConf[0].nItem = 0x0205;  //Defined in "Configuration Parameters" document
		sConf[0].cbSize = size;
		sConf[0].pbData = (BYTE *)&Bitrate;

		int items = 1;
		VARIANT_BOOL b;
		ptr->GetServerConfig(m_dlgVideo.m_lCurChID, items, sConf, &b); 

		if(b)
		{
			str.Format(_T("%d"), Bitrate);
			m_Bitrate.SetWindowText(str);
		}
	
	}
}

void CBasicDlg::OnServerBitrateSet() 
{
	// TODO: Add your control notification handler code here
		CComPtr<ITVSLiveControl> ptr;

	unsigned short Bitrate = 0;
	int size = sizeof(Bitrate);
	stConfig sConf[1]={0};
	CComVariant vars;
	CString str;

	m_dlgVideo.m_tvsLive.GetControlUnknown()->QueryInterface(IID_ITVSLiveControl, (void **)&ptr);
	if(ptr)
	{
		//for Bitrate
		m_Bitrate.GetWindowText(str);
		Bitrate = _ttoi(str);
	    sConf[0].nItem = 0x0205;  //Defined in "Configuration Parameters" document
		sConf[0].cbSize = size;
		sConf[0].pbData = (BYTE *)&Bitrate;

		int items = 1;
		VARIANT_BOOL b;

		ptr->SetServerConfig(m_dlgVideo.m_lCurChID, items, sConf, &b); 

		if(b)
		{
			OnServerBitrateGet() ;
		}
	
	}
}
LRESULT CBasicDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// 메시지 수신
	if (message == this->message && (HWND)wParam != this->GetSafeHwnd())
	{
		CString str;
		str.Format(_T("%d"), lParam);
		//MessageBox(str);

		if (m_nCh == (int)lParam)
		{
			OnButtonPlaywave();
			//UpdateStatusBar();
		}
	}

	return CDialog::WindowProc(message, wParam, lParam);
}