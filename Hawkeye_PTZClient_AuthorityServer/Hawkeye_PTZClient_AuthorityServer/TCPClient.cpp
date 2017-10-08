// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// Hawkeye_PTZClient_AuthorityServer.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"

// TODO: �ʿ��� �߰� �����
// �� ������ �ƴ� STDAFX.H���� �����մϴ�.

#include "ByteCollector.h"

CString g_strArrServerIP[MAX_CHANNEL_NUM];
int g_nArrServerPort[MAX_CHANNEL_NUM] = {0, };

CByteCollector g_arrByteCollector[MAX_CHANNEL_NUM];

BOOL g_bArrTCPClientConnection[MAX_CHANNEL_NUM] = { FALSE, };
SOCKET arrSockTCPClient[MAX_CHANNEL_NUM]{ INVALID_SOCKET, };
CWinThread * arrSendToPTZServerThread[MAX_CHANNEL_NUM] = { NULL, };
CWinThread * arrReceiveFromPTZServerThread[MAX_CHANNEL_NUM] = { NULL, };
CWinThread * g_arrReConnectionThread[MAX_CHANNEL_NUM] = { NULL, };


queue<CMD> g_queueSendToPTZCommand[MAX_CHANNEL_NUM];
CStandardCommandToProtocol g_arrStdCmdToProtocol[MAX_CHANNEL_NUM];


extern CRITICAL_SECTION g_csArrSendToAuthorityClient[MAX_CHANNEL_NUM];
extern queue<AUTHORITY_PACKET> g_queuePakcetSendToAuthorityClient[MAX_CHANNEL_NUM];

//�Լ���..
UINT SendToPTZServerThread(void * pParam);
UINT ReceiveFromPTZServerThread(void * pParam);
UINT ReConnectionThread(void * pParam);

void TCPClientReceiveFromPTZServer_ProcessServiceCode(int nCh, int nServiceCode);
void TCPClientReceiveFromPTZServer_PushAuthorityPacket(int nCh, BYTE byCmdGroup, BYTE byCmdType, AUTHORITY_DATA & authorityData);

bool ConnectWithTimeout(int nCh, const char *host, int port, int timeout)
{
	int nIndex = nCh - 1;

	TIMEVAL Timeout;
	Timeout.tv_sec = timeout;
	Timeout.tv_usec = 0;
	struct sockaddr_in address;  /* the libc network address data structure */

	arrSockTCPClient[nIndex] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	address.sin_addr.s_addr = inet_addr(host); /* assign the address */
	address.sin_port = htons(port);            /* translate int2port num */
	address.sin_family = AF_INET;

	//set the socket in non-blocking
	unsigned long iMode = 1;
	int iResult = ioctlsocket(arrSockTCPClient[nIndex], FIONBIO, &iMode);
	if (iResult != NO_ERROR)
	{
		printf("ioctlsocket failed with error: %ld\n", iResult);
	}

	if (connect(arrSockTCPClient[nIndex], (struct sockaddr *)&address, sizeof(address)) == false)
	{
		return false;
	}

	// restart the socket mode
	iMode = 0;
	iResult = ioctlsocket(arrSockTCPClient[nIndex], FIONBIO, &iMode);
	if (iResult != NO_ERROR)
	{
		printf("ioctlsocket failed with error: %ld\n", iResult);
	}

	fd_set Write, Err;
	FD_ZERO(&Write);
	FD_ZERO(&Err);
	FD_SET(arrSockTCPClient[nIndex], &Write);
	FD_SET(arrSockTCPClient[nIndex], &Err);

	// check if the socket is ready
	select(0, NULL, &Write, &Err, &Timeout);
	if (FD_ISSET(arrSockTCPClient[nIndex], &Write))
	{
		return true;
	}

	return false;
}


