// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// Hawkeye_PTZClient_AuthorityServer.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"

// TODO: 필요한 추가 헤더는
// 이 파일이 아닌 STDAFX.H에서 참조합니다.

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

//함수들..
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
	//PTZ와 연결 할 소켓
	//http://www.sysnet.pe.kr/Default.aspx?mode=2&sub=0&detail=1&pageno=0&wid=1473&rssMode=1&wtype=0
	int nIndex = nCh - 1;

#if 0 //기존소켓접속방식
	//SOCKET socket = INVALID_SOCKET;
	
	sockaddr_in target;
	target.sin_family = AF_INET;
	// target.sin_addr.s_addr = inet_addr("192.168.0.70");

	target.sin_addr.s_addr = inet_addr(ipAddr);
	target.sin_port = htons(nPort);

	

#if 0//타이아웃처리
	TIMEVAL Timeout;
	Timeout.tv_sec = 3000;
	Timeout.tv_usec = 0;
#endif

	arrSockTCPClient[nIndex] = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (arrSockTCPClient[nIndex] == INVALID_SOCKET)
	{
		printf("채널=%d TCP클라이언트 소켓 생성 실패, 에러 번호 : %ld \n", nCh, WSAGetLastError());
		nRet = false;
	}


#if 0 //타임아웃처리
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
		printf("채널=%d TCP클라이언트 서버(%s, %d) 접속(connect 함수) 실패, 에러 번호 : %ld \n", nCh, ipAddr, nPort, WSAGetLastError());
		g_bArrTCPClientConnection[nIndex] = FALSE;
		nRet = false;
	}
	else
	{
		printf("채널=%d TCP클라이언트 서버(%s, %d) 접속(connect 함수) 성공 \n", nCh, ipAddr, nPort );
		g_bArrTCPClientConnection[nIndex] = TRUE;
		nRet = true;

	}
