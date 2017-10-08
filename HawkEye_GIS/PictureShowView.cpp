// PictureShowView.cpp : implementation of the CPictureShowView class
//

#include "stdafx.h"
#include "MainFrm.h"
#include "PictureShow.h"
#include "PictureShowDoc.h"
#include "PictureShowView.h"

//yeun
#include "./SourceLIB/CoordConversion/mgrs.h"
#include "./SourceLIB/CoordConversion/utm.h"
#include "./SourceLIB/ShareUtil/QTRegistry.h"

//yeun 140116
#include "OptMapInfo.h"
//
//  [3/27/2014 Yeun]
#include "OptCommonInfo.h"

//  [3/30/2014 Yeun]
#include "SourceLIB/CoordApp/CoordApp.h"

//Steven 170404
#include "ErrorDefine.h"

// ChildSocket -> XXXXWindow
//패킷을 받을 이벤트 정의
extern UINT UWM_AUTHORITY_CLIENT_SOCKET_PACKET_TO_WINDOW_MSG;
extern UINT UWM_AUTHORITY_CLIENT_SOCKET_EVENT_TO_WINDOW_MSG;

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

CQTRegistry g_QTRegistry;
CString g_strKey = _T("Software\\U2SR\\HAWKEYE_GIS");
// MGRS
#define PI 3.141592653589793f
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPictureShowView

IMPLEMENT_DYNCREATE(CPictureShowView, CScrollView)

BEGIN_MESSAGE_MAP(CPictureShowView, CScrollView)
//{{AFX_MSG_MAP(CPictureShowView)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_OPTIONS_FITTOSCREEN, OnOptionsFittoscreen)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FITTOSCREEN, OnUpdateOptionsFittoscreen)
	ON_COMMAND(ID_BUTTON_MAGNIFY, OnButtonMagnify)
	ON_COMMAND(ID_BUTTON_DIMINISH, OnButtonDiminish)
	ON_COMMAND(ID_OPTIONS_ASSOCIATEFILEEXTENTIONS, OnOptionsAssociatefileextentions)
	ON_COMMAND(ID_BUTTON_FITTOSCREEN, OnButtonFittoscreen)
	ON_COMMAND(ID_BUTTON_PREV, OnButtonPrev)
	ON_COMMAND(ID_BUTTON_NEXT, OnButtonNext)

	//yeun 
/*
	ON_COMMAND(ID_BUTTON_MAP1, OnButtonMap1)
	ON_COMMAND(ID_BUTTON_MAP2, OnButtonMap2)*///  [3/28/2014 Yeun]

	//yeun 20140116
	ON_COMMAND(ID_BUTTON_MAP_OPEN, OnButtonMapOpen)
	ON_COMMAND(ID_BUTTON_PEN, OnButtonPen) //  [3/28/2014 Yeun]
	ON_COMMAND(ID_BUTTON_DRAWING_LOAD, OnButtonDrawingLoad)
	ON_COMMAND(ID_BUTTON_STYLE_SETUP, OnButtonStyleSetup)
	ON_COMMAND(ID_BUTTON_NEW_DRAWING, OnButtonNewDrawing)

	//  [4/14/2014 Yeun]
	ON_COMMAND(ID_HIDDEN_MENU, OnButtonHiddenMenu)
	//
	ON_UPDATE_COMMAND_UI(ID_BUTTON_NEXT, OnUpdateButtonNext)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_PREV, OnUpdateButtonPrev)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_HELP_HOMEPAGE, OnHelpHomepage)
	ON_COMMAND(ID_OPTIONS_FITBORDERSTOPICTURE, OnOptionsFitborderstopicture)
	ON_COMMAND(ID_OPTIONS_NEXTPICTURE, OnOptionsNextpicture)
	ON_COMMAND(ID_OPTIONS_PREVIOUSPICTURE, OnOptionsPreviouspicture)


	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)

	// Support The New Status Indicator (Must Be Outside The ASX Message MAP...)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_INFO, OnIndicatorInfo)

	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_MOUSEMOVE()
