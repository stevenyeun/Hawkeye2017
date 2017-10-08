//{{AFX_INCLUDES()
#include "tvslivecontrol.h"
//}}AFX_INCLUDES
#if !defined(AFX_VIDEODLG_H__66D970EB_D4E9_4A8F_8AB1_5B8D492DF4B4__INCLUDED_)
#define AFX_VIDEODLG_H__66D970EB_D4E9_4A8F_8AB1_5B8D492DF4B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoDlg.h : header file
//

//#include "../../../inc/tvs_const.h"
#include ".\\idl\tvs.h"
#include "tvsdisplay.h"



//colorspace
void MMX_memcpy(LPVOID dst, const VOID *src, DWORD count);

void term_yuv();
void init_yuv();
void convert_32_to_24(unsigned char * in_frame,
                      unsigned char * out_frame,
                      int width, int height);
void convert_24_to_32(unsigned char * in_frame,
                      unsigned char * out_frame,
                      int width, int height);
void convert_YUY2_to_RGB24(unsigned char * in_frame,
                           unsigned char * out_frame,
                           int width, int height);
void convert_RGB24_to_YUY2(unsigned char * in_frame,
                           unsigned char * out_frame,
                           int width, int height);
void convert_YUY2_to_RGB32(unsigned char * in_frame,
                           unsigned char * out_frame,
                           int width, int height);
void convert_RGB32_to_YUY2(unsigned char * in_frame,
                           unsigned char * out_frame,
                           int width, int height);


/////////////////////////////////////////////////////////////////////////////
// CVideoDlg dialog

class CVideoDlg : public CDialog
{

	DWORD m_isGetFrame;
	BYTE *m_pFrameBuf;
	long m_FrameBufSize;

	void ResampleFrame(BYTE_SIZEDARR_STM *pStream);
// Construction
public:
	CVideoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVideoDlg();

// Dialog Data
	//{{AFX_DATA(CVideoDlg)
	enum { IDD = IDD_DIALOG_VIDEO };
	CTVSLiveControl	m_tvsLive;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	class CBasicDlg	*m_pdlgMain;

	int m_nFrameCountIncoming;
	ULONG m_prev_pts;
	
public:
	CTVSDisplay	m_tvsDisplay;
	long m_lCurChID;
	
	//OSDID added by YI
	long m_lOsdID;
	long m_lOsdID2;

	FILE *m_pVideoStream;
	FILE *m_pAudioStream;

	int m_nFrmIdx;

	void GetFrame();

public:
	BOOL Create(class CBasicDlg* pdlgMain);

	// Generated message map functions
	//{{AFX_MSG(CVideoDlg)
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnChannelNotifyTvslivecontrol1(long lChID, long eNewState, long eReason);
	afx_msg void OnStreamDataTvslivecontrol1(long lChID, const VARIANT FAR& vData);
	afx_msg void OnMouseEventTvslivecontrol1(long lChID, long lMsg, long wParam, long lParam);
	afx_msg void OnServerEventTvslivecontrol1(long lChID, long eEventType, short nIndex, long eEventStatus, const VARIANT FAR& vData);
	afx_msg void OnSerialDataTvslivecontrol1(long lChID, short nIndex, const VARIANT FAR& vData);
	afx_msg void OnSystemNotifyTvslivecontrol1(long lNotifyCode, const VARIANT FAR& vData);
	afx_msg void OnRecordNotifyTvslivecontrol1(long lNotifyCode, long lChID, const VARIANT FAR& vData);
	afx_msg void OnWaveNotifyTvslivecontrol1(long lChID, long lState);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEODLG_H__66D970EB_D4E9_4A8F_8AB1_5B8D492DF4B4__INCLUDED_)
