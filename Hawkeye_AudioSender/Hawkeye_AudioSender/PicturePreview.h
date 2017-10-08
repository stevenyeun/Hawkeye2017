#if !defined(AFX_PICTUREPREVIEW_H__E2C31EB7_D817_401F_AA10_E0B7D2093FEC__INCLUDED_)
#define AFX_PICTUREPREVIEW_H__E2C31EB7_D817_401F_AA10_E0B7D2093FEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PicturePreview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPicturePreview dialog

class CPicturePreview : public CDialog
{
// Construction
	CStatic   m_image;
	HBITMAP m_bitmap;

public:
	CPicturePreview(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPicturePreview();

	HRESULT SetBMP(LPTSTR filename);

// Dialog Data
	//{{AFX_DATA(CPicturePreview)
	enum { IDD = IDD_DIALOG_PREVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_MSG(CPicturePreview)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnDestroy();
	//}}AFX_MSG

// Implementation
protected:
	class CBasicDlg	*m_pdlgMain;
public:
	BOOL Create(class CBasicDlg* pdlgMain) ;
//protected:

	// Generated message map functions
	//{{AFX_MSG(CPicturePreview)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICTUREPREVIEW_H__E2C31EB7_D817_401F_AA10_E0B7D2093FEC__INCLUDED_)