//	ON_WM_COPYDATA()
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_MOVE()
	ON_WM_MOVING()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_LINE_SAVE, &CPictureShowView::OnLineSave)
	ON_COMMAND(ID_LINE_UNDO, &CPictureShowView::OnLineUndo)
	ON_COMMAND(ID_RULER_SHOW, &CPictureShowView::OnShowRuler)

	ON_REGISTERED_MESSAGE(UWM_AUTHORITY_CLIENT_SOCKET_PACKET_TO_WINDOW_MSG, OnClientSocketPacketMsg)
	ON_REGISTERED_MESSAGE(UWM_AUTHORITY_CLIENT_SOCKET_EVENT_TO_WINDOW_MSG, OnClientSocketEventMsg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPictureShowView construction/destruction

//-----------------------------------------------------------------------------
CPictureShowView::CPictureShowView()
//=============================================================================
{
	//140922 Yeun
	m_bShowRuler = FALSE;

	m_ViewFirst = TRUE; // Until Changed...
	m_FitToScreen = FALSE;
	m_Magnify = 0;
	m_ScrollKeySpeed = 50 * 4;

	//m_byCamOpacity = 128;

	m_iAbsCamPixelX=0;
	m_iAbsCamPixelY=0;
	m_iCurScrCamPixelX=0;
	m_iCurScrCamPixelY=0;


	m_iAbsCamPixelApplyMagX=0;
	m_iAbsCamPixelApplyMagY=0;


	//ZeroMemory(&m_arrTmPtCamDirec, sizeof(DOUBLEPOINT)*POINT_NUM);

	ZeroMemory(&m_OldScrollSizeTotal, sizeof(CSize));


	//  [3/28/2014 Yeun]
	m_bPenMode = FALSE;

	m_hStdCursor	= AfxGetApp()->LoadStandardCursor(IDC_ARROW);  
	m_hPenCursor	= AfxGetApp()->LoadCursor(IDC_CURSOR_PEN);

	m_pFileDrawingInfo = NULL;

	UWM_AUTHORITY_CLIENT_SOCKET_PACKET_TO_WINDOW_MSG = ::RegisterWindowMessage(STR_AUTHORITY_CLIENT_SOCKET_PACKET_TO_WINDOW_MSG);
	UWM_AUTHORITY_CLIENT_SOCKET_EVENT_TO_WINDOW_MSG = ::RegisterWindowMessage(STR_AUTHORITY_CLIENT_SOCKET_EVENT_TO_WINDOW_MSG);

	message = RegisterWindowMessage(_T("Hawkeye_PTZEnvSetup"));
}

//-----------------------------------------------------------------------------
CPictureShowView::~CPictureShowView()
//=============================================================================
{
	CMainFrame* pMFrm = (CMainFrame*)AfxGetMainWnd();
	CRect rc;

	//  [3/30/2014 Administrator]
/*
	pMFrm->GetWindowRect( rc );
	m_optCommonInfo.m_s.iX = rc.left;
	m_optCommonInfo.m_s.iY = rc.top;
	m_optCommonInfo.m_s.iWidth = rc.Width()+1;
	m_optCommonInfo.m_s.iHeight = rc.Height()+1;		
	m_optCommonInfo.Write();*/


	SAFE_DELETE( m_pFileDrawingInfo );
}

//-----------------------------------------------------------------------------
BOOL CPictureShowView::PreCreateWindow(CREATESTRUCT& cs)
//=============================================================================
{
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPictureShowView drawing

//-----------------------------------------------------------------------------
void CPictureShowView::OnDraw(CDC* pDC)
//=============================================================================
{
	CPictureShowDoc* pDoc = GetDocument();
	if(m_ViewFirst)
	{
		//if(m_FileName.IsEmpty()) pDoc->SetTitle("Default"); //yeun disable

		OnOptionsFitborderstopicture();
		OnOptionsFitborderstopicture();
		m_ViewFirst = FALSE;
		Invalidate(TRUE);
	}

	GetClientRect(&m_ClientRect);
	pDoc->m_Picture.UpdateSizeOnDC(pDC); // Get Picture Dimentions In Pixels

	if(m_FitToScreen)
	{
		ASSERT(FALSE);
		pDoc->m_Picture.Show(pDC, CRect(0,0, m_ClientRect.right, m_ClientRect.bottom));
		// Set Off Scrolls
		m_ScrollSizeTotal.cx = 0;
		m_ScrollSizeTotal.cy = 0;
	}
	else	
	{
		// Calculate Delta Width - To Center The Picture
		if(m_ClientRect.right - pDoc->m_Picture.m_Width > 0)
			m_DeltaX = (m_ClientRect.right - pDoc->m_Picture.m_Width)/2;
		else m_DeltaX = 0;
		// Calculate Delta Height - To Center The Picture
		if(m_ClientRect.bottom - pDoc->m_Picture.m_Height > 0)
			m_DeltaY = (m_ClientRect.bottom - pDoc->m_Picture.m_Height)/2;
		else m_DeltaY = 0;

		if(m_DeltaX + pDoc->m_Picture.m_Width*(m_Magnify+1) > m_ClientRect.right)
		{
			m_DeltaX = (m_ClientRect.right - pDoc->m_Picture.m_Width*(m_Magnify+1))/2;
			m_DeltaY = (m_ClientRect.bottom - pDoc->m_Picture.m_Height*(m_Magnify+1))/2;
		}

		if(m_Magnify >= 0) // Magnify Or Set Original Picture Dimentions
		{
			// Calculate New Dimentions For ScrollView

			//yeun
			m_OldCalcedMagnify = m_CalcedMagnify;
			m_CalcedMagnify = (m_Magnify+1)-2;
			//

			m_ScrollSizeTotal.cx = pDoc->m_Picture.m_Width*(m_Magnify+1)-2;
			m_ScrollSizeTotal.cy = pDoc->m_Picture.m_Height*(m_Magnify+1)-2;
			// Center Picture (If We Have Enough Space)
			if(m_ClientRect.right - m_ScrollSizeTotal.cx <= 0) m_DeltaX = 0;
			if(m_ClientRect.bottom - m_ScrollSizeTotal.cy <= 0) m_DeltaY = 0;

			m_ImgScreenBuf.Destroy();
			/*
			CRect rc;
			rc.left		= m_DeltaX;
			rc.right	= pDoc->m_Picture.m_Width;
			rc.top		= m_DeltaY;
			rc.bottom	= pDoc->m_Picture.m_Height; 
			*/
			m_ImgScreenBuf.Create(m_DeltaX+pDoc->m_Picture.m_Width, m_DeltaY+pDoc->m_Picture.m_Height, 24);

			CDC *pDC = CDC::FromHandle(m_ImgScreenBuf.GetDC()); 
			pDoc->m_Picture.Show(pDC, CPoint(m_DeltaX,m_DeltaY), CPoint(pDoc->m_Picture.m_Width, pDoc->m_Picture.m_Height), m_Magnify,m_Magnify);
			m_ImgScreenBuf.ReleaseDC();
		}
		else // Diminish Picture Dimentions
		{
			//yeun
			m_OldCalcedMagnify = m_CalcedMagnify;
			m_CalcedMagnify = (abs(m_Magnify-1));
			//

			// Calculate New Dimentions For ScrollView
			m_ScrollSizeTotal.cx = pDoc->m_Picture.m_Width/(abs(m_Magnify-1));
			m_ScrollSizeTotal.cy = pDoc->m_Picture.m_Height/(abs(m_Magnify-1));

			// Center Picture (If We Have Enough Space)
			if(m_ClientRect.right - m_ScrollSizeTotal.cx > 1)
				m_DeltaX = (m_ClientRect.right - pDoc->m_Picture.m_Width/(abs(m_Magnify-1)))/2;
			else m_DeltaX = 0;
			if(m_ClientRect.bottom - m_ScrollSizeTotal.cy > 1)
				m_DeltaY = (m_ClientRect.bottom - pDoc->m_Picture.m_Height/(abs(m_Magnify-1)))/2;
			else m_DeltaY = 0;


			m_ImgScreenBuf.Destroy();
			m_ImgScreenBuf.Create(m_DeltaX+pDoc->m_Picture.m_Width, m_DeltaY+pDoc->m_Picture.m_Height, 24);
			CDC *pDC = CDC::FromHandle(m_ImgScreenBuf.GetDC()); 
			pDoc->m_Picture.Show(pDC, CRect(m_DeltaX,m_DeltaY, m_DeltaX + m_ScrollSizeTotal.cx, m_DeltaY + m_ScrollSizeTotal.cy));
			m_ImgScreenBuf.ReleaseDC();

		}
	} // !FitToScreen


	//현재 스크롤 중심 얻어오기
	CPoint centerScrollPosition = GetCenterScrollPosition();
	//  [3/29/2014 Yeun] TRACE("x=%d y=%d\r\n", centerScrollPosition.x, centerScrollPosition.y);
	if(m_ScrollSizeTotal.cx >= 0 && m_ScrollSizeTotal.cy >= 0 )
	{				
		//m_OldScrollSizeTotal = m_ScrollSizeTotal;
		SetScrollSizes(MM_TEXT, m_ScrollSizeTotal);
	}

	if( m_ScrollSizeTotal.cx != 0 && m_ScrollSizeTotal.cy != 0 && m_OldScrollSizeTotal.cx !=0 && m_OldScrollSizeTotal.cy )
	{
		if(
			m_ScrollSizeTotal.cx != m_OldScrollSizeTotal.cx ||
			m_ScrollSizeTotal.cy != m_OldScrollSizeTotal.cy
			)
		{
			//이전 화면에 비례하게 스크롤 이동		
			//m_OldScrollSizeTotal.cx : centerScrollPosition.x = m_ScrollSizeTotal.cx : X

			int newXScrollPosition=0, newYScrollPosition=0;
			newXScrollPosition = (centerScrollPosition.x * m_ScrollSizeTotal.cx) / m_OldScrollSizeTotal.cx;
			newYScrollPosition = (centerScrollPosition.y * m_ScrollSizeTotal.cy) / m_OldScrollSizeTotal.cy;
			CRect clientRect(0,0,0,0);
			GetClientRect(&clientRect);
			newXScrollPosition -= clientRect.right/2;
			newYScrollPosition -= clientRect.bottom/2;

			ScrollToPosition(CPoint(newXScrollPosition,newYScrollPosition));									
		}
	}	

	CDC * pDCImgScrBuf = CDC::FromHandle(m_ImgScreenBuf.GetDC()); 
	DrawMapInfo(pDCImgScrBuf);
	m_ImgScreenBuf.ReleaseDC();

	CPoint cur_pos = GetScrollPosition(); 
	m_ImgScreenBuf.BitBlt(pDC->GetSafeHdc(), 0, 0);

	m_OldScrollSizeTotal = m_ScrollSizeTotal;




}

CPoint CPictureShowView::GetCenterScrollPosition(void)
{
	CPoint ScrollPosition = GetScrollPosition();
	CRect ClientRect(0,0,0,0);
	GetClientRect(&ClientRect);
	ScrollPosition.x += ClientRect.right/2;
	ScrollPosition.y += ClientRect.bottom/2;
	return ScrollPosition;
}
/*
void CPictureShowView::SetZoomScale(int iScale)
{
	float oldZoomFactor = iScale;
	CPoint centerScrollPosition = GetCenterScrollPosition();

	TRACE("m_zoomFactor=%f\r\n", m_zoomFactor);

	SetDisplaySize();

	int newXScrollPosition = FloatToInt((centerScrollPosition.x / oldZoomFactor) * m_zoomFactor);
	int newYScrollPosition = FloatToInt((centerScrollPosition.y / oldZoomFactor) * m_zoomFactor);
	CRect clientRect(0,0,0,0);
	GetClientRect(&clientRect);
	newXScrollPosition -= clientRect.right/2;
	newYScrollPosition -= clientRect.bottom/2;
	ScrollToPosition(CPoint(newXScrollPosition,newYScrollPosition));
}
*/
int CPictureShowView::FloatToInt(float fNumber)
{
	if (fNumber >= 0)
	{
		fNumber += 0.5f;
	}
	else
	{
		fNumber -= 0.5f;
	}
	return int(fNumber);
}
#if 0
void CPictureShowView::DrawMapInfo(CDC* pDC)
{
	



	Graphics G(pDC->m_hDC);//이미지를 그린 DC에 카메라 위치를 그린다.
	//yeun add
	//if(m_iCurScrCamPixelX != 0 && m_iCurScrCamPixelY != 0)
	if(m_iAbsCamPixelApplyMagX != 0 && m_iAbsCamPixelApplyMagY != 0)
	{
#if 0
		CClientDC dc(this);//현재 스크린 DC에 카메라 위치를 그린다.
		Graphics G(dc.m_hDC);//이미지를 그린 DC에 카메라 위치를 그린다.
#else
		Graphics G(pDC->m_hDC);//이미지를 그린 DC에 카메라 위치를 그린다.
#endif

		COLORREF clr = m_optCommonInfo.m_s.CamDirecStyle.clr;
		BYTE byOpacity = m_optCommonInfo.m_s.CamDirecStyle.byOpacity;
		Color C2(byOpacity, GetRValue(clr), GetGValue(clr), GetBValue(clr));

		SolidBrush B2(C2);

		//	G.FillRectangle(&B1,10,10,300,200);
		int iCamDispSize = m_optCommonInfo.m_s.CamDirecStyle.uSymbolSize;
		int iHalf = iCamDispSize/2;

#if 0
		G.FillEllipse(&B2,
			m_iCurScrCamPixelX-iHalf, m_iCurScrCamPixelY-iHalf,
			m_iCamDispSize, m_iCamDispSize);
#else
		//이미지의 절대 위치에 카메라 위치 표시
		G.FillEllipse(&B2,
			m_iAbsCamPixelApplyMagX-iHalf, m_iAbsCamPixelApplyMagY-iHalf,
			iCamDispSize, iCamDispSize);

		//카메라 방향, 화각
		//Point ar[]={Point(m_iAbsCamPixelApplyMagX[0].,10),Point(125,10),Point(140,30),Point(10,30),Point(25,10)};
		G.FillPolygon(&B2, m_arrAbsPtCamDirecApplyMag, POINT_NUM);		
#endif
	}

	if(m_ptAbsTargetPixelApplyMag.X !=0 && m_ptAbsTargetPixelApplyMag.Y != 0)
	{
		COLORREF clr = m_optCommonInfo.m_s.TargetPointStyle.clr;
		BYTE byOpacity = m_optCommonInfo.m_s.TargetPointStyle.byOpacity;

		Color C1(byOpacity, GetRValue(clr), GetGValue(clr), GetBValue(clr));
		SolidBrush B1(C1);

		int iTargetDispSize = m_optCommonInfo.m_s.TargetPointStyle.uSymbolSize;
		int iHalf = iTargetDispSize/2;

		//표적 위치 
		G.FillEllipse(&B1,
			m_ptAbsTargetPixelApplyMag.X-iHalf, m_ptAbsTargetPixelApplyMag.Y-iHalf,
			iTargetDispSize, iTargetDispSize);
	}

#if 1
	//  [3/28/2014 Yeun] 임시 라인 그리기
	//포인트 구조체 배열
	int iNumOfLine = m_vecTempPointsOfLines.size();
	
	if( iNumOfLine != 0 )
	{
		COLORREF clr = m_optCommonInfo.m_s.LineStyle.clr;
		BYTE byOpacity = m_optCommonInfo.m_s.LineStyle.byOpacity;

		Color C1(byOpacity, GetRValue(clr), GetGValue(clr), GetBValue(clr));
		SolidBrush B1(C1);

		Pen drPen(
		&B1,
		m_optCommonInfo.m_s.LineStyle.uPenSize
		);

		Point * pPoint = new Point[ iNumOfLine ];

		double dSumOfDist=0;
		for ( int i=0; i<iNumOfLine; i++ )
		{			
			//현재 설정된 Opacity 저장 하기
			m_vecTempPointsOfLines[i].penStyle.byOpacity = byOpacity;

			ImageAbsPosToScaledPos( m_vecTempPointsOfLines[i].point, pPoint[i] );			
			if( i != 0 )
			{
				double x1=0,y1=0;
				double x2=0,y2=0;
				m_scaler.DeviceToWorld(m_vecTempPointsOfLines[i-1].point.X, m_vecTempPointsOfLines[i-1].point.Y,
					&x1, &y1);
				m_scaler.DeviceToWorld(m_vecTempPointsOfLines[i].point.X, m_vecTempPointsOfLines[i].point.Y,
					&x2, &y2);

				double dist = CCoordApp::GetDistance(x1, y1, x2, y2);
				dSumOfDist+=dist;
				CString str;
				str.Format(_T("%.2lf"), dSumOfDist);
			
				if( m_bShowRuler )
				{
					pDC->TextOut(
						pPoint[i].X, pPoint[i].Y,
						str );
				}
			}
		}

		G.DrawLines( &drPen, pPoint, iNumOfLine ); 
		
		delete []pPoint;	
	}
#endif


#if 1
	//멤버로 저장된 라인 그리기
	iNumOfLine = m_vec2dPointsOfLines.size();
	if( iNumOfLine != 0 )
	{
		
		for ( int i=0; i<iNumOfLine; i++ ){			

			VEC_STYLISH_POINT vec = m_vec2dPointsOfLines[i];
			int iNumOfPoint = vec.size();
			Point * pPoint = new Point[ iNumOfPoint ];

/*
			Pen drPen(
				Color(
				GetRValue( vec[0].penStyle.clr ),
				GetGValue( vec[0].penStyle.clr ),
				GetBValue( vec[0].penStyle.clr ) ),
				vec[0].penStyle.uPenSize
				);*/

			COLORREF clr	= vec[0].penStyle.clr;
			BYTE byOpacity	= vec[0].penStyle.byOpacity;

			Color C1(byOpacity, GetRValue(clr), GetGValue(clr), GetBValue(clr));
			SolidBrush B1(C1);

			Pen drPen(
				&B1,
				vec[0].penStyle.uPenSize
				);

			for ( int j=0; j<iNumOfPoint; j++ ){			
				ImageAbsPosToScaledPos( vec[j].point, pPoint[j] );				
			}
		
			G.DrawLines( &drPen, pPoint, iNumOfPoint ); 
			delete []pPoint;	
		}
	}
#endif

}

#else
void CPictureShowView::DrawMapInfo(CDC* pDC)
{
	Graphics G(pDC->m_hDC);//이미지를 그린 DC에 카메라 위치를 그린다.
						   //yeun add
						   //if(m_iCurScrCamPixelX != 0 && m_iCurScrCamPixelY != 0)

	for (int i = 0; i < MAX_CHANNEL_NUM; i++)
	{
		if (m_iArrAbsCamPixelApplyMagX[i] != 0 && m_iArrAbsCamPixelApplyMagY[i] != 0)
		{
			Graphics G(pDC->m_hDC);//이미지를 그린 DC에 카메라 위치를 그린다.


			COLORREF clr = m_optCommonInfo.m_s.CamDirecStyle.clr;
			BYTE byOpacity = m_optCommonInfo.m_s.CamDirecStyle.byOpacity;
			Color C2(byOpacity, GetRValue(clr), GetGValue(clr), GetBValue(clr));

			SolidBrush B2(C2);

			//	G.FillRectangle(&B1,10,10,300,200);
			int iCamDispSize = m_optCommonInfo.m_s.CamDirecStyle.uSymbolSize;
			int iHalf = iCamDispSize / 2;


			//이미지의 절대 위치에 카메라 위치 표시
			G.FillEllipse(&B2,
				m_iArrAbsCamPixelApplyMagX[i] - iHalf, m_iArrAbsCamPixelApplyMagY[i] - iHalf,
				iCamDispSize, iCamDispSize);

			//카메라 방향, 화각
			//Point ar[]={Point(m_iAbsCamPixelApplyMagX[0].,10),Point(125,10),Point(140,30),Point(10,30),Point(25,10)};
			G.FillPolygon(&B2, m_arrAbsPtArrCamDirecApplyMag[i], POINT_NUM);
		}
	}


	if (m_ptAbsTargetPixelApplyMag.X != 0 && m_ptAbsTargetPixelApplyMag.Y != 0)
	{
		COLORREF clr = m_optCommonInfo.m_s.TargetPointStyle.clr;
		BYTE byOpacity = m_optCommonInfo.m_s.TargetPointStyle.byOpacity;

		Color C1(byOpacity, GetRValue(clr), GetGValue(clr), GetBValue(clr));
		SolidBrush B1(C1);

		int iTargetDispSize = m_optCommonInfo.m_s.TargetPointStyle.uSymbolSize;
		int iHalf = iTargetDispSize / 2;

		//표적 위치 
		G.FillEllipse(&B1,
			m_ptAbsTargetPixelApplyMag.X - iHalf, m_ptAbsTargetPixelApplyMag.Y - iHalf,
			iTargetDispSize, iTargetDispSize);
	}

#if 1
	//  [3/28/2014 Yeun] 임시 라인 그리기
	//포인트 구조체 배열
	int iNumOfLine = m_vecTempPointsOfLines.size();

	if (iNumOfLine != 0)
	{
		COLORREF clr = m_optCommonInfo.m_s.LineStyle.clr;
		BYTE byOpacity = m_optCommonInfo.m_s.LineStyle.byOpacity;

		Color C1(byOpacity, GetRValue(clr), GetGValue(clr), GetBValue(clr));
		SolidBrush B1(C1);

		Pen drPen(
			&B1,
			m_optCommonInfo.m_s.LineStyle.uPenSize
		);

		Point * pPoint = new Point[iNumOfLine];

		double dSumOfDist = 0;
		for (int i = 0; i<iNumOfLine; i++)
		{
			//현재 설정된 Opacity 저장 하기
			m_vecTempPointsOfLines[i].penStyle.byOpacity = byOpacity;

			ImageAbsPosToScaledPos(m_vecTempPointsOfLines[i].point, pPoint[i]);
			if (i != 0)
			{
				double x1 = 0, y1 = 0;
				double x2 = 0, y2 = 0;
				m_scaler.DeviceToWorld(m_vecTempPointsOfLines[i - 1].point.X, m_vecTempPointsOfLines[i - 1].point.Y,
					&x1, &y1);
				m_scaler.DeviceToWorld(m_vecTempPointsOfLines[i].point.X, m_vecTempPointsOfLines[i].point.Y,
					&x2, &y2);

				double dist = CCoordApp::GetDistance(x1, y1, x2, y2);
				dSumOfDist += dist;
				CString str;
				str.Format(_T("%.2lf"), dSumOfDist);

				if (m_bShowRuler)
				{
					pDC->TextOut(
						pPoint[i].X, pPoint[i].Y,
						str);
				}
			}
		}

		G.DrawLines(&drPen, pPoint, iNumOfLine);

		delete[]pPoint;
	}
#endif


#if 1
	//멤버로 저장된 라인 그리기
	iNumOfLine = m_vec2dPointsOfLines.size();
	if (iNumOfLine != 0)
	{

		for (int i = 0; i<iNumOfLine; i++) {

			VEC_STYLISH_POINT vec = m_vec2dPointsOfLines[i];
			int iNumOfPoint = vec.size();
			Point * pPoint = new Point[iNumOfPoint];

			/*
			Pen drPen(
			Color(
			GetRValue( vec[0].penStyle.clr ),
			GetGValue( vec[0].penStyle.clr ),
			GetBValue( vec[0].penStyle.clr ) ),
			vec[0].penStyle.uPenSize
			);*/

			COLORREF clr = vec[0].penStyle.clr;
			BYTE byOpacity = vec[0].penStyle.byOpacity;

			Color C1(byOpacity, GetRValue(clr), GetGValue(clr), GetBValue(clr));
			SolidBrush B1(C1);

			Pen drPen(
				&B1,
				vec[0].penStyle.uPenSize
			);

			for (int j = 0; j<iNumOfPoint; j++) {
				ImageAbsPosToScaledPos(vec[j].point, pPoint[j]);
			}

			G.DrawLines(&drPen, pPoint, iNumOfPoint);
			delete[]pPoint;
		}
	}
#endif

}

#endif



//-----------------------------------------------------------------------------
void CPictureShowView::OnInitialUpdate()
//=============================================================================
{
	CScrollView::OnInitialUpdate();

	CPictureShowDoc* pDoc = GetDocument();

	//m_sockAuthorityClient.SetCh(i + 1);
	m_sockAuthorityClient.SetUpdatingDlg(this);
	m_sockAuthorityClient.SetPacketUpdatingDlg(this);
	if (!m_sockAuthorityClient.Create(30004, SOCK_DGRAM))
	{
		AfxMessageBox(GetSocketCreationError(GetLastError()));
		return;
	}
	else//소켓 생성 성공
	{
		//서버에 접속 한다.
		//BOOL bResult = m_sockAuthorityClient.Connect((WCHAR*)chConfINI.m_s.tstrAuthServerIPAddr[i], (UINT)chConfINI.m_s.nAuthServerPort[i]);

		//OnConnect() 이벤트 함수에서 접속 되었는지 확인
		//m_ClientSocket_Login.m_bLoginSocketCreation = TRUE;
	}
	

	//yeun add

	m_dlgStatusCoord.Create(IDD_DIALOG_STATUS_COORD, this);	

	
	//  [3/27/2014 Yeun]
	TCHAR programpath[MAX_PATH];
	TCHAR szDrv[256] = { 0x00 };
	TCHAR szDir[256] = { 0x00 };
	::GetModuleFileName(NULL, programpath, MAX_PATH);
	::_tsplitpath(programpath, szDrv, szDir, NULL, NULL);

	//절대 경로 로드를 위해
	CString strDefFile;
	strDefFile.Format(_T("%s%s%s"), szDrv, szDir, _T("ImgMap\\U2SR.jpg"));	
	GetDocument()->m_strMapPath.Format(_T("%s%s%s"), szDrv, szDir, _T("ImgMap\\"));

	
	if( strcmp(m_optCommonInfo.m_s.strMapFilePathName, _T("")) != 0 )//이전에 사용한 파일이 있는경우
	{
		//실제 파일이 있는지 찾아본다.
		CFileFind find;
		BOOL bFind = find.FindFile( m_optCommonInfo.m_s.strMapFilePathName );
		if(!bFind)
		{
			int iErr = GetLastError();
			CString strMsg;
			strMsg.Format( _T("%s 파일이 없습니다."), m_optCommonInfo.m_s.strMapFilePathName );
			AfxMessageBox( strMsg );
			pDoc->m_strMapPathName = strDefFile;
		}
		else
		{
			pDoc->m_strMapPathName = m_optCommonInfo.m_s.strMapFilePathName;
			
		}		
	}
	else//기본 파일로 로드
	{	
		pDoc->m_strMapPathName = strDefFile;		
	}
	LoadMapFile();
	

	//  [3/29/2014 Yeun]
	m_dlgDrawingStyleConfig.SetOpt(&m_optCommonInfo);
	m_dlgDrawingStyleConfig.Create(IDD_DRAWINGSTYLE_CONFIG, this);	

	pDoc->SetTitle(_T("U2SR"));

	g_QTRegistry.SetRootKey(HKEY_CURRENT_USER);	
	g_QTRegistry.CreateKey(g_strKey);
	g_QTRegistry.SetKey(g_strKey, TRUE);

	m_Magnify = g_QTRegistry.ReadInt("MAGNIFICATION", -5);

	CString strText;
	strText.Format(_T("배율 %d"), m_Magnify);
	m_dlgStatusCoord.GetDlgItem(IDC_STATIC_MAGNIFICATION)->SetWindowText(strText);


	//ini읽어온 값으로 카메라 위치 표시
	
#if 0
		SetCamInfo(m_ipc_caminfo);
	SetTargetInfo(m_ipc_targetinfo);
#else

	
	

#endif
	//  [3/30/2014 Administrator] test
	SetTimer(1, 1000, NULL);

	// 메시지 등록
	message = RegisterWindowMessage(_T("Hawkeye_PTZEnvSetup"));
}

/////////////////////////////////////////////////////////////////////////////
// CPictureShowView printing

//-----------------------------------------------------------------------------
BOOL CPictureShowView::OnPreparePrinting(CPrintInfo* pInfo)
//=============================================================================
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

//-----------------------------------------------------------------------------
void CPictureShowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
//=============================================================================
{
	// TODO: add extra initialization before printing
}

//-----------------------------------------------------------------------------
void CPictureShowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
//=============================================================================
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPictureShowView diagnostics

#ifdef _DEBUG
//-----------------------------------------------------------------------------
void CPictureShowView::AssertValid() const
//=============================================================================
{
	CScrollView::AssertValid();
}

//-----------------------------------------------------------------------------
void CPictureShowView::Dump(CDumpContext& dc) const
//=============================================================================
{
	CScrollView::Dump(dc);
}

//-----------------------------------------------------------------------------
CPictureShowDoc* CPictureShowView::GetDocument() // non-debug version is inline
//=============================================================================
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPictureShowDoc)));
	return (CPictureShowDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPictureShowView message handlers

//-----------------------------------------------------------------------------
BOOL CPictureShowView::OnEraseBkgnd(CDC* pDC)
//=============================================================================
{
	if(m_FitToScreen)
	{
	// Do Nothing Coz We Cover All Client Area...
	}
	else // FitToScreen = TRUE
	{	
	CPictureShowDoc* pDoc = GetDocument();
	CRect ClientRect;
	GetClientRect(&ClientRect);
	COLORREF BackgroundColor = RGB(0,0,0);
	CBrush BackgroundBrush(BackgroundColor);
	pDC->SelectObject(BackgroundBrush);
	pDC->FillSolidRect(CRect(0,0,ClientRect.right,ClientRect.bottom), BackgroundColor);
	} // FitToScreen = FALSE

//////////////////////////////////////////////////////////////////////////
// ToDo: Create An OffScreen DC And Update The Background OffScreen     //
//       To Allow Resizing The Window With No Flickering (Blinking)     //
//		 (Just Have No Time 4 This - Please Send Me Some Working Stuff) //
//////////////////////////////////////////////////////////////////////////
/*	// Erase Background - But Keep Picture In The Middle...
	if(ClientRect.right - pDoc->m_Picture.m_Width > 0) // Top
	pDC->FillSolidRect(CRect(
			0,
			0,
			ClientRect.right,
			m_DeltaY), BackgroundColor);
	
	if(ClientRect.right - pDoc->m_Picture.m_Width > 1) // Bottom
	pDC->FillSolidRect(CRect(
			0,
			m_DeltaY + pDoc->m_Picture.m_Height,
			ClientRect.right,
			ClientRect.bottom), BackgroundColor);

	if(ClientRect.right - pDoc->m_Picture.m_Width > 0) // Left
	pDC->FillSolidRect(CRect(
			0,
			m_DeltaY,
			m_DeltaX,
			m_DeltaY + pDoc->m_Picture.m_Height), BackgroundColor);

	if(ClientRect.right - pDoc->m_Picture.m_Width > 1) // Right
	pDC->FillSolidRect(CRect(
			m_DeltaX + pDoc->m_Picture.m_Width,
			m_DeltaY,  
			ClientRect.right,
			m_DeltaY + pDoc->m_Picture.m_Height), BackgroundColor);

*/

//	return CScrollView::OnEraseBkgnd(pDC);
	return(TRUE);
}

//-----------------------------------------------------------------------------
void CPictureShowView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
//=============================================================================
{
	CPictureShowDoc* pDoc = GetDocument();
	CMainFrame* pMFrm = (CMainFrame*)AfxGetMainWnd();

	switch(nChar)
	{
	case 27: // Escape
		{
		if((m_Magnify || m_FitToScreen != FALSE || pMFrm->m_FullScreen) != 0)
			{ 
			m_Magnify = 0;
			m_FitToScreen = FALSE;
			if(pMFrm->m_FullScreen) pMFrm->OnOptionsFullscreen();
			}
		else PostMessage(WM_QUIT, 0, 0);

		Invalidate();
		break;
		}

	case 106: // "*"
		{
		OnOptionsFittoscreen();
		break;
		}

	case 107: // "+" if(nChar == 109 || nChar ==189)
		{
		OnButtonMagnify();
		break;
		}
	case 109: // "-" if(nChar == 109 || nChar ==189)
		{
		OnButtonDiminish();
		break;
		}

	case 38: // Up
		{ 
		CPoint CurrentScroll = GetDeviceScrollPosition();
		ScrollToPosition(CPoint(CurrentScroll.x, CurrentScroll.y - m_ScrollKeySpeed));
		break;
		}
	case 40: // Down
		{ 
		CPoint CurrentScroll = GetDeviceScrollPosition();
		if(m_DeltaY == 0) // Genius !!! - Scrool Only When Picture Has No Free Space
		ScrollToPosition(CPoint(CurrentScroll.x, CurrentScroll.y + m_ScrollKeySpeed));
		break;
		}
	case 37: // Left
		{
		CPoint CurrentScroll = GetDeviceScrollPosition();
		ScrollToPosition(CPoint(CurrentScroll.x - m_ScrollKeySpeed, CurrentScroll.y));
		break;
		}
	case 39: // Right
		{ 
		CPoint CurrentScroll = GetDeviceScrollPosition();
		if(m_DeltaX == 0) // Genius !!! - Scrool Only When Picture Has No Free Space
		ScrollToPosition(CPoint(CurrentScroll.x + m_ScrollKeySpeed, CurrentScroll.y));
		break;
		}
	case 36: // Home
		{ 
		CPoint CurrentScroll = GetDeviceScrollPosition();
		ScrollToPosition(CPoint(CurrentScroll.x, 0));
		break;
		}
	case 35: // End
		{ 
		CPoint CurrentScroll = GetDeviceScrollPosition();
		ScrollToPosition(CPoint(CurrentScroll.x, pDoc->m_Picture.m_Height*(m_Magnify+1)));
		break;
		}
	case 33: // PgUp
		{
		OnButtonPrev();
		break;
		}
	case 34: // PgDn
		{ 
		OnButtonNext();
		break;
		}
  
	} // switch...

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//-----------------------------------------------------------------------------
void CPictureShowView::OnOptionsFittoscreen() 
//=============================================================================
{
	CPictureShowDoc* pDoc = GetDocument();

	m_FitToScreen = m_FitToScreen ? FALSE : TRUE;

	pDoc->UpdateAllViews(NULL);
}

//-----------------------------------------------------------------------------
void CPictureShowView::OnUpdateOptionsFittoscreen(CCmdUI* pCmdUI) 
//=============================================================================
{
	CPictureShowDoc* pDoc = GetDocument();
//	m_FitToScreen ? pCmdUI->SetCheck(1) : pCmdUI->SetCheck(0);
	m_FitToScreen ? pCmdUI->SetText("Maintain aspect ratio (1:1)\t *") : pCmdUI->SetText("Fit picture to screen\t *");
}

//-----------------------------------------------------------------------------
void CPictureShowView::OnButtonMagnify() 
//=============================================================================
{
	if(m_FitToScreen)
		{
		HWND hWnd = AfxGetApp()->GetMainWnd()->m_hWnd;
		MessageBoxEx(hWnd, "You are on a\"Fit to screen\" mode\t\nPlease switch to a normal (1:1) aspect ratio\t", "Attention", MB_OK | MB_ICONINFORMATION, LANG_ENGLISH);
		}
	else if(m_Magnify < 50)
	{		
		m_Magnify++;	
		//Invalidate();//  [3/29/2014 Yeun]
		Invalidate(FALSE);

		CString strText;
		strText.Format(_T("배율 %d"), m_Magnify);
		m_dlgStatusCoord.GetDlgItem(IDC_STATIC_MAGNIFICATION)->SetWindowText(strText);
		g_QTRegistry.WriteInt("MAGNIFICATION", m_Magnify);
		SetTimer(1, 500, NULL);
	}
}

//-----------------------------------------------------------------------------
void CPictureShowView::OnButtonDiminish()
//=============================================================================
{
	if(m_FitToScreen)
		{
		HWND hWnd = AfxGetApp()->GetMainWnd()->m_hWnd;
		MessageBoxEx(hWnd, "You are on a\"Fit to screen\" mode\t\nPlease switch to a normal (1:1) aspect ratio\t", "Attention", MB_OK | MB_ICONINFORMATION, LANG_ENGLISH);
		}
	else if(m_Magnify > -12)
	{
		m_Magnify--;		
		//Invalidate();
		Invalidate(FALSE);
	
		CString strText;
		strText.Format(_T("배율 %d"), m_Magnify);
		m_dlgStatusCoord.GetDlgItem(IDC_STATIC_MAGNIFICATION)->SetWindowText(strText);
		g_QTRegistry.WriteInt("MAGNIFICATION", m_Magnify);
		SetTimer(1, 500, NULL);
	}
}

#include "AssociationsDlg.h"
//-----------------------------------------------------------------------------
void CPictureShowView::OnOptionsAssociatefileextentions() 
//=============================================================================
{
	CAssociationsDlg AssociationsDlg;
	AssociationsDlg.DoModal();
}

//-----------------------------------------------------------------------------
void CPictureShowView::OnButtonFittoscreen() 
//=============================================================================
{
	OnOptionsFittoscreen(); // Just Do The Same...
}

//-----------------------------------------------------------------------------
void CPictureShowView::OnIndicatorInfo(CCmdUI *pCmdUI)
//=============================================================================
{
	CPictureShowDoc* pDoc = GetDocument();

	CString sPictureInfo = "";

	CString strShow; strShow.Format("%s", m_bShowRuler ? "On" : "Off" );
	sPictureInfo.Format(" %4d x %4d (%dKb) Rulrer "+strShow, pDoc->m_Picture.m_Width, pDoc->m_Picture.m_Height, pDoc->m_Picture.m_Weight/1024);

	pCmdUI->SetText(sPictureInfo);
}


//-----------------------------------------------------------------------------
void CPictureShowView::OnButtonPrev() 
//=============================================================================
{
	//  [3/29/2014 Yeun]
	/*
		m_ViewForward = FALSE;
		
			CPictureShowDoc* pDoc = GetDocument();
		
			if(pDoc->m_FilesListPos > 1)
				{
				pDoc->m_FilesListPos--;
				pDoc->m_FilesList.GetPrev(pDoc->m_FilesListPosition);
		
				pDoc->m_FilePathName.Format("%s", pDoc->m_FilesList.GetAt(pDoc->m_FilesListPosition));
				pDoc->UpdateAllViews(NULL);
		
				//CString S;
				//S.Format("Number = %d, \"%s\"", m_FilesListPos, m_FilesList.GetAt(m_FilesListPosition));
				//AfxMessageBox(S);
				}*/
		
}

//-----------------------------------------------------------------------------
void CPictureShowView::OnButtonNext() 
//=============================================================================
{
	//  [3/29/2014 Yeun]
	/*
		m_ViewForward = TRUE;
		
			CPictureShowDoc* pDoc = GetDocument();
		
			if(pDoc->m_FilesListPos < pDoc->m_FilesListCount)
				{
				pDoc->m_FilesListPos++;
				pDoc->m_FilesList.GetNext(pDoc->m_FilesListPosition);
		
				pDoc->m_FilePathName.Format("%s", pDoc->m_FilesList.GetAt(pDoc->m_FilesListPosition));
				pDoc->UpdateAllViews(NULL);
		
				//CString S;
				//S.Format("Number = %d, \"%s\"", m_FilesListPos, m_FilesList.GetAt(m_FilesListPosition));
				//AfxMessageBox(S);
				}*/
		
}
/*
void CPictureShowView::OnButtonMap1()
{
	//GetDocument()->m_strSelFilePathName = GetDocument()->m_strMap1;
	Invalidate(FALSE);
}
void CPictureShowView::OnButtonMap2()
{
	//GetDocument()->m_strSelFilePathName = GetDocument()->m_strMap2;
	Invalidate(FALSE);
}*/

void CPictureShowView::OnButtonMapOpen()
{

	/*
	GetDocument()->m_strSelFilePathName = GetDocument()->m_strMap2;
	Invalidate(FALSE);
	*/
	
	//yeun 20131114
	TCHAR programpath[MAX_PATH];
	TCHAR szDrv[256] = { 0x00 };
	TCHAR szDir[256] = { 0x00 };
	::GetModuleFileName(NULL, programpath, MAX_PATH);
	::_tsplitpath(programpath, szDrv, szDir, NULL, NULL);

	CString strFilter = "Picture Files (bmp.dib.emf.gif.ico.jpg.wmf)|*.bmp;dib;emf;gif;ico;*.jpg;wmf|BMP (*.bmp)|*.bmp|DIB (*.dib)|*.dib|EMF (*.emf)|*.emf|GIF (*.gif)|*.gif|ICO (*.ico)|*.ico|JPG (*.jpg)|*.jpg|WMF (*.wmf)|*.wmf|All Files (*.*)|*.*||";
	CFileDialog OpenFileDialog(TRUE, NULL, GetDocument()->m_strMapPathName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	OpenFileDialog.m_ofn.lpstrTitle = "Open a picture file";

	if(OpenFileDialog.DoModal() == IDOK)
	{
		//m_FilePathName.Format("%s", OpenFileDialog.m_ofn.lpstrFile);
		GetDocument()->m_strMapPathName.Format("%s", OpenFileDialog.m_ofn.lpstrFile);
		LoadMapFile();
		

		//  [3/28/2014 Yeun] GetDocument()->UpdateAllViews(NULL);

		//CreateFilesList(); // Read Files At The Current Directory As It Changes			
		
		CString strText;
		strText.Format(_T("배율 %d"), m_Magnify);
		m_dlgStatusCoord.GetDlgItem(IDC_STATIC_MAGNIFICATION)->SetWindowText(strText);

		SetCamInfo(m_ipc_caminfo);
		SetTargetInfo(m_ipc_targetinfo);
	}
}

void CPictureShowView::OnButtonPen()
{
	if( m_bPenMode == FALSE)
	{
		m_bPenMode = TRUE;
		SendMessage(WM_SETCURSOR, 2);
	}
	else
	{
		m_bPenMode = FALSE;
		SendMessage(WM_SETCURSOR, 1);
	}
}
//-----------------------------------------------------------------------------
void CPictureShowView::OnUpdateButtonNext(CCmdUI* pCmdUI) 
//=============================================================================
{
	CPictureShowDoc* pDoc = GetDocument();

	if(!(pDoc->m_FilesListPos < pDoc->m_FilesListCount)) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
}

//-----------------------------------------------------------------------------
void CPictureShowView::OnUpdateButtonPrev(CCmdUI* pCmdUI) 
//=============================================================================
{
	CPictureShowDoc* pDoc = GetDocument();

	if(!(pDoc->m_FilesListPos > 1)) pCmdUI->Enable(FALSE);
	else pCmdUI->Enable(TRUE);
}

//-----------------------------------------------------------------------------
void CPictureShowView::OnLButtonDblClk(UINT nFlags, CPoint point) 
//=============================================================================
{
	CMainFrame* pMFrm = (CMainFrame*)AfxGetMainWnd();

	//pMFrm->OnButtonFullscreen();//yeun

	CScrollView::OnLButtonDblClk(nFlags, point);
}

//-----------------------------------------------------------------------------
void CPictureShowView::OnHelpHomepage() 
//=============================================================================
{
	ShellExecute(NULL, "open", "http://www.SuperMain.com", NULL, NULL, SW_SHOWNORMAL); 
}

//-----------------------------------------------------------------------------
void CPictureShowView::OnOptionsFitborderstopicture()
//=============================================================================
{
	CPictureShowDoc* pDoc = GetDocument();
	CMainFrame* pMFrm = (CMainFrame*)AfxGetMainWnd();

	// Hay You - If U Have The Time, Get "Bar" Sizes Properly And Send Me The Final Code
	int Borders_Width = 6; // Each Border Sides = 6 (Left And Right)
	int ToolBars_Height = 47; // Height Of Both ToolBar And StatusBar;

	int DesktopWidth  = GetSystemMetrics(SM_CXSCREEN);
	int DesktopHeight = GetSystemMetrics(SM_CYSCREEN);

	CRect GlobalWnd; // Will Include The LocalWnd At The Center
    CRect ToolBarRect;
	pMFrm->m_WndToolBar.GetClientRect(&ToolBarRect);
	ToolBars_Height = ToolBarRect.Height() - 1;

	if(pMFrm->m_WndToolBar.IsFloating()) ToolBars_Height = ToolBars_Height / 2 - 1;

    CRect StatusBarRect;
	pMFrm->m_WndStatusBar.GetClientRect(&StatusBarRect);
	ToolBars_Height += StatusBarRect.Height() + 7;
	
	if(!pMFrm->m_WndStatusBar.IsWindowVisible()) ToolBars_Height -= (StatusBarRect.Height() -7 -1);

	CRect LocalWnd(0,
				   0,
				   pDoc->m_Picture.m_Width + Borders_Width*2,
				   pDoc->m_Picture.m_Height + ToolBars_Height*2);

	// Make Width At Least The Size Of The ToolBar
	if(LocalWnd.Width() < ToolBarRect.Width())
	   LocalWnd.InflateRect(0, 0, ToolBarRect.Width() - pDoc->m_Picture.m_Width + Borders_Width, 0);

	GlobalWnd.left = (DesktopWidth - LocalWnd.right)/2;
	GlobalWnd.top = (DesktopHeight - LocalWnd.bottom)/2;
	GlobalWnd.right= LocalWnd.right + GlobalWnd.left;
	GlobalWnd.bottom = LocalWnd.bottom + GlobalWnd.top;



	


	// Cut Extra Space When Needed...
#if 0//  [3/30/2014 Yeun]
	if(GlobalWnd.top < 0) GlobalWnd.top = 0;
	if(GlobalWnd.left < 0) GlobalWnd.left = 0;
	if(GlobalWnd.bottom > DesktopHeight) GlobalWnd.bottom = GetSystemMetrics(SM_CYMAXIMIZED);
	if(GlobalWnd.right > DesktopWidth) GlobalWnd.right = GetSystemMetrics(SM_CXMAXIMIZED);
#else//

	if( m_optCommonInfo.m_s.iWidth == 0 || m_optCommonInfo.m_s.iHeight == 0 )
	{
		m_optCommonInfo.m_s.iHeight =  GetSystemMetrics(SM_CYMAXIMIZED)/2;
		m_optCommonInfo.m_s.iWidth  = GetSystemMetrics(SM_CXMAXIMIZED)/2+60;
	}
	
	if( GlobalWnd.top < 0 )
		GlobalWnd.top = m_optCommonInfo.m_s.iY;
	if( GlobalWnd.left < 0 )
		GlobalWnd.left = m_optCommonInfo.m_s.iX;

	if(GlobalWnd.bottom > DesktopHeight)
		GlobalWnd.bottom = m_optCommonInfo.m_s.iHeight;
	if(GlobalWnd.right > DesktopWidth)
		GlobalWnd.right = m_optCommonInfo.m_s.iWidth;

#endif
	WINDOWPLACEMENT WP;
	WP.rcNormalPosition = GlobalWnd;
	WP.showCmd = SW_SHOW;

	pMFrm->SetWindowPlacement(&WP);
}

//-----------------------------------------------------------------------------
void CPictureShowView::OnOptionsNextpicture() 
//=============================================================================
{
	OnButtonNext();
}

//-----------------------------------------------------------------------------
void CPictureShowView::OnOptionsPreviouspicture() 
//=============================================================================
{
	OnButtonPrev();
}

void CPictureShowView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here	
	CMainFrame* pMFrm = (CMainFrame*)AfxGetMainWnd();
	if( pMFrm != NULL)
		pMFrm->MoveDlgStatusCoord();
}

void CPictureShowView::OnSizing(UINT fwSide, LPRECT pRect)
{
	CScrollView::OnSizing(fwSide, pRect);

	// TODO: Add your message handler code here

}

void CPictureShowView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if( m_bPenMode == TRUE )
	{
		//  [3/28/2014 Yeun]
		//클릭한 지점의 위치를 임시 벡터에 푸시

		int iScrolledX=0, iScrolledY=0;
		MouseCurPosToScrolledPos( point, iScrolledX, iScrolledY );
		Point imgAbsPos;
		ScrolledToImageAbsPos( iScrolledX, iScrolledY, imgAbsPos );
		
		STYLISH_POINT stylept;
		stylept.point = imgAbsPos;
		stylept.penStyle.clr = m_optCommonInfo.m_s.LineStyle.clr;
		stylept.penStyle.uPenSize = m_optCommonInfo.m_s.LineStyle.uPenSize;

		if( m_vecTempPointsOfLines.size() == 0 )//처음에만 포인트를 두개 추가
		{		
			m_vecTempPointsOfLines.push_back( stylept );//시작점
			TRACE( "push_back\n" );
			m_vecTempPointsOfLines.push_back( stylept );//끝점 onmousemove에서 끝점을 계속 업데이트 한다. 실시간으로 그려짐
			TRACE( "push_back\n" );
		}
		else//이어 그리기
		{
			m_vecTempPointsOfLines.push_back( stylept );//다음점
			TRACE( "push_back\n" );
		}

		//RedrawWindow();
		Invalidate(FALSE);
	}

	CScrollView::OnLButtonDown(nFlags, point);
}

void CPictureShowView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if( m_bPenMode == TRUE && (nFlags & MK_LBUTTON))//그리기 모드에서 한점을 클릭하고 이동할때
	{
		int iScrolledX=0, iScrolledY=0;
		MouseCurPosToScrolledPos( point, iScrolledX, iScrolledY );
		Point imgAbsPos;
		ScrolledToImageAbsPos( iScrolledX, iScrolledY, imgAbsPos );
		
		m_vecTempPointsOfLines[ m_vecTempPointsOfLines.size()-1].point = imgAbsPos;

		//RedrawWindow();
		Invalidate(FALSE);
	}
	

	int iMouseAbsX=0, iMouseAbsY=0;
	MouseCurPosToScrolledPos( point, iMouseAbsX, iMouseAbsY );
	CString strText;
	strText.Format(_T("X픽셀 : %d, Y픽셀 : %d"), iMouseAbsX, iMouseAbsY);
	m_dlgStatusCoord.GetDlgItem(IDC_STATIC_VIEW_PIXEL)->SetWindowText(strText);

	int OrgX=0, OrgY=0;
	Point imgAbsPos;
	ScrolledToImageAbsPos( iMouseAbsX, iMouseAbsY, imgAbsPos );

	strText.Format(_T("원본픽셀 : %d, 원본픽셀 %d"), imgAbsPos.X, imgAbsPos.Y);
	m_dlgStatusCoord.GetDlgItem(IDC_STATIC_ORGIMG_PIXEL)->SetWindowText(strText);	


	double dX=0, dY=0;
	//  [3/28/2014 Yeun] m_scaler.DeviceToWorld( OrgX, OrgY, &dX, &dY );
	m_scaler.DeviceToWorld( imgAbsPos.X, imgAbsPos.Y, &dX, &dY);
	
	strText.Format(_T("x : %lf, y : %lf"), dX, dY);
	m_dlgStatusCoord.GetDlgItem(IDC_STATIC_TM)->SetWindowText(strText);
	
	int iLatD=0, iLatM=0;
	double dLatS=0.0;
	int iLongD=0, iLongM=0;
	double dLongS=0.0;

	m_scaler.Tm2DMS( dX, dY,
		iLatD, iLatM, dLatS,
		iLongD, iLongM, dLongS
		);
	
	strText.Format(_T("위도(Lat) %d도%d분%05.02lf초 경도(Long) %d도%d분%05.02lf초"),
		iLatD, iLatM, dLatS,
		iLongD, iLongM, dLongS);
	m_dlgStatusCoord.GetDlgItem(IDC_STATIC_DMS)->SetWindowText(strText);

	CString strMgrs, strLat, strLong;
	
	strLat.Format(  _T("N %02d˚%02d\'%05.02lf\""), iLatD, iLatM, dLatS);
	strLong.Format( _T("E %03d˚%02d\'%05.02lf\""), iLongD, iLongM, dLongS);

	// convert gps to mgrs : (N 00˚59'59.99"), (E 000˚59'59.99")
	Util_ConvGPStoMGRS( strMgrs, strLat, strLong);
	
	strText.Format( "군사좌표(MGRS) %s %s %s", strMgrs.Left(5), strMgrs.Mid(5, 5), strMgrs.Right(5) );
	m_dlgStatusCoord.GetDlgItem(IDC_STATIC_MGRS)->SetWindowText(strText);
	

	int nCh = m_dlgStatusCoord.GetSelectedCh();
	double dPan;
	UINT nDistance;

	IPC_CAMINFO caminfo = m_arrCaminfo[nCh - 1];
	CCoordApp coordApp;
	coordApp.TwoLatLongToAzimuthAndDistance(
		caminfo.coordinfo.byLatDeg, caminfo.coordinfo.byLatMin, caminfo.coordinfo.byLatSec, caminfo.coordinfo.byLatSecFrac, 
		caminfo.coordinfo.byLongDeg, caminfo.coordinfo.byLongMin, caminfo.coordinfo.byLongSec, caminfo.coordinfo.byLongSecFrac,
		(BYTE)iLatD, (BYTE)iLatM, (BYTE)dLatS, (BYTE)((dLatS - (BYTE)dLatS)*100),
		(BYTE)iLongD, (BYTE)iLongM, (BYTE)dLongS, (BYTE)((dLongS - (BYTE)dLongS) * 100),
		dPan, nDistance
		);
	
	CString strPanAndDistance;
	strPanAndDistance.Format(_T("방위각:%06.02f, 거리:%d(m)"),
		dPan, nDistance);

	m_dlgStatusCoord.GetDlgItem(IDC_STATIC_MOUSE_PANTILT)->SetWindowText(strPanAndDistance);
	
	CScrollView::OnMouseMove(nFlags, point);
}

