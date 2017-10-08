// DlgDrawingStyleConfig.cpp : implementation file
//

#include "stdafx.h"
#include "PictureShow.h"
#include "DlgDrawingStyleConfig.h"


// CDlgDrawingStyleConfig dialog

IMPLEMENT_DYNAMIC(CDlgDrawingStyleConfig, CDialog)

CDlgDrawingStyleConfig::CDlgDrawingStyleConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDrawingStyleConfig::IDD, pParent)
{

}

CDlgDrawingStyleConfig::~CDlgDrawingStyleConfig()
{
}

void CDlgDrawingStyleConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CDlgDrawingStyleConfig, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_HIDE, &CDlgDrawingStyleConfig::OnBnClickedButtonHide)
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_SETUP_CAMDIREC_COLOR_SEL, &CDlgDrawingStyleConfig::OnBnClickedSetupCamdirecColorSel)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_COMBO_CAMDIREC_SYMBOL, &CDlgDrawingStyleConfig::OnCbnSelchangeComboCamdirecSymbol)
	ON_CBN_SELCHANGE(IDC_COMBO_REFPOINT_SYMBOL, &CDlgDrawingStyleConfig::OnCbnSelchangeComboRefpointSymbol)
	ON_CBN_SELCHANGE(IDC_COMBO_TARGETPOINT_SYMBOL, &CDlgDrawingStyleConfig::OnCbnSelchangeComboTargetpointSymbol)
	ON_BN_CLICKED(IDC_SETUP_REFPOINT_COLOR_SEL, &CDlgDrawingStyleConfig::OnBnClickedSetupRefpointColorSel)
	ON_BN_CLICKED(IDC_SETUP_TARGETPOINT_COLOR_SEL, &CDlgDrawingStyleConfig::OnBnClickedSetupTargetpointColorSel)
	//ON_EN_CHANGE(IDC_EDIT_CAMDIREC_LINEWIDTH, &CDlgDrawingStyleConfig::OnEnChangeEditCamdirecLinewidth)
	ON_EN_CHANGE(IDC_EDIT_REFPOINT_LINEWIDTH, &CDlgDrawingStyleConfig::OnEnChangeEditRefpointLinewidth)
	ON_EN_CHANGE(IDC_EDIT_TARGETPOINT_LINEWIDTH, &CDlgDrawingStyleConfig::OnEnChangeEditTargetpointLinewidth)
	ON_EN_CHANGE(IDC_EDIT_CAMDIREC_SYMBOLSIZE, &CDlgDrawingStyleConfig::OnEnChangeEditCamdirecSize)
	ON_EN_CHANGE(IDC_EDIT_REFPOINT_SYMBOLSIZE, &CDlgDrawingStyleConfig::OnEnChangeEditRefpointSymbolsize)
	ON_EN_CHANGE(IDC_EDIT_TARGETPOINT_SYMBOLSIZE, &CDlgDrawingStyleConfig::OnEnChangeEditTargetpointSymbolsize)
	ON_BN_CLICKED(IDC_CHECK_REFPOINT_NUM, &CDlgDrawingStyleConfig::OnBnClickedCheckRefpointNum)
	ON_BN_CLICKED(IDC_SETUP_LINE_COLOR_SEL, &CDlgDrawingStyleConfig::OnBnClickedSetupLineColorSel)
	ON_EN_CHANGE(IDC_EDIT_LINE_LINEWIDTH, &CDlgDrawingStyleConfig::OnEnChangeEditLineLinewidth)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CDlgDrawingStyleConfig::OnBnClickedButtonApply)
	ON_EN_CHANGE(IDC_EDIT_CAMDIREC_OPACITY, &CDlgDrawingStyleConfig::OnEnChangeEditCamdirecOpacity)
	ON_EN_CHANGE(IDC_EDIT_TARGETPOINT_OPACITY, &CDlgDrawingStyleConfig::OnEnChangeEditTargetpointOpacity)
	ON_EN_CHANGE(IDC_EDIT_LINE_OPACITY, &CDlgDrawingStyleConfig::OnEnChangeEditLineOpacity)
	ON_CBN_SELCHANGE(IDC_COMBO_LINE_SYMBOL, &CDlgDrawingStyleConfig::OnCbnSelchangeComboLineSymbol)
