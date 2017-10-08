// PictureShow.h : main header file for the PICTURESHOW application
//

#if !defined(AFX_PICTURESHOW_H__85AC48B8_BAA3_40FF_ACF7_D2B4AF6A2532__INCLUDED_)
#define AFX_PICTURESHOW_H__85AC48B8_BAA3_40FF_ACF7_D2B4AF6A2532__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPictureShowApp:
// See PictureShow.cpp for the implementation of this class
//




class CGdiPlusStarter
{
private:
	ULONG_PTR m_gpToken;

public:
	bool m_bSuccess;
	CGdiPlusStarter() {
		GdiplusStartupInput gpsi;
		m_bSuccess=(GdiplusStartup(&m_gpToken,&gpsi,NULL) == Ok);
	}
	~CGdiPlusStarter() {
		GdiplusShutdown(m_gpToken);
	}
};

class CPictureShowApp : public CWinApp
{
public:
	CPictureShowApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPictureShowApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPictureShowApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICTURESHOW_H__85AC48B8_BAA3_40FF_ACF7_D2B4AF6A2532__INCLUDED_)