void CPictureShowView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if( m_bPenMode == TRUE)//그리기 모드에서 한점을 클릭하고 이동할때
	{
		int iScrolledX=0, iScrolledY=0;
		MouseCurPosToScrolledPos( point, iScrolledX, iScrolledY );
		Point imgAbsPos;
		ScrolledToImageAbsPos( iScrolledX, iScrolledY, imgAbsPos );

		m_vecTempPointsOfLines[ m_vecTempPointsOfLines.size()-1].point = imgAbsPos;

		//RedrawWindow();
		Invalidate(FALSE);
	}
	CScrollView::OnLButtonUp(nFlags, point);
}

void CPictureShowView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	switch ( nIDEvent )
	{
	case 1:
		{

		/*
				IPC_CAMINFO caminfo;
						caminfo.coordinfo.byLatSign		= NORTH_BYTE;
						caminfo.coordinfo.byLatDeg		= 37;
						caminfo.coordinfo.byLatMin		= 36;
						caminfo.coordinfo.byLatSec		= 14;
						caminfo.coordinfo.byLatSecFrac	= 12;
			
						caminfo.coordinfo.byLongSign	= EAST_BYTE;
						caminfo.coordinfo.byLongDeg		= 127;
						caminfo.coordinfo.byLongMin		= 2;	
						caminfo.coordinfo.byLongSec		= 9;	
						caminfo.coordinfo.byLongSecFrac	= 83;
			
						caminfo.fPan					= 30;
						caminfo.fTilt					= -5;
						caminfo.fFovW					= 30;
						caminfo.uSuvailRange			= 500;
			
						caminfo.byCamType				= 1;*/
			

			KillTimer(nIDEvent);

			for (int i = 0; i < MAX_CHANNEL_NUM; i++)
			{

				m_dArrPanOffset[i] = m_iniPTZEnvSetup.m_s.panOffset[i];

				IPC_CAMINFO caminfo;

				m_arrCaminfo[i].coordinfo.byLatSign = NORTH_BYTE;
				m_arrCaminfo[i].coordinfo.byLatDeg = (byte)m_iniPTZEnvSetup.m_s.latitudeDegrees[i];
				m_arrCaminfo[i].coordinfo.byLatMin = (byte)m_iniPTZEnvSetup.m_s.latitudeMinute[i];
				m_arrCaminfo[i].coordinfo.byLatSec = (byte)m_iniPTZEnvSetup.m_s.latitudeSecond[i];
				m_arrCaminfo[i].coordinfo.byLatSecFrac = (byte)m_iniPTZEnvSetup.m_s.longitudeSecondDot[i];

				m_arrCaminfo[i].coordinfo.byLongSign = WEST_BYTE;
				m_arrCaminfo[i].coordinfo.byLongDeg = (byte)m_iniPTZEnvSetup.m_s.longitudeDegrees[i];
				m_arrCaminfo[i].coordinfo.byLongMin = (byte)m_iniPTZEnvSetup.m_s.longitudeMinute[i];
				m_arrCaminfo[i].coordinfo.byLongSec = (byte)m_iniPTZEnvSetup.m_s.longitudeSecond[i];
				m_arrCaminfo[i].coordinfo.byLongSecFrac = (byte)m_iniPTZEnvSetup.m_s.longitudeSecondDot[i];

				m_arrCaminfo[i].fPan = (float)20.30;
				m_arrCaminfo[i].fFovW = 30;
				m_arrCaminfo[i].uSuvailRange = m_iniPTZEnvSetup.m_s.rangeSurveillance[i];
				SetCamInfo(m_arrCaminfo[i], i + 1);

			}
			//SetCamInfo(m_ipc_caminfo);
			//SetTargetInfo(m_ipc_targetinfo);
		}
		break;
	}


	CScrollView::OnTimer(nIDEvent);
}