END_MESSAGE_MAP()


// CDlgDrawingStyleConfig message handlers

BOOL CDlgDrawingStyleConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	
	//1
	((CComboBox*)GetDlgItem(IDC_COMBO_CAMDIREC_SYMBOL))->InsertString(0, _T("��"));
	//((CComboBox*)GetDlgItem(IDC_COMBO_CAMDIREC_SYMBOL))->InsertString(1, _T("�簢"));
	//((CComboBox*)GetDlgItem(IDC_COMBO_CAMDIREC_SYMBOL))->InsertString(2, _T("�ﰢ"));

	((CComboBox*)GetDlgItem(IDC_COMBO_CAMDIREC_SYMBOL))->SetCurSel( m_pOptCommon->m_s.CamDirecStyle.uSymbol-1 );

	CString strText;
	strText.Format(_T("%d"), m_pOptCommon->m_s.CamDirecStyle.uPenSize);
	//GetDlgItem(IDC_EDIT_CAMDIREC_LINEWIDTH)->SetWindowText( strText );
	strText.Format(_T("%d"), m_pOptCommon->m_s.CamDirecStyle.uSymbolSize);
	GetDlgItem(IDC_EDIT_CAMDIREC_SYMBOLSIZE)->SetWindowText( strText );
	strText.Format(_T("%d"), m_pOptCommon->m_s.CamDirecStyle.byOpacity);
	GetDlgItem(IDC_EDIT_CAMDIREC_OPACITY)->SetWindowText( strText );
	

	 

	//2
	((CComboBox*)GetDlgItem(IDC_COMBO_REFPOINT_SYMBOL))->InsertString(0, _T("��"));
	//((CComboBox*)GetDlgItem(IDC_COMBO_REFPOINT_SYMBOL))->InsertString(1, _T("�簢"));
	//((CComboBox*)GetDlgItem(IDC_COMBO_REFPOINT_SYMBOL))->InsertString(2, _T("�ﰢ"));
	
	((CComboBox*)GetDlgItem(IDC_COMBO_REFPOINT_SYMBOL))->SetCurSel( m_pOptCommon->m_s.RefPointStyle.uSymbol-1 );

	strText.Format(_T("%d"), m_pOptCommon->m_s.RefPointStyle.uPenSize);
	GetDlgItem(IDC_EDIT_REFPOINT_LINEWIDTH)->SetWindowText( strText );
	strText.Format(_T("%d"), m_pOptCommon->m_s.RefPointStyle.uSymbolSize);
	GetDlgItem(IDC_EDIT_REFPOINT_SYMBOLSIZE)->SetWindowText( strText );
	strText.Format(_T("%d"), m_pOptCommon->m_s.RefPointStyle.byOpacity);
	GetDlgItem(IDC_EDIT_REFPOINT_OPACITY)->SetWindowText( strText );


	//3
	((CComboBox*)GetDlgItem(IDC_COMBO_TARGETPOINT_SYMBOL))->InsertString(0, _T("��"));
	//((CComboBox*)GetDlgItem(IDC_COMBO_TARGETPOINT_SYMBOL))->InsertString(1, _T("�簢"));
	//((CComboBox*)GetDlgItem(IDC_COMBO_TARGETPOINT_SYMBOL))->InsertString(2, _T("�ﰢ"));

	((CComboBox*)GetDlgItem(IDC_COMBO_TARGETPOINT_SYMBOL))->SetCurSel( m_pOptCommon->m_s.TargetPointStyle.uSymbol-1 );

	strText.Format(_T("%d"), m_pOptCommon->m_s.TargetPointStyle.uPenSize);
	GetDlgItem(IDC_EDIT_TARGETPOINT_LINEWIDTH)->SetWindowText( strText );
	strText.Format(_T("%d"), m_pOptCommon->m_s.TargetPointStyle.uSymbolSize);
	GetDlgItem(IDC_EDIT_TARGETPOINT_SYMBOLSIZE)->SetWindowText( strText );
	strText.Format(_T("%d"), m_pOptCommon->m_s.TargetPointStyle.byOpacity);
	GetDlgItem(IDC_EDIT_TARGETPOINT_OPACITY)->SetWindowText( strText );


	((CButton*)GetDlgItem(IDC_CHECK_REFPOINT_NUM))->SetCheck(m_pOptCommon->m_s.RefPointStyle.bDispNum);


	//4
	((CComboBox*)GetDlgItem(IDC_COMBO_LINE_SYMBOL))->InsertString(0, _T("�⺻��"));
	//((CComboBox*)GetDlgItem(IDC_COMBO_LINE_SYMBOL))->InsertString(1, _T("����"));	

	((CComboBox*)GetDlgItem(IDC_COMBO_LINE_SYMBOL))->SetCurSel( m_pOptCommon->m_s.LineStyle.uSymbol-1 );

	strText.Format(_T("%d"), m_pOptCommon->m_s.LineStyle.uPenSize);
	GetDlgItem(IDC_EDIT_LINE_LINEWIDTH)->SetWindowText( strText );
	strText.Format(_T("%d"), m_pOptCommon->m_s.LineStyle.byOpacity);
	GetDlgItem(IDC_EDIT_LINE_OPACITY)->SetWindowText( strText );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDrawingStyleConfig::OnBnClickedButtonHide()
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
}

