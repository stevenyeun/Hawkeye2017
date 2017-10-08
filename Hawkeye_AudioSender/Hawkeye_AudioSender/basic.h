// basic.h : main header file for the BASIC application
//

#if !defined(AFX_BASIC_H__42D5EBAC_3AFF_42D5_B35A_91F9251C26B5__INCLUDED_)
#define AFX_BASIC_H__42D5EBAC_3AFF_42D5_B35A_91F9251C26B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBasicApp:
// See basic.cpp for the implementation of this class
//

class CBasicApp : public CWinApp
{
public:
	CBasicApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBasicApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBasicApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASIC_H__42D5EBAC_3AFF_42D5_B35A_91F9251C26B5__INCLUDED_)
