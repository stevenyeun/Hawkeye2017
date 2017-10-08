// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MainFrm.h"
#include "PictureShow.h"

#include "PictureShowDoc.h"
#include "PictureShowView.h"

#include "CommonMFCFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_OPTIONS_FULLSCREEN, OnOptionsFullscreen)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_BUTTON_FULLSCREEN, OnButtonFullscreen)
	ON_COMMAND(ID_BUTTON_FULLSCREEN_FLOAT, OnButtonFullscreenFloat)
	//}}AFX_MSG_MAP

	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_COPYDATA()
	ON_WM_TIMER()
	ON_WM_MOVING()
	ON_WM_MOVE()
	ON_WM_CHANGEUISTATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
//	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_INFO,
//	ID_INDICATOR_NUM,
//	ID_INDICATOR_CAPS,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

//-----------------------------------------------------------------------------
CMainFrame::CMainFrame()
//=============================================================================
{
	m_FullScreen = FALSE;
}

//-----------------------------------------------------------------------------
CMainFrame::~CMainFrame()
//=============================================================================
{
}

//-----------------------------------------------------------------------------
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
//=============================================================================
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1) return -1;

	if (!m_WndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		//!m_WndToolBar.LoadToolBar(IDR_MAINFRAME))
		!m_WndToolBar.LoadToolBar(IDR_MAINFRAME_EDITED))
		{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
		}

	if (!m_WndStatusBar.Create(this) ||
		!m_WndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
		{
		TRACE0("Failed to create status bar\n"); 
		return -1;      // fail to create
		}
	m_WndStatusBar.SetPaneInfo( 0, ID_INDICATOR_INFO, SBPS_NORMAL | SBPS_STRETCH, 100 );

	// Delete these three lines if you don't want the toolbar to be dockable
	m_WndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_WndToolBar);
	
	
	//yeun 140116
	::SetWindowPos(m_hWnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_HIDEWINDOW);

	//SetTimer(1, 500, NULL);
	//SetTimer(2, 500, NULL);
	//SetTimer(2, 1000, NULL);
	
	//CCommonMFCFunc::HideIconFromTaskbar();

	return 0;
}