LRESULT CDlgDrawingStyleConfig::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//ĸ�ǹ� ���� �̵�
	UINT nHitTest = CDialog::OnNcHitTest(point);
	return(nHitTest == HTCLIENT)?HTCAPTION : nHitTest;
	//

	return CDialog::OnNcHitTest(point);
}

HBRUSH CDlgDrawingStyleConfig::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (pWnd->GetDlgCtrlID() == IDC_SETUP_CAMDIREC_COLOR)
	{
		pDC->SetBkMode(OPAQUE);
		pDC->SetBkColor(m_pOptCommon->m_s.CamDirecStyle.clr);
		pDC->SetTextColor(m_pOptCommon->m_s.CamDirecStyle.clr);
	}

	if (pWnd->GetDlgCtrlID() == IDC_SETUP_REFPOINT_COLOR)
	{
		pDC->SetBkMode(OPAQUE);
		pDC->SetBkColor(m_pOptCommon->m_s.RefPointStyle.clr);
		pDC->SetTextColor(m_pOptCommon->m_s.RefPointStyle.clr);
	}

	if (pWnd->GetDlgCtrlID() == IDC_SETUP_TARGETPOINT_COLOR)
	{
		pDC->SetBkMode(OPAQUE);
		pDC->SetBkColor(m_pOptCommon->m_s.TargetPointStyle.clr);
		pDC->SetTextColor(m_pOptCommon->m_s.TargetPointStyle.clr);
	}

	if (pWnd->GetDlgCtrlID() == IDC_SETUP_LINE_COLOR)
	{
		pDC->SetBkMode(OPAQUE);
		pDC->SetBkColor(m_pOptCommon->m_s.LineStyle.clr);
		pDC->SetTextColor(m_pOptCommon->m_s.LineStyle.clr);
	}

	// TODO:  Return a different brush if the default is not desired

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(WHITE_SMOKE);

		return m_brBlack;
	}
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return m_brBlack;
	//return hbr;
}

void CDlgDrawingStyleConfig::OnCbnSelchangeComboCamdirecSymbol()
{
	// TODO: Add your control notification handler code here
	int iSel = ((CComboBox*)GetDlgItem( IDC_COMBO_CAMDIREC_SYMBOL ))->GetCurSel();
	m_pOptCommon->m_s.CamDirecStyle.uSymbol = iSel+1;
	m_pOptCommon->Write();

	GetParent()->Invalidate();
}

void CDlgDrawingStyleConfig::OnCbnSelchangeComboRefpointSymbol()
{
	// TODO: Add your control notification handler code here
	int iSel = ((CComboBox*)GetDlgItem( IDC_COMBO_REFPOINT_SYMBOL ))->GetCurSel();
	m_pOptCommon->m_s.RefPointStyle.uSymbol = iSel+1;
	m_pOptCommon->Write();

	GetParent()->Invalidate();
}

