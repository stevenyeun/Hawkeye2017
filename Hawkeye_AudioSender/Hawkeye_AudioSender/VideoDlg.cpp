// VideoDlg.cpp : implementation file
//


#include "stdafx.h"

#include <atlbase.h>
#include ".\idl\tvs_i.c"


#include "basic.h"
#include "VideoDlg.h"

#include "basicDlg.h"
#include "TVSDisplay.h"

#include "PicturePreview.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVideoDlg dialog


CVideoDlg::CVideoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVideoDlg)
	//}}AFX_DATA_INIT
	m_pdlgMain = NULL;
	m_lCurChID = 0;
	m_pVideoStream = NULL;
	m_pAudioStream = NULL;
	m_nFrameCountIncoming = 0;

	m_nFrmIdx = 0;

	m_isGetFrame = 0;
	m_pFrameBuf = NULL;
	m_FrameBufSize = 0;

	init_yuv();
}

CVideoDlg::~CVideoDlg()
{
	if(m_pFrameBuf)
		delete m_pFrameBuf;
	m_pFrameBuf = NULL;
	m_FrameBufSize = 0;

	term_yuv();
}


void CVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoDlg)
	DDX_Control(pDX, IDC_TVSLIVECONTROL1, m_tvsLive);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVideoDlg, CDialog)
	//{{AFX_MSG_MAP(CVideoDlg)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoDlg message handlers

BOOL CVideoDlg::Create(CBasicDlg* pdlgMain) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pdlgMain = pdlgMain;

	return CDialog::Create(CVideoDlg::IDD, m_pdlgMain);
}

BOOL CVideoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_lCurChID = 0;
	m_tvsDisplay = m_tvsLive.GetDisplay();

	m_prev_pts = 0;


	//GDI or D3D
	VARIANT var; 
	var.vt = VT_I4;
	var.lVal = 0;//GDI or D3D
	m_tvsLive.SetLocalConfig(TN_LCI_OSD_MODE, var);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVideoDlg::OnDestroy() 
{
	if (m_lCurChID > 0)
	{
		if (m_tvsLive.GetChannelState(m_lCurChID) & TN_CS_CONNECTED)
		{
			m_tvsLive.Disconnect(m_lCurChID);
			m_lCurChID = 0;
		}
	}

	if (m_pVideoStream)
	{
		fclose(m_pVideoStream);
		m_pVideoStream = NULL;
	}
	if (m_pAudioStream)
	{
		fclose(m_pAudioStream);
		m_pAudioStream = NULL;
	}

	if(m_pFrameBuf)
		delete m_pFrameBuf;
	m_pFrameBuf = NULL;
	m_FrameBufSize = 0;

	term_yuv();

	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
}

void CVideoDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

}

void CVideoDlg::GetFrame()
{
	m_isGetFrame = GetTickCount();
	return;
}