//-----------------------------------------------------------------------------
// This Has To Be Improved - Guess I Just Had No Time To Do It The Right Way...
//-----------------------------------------------------------------------------
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
//=============================================================================
{
	cs.style = WS_POPUP;//캡션바 없애기
	
	int DesktopWidth  = GetSystemMetrics(SM_CXSCREEN);
	int DesktopHeight = GetSystemMetrics(SM_CYSCREEN);

	// Just Make It Small So We Will Not Feel a "Blink"
	CRect MainWindow_Rect(0,0, 100, 100); // First Opening Screen

	cs.x = (DesktopWidth - MainWindow_Rect.right)/2;
	cs.y = (DesktopHeight - MainWindow_Rect.bottom)/2;

    cs.cx = MainWindow_Rect.right;
	cs.cy = MainWindow_Rect.bottom;


	//  [3/28/2014 Yeun]
	if(cs.hMenu!=NULL)
	{
		::DestroyMenu(cs.hMenu);      // delete menu if loaded
		cs.hMenu = NULL;              // no menu for this window
	}	




	// Create invisible window and set it a parent
	//작업표시줄과 Alt Tab 리스트에서 없애기
	if (!::IsWindow(m_wndInvisible.m_hWnd))
	{
		LPCTSTR pstrOwnerClass = AfxRegisterWndClass(0);
		if (!m_wndInvisible.CreateEx(WS_EX_TOOLWINDOW, pstrOwnerClass, _T(""), WS_POPUP,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			NULL, 0))
			return FALSE;
	}
	cs.hwndParent = m_wndInvisible.m_hWnd;
	// Other settings
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;


	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
//-----------------------------------------------------------------------------
void CMainFrame::AssertValid() const
//=============================================================================
{
	CFrameWnd::AssertValid();
}

//-----------------------------------------------------------------------------
void CMainFrame::Dump(CDumpContext& dc) const
//=============================================================================
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

//-----------------------------------------------------------------------------
//
// (This Function Is Based On The Article On Microsoft)
// "Adding a Full Screen Feature to an MFC Application (Q164162)"
//
//-----------------------------------------------------------------------------
void CMainFrame::OnOptionsFullscreen()
//=============================================================================
{
	RECT DesktopRect;
    WINDOWPLACEMENT WPNew;

	m_FullScreen = m_FullScreen ? TRUE : FALSE;

    if(!m_FullScreen)
	    {
        // need to hide all status bars
        m_WndStatusBar.ShowWindow(SW_HIDE);
	    m_WndToolBar.ShowWindow(SW_HIDE);

	    // We'll need these to restore the original state.
	    GetWindowPlacement (&m_WPPrev);

	    m_WPPrev.length = sizeof m_WPPrev;

        //Adjust RECT to new size of window
	    ::GetWindowRect(::GetDesktopWindow(), &DesktopRect);

		DesktopRect.left -= 1;
		DesktopRect.top -= 1;
		DesktopRect.bottom += 2;
		DesktopRect.right += 2;

	    ::AdjustWindowRectEx(&DesktopRect, GetStyle(), TRUE, GetExStyle());

	    // Remember this for OnGetMinMaxInfo()
	    m_FullScreenWindowRect = DesktopRect;
        
        WPNew = m_WPPrev;
        WPNew.showCmd =  SW_SHOWNORMAL;
	    WPNew.rcNormalPosition = DesktopRect;
	    
        m_pWndFullScreenBar=new CToolBar;

        if(!m_pWndFullScreenBar->Create(this,CBRS_SIZE_DYNAMIC|CBRS_FLOATING) ||
	       !m_pWndFullScreenBar->LoadToolBar(IDR_FULLSCREEN))
    		{
	    	TRACE0("Failed to create toolbar\n");
			return; // fail to create
	        }
        
        //don't allow the toolbar to dock
        m_pWndFullScreenBar->EnableDocking(0);
		m_pWndFullScreenBar->SetWindowPos(0, 0,0, 0,0,SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE|SWP_SHOWWINDOW);
		m_pWndFullScreenBar->SetWindowText(_T("Hold Ctrl+F to switch between normal and a full screen"));
		FloatControlBar(m_pWndFullScreenBar, CPoint(0,0));
		m_pWndFullScreenBar->EnableToolTips(TRUE);
		m_FullScreen=TRUE;
	    }
    else
	    {
        m_pWndFullScreenBar->DestroyWindow();
		delete m_pWndFullScreenBar;

        m_FullScreen=FALSE;

        m_WndStatusBar.ShowWindow(SW_SHOWNORMAL);
	    m_WndToolBar.ShowWindow(SW_SHOWNORMAL);
        WPNew = m_WPPrev;
	    }
    
    SetWindowPlacement(&WPNew);
}

//-----------------------------------------------------------------------------
void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
//=============================================================================
{
	if(m_FullScreen)
	    {
	    lpMMI->ptMaxSize.y = m_FullScreenWindowRect.Height();
	    lpMMI->ptMaxTrackSize.y = lpMMI->ptMaxSize.y;
	    lpMMI->ptMaxSize.x = m_FullScreenWindowRect.Width();
	    lpMMI->ptMaxTrackSize.x = lpMMI->ptMaxSize.x;
	    }
	else//  [3/28/2014 Yeun]
	{
		/*
		CPictureShowView * pView  = ((CPictureShowView*)GetActiveView());
				if( pView != NULL )
				{
					CRect rc;
					pView->m_dlgStatusCoord.GetClientRect(rc);
		
					lpMMI->ptMinTrackSize.x=rc.Width()+50;
					lpMMI->ptMinTrackSize.y=rc.Height()*3;
				}
				*/
		
		

/*
		lpMMI->ptMaxPosition.x=100;
		lpMMI->ptMaxPosition.y=100;*/


		//최대 사이즈 제한
/*
		lpMMI->ptMinTrackSize.x=200;
		lpMMI->ptMinTrackSize.y=200;

		lpMMI->ptMaxTrackSize.x=300;
		lpMMI->ptMaxTrackSize.y=300;*/

		
	}

// CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

//-----------------------------------------------------------------------------
void CMainFrame::OnButtonFullscreen() 
//=============================================================================
{
	OnOptionsFullscreen();
}

//-----------------------------------------------------------------------------
void CMainFrame::OnButtonFullscreenFloat() 
//=============================================================================
{
	OnOptionsFullscreen();
}



void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	//MoveDlgStatusCoord();

}

void CMainFrame::OnSizing(UINT fwSide, LPRECT pRect)
{
	CFrameWnd::OnSizing(fwSide, pRect);

	// TODO: Add your message handler code here
}

BOOL CMainFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: Add your message handler code here and/or call default

	int iLen = pCopyDataStruct->cbData;

	switch (pCopyDataStruct->dwData)
	{
	case TO_IPC_HWAKEEYEGIS_CAMINFO:
		{
			if(iLen == sizeof(IPC_CAMINFO))
			{
				IPC_CAMINFO caminfo = *(IPC_CAMINFO*)pCopyDataStruct->lpData;
				((CPictureShowView*)GetActiveView())->SetCamInfo(caminfo);
			}
		}
		break;
	case TO_IPC_HWAKEEYEGIS_TARGETINFO:
		{
			IPC_COORDINFO coordinfo = *(IPC_COORDINFO*)pCopyDataStruct->lpData;
			((CPictureShowView*)GetActiveView())->SetTargetInfo(coordinfo);
		}
		break;
	default:
		break;
	}

	return CFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	switch (nIDEvent)
	{
	case 1:
		{		
#if 1
			IPC_CAMINFO caminfo;
			caminfo.coordinfo.byLatSign		= NORTH_BYTE;
			caminfo.coordinfo.byLatDeg		= 37;
			caminfo.coordinfo.byLatMin		= 36;
			caminfo.coordinfo.byLatSec		= 18;
			caminfo.coordinfo.byLatSecFrac	= 33;

			caminfo.coordinfo.byLongSign	= WEST_BYTE;
			caminfo.coordinfo.byLongDeg		= 127;
			caminfo.coordinfo.byLongMin		= 2;	
			caminfo.coordinfo.byLongSec		= 11;	
			caminfo.coordinfo.byLongSecFrac	= 99;

			static int iFlag=0;
			if(iFlag==0)
			{
				iFlag=1;

				

				caminfo.fPan					= (float)20.30;
				caminfo.fFovW					= 30;
				caminfo.uSuvailRange				= 1520;		
			}
			else if(iFlag==1)
			{
				iFlag=2;

			

				caminfo.fPan					= (float)30.00;
				caminfo.fFovW					= 30;
				caminfo.uSuvailRange				= 1600;
			}
			else if(iFlag==2)
			{
				iFlag=3;

			

				caminfo.fPan					= (float)40.00;
				caminfo.fFovW					= 30;
				caminfo.uSuvailRange				= 1600;
			}
			else if(iFlag==3)
			{
				iFlag=4;


				caminfo.fPan					= (float)50.00;
				caminfo.fFovW					= 30;
				caminfo.uSuvailRange				= 1600;
			}
			else if(iFlag==4)
			{
				iFlag=5;

				

				caminfo.fPan					= (float)40.00;
				caminfo.fFovW					= 30;
				caminfo.uSuvailRange				= 1600;
			}
			else if(iFlag==5)
			{
				iFlag=1;

				

				caminfo.fPan					= (float)30.00;
				caminfo.fFovW					= 30;
				caminfo.uSuvailRange				= 1300;
			}

			((CPictureShowView*)GetActiveView())->SetCamInfo(caminfo, 1);		


		/*
				CString strWinName = _T("U2SR - HWAKEYE_GIS");
						CWnd*	pOtherWnd = NULL;
						pOtherWnd = CWnd::FindWindow( NULL, strWinName );
			
						if(pOtherWnd != NULL)
						{
							COPYDATASTRUCT cpd;
							LRESULT copyDataResult;
							cpd.dwData = TO_IPC_HWAKEEYEGIS_CAMINFO;//명령어 타입 저장
			
							cpd.cbData = sizeof(caminfo);
							cpd.lpData = (PVOID)&caminfo;
							PDWORD_PTR lpdwResult=NULL;
							copyDataResult = SendMessageTimeout(pOtherWnd->m_hWnd, WM_COPYDATA,
								(WPARAM)AfxGetApp()->m_pMainWnd->GetSafeHwnd(), (LPARAM)&cpd,
								SMTO_NORMAL, 1000, lpdwResult
								);
						}*/
			
#endif
		}
		break;
			case 2:
			{
#if 1
				IPC_CAMINFO caminfo;
				caminfo.coordinfo.byLatSign = NORTH_BYTE;
				caminfo.coordinfo.byLatDeg = 37;
				caminfo.coordinfo.byLatMin = 36;
				caminfo.coordinfo.byLatSec = 10;
				caminfo.coordinfo.byLatSecFrac = 33;

				caminfo.coordinfo.byLongSign = WEST_BYTE;
				caminfo.coordinfo.byLongDeg = 127;
				caminfo.coordinfo.byLongMin = 2;
				caminfo.coordinfo.byLongSec = 18;
				caminfo.coordinfo.byLongSecFrac = 99;

				static int iFlag = 0;
				if (iFlag == 0)
				{
					iFlag = 1;



					caminfo.fPan = (float)20.30;
					caminfo.fFovW = 30;
					caminfo.uSuvailRange = 1520;
				}
				else if (iFlag == 1)
				{
					iFlag = 2;



					caminfo.fPan = (float)30.00;
					caminfo.fFovW = 30;
					caminfo.uSuvailRange = 1600;
				}
				else if (iFlag == 2)
				{
					iFlag = 3;



					caminfo.fPan = (float)40.00;
					caminfo.fFovW = 30;
					caminfo.uSuvailRange = 1600;
				}
				else if (iFlag == 3)
				{
					iFlag = 4;


					caminfo.fPan = (float)50.00;
					caminfo.fFovW = 30;
					caminfo.uSuvailRange = 1600;
				}
				else if (iFlag == 4)
				{
					iFlag = 5;



					caminfo.fPan = (float)40.00;
					caminfo.fFovW = 30;
					caminfo.uSuvailRange = 1600;
				}
				else if (iFlag == 5)
				{
					iFlag = 1;



					caminfo.fPan = (float)30.00;
					caminfo.fFovW = 30;
					caminfo.uSuvailRange = 1300;
				}

				((CPictureShowView*)GetActiveView())->SetCamInfo(caminfo, 2);



#endif
			}
			break;
	case 3:
		{
			IPC_COORDINFO coordinfo;

			static int iFlag=0;
			if(iFlag==0)
			{
				iFlag=1;			

				coordinfo.byLatSign		= NORTH_BYTE;
				coordinfo.byLatDeg		= 36;
				coordinfo.byLatMin		= 19;
				coordinfo.byLatSec		= 16;
				coordinfo.byLatSecFrac	= 05;

				coordinfo.byLongSign	= WEST_BYTE;
				coordinfo.byLongDeg		= 127;
				coordinfo.byLongMin		= 14;	
				coordinfo.byLongSec		= 2;	
				coordinfo.byLongSecFrac	= 62;		
			}
			else if(iFlag==1)
			{
				iFlag=2;
				coordinfo.byLatSign		= NORTH_BYTE;
				coordinfo.byLatDeg		= 36;
				coordinfo.byLatMin		= 19;
				coordinfo.byLatSec		= 10;
				coordinfo.byLatSecFrac	= 31;

				coordinfo.byLongSign	= WEST_BYTE;
				coordinfo.byLongDeg		= 127;
				coordinfo.byLongMin		= 14;	
				coordinfo.byLongSec		= 8;	
				coordinfo.byLongSecFrac	= 44;		
			}
			else if(iFlag==2)
			{
				iFlag=0;
				coordinfo.byLatSign		= NORTH_BYTE;
				coordinfo.byLatDeg		= 36;
				coordinfo.byLatMin		= 19;
				coordinfo.byLatSec		= 04;
				coordinfo.byLatSecFrac	= 96;

				coordinfo.byLongSign	= WEST_BYTE;
				coordinfo.byLongDeg		= 127;
				coordinfo.byLongMin		= 14;	
				coordinfo.byLongSec		= 12;	
				coordinfo.byLongSecFrac	= 53;		
			}


			CString strWinName = _T("U2SR - HWAKEYE_GIS");
			CWnd*	pOtherWnd = NULL;
			pOtherWnd = CWnd::FindWindow( NULL, strWinName );

			if(pOtherWnd != NULL)
			{
				COPYDATASTRUCT cpd;
				LRESULT copyDataResult;
				cpd.dwData = TO_IPC_HWAKEEYEGIS_TARGETINFO;//명령어 타입 저장

				cpd.cbData = sizeof(coordinfo);
				cpd.lpData = (PVOID)&coordinfo;
				PDWORD_PTR lpdwResult=NULL;
				copyDataResult = SendMessageTimeout(pOtherWnd->m_hWnd, WM_COPYDATA,
					(WPARAM)AfxGetApp()->m_pMainWnd->GetSafeHwnd(), (LPARAM)&cpd,
					SMTO_NORMAL, 1000, lpdwResult
					);
			}

		}
		break;
	default:
		break;
	}

	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnMoving(UINT fwSide, LPRECT pRect)
{
	CFrameWnd::OnMoving(fwSide, pRect);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	//CPictureShowView * pView = ((CPictureShowView*)GetActiveView());
	//GetActiveView()->SendMessage(WM_MOVING, 0, 0);	
	//MoveDlgStatusCoord();
}
void CMainFrame::MoveDlgStatusCoord()
{
	CPictureShowView * pView = ((CPictureShowView*)GetActiveView());
	
	if( pView != NULL )
	{
		
		if(pView->m_dlgStatusCoord.m_hWnd != NULL)
		{
			//int iSizeX = 380;
			//int iSizeY = 250;			
			CRect rcToolbar;
			CRect rcFrame;
			CRect rcView;
			CRect rcDlgStatus;
			

			m_WndToolBar.GetWindowRect( rcToolbar );
			ScreenToClient( rcToolbar );
			GetWindowRect( rcFrame );
			pView->GetWindowRect( rcView );			
		
			//프로그램 윈도우 크기가 상태창을 보여 주지 못 할 만큼 작아지면 숨긴다.
		
			if( pView->m_dlgStatusCoord.m_bChkTopDocking )
			{
				if( rcToolbar.top == 0)//상단에 붙어 있으면
				{
					m_WndToolBar.GetWindowRect( rcToolbar );

					/*
					CRect rcDlg;
					pView->m_dlgStatusCoord.GetClientRect(rcDlg);*/			

					CRect rc;
					rc.left = rcView.left;
					rc.top = rcToolbar.bottom-2;

					BOOL bHor, bVer;
					pView->CheckScrollBars( bHor, bVer ); 
					
					if( bVer )
						rc.right = rcView.right-19;
					else
						rc.right = rcView.right-2;

					rc.bottom = rc.top + 132;
					//rc.bottom = rc.top + 105;//yeun140419
					//rc.bottom = rc.top + 200;//윈도우 세로 크기 제어

					pView->m_dlgStatusCoord.MoveWindow( rc );

					//pView->m_dlgStatusCoord.ShowWindow(SW_SHOW);

				}
				else
				{
					CRect rc;
					rc.left  = rcView.left;
					rc.top   = rcView.top;
					rc.right = rcView.right-19;
					rc.bottom = rc.top + 105;

					pView->m_dlgStatusCoord.MoveWindow( rc );

					//pView->m_dlgStatusCoord.ShowWindow(SW_SHOW);
				}

				int iWidth = pView->m_dlgStatusCoord.GetDefaultDlgSize().Width();
				if( rcFrame.Width() < iWidth ){
					pView->m_dlgStatusCoord.ShowWindow(SW_HIDE);
				}
				else
					pView->m_dlgStatusCoord.ShowWindow(SW_SHOW);

			}			
		}	
	}
	
}

void CMainFrame::UpdateDlgStatus()
{
	//CPictureShowView * pView = ((CPictureShowView*)GetActiveView());
	//pView->SetCamInfo()
}

void CMainFrame::OnMove(int x, int y)
{
	CFrameWnd::OnMove(x, y);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	MoveDlgStatusCoord();
}

void CMainFrame::OnChangeUIState(UINT nAction, UINT nUIElement)
{
	// 이 기능을 사용하려면 Windows 2000 이상이 필요합니다.
	// _WIN32_WINNT 및 WINVER 기호는 0x0500보다 크거나 같아야 합니다.
	CFrameWnd::OnChangeUIState(nAction, nUIElement);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