void CPictureShowView::SetCamInfo(IPC_CAMINFO caminfo, int nCh)
{
	int nChIndex = nCh-1;

	int nCurCh = m_dlgStatusCoord.GetSelectedCh();


	CString strLatSec, strLongSec;

	strLatSec.Format(_T("%02d.%02d"), caminfo.coordinfo.byLatSec, caminfo.coordinfo.byLatSecFrac);
	double dLatDec = m_scaler.DMS2Deg(
		caminfo.coordinfo.byLatDeg, caminfo.coordinfo.byLatMin, atof(strLatSec));

	strLongSec.Format(_T("%02d.%02d"), caminfo.coordinfo.byLongSec, caminfo.coordinfo.byLongSecFrac);
	double dLongDec = m_scaler.DMS2Deg(
		caminfo.coordinfo.byLongDeg, caminfo.coordinfo.byLongMin, atof(strLongSec));


	CString strText;
	strText.Format(_T("위도(Lat) %02d도%02d분%s초 경도(Long) %03d도%02d분%s초"),
		caminfo.coordinfo.byLatDeg, caminfo.coordinfo.byLatMin, strLatSec,
		caminfo.coordinfo.byLongDeg, caminfo.coordinfo.byLongMin, strLongSec,
		caminfo.fPan, caminfo.uSuvailRange);

	if (nCurCh == nCh)
		m_dlgStatusCoord.GetDlgItem(IDC_STATIC_CAMPOS)->SetWindowText(strText);
	
#if 0
	strText.Format(_T("방위각:%06.02f, 고저각:%+07.02f, 화각(W)%05.02f, 감시거리:%d"),
		caminfo.fPan, caminfo.fTilt, caminfo.fFovW, caminfo.uSuvailRange);
#else
	strText.Format(_T("방위각:%06.02f(%06.02f), 고저각:%+07.02f, 감시거리:%d(m)"),
		CCoordApp::PanDecToOffsetCalc( caminfo.fPan, m_dArrPanOffset[nChIndex]) , caminfo.fPan, caminfo.fTilt, caminfo.uSuvailRange);
#endif

	if (nCurCh == nCh)
		m_dlgStatusCoord.GetDlgItem(IDC_STATIC_CAMINFO)->SetWindowText(strText);

	CString strMgrs, strLat, strLong;
	strLat.Format(_T("N %02d˚%02d\'%02d.%02d\""),
		(int)caminfo.coordinfo.byLatDeg, (int)caminfo.coordinfo.byLatMin, (int)caminfo.coordinfo.byLatSec, (int)caminfo.coordinfo.byLatSecFrac);
	strLong.Format(_T("E %03d˚%02d\'%02d.%02d\""),
		(int)caminfo.coordinfo.byLongDeg, (int)caminfo.coordinfo.byLongMin, (int)caminfo.coordinfo.byLongSec, (int)caminfo.coordinfo.byLongSecFrac);

	// convert gps to mgrs : (N 00˚59'59.99"), (E 000˚59'59.99")
	Util_ConvGPStoMGRS(strMgrs, strLat, strLong);

	strText.Format("군사좌표(MGRS) %s %s %s", strMgrs.Left(5), strMgrs.Mid(5, 5), strMgrs.Right(5));

	if (nCurCh == nCh)
		m_dlgStatusCoord.GetDlgItem(IDC_STATIC_CAMPOS_MGRS)->SetWindowText(strText);


	double dTmX = 0, dTmY = 0;
	m_scaler.Deg2Tm(dLatDec, dLongDec, dTmX, dTmY);

	//카메라 위치좌표를 비트맵 절대 좌표로
	m_scaler.WorldToDevice(dTmX, dTmY, m_iArrAbsCamPixelX[nChIndex], m_iArrAbsCamPixelY[nChIndex]);

	//화각 방향 표시 계산 구하기
	DOUBLEPOINT arrTmPtCamDirec[POINT_NUM];
#if 0
	CamPosInfoTo5Point(dTmX, dTmY, caminfo.fPan, caminfo.fFovW, caminfo.uSuvailRange, arrTmPtCamDirec);
#else
	CamPosInfoTo5Point(dTmX, dTmY, CCoordApp::PanDecToOffsetCalc(caminfo.fPan, m_dArrPanOffset[nChIndex]), caminfo.fFovW, caminfo.uSuvailRange, arrTmPtCamDirec);
#endif
	//Tm to AbsPixel
	for (int i = 0; i<POINT_NUM; i++)
	{
		m_scaler.WorldToDevice(
			arrTmPtCamDirec[i].x, arrTmPtCamDirec[i].y,
			m_arrAbsPtCamDirec[i].X, m_arrAbsPtCamDirec[i].Y);
	}

	//축척에 따른 픽셀 계산
	if (m_Magnify >= 0) // Magnify Or Set Original Picture Dimentions
	{
		//기본 배율
		m_iArrAbsCamPixelApplyMagX[nChIndex] = m_iArrAbsCamPixelX[nChIndex] + m_DeltaX;
		m_iArrAbsCamPixelApplyMagY[nChIndex] = m_iArrAbsCamPixelY[nChIndex] + m_DeltaY;

		//절대좌표에 현재 축척 적용
		for (int i = 0; i<POINT_NUM; i++)
		{
			m_arrAbsPtArrCamDirecApplyMag[nChIndex][i].X = (m_arrAbsPtCamDirec[i].X + m_DeltaX);
			m_arrAbsPtArrCamDirecApplyMag[nChIndex][i].Y = (m_arrAbsPtCamDirec[i].Y + m_DeltaX);
		}
	}
	else // Diminish Picture Dimentions
	{
		int iCalcedMag = abs(m_Magnify - 1);//yeun 

											//절대좌표에 현재 축척 적용
		m_iArrAbsCamPixelApplyMagX[nChIndex] = (m_iArrAbsCamPixelX[nChIndex] / iCalcedMag) + m_DeltaX;
		m_iArrAbsCamPixelApplyMagY[nChIndex] = (m_iArrAbsCamPixelY[nChIndex] / iCalcedMag) + m_DeltaY;

		//절대좌표에 현재 축척 적용
		for (int i = 0; i<POINT_NUM; i++)
		{
			m_arrAbsPtArrCamDirecApplyMag[nChIndex][i].X = (m_arrAbsPtCamDirec[i].X / iCalcedMag) + m_DeltaX;
			m_arrAbsPtArrCamDirecApplyMag[nChIndex][i].Y = (m_arrAbsPtCamDirec[i].Y / iCalcedMag) + m_DeltaY;
		}
	}

	Invalidate(FALSE);
}
void CPictureShowView::SetCamInfo()
{
	int nCh = m_dlgStatusCoord.GetSelectedCh();
	SetCamInfo(m_arrCaminfo[nCh - 1], nCh);

}
void CPictureShowView::SetCamInfo(IPC_CAMINFO caminfo)
{
/*
	//이전 화면 지우기		
	ZeroMemory(m_arrAbsPtCamDirecApplyMag, sizeof(Point)*POINT_NUM);
	m_iAbsCamPixelApplyMagX=0; 
	m_iAbsCamPixelApplyMagY=0;
	InvalidateRect(m_rcDrawCam);
	//f
*/
	m_ipc_caminfo = caminfo;

	CString strLatSec, strLongSec;

	strLatSec.Format(_T("%02d.%02d"), m_ipc_caminfo.coordinfo.byLatSec, m_ipc_caminfo.coordinfo.byLatSecFrac);
	double dLatDec = m_scaler.DMS2Deg(
		m_ipc_caminfo.coordinfo.byLatDeg, m_ipc_caminfo.coordinfo.byLatMin, atof(strLatSec) );

	strLongSec.Format(_T("%02d.%02d"), m_ipc_caminfo.coordinfo.byLongSec, m_ipc_caminfo.coordinfo.byLongSecFrac);
	double dLongDec = m_scaler.DMS2Deg(
		m_ipc_caminfo.coordinfo.byLongDeg, m_ipc_caminfo.coordinfo.byLongMin, atof(strLongSec) );

	CString strText;
	strText.Format(_T("위도(Lat) %02d도%02d분%s초 경도(Long) %03d도%02d분%s초"),
		m_ipc_caminfo.coordinfo.byLatDeg, m_ipc_caminfo.coordinfo.byLatMin, strLatSec,
		m_ipc_caminfo.coordinfo.byLongDeg, m_ipc_caminfo.coordinfo.byLongMin, strLongSec,
		m_ipc_caminfo.fPan, m_ipc_caminfo.uSuvailRange);
	m_dlgStatusCoord.GetDlgItem(IDC_STATIC_CAMPOS)->SetWindowText(strText);

#if 0
	strText.Format(_T("방위각:%06.02f, 고저각:%+07.02f, 화각(W)%05.02f, 감시거리:%d"),
		m_ipc_caminfo.fPan, m_ipc_caminfo.fTilt, m_ipc_caminfo.fFovW, m_ipc_caminfo.uSuvailRange);
#else
	strText.Format(_T("방위각:%06.02f, 고저각:%+07.02f, 감시거리:%d(m)"),
		m_ipc_caminfo.fPan, m_ipc_caminfo.fTilt, m_ipc_caminfo.uSuvailRange);
#endif
	m_dlgStatusCoord.GetDlgItem(IDC_STATIC_CAMINFO)->SetWindowText(strText);

	CString strMgrs, strLat, strLong;
	strLat.Format(  _T("N %02d˚%02d\'%02d.%02d\""),
		(int)m_ipc_caminfo.coordinfo.byLatDeg, (int)m_ipc_caminfo.coordinfo.byLatMin, (int)m_ipc_caminfo.coordinfo.byLatSec, (int)m_ipc_caminfo.coordinfo.byLatSecFrac);
	strLong.Format( _T("E %03d˚%02d\'%02d.%02d\""),
		(int)m_ipc_caminfo.coordinfo.byLongDeg, (int)m_ipc_caminfo.coordinfo.byLongMin, (int)m_ipc_caminfo.coordinfo.byLongSec, (int)m_ipc_caminfo.coordinfo.byLongSecFrac);

	// convert gps to mgrs : (N 00˚59'59.99"), (E 000˚59'59.99")
	Util_ConvGPStoMGRS( strMgrs, strLat, strLong);

	strText.Format( "군사좌표(MGRS) %s %s %s", strMgrs.Left(5), strMgrs.Mid(5, 5), strMgrs.Right(5) );
	m_dlgStatusCoord.GetDlgItem(IDC_STATIC_CAMPOS_MGRS)->SetWindowText(strText);


	double dTmX=0, dTmY=0;
	m_scaler.Deg2Tm(dLatDec, dLongDec, dTmX, dTmY);

	//카메라 위치좌표를 비트맵 절대 좌표로
	m_scaler.WorldToDevice(dTmX, dTmY, m_iAbsCamPixelX, m_iAbsCamPixelY );

	//화각 방향 표시 계산 구하기
	DOUBLEPOINT arrTmPtCamDirec[POINT_NUM];	
	CamPosInfoTo5Point(dTmX, dTmY, caminfo.fPan, caminfo.fFovW, caminfo.uSuvailRange, arrTmPtCamDirec );
	
	//Tm to AbsPixel
	for (int i=0; i<POINT_NUM; i++)
	{
		m_scaler.WorldToDevice(
			arrTmPtCamDirec[i].x, arrTmPtCamDirec[i].y,
			m_arrAbsPtCamDirec[i].X, m_arrAbsPtCamDirec[i].Y);
	}

	//축척에 따른 픽셀 계산
	if(m_Magnify >= 0) // Magnify Or Set Original Picture Dimentions
	{
		//기본 배율
		m_iAbsCamPixelApplyMagX = m_iAbsCamPixelX + m_DeltaX;
		m_iAbsCamPixelApplyMagY = m_iAbsCamPixelY + m_DeltaY;

		//절대좌표에 현재 축척 적용
		for (int i=0; i<POINT_NUM; i++)
		{
			m_arrAbsPtCamDirecApplyMag[i].X = (m_arrAbsPtCamDirec[i].X + m_DeltaX);
			m_arrAbsPtCamDirecApplyMag[i].Y = (m_arrAbsPtCamDirec[i].Y + m_DeltaX);					
		}
	}
	else // Diminish Picture Dimentions
	{
		int iCalcedMag	= abs(m_Magnify-1);//yeun 

		//절대좌표에 현재 축척 적용
		m_iAbsCamPixelApplyMagX = (m_iAbsCamPixelX / iCalcedMag) + m_DeltaX;
		m_iAbsCamPixelApplyMagY = (m_iAbsCamPixelY / iCalcedMag) + m_DeltaY;

		//절대좌표에 현재 축척 적용
		for (int i=0; i<POINT_NUM; i++)
		{
			m_arrAbsPtCamDirecApplyMag[i].X = (m_arrAbsPtCamDirec[i].X / iCalcedMag) + m_DeltaX;
			m_arrAbsPtCamDirecApplyMag[i].Y = (m_arrAbsPtCamDirec[i].Y / iCalcedMag) + m_DeltaY;					
		}
	}

/*	
	//절대좌표를 현재 화면상 스크린 좌표로
	if(AbsToScr(m_iAbsCamPixelX, m_iAbsCamPixelY, m_iCurScrCamPixelX, m_iCurScrCamPixelY))
	{
		//이미지 갱신 하고자 하는 렉트계산
		CRect rc;		
		rc.left		= m_iCurScrCamPixelX-m_iCamDispSize;
		rc.right	= m_iCurScrCamPixelX+m_iCamDispSize;
		rc.top		= m_iCurScrCamPixelY-m_iCamDispSize;
		rc.bottom	= m_iCurScrCamPixelY+m_iCamDispSize;

		//현재 이미지를 그리고자 하는 위치만 갱신한다.
		InvalidateRect(rc);
	}
*/

#if 0
	//이미지 갱신 하고자 하는 렉트계산	



	//절대 위치 좌표를 화면 좌표로 변환
	//그리기는 절대 좌표로.. 그리기 갱신은 화면 좌표로..
	BOOL bInScr=FALSE;
	for (int i=0; i<POINT_NUM; i++)
	{
		if(AbsToScr(m_arrAbsPtCamDirec[i].X, m_arrAbsPtCamDirec[i].Y, m_arrCurScrPtCamDirec[i].X, m_arrCurScrPtCamDirec[i].Y))
		{	bInScr = TRUE;	}
		else
		{
			TRACE("i = %d\r\n", i);
			TRACE("x = %d, y =%d\r\n\r\n", m_arrCurScrPtCamDirec[i].X, m_arrCurScrPtCamDirec[i].Y);
			//ASSERT(FALSE);
		}
	}
	if(bInScr)
	{
		//범위 갱신할 최소 범위 구하기
		ZeroMemory(&m_rcDrawCam, sizeof(m_rcDrawCam));
		m_rcDrawCam.left = m_arrCurScrPtCamDirec[0].X;
		m_rcDrawCam.right = m_arrCurScrPtCamDirec[0].X;
		m_rcDrawCam.top = m_arrCurScrPtCamDirec[0].Y;
		m_rcDrawCam.bottom = m_arrCurScrPtCamDirec[0].Y;

		for (int i=0; i<POINT_NUM; i++)
		{
			if(m_arrCurScrPtCamDirec[i].X < m_rcDrawCam.left )//left 가장 작은 수를 넣는다
				m_rcDrawCam.left = m_arrCurScrPtCamDirec[i].X;

			if(m_arrCurScrPtCamDirec[i].X > m_rcDrawCam.right )
				m_rcDrawCam.right = m_arrCurScrPtCamDirec[i].X;

			if(m_arrCurScrPtCamDirec[i].Y < m_rcDrawCam.top )
				m_rcDrawCam.top = m_arrCurScrPtCamDirec[i].Y;

			if(m_arrCurScrPtCamDirec[i].Y > m_rcDrawCam.bottom )
				m_rcDrawCam.bottom = m_arrCurScrPtCamDirec[i].Y;
		}

		m_rcDrawCam.left	-=m_iCamDispSize;
		m_rcDrawCam.right	+=m_iCamDispSize;
		m_rcDrawCam.top		-=m_iCamDispSize;
		m_rcDrawCam.bottom	+=m_iCamDispSize;
		InvalidateRect(m_rcDrawCam, FALSE);
		//Invalidate();
	}	
#endif
	Invalidate(FALSE);
}
void CPictureShowView::SetTargetInfo(IPC_COORDINFO coordinfo)
{
	/*
	//이전 화면 지우기		
	ZeroMemory(&m_ptAbsTargetPixelApplyMag, sizeof(Point));	
	InvalidateRect(m_rcDrawTarget);
	//
*/

	m_ipc_targetinfo = coordinfo;

	CString strLatSec, strLongSec;

	strLatSec.Format(_T("%02d.%02d"), m_ipc_targetinfo.byLatSec, m_ipc_targetinfo.byLatSecFrac);
	double dLatDec = m_scaler.DMS2Deg(
		m_ipc_targetinfo.byLatDeg, m_ipc_targetinfo.byLatMin, atof(strLatSec) );

	strLongSec.Format(_T("%02d.%02d"), m_ipc_targetinfo.byLongSec, m_ipc_targetinfo.byLongSecFrac);
	double dLongDec = m_scaler.DMS2Deg(
		m_ipc_targetinfo.byLongDeg, m_ipc_targetinfo.byLongMin, atof(strLongSec) );

	
	CString strText;
	strText.Format(_T("위도(Lat) %02d도%02d분%s초 경도(Long) %03d도%02d분%s초"),
		m_ipc_targetinfo.byLatDeg, m_ipc_targetinfo.byLatMin, strLatSec,
		m_ipc_targetinfo.byLongDeg, m_ipc_targetinfo.byLongMin, strLongSec
		);
	m_dlgStatusCoord.GetDlgItem(IDC_STATIC_TARGETINFO)->SetWindowText(strText);

	CString strMgrs, strLat, strLong;
	strLat.Format(  _T("N %02d˚%02d\'%02d.%02d\""),
		(int)m_ipc_targetinfo.byLatDeg, (int)m_ipc_targetinfo.byLatMin, (int)m_ipc_targetinfo.byLatSec, (int)m_ipc_targetinfo.byLatSecFrac);
	strLong.Format( _T("E %03d˚%02d\'%02d.%02d\""),
		(int)m_ipc_targetinfo.byLongDeg, (int)m_ipc_targetinfo.byLongMin, (int)m_ipc_targetinfo.byLongSec, (int)m_ipc_targetinfo.byLongSecFrac);

	// convert gps to mgrs : (N 00˚59'59.99"), (E 000˚59'59.99")
	Util_ConvGPStoMGRS( strMgrs, strLat, strLong);

	strText.Format( "군사좌표(MGRS) %s %s %s", strMgrs.Left(5), strMgrs.Mid(5, 5), strMgrs.Right(5) );
	m_dlgStatusCoord.GetDlgItem(IDC_STATIC_TARGETINFO_MGRS)->SetWindowText(strText);

	double dTmX=0, dTmY=0;
	m_scaler.Deg2Tm(dLatDec, dLongDec, dTmX, dTmY);

	//타겟 위치좌표를 비트맵 절대 좌표로
	m_scaler.WorldToDevice(dTmX, dTmY, m_ptAbsTargetPixel.X, m_ptAbsTargetPixel.Y );

	//축척에 따른 픽셀 계산
	if(m_Magnify >= 0) // Magnify Or Set Original Picture Dimentions
	{
		//기본 배율
		m_ptAbsTargetPixelApplyMag.X = m_ptAbsTargetPixel.X + m_DeltaX;
		m_ptAbsTargetPixelApplyMag.Y = m_ptAbsTargetPixel.Y + m_DeltaY;
	
	}
	else // Diminish Picture Dimentions
	{
		int iCalcedMag	= abs(m_Magnify-1);//yeun 

		//절대좌표에 현재 축척 적용
		m_ptAbsTargetPixelApplyMag.X = (m_ptAbsTargetPixel.X / iCalcedMag) + m_DeltaX;
		m_ptAbsTargetPixelApplyMag.Y = (m_ptAbsTargetPixel.Y / iCalcedMag) + m_DeltaY;		
	}
#if 0
	//절대좌표를 현재 화면상 스크린 좌표로
	if(AbsToScr(m_ptAbsTargetPixel.X, m_ptAbsTargetPixel.Y, m_ptCurScrTargetPixel.X, m_ptCurScrTargetPixel.Y))
	{
		//이미지 갱신 하고자 하는 렉트계산		
		m_rcDrawTarget.left		= m_ptCurScrTargetPixel.X-m_iCamDispSize;
		m_rcDrawTarget.right	= m_ptCurScrTargetPixel.X+m_iCamDispSize;
		m_rcDrawTarget.top		= m_ptCurScrTargetPixel.Y-m_iCamDispSize;
		m_rcDrawTarget.bottom	= m_ptCurScrTargetPixel.Y+m_iCamDispSize;

		//현재 이미지를 그리고자 하는 위치만 갱신한다.
		InvalidateRect(m_rcDrawTarget, FALSE);
	}	
#endif
	Invalidate(FALSE);
}
BOOL CPictureShowView::AbsToScr(int iAbsX, int iAbsY, int &iScrX, int &iScrY)
{
	int iScrollPosX = GetScrollPosition().x;
	int iScrollPosY = GetScrollPosition().y;

	CRect rc;
	GetClientRect(rc);	

	
	CRect rcCurScr;
	rcCurScr.left	= iScrollPosX;
	rcCurScr.right	= rc.Width() + iScrollPosX;
	rcCurScr.top	= iScrollPosY;
	rcCurScr.bottom	= rc.Height() + iScrollPosY;

	CRect rcAbsScr;
	rcAbsScr = rcCurScr;

	int iCalcedMag=1;
	if(m_Magnify >= 0) // Magnify Or Set Original Picture Dimentions
	{

	}
	else // Diminish Picture Dimentions
	{	
		iCalcedMag	= abs(m_Magnify-1);//yeun 
		
		//현재 화면좌표를 절대 좌표로 바꾸기
		rcAbsScr.left	= (rcCurScr.left-m_DeltaX)	* iCalcedMag;
		rcAbsScr.right	= (rcCurScr.right-m_DeltaX)	* iCalcedMag;		

		rcAbsScr.top		= (rcCurScr.top-m_DeltaY)	* iCalcedMag;
		rcAbsScr.bottom	= (rcCurScr.bottom-m_DeltaY) * iCalcedMag;
	}
	//화면에 1000픽셀 넘어가는 것은 그리기위해서 범위를 넉넉히 잡는다.
/*
	rcAbsMapScr.left-=1000;
	rcAbsMapScr.right+=1000;
	rcAbsMapScr.top-=1000;
	rcAbsMapScr.bottom+=1000;
*/
	//카메라 위치가 현재 화면 범위 내에 있는지 확인
	if(
		rcAbsScr.left-1000		<= iAbsX &&
		rcAbsScr.right+1000		>= iAbsX &&
		rcAbsScr.top-1000		<= iAbsY &&
		rcAbsScr.bottom+1000	>= iAbsY
		)
	{		
		int iDrawPointX = iAbsX - rcAbsScr.left;
		int iDrawPointY = iAbsY - rcAbsScr.top;

		//절대 좌표 -> 클라이언트 스크린 좌표
		iScrX = iDrawPointX/iCalcedMag;
		iScrY = iDrawPointY/iCalcedMag;
		return TRUE;
	}
	else
		return FALSE;

	return FALSE;
}
void CPictureShowView::CamPosInfoTo5Point(double dTmCamX, double dTmCamY, float fPan, float fFovW, int iDistance, DOUBLEPOINT * pArr)
{

	float fLeftFOV  = fPan - (fFovW/2);
	float fRightFOV = fPan + (fFovW/2);

	double x1=0, y1=0;	
	double x2=0, y2=0;	
	double x3=0, y3=0;

	if( iDistance == 0 )
		iDistance = 1000;

	//우측화각반
	m_scaler.CamInfoToTargetInfo(dTmCamX, dTmCamY, fRightFOV, iDistance, x1, y1 );

	//좌측화각반
	m_scaler.CamInfoToTargetInfo(dTmCamX, dTmCamY, fLeftFOV, iDistance, x2, y2 );

	//중심선
	m_scaler.CamInfoToTargetInfo(dTmCamX, dTmCamY, fPan, iDistance, x3, y3 );

	pArr[0].x = dTmCamX;
	pArr[0].y = dTmCamY;

	pArr[1].x = x1;
	pArr[1].y = y1;

	pArr[2].x = x2;
	pArr[2].y = y2;

	pArr[3].x = dTmCamX;
	pArr[3].y = dTmCamY;
}
void CPictureShowView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default

	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CPictureShowView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default

	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}


