#if !defined(AFX_ASSOCIATIONSDLG_H__C5EE3031_8FDC_11D5_99EF_00C02611782C__INCLUDED_)
#define AFX_ASSOCIATIONSDLG_H__C5EE3031_8FDC_11D5_99EF_00C02611782C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AssociationsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAssociationsDlg dialog

class CAssociationsDlg : public CDialog
{
// Construction
public:
	BOOL AllChecked();
	CAssociationsDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL RegExterminateKey(HKEY hKey, LPCTSTR SubKey, LPCTSTR Value);

// Dialog Data
	//{{AFX_DATA(CAssociationsDlg)
	enum { IDD = IDD_ASSOCIATIONS };
	BOOL	m_AssociateALL;
	BOOL	m_AssociateBMP;
	BOOL	m_AssociateDIB;
	BOOL	m_AssociateEMF;
	BOOL	m_AssociateGIF;
	BOOL	m_AssociateICO;
	BOOL	m_AssociateJPG;
	BOOL	m_AssociateWMF;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAssociationsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAssociationsDlg)
	afx_msg void OnButtonAssociate();
	afx_msg void OnButtonClear();
	afx_msg void OnCheckAll();
	afx_msg void OnCheckBmp();
	afx_msg void OnCheckDib();
	afx_msg void OnCheckEmf();
	afx_msg void OnCheckGif();
	afx_msg void OnCheckIco();
	afx_msg void OnCheckJpg();
	afx_msg void OnCheckWmf();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASSOCIATIONSDLG_H__C5EE3031_8FDC_11D5_99EF_00C02611782C__INCLUDED_)
