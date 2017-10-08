// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__1B1D8339_B69E_4B44_8E0F_C6C09F021FC5__INCLUDED_)
#define AFX_STDAFX_H__1B1D8339_B69E_4B44_8E0F_C6C09F021FC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1B1D8339_B69E_4B44_8E0F_C6C09F021FC5__INCLUDED_)


//yeun

#ifndef SAFE_DELETE
#define SAFE_DELETE(x)  { if (x) delete x; x = NULL; }
#endif

#if 1//GDI Plus include

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

#endif


//  [3/28/2014 Yeun]
using namespace std;
#include <vector>

typedef struct _PENSTYLE
{
	_PENSTYLE(void)
	{
		clr = RGB(0, 0, 0);
		uPenSize = 1;
		byOpacity = (int)255/2;
	}
	COLORREF clr;
	UINT uPenSize;
	BYTE byOpacity;

}PENSTYLE;

typedef struct _STYLISH_POINT
{
	_STYLISH_POINT(void)
	{
		ZeroMemory( &point, sizeof(Point) );
		ZeroMemory( &penStyle, sizeof(PENSTYLE) );
		bRowEnd=FALSE;
	}
	BOOL bRowEnd;
	Point point;
	PENSTYLE penStyle;

}STYLISH_POINT;

typedef vector<STYLISH_POINT> VEC_STYLISH_POINT;
typedef vector<VEC_STYLISH_POINT> VEC2D_STYLISH_POINT;

#define		WHITE_SMOKE			RGB(245, 245, 245)


#include <afxsock.h>            // MFC socket extensions