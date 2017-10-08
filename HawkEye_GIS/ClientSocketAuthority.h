#pragma once

//Yeun
class CDlgSetupAuthorityServerConn;
#include "AuthorityPacket.h"
#define STR_AUTHORITY_CLIENT_SOCKET_PACKET_TO_WINDOW_MSG _T("UWM_AUTHORITY_CLIENT_SOCKET_PACKET_TO_WINDOW_MSG")
#define STR_AUTHORITY_CLIENT_SOCKET_EVENT_TO_WINDOW_MSG _T("UWM_AUTHORITY_CLIENT_SOCKET_EVENT_TO_WINDOW_MSG")
#define TO_AUTHORITY_SERVER_CONNECTION_COMPLETED 1
///////////////////////////////////////////////////

// CClientSocketPTZ command target

class CClientSocketAuthority : public CAsyncSocket
{
public:	
	//void SetCh(int nCh)
	//{
	//	m_nCh = nCh;
	//}	
	void SetUpdatingDlg(CWnd * pUpdatingDlg)
	{
		m_pUpdatingDlg = pUpdatingDlg;
	}
	void SetPacketUpdatingDlg(CWnd * pUpdatingDlg)
	{
		m_pPacketUpdatingWindow = pUpdatingDlg;
	}
private:
	CWnd * m_pUpdatingDlg;
	CWnd * m_pPacketUpdatingWindow;
	//int m_nCh;
public:
	//BOOL m_bLoginSocketCreation;//소켓생성상태
	//BOOL m_bLoginSocketConnection;//서버와의 연결상태
public:
	CClientSocketAuthority();
	virtual ~CClientSocketAuthority();
	virtual void OnReceive(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};