// PictureShowView.h : interface of the CPictureShowView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICTURESHOWVIEW_H__4C81406C_4468_482C_BABE_53F0AB916641__INCLUDED_)
#define AFX_PICTURESHOWVIEW_H__4C81406C_4468_482C_BABE_53F0AB916641__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//yeun
#include "DlgStatusCoord.h"
#include "SourceLIB/GISUtil/Scaler.h"

#include "IPCdefine.h"
#include <atlimage.h>

#include "IniPTZEnvSetup.h"


typedef struct _DOUBLEPOINT
{
	double  x;
	double  y;
}DOUBLEPOINT;

#define POINT_NUM 4



#include "FileDrawingInfo.h"//  [3/29/2014 Yeun]
#include "DlgDrawingStyleConfig.h"//  [3/29/2014 Yeun]
#include "ClientSocketAuthority.h"//Steven 170404

class CPictureShowView : public CScrollView
{
protected:		
	Scaler			m_scaler;


	IPC_CAMINFO m_ipc_caminfo;	
	IPC_COORDINFO m_ipc_targetinfo;

	//ī�޶� ���밪 �ȼ� ��ġ
	int m_iAbsCamPixelX;//StevenYeun 5ä�η� ���� �ؾ���
	int m_iAbsCamPixelY;
	//
	//���밪�� ���� ������ ��ġ
	int m_iAbsCamPixelApplyMagX;
	int m_iAbsCamPixelApplyMagY;
	//	
	//���밪�� ���� ��ũ����ġ�� �ٲ۰�
	int m_iCurScrCamPixelX;
	int m_iCurScrCamPixelY;
	//	

	//////////////////////////////////////////////////////////////
	//ä�� ����
	IPC_CAMINFO m_arrCaminfo[MAX_CHANNEL_NUM];//����� ������ �ִٰ� �ʿ��� ������ ������Ʈ�ؼ� ���
	IPC_COORDINFO m_arrTargetinfo[MAX_CHANNEL_NUM];
	//ī�޶� ���밪 �ȼ� ��ġ
	int m_iArrAbsCamPixelX[MAX_CHANNEL_NUM] = { 0, };//StevenYeun 5ä�η� ���� �ؾ���
	int m_iArrAbsCamPixelY[MAX_CHANNEL_NUM] = { 0, };
	//
	//���밪�� ���� ������ ��ġ
	int m_iArrAbsCamPixelApplyMagX[MAX_CHANNEL_NUM] = { 0, };
	int m_iArrAbsCamPixelApplyMagY[MAX_CHANNEL_NUM] = { 0, };	
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////


	//ī�޶� ���� �� ȭ�� ǥ��
	//DOUBLEPOINT m_arrTmPtCamDirec[POINT_NUM];	
	Point		m_arrAbsPtCamDirec[POINT_NUM];	
		
	Point		m_arrAbsPtCamDirecApplyMag[POINT_NUM];
	Point		m_arrCurScrPtCamDirec[POINT_NUM];

	//////////////////////////////////////////////////////////////
	//ä�� ����
	Point		m_arrAbsPtArrCamDirecApplyMag[MAX_CHANNEL_NUM][POINT_NUM];
	//Point		m_arrCurScrPtCamDirec[POINT_NUM];

	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////



	
	//ǥ�� ��ġ
	Point m_ptAbsTargetPixel;	
	//
	//���밪�� ���� ������ ��ġ
	Point m_ptAbsTargetPixelApplyMag;	
	//	
	//���밪�� ���� ��ũ����ġ�� �ٲ۰�
	Point m_ptCurScrTargetPixel;	
	//

	//-Yeun 140922
	BOOL m_bShowRuler;


	CRect m_rcDrawCam;
	CRect m_rcDrawTarget;

	unsigned int message;//20170430 stevenYeun
	int FloatToInt(float fNumber);
	CPoint GetCenterScrollPosition(void);
	BOOL AbsToScr(int iAbsX, int iAbsY, int &iScrX, int &iScrY);//���� ��ǥ�� ���� ��ũ�� ��ǥ��	
	void UpdateScreen();
	void CamPosInfoTo5Point(double dTmCamX, double dTmCamY, float fPan, float fFovW, int iDistance, DOUBLEPOINT * pArr);
	void Util_ConvGPStoMGRS(CString& mgrs, CString la, CString lo);

//  [3/28/2014 Yeun]
private:
	COptCommonInfo m_optCommonInfo;	
	CIniPTZEnvSetup m_iniPTZEnvSetup;
	double m_dArrPanOffset[MAX_CHANNEL_NUM] = { 0, };
	BOOL m_bPenMode;
	HCURSOR m_hStdCursor;
	HCURSOR m_hPenCursor;