#if 0//타이아웃처리
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

		//바이트를 뭉쳐서 프로토콜로 만드어 주는 클래스
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
			printf("채널=%d TCP클라이언트 소켓 종료 실패, 에러번호 : %ld \n", nCh, WSAGetLastError());
			return false;
		}

		arrSockTCPClient[nIndex] = INVALID_SOCKET;
		printf("채널=%d TCP클라이언트 소켓 종료 성공 \n", nCh);

		//printf("TCP Client socket: Closed\n");
	}
	else
	{
		printf("채널=%d TCP클라이언트 소켓이 이미 종료 되었음 \n", nCh);

	}
	
	return true;
}
//PTZServer로 전송
UINT SendToPTZServerThread(void * pParam)
{
	

	int nCh = (*(int*)pParam);
	int nChIndex = nCh - 1;

	printf("채널=%d TCP클라이언트 SendToPTZServerThread 생성됨 \n", nCh);
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
					printf("채널=%d TCP클라이언트 PTZServer에 패킷 전송 성공 %s \n", nCh, (const char *)byBuf);
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
	printf("채널=%d TCP클라이언트 ReceiveFromPTZServerThread 생성됨 \n", nCh);

	while (true)
	{
		int const bufSize = 4096;
		byte recvbuf[bufSize];

		//int iResult = recv(clientSock, recvbuf, bufSize, 0);
		int iResult = recv(arrSockTCPClient[nChIndex], (char*)recvbuf, bufSize, 0);
		if (iResult > 0)
		{
			printf("채널=%d TCP클라이언트 %d 바이트 수신함 \n", nCh, iResult);
			//printf("Bytes received: %d\n", iResult);
			g_bArrTCPClientConnection[nChIndex] = TRUE;
		}
		else if (iResult == 0)
		{
			//printf("Connection closed\n");
			//WSAENOTSOCK 10038 Socket operation on nonsocket.
			printf("채널=%d recv 함수 에러 리턴값=%d %d\n", nCh, iResult, WSAGetLastError());

			g_bArrTCPClientConnection[nChIndex] = FALSE;
			ReleaseTCPClientSocket(nCh);
			Sleep(5000);
			continue;
		}
		else
		{
			//WSAENOTCONN
			//WSAECONNRESET 10054 Connection reset by peer.
			//printf("채널=%d recv failed with error: %d\n", nCh, WSAGetLastError());
			printf("채널=%d TCP클라이언트 recv() 함수 에러 리턴값=%d %d\n", nCh, iResult, WSAGetLastError());
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

		//made = $00004HM = CD3//보내는명령
		//made = $00104HM = PC5//
		//printf("ParsedCmd : %s \n", (CStringA)strCmd);
		printf("채널=%d TCP클라이언트 패킷 파싱 : %s \n", nCh, (CStringA)strCmd);
		//get명령 Queue를 만들어서 보낸 명령이 뭐인지 확인하고 파싱 하는 방법?
		//커맨드 길이를 보고 판단하는방법
		//GC     : 29
		//GC=L   -> $00117067.7664,-03.483517 -> ParsedCmd : 067.7664,-03.4835 -> 17
		//GC=M	 : 11
		//GS=P	 : 2
		//GS=T	 : 2
		//PW=? L : PW=O or PW=F 로 날라옴 구분하면 상태 파싱 가능
		//PP=001:022.5000,+00.0000,50000,50000 -> $00036PP=001:022.5000,+00.0000,50000,500002A 
		//GC=M   -> $0011100191,0067311 -> ParsedCmd : 00191,00673 -> 11
		//GC=G

		//서비스 코드 처리
		
		if (nServiceCode == -1)
			continue;

		TCPClientReceiveFromPTZServer_ProcessServiceCode(nCh, nServiceCode);

		int nLen = strCmd.GetLength();

		if (strCmd.GetLength() != 0)
		{
			//제어권 패킷으로 변환하여 클라이언트들에게 전송한다.
			
			if (nServiceCode == GET_OK_INT || nServiceCode == ERR_DEV_PWROFF_INT)//정상적으로 리턴을 받음
			{				
				if (strCmd.GetLength() == 2)
				{
					CString strStatus = CU2SRProtoParser::Util_ConvertAscii2Hexa(strCmd);	// [40] => [64]
					strStatus = CU2SRProtoParser::Util_GetBinaryData(strStatus);		// [64] => [00000010]

					char chMoving = strStatus.GetAt(3);
					if (chMoving == '1')//이동중
					{
						//MSB         LSB
						//7 6 5 4 3 2 1 0
						/*
						bit7 : motor unconnected, bit6 : undefined,	bit5 : Pan 센터센서 동작, bit4 : motor busy(모터 동작 중),
						bit3 : homming(모터 Center 위치), bit2 : position error, (모터 위치인식 error), bit1 : limitte left 동작, bit0 : limitte right 동작
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
						//모터 정지 상태
						AUTHORITY_DATA data;
						MakeAuthorityData(2, data);
						TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_PTZREQ, CMDTYPE_PTZREQ_PAN_MOVESTATUS_RESP, data);
					}

					char chPanInit = strStatus.GetAt(5);//팬모터 초기화 상태
					if (chPanInit == '1')//모터위치인식에러
					{
						AUTHORITY_DATA data;
						MakeAuthorityData(2, data);
						TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_PTZREQ, CMDTYPE_PTZREQ_PAN_INITSTATUS_RESP, data);
						//this->SendToAllAuthorityClient(nCh, CMDGROUP_ETCFUNC, CMDTYPE_ETCFUNC_PANTILT_MOTOR_ADJUSTMENT_STATUS, data);
					}
					else if (chPanInit == '0')//정상
					{
						AUTHORITY_DATA data;
						MakeAuthorityData(1, data);
						TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_PTZREQ, CMDTYPE_PTZREQ_PAN_INITSTATUS_RESP, data);
						//this->SendToAllAuthorityClient(nCh, CMDGROUP_ETCFUNC, CMDTYPE_ETCFUNC_PANTILT_MOTOR_ADJUSTMENT_STATUS, data);
					}
				}
				else if (strCmd.Find(_T("HM=C")) != -1)//센터 이동 완료
				{
					//HM=C 명령을 보내면 같은 명령이 ack된다.
					//현재상태가 아직 자동 상태확인 설정이 안되어있고 / 홈위치 완료가 안된 상태이면

					//초기화가 완료되면 HM=C 상태가 ACK 된다.

					//완료설정을한다.

					//m_arrPTZInfo[nChIndex].bHomePostionCompleted = TRUE;
					AUTHORITY_DATA data;
					MakeAuthorityData(2, data);
					TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_PANTILTINIT, CMDTYPE_PANTILTINIT_RESP_HOMEPOS, data);
				
				}
				else if ((strCmd.Find(_T("HM=P")) != -1 || strCmd.Find(_T("HM=T")) != -1))//센터 이동중을 의미하는 ack
				{
					//m_arrPTZInfo[nChIndex].bHomePostionCompleted = FALSE;

					AUTHORITY_DATA data;
					MakeAuthorityData(1, data);
					TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_PANTILTINIT, CMDTYPE_PANTILTINIT_RESP_HOMEPOS, data);
				}
				else if (strCmd.GetLength() == 17)////GC=L   -> $00117067.7664,-03.483517 -> ParsedCmd : 067.7664,-03.4835 -> 17
				{
					//160107 commented by yeun
					//PTZ 제어시 타이머를 이용해서 정지을 전송 될때까지 GC=L 계속 요청되게 구현했음
					//수신데 패킷을 파싱해서 변수에 저장
#if 0
					int iFind = strCmd.Find(_T(","));
					theApp.m_dPanDeg = atof(strCmd.Left(iFind));
					theApp.m_dTiltDeg = atof(strCmd.Mid(iFind + 1));

					//  [3/28/2014 Administrator]
					theApp.m_dBeOffsetPanDeg = theApp.PanDecToOffsetCalc(theApp.m_dPanDeg, theApp.m_dPanDegOffset);
					theApp.m_dBeOffsetTiltDeg = theApp.TiltDecToOffsetCalc(theApp.m_dTiltDeg, theApp.m_dTiltDegOffset);
#endif
					//클라이언트로 방위각/고저각 전송
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
					//클라이언트로 주간카메라 줌/포커스 전송
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
					//클라이언트로 PTZF 값 전송
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
				else if (strCmd.GetLength() == 24)//플리어 열상 명령
				{
					byte packet[12] = { 0, };
					CU2SRProtoParser::StringHexaToByteHexa(strCmd, packet, 12);
					double dDZoom = CProtoFlirTau2::ParseDigitalZoomPacket(packet);

					AUTHORITY_DATA data;
					MakeAuthorityData(dDZoom, data);
					TCPClientReceiveFromPTZServer_PushAuthorityPacket(nCh, CMDGROUP_THERMCAM, CMDTYPE_THERMCAM_DZOOM_RESP, data);
				}
			
			
			}
			if (nServiceCode == SET_OK_INT || nServiceCode == ERR_DEV_PWROFF_INT)//정상적으로 명령이 전달됨 Ack
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
	
	printf("채널=%d TCP클라이언트 ReConnectionThread 생성됨 \n", nCh);

	while (true)
	{
		Sleep(10000);
		
		if (g_bArrTCPClientConnection[nChIndex] == FALSE)
		{
			CreateTCPClientSocket(nCh, (CStringA)g_strArrServerIP[nChIndex], (u_short)g_nArrServerPort[nChIndex]);
#if 0
			//printf("채널=%d 소켓 연결 끊킴 확인됨 \n", nCh);

			sockaddr_in target;
			target.sin_family = AF_INET;
			// target.sin_addr.s_addr = inet_addr("192.168.0.70");

			target.sin_addr.s_addr = inet_addr((CStringA)g_strArrServerIP[nChIndex]);
			target.sin_port = htons(g_nArrServerPort[nChIndex]);

			int result = ::connect(arrSockTCPClient[nChIndex], (SOCKADDR *)&target, sizeof(target));
			if (result == SOCKET_ERROR)
			{
				printf("채널=%d TCP클라이언트 서버(%s, %d) 재 접속(connect 함수) 실패, 에러 번호 : %ld \n", nCh, (CStringA)g_strArrServerIP[nChIndex], g_nArrServerPort[nChIndex], WSAGetLastError());
				g_bArrTCPClientConnection[nChIndex] = FALSE;
				//break;
			}
			else
			{
				//WSAEISCONN 10056 Socket is already connected.
				//WSAENOTCONN 10057 Socket is not connected.
				//WSAECONNREFUSED 10061 Connection refused.
					
				printf("채널=%d TCP클라이언트 서버(%s, %d) 재 접속(connect 함수) 성공 \n", nCh, (CStringA)g_strArrServerIP[nChIndex], g_nArrServerPort[nChIndex]);
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
				printf("채널=%d 소켓 연결 끊킴 확인됨(WSAENOTCONN) \n", nCh);

				
				
				
			}

		}
		*/

		
	}
	return 0;
}

void TCPClientReceiveFromPTZServer_ProcessServiceCode(int nCh, int nServiceCode)
{
	AUTHORITY_DATA data;
	if (nServiceCode == ERR_DEV_PWROFF_INT)//명령을 보낸 디바이스 전원이 꺼져있음
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
		//클라이언트가 지원되지 않는 명령을 보냈음 
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
		//프리셋 명령 실행중??? 특정한 명령 처리 불가?
	}
	else
		ASSERT(FALSE);
	/*
	“0”: 콘솔에서 보내는 Set 명령이 정상적으로 처리됨
	“1”: 콘솔에서 보내는 Get 명령에 대한 정상적인 리턴 값을 받음
	“2”: 명령은 정상인식 되었으나 값의 오류, 부적절한 조건으로 인해 실행되지 못함
	“3”: 수신된 명령이 알 수 없는 명령 또는 지원하지 않는 명령입니다
	“4”: DEVICE 에서 통신지연
	“5”: 명령을 보낸 Device가 연결되어 있지 않음
	“6”: 명령을 보낸 Device가 전원이 켜져 있지 않음
	“7”: 명령을 보낸 Device가 해당 명령에 대한 리미트 상태 임
	“8”: 팬틸트의 좌표가 관측지에 동기된 좌표가 아님
	“9”: 보낸 명령이 정상적인 포맷이 아님(ASCII 0x20 ~ 0x7E가 아님) (참고) 2011.1030 이후 버전에 한함
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