// convert gps to mgrs : (N 00˚59'59.99"), (E 000˚59'59.99")
void CPictureShowView::Util_ConvGPStoMGRS(CString& mgrs, CString la, CString lo)
{
	char cLa, cLo;
	CString csD1, csB1, csC1;
	CString csD2, csB2, csC2;

	// Old
	
	cLa  = la.GetAt(0);
	csD1 = la.Mid( 2, 2);
	csB1 = la.Mid( 6, 2);
	csC1 = la.Mid( 9, 5);

	cLo = lo.GetAt(0);
	csD2 = lo.Mid( 2, 3);
	csB2 = lo.Mid( 7, 2);
	csC2 = lo.Mid(10, 5);
	
	//  [3/28/2014 Yeun]
	/*
	cLa  = la.GetAt(0);
	csD1 = la.Mid( 2, 2);
	csB1 = la.Mid( 5, 2);
	csC1 = la.Mid( 8, 5);

	cLo = lo.GetAt(0);
	csD2 = lo.Mid( 2, 3);
	csB2 = lo.Mid( 6, 2);
	csC2 = lo.Mid( 9, 5);
	*/

	double fLa = atof(csD1) + ((atof(csB1) * 60.0) + atof(csC1)) / 3600.0;
	double fLo = atof(csD2) + ((atof(csB2) * 60.0) + atof(csC2)) / 3600.0;

	fLa = (int)(fLa * 10000) / 10000.0;
	fLo = (int)(fLo * 10000) / 10000.0;

	if (cLa == 'S') fLa *= -1;
	if (cLo == 'W') fLo *= -1;

	double Latitude  = fLa * (PI / 180.0);
	double Longitude = fLo * (PI / 180.0);

	long Precision = 5;	// 정밀도
	char MGRS[256] = {0};
	long l = Convert_Geodetic_To_MGRS(Latitude, Longitude, Precision, MGRS);
	ASSERT(l == MGRS_NO_ERROR);

	mgrs = MGRS;	
}



