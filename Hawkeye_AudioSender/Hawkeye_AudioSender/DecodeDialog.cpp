// DecodeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "basic.h"
#include "basicDlg.h"
#include "DecodeDialog.h"

#include ".\idl\tvs_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef SAFE_RELEASEH
#define SAFE_RELEASEH(x) {if(x) CloseHandle(x); x=0;}
#endif //SAFE_RELEASEH


/////////////////////////////////////////////////////////////////////////////
// CDecodeDialog dialog


CDecodeDialog::CDecodeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDecodeDialog::IDD, pParent)
{
	m_pdlgMain = NULL;
	m_lChID = 0;
	m_nTimerID = 0;
	m_nReadCount = 0;
	m_hevDecodeStop = NULL;
	EnableAutomation();

	m_nDecFrmIdx = 0;

	m_bFrame = new char[BUF_SIZE];


	//{{AFX_DATA_INIT(CDecodeDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDecodeDialog::~CDecodeDialog()
{
	if(m_bFrame)
		delete m_bFrame;
	m_bFrame = NULL;
}



void CDecodeDialog::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CDecodeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDecodeDialog)
	DDX_Control(pDX, IDC_TVSDECODECONTROL1, m_tvsdecode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDecodeDialog, CDialog)
	//{{AFX_MSG_MAP(CDecodeDialog)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDecodeDialog, CDialog)
	//{{AFX_DISPATCH_MAP(CDecodeDialog)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDecodeDialog to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {9002D83A-8D6D-4F9B-A1BB-116C4FB8A9E1}
static const IID IID_IDecodeDialog =
{ 0x9002d83a, 0x8d6d, 0x4f9b, { 0xa1, 0xbb, 0x11, 0x6c, 0x4f, 0xb8, 0xa9, 0xe1 } };