bool CreateTCPClientSocket(int nCh, const char * ipAddr, u_short nPort)
{
	int nRet = false;
	//PTZ�� ���� �� ����
	//http://www.sysnet.pe.kr/Default.aspx?mode=2&sub=0&detail=1&pageno=0&wid=1473&rssMode=1&wtype=0
	int nIndex = nCh - 1;

#if 0 //�����������ӹ��
	//SOCKET socket = INVALID_SOCKET;
	
	sockaddr_in target;
	target.sin_family = AF_INET;
	// target.sin_addr.s_addr = inet_addr("192.168.0.70");

	target.sin_addr.s_addr = inet_addr(ipAddr);
	target.sin_port = htons(nPort);

	

#if 0//Ÿ�̾ƿ�ó��
	TIMEVAL Timeout;
	Timeout.tv_sec = 3000;
	Timeout.tv_usec = 0;
#endif

	arrSockTCPClient[nIndex] = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (arrSockTCPClient[nIndex] == INVALID_SOCKET)
	{
		printf("ä��=%d TCPŬ���̾�Ʈ ���� ���� ����, ���� ��ȣ : %ld \n", nCh, WSAGetLastError());
		nRet = false;
	}


#if 0 //Ÿ�Ӿƿ�ó��
	//set the socket in non-blocking
	unsigned long iMode = 1;
	int iResult = ioctlsocket(arrSockTCPClient[nIndex], FIONBIO, &iMode);
	if (iResult != NO_ERROR)
	{
		printf("ioctlsocket failed with error: %ld\n", iResult);
	}	
#endif
	int result = ::connect(arrSockTCPClient[nIndex], (SOCKADDR *)&target, sizeof(target));
	if (result == SOCKET_ERROR)
	{
		printf("ä��=%d TCPŬ���̾�Ʈ ����(%s, %d) ����(connect �Լ�) ����, ���� ��ȣ : %ld \n", nCh, ipAddr, nPort, WSAGetLastError());
		g_bArrTCPClientConnection[nIndex] = FALSE;
		nRet = false;
	}
	else
	{
		printf("ä��=%d TCPŬ���̾�Ʈ ����(%s, %d) ����(connect �Լ�) ���� \n", nCh, ipAddr, nPort );
		g_bArrTCPClientConnection[nIndex] = TRUE;
		nRet = true;

	}
#if 0//Ÿ�̾ƿ�ó��
	// restart the socket mode

	iMode = 0;
	iResult = ioctlsocket(arrSockTCPClient[nIndex], FIONBIO, &iMode);
	if (iResult != NO_ERROR)
	{
		printf("ioctlsocket failed with error: %ld\n", iResult);
	}

	fd_set Write, Err;
	FD_ZERO(&Write);
	FD_ZERO(&Err);
	FD_SET(arrSockTCPClient[nIndex], &Write);
	FD_SET(arrSockTCPClient[nIndex], &Err);

	// check if the socket is ready
	select(0, NULL, &Write, &Err, &Timeout);
	if (FD_ISSET(arrSockTCPClient[nIndex], &Write))
	{
		nRet = false;
	}
#endif
	//g_bArrTCPClientConnection[nIndex] = TRUE;
#else
	nRet = ConnectWithTimeout(nCh, ipAddr, nPort, 2);

#endif
	if (arrSendToPTZServerThread[nIndex] == NULL)
	{
		arrSendToPTZServerThread[nIndex] = AfxBeginThread(SendToPTZServerThread, &nCh, THREAD_PRIORITY_NORMAL);
		Sleep(1000);
	}
	if (arrReceiveFromPTZServerThread[nIndex] == NULL)
	{
		arrReceiveFromPTZServerThread[nIndex] = AfxBeginThread(ReceiveFromPTZServerThread, &nCh, THREAD_PRIORITY_NORMAL);
		Sleep(1000);
	}
	if (g_arrReConnectionThread[nIndex] == NULL)
	{
		g_arrReConnectionThread[nIndex] = AfxBeginThread(ReConnectionThread, &nCh, THREAD_PRIORITY_NORMAL);
		Sleep(1000);
	}

#if 0
	if (g_arrByteCollector[nIndex].GetSafeHwnd() == NULL)
	{
		HWND hWndDesktop = GetDesktopWindow();
		CWnd* pWndDesktop = CWnd::FromHandle(hWndDesktop);

		//����Ʈ�� ���ļ� �������ݷ� ����� �ִ� Ŭ����
		BOOL bRet = g_arrByteCollector[nIndex].Create(NULL, NULL, WS_CHILD | WS_VISIBLE,
			CRect(0, 0, 0, 0), pWndDesktop, 0);

		g_arrByteCollector[nIndex].SetProtocolStyle('$', 0x0d, 0);
	}
#else
	g_arrByteCollector[nIndex].SetProtocolStyle('$', 0x0d, 0);
#endif
	//g_arrByteCollector[nIndex].SetProtocolStyle('$', 0x0d, 0);

	//arrReceiveFromPTZServerThread[nIndex] = new thread(ReceiveFromPTZServerThread, 0);



	return nRet;
}


