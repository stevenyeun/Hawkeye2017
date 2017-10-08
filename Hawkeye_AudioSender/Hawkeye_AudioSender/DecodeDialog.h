//{{AFX_INCLUDES()
#include "tvsdecodecontrol.h"
//}}AFX_INCLUDES
#if !defined(AFX_DECODEDIALOG_H__6FA7E4B1_F8EC_4E54_A010_BE5B7C2D7A5D__INCLUDED_)
#define AFX_DECODEDIALOG_H__6FA7E4B1_F8EC_4E54_A010_BE5B7C2D7A5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DecodeDialog.h : header file
//
#include <atlbase.h>
#include ".\idl\_cunk.h"
#include "tvsdisplay.h"
#include ".\idl\tvs.h"
#include <objbase.h>
#include "cthr.hpp"

#define BUF_SIZE (1*1024*1024)

/////////////////////////////////////////////////////////////////////////////
// CDecodeDialog dialog

class CDecodeDialog : public CDialog
					,public CUnk
					,public ITVSDecodeCallback
					,public CThread
					
{
	int m_nTimerID;

	char *m_bFrame;
	FILE *m_fh;
	int m_nReadCount;

	HANDLE m_hevDecodeStop;

	ULONG m_prev_pts;


// Construction
public:
	long m_lChID;

	CDecodeDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDecodeDialog();

	BOOL IsStarted(){return (m_lChID != 0);};

	HRESULT StartDecode();
	HRESULT StopDecode();

// Dialog Data
	//{{AFX_DATA(CDecodeDialog)
	enum { IDD = IDD_DIALOG_DECODE };
	CTVSDecodeControl	m_tvsdecode;
	//}}AFX_DATA

	int m_nDecFrmIdx;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDecodeDialog)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	class CBasicDlg	*m_pdlgMain;

public:
	BOOL Create(class CBasicDlg* pdlgMain);

	//decode routine
	DWORD Proc();



    ULONG STDMETHODCALLTYPE AddRef( void){return CUnk::AddRef();};
	ULONG STDMETHODCALLTYPE Release( void){return CUnk::Release();};
	STDMETHOD(QueryInterface)(/* [in] */ REFIID riid,
		/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject)
	{
		if(riid == IID_ITVSDecodeCallback){
			*ppvObject = (ITVSDecodeCallback *)this;
			CUnk::AddRef();
			return S_OK;
		}
		return CUnk::QueryInterface(riid, ppvObject);
	}

	STDMETHOD(OnDataReceive)( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT vData,
            /* [in] */ long lError);


	// Generated message map functions
	//{{AFX_MSG(CDecodeDialog)
	afx_msg void OnDataEventTvsdecodecontrol1(long lChID, const VARIANT FAR& vData, long lError);
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDecodeDialog)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DECODEDIALOG_H__6FA7E4B1_F8EC_4E54_A010_BE5B7C2D7A5D__INCLUDED_)