void CVideoDlg::ResampleFrame(BYTE_SIZEDARR_STM *pStream)
{
	if(GetTickCount()-m_isGetFrame>3000){
		m_isGetFrame = 0;
		return;
	}
	m_isGetFrame = 0;

	if(!pStream || !pStream->clSize || !pStream->stride)
		return;

	long eDataFormat = pStream->eDataFormat;
	long eDataFormatOut = TN_MTC_RAW_RGB888;


	int in_btcnt = 2;
	if(eDataFormat == TN_MTC_RAW_RGB32){
		in_btcnt = 4;
	}
	if(eDataFormat == TN_MTC_RAW_RGB888){
		in_btcnt = 3;
	}
	
	int out_btcnt = 2;
	if(eDataFormatOut == TN_MTC_RAW_RGB32){
		out_btcnt = 4;
	}
	if(eDataFormatOut == TN_MTC_RAW_RGB888){
		out_btcnt = 3;
	}
	
	int in_height = pStream->stride/in_btcnt;
	int in_width = pStream->clSize/pStream->stride;

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
	default:
		return;
	}
	
	int out_size = out_height*out_width*out_btcnt;
	
	if(!m_pFrameBuf || (int)m_FrameBufSize != out_size){
		m_FrameBufSize = 0;
		if(m_pFrameBuf) delete m_pFrameBuf; m_pFrameBuf=NULL;
		m_pFrameBuf = new BYTE[out_size];
		if(!m_pFrameBuf) 
			return;
		m_FrameBufSize = out_size;
	}
	
	BYTE *in_buf = pStream->pData;
	BYTE *out_buf = m_pFrameBuf;
	
	/*if(eDataFormatOut == TN_MTC_RAW_YUV422){
		if(in_btcnt==3)
			convert_RGB24_to_YUY2(in_buf, out_buf, width, height);
		else
			convert_RGB32_to_YUY2(in_buf, out_buf, width, height);
	}
	
	if(eDataFormatOut == TN_MTC_RAW_RGB32){
		if(in_btcnt==3)
			convert_24_to_32(in_buf, out_buf, width, height);
		else
			convert_YUY2_to_RGB32(in_buf, out_buf, width, height);
	}*/
	
	if(eDataFormatOut == TN_MTC_RAW_RGB888){
		in_buf += pStream->stride*(out_height-1);//because a source image flipped
		for(int i = 0; i< out_height; i++){
			if(in_btcnt==4)
				convert_32_to_24(in_buf, out_buf, out_width, 1);
			else
				convert_YUY2_to_RGB24(in_buf, out_buf, out_width, 1);
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

	TCHAR szTempFile[_MAX_PATH]; szTempFile[0] = '\0';
	GetModuleFileName(NULL, szTempFile, _MAX_PATH);
	LPTSTR lps = _tcsrchr(szTempFile,'\\');
	if(lps)
		lps[0] = '\0';
	lstrcat(szTempFile, _T("\\temp.bmp"));

	HANDLE hF = ::CreateFile( szTempFile,GENERIC_ALL,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
	
	if (hF == 0){
		//wsprintf(szMess, _T("Error create file 0x%08x"), HRESULT_FROM_WIN32(GetLastError()));
		//MessageBox(szMess);
		return;
	}
	
	BITMAPFILEHEADER bfh;
	RGBQUAD bmiColors[1]; 
	memset(&bfh,0,sizeof(BITMAPFILEHEADER));
	memset(bmiColors,0,sizeof(bmiColors));
	BYTE * type = (BYTE*) &bfh;
	type[0] = 'B';
	type[1] = 'M';
	
	bfh.bfSize = bih.biSizeImage + sizeof(BITMAPFILEHEADER) + 
		sizeof(BITMAPINFOHEADER) + sizeof(bmiColors);
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
		+sizeof(bmiColors);
	
	DWORD dwWritten;
	BOOL bRet = WriteFile(hF,&bfh,sizeof(BITMAPFILEHEADER),&dwWritten,0);
	if (bRet == 0){
		CloseHandle(hF);
		//wsprintf(szMess, _T("Error create file 0x%08x"), HRESULT_FROM_WIN32(GetLastError()));
		//MessageBox(szMess);
		return;
	}
	bRet = WriteFile(hF,&bih,sizeof(BITMAPINFOHEADER),&dwWritten,0);
	if (bRet == 0){
		CloseHandle(hF);
		//wsprintf(szMess, _T("Error create file 0x%08x"), HRESULT_FROM_WIN32(GetLastError()));
		//MessageBox(szMess);
		return;
	}
	bRet = WriteFile(hF,bmiColors,sizeof(bmiColors),&dwWritten,0);
	if (bRet == 0){
		CloseHandle(hF);
		//wsprintf(szMess, _T("Error create file 0x%08x"), HRESULT_FROM_WIN32(GetLastError()));
		//MessageBox(szMess);
		return ;
	}
	
	bRet = WriteFile(hF,m_pFrameBuf,bih.biSizeImage,&dwWritten,0);
	if (bRet == 0){
		CloseHandle(hF);
		//wsprintf(szMess, _T("Error create file 0x%08x"), HRESULT_FROM_WIN32(GetLastError()));
		//MessageBox(szMess);
		return ;
	}
	CloseHandle(hF);

	/* something mistic assert!!
	CPicturePreview dlg;
	dlg.SetBMP(szTempFile);
	dlg.Create(m_pdlgMain);*/
}



BEGIN_EVENTSINK_MAP(CVideoDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CVideoDlg)
	ON_EVENT(CVideoDlg, IDC_TVSLIVECONTROL1, 1 /* OnChannelNotify */, OnChannelNotifyTvslivecontrol1, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CVideoDlg, IDC_TVSLIVECONTROL1, 2 /* OnStreamData */, OnStreamDataTvslivecontrol1, VTS_I4 VTS_VARIANT)
	ON_EVENT(CVideoDlg, IDC_TVSLIVECONTROL1, 3 /* OnMouseEvent */, OnMouseEventTvslivecontrol1, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CVideoDlg, IDC_TVSLIVECONTROL1, 4 /* OnServerEvent */, OnServerEventTvslivecontrol1, VTS_I4 VTS_I4 VTS_I2 VTS_I4 VTS_VARIANT)
	ON_EVENT(CVideoDlg, IDC_TVSLIVECONTROL1, 5 /* OnSerialData */, OnSerialDataTvslivecontrol1, VTS_I4 VTS_I2 VTS_VARIANT)
	ON_EVENT(CVideoDlg, IDC_TVSLIVECONTROL1, 6 /* OnSystemNotify */, OnSystemNotifyTvslivecontrol1, VTS_I4 VTS_VARIANT)
	ON_EVENT(CVideoDlg, IDC_TVSLIVECONTROL1, 7 /* OnRecordNotify */, OnRecordNotifyTvslivecontrol1, VTS_I4 VTS_I4 VTS_VARIANT)
	ON_EVENT(CVideoDlg, IDC_TVSLIVECONTROL1, 8 /* OnWaveNotify */, OnWaveNotifyTvslivecontrol1, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



void CVideoDlg::OnChannelNotifyTvslivecontrol1(long lChID, long eNewState, long eReason) 
{
	// TODO: Add your control notification handler code here

	if (eNewState & TN_CS_CONNECTED)
	{
		m_pdlgMain->AddToLog(_T("OnChannelNotifyTvslivecontrol1(TN_CS_CONNECTED)\r\n"));	
	}
	else
	{
		if (eReason < 10)
		{
            m_pdlgMain->AddToLog(_T("OnChannelNotifyTvslivecontrol1(NOT CONNECTED:reason=%d)\r\n"), eReason);
		}
		else
		{
			switch (eReason)
			{
			case TN_SNC_CN_SERVER_UNREACHABLE:
				m_pdlgMain->AddToLog(_T("OnChannelNotifyTvslivecontrol1(NOT CONNECTED:Server is unreachable for connection)\r\n"));
				m_pdlgMain->Pause();
				return;
//				break;
			case TN_SNC_CN_TOO_MANY_CONNECTION: 
				m_pdlgMain->AddToLog(_T("OnChannelNotifyTvslivecontrol1(NOT CONNECTED:Too many connections on the server)\r\n"));
				break;
			case TN_SNC_CN_PASSWORD_MISMATCH: 
				m_pdlgMain->AddToLog(_T("OnChannelNotifyTvslivecontrol1(NOT CONNECTED:Password is incorrect)\r\n"));
				break;
			case TN_SNC_CN_CONNECTION_DISABLED: 
				m_pdlgMain->AddToLog(_T("OnChannelNotifyTvslivecontrol1(NOT CONNECTED:Server disabled the connection)\r\n"));
				break;
			case TN_SNC_CN_ID_NOT_EXIST: 
				m_pdlgMain->AddToLog(_T("OnChannelNotifyTvslivecontrol1(NOT CONNECTED:Login ID doesn't exist)\r\n"));
				break;
			case TN_SNC_CN_DOMAINNAME_UNKNOWN: 
				m_pdlgMain->AddToLog(_T("OnChannelNotifyTvslivecontrol1(NOT CONNECTED:Can't resolve the domain name)\r\n"));
				break;
/*			case TN_SNC_CN_PARAMETER_OUTOFRANGE:
				m_pdlgMain->AddToLog("OnChannelNotifyTvslivecontrol1(NOT CONNECTED:Invalid channels is one of this case)\r\n");
				break;
*/			case TN_SNC_CN_DUPLICATE_CONNECT: 
				m_pdlgMain->AddToLog(_T("OnChannelNotifyTvslivecontrol1(NOT CONNECTED:Multiple connections to a channel are not allowed)\r\n"));
				break;
			case TN_SNC_CN_KEEPALIVE_FAILED: 
				m_pdlgMain->AddToLog(_T("OnChannelNotifyTvslivecontrol1(NOT CONNECTED:Disconnected due to keep alive timeout)\r\n"));
				m_pdlgMain->Pause();
				return;
//				break;
			case TN_SNC_CN_NO_AUTHORITY_OPERATION:
				m_pdlgMain->AddToLog(_T("OnChannelNotifyTvslivecontrol1(NOT CONNECTED:No authority operation)\r\n"));
				break;
			case TN_SNC_CN_OPERATION_FAILED:
				m_pdlgMain->AddToLog(_T("OnChannelNotifyTvslivecontrol1(NOT CONNECTED:General failure)\r\n"));
				break;
			}

			m_pdlgMain->Disconnect();
		}

	}

	if (eNewState & TN_CS_STREAMED)
	{
		m_pdlgMain->AddToLog(_T("OnChannelNotifyTvslivecontrol1(TN_CS_STREAMED)\r\n"));	
	}

	if (eNewState & TN_CS_DECODED)
	{
		m_pdlgMain->AddToLog(_T("OnChannelNotifyTvslivecontrol1(TN_CS_DECODED)\r\n"));	
	}

	if (eNewState & TN_CS_DISPLAYED)
	{
		m_pdlgMain->GetDlgItem(IDC_BUTTON_PLAY)->SetWindowText(_T("Pause"));
		m_pdlgMain->AddToLog(_T("OnChannelNotifyTvslivecontrol1(TN_CS_DISPLAYED)\r\n"));	
	}

	if (eNewState & TN_CS_RECORDED)
	{
		m_pdlgMain->AddToLog(_T("OnChannelNotifyTvslivecontrol1(TN_CS_RECORDED)\r\n"));	
	}
}

void CVideoDlg::OnStreamDataTvslivecontrol1(long lChID, const VARIANT FAR& vData) 
{
	// TODO: Add your control notification handler code here
	BYTE_SIZEDARR_STM *pStream = (BYTE_SIZEDARR_STM *)vData.pbVal;
	TCHAR szLog[255]={0};

	int delta=0;
	SYSTEMTIME st;
	FILETIME ft;
	ft.dwLowDateTime = pStream->stime;
	ft.dwHighDateTime = (pStream->stime>>32);
	FileTimeToSystemTime(&ft, &st);

	switch (pStream->eDataFormat)
	{
	case TN_MTC_H_264:
		m_nFrameCountIncoming++;
		if (m_pdlgMain->m_pDataStreamFile)
		{
			//write all, include header
			fwrite(vData.pbVal, 1, pStream->cbSize+pStream->clSize, m_pdlgMain->m_pDataStreamFile);
			//size = fwrite(pStream->pData, 1, pStream->clSize, m_pdlgMain->m_pDataStreamFile);
		}

#ifndef _UNICODE
		TRACE("\n[%03d] ChID=0x%08X, MType=%3d, Format=%2d, Res=%d, DSize=%6u, CBSize=%u, Flag=%3d, stride=%9d, pts=%u, stime=%9I64d ",
			m_nFrmIdx, lChID, pStream->eMediaType, pStream->eDataFormat, pStream->eDataResolution, pStream->clSize, pStream->cbSize,
			pStream->eFlags, pStream->stride, pStream->pts, pStream->stime);
#endif
		m_nFrmIdx++;

		delta = (int)(pStream->pts - m_prev_pts);
		m_prev_pts = pStream->pts;
#ifdef _DEBUG
//		_stprintf(szLog, _T("OnStreamDataTvsLivecontrol pts_time(%d) delta_pts(%d) serv_time(%I64d)\r\n"), pStream->pts, delta, pStream->stime);
//		OutputDebugString(szLog);
#endif

		if (pStream->eFlags & TN_FF_KEYFRAME)
		{
			m_pdlgMain->AddToLog(_T("OnStreamDataTvslivecontrol1(ENCODED VIDEO KEY_FRAME(%i): time(%d) serv_time(%d:%d:%d))\r\n"), m_nFrameCountIncoming, pStream->pts, st.wHour, st.wMinute, st.wSecond);	
		}
		break;
	case TN_MTC_RAW_YUV420:
	case TN_MTC_RAW_YUV422:
	case TN_MTC_RAW_RGB888:
		m_nFrameCountIncoming++;
		if (m_pdlgMain->m_pDataStreamFile)
		{
			//fwrite(vData.pbVal, 1, pStream->cbSize+pStream->clSize, m_pdlgMain->m_pDataStreamFile);
			fwrite(pStream->pData, 1, pStream->clSize, m_pdlgMain->m_pDataStreamFile);

			delta = (int)(pStream->pts - m_prev_pts);
			m_prev_pts = pStream->pts;
#ifdef _DEBUG
			_stprintf(szLog, _T("OnStreamDataTvsLivecontrol pts_time(%d) delta_pts(%d) serv_time(%I64d)\r\n"), pStream->pts, delta, pStream->stime);
			OutputDebugString(szLog);
#endif

		}
		if(m_isGetFrame){
			ResampleFrame(pStream);
		}
		if(!((m_nFrameCountIncoming+101) % 101)){
			m_pdlgMain->AddToLog(_T("OnStreamDataTvslivecontrol1(DECODED VIDEO frame(%i): time%d)\r\n"), m_nFrameCountIncoming, pStream->pts);	
		}
		break;

	case TN_MTC_G_711U:
		break;
	}

//	m_pdlgMain->AddToLog("OnStreamDataTvslivecontrol1\r\n");	
}

void CVideoDlg::OnMouseEventTvslivecontrol1(long lChID, long lMsg, long wParam, long lParam) 
{
	// TODO: Add your control notification handler code here
	if(lMsg==WM_MOUSEWHEEL)
	{
		int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		long zoom=100, x = 0, y = 0;
		
		m_tvsDisplay.GetDigitalZoom(m_lCurChID, &zoom, &x, &y);
		
		RECT rect = {0};
		if(zoom==100){
			m_tvsDisplay.GetDURect(0, 0, (short*)&rect.left, (short*)&rect.top, (short*)&rect.right, (short*)&rect.bottom);
			x = rect.left;
			y = rect.top;
		}
		
		zoom += delta>0 ? -25 : 25;
		if(zoom<100) zoom = 100;
		if(zoom>1000) zoom = 1000;
		m_tvsDisplay.SetDigitalZoom(m_lCurChID, zoom, x, y);
	}
	else if(lMsg==WM_LBUTTONUP)
	{
		WORD nX = LOWORD(lParam);
		WORD nY = HIWORD(lParam);
		RECT rect = {0};
		m_tvsDisplay.GetDURect(0, 0, (short*)&rect.left, (short*)&rect.top, (short*)&rect.right, (short*)&rect.bottom);

		HRGN rgnl, rgnu, rgnr, rgnd;
		POINT ptVertex[3];

		ptVertex[0].x = rect.left;
		ptVertex[0].y = rect.top;
		ptVertex[1].x = rect.left+(rect.right-rect.left)/2;
		ptVertex[1].y = rect.top+(rect.bottom-rect.top)/2;
		ptVertex[2].x = rect.left;
		ptVertex[2].y = rect.bottom;

		rgnl = CreatePolygonRgn(ptVertex, 3, ALTERNATE);

		ptVertex[0].x = rect.left;
		ptVertex[0].y = rect.top;
		ptVertex[1].x = rect.left+(rect.right-rect.left)/2;
		ptVertex[1].y = rect.top+(rect.bottom-rect.top)/2;
		ptVertex[2].x = rect.right;
		ptVertex[2].y = rect.top;

		rgnu = CreatePolygonRgn(ptVertex, 3, ALTERNATE);

		ptVertex[0].x = rect.right;
		ptVertex[0].y = rect.top;
		ptVertex[1].x = rect.left+(rect.right-rect.left)/2;
		ptVertex[1].y = rect.top+(rect.bottom-rect.top)/2;
		ptVertex[2].x = rect.right;
		ptVertex[2].y = rect.bottom;

		rgnr = CreatePolygonRgn(ptVertex, 3, ALTERNATE);

		ptVertex[0].x = rect.right;
		ptVertex[0].y = rect.bottom;
		ptVertex[1].x = rect.left+(rect.right-rect.left)/2;
		ptVertex[1].y = rect.top+(rect.bottom-rect.top)/2;
		ptVertex[2].x = rect.left;
		ptVertex[2].y = rect.bottom;

		rgnd = CreatePolygonRgn(ptVertex, 3, ALTERNATE);

		// set zoom point
		long zoom=100, x = 0, y = 0;
		m_tvsDisplay.GetDigitalZoom(m_lCurChID, &zoom, &x, &y);

		int center_x = rect.left+(rect.right-rect.left)/2;
		int center_y = rect.top+(rect.bottom-rect.top)/2;

		int dx = (nX-center_x)*100/zoom;
		int dy = (nY-center_y)*100/zoom;

		if(PtInRegion(rgnl, nX, nY) || PtInRegion(rgnr, nX, nY))
			x+=dx;
		else if(PtInRegion(rgnu, nX, nY) || PtInRegion(rgnd, nX, nY))
			y+=dy;			

		if(x<=rect.left)		x = rect.left+1;
		if(y<=rect.top)			y = rect.top+1;
		if(x>=rect.right)		x = rect.right-1;
		if(y>=rect.bottom)		y = rect.bottom-1;

		m_tvsDisplay.SetDigitalZoom(m_lCurChID, zoom, x, y);
	}

	//m_pdlgMain->AddToLog(_T("OnMouseEventTvslivecontrol1\r\n")); 
}

void CVideoDlg::OnServerEventTvslivecontrol1(long lChID, long eEventType, short nIndex, long eEventStatus, const VARIANT FAR& vData) 
{
	// TODO: Add your control notification handler code here
	switch (eEventType)
	{
		case TN_ET_DI:
			m_pdlgMain->AddToLog(_T("OnServerEventTvslivecontrol1([%d] TN_ET_DI=%d)\r\n"), nIndex, eEventStatus);	
			break;
		case TN_ET_VIDEOLOSS:
			m_pdlgMain->AddToLog(_T("OnServerEventTvslivecontrol1([%d] TN_ET_VIDEOLOSS=%d)\r\n"), nIndex, eEventStatus);	
			break;
		case TN_ET_MOTION:
			//m_pdlgMain->AddToLog(_T("OnServerEventTvslivecontrol1([%d] TN_ET_MOTION=%d)\r\n"), nIndex, eEventStatus);	
			break;
		case TN_ET_TIMECHANGED:
			m_pdlgMain->AddToLog(_T("OnServerEventTvslivecontrol1([%d] TN_ET_TIMECHANGED)\r\n"), nIndex);	
			break;
		case TN_ET_DO:
			m_pdlgMain->AddToLog(_T("OnServerEventTvslivecontrol1([%d] TN_ET_DO=%d)\r\n"), nIndex, eEventStatus);	
			break;
		case TN_ET_RECORD:
			m_pdlgMain->AddToLog(_T("OnServerEventTvslivecontrol1(TN_ET_RECORD=%d)\r\n"), eEventStatus);	
			break;
        case TN_ET_RESOLUTIONCHANGED:
            m_pdlgMain->AddToLog(_T("OnServerEventTvslivecontrol1(TN_ET_RESOLUTIONCHANGED=%d)\r\n"), vData.lVal);
            break;
		default:
			m_pdlgMain->AddToLog(_T("OnServerEventTvslivecontrol1(unknown)\r\n"));	
	 }
}

void CVideoDlg::OnSerialDataTvslivecontrol1(long lChID, short nIndex, const VARIANT FAR& vData) 
{
	// TODO: Add your control notification handler code here
	m_pdlgMain->AddToLog(_T("OnSerialDataTvslivecontrol1\r\n"));	
	
}

void CVideoDlg::OnSystemNotifyTvslivecontrol1(long lNotifyCode, const VARIANT FAR& vData) 
{
	// TODO: Add your control notification handler code here
	m_pdlgMain->AddToLog(_T("OnOnSystemNotifyTvslivecontrol1\r\n"));	
}

void CVideoDlg::OnRecordNotifyTvslivecontrol1(long lNotifyCode, long lChID, const VARIANT FAR& vData) 
{
	// TODO: Add your control notification handler code here
	m_pdlgMain->AddToLog(_T("OnOnRecordNotifyTvslivecontrol1\r\n"));
}

void CVideoDlg::OnWaveNotifyTvslivecontrol1(long lChID, long lState) 
{
    m_pdlgMain->AddToLog(_T("OnWaveNotifyTvslivecontrol1(lState=0x%x)\r\n"), lState);

    switch (lState)
    {
    case TN_WAV_STOP:
        m_pdlgMain->GetDlgItem(IDC_BUTTON_PLAYWAVE)->SetWindowText(_T("Play Wave"));
        break;

    case TN_WAV_START:
        m_pdlgMain->GetDlgItem(IDC_BUTTON_PLAYWAVE)->SetWindowText(_T("Stop Playing"));
        break;

    case TN_WAV_FILE_NOT_FOUND:
        m_pdlgMain->GetDlgItem(IDC_BUTTON_PLAYWAVE)->SetWindowText(_T("Play Wave"));
        break;

    case TN_WAV_FILE_WRONG_FMT:
        m_pdlgMain->GetDlgItem(IDC_BUTTON_PLAYWAVE)->SetWindowText(_T("Play Wave"));
        break;
    }
}