bool ReleaseTCPClientSocket(int nCh)
{
	int nIndex = nCh - 1;

	if (arrSockTCPClient[nIndex] != INVALID_SOCKET)
	{
		int result = ::closesocket(arrSockTCPClient[nIndex]);
		if (result == SOCKET_ERROR)
		{
			printf("ä��=%d TCPŬ���̾�Ʈ ���� ���� ����, ������ȣ : %ld \n", nCh, WSAGetLastError());
			return false;
		}

		arrSockTCPClient[nIndex] = INVALID_SOCKET;
		printf("ä��=%d TCPŬ���̾�Ʈ ���� ���� ���� \n", nCh);

		//printf("TCP Client socket: Closed\n");
	}
	else
	{
		printf("ä��=%d TCPŬ���̾�Ʈ ������ �̹� ���� �Ǿ��� \n", nCh);

	}
	
	return true;
}
//PTZServer�� ����
UINT SendToPTZServerThread(void * pParam)
{
	

	int nCh = (*(int*)pParam);
	int nChIndex = nCh - 1;

	printf("ä��=%d TCPŬ���̾�Ʈ SendToPTZServerThread ������ \n", nCh);
	while (true)
	{
		if (g_queueSendToPTZCommand[nChIndex].size() > 0)
		{
			CMD gotCMD = g_queueSendToPTZCommand[nChIndex].front();
			g_queueSendToPTZCommand[nChIndex].pop();

			BYTE byBuf[PROTO_BUFFER_SIZE] = { 0, };
			int nProtocolSize = g_arrStdCmdToProtocol[nChIndex].StdCmdToProtocolPacket(gotCMD, byBuf);
			if (nProtocolSize > 0)
			{
				//pDlg->SendToPTZServer(pInfo->nCh, byBuf, nProtocolSize);

				int sentLength = ::send(arrSockTCPClient[nChIndex], (const char *)byBuf, nProtocolSize, 0);
				if (sentLength > 0)
				{
					printf("ä��=%d TCPŬ���̾�Ʈ PTZServer�� ��Ŷ ���� ���� %s \n", nCh, (const char *)byBuf);
				}
				else if (sentLength == 0)
				{
					g_bArrTCPClientConnection[nChIndex] = FALSE;
					break;
				}
				else if (sentLength == -1)
				{
					g_bArrTCPClientConnection[nChIndex] = FALSE;

					printf("Socket Failed: %d", ::WSAGetLastError());
					break;
				}
			}
		}
		Sleep(50);
	}

	return 0;
}
UINT ReceiveFromPTZServerThread(void * pParam)
{
	int nCh = (*(int*)pParam);
	int nChIndex = nCh - 1;
	printf("ä��=%d TCPŬ���̾�Ʈ ReceiveFromPTZServerThread ������ \n", nCh);

	while (true)
	{
		int const bufSize = 4096;
		byte recvbuf[bufSize];

		//int iResult = recv(clientSock, recvbuf, bufSize, 0);
		int iResult = recv(arrSockTCPClient[nChIndex], (char*)recvbuf, bufSize, 0);
		if (iResult > 0)
		{
			printf("ä��=%d TCPŬ���̾�Ʈ %d ����Ʈ ������ \n", nCh, iResult);
			//printf("Bytes received: %d\n", iResult);
			g_bArrTCPClientConnection[nChIndex] = TRUE;
		}
		else if (iResult == 0)
		{
			//printf("Connection closed\n");
			//WSAENOTSOCK 10038 Socket operation on nonsocket.
			printf("ä��=%d recv �Լ� ���� ���ϰ�=%d %d\n", nCh, iResult, WSAGetLastError());

			g_bArrTCPClientConnection[nChIndex] = FALSE;
			ReleaseTCPClientSocket(nCh);
			Sleep(5000);
			continue;
		}
		else
		{
			//WSAENOTCONN
			//WSAECONNRESET 10054 Connection reset by peer.
			//printf("ä��=%d recv failed with error: %d\n", nCh, WSAGetLastError());
			printf("ä��=%d TCPŬ���̾�Ʈ recv() �Լ� ���� ���ϰ�=%d %d\n", nCh, iResult, WSAGetLastError());
			g_bArrTCPClientConnection[nChIndex] = FALSE;
			ReleaseTCPClientSocket(nCh);
			Sleep(5000);
			continue;
		}

		vector<byte> vecPacket;

		if (g_arrByteCollector[nChIndex].CollectByte(recvbuf, iResult, vecPacket) == FALSE)
			continue;

		CString strCmd;
		int nServiceCode = CU2SRProtoParser::GetCmd(&vecPacket[0], strCmd);

		//made = $00004HM = CD3//�����¸��
		//made = $00104HM = PC5//
		//printf("ParsedCmd : %s \n", (CStringA)strCmd);
		printf("ä��=%d TCPŬ���̾�Ʈ ��Ŷ �Ľ� : %s \n", nCh, (CStringA)strCmd);
		//get��� Queue�� ���� ���� ����� ������ Ȯ���ϰ� �Ľ� �ϴ� ���?
		//Ŀ�ǵ� ���̸� ���� �Ǵ��ϴ¹��
		//GC     : 29
		//GC=L   -> $00117067.7664,-03.483517 -> ParsedCmd : 067.7664,-03.4835 -> 17
		//GC=M	 : 11
		//GS=P	 : 2
		//GS=T	 : 2
		//PW=? L : PW=O or PW=F �� ����� �����ϸ� ���� �Ľ� ����
		//PP=001:022.5000,+00.0000,50000,50000 -> $00036PP=001:022.5000,+00.0000,50000,500002A 
		//GC=M   -> $0011100191,0067311 -> ParsedCmd : 00191,00673 -> 11
		//GC=G

		//���� �ڵ� ó��
		
		if (nServiceCode == -1)
			continue;

		TCPClientReceiveFromPTZServer_ProcessServiceCode(nCh, nServiceCode);

		int nLen = strCmd.GetLength();

		if (strCmd.GetLength() != 0)
		{
			//����� ��Ŷ���� ��ȯ�Ͽ� Ŭ���̾�Ʈ�鿡�� �����Ѵ�.
			
			if (nServiceCode == GET_OK_INT || nServiceCode == ERR_DEV_PWROFF_INT)//���������� ������ ����
			{				
				if (strCmd.GetLength() == 2)
				{
					CString strStatus = CU2SRProtoParser::Util_ConvertAscii2Hexa(strCmd);	// [40] => [64]
					strStatus = CU2SRProtoParser::Util_GetBinaryData(strStatus);		// [64] => [00000010]

					char chMoving = strStatus.GetAt(3);
					if (chMoving == '1')//�̵���
					{
						//MSB         LSB
						//7 6 5 4 3 2 1 0
						/*
						bit7 : motor unconnected, bit6 : undefined,	bit5 : Pan ���ͼ��� ����, bit4 : motor busy(���� ���� ��),
						bit3 : homming(���� Center ��ġ), bit2 : position error, (���� ��ġ�ν� error), bit1 : limitte left ����, bit0 : limitte right ����
						*/						
						//m_arrPTZInfo[nChIndex].bPanMoving = TRUE;
						TRACE("PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP\n");

						AUTHORITY_DATA data;
						MakeAuthorityData(1, data);
						TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_PTZREQ, CMDTYPE_PTZREQ_PAN_MOVESTATUS_RESP, data);
					}
					else if (chMoving == '0')
					{
						//m_arrPTZInfo[nChIndex].bPanMoving = FALSE;
						//���� ���� ����
						AUTHORITY_DATA data;
						MakeAuthorityData(2, data);
						TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_PTZREQ, CMDTYPE_PTZREQ_PAN_MOVESTATUS_RESP, data);
					}

					char chPanInit = strStatus.GetAt(5);//�Ҹ��� �ʱ�ȭ ����
					if (chPanInit == '1')//������ġ�νĿ���
					{
						AUTHORITY_DATA data;
						MakeAuthorityData(2, data);
						TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_PTZREQ, CMDTYPE_PTZREQ_PAN_INITSTATUS_RESP, data);
						//this->SendToAllAuthorityClient(nCh, CMDGROUP_ETCFUNC, CMDTYPE_ETCFUNC_PANTILT_MOTOR_ADJUSTMENT_STATUS, data);
					}
					else if (chPanInit == '0')//����
					{
						AUTHORITY_DATA data;
						MakeAuthorityData(1, data);
						TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_PTZREQ, CMDTYPE_PTZREQ_PAN_INITSTATUS_RESP, data);
						//this->SendToAllAuthorityClient(nCh, CMDGROUP_ETCFUNC, CMDTYPE_ETCFUNC_PANTILT_MOTOR_ADJUSTMENT_STATUS, data);
					}
				}
				else if (strCmd.Find(_T("HM=C")) != -1)//���� �̵� �Ϸ�
				{
					//HM=C ����� ������ ���� ����� ack�ȴ�.
					//������°� ���� �ڵ� ����Ȯ�� ������ �ȵǾ��ְ� / Ȩ��ġ �Ϸᰡ �ȵ� �����̸�

					//�ʱ�ȭ�� �Ϸ�Ǹ� HM=C ���°� ACK �ȴ�.

					//�Ϸἳ�����Ѵ�.

					//m_arrPTZInfo[nChIndex].bHomePostionCompleted = TRUE;
					AUTHORITY_DATA data;
					MakeAuthorityData(2, data);
					TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_PANTILTINIT, CMDTYPE_PANTILTINIT_RESP_HOMEPOS, data);
				
				}
				else if ((strCmd.Find(_T("HM=P")) != -1 || strCmd.Find(_T("HM=T")) != -1))//���� �̵����� �ǹ��ϴ� ack
				{
					//m_arrPTZInfo[nChIndex].bHomePostionCompleted = FALSE;

					AUTHORITY_DATA data;
					MakeAuthorityData(1, data);
					TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_PANTILTINIT, CMDTYPE_PANTILTINIT_RESP_HOMEPOS, data);
				}
				else if (strCmd.GetLength() == 17)////GC=L   -> $00117067.7664,-03.483517 -> ParsedCmd : 067.7664,-03.4835 -> 17
				{
					//160107 commented by yeun
					//PTZ ����� Ÿ�̸Ӹ� �̿��ؼ� ������ ���� �ɶ����� GC=L ��� ��û�ǰ� ��������
					//���ŵ� ��Ŷ�� �Ľ��ؼ� ������ ����
#if 0
					int iFind = strCmd.Find(_T(","));
					theApp.m_dPanDeg = atof(strCmd.Left(iFind));
					theApp.m_dTiltDeg = atof(strCmd.Mid(iFind + 1));

					//  [3/28/2014 Administrator]
					theApp.m_dBeOffsetPanDeg = theApp.PanDecToOffsetCalc(theApp.m_dPanDeg, theApp.m_dPanDegOffset);
					theApp.m_dBeOffsetTiltDeg = theApp.TiltDecToOffsetCalc(theApp.m_dTiltDeg, theApp.m_dTiltDegOffset);
#endif
					//Ŭ���̾�Ʈ�� ������/������ ����
					int iFind = strCmd.Find(_T(","));
					CString strPan = strCmd.Left(iFind);
					CString strTilt = strCmd.Mid(iFind + 1);;

					AUTHORITY_DATA data;
					sprintf((char*)data.data, "%s;%s", (CStringA)strPan, (CStringA)strTilt);

					TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_PTZREQ, CMDTYPE_PTZREQ_PANTILT_POS_RESP, data);
					//this->SendToAllAuthorityClient(nCh, CMDGROUP_PTZREQ, CMDTYPE_PTZREQ_PANTILT_POS_RESP, data);
				}
				else if (strCmd.GetLength() == 11)//GC=M   -> $0011100191,0067311 -> ParsedCmd : 00191,00673 -> 11
				{
#if 0
					int iFind = strCmd.Find(_T(","));
					theApp.m_iHighCamFocusAbs = atof(strCmd.Left(iFind));
					theApp.m_iHighCamZoomAbs = atof(strCmd.Mid(iFind + 1));
					m_pAssignedAutoMoveManager->SendMessageZoomFocusUpdateSignal();
#endif
					//Ŭ���̾�Ʈ�� �ְ�ī�޶� ��/��Ŀ�� ����
					int iFind = strCmd.Find(_T(","));
					CString strFocus = strCmd.Left(iFind);
					CString strZoom = strCmd.Mid(iFind + 1);;

					AUTHORITY_DATA data;
					sprintf((char*)data.data, "%s;%s", (CStringA)strZoom, (CStringA)strFocus);

					TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_PTZREQ, CMDTYPE_PTZREQ_DAYZF_POS_RESP, data);
					//this->SendToAllAuthorityClient(nCh, CMDGROUP_PTZREQ, CMDTYPE_PTZREQ_DAYZF_POS_RESP, data);
				}
				else if (strCmd.GetLength() == 29)//PG=000
				{
					//Ŭ���̾�Ʈ�� PTZF �� ����
					CString strTok_1, strTok_2, strTok_3, strTok_4, strTok_5;

					AfxExtractSubString(strTok_1, strCmd, 0, ',');
					AfxExtractSubString(strTok_2, strCmd, 1, ',');
					AfxExtractSubString(strTok_3, strCmd, 2, ',');
					AfxExtractSubString(strTok_4, strCmd, 3, ',');
									
					AUTHORITY_DATA data;
					sprintf((char*)data.data, "%s;%s;%s;%s", (CStringA)strTok_1, (CStringA)strTok_2, (CStringA)strTok_4, (CStringA)strTok_3);

					TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_PTZFABSMOVE, CMDTYPE_PTZFABSMOVE_RESP_SAVEPOS, data);
				}
				else if (strCmd.Find(_T("PW=O")) != -1)
				{
					AUTHORITY_DATA data;
					MakeAuthorityData(1, data);
					TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_POWERMGT, CMDTYPE_POWERMGT_SYS_PWR_STATUS, data);
				}
				else if (strCmd.Find(_T("PW=F")) != -1)
				{
					AUTHORITY_DATA data;
					MakeAuthorityData(2, data);
					TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_POWERMGT, CMDTYPE_POWERMGT_SYS_PWR_STATUS, data);
				}

				else if (strCmd.Find(_T("TP=O")) != -1)
				{
					AUTHORITY_DATA data;
					MakeAuthorityData(1, data);
					TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_POWERMGT, CMDTYPE_POWERMGT_THERMCAM_STATUS, data);
				}
				else if (strCmd.Find(_T("TP=F")) != -1)
				{
					AUTHORITY_DATA data;
					MakeAuthorityData(2, data);
					TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_POWERMGT, CMDTYPE_POWERMGT_THERMCAM_STATUS, data);
				}
				else if (strCmd.GetLength() == 24)//�ø��� ���� ���
				{
					byte packet[12] = { 0, };
					CU2SRProtoParser::StringHexaToByteHexa(strCmd, packet, 12);
					double dDZoom = CProtoFlirTau2::ParseDigitalZoomPacket(packet);

					AUTHORITY_DATA data;
					MakeAuthorityData(dDZoom, data);
					TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_THERMCAM, CMDTYPE_THERMCAM_DZOOM_RESP, data);
				}
			
			
			}
			if (nServiceCode == SET_OK_INT || nServiceCode == ERR_DEV_PWROFF_INT)//���������� ����� ���޵� Ack
			{
				if (strCmd.Find(_T("PW=O")) != -1)
				{
					AUTHORITY_DATA data;
					MakeAuthorityData(1, data);
					TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_POWERMGT, CMDTYPE_POWERMGT_SYS_PWR_STATUS, data);
				}
				else if (strCmd.Find(_T("PW=F")) != -1)
				{
					AUTHORITY_DATA data;
					MakeAuthorityData(2, data);
					TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_POWERMGT, CMDTYPE_POWERMGT_SYS_PWR_STATUS, data);
				}

				else if (strCmd.Find(_T("TP=O")) != -1)
				{
					AUTHORITY_DATA data;
					MakeAuthorityData(1, data);
					TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_POWERMGT, CMDTYPE_POWERMGT_THERMCAM_STATUS, data);
				}
				else if (strCmd.Find(_T("TP=F")) != -1)
				{
					AUTHORITY_DATA data;
					MakeAuthorityData(2, data);
					TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_POWERMGT, CMDTYPE_POWERMGT_THERMCAM_STATUS, data);
				}
			}

		}


		Sleep(1);
	}
	return 0;
}

