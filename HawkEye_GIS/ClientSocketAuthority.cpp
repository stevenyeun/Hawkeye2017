// ClientSocket_Login.cpp : implementation file
//

#include "stdafx.h"
#include "PictureShow.h"
#include "ClientSocketAuthority.h"

//yeun

#include "ErrorDefine.h"
#include "AuthorityPacket.h"
// ClientSocket -> XXXXWindow
UINT UWM_AUTHORITY_CLIENT_SOCKET_PACKET_TO_WINDOW_MSG;//소켓 패킷을 메인윈도우로 전송
UINT UWM_AUTHORITY_CLIENT_SOCKET_EVENT_TO_WINDOW_MSG;//소켓이벤트를 메인윈도우로 전송
//////////////////////////////

// CClientSocketPTZ

CClientSocketAuthority::CClientSocketAuthority()
{
	//m_pUpdatingDlg = NULL;
	m_pPacketUpdatingWindow = NULL;
	//	m_bLoginSocketCreation = FALSE;
	//	m_bLoginSocketConnection = FALSE;
}

CClientSocketAuthority::~CClientSocketAuthority()
{
}


// CClientSocket_Login member functions

void CClientSocketAuthority::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	BYTE byBuf[sizeof(AUTHORITY_PACKET)];
	ZeroMemory(byBuf, sizeof(byBuf));

	CString strSenderIP;
	UINT uSenderPort;
	int nRead = ReceiveFrom(byBuf, sizeof(byBuf), strSenderIP, uSenderPort);

	switch (nRead)
	{
	case 0:
		Close();
		break;
	case SOCKET_ERROR:
		if (GetLastError() != WSAEWOULDBLOCK)
		{
			AfxMessageBox(_T("Error occurred"));
			Close();
		}
		break;
	default:
		//CString szTemp(byBuff);
		//m_strRecv += szTemp;   // m_strRecv is a CString declared 

		if (m_pPacketUpdatingWindow != NULL)
		{
#if 0
			DATAANDLENGTH dataandlen;
			dataandlen.nLen = nRead;
			dataandlen.lpData = (LPBYTE)byBuff;

			m_pPacketUpdatingWindow->SendMessage(
				UWM_AUTHORITY_CLIENT_SOCKET_PACKET_TO_WINDOW_MSG,
				m_nCh,
				(LPARAM)&dataandlen);
#else
			PACKET_LENGTH packet_len;
			packet_len.nLen = nRead;
			 
			//CString strPeerIPaddr;
			//UINT uPeerPort = 0;
			//BOOL bReturn = this->GetPeerName(strPeerIPaddr, uPeerPort);

			packet_len.srcIPPort.dwIPAddr = htonl(inet_addr((CStringA)strSenderIP));
			packet_len.srcIPPort.uPort = uSenderPort;
			packet_len.lpData = (LPBYTE)byBuf;

			//포트 번호로 채널 구분
			CString strCh; strCh.Format("%d", uSenderPort);
			strCh = strCh.Right(1);
			int nCh = atoi(strCh);

			m_pPacketUpdatingWindow->SendMessage(
				UWM_AUTHORITY_CLIENT_SOCKET_PACKET_TO_WINDOW_MSG,
				nCh,
				(LPARAM)&packet_len);
#endif

		}
	}

	CAsyncSocket::OnReceive(nErrorCode);
}

void CClientSocketAuthority::OnConnect(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
#if 0
	if (nErrorCode != 0)
	{
		CString str; str.Format(_T("%d채널 "), m_nCh);
		AfxMessageBox(str + GetSocketConnectError(nErrorCode));
		//m_pUpdatingDlg->SetAuthServerConnStatus(m_nCh, FALSE);

	}
	else//접속성공
	{
		//UI 접속 성공 표시
		//m_pUpdatingDlg->SetAuthServerConnStatus(m_nCh, TRUE);

		//접속 성공을 메인 윈도우에 알림(서버측으로 패킷 전송)
		m_pPacketUpdatingWindow->SendMessage(
			UWM_AUTHORITY_CLIENT_SOCKET_EVENT_TO_WINDOW_MSG,
			TO_AUTHORITY_SERVER_CONNECTION_COMPLETED,
			m_nCh);
	}
#endif
	CAsyncSocket::OnConnect(nErrorCode);
}

void CClientSocketAuthority::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	this->Close();
	//m_pUpdatingDlg->SetAuthServerConnStatus(m_nCh, FALSE);

	CAsyncSocket::OnClose(nErrorCode);
}
