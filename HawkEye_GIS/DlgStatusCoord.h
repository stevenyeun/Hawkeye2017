#pragma once

#include "resource.h"
// CDlgStatusCoord dialog

class CDlgStatusCoord : public CDialog
{
	DECLARE_DYNAMIC(CDlgStatusCoord)
private:
	HBRUSH m_brBlack = CreateSolidBrush(RGB(0, 0, 0));
private:
	CFont m_fontTitle;
	CFont m_fontText;
	CRect m_rcDefaultDlgSize;
private:
	int m_nRadioCh;
public:
	int GetSelectedCh() {
		return m_nRadioCh;
	}
public:
	CRect GetDefaultDlgSize() const { return m_rcDefaultDlgSize; }
public:
	CDlgStatusCoord(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgStatusCoord();

// Dialog Data
	enum { IDD = IDD_DIALOG_STATUS_COORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRadioChClicked(UINT value);
	LRESULT OnNcHitTest(CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckDockingTop();

	BOOL m_bChkTopDocking;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	afx_msg void OnBnClickedRadioCh1();
	afx_msg void OnBnClickedRadioCh2();
	afx_msg void OnBnClickedRadioCh3();
	afx_msg void OnBnClickedRadioCh4();
	afx_msg void OnBnClickedRadioCh5();
};