void CDlgDrawingStyleConfig::OnCbnSelchangeComboTargetpointSymbol()
{
	// TODO: Add your control notification handler code here
	int iSel = ((CComboBox*)GetDlgItem( IDC_COMBO_TARGETPOINT_SYMBOL ))->GetCurSel();
	m_pOptCommon->m_s.TargetPointStyle.uSymbol = iSel+1;
	m_pOptCommon->Write();

	GetParent()->Invalidate();
}

void CDlgDrawingStyleConfig::OnBnClickedSetupCamdirecColorSel()
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg(m_pOptCommon->m_s.CamDirecStyle.clr, CC_FULLOPEN);
	dlg.DoModal();
	m_pOptCommon->m_s.CamDirecStyle.clr = dlg.GetColor();

	GetDlgItem(IDC_SETUP_CAMDIREC_COLOR)->Invalidate();
	GetDlgItem(IDC_SETUP_CAMDIREC_COLOR)->UpdateWindow();	

	m_pOptCommon->Write();

	GetParent()->Invalidate();
}

void CDlgDrawingStyleConfig::OnBnClickedSetupRefpointColorSel()
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg(m_pOptCommon->m_s.RefPointStyle.clr, CC_FULLOPEN);
	dlg.DoModal();
	m_pOptCommon->m_s.RefPointStyle.clr = dlg.GetColor();

	GetDlgItem(IDC_SETUP_REFPOINT_COLOR)->Invalidate();
	GetDlgItem(IDC_SETUP_REFPOINT_COLOR)->UpdateWindow();

	m_pOptCommon->Write();

	GetParent()->Invalidate();
}

void CDlgDrawingStyleConfig::OnBnClickedSetupTargetpointColorSel()
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg(m_pOptCommon->m_s.TargetPointStyle.clr, CC_FULLOPEN);
	dlg.DoModal();
	m_pOptCommon->m_s.TargetPointStyle.clr = dlg.GetColor();

	GetDlgItem(IDC_SETUP_TARGETPOINT_COLOR)->Invalidate();
	GetDlgItem(IDC_SETUP_TARGETPOINT_COLOR)->UpdateWindow();

	m_pOptCommon->Write();

	GetParent()->Invalidate();
}

void CDlgDrawingStyleConfig::OnEnChangeEditCamdirecLinewidth()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strText;
	//GetDlgItem(IDC_EDIT_CAMDIREC_LINEWIDTH)->GetWindowText(strText);

	m_pOptCommon->m_s.CamDirecStyle.uPenSize = atoi(strText);
	m_pOptCommon->Write();

	GetParent()->Invalidate();
}

void CDlgDrawingStyleConfig::OnEnChangeEditRefpointLinewidth()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strText;
	GetDlgItem(IDC_EDIT_REFPOINT_LINEWIDTH)->GetWindowText(strText);

	m_pOptCommon->m_s.RefPointStyle.uPenSize = atoi(strText);
	m_pOptCommon->Write();

	GetParent()->Invalidate();
}

void CDlgDrawingStyleConfig::OnEnChangeEditTargetpointLinewidth()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strText;
	GetDlgItem(IDC_EDIT_TARGETPOINT_LINEWIDTH)->GetWindowText(strText);

	m_pOptCommon->m_s.TargetPointStyle.uPenSize = atoi(strText);
	m_pOptCommon->Write();

	GetParent()->Invalidate();
}
void CDlgDrawingStyleConfig::OnEnChangeEditCamdirecSize()

{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	CString strText;
	GetDlgItem(IDC_EDIT_CAMDIREC_SYMBOLSIZE)->GetWindowText(strText);

	m_pOptCommon->m_s.CamDirecStyle.uSymbolSize = atoi(strText);
	m_pOptCommon->Write();

	GetParent()->Invalidate();
}

