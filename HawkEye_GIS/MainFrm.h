// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__136DA222_B558_415A_9C9F_AC4244827060__INCLUDED_)
#define AFX_MAINFRM_H__136DA222_B558_415A_9C9F_AC4244827060__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
protected:
	CWnd m_wndInvisible;
	
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	BOOL m_FullScreen;
	CToolBar		*m_pWndFullScreenBar;
	WINDOWPLACEMENT  m_WPPrev;
    CRect			 m_FullScreenWindowRect;

public:  // control bar embedded members
	CStatusBar  m_WndStatusBar;
	CToolBar    m_WndToolBar;
	void MoveDlgStatusCoord();
	void UpdateDlgStatus();
// Generated message map functions
public:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnOptionsFullscreen();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnButtonFullscreen();
	afx_msg void OnButtonFullscreenFloat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	
	afx_msg void OnMove(int x, int y);
	afx_msg void OnChangeUIState(UINT nAction, UINT nUIElement);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__136DA222_B558_415A_9C9F_AC4244827060__INCLUDED_)
