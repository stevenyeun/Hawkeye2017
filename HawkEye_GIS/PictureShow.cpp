// PictureShow.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PictureShow.h"

#include "MainFrm.h"
#include "PictureShowDoc.h"
#include "PictureShowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//yeun
CGdiPlusStarter g_gps;

/////////////////////////////////////////////////////////////////////////////
// CPictureShowApp

BEGIN_MESSAGE_MAP(CPictureShowApp, CWinApp)
	//{{AFX_MSG_MAP(CPictureShowApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPictureShowApp construction

//-----------------------------------------------------------------------------
CPictureShowApp::CPictureShowApp()
//=============================================================================
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPictureShowApp object

CPictureShowApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPictureShowApp initialization

//-----------------------------------------------------------------------------
BOOL CPictureShowApp::InitInstance()
//=============================================================================
{
	HANDLE hMutex = ::CreateMutex(NULL, TRUE, _T("HAWKEYE_GIS"));

	if (::GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hMutex);
		AfxMessageBox(_T("이미 실행중입니다"));
		return FALSE;
	}

	if (!AfxSocketInit())
	{
		AfxMessageBox("AfxSocketInit() Error");
		return FALSE;
	}

	/*
	CFileFind find;
	BOOL bFind = find.FindFile("C:\\Windows\\System32\\oasistech.dll");
	if(!bFind)
	{
		int iErr = GetLastError();
		AfxMessageBox(_T("no license"));
		return FALSE;
	}
	*/

	if (g_gps.m_bSuccess == FALSE) {
		MessageBox(NULL,TEXT("GDI+ 라이브러리를 초기화할 수 없습니다."),
			TEXT("알림"),MB_OK);
		return 0;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("PictureShow"));

	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPictureShowDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CPictureShowView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	// If Not Parsed cmdInfo Will Not Get Values And Will Not Open cmdInfo.m_strFileName
	// ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if(!ProcessShellCommand(cmdInfo)) return FALSE;
	// AfxMessageBox(this->m_lpCmdLine);
	// AfxMessageBox(cmdInfo.m_strFileName);

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();		
	return TRUE;
}


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

//-----------------------------------------------------------------------------
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
//=============================================================================
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

//-----------------------------------------------------------------------------
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
//=============================================================================
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
//-----------------------------------------------------------------------------
void CPictureShowApp::OnAppAbout()
//=============================================================================
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CPictureShowApp message handlers