void CPictureShowView::OnMove(int x, int y)
{
	CScrollView::OnMove(x, y);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

}

void CPictureShowView::OnMoving(UINT fwSide, LPRECT pRect)
{
	CScrollView::OnMoving(fwSide, pRect);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.		
}
void CPictureShowView::LoadMapFile()
{
	CPictureShowDoc* pDoc = GetDocument();

	//m_FitToScreen = FALSE;

	if(pDoc->m_Picture.Load(pDoc->m_strMapPathName)) // Load Picture Succeeded
	{			
		//OnOptionsFitborderstopicture();
		//Invalidate(TRUE);
	}
	else // Load Picture Failed
	{
		CString strMsg;
		strMsg.Format( _T("%s 파일을 불러 올 수 없습니다."), pDoc->m_strMapPathName );
		AfxMessageBox( strMsg );
		return;
	}

	//맵파일과 같은 이름으로 맵정보 파일 읽어오기
	int iFound = pDoc->m_strMapPathName.Find(".jpg");
	CString strFileName = pDoc->m_strMapPathName.Mid(0, iFound+1);
	strFileName.Insert(iFound+1, _T("ini"));

	//실제 파일이 있는지 찾아본다.
	CFileFind find;
	BOOL bFind = find.FindFile( strFileName );
	if(!bFind)
	{
		int iErr = GetLastError();
		CString strMsg;
		strMsg.Format( _T("%s 파일이 없습니다. 지도 정보를 입력하세요"), strFileName );
		AfxMessageBox( strMsg );			
	}


	//
	CSize sizeTotal;
	sizeTotal.cx = pDoc->m_Picture.m_Width;
	sizeTotal.cy = pDoc->m_Picture.m_Height;
	SetScrollSizes(MM_TEXT, sizeTotal);

	//yeun add
	CRect rcMapPixel;
	rcMapPixel.left = 0;
	rcMapPixel.top = 0;
	rcMapPixel.right = pDoc->m_Picture.m_Width;
	rcMapPixel.bottom = pDoc->m_Picture.m_Height;
	m_scaler.SetRectMapPixel(rcMapPixel);

	COptMapInfo opt(strFileName);

	double dDegLat = m_scaler.DMS2Deg(opt.m_s.RefPoint1.iLatDeg, opt.m_s.RefPoint1.iLatMin, opt.m_s.RefPoint1.dLatSec);
	double dDegLong = m_scaler.DMS2Deg(opt.m_s.RefPoint1.iLongDeg, opt.m_s.RefPoint1.iLongMin, opt.m_s.RefPoint1.dLongSec);

	if( (dDegLat <= 0) || (dDegLong <= 0) )
	{

	}
	else
	{
		m_scaler.SetRefPoint(1, dDegLat, dDegLong, opt.m_s.RefPoint1.iRefPointPixelX, opt.m_s.RefPoint1.iRefPointPixelY);

		dDegLat = m_scaler.DMS2Deg(opt.m_s.RefPoint2.iLatDeg, opt.m_s.RefPoint2.iLatMin, opt.m_s.RefPoint2.dLatSec);
		dDegLong = m_scaler.DMS2Deg(opt.m_s.RefPoint2.iLongDeg, opt.m_s.RefPoint2.iLongMin, opt.m_s.RefPoint2.dLongSec);
		m_scaler.SetRefPoint(2, dDegLat, dDegLong, opt.m_s.RefPoint2.iRefPointPixelX, opt.m_s.RefPoint2.iRefPointPixelY);
	}

	m_optCommonInfo.Write();//StevenYeun 170404
}

