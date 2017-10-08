#pragma once

//yeun
#include "OptCommonInfo.h"
//////////////////////////////////////////////////////////////////////////

// CDlgDrawingStyleConfig dialog

class CDlgDrawingStyleConfig : public CDialog
{
private:
	HBRUSH m_brBlack = CreateSolidBrush(RGB(0, 0, 0));
public:
	void SetOpt(COptCommonInfo * pOpt)
	{
		m_pOptCommon = pOpt;
	}
protected:
	COptCommonInfo * m_pOptCommon;

	DECLARE_DYNAMIC(CDlgDrawingStyleConfig)

public:
	CDlgDrawingStyleConfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgDrawingStyleConfig();

// Dialog Data
	enum { IDD = IDD_DRAWINGSTYLE_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonHide();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnBnClickedSetupCamdirecColorSel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCbnSelchangeComboCamdirecSymbol();
	afx_msg void OnCbnSelchangeComboRefpointSymbol();
	afx_msg void OnCbnSelchangeComboTargetpointSymbol();
	afx_msg void OnBnClickedSetupRefpointColorSel();
	afx_msg void OnBnClickedSetupTargetpointColorSel();
	afx_msg void OnEnChangeEditCamdirecLinewidth();
	afx_msg void OnEnChangeEditRefpointLinewidth();
	afx_msg void OnEnChangeEditTargetpointLinewidth();
	afx_msg void OnEnChangeEditCamdirecSize();
	afx_msg void OnEnChangeEditRefpointSymbolsize();
	afx_msg void OnEnChangeEditTargetpointSymbolsize();
	afx_msg void OnBnClickedCheckRefpointNum();
	afx_msg void OnBnClickedSetupLineColorSel();
	afx_msg void OnEnChangeEditLineLinewidth();
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnEnChangeEditCamdirecOpacity();
	afx_msg void OnEnChangeEditTargetpointOpacity();
	afx_msg void OnEnChangeEditLineOpacity();
	afx_msg void OnCbnSelchangeComboLineSymbol();

};
