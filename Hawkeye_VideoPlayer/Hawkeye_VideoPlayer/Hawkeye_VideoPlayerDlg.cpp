
// Hawkeye_VideoPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Hawkeye_VideoPlayer.h"
#include "Hawkeye_VideoPlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHawkeye_VideoPlayerDlg dialog

using namespace std;
#include "../Hawkeye_HWDecodingWithFFmpeg/Hawkeye_HWDecodingWithFFmpeg.h"
#pragma comment ( lib, "../../HawkEye/Hawkeye_VideoPlayer/Hawkeye_HWDecodingWithFFmpeg.lib")

void CALLBACK MyCallbackFunc(AVFrame *frame, string result)
{
	TRACE(result.c_str());
	if (frame == NULL)
	{
		//printf("callback: %s\n", "NULL");
		TRACE("callback: %s\n", "NULL");
	}
	else
	{
		//printf("callback: %s\n", "GotFrame");
		TRACE("callback: %s\n", "GotFrame");
	}
}

#if 1
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/pixdesc.h>
#include <libavutil/hwcontext.h>
#include <libavutil/opt.h>
#include <libavutil/avassert.h>
#include <libavutil/imgutils.h>

#pragma comment ( lib, "avformat.lib")
#pragma comment ( lib, "swscale.lib" )
#pragma comment ( lib, "avcodec.lib" )
#pragma comment ( lib, "avutil.lib" )
#pragma comment ( lib, "avdevice.lib" )
}
#endif


CHawkeye_VideoPlayerDlg::CHawkeye_VideoPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HAWKEYE_VIDEOPLAYER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHawkeye_VideoPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHawkeye_VideoPlayerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CHawkeye_VideoPlayerDlg message handlers

BOOL CHawkeye_VideoPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	Init("rtsp://admin:q1w2e3r4t5@192.168.10.100:554/profile2/media.smp", AV_HWDEVICE_TYPE_DXVA2);
	
	Register_Callback(MyCallbackFunc);

	Sleep(20000);

	DeInit();




	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHawkeye_VideoPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHawkeye_VideoPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