BOOL CPictureShowView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if( m_bPenMode )
	{
		SetCursor( m_hPenCursor );
	}
	else
	{
		SetCursor( m_hStdCursor );
	}
	//  [3/28/2014 Yeun] return CScrollView::OnSetCursor(pWnd, nHitTest, message);

	return TRUE;
}
void CPictureShowView::MouseCurPosToScrolledPos( CPoint mousePoint, int& iAbsX, int& iAbsY )
{
	int iScrollPosX = GetScrollPosition().x;
	int iScrollPosY = GetScrollPosition().y;

	iAbsX = iScrollPosX + mousePoint.x;
	iAbsY = iScrollPosY + mousePoint.y;
}

void CPictureShowView::ScrolledToImageAbsPos( int iMouseAbsX, int iMouseAbsY, Point &point )
{
	int OrgX=0, OrgY=0;

	if(m_Magnify >= 0) // Magnify Or Set Original Picture Dimentions
	{

		int iCalcedMag = (m_Magnify+1)-2;//yeun

		// Calculate New Dimentions For ScrollView
		//point. = pDoc->m_Picture.m_Width*
		//m_ScrollSizeTotal.cy = pDoc->m_Picture.m_Height*(m_Magnify+1)-2;

		point.X = iMouseAbsX;
		point.Y = iMouseAbsY;
	}
	else // Diminish Picture Dimentions
	{
		int iCalcedMag	= abs(m_Magnify-1);//yeun 

		point.X = (iMouseAbsX-m_DeltaX) * iCalcedMag;
		point.Y = (iMouseAbsY-m_DeltaY) * iCalcedMag;			
	}	
}
void CPictureShowView::ImageAbsPosToScaledPos( const Point &ImgAbsPos, Point &ScaledPos )
{
	//축척에 따른 픽셀 계산
	if(m_Magnify >= 0) // Magnify Or Set Original Picture Dimentions
	{
		//기본 배율
		ScaledPos.X = ImgAbsPos.X + m_DeltaX;
		ScaledPos.Y = ImgAbsPos.Y + m_DeltaY;	
	}
	else // Diminish Picture Dimentions
	{
		int iCalcedMag	= abs(m_Magnify-1);//yeun 

		//절대좌표에 현재 축척 적용
		ScaledPos.X = (ImgAbsPos.X / iCalcedMag) + m_DeltaX;
		ScaledPos.Y = (ImgAbsPos.Y / iCalcedMag) + m_DeltaY;		
	}
}
void CPictureShowView::OnLineSave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	int iNumOfPoint = m_vecTempPointsOfLines.size();//임시로 그려진 라인의 포인트 개수를 구한다.
	if( iNumOfPoint > 0 )
	{
		//  [3/13/2014 Yeun]
		// 임시로 그린 선을 현재 파일에 추가한다.
		if( m_pFileDrawingInfo == NULL || m_pFileDrawingInfo->GetFileName().GetLength() == 0 )//파일이 처음 만들어지는거니
		{
			SAFE_DELETE(m_pFileDrawingInfo);
			m_pFileDrawingInfo = new CFileDrawingInfo( GetDocument()->m_strMapPath );
			if( m_pFileDrawingInfo->CreateNewFile() == FALSE)
				return;			
		}
		
		//  [3/12/2014 Yeun] 현재 임시로 그려진 선들의 점을  2차원 벡터로 저장한다.
		vector<STYLISH_POINT> vecTempPoint;//포인트벡터

		m_vecTempPointsOfLines[ iNumOfPoint-1 ].bRowEnd = TRUE;		
		m_pFileDrawingInfo->AddVectorInfo( m_vecTempPointsOfLines );

		m_vec2dPointsOfLines.push_back( m_vecTempPointsOfLines );
		m_vecTempPointsOfLines.clear();
		Invalidate(FALSE);
	}
}

