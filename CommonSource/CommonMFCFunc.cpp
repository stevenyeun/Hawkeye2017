#include "stdafx.h"
#include "CommonMFCFunc.h"


CCommonMFCFunc::CCommonMFCFunc()
{
}


CCommonMFCFunc::~CCommonMFCFunc()
{
}

void CCommonMFCFunc::HideIconFromTaskbar()
{
	HWND hWnd = AfxGetMainWnd()->GetSafeHwnd();

	long style = GetWindowLong(hWnd, GWL_EXSTYLE);
	style &= ~(WS_VISIBLE);
	style |= WS_EX_TOOLWINDOW;
	style &= ~(WS_EX_APPWINDOW);

	::ShowWindow(hWnd, SW_HIDE);
	SetWindowLong(hWnd, GWL_EXSTYLE, style);
	::ShowWindow(hWnd, SW_SHOW);
}

void CCommonMFCFunc::AutoHideTaskbar()
{
	APPBARDATA TAppBarData;
	memset(&TAppBarData, 0, sizeof(TAppBarData));
	TAppBarData.cbSize = sizeof(TAppBarData);
	TAppBarData.hWnd = (HWND)FindWindow(_T("Shell_TrayWnd"), NULL);
	TAppBarData.lParam |= ABS_AUTOHIDE;
	SHAppBarMessage(ABM_SETSTATE, &TAppBarData);
}