UINT ReConnectionThread(void * pParam)
{
	int nCh = (*(int*)pParam);
	int nChIndex = nCh - 1;
	
	printf("ä��=%d TCPŬ���̾�Ʈ ReConnectionThread ������ \n", nCh);

	while (true)
	{
		Sleep(10000);
		
		if (g_bArrTCPClientConnection[nChIndex] == FALSE)
		{
			CreateTCPClientSocket(nCh, (CStringA)g_strArrServerIP[nChIndex], (u_short)g_nArrServerPort[nChIndex]);
#if 0
			//printf("ä��=%d ���� ���� ��Ŵ Ȯ�ε� \n", nCh);

			sockaddr_in target;
			target.sin_family = AF_INET;
			// target.sin_addr.s_addr = inet_addr("192.168.0.70");

			target.sin_addr.s_addr = inet_addr((CStringA)g_strArrServerIP[nChIndex]);
			target.sin_port = htons(g_nArrServerPort[nChIndex]);

			int result = ::connect(arrSockTCPClient[nChIndex], (SOCKADDR *)&target, sizeof(target));
			if (result == SOCKET_ERROR)
			{
				printf("ä��=%d TCPŬ���̾�Ʈ ����(%s, %d) �� ����(connect �Լ�) ����, ���� ��ȣ : %ld \n", nCh, (CStringA)g_strArrServerIP[nChIndex], g_nArrServerPort[nChIndex], WSAGetLastError());
				g_bArrTCPClientConnection[nChIndex] = FALSE;
				//break;
			}
			else
			{
				//WSAEISCONN 10056 Socket is already connected.
				//WSAENOTCONN 10057 Socket is not connected.
				//WSAECONNREFUSED 10061 Connection refused.
					
				printf("ä��=%d TCPŬ���̾�Ʈ ����(%s, %d) �� ����(connect �Լ�) ���� \n", nCh, (CStringA)g_strArrServerIP[nChIndex], g_nArrServerPort[nChIndex]);
				g_bArrTCPClientConnection[nChIndex] = TRUE;
			}
#endif
		}
		
		
		/*
		sockaddr addr;
		int nLen = sizeof(sockaddr);

		int nRet = ::getpeername(arrSockTCPClient[nChIndex], (struct sockaddr *)&addr, &nLen);
		if (nRet == 0)
		{

		}
		else
		{
			DWORD dwError = WSAGetLastError();

			//#define WSAEFAULT                        10014L

			if (dwError == WSAENOTCONN)
			{
				printf("ä��=%d ���� ���� ��Ŵ Ȯ�ε�(WSAENOTCONN) \n", nCh);

				
				
				
			}

		}
		*/

		
	}
	return 0;
}

