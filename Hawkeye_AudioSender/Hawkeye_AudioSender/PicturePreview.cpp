// PicturePreview.cpp : implementation file
//

#include "stdafx.h"
#include "basic.h"
#include "PicturePreview.h"

#include "basicDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPicturePreview dialog


CPicturePreview::CPicturePreview(CWnd* pParent /*=NULL*/)
	: CDialog(CPicturePreview::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPicturePreview)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pdlgMain = NULL;

	m_bitmap = NULL;
}

CPicturePreview::~CPicturePreview()
{
	if(m_bitmap){
		DeleteObject(m_bitmap);
	}
	m_bitmap = NULL;
}

HRESULT CPicturePreview::SetBMP(LPTSTR filename)

{
	if(!filename) return E_INVALIDARG;
	
	//lstrcpy(m_szFileSave, filename);
	
	m_bitmap = (HBITMAP)LoadImage(NULL, filename, 
		IMAGE_BITMAP,
		0,0,
		LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	
	return (m_bitmap? S_OK : S_FALSE);
}



void CPicturePreview::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPicturePreview)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPicturePreview, CDialog)
	//{{AFX_MSG_MAP(CPicturePreview)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CPicturePreview::Create(CBasicDlg* pdlgMain) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pdlgMain = pdlgMain;
	
	return CDialog::Create(CPicturePreview::IDD, m_pdlgMain);
}

void CPicturePreview::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}



/////////////////////////////////////////////////////////////////////////////
// CPicturePreview message handlers

BOOL CPicturePreview::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_image.Attach(GetDlgItem(IDC_ST_IMAGE)->GetSafeHwnd());

	if(m_bitmap){
		m_image.SetBitmap(m_bitmap);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPicturePreview::DestroyWindow() 
{
	m_image.Detach();
	
	return CDialog::DestroyWindow();
}