void CPictureShowView::OnButtonDrawingLoad()
{
	if( m_pFileDrawingInfo == NULL)
		m_pFileDrawingInfo = new CFileDrawingInfo( GetDocument()->m_strMapPath );


	m_vec2dPointsOfLines = m_pFileDrawingInfo->LoadFileInfo();

	Invalidate(FALSE);
}

void CPictureShowView::OnButtonStyleSetup()
{
	m_dlgDrawingStyleConfig.ShowWindow(SW_SHOW);
}
void CPictureShowView::OnLineUndo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	DoUndoLine();
}
void CPictureShowView::OnShowRuler()
{
	m_bShowRuler = !m_bShowRuler;
}
void CPictureShowView::DoUndoLine( BOOL bAll /*= FALSE*/ )
{
	int iNumOfEle = m_vecTempPointsOfLines.size();

	if( iNumOfEle == 2)//첫 클릭 지점과 그다음 지점이 살아있다 이럴땐 둘다 지운다.
	{
		m_vecTempPointsOfLines.clear();
	}
	else if( iNumOfEle > 0 )
	{
		if( bAll )
			m_vecTempPointsOfLines.clear();
		else
			m_vecTempPointsOfLines.pop_back();
	}
	else
	{
		return;
	}

	//RedrawWindow();		
	Invalidate(FALSE);
}

void CPictureShowView::OnButtonNewDrawing()
{
	m_vec2dPointsOfLines.clear();
	SAFE_DELETE(m_pFileDrawingInfo);
	Invalidate(FALSE);

}

void CPictureShowView::OnButtonHiddenMenu()
{
	CRect rcDlg;
	m_dlgStatusCoord.GetClientRect(rcDlg);
	rcDlg.bottom+=100;
	m_dlgStatusCoord.MoveWindow( rcDlg );

}

void CPictureShowView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);//3D 효과를 없앤다.
}
LRESULT CPictureShowView::OnClientSocketPacketMsg(WPARAM wParam, LPARAM lParam)
{
	
	PACKET_LENGTH packet_len = *(PACKET_LENGTH*)lParam;
	int nCh = (int)wParam;

	if (packet_len.lpData[0] == PROTO_STX && packet_len.lpData[packet_len.nLen - 1] == PROTO_ETX)
	{
		AUTHORITY_PACKET * authPacket = (AUTHORITY_PACKET*)packet_len.lpData;

		//수신된 패킷을 스트링으로 변환하여 뿌려준다.
		CString strRecvedPacket = ConvertAuthorityPacketToString(authPacket);
		//this->m_dlgSetupAuthSvrConn.SetTextFromAuthServer(nCh, strRecvedPacket + _T("\r\n"));
		//////////////////////////////////////////////////////////////////////////////////////////////////////

		if (authPacket->byCmdGroup == CMDGROUP_AUTHORITY)//제어권한 관련 명령 처리
		{

			//ProcessCmdGroupAuthority(nCh, authPacket->byCmdType, authPacket->authorityData);
		}
		else//제어권한 명령 외 제어명령 처리
		{
			//제어권이 있는 클라이언트만 명령을 처리한다.
			//AUTHORITY_CLIENT_INFO authCliInfo;
			//authCliInfo.connectioninfo.dwIPAddr = packet_len.srcIPPort.dwIPAddr;
			//authCliInfo.connectioninfo.uPort = packet_len.srcIPPort.uPort;

			switch (authPacket->byCmdGroup)
			{
			case CMDGROUP_PTZCTRL:
				//ProcessCmdGroupPTZCtrl(nCh, authPacket->byCmdType);
				break;
			case CMDGROUP_PTZREQ:
				ProcessCmdGroupPTZReqResp(nCh, authPacket->byCmdType, authPacket->authorityData);
				break;
			case CMDGROUP_DAYCAM:
				break;
			case CMDGROUP_THERMCAM:
				break;
			case CMDGROUP_ETCFUNC:
				//ProcessCmdGroupETCFunc(nCh, authPacket->byCmdType, authPacket->authorityData);
				break;
			case CMDGROUP_ETC_DEVICE:
				break;
			//case CMDGROUP_ETC_LINK:
			//	break;
			}
		}

	}
	return LRESULT();
}

LRESULT CPictureShowView::OnClientSocketEventMsg(WPARAM wParam, LPARAM lParam)
{
	if (wParam == TO_AUTHORITY_SERVER_CONNECTION_COMPLETED)//서버에 접속이 되었음을 알림
	{
		//서버측으로 클라이언트의 정보를 보냄
		//SendToAuthorityServer((int)lParam, CMDGROUP_AUTHORITY, CMDTYPE_AUTHORITY_LOGIN);
	}

	return LRESULT();
}

void CPictureShowView::ProcessCmdGroupPTZReqResp(int nCh, BYTE byCmdType, AUTHORITY_DATA & authorityData)
{
	CString strData;
	switch (byCmdType)
	{
	case CMDTYPE_PTZREQ_PANTILT_POS_RESP:
	{
		strData = ParseAuthorityData2(authorityData);

		int iFind = strData.Find(_T(";"));
		double dPan = atof(strData.Left(iFind));
		double dTilt = atof(strData.Mid(iFind + 1));

		


		m_arrCaminfo[nCh-1].fPan = dPan;
	
		SetCamInfo(m_arrCaminfo[nCh - 1], nCh);

		//m_dlgPresetList.SetPanTiltOnUI(dPan, dTilt);
	}
	break;

	case CMDTYPE_PTZREQ_DAYZF_POS_RESP:
	{
		strData = ParseAuthorityData2(authorityData);

		int iFind = strData.Find(_T(","));
		int nFocus = atoi(strData.Left(iFind));
		int nZoom = atoi(strData.Mid(iFind + 1));

		//if (m_bArrAuthority[nCh - 1] == TRUE)
		//	m_dlgPresetList.SetZoomFocusOnUI(nZoom, nFocus);
	}
	break;
	default:
		break;
	}
}
LRESULT CPictureShowView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// 메시지 수신
	//if (message == this->message && (HWND)wParam != this->GetSafeHwnd())
	if (message == 867 && (HWND)wParam != this->GetSafeHwnd())//메세지번호가다르게옴.. 이상함
	{
		char buf[256];

		//sprintf_s(buf, "WPF Message : %d", lParam);

		CString str;
		str.Format(_T("%d"), lParam);
		//MessageBox(str);

		
		int nCh = m_dlgStatusCoord.GetSelectedCh();

		m_iniPTZEnvSetup.Read(nCh);
		
		
		m_dArrPanOffset[nCh - 1] = m_iniPTZEnvSetup.m_s.panOffset[nCh - 1];

		SetCamInfo(m_arrCaminfo[nCh - 1], nCh);

		//if (nCh == (int)lParam)
		//	UpdateStatusBar();
	}

	return CScrollView::WindowProc(message, wParam, lParam);
}