BEGIN_INTERFACE_MAP(CDecodeDialog, CDialog)
	INTERFACE_PART(CDecodeDialog, IID_IDecodeDialog, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDecodeDialog message handlers

BEGIN_EVENTSINK_MAP(CDecodeDialog, CDialog)
    //{{AFX_EVENTSINK_MAP(CDecodeDialog)
	ON_EVENT(CDecodeDialog, IDC_TVSDECODECONTROL1, 1 /* OnDataEvent */, OnDataEventTvsdecodecontrol1, VTS_I4 VTS_VARIANT VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

BOOL CDecodeDialog::Create(CBasicDlg* pdlgMain) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pdlgMain = pdlgMain;

	return CDialog::Create(CDecodeDialog::IDD, (CWnd*)m_pdlgMain);
}

void CDecodeDialog::OnDataEventTvsdecodecontrol1(long lChID, const VARIANT FAR& vData, long lError) 
{
	BYTE_SIZEDARR_STM *pStream = (BYTE_SIZEDARR_STM *)vData.pbVal;
	TCHAR szLog[255]={0};
	int delta=0;

#ifndef _UNICODE
	TRACE("\nDecode [%03d] ChID=0x%08X, MType=%3d, Format=%2d, Res=%d, DSize=%6u, CBSize=%u, Flag=%3d, stride=%9d, pts=%9u, stime=%9I64d ",
		m_nDecFrmIdx, lChID, pStream->eMediaType, pStream->eDataFormat, pStream->eDataResolution, pStream->clSize, pStream->cbSize,
		pStream->eFlags, pStream->stride, pStream->pts, pStream->stime);
#endif

	m_nDecFrmIdx++;

	switch (pStream->eDataFormat)
	{
	case TN_MTC_H_264:
		SYSTEMTIME st;
		FILETIME ft;
		ft.dwLowDateTime = pStream->stime;
		ft.dwHighDateTime = (pStream->stime>>32);
		FileTimeToSystemTime(&ft, &st);

		delta = (int)(pStream->pts - m_prev_pts);
		m_prev_pts = pStream->pts;
#ifdef _DEBUG
		_stprintf(szLog, _T("OnDataEventTvsDecodecontrol1 pts_time(%d) delta_pts(%d) serv_time(%I64d)\r\n"), pStream->pts, delta, pStream->stime);
		OutputDebugString(szLog);
#endif
		break;
	case TN_MTC_RAW_YUV420:
	case TN_MTC_RAW_YUV422:
	case TN_MTC_RAW_RGB888:
		break;

	case TN_MTC_G_711U:
		break;
	}

	m_pdlgMain->AddToLog(_T("OnDataReceive connection point\r\n"));	
}


BOOL CDecodeDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_prev_pts = 0;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


HRESULT CDecodeDialog::StartDecode()
{
	if(IsStarted()) return S_OK;
	m_fh = fopen("c:\\datastream.raw","rb");
	if(!m_fh)
		return S_FALSE;

	int display = m_pdlgMain->IsDlgButtonChecked(IDC_CH_DISP);
	int cb = m_pdlgMain->IsDlgButtonChecked(IDC_CH_CB);
	int cp = m_pdlgMain->IsDlgButtonChecked(IDC_CH_CP);


	m_lChID = m_tvsdecode.Open(display, cp, (cb)?(IUnknown *)(CUnk *)this:NULL);

	long eFormat = 0;
	int sel = m_pdlgMain->m_cbOutputFormat.GetCurSel();
	switch(sel){
	case 1:
		eFormat = TN_MTC_RAW_RGB888;
		break;
	case 2:
		eFormat = TN_MTC_RAW_RGB32;
		break;
	case 3:
		eFormat = TN_MTC_RAW_YUV422;
		break;
	}
	m_tvsdecode.SetOutputFormat(m_lChID, eFormat);


	//m_bFrame = new char[BUF_SIZE];

	//m_nTimerID = SetTimer(1, 1000, NULL);

	m_tvsdecode.StartDecoding(m_lChID);

	m_pdlgMain->GetDlgItem(IDC_BTN_DEC_START)->SetWindowText(IsStarted() ? _T("Stop"):_T("Start"));

	//ShowWindow(display?SW_NORMAL:SW_HIDE);
	ShowWindow(SW_NORMAL);

	m_pdlgMain->GetDlgItem(IDC_CH_DISP)->EnableWindow(FALSE);
	m_pdlgMain->GetDlgItem(IDC_CH_CB)->EnableWindow(FALSE);
	m_pdlgMain->GetDlgItem(IDC_CH_CP)->EnableWindow(FALSE);

	if(IsStarted()){
		if(!m_hevDecodeStop)
			m_hevDecodeStop = CreateEvent(NULL, 1, 0, NULL);
		if(!handle){
			CreateThread();
			ResumeThread();
		}
	}

	return (IsStarted())?S_OK : S_FALSE;
}

HRESULT CDecodeDialog::StopDecode()
{
	if(!IsStarted()) return S_OK;

	if(m_hevDecodeStop){
		SetEvent(m_hevDecodeStop);
		if(handle)
			WaitForSingleObject(handle, 1000);
		handle = NULL;
		SAFE_RELEASEH(m_hevDecodeStop);
	}else
		TerminateThread();

	m_tvsdecode.StopDecoding(m_lChID);
	m_tvsdecode.Close(m_lChID);
	m_lChID = 0;
	/*if(m_nTimerID)
		KillTimer(m_nTimerID);
	m_nTimerID = 0;*/

	/*if(m_bFrame)
		delete m_bFrame;
	m_bFrame = NULL;*/
	if(m_fh)
		fclose(m_fh);
	m_fh = NULL;

	m_pdlgMain->GetDlgItem(IDC_BTN_DEC_START)->SetWindowText(IsStarted() ? _T("Stop"):_T("Start"));

	ShowWindow(SW_HIDE);

	m_pdlgMain->GetDlgItem(IDC_CH_DISP)->EnableWindow(TRUE);
	m_pdlgMain->GetDlgItem(IDC_CH_CB)->EnableWindow(TRUE);
	m_pdlgMain->GetDlgItem(IDC_CH_CP)->EnableWindow(TRUE);

	return S_OK;
}

// RGB888 mode test 
//BYTE outbuffer[720*576*3];
BYTE outbuffer[1920*1080*3];
//callback
STDMETHODIMP CDecodeDialog::OnDataReceive( 
            /* [in] */ INT_PTR lChID,
            /* [in] */ VARIANT vData,
            /* [in] */ long lError)
{
	BYTE_SIZEDARR_STM *pStream = (BYTE_SIZEDARR_STM *)vData.pbVal;
	TCHAR szLog[255]={0};
	int delta=0;

	/////////////////////////////////////////////////
	// RGB 888 mode test 
	long eDataFormatOut = pStream->eDataFormat;
	int out_btcnt = 2;
	if(eDataFormatOut == TN_MTC_RAW_RGB32){
		out_btcnt = 4;
	}
	if(eDataFormatOut == TN_MTC_RAW_RGB888){
		out_btcnt = 3;
	}
	
	int out_height = 0;
	int out_width = 0;

	switch((char)pStream->eDataResolution){
	case TN_RM_720X480:
		out_width = 720; out_height=480;
		break;
	case TN_RM_720X240:
		out_width = 720; out_height=240;
		break;
	case TN_RM_352X480:
		out_width = 352; out_height=480;
		break;
	case TN_RM_352X240:
		out_width = 352; out_height=240;
		break;
	case TN_RM_720x576:
		out_width = 720; out_height=576;
		break;
	case TN_RM_720x288:
		out_width = 720; out_height=288;
		break;
	case TN_RM_352x576:
		out_width = 352; out_height=576;
		break;
	case TN_RM_352x288:
		out_width = 352; out_height=288;
		break;
	case TN_RM_1920x1080:
		out_width = 1920; out_height=1080;
		OutputDebugString(_T("1920x1080\n"));
		break;
	default:
				OutputDebugString(_T("DEFAULT\n"));
		return 0;
	}

	int out_size = out_height*out_width*out_btcnt;
	
	BYTE *in_buf = pStream->pData;
	BYTE *out_buf = outbuffer;
	if(eDataFormatOut == TN_MTC_RAW_RGB888)
	{
		in_buf += pStream->stride*(out_height-1); //because a source image is flipped
		for(int i = 0; i< out_height; i++){
			memcpy( out_buf, in_buf, out_btcnt*out_width );
			in_buf -= pStream->stride;
			out_buf += out_btcnt*out_width;
		}
	}

	BITMAPINFOHEADER bih;
	BITMAPINFOHEADER * bmih = (BITMAPINFOHEADER *) &bih;
	
	memset(bmih, 0, sizeof(BITMAPINFOHEADER));
	bmih->biBitCount = 24;
	bmih->biCompression = BI_RGB;
	bmih->biSizeImage = out_size;
	bmih->biHeight = out_height;
	bmih->biWidth = out_width;
	bmih->biSize = sizeof(BITMAPINFOHEADER);
	bmih->biPlanes = 1;

	CDC* pDC = GetDC();
	::SetStretchBltMode(pDC->m_hDC, COLORONCOLOR);  
	::StretchDIBits( pDC->m_hDC,
					 0, 0, out_width, out_height,
					 0, 0, out_width, out_height,
					 outbuffer,//pStream->pData, 
					 (BITMAPINFO *)&bih, 
					 DIB_RGB_COLORS, SRCCOPY );	
	
	ReleaseDC( pDC);

#ifndef _UNICODE
	TRACE("\nDecode [%03d] ChID=0x%08X, MType=%3d, Format=%2d, Res=%d, DSize=%6u, CBSize=%u, Flag=%3d, stride=%9d, pts=%9u, stime=%9I64d ",
		m_nDecFrmIdx, lChID, pStream->eMediaType, pStream->eDataFormat, pStream->eDataResolution, pStream->clSize, pStream->cbSize,
		pStream->eFlags, pStream->stride, pStream->pts, pStream->stime);
#endif

	m_nDecFrmIdx++;

	switch (pStream->eDataFormat)
	{
	case TN_MTC_H_264:
		SYSTEMTIME st;
		FILETIME ft;
		ft.dwLowDateTime = pStream->stime;
		ft.dwHighDateTime = (pStream->stime>>32);
		FileTimeToSystemTime(&ft, &st);

		delta = (int)(pStream->pts - m_prev_pts);
		m_prev_pts = pStream->pts;
#ifdef _DEBUG
		_stprintf(szLog, _T("OnDataEventTvsDecodecontrol1 pts_time(%d) delta_pts(%d) serv_time(%I64d)\r\n"), pStream->pts, delta, pStream->stime);
		OutputDebugString(szLog);
#endif
		break;
	case TN_MTC_RAW_YUV420:
	case TN_MTC_RAW_YUV422:
	case TN_MTC_RAW_RGB888:
		break;

	case TN_MTC_G_711U:
		break;
	}

	m_pdlgMain->AddToLog(_T("OnDataReceive callback\r\n"));	
	return S_OK;
}

DWORD CDecodeDialog::Proc()
{
	DWORD dwwait = WAIT_FAILED;
	int i=0;
	int res;
	DWORD timeout = 1;
	int fcorrect = 0;
	m_nReadCount = 0;
	while(1){
		dwwait = WaitForSingleObject(m_hevDecodeStop, timeout);
		if(dwwait != WAIT_TIMEOUT)
			break;

		int actual = BUF_SIZE;
		int count = 10;

		BYTE_SIZEDARR_STM *stm = (BYTE_SIZEDARR_STM *)m_bFrame;
		int size_stm = sizeof(BYTE_SIZEDARR_STM);

		actual = fread(m_bFrame, 1, size_stm, m_fh);
		if(actual < sizeof(BYTE_SIZEDARR_STM) || stm->cbSize != size_stm){
			if(!fcorrect){
				m_pdlgMain->AddToLog(_T("Incorrect file\r\n"));
				m_pdlgMain->PostMessage(WM_COMMAND, MAKEWPARAM(IDC_BTN_DEC_START, BN_CLICKED));
				//StopDecode();
				return 0;
			}else{
				stm->eFlags = TN_FF_ENDOFSTREAM;
				stm->clSize = 0;

				VARIANT vData; vData.vt = VT_I1|VT_BYREF;
				vData.pbVal = (unsigned char *)stm;
				if (m_tvsdecode.PutData(m_lChID, vData) == FALSE){
#ifndef _UNICODE
					TRACE("Decode Putdata Error ***** \n");
#endif 
				}

				fseek(m_fh, 0, 0);
				m_pdlgMain->AddToLog(_T("End of file. Seek 0\r\n"));
				//continue;
				return 0;
			}
		}
		if( (BUF_SIZE-size_stm) < stm->clSize){
			m_pdlgMain->AddToLog(_T("Incorrect header\r\n"));
			m_pdlgMain->PostMessage(WM_COMMAND, MAKEWPARAM(IDC_BTN_DEC_START, BN_CLICKED));
			//StopDecode();
			return 0;
		}

		TCHAR szLog[255]={0};
		int delta = (int)(stm->pts - m_prev_pts);
		m_prev_pts = stm->pts;
#ifdef _DEBUG
		_stprintf(szLog, _T("Decodecontrol pts_time(%d) delta_pts(%d) serv_time(%I64d)\r\n"), stm->pts, delta, stm->stime);
#endif

		fcorrect = 1;
		actual = fread(m_bFrame+size_stm, 1, stm->clSize, m_fh);
		if(actual != stm->clSize){
			fseek(m_fh, 0, 0);
		}

		stm->pData = (BYTE *)m_bFrame+size_stm;

		m_nReadCount++;

		/*BYTE_SIZEDARR_STM stm = {0};
		stm.cbSize = sizeof(stm);
		stm.eMediaType = TN_MT_VIDEO;
		stm.eDataFormat = TN_MTC_H_264;
		stm.eFlags = 0;
		stm.pData = (unsigned char *)m_bFrame;
		stm.clSize = actual;*/

		BYTE_SIZEDARR_STM * pStream = stm;
#ifndef _UNICODE
		TRACE("\nPutData[%03d] ChID=0x%08X, MType=%3d, Format=%2d, Res=%d, DSize=%6u, CBSize=%u, Flag=%3d, stride=%9d, pts=%9u, stime=%9I64d ",
			m_nReadCount-1, m_lChID, pStream->eMediaType, pStream->eDataFormat, pStream->eDataResolution, pStream->clSize, pStream->cbSize,
			pStream->eFlags, pStream->stride, pStream->pts, pStream->stime);
#endif

		VARIANT vData; vData.vt = VT_I1|VT_BYREF;
		vData.pbVal = (unsigned char *)stm;

		if (m_tvsdecode.PutData(m_lChID, vData) == FALSE){
#ifndef _UNICODE
			TRACE("Decode Putdata Error ***** \n");
#endif
		}

	}

	return 0;
}

void CDecodeDialog::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == m_nTimerID && IsStarted())
	{
		int actual = BUF_SIZE;

		int count = 10;

		BYTE_SIZEDARR_STM *stm = (BYTE_SIZEDARR_STM *)m_bFrame;
		int size_stm = sizeof(BYTE_SIZEDARR_STM);

		actual = fread(m_bFrame, 1, size_stm, m_fh);
		if(actual < sizeof(BYTE_SIZEDARR_STM) || stm->cbSize != size_stm){
			m_pdlgMain->AddToLog(_T("End of file"));
			StopDecode();
			return ;
		}
		if( (BUF_SIZE-size_stm) < stm->clSize){
			m_pdlgMain->AddToLog(_T("Incorrect header"));
			StopDecode();
			return ;
		}
		actual = fread(m_bFrame+size_stm, 1, stm->clSize, m_fh);
		if(actual != stm->clSize){
			fseek(m_fh, 0, 0);
		}

		stm->pData = (BYTE *)m_bFrame+size_stm;

		m_nReadCount++;

		/*BYTE_SIZEDARR_STM stm = {0};
		stm.cbSize = sizeof(stm);
		stm.eMediaType = TN_MT_VIDEO;
		stm.eDataFormat = TN_MTC_H_264;
		stm.eFlags = 0;
		stm.pData = (unsigned char *)m_bFrame;
		stm.clSize = actual;*/

		VARIANT vData; vData.vt = VT_I1|VT_BYREF;
		vData.pbVal = (unsigned char *)stm;
		m_tvsdecode.PutData(m_lChID, vData);
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CDecodeDialog::OnDestroy() 
{
	StopDecode();
		if(m_bFrame)
		delete m_bFrame;
	m_bFrame = NULL;
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