void TCPClientReceiveFromPTZServer_ProcessServiceCode(int nCh, int nServiceCode)
{
	AUTHORITY_DATA data;
	if (nServiceCode == ERR_DEV_PWROFF_INT)//����� ���� ����̽� ������ ��������
	{
		//MakeAuthorityData(2, data);
		//TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_POWERMGT, CMDTYPE_POWERMGT_SYS_PWR_STATUS, data);
		//this->SendToAllAuthorityClient(nCh, CMDGROUP_ETCFUNC, CMDTYPE_ETCFUNC_PWR_STATUS, data);
		MakeAuthorityData(6, data);
		TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_PTZREQ, CMDTYPE_PTZREQ_MAINBOARD_STATUS_RESP, data);
	}
	else if (nServiceCode == SET_OK_INT)
	{
		//MakeAuthorityData(1, data);
		//TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_POWERMGT, CMDTYPE_POWERMGT_SYS_PWR_STATUS, data);
		//this->SendToAllAuthorityClient(nCh, CMDGROUP_ETCFUNC, CMDTYPE_ETCFUNC_PWR_STATUS, data);
		MakeAuthorityData(0, data);
		TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_PTZREQ, CMDTYPE_PTZREQ_MAINBOARD_STATUS_RESP, data);
	}
	else if (nServiceCode == GET_OK_INT)
	{
		MakeAuthorityData(1, data);
		TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_PTZREQ, CMDTYPE_PTZREQ_MAINBOARD_STATUS_RESP, data);
	}
	else if (nServiceCode == ERR_NOTSUPP_INT)
	{
		//Ŭ���̾�Ʈ�� �������� �ʴ� ����� ������ 
		MakeAuthorityData(3, data);
		TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_PTZREQ, CMDTYPE_PTZREQ_MAINBOARD_STATUS_RESP, data);
	}
	else if(nServiceCode == 9 )
	{
		MakeAuthorityData(9, data);
		TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_PTZREQ, CMDTYPE_PTZREQ_MAINBOARD_STATUS_RESP, data);
	}
	else if (nServiceCode == ERR_CANT_PROC_INT)
	{
		//������ ��� ������??? Ư���� ��� ó�� �Ұ�?
	}
	else
		ASSERT(FALSE);
	/*
	��0��: �ֿܼ��� ������ Set ����� ���������� ó����
	��1��: �ֿܼ��� ������ Get ��ɿ� ���� �������� ���� ���� ����
	��2��: ����� �����ν� �Ǿ����� ���� ����, �������� �������� ���� ������� ����
	��3��: ���ŵ� ����� �� �� ���� ��� �Ǵ� �������� �ʴ� ����Դϴ�
	��4��: DEVICE ���� �������
	��5��: ����� ���� Device�� ����Ǿ� ���� ����
	��6��: ����� ���� Device�� ������ ���� ���� ����
	��7��: ����� ���� Device�� �ش� ��ɿ� ���� ����Ʈ ���� ��
	��8��: ��ƿƮ�� ��ǥ�� �������� ����� ��ǥ�� �ƴ�
	��9��: ���� ����� �������� ������ �ƴ�(ASCII 0x20 ~ 0x7E�� �ƴ�) (����) 2011.1030 ���� ������ ����
	*/
}

void TCPClientReceiveFromPTZServer_PushAuthorityPacket(int nCh, BYTE byCmdGroup, BYTE byCmdType, AUTHORITY_DATA & authorityData)
{
	AUTHORITY_PACKET authorityPacket;

	authorityPacket.bySTX = PROTO_STX;

	sprintf(authorityPacket.srcName.name, "%s%02d", (CStringA)"AuthorityServer", nCh);

	authorityPacket.byCmdGroup = byCmdGroup;
	authorityPacket.byCmdType = byCmdType;
	authorityPacket.byETX = PROTO_ETX;

	memcpy(&authorityPacket.authorityData, &authorityData, sizeof(AUTHORITY_DATA));

	EnterCriticalSection(&g_csArrSendToAuthorityClient[nCh-1]);
	g_queuePakcetSendToAuthorityClient[nCh - 1].push(authorityPacket);
	LeaveCriticalSection(&g_csArrSendToAuthorityClient[nCh - 1]);

}
