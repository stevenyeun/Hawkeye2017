// DlgStatusCoord.cpp : implementation file
//

#include "stdafx.h"
#include "PictureShow.h"
#include "DlgStatusCoord.h"


// CDlgStatusCoord dialog

IMPLEMENT_DYNAMIC(CDlgStatusCoord, CDialog)

CDlgStatusCoord::CDlgStatusCoord(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStatusCoord::IDD, pParent)
	, m_bChkTopDocking(FALSE)
	
{
	m_nRadioCh = 1;
}

CDlgStatusCoord::~CDlgStatusCoord()
{
	m_fontTitle.DeleteObject();
	m_fontText.DeleteObject();
}

void CDlgStatusCoord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_DOCKING_TOP, m_bChkTopDocking);
	//DDX_Radio(pDX, IDC_RADIO_CH1, m_nRadioCh);

}


BEGIN_MESSAGE_MAP(CDlgStatusCoord, CDialog)
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_CHECK_DOCKING_TOP, &CDlgStatusCoord::OnBnClickedCheckDockingTop)
	ON_WM_CTLCOLOR()
	//ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_CH1, IDC_RADIO_CH5, CDlgStatusCoord::OnRadioChClicked)

	ON_BN_CLICKED(IDC_RADIO_CH1, &CDlgStatusCoord::OnBnClickedRadioCh1)
	ON_BN_CLICKED(IDC_RADIO_CH2, &CDlgStatusCoord::OnBnClickedRadioCh2)
	ON_BN_CLICKED(IDC_RADIO_CH3, &CDlgStatusCoord::OnBnClickedRadioCh3)
	ON_BN_CLICKED(IDC_RADIO_CH4, &CDlgStatusCoord::OnBnClickedRadioCh4)
	ON_BN_CLICKED(IDC_RADIO_CH5, &CDlgStatusCoord::OnBnClickedRadioCh5)
END_MESSAGE_MAP()


// CDlgStatusCoord message handlers
void CDlgStatusCoord::OnRadioChClicked(UINT value)
{
	UpdateData(TRUE); 
	/*
	switch (m_nRadioCh)
	{
	case 0:
		break;

	case 1:
		break;

	case 2:
		break;
	}
	*/
}
LRESULT CDlgStatusCoord::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
	//캡션바 없이 이동
#if 0
	UINT nHitTest = CDialog::OnNcHitTest(point);
	return(nHitTest == HTCLIENT)?HTCAPTION : nHitTest;
#endif
	return CDialog::OnNcHitTest(point);
}

BOOL CDlgStatusCoord::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	GetClientRect(m_rcDefaultDlgSize);

	m_fontText.CreatePointFont(79, "맑은 고딕");

	VERIFY(m_fontTitle.CreateFont(
		14,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapementf
		0,                         // nOrientation
		FW_BOLD,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"맑은 고딕"));                 // lpszFacename

#if 0
	GetDlgItem(IDC_RADIO_CH1)->SetFont(&m_fontText);
	GetDlgItem(IDC_RADIO_CH2)->SetFont(&m_fontText);
	GetDlgItem(IDC_RADIO_CH3)->SetFont(&m_fontText);
	GetDlgItem(IDC_RADIO_CH4)->SetFont(&m_fontText);
	GetDlgItem(IDC_RADIO_CH5)->SetFont(&m_fontText);
#endif


	GetDlgItem(IDC_STATIC_DMS)->SetFont(&m_fontText);
	GetDlgItem(IDC_STATIC_MGRS)->SetFont(&m_fontText);

	GetDlgItem(IDC_STATIC_CAMPOS)->SetFont(&m_fontText);
	GetDlgItem(IDC_STATIC_CAMPOS_MGRS)->SetFont(&m_fontText);

	GetDlgItem(IDC_STATIC_CAMINFO)->SetFont(&m_fontText);
	

	GetDlgItem(IDC_STATIC_TARGETINFO)->SetFont(&m_fontText);
	GetDlgItem(IDC_STATIC_TARGETINFO_MGRS)->SetFont(&m_fontText);
	GetDlgItem(IDC_STATIC_MAGNIFY)->SetFont(&m_fontText);

	GetDlgItem(IDC_STATIC_1)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC_1)->SetWindowText("마우스 좌표");

	GetDlgItem(IDC_STATIC_2)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC_2)->SetWindowText("카메라 좌표");

	GetDlgItem(IDC_STATIC_3)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC_3)->SetWindowText("표적 좌표");	

	m_bChkTopDocking=TRUE;
	
	((CButton*)GetDlgItem(IDC_RADIO_CH1))->SetCheck(1);
	UpdateData(FALSE);



	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgStatusCoord::OnBnClickedCheckDockingTop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
}


HBRUSH CDlgStatusCoord::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(WHITE_SMOKE);
		
		return m_brBlack;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return m_brBlack;
}

#include "MainFrm.h"
#include "PictureShow.h"

#include "PictureShowDoc.h"
#include "PictureShowView.h"
void CDlgStatusCoord::OnBnClickedRadioCh1()
{
	// TODO: Add your control notification handler code here
	m_nRadioCh = 1;
	
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->GetMainWnd();

	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();

	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();

	// Get the active view attached to the active MDI child window.
	CPictureShowView *pView = (CPictureShowView*)pChild->GetActiveView();
	pView->SetCamInfo();

	//((CPictureShowView*)GetActiveView())->SetCamInfo(caminfo);
}


void CDlgStatusCoord::OnBnClickedRadioCh2()
{
	// TODO: Add your control notification handler code here
	m_nRadioCh = 2;

	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->GetMainWnd();

	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();

	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();

	// Get the active view attached to the active MDI child window.
	CPictureShowView *pView = (CPictureShowView*)pChild->GetActiveView();
	pView->SetCamInfo();
}


void CDlgStatusCoord::OnBnClickedRadioCh3()
{
	// TODO: Add your control notification handler code here
	m_nRadioCh = 3;

	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->GetMainWnd();

	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();

	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();

	// Get the active view attached to the active MDI child window.
	CPictureShowView *pView = (CPictureShowView*)pChild->GetActiveView();
	pView->SetCamInfo();
}


void CDlgStatusCoord::OnBnClickedRadioCh4()
{
	// TODO: Add your control notification handler code here
	m_nRadioCh = 4;
	
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->GetMainWnd();

	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();

	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();

	// Get the active view attached to the active MDI child window.
	CPictureShowView *pView = (CPictureShowView*)pChild->GetActiveView();
	pView->SetCamInfo();
}


void CDlgStatusCoord::OnBnClickedRadioCh5()
{
	// TODO: Add your control notification handler code here
	m_nRadioCh = 5;

	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->GetMainWnd();

	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();

	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();

	// Get the active view attached to the active MDI child window.
	CPictureShowView *pView = (CPictureShowView*)pChild->GetActiveView();
	pView->SetCamInfo();
}