void CDlgDrawingStyleConfig::OnEnChangeEditRefpointSymbolsize()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strText;
	GetDlgItem(IDC_EDIT_REFPOINT_SYMBOLSIZE)->GetWindowText(strText);

	m_pOptCommon->m_s.RefPointStyle.uSymbolSize = atoi(strText);
	m_pOptCommon->Write();

	GetParent()->Invalidate();
}

void CDlgDrawingStyleConfig::OnEnChangeEditTargetpointSymbolsize()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strText;
	GetDlgItem(IDC_EDIT_TARGETPOINT_SYMBOLSIZE)->GetWindowText(strText);

	m_pOptCommon->m_s.TargetPointStyle.uSymbolSize = atoi(strText);
	m_pOptCommon->Write();

	GetParent()->Invalidate();
	
}

void CDlgDrawingStyleConfig::OnBnClickedCheckRefpointNum()
{
	// TODO: Add your control notification handler code here
	CString strText;
	
	m_pOptCommon->m_s.RefPointStyle.bDispNum = ((CButton*)GetDlgItem(IDC_CHECK_REFPOINT_NUM))->GetCheck();
	m_pOptCommon->Write();

	GetParent()->Invalidate();
}

void CDlgDrawingStyleConfig::OnBnClickedSetupLineColorSel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CColorDialog dlg(m_pOptCommon->m_s.LineStyle.clr, CC_FULLOPEN);
	dlg.DoModal();
	m_pOptCommon->m_s.LineStyle.clr = dlg.GetColor();

	GetDlgItem(IDC_SETUP_LINE_COLOR)->Invalidate();
	GetDlgItem(IDC_SETUP_LINE_COLOR)->UpdateWindow();

	m_pOptCommon->Write();

	GetParent()->Invalidate();
}

void CDlgDrawingStyleConfig::OnEnChangeEditLineLinewidth()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CString strText;
	GetDlgItem(IDC_EDIT_LINE_LINEWIDTH)->GetWindowText(strText);

	m_pOptCommon->m_s.LineStyle.uPenSize = atoi(strText);
	m_pOptCommon->Write();

	GetParent()->Invalidate();
}

void CDlgDrawingStyleConfig::OnBnClickedButtonApply()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//GetParent()->Invalidate();
}

void CDlgDrawingStyleConfig::OnEnChangeEditCamdirecOpacity()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strText;
	GetDlgItem(IDC_EDIT_CAMDIREC_OPACITY)->GetWindowText(strText);


	int iNum = atoi(strText);
	
	if(	iNum < 1 || iNum > 255 )
		AfxMessageBox("1~255 ���� �Է��ϼ���");

	m_pOptCommon->m_s.CamDirecStyle.byOpacity = iNum;

	m_pOptCommon->Write();

	GetParent()->Invalidate();
}

void CDlgDrawingStyleConfig::OnEnChangeEditTargetpointOpacity()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strText;
	GetDlgItem(IDC_EDIT_TARGETPOINT_OPACITY)->GetWindowText(strText);


	int iNum = atoi(strText);

	if(	iNum < 1 || iNum > 255 )
		AfxMessageBox("1~255 ���� �Է��ϼ���");

	m_pOptCommon->m_s.TargetPointStyle.byOpacity = atoi(strText);
	m_pOptCommon->Write();

	GetParent()->Invalidate();
}

void CDlgDrawingStyleConfig::OnEnChangeEditLineOpacity()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strText;
	GetDlgItem(IDC_EDIT_LINE_OPACITY)->GetWindowText(strText);

	int iNum = atoi(strText);

	if(	iNum < 1 || iNum > 255 )
		AfxMessageBox("1~255 ���� �Է��ϼ���");

	m_pOptCommon->m_s.LineStyle.byOpacity = atoi(strText);
	m_pOptCommon->Write();

	GetParent()->Invalidate();
}

void CDlgDrawingStyleConfig::OnCbnSelchangeComboLineSymbol()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int iSel = ((CComboBox*)GetDlgItem( IDC_COMBO_LINE_SYMBOL ))->GetCurSel();
	m_pOptCommon->m_s.LineStyle.uSymbol = iSel+1;
	m_pOptCommon->Write();

	GetParent()->Invalidate();
}
