// PictureShowDoc.h : interface of the CPictureShowDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICTURESHOWDOC_H__E62121DE_C885_46F0_A23C_F8BBD6313FB5__INCLUDED_)
#define AFX_PICTURESHOWDOC_H__E62121DE_C885_46F0_A23C_F8BBD6313FB5__INCLUDED_

#include "Picture.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPictureShowDoc : public CDocument
{
protected: // create from serialization only
	CPictureShowDoc();
	DECLARE_DYNCREATE(CPictureShowDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPictureShowDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL IsWantedExtention(CString sExtention);
	CString FileExtentionOnly(CString sFilePathName);
	CString FileNameOnly(CString sFilePathName);
	BOOL CreateFilesList();

	CPicture m_Picture;

	//  [3/29/2014 Yeun]	
	CString m_strMapPathName;
	CString m_strMapPath;
	//


	CFileFind   m_Finder;
	int         m_Finding;

	CStringList m_FilesList;
	int			m_FilesListCount;
	int			m_FilesListPos;
	POSITION    m_FilesListPosition;

	virtual ~CPictureShowDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPictureShowDoc)
	afx_msg void OnFileOpen();
	afx_msg void OnFileSaveAs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICTURESHOWDOC_H__E62121DE_C885_46F0_A23C_F8BBD6313FB5__INCLUDED_)