	vector<STYLISH_POINT> m_vecTempPointsOfLines;//  [3/28/2014 Yeun] �ӽ������� �׸� ���� ���� �����ϴ� ����(�̹���������ǥ)

	//���������� ���� �̹��� ������ǥ ����
	vector<VEC_STYLISH_POINT> m_vec2dPointsOfLines;//������ ���� ȭ�鿡 �׷��� �� ��� ����
	CFileDrawingInfo * m_pFileDrawingInfo;

	CDlgDrawingStyleConfig m_dlgDrawingStyleConfig;//  [3/29/2014 Yeun]
	//////////////////////////////////////////////////////////////////////////
private:
	CClientSocketAuthority m_sockAuthorityClient;//Steven 170404 ����� Ŭ���̾�Ʈ ����
	afx_msg LRESULT OnClientSocketPacketMsg(WPARAM, LPARAM);
	afx_msg LRESULT OnClientSocketEventMsg(WPARAM, LPARAM);
	void ProcessCmdGroupPTZReqResp(int nCh, BYTE byCmdType, AUTHORITY_DATA& authorityData);

private:
	
	void DoUndoLine( BOOL bAll = FALSE );

	void MouseCurPosToScrolledPos( CPoint mousePoint, int& iAbsX, int& iAbsY );
	void ScrolledToImageAbsPos( int iMouseAbsX, int iMouseAbsY, Point &point );

	void ImageAbsPosToScaledPos( const Point &ImgAbsPos, Point &ScaledPos );//  [3/29/2014 Yeun]

//
protected:
	CImage m_ImgScreenBuf;
	void DrawMapInfo(CDC* pDC);
	void LoadMapFile();
public:
	CDlgStatusCoord m_dlgStatusCoord;
	void SetCamInfo();
	void SetCamInfo(IPC_CAMINFO caminfo);//ä�� ��ȣ�� ���� �� �ְ� ���� �ؾ���.
	void SetCamInfo(IPC_CAMINFO caminfo, int nCh);
	void SetTargetInfo(IPC_COORDINFO coordinfo);
	
protected: // create from serialization only
	CPictureShowView();
	DECLARE_DYNCREATE(CPictureShowView)

// Attributes
public:
	CPictureShowDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPictureShowView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	int     m_DeltaX;//ȭ�� �¿� ����
	int     m_DeltaY;//ȭ�� ���� ����

	int     m_OldCalcedMagnify;
	int     m_CalcedMagnify;

	int  m_Magnify;
	int     m_ScrollKeySpeed;

	bool    m_FitToScreen;
	bool	m_ViewFirst;
	bool	m_ViewForward;

	CString m_FileName;

	CRect   m_ClientRect;
	CSize   m_ScrollSizeTotal; // Set Scrollers According To Picture Dimentions
	CSize   m_OldScrollSizeTotal;//yeun

	virtual ~CPictureShowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPictureShowView)
	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnOptionsFittoscreen();
	afx_msg void OnUpdateOptionsFittoscreen(CCmdUI* pCmdUI);
	afx_msg void OnButtonMagnify();
	afx_msg void OnButtonDiminish();
	afx_msg void OnOptionsAssociatefileextentions();
	afx_msg void OnButtonFittoscreen();
	afx_msg void OnButtonPrev();
	afx_msg void OnButtonNext();

/*
	afx_msg void OnButtonMap1();
	afx_msg void OnButtonMap2();*/

	afx_msg void OnButtonMapOpen();
	afx_msg void OnButtonPen();
	afx_msg void OnButtonDrawingLoad();
	afx_msg void OnLineSave();
	afx_msg void OnButtonStyleSetup();
	afx_msg void OnButtonNewDrawing();
	afx_msg void OnButtonHiddenMenu();//  [4/14/2014 Yeun]

	afx_msg void OnUpdateButtonNext(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonPrev(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnHelpHomepage();
	afx_msg void OnOptionsFitborderstopicture();
	afx_msg void OnOptionsNextpicture();
	afx_msg void OnOptionsPreviouspicture();
	//}}AFX_MSG

	// Support The New Status Indicator (Must Be Outside The AFX Message MAP...)
	afx_msg void OnIndicatorInfo(CCmdUI *pCmdUI);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);

	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);


	afx_msg void OnLineUndo();
	afx_msg void OnShowRuler();
	
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};

#ifndef _DEBUG  // debug version in PictureShowView.cpp
inline CPictureShowDoc* CPictureShowView::GetDocument()
   { return (CPictureShowDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICTURESHOWVIEW_H__4C81406C_4468_482C_BABE_53F0AB916641__INCLUDED_)
