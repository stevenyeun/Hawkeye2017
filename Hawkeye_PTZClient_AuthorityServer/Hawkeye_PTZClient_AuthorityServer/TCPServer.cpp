#include "stdafx.h"



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//TCP Server
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//https://www.codeproject.com/Articles/1922/Beginning-Winsock-Programming-Multithreaded-TCP-se
//http://dbckdgns0515.tistory.com/entry/WindowsTCP-%EC%98%88%EC%A0%9C-%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8D-serverclient


bool ReleaseClientOfTCPServerSocket(int nCh, SOCKET sockClient);
void ProcessCmdGroupAuthority(int nCh, const AUTHORITY_PACKET* pAuthorityPacket);
void ProcessCmdGroupPTZCtrl(int nCh, BYTE byCmdType, AUTHORITY_DATA& authorityData);
void ProcessCmdGroupPTZReq(int nCh, BYTE byCmdType, AUTHORITY_DATA & authorityData);
void ProcessCmdGroupETCFunc(int nCh, BYTE byCmdType, AUTHORITY_DATA & authorityData);
void ProcessCmdGroupPowerMgt(int nCh, BYTE byCmdType, AUTHORITY_DATA & authorityData);
void ProcessCmdGroupPanTiltInit(int nCh, BYTE byCmdType, AUTHORITY_DATA & authorityData);
void ProcessCmdGroupAbsMove(int nCh, BYTE byCmdType, AUTHORITY_DATA & authorityData);
void ProcessCmdGroupThermalCam(int nCh, BYTE byCmdType, AUTHORITY_DATA & authorityData);
void ProcessCmdGroupETCDevice(int nCh, BYTE byCmdType, AUTHORITY_DATA & authorityData);
void ProcessCmdGroupDayLensCtrl(int nCh, BYTE byCmdType, AUTHORITY_DATA & authorityData);

UINT ProcessReceivedPacketThread(void * pParam);

typedef struct _SOCKET_THREAD_INFO
{
	_SOCKET_THREAD_INFO(void)
	{
		port = 0;
		nCh = 0;
	}
	u_short port;
	int nCh;
	SOCKET hSock;

}SOCKET_THREAD_INFO;



SOCKET_THREAD_INFO g_arrTCPServerInfo[MAX_CHANNEL_NUM];
SOCKET_THREAD_INFO g_arrTCPServerClientInfo[MAX_CHANNEL_NUM];

CWinThread * arrTCPServerThread[MAX_CHANNEL_NUM] = { NULL, };
CWinThread * arrSendToAuthorityClientThread[MAX_CHANNEL_NUM] = { NULL, };
CWinThread * arrReceiveFromAuthorityClientThread[MAX_CHANNEL_NUM] = { NULL, };
CWinThread * g_pArrProcessReceivedPacketFromAuthorityClientThread[MAX_CHANNEL_NUM] = { NULL, };


SOCKET arrSockTCPServer[MAX_CHANNEL_NUM]{ INVALID_SOCKET, };

//steven171008
SOCKET g_arrSockMulticastSender[MAX_CHANNEL_NUM]{ INVALID_SOCKET, };
CString g_arrDestAddr[MAX_CHANNEL_NUM];
int g_arrDestPort[MAX_CHANNEL_NUM];

SOCKET arrSockMulticastReceiver[MAX_CHANNEL_NUM]{ INVALID_SOCKET, };

BOOL g_bArrExitrProcessReceivedPacketFromAuthorityClientThread[MAX_CHANNEL_NUM] = { FALSE, };

//////////////////////////////////////////////////////////////////////
queue<AUTHORITY_PACKET> g_queuePakcetReceivedPakcetFromAuthorityClient[MAX_CHANNEL_NUM];
queue<AUTHORITY_PACKET> g_queuePakcetSendToAuthorityClient[MAX_CHANNEL_NUM];
CRITICAL_SECTION g_csArrSendToAuthorityClient[MAX_CHANNEL_NUM];

extern queue<CMD> g_queueSendToPTZCommand[MAX_CHANNEL_NUM];

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

#if 1
//패킷처리
UINT ProcessReceivedPacketThread(void * pParam)
{
	int nCh = *((int*)pParam);
	int nChIndex = nCh - 1;

	printf("채널=%d TCP클라이언트 ProcessReceivedPacketThread 생성됨 \n", nCh);

	//printf("Ch = %d ProcessReceivedPacketThread Start \n", nCh);

	while (1)
	{
		if (g_bArrExitrProcessReceivedPacketFromAuthorityClientThread[nChIndex] == TRUE)
			break;

		if (g_queuePakcetReceivedPakcetFromAuthorityClient[nChIndex].size() > 0)
		{
			//패킷 분석해서 호크아이명령으로 변환
			//수신된 명령을 화면에 에디트 박스에 뿌려준다.
			AUTHORITY_PACKET packet = g_queuePakcetReceivedPakcetFromAuthorityClient[nChIndex].front();
			g_queuePakcetReceivedPakcetFromAuthorityClient[nChIndex].pop();
			CString strRecv = ConvertAuthorityPacketToString(&packet);//제어권패킷을 스트링으로 바꾸기
			//printf( (CStringA)strRecv + "\n");
			printf("채널=%d TCP클라이언트 제어권 패킷 수신 %s \n", nCh, (CStringA)strRecv);
			//PTZ 송신 큐에 저장
			//제어권한 관련 명령 처리
			if (packet.byCmdGroup == CMDGROUP_AUTHORITY)
			{
				ProcessCmdGroupAuthority(nCh, &packet);
			}
			else//제어권한 명령 외 제어명령 처리
			{
				switch (packet.byCmdGroup)
				{
				case CMDGROUP_PTZCTRL:
					//if (GetPTZAutomaticMoving(nCh) == FALSE)//자동화 이동 중이면 클라이언트 제어 명령 처리안함
					ProcessCmdGroupPTZCtrl(nCh, packet.byCmdType, packet.authorityData);
					break;
				case CMDGROUP_PTZREQ:
					ProcessCmdGroupPTZReq(nCh, packet.byCmdType, packet.authorityData);
					break;
				case CMDGROUP_DAYCAM:
					ProcessCmdGroupDayLensCtrl(nCh, packet.byCmdType, packet.authorityData);
					//ProcessCmdGroupDayCam(nCh, pAuthPacket->byCmdType, pAuthPacket->authorityData);
					break;
				case CMDGROUP_THERMCAM:
					ProcessCmdGroupThermalCam(nCh, packet.byCmdType, packet.authorityData);
					break;
				case CMDGROUP_POWERMGT:
					ProcessCmdGroupPowerMgt(nCh, packet.byCmdType, packet.authorityData);
					break;
				case CMDGROUP_PANTILTINIT:
					ProcessCmdGroupPanTiltInit(nCh, packet.byCmdType, packet.authorityData);
					break;
				case CMDGROUP_PTZFABSMOVE:
					ProcessCmdGroupAbsMove(nCh, packet.byCmdType, packet.authorityData);
					break;
				case CMDGROUP_ETCFUNC://기타기능
					ProcessCmdGroupETCFunc(nCh, packet.byCmdType, packet.authorityData);
					break;
				case CMDGROUP_ETC_DEVICE:
					ProcessCmdGroupETCDevice(nCh, packet.byCmdType, packet.authorityData);
					break;
					/*
				case CMDGROUP_ETC_LINK:
					break;
					*/
				default:
					ASSERT(FALSE);
					break;
				}
			}

			//m_dlgPTZCliAuthSvrConf.SetTextFromAuthClient(nCh, strRecv + _T("\r\n"));
			////////////////////////////////////////////////////////////////////////////////////////////////
		}
		Sleep(1);
	}

	printf("Ch = %d ProcessReceivedPacketThread Exit \n", nCh);
	return 0;
}
#endif

UINT SendToAuthorityClientThread(PVOID lpParam)
{
#if 1
	int nCh = *((int*)lpParam);
	int nIndex = nCh - 1;
	
	printf("채널=%d TCP SendToAuthorityClientThread 생성됨 \n", nCh);

	SOCKET clientSock = g_arrTCPServerClientInfo[nIndex].hSock;

	while (true)
	{
		EnterCriticalSection(&g_csArrSendToAuthorityClient[nIndex]);
		if (g_queuePakcetSendToAuthorityClient[nIndex].size() > 0)
		{
			AUTHORITY_PACKET packet;

			printf("채널=%d TCP서버 제어권 클라이언트로 QueueSize=%d \n", nCh, g_queuePakcetSendToAuthorityClient[nIndex].size());
			
			
		
			packet = g_queuePakcetSendToAuthorityClient[nIndex].front();//에러 발생 
			g_queuePakcetSendToAuthorityClient[nIndex].pop();
		

			//int const bufSize = sizeof(AUTHORITY_PACKET);
			//char sendBuf[bufSize];

			int iResult = send(clientSock, (const char*)&packet, sizeof(AUTHORITY_PACKET), 0);
			if (iResult > 0)
			{
				CString strRecv = ConvertAuthorityPacketToString(&packet);//제어권패킷을 스트링으로 바꾸기
				//printf((CStringA)strRecv + "\n");
				printf("채널=%d TCP서버 제어권 클라이언트로 전송 성공 %s \n", nCh, (CStringA)strRecv);
			}
			if (iResult == SOCKET_ERROR) {
				printf("채널=%d TCP서버 제어권 클라이언트로 전송 실패, 에러번호 : %ld  \n", nCh, WSAGetLastError());
				//printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(clientSock);
				WSACleanup();
				break;
			}

#if 1//멀티캐스트 전송
			sockaddr_in send_addr;
			memset(&send_addr, 0, sizeof(SOCKADDR_IN));
			send_addr.sin_family = AF_INET;
			send_addr.sin_addr.s_addr = inet_addr(LPSTR(LPCTSTR(g_arrDestAddr[nIndex])));					// this is our test destination IP
			send_addr.sin_port = htons(g_arrDestPort[nIndex]);
			if (sendto(g_arrSockMulticastSender[nIndex], (const char*)&packet, sizeof(AUTHORITY_PACKET), MSG_DONTROUTE, (sockaddr*)&send_addr, sizeof(send_addr)) == INVALID_SOCKET)
			{
				printf("\nError in Sending data on the socket - %d", WSAGetLastError());
				WSACleanup();
				exit(-1);
			}
#endif





		}
		LeaveCriticalSection(&g_csArrSendToAuthorityClient[nIndex]);
		Sleep(1);
	}
#endif
	return 0;
}
UINT ReceiveFromAuthorityClientThread(PVOID lpParam)
{
#if 1//z
	int nCh = *((int*)lpParam);
	int nIndex = nCh - 1;

	printf("채널=%d TCP ReceiveFromAuthorityClientThread 생성됨 \n", nCh);

	SOCKET clientSock = g_arrTCPServerClientInfo[nIndex].hSock;

	while (true)
	{
		int const bufSize = sizeof(AUTHORITY_PACKET);
		char recvbuf[bufSize];
		AUTHORITY_PACKET packet;
		//int iResult = recv(clientSock, recvbuf, bufSize, 0);
		int iResult = recv(clientSock, (char *)&packet, sizeof(AUTHORITY_PACKET), 0);
		if (iResult > 0)
			printf("Bytes received: %d\n", iResult);
		else if (iResult == 0)
		{
			printf("Connection closed\n");
			ReleaseClientOfTCPServerSocket(nCh, clientSock);
			Sleep(5000);
			return 0;
		}
		else
		{
			printf("recv failed with error: %d\n", WSAGetLastError());
			ReleaseClientOfTCPServerSocket(nCh, clientSock);
			Sleep(5000);
			return 0;
		}

		//제어권 클라이언트로 온 패킷 저장
		//PTZ서버로 보낼거임
		g_queuePakcetReceivedPakcetFromAuthorityClient[nIndex].push(packet);
		Sleep(1);
	}
#endif
	return 0;
}


UINT TCPServerThread(PVOID lpParam)
{

	int nCh = *((int*)lpParam);
	int nChIndex = nCh - 1;
	int port = g_arrTCPServerInfo[nChIndex].port;

	printf("채널=%d TCP서버(%d) TCPServerThread 생성됨 \n", nCh, port); 


	WSADATA wsaData;
	SOCKET hServSock;
	SOCKET hClntSock;
	SOCKADDR_IN servAddr;
	SOCKADDR_IN clntAddr;
	int szClntAddr;

	hServSock = ::socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
	{
		ErrorHandling("socket() error");
	}
	g_arrTCPServerInfo[nChIndex].hSock = hServSock;

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port);

	// 소켓에 주소 할당
	if (::bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		ErrorHandling("bind() error");
	}

	// 연결 요청 대기 상태
	if (::listen(hServSock, 5) == SOCKET_ERROR)
	{
		ErrorHandling("listen() error");
	}

	while (true)
	{
		// 연결 요청 수락
		szClntAddr = sizeof(clntAddr);
		printf("채널=%d TCP서버 클라이언트 접속 대기중 \n", nCh);
		hClntSock = ::accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);
		printf("채널=%d TCP서버 클라이언트 접속함 \n", nCh); 	

		if (hClntSock == INVALID_SOCKET)
		{
			ErrorHandling("accept() error");
		}

		g_arrTCPServerClientInfo[nChIndex].hSock = hClntSock;
		g_arrTCPServerClientInfo[nChIndex].port = clntAddr.sin_port;


		//클라이언트 스레드 처리		
		if (arrSendToAuthorityClientThread[nChIndex] == NULL)
		{
			AfxBeginThread(SendToAuthorityClientThread, &nCh, THREAD_PRIORITY_NORMAL);
			Sleep(1000);
		}
		if (arrReceiveFromAuthorityClientThread[nChIndex] == NULL)
		{
			AfxBeginThread(ReceiveFromAuthorityClientThread, &nCh, THREAD_PRIORITY_NORMAL);
			Sleep(1000);
		}
		

#if 0
		//송신 스레드
		//arrSendToAuthorityClientThread[nChIndex] = new thread(SendToAuthorityClientThread, nCh);
		//_beginthread(SendToAuthorityClientThread, 0, &nCh);
		DWORD dwThreadId = 1;
		DWORD dwThrdParam = nCh;
		//arrSendToAuthorityClientThread[nChIndex] = ::CreateThread(NULL, 0, SendToAuthorityClientThread, &nCh, 0, &dwThreadId);
		Sleep(1000);
		printf("The thread ID: %d\n", dwThreadId);

		if (arrSendToAuthorityClientThread[nChIndex] == NULL)
			printf("TCPServerThread CreateThread() failed, error : %d\n", GetLastError());
		else
			printf("TCPServerThreads CreateThread() is OK!\n");

		//수신 스레드
		//arrReceiveFromAuthorityClientThread[nChIndex] = new thread(ReceiveFromAuthorityClientThread, nCh);
		//_beginthread(ReceiveFromAuthorityClientThread, 0, &nCh);
		arrReceiveFromAuthorityClientThread[nChIndex] = ::CreateThread(NULL, 0, ReceiveFromAuthorityClientThread, &nCh, 0, &dwThreadId);
		Sleep(1000);
		printf("The thread ID: %d\n", dwThreadId);

		if (arrReceiveFromAuthorityClientThread[nChIndex] == NULL)
			printf("TCPServerThread CreateThread() failed, error : %d\n", GetLastError());
		else
			printf("TCPServerThreads CreateThread() is OK!\n");
#endif
	}

}



void CreateMulticastSenderReceiverSocket(int nCh, char * destAddress, int destPort, int recvPort)
{

	

	int ttlValue = 32;					// TTL
	int err;

	g_arrDestAddr[nCh - 1].Format(_T("%s"), destAddress);
	g_arrDestPort[nCh - 1] = destPort;


	WSADATA WSAData;

	err = WSAStartup(MAKEWORD(2, 2), &WSAData);
	if (err)
	{
		printf("WSAStartup Failed (%d) Exiting\n", err);
		exit(err);
	}

#if 1
	// Create a normal UDP socket for sending data
	g_arrSockMulticastSender[nCh-1] = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (g_arrSockMulticastSender[nCh - 1] == INVALID_SOCKET)
	{
		err = GetLastError();
		printf("\"Socket\" failed with error %d\n", err);
		exit(-1);
	}

	sockaddr_in send_addr;
	memset(&send_addr, 0, sizeof(SOCKADDR_IN));
	send_addr.sin_family = AF_INET;
	send_addr.sin_addr.s_addr = inet_addr(destAddress);					// this is our test destination IP
	send_addr.sin_port = htons(destPort);

	// Set the Time-to-Live of the multicast
	if (setsockopt(g_arrSockMulticastSender[nCh - 1], IPPROTO_IP, IP_MULTICAST_TTL, (char *)&ttlValue, sizeof(int)) == SOCKET_ERROR)
	{
		printf("Error: Setting TTL value: error - %d\n", WSAGetLastError());
		closesocket(g_arrSockMulticastSender[nCh - 1]);
		exit(-1);
	}
	CString text; text.Format(_T("%02dch Hi~"), nCh);

	if (sendto(g_arrSockMulticastSender [nCh - 1], (CStringA)text, text.GetLength(), MSG_DONTROUTE, (sockaddr*)&send_addr, sizeof(send_addr)) == INVALID_SOCKET)
	{
		printf("\nError in Sending data on the socket - %d", WSAGetLastError());
		WSACleanup();
		exit(-1);
	}

	//printf("\nSuccess: Setting TTL value - %d\n", ttlValue);

	//printf("\ndestAddress = %s\n", destAddress);
	//printf("destPort    = %d\n", destPort);
	//printf("dscpValue   = %d\n", dscpValue);
	//printf("ttlValue    = %d\n", ttlValue);
	//printf("waitValue   = %d ms\n", waitValue);

	// Get System Local Time and send a Multicast packet
	//printf("\nSending...\n");
#endif




#if 1
	// Create a normal UDP socket for sending data
	arrSockMulticastReceiver[nCh-1] = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (arrSockMulticastReceiver[nCh - 1] == INVALID_SOCKET)
	{
		err = GetLastError();
		printf("\"Socket\" failed with error %d\n", err);
		exit(-1);
	}

	char time_message[100];					// ASCII string 
	int iRecvLen;							// Length of receive_addr
	SYSTEMTIME *lpstLocTime;
	lpstLocTime = (SYSTEMTIME *)(time_message);

	sockaddr_in receive_addr;		// Local socket's address. Holds the source address upon recvfrom function returns
	receive_addr.sin_family = AF_INET;
	receive_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	receive_addr.sin_port = htons(recvPort);
	iRecvLen = sizeof(receive_addr);

	// Binding the socket to the address. Only necessary on receiver
	if (::bind(arrSockMulticastReceiver[nCh-1], (sockaddr*)&receive_addr, sizeof(receive_addr)) == SOCKET_ERROR)
	{
		printf("\nError: Binding the socket - %d", WSAGetLastError());
		WSACleanup();
		exit(-1);
	}
	

	printf("\nSuccess: Binding the socket - %d", WSAGetLastError());

	ip_mreq req;
	req.imr_multiaddr.s_addr = inet_addr(destAddress);
	req.imr_interface.s_addr = INADDR_ANY;
	// Joining a multicast group
	if (setsockopt(arrSockMulticastReceiver[nCh - 1], IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&req, sizeof(req)) == -1)
	{
		printf("\nError: Joining Multicast Group - %d", WSAGetLastError());
		WSACleanup();
		exit(-1);
	}
	printf("\nSuccess: Joining Multicast Group - %d\n", WSAGetLastError());

	//printf("\ndestAddress = %s\n", destAddress);
	//printf("destPort    = %d\n", recvPort);


	// Receive data from the multicasting groupf server.
	//printf("\nReceiving...\n");
#endif
}

void CreateTCPServerSocket(int nCh, u_short port)
{
	//AuthorityServer
	//thread *arrSocketSendToAuthorityClientThread[MAX_CHANNEL_NUM];
	//thread *arrSocketReceiveFromAuthorityClientThread[MAX_CHANNEL_NUM];
	//SOCKET arrSockTCPServer[MAX_CHANNEL_NUM]{ INVALID_SOCKET, };
	// 서버 소켓 생성


	int nChIndex = nCh - 1;

	g_arrTCPServerInfo[nChIndex].nCh = nCh;
	g_arrTCPServerInfo[nChIndex].port = port;

	if (arrTCPServerThread[nChIndex] == NULL)
	{
		arrTCPServerThread[nChIndex] = AfxBeginThread(TCPServerThread, &nCh, THREAD_PRIORITY_NORMAL);
		Sleep(1000);
	}


#if 0
	//arrTCPServerThread[nChIndex] = new thread(TCPServerThread, 0);
	int nTempCh = nCh;
	//::_beginthread(TCPServerThread, 0, &nTempCh);


	DWORD dwThreadId = 1;
	DWORD dwThrdParam = nCh;

	arrTCPServerThread[nChIndex] = ::CreateThread(NULL, 0, TCPServerThread, &dwThrdParam, 0, &dwThreadId);
	Sleep(1000);
	printf("The thread ID: %d\n", dwThreadId);

	if (arrTCPServerThread[nChIndex] == NULL)
		printf("TCPServerThread CreateThread() failed, error : %d\n", GetLastError());
	else
		printf("TCPServerThreads CreateThread() is OK!\n");

	/*
	if (CloseHandle(arrTCPServerThread[nChIndex]) != 0)
	printf("TCPServerThread Handle to thread closed successfully.\n");
	*/
#endif
}


bool ReleaseClientOfTCPServerSocket(int nCh, SOCKET sockClient)
{
	int nIndex = nCh - 1;

	if (sockClient != INVALID_SOCKET)
	{
		int result = ::closesocket(sockClient);
		if (result == SOCKET_ERROR)
		{
			printf("채널=%d TCP서버의 클라이언트 소켓 종료 실패, 에러번호 : %ld \n", nCh, WSAGetLastError());
			return false;
		}

		//arrSockTCPServer[nIndex] = INVALID_SOCKET;
		printf("채널=%d TCP서버의 클라이언트 소켓 종료 성공 \n", nCh);

		//printf("TCP Client socket: Closed\n");
	}
	else
	{
		printf("채널=%d TCP서버 소켓이 이미 종료 되었음 \n", nCh);

	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//제어권 패킷 처리
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//void ProcessCmdGroupAuthority(int nCh, const AUTHORITY_PACKET* pAuthorityPacket, DWORD dwIPAddr, UINT uPort)
void ProcessCmdGroupAuthority(int nCh, const AUTHORITY_PACKET* pAuthorityPacket)
{
	switch (pAuthorityPacket->byCmdType)
	{
	case CMDTYPE_AUTHORITY_LOGIN:
	{
		AUTHORITY_CLIENT_INFO authCliInfo;
		sprintf(authCliInfo.cstrSrcName, "%s", pAuthorityPacket->srcName.name);

		//authCliInfo.connectioninfo.dwIPAddr = dwIPAddr;
		//authCliInfo.connectioninfo.uPort = uPort;

		//m_dlgAuthManagement.AddAuthorityClientInfo(nCh, authCliInfo);
	}
	break;

	case CMDTYPE_AUTHORITY_TEMPAUTHORITY_USE_NOTIFICATION://임시제어권 제어권 사용 시작 통보
	{
		//ProcessRadarTempAuthorityUsingStart(nCh);

		//m_dlgAuthManagement.SetRadarTempAuthorityUsingTime(nCh, RADAR_USINGTIME_TIMEOUT);

		//만약 프리셋 이동중이면 pause시킨다.
		//PausePresetMoving(nCh);

		//클라이언트들에게 알림
		//AUTHORITY_DATA data;
		//this->SendToAllAuthorityClient(nCh, CMDGROUP_AUTHORITY, CMDTYPE_AUTHORITY_TEMPAUTHORITY_USE_NOTIFICATION, data);
	}

	break;

	case CMDTYPE_AUTHORITY_TEMPAUTHORITY_RETURN_NOTIFICATION://제어권 반환 통보
	{
		//ProcessRadarTempAuthorityReturnNotification(nCh);

		//m_dlgAuthManagement.SetRadarTempAuthorityUsingTime(nCh, RADAR_USINGTIME_TIMEOUT);

		//만약 제어권 반납전에 프리셋 이동중이였으면 다시 시작 한다.
		//ResumePresetMoving(nCh);

		//클라이언트들에게 알림
		AUTHORITY_DATA data;
		//this->SendToAllAuthorityClient(nCh, CMDGROUP_AUTHORITY, CMDTYPE_AUTHORITY_TEMPAUTHORITY_RETURN_NOTIFICATION, data);

		//체크박스 해제
		//m_dlgAuthManagement.SetIsRadarTempAuthority(nCh, FALSE);


	}
	break;
	case CMDTYPE_AUTHORITY_TEMPAUTHORITY_INUSE_NOTIFICATION://제어권을 사용중임을 통보
	{
		//ProcessRadarTempAuthorityInuseNotification(nCh);

		//클라이언트들에게 알림
		AUTHORITY_DATA data;
		//this->SendToAllAuthorityClient(nCh, CMDGROUP_AUTHORITY, CMDTYPE_AUTHORITY_TEMPAUTHORITY_INUSE_NOTIFICATION, data);

		//체크박스 체크
		//m_dlgAuthManagement.SetIsRadarTempAuthority(nCh, TRUE);
	}
	break;
	default:
		break;
	}
}


void ProcessCmdGroupPTZCtrl(int nCh, BYTE byCmdType, AUTHORITY_DATA& authorityData)
{
	CMD cmd;
	switch (byCmdType)
	{
	case CMDTYPE_PTZCTRL_PAN_LEFT:
	{
		cmd.iCmd = PANTILT_MOVE_LEFT;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		//pushcommand
	}
	break;
	case CMDTYPE_PTZCTRL_PAN_RIGHT:
	{
		cmd.iCmd = PANTILT_MOVE_RIGHT;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
	}
	break;
	case CMDTYPE_PTZCTRL_TILT_UP:

		cmd.iCmd = PANTILT_MOVE_UP;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;
	case CMDTYPE_PTZCTRL_TILT_DOWN:

		cmd.iCmd = PANTILT_MOVE_DOWN;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);

		break;
	case CMDTYPE_PTZCTRL_PT_LU:

		cmd.iCmd = PANTILT_MOVE_UP;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		cmd.iCmd = PANTILT_MOVE_LEFT;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);

		break;
	case CMDTYPE_PTZCTRL_PT_RU:

		cmd.iCmd = PANTILT_MOVE_RIGHT;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		cmd.iCmd = PANTILT_MOVE_UP;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;
	case CMDTYPE_PTZCTRL_PT_LD:

		cmd.iCmd = PANTILT_MOVE_LEFT;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		cmd.iCmd = PANTILT_MOVE_DOWN;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;
	case CMDTYPE_PTZCTRL_PT_RD:

		cmd.iCmd = PANTILT_MOVE_RIGHT;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		cmd.iCmd = PANTILT_MOVE_DOWN;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
	case CMDTYPE_PTZCTRL_PAN_STOP:
		cmd.iCmd = PANTILT_QUIT_LEFT;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;
	case CMDTYPE_PTZCTRL_TILT_STOP:

		cmd.iCmd = PANTILT_QUIT_RIGHT;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		cmd.iCmd = PANTILT_QUIT_DOWN;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;
	case CMDTYPE_PTZCTRL_PT_STOP:

		cmd.iCmd = PANTILT_QUIT_LEFT;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);

		cmd.iCmd = PANTILT_QUIT_UP;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);

		break;
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
	case CMDTYPE_PTZCTRL_ZOOM_TELE:


		if (ParseAuthorityDataToInt(authorityData) == 1)
			cmd.iCmd = HIGHCAM_ZOOM_TELE;
		else if (ParseAuthorityDataToInt(authorityData) == 2)
			cmd.iCmd = THERMCAM_ZOOM_TELE;
		else
			ASSERT(FALSE);

		g_queueSendToPTZCommand[nCh - 1].push(cmd);

		break;

	case CMDTYPE_PTZCTRL_ZOOM_WIDE:

		if (ParseAuthorityDataToInt(authorityData) == 1)
			cmd.iCmd = HIGHCAM_ZOOM_WIDE;
		else if (ParseAuthorityDataToInt(authorityData) == 2)
			cmd.iCmd = THERMCAM_ZOOM_WIDE;
		else
			ASSERT(FALSE);

		g_queueSendToPTZCommand[nCh - 1].push(cmd);

		break;

	case CMDTYPE_PTZCTRL_ZOOM_STOP:

		if (ParseAuthorityDataToInt(authorityData) == 1)
			cmd.iCmd = HIGHCAM_ZOOM_STOP;
		else if (ParseAuthorityDataToInt(authorityData) == 2)
			cmd.iCmd = THERMCAM_ZOOM_STOP;
		else
			ASSERT(FALSE);

		g_queueSendToPTZCommand[nCh - 1].push(cmd);

		break;

	case CMDTYPE_PTZCTRL_FOCUS_NEAR:

		if (ParseAuthorityDataToInt(authorityData) == 1)
			cmd.iCmd = HIGHCAM_FOCUS_NEAR;
		else if (ParseAuthorityDataToInt(authorityData) == 2)
			cmd.iCmd = THERMCAM_FOCUS_NEAR;
		else
			ASSERT(FALSE);

		g_queueSendToPTZCommand[nCh - 1].push(cmd);

		break;

	case CMDTYPE_PTZCTRL_FOCUS_FAR:

		if (ParseAuthorityDataToInt(authorityData) == 1)
			cmd.iCmd = HIGHCAM_FOCUS_FAR;
		else if (ParseAuthorityDataToInt(authorityData) == 2)
			cmd.iCmd = THERMCAM_FOCUS_FAR;
		else
			ASSERT(FALSE);

		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;

	case CMDTYPE_PTZCTRL_FOCUS_STOP:

		if (ParseAuthorityDataToInt(authorityData) == 1)
			cmd.iCmd = HIGHCAM_FOCUS_STOP;
		else if (ParseAuthorityDataToInt(authorityData) == 2)
			cmd.iCmd = THERMCAM_FOCUS_STOP;
		else
			ASSERT(FALSE);

		g_queueSendToPTZCommand[nCh - 1].push(cmd);

		break;
	case CMDTYPE_PTZCTRL_PT_SPEED:
	{
		int nData = ParseAuthorityDataToInt(authorityData);
		cmd.iCmd = PANTILT_SPD;
		cmd.dArrParam[0] = nData;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
	}
	break;
	case CMDTYPE_PTZCTRL_ZOOM_SPEED:
	{
		int nData = ParseAuthorityDataToInt(authorityData);
		cmd.iCmd = HIGHCAM_ZOOM_SPD;
		cmd.dArrParam[0] = nData;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
	}
	break;
	case CMDTYPE_PTZCTRL_FOCUS_SPEED:
	{
		int nData = ParseAuthorityDataToInt(authorityData);
		cmd.iCmd = HIGHCAM_FOCUS_SPD;
		cmd.dArrParam[0] = nData;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
	}
	break;
	case CMDTYPE_PTZCTRL_PRESET_SPEED:
	{
		int nData = ParseAuthorityDataToInt(authorityData);
		cmd.iCmd = PANTILT_PRESET_SPD;
		cmd.dArrParam[0] = nData;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
	}
		break;
	default:
		ASSERT(FALSE);
		break;
	}
}
void ProcessCmdGroupPTZReq(int nCh, BYTE byCmdType, AUTHORITY_DATA & authorityData)
{
	CMD cmd;
	switch (byCmdType)
	{
	case CMDTYPE_PTZREQ_PANTILT_POS_REQ:

		cmd.iCmd = PANTILT_REQ_CUR_POS2;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;

	case CMDTYPE_PTZREQ_DAYZF_POS_REQ:

		cmd.iCmd = HIGHCAM_REQ_CUR_ZFPOS;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;
	case CMDTYPE_PTZREQ_PAN_MOTORSTATUS_REQ:
		cmd.iCmd = PANTILT_REQ_CUR_PANSTATUS;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;
	case CMDTYPE_PTZREQ_PAN_INITSTATUS_RESP:
		break;
	case CMDTYPE_PTZREQ_TILT_STATUS_REQ:
		break;
	case CMDTYPE_PTZREQ_TILT_STATUS_RESP:
		break;
	case CMDTYPE_PTZREQ_ZF_STATUS_REQ:
		break;
	case CMDTYPE_PTZREQ_ZF_STATUS_RESP:
		break;
	case CMDTYPE_PTZREQ_MAINBOARD_STATUS_RESP:
	default:
		ASSERT(FALSE);
		break;
	}
}

void ProcessCmdGroupPowerMgt(int nCh, BYTE byCmdType, AUTHORITY_DATA & authorityData)
{
	CMD cmd;
	switch (byCmdType)
	{
	case CMDTYPE_POWERMGT_SYS_PWR_CTL:

		if (ParseAuthorityDataToInt(authorityData) == 1)
			cmd.iCmd = PWR_ON;
		else if (ParseAuthorityDataToInt(authorityData) == 2)
			cmd.iCmd = PWR_OFF;

		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;
	case CMDTYPE_POWERMGT_SYS_PWR_STATUS:
		cmd.iCmd = PWR_REQ_STATUS;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;
	case CMDTYPE_POWERMGT_THERMCAM_PWR_CTL:

		cmd.iCmd = THERMCAM_SET_PWR;
		if (ParseAuthorityDataToInt(authorityData) == 1)
			cmd.dArrParam[0] = 1;
		else if (ParseAuthorityDataToInt(authorityData) == 2)
			cmd.dArrParam[0] = 2;

		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;
	case CMDTYPE_POWERMGT_THERMCAM_STATUS:
		cmd.iCmd = THERMCAM_GET_PWR;	

		g_queueSendToPTZCommand[nCh - 1].push(cmd);

		break;
	default:
		ASSERT(FALSE);
		break;
	}	
}
void ProcessCmdGroupPanTiltInit(int nCh, BYTE byCmdType, AUTHORITY_DATA & authorityData)
{
	CMD cmd;
	switch (byCmdType)
	{
	case CMDTYPE_PANTILTINIT_MOVE_HOMEPOS:
		cmd.iCmd = PANTILT_MOVE_HOME;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;
	case CMDTYPE_PANTILTINIT_REQ_HOMEPOS:
		cmd.iCmd = PANTILT_REQ_HOMESTATUS;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;
	case CMDTYPE_PANTILTINIT_SYNC_HOMEPOS:
#if 1//현재위치를 아래 좌표 저장	
		cmd.iCmd = PANTILT_PRESET_SET;
		cmd.dArrParam[0] = 0;
		cmd.dArrParam[1] = 180.00;
		cmd.dArrParam[2] = 0.00;
		cmd.dArrParam[3] = 50000;
		cmd.dArrParam[4] = 50000;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		
		//0번지에 링크
		cmd.iCmd = PANTILT_PRESET_LINK;	cmd.dArrParam[0] = 0;	
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
	
		//0번지의 값으로 팬틸트 값 동기화
		cmd.iCmd = PANTILT_PRESET_SYNC;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
#endif
		break;
	default:
		ASSERT(FALSE);
		break;
	}
}
void ProcessCmdGroupAbsMove(int nCh, BYTE byCmdType, AUTHORITY_DATA & authorityData)
{
	CMD cmd;
	switch (byCmdType)
	{
	case CMDTYPE_PTZFABSMOVE_MOVE:
	{
		CString strPTZF = ParseAuthorityData2(authorityData);

		CString strTok_1, strTok_2, strTok_3, strTok_4, strTok_5;

		AfxExtractSubString(strTok_1, strPTZF, 0, ';');
		AfxExtractSubString(strTok_2, strPTZF, 1, ';');
		AfxExtractSubString(strTok_3, strPTZF, 2, ';');
		AfxExtractSubString(strTok_4, strPTZF, 3, ';');
		AfxExtractSubString(strTok_5, strPTZF, 4, ';');


#if 1//현재위치를 아래 좌표 저장	
		cmd.iCmd = PANTILT_PRESET_SET;
		cmd.dArrParam[0] = _wtof(strTok_1);
		cmd.dArrParam[1] = _wtof(strTok_2);
		cmd.dArrParam[2] = _wtof(strTok_3);
		cmd.dArrParam[3] = _wtoi(strTok_4);//zoom
		cmd.dArrParam[4] = _wtoi(strTok_5);//focus
		g_queueSendToPTZCommand[nCh - 1].push(cmd);

		//1 번지에 링크
		cmd.iCmd = PANTILT_PRESET_LINK;
		cmd.dArrParam[0] = 1;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);

		//1번지의 값으로 팬틸트 이동
		cmd.iCmd = PANTILT_PRESET_MOVE;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
#endif
	}
	break;
	case CMDTYPE_PTZFABSMOVE_SAVE_POS:
	{
		CString strPTZF = ParseAuthorityData2(authorityData);

		CString strTok_1, strTok_2, strTok_3, strTok_4, strTok_5;

		AfxExtractSubString(strTok_1, strPTZF, 0, ';');
		AfxExtractSubString(strTok_2, strPTZF, 1, ';');
		AfxExtractSubString(strTok_3, strPTZF, 2, ';');
		AfxExtractSubString(strTok_4, strPTZF, 3, ';');
		AfxExtractSubString(strTok_5, strPTZF, 4, ';');

		cmd.iCmd = PANTILT_PRESET_SET;
		cmd.dArrParam[0] = _wtof(strTok_1);
		cmd.dArrParam[1] = _wtof(strTok_2);
		cmd.dArrParam[2] = _wtof(strTok_3);
		cmd.dArrParam[3] = _wtoi(strTok_4);//zoom
		cmd.dArrParam[4] = _wtoi(strTok_5);//focus

		g_queueSendToPTZCommand[nCh - 1].push(cmd);
	}
	break;
	case CMDTYPE_PTZFABSMOVE_MOVE_SAVEPOS:
	{
		//1 번지에 링크
		int nPos = ParseAuthorityDataToInt(authorityData);
		cmd.iCmd = PANTILT_PRESET_LINK;
		cmd.dArrParam[0] = nPos;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);

		//1번지의 값으로 팬틸트 이동
		cmd.iCmd = PANTILT_PRESET_MOVE;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
	}
	break;

	case CMDTYPE_PTZFABSMOVE_REQ_SAVEPOS:
	{
		//n번지 요청
		int nPos = ParseAuthorityDataToInt(authorityData);
		cmd.iCmd = PANTILT_PRESET_GET;
		cmd.dArrParam[0] = nPos;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
	}
	break;
	default:
		ASSERT(FALSE);
	}
}


void ProcessCmdGroupDayLensCtrl(int nCh, BYTE byCmdType, AUTHORITY_DATA & authorityData)
{
	CMD cmd;
	switch (byCmdType)
	{
	case CMDTYPE_DAYCAM_IRIS:
	{
		cmd.iCmd = HIGHCAM_IRIS;
		int nData = ParseAuthorityDataToInt(authorityData);
		cmd.dArrParam[0] = nData;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
	}
	break;

	default:
		ASSERT(FALSE);
	}
}
void ProcessCmdGroupThermalCam(int nCh, BYTE byCmdType, AUTHORITY_DATA & authorityData)
{
	CMD cmd;
	switch (byCmdType)
	{
	case CMDTYPE_THERMCAM_WHITE_HOT:
		cmd.iCmd = THERMCAM_SET_WHITEHOT;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;
	case CMDTYPE_THERMCAM_BLACK_HOT:
		cmd.iCmd = THERMCAM_SET_BLACKHOT;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;
	case CMDTYPE_THERMCAM_DZOOM:
	{
		cmd.iCmd = THERMCAM_SET_DZOOM;

		double dData = ParseAuthorityDataToDouble(authorityData);
		cmd.dArrParam[0] = dData;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
	}
	break;
	case CMDTYPE_THERMCAM_DZOOM_REQ:
	{
		cmd.iCmd = THERMCAM_REQ_DZOOM;

		//int nData = ParseAuthorityDataToInt(authorityData);
		//cmd.dArrParam[0] = nData;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);

	}
	break;
	case CMDTYPE_THERMCAM_COLOR:
	{
		cmd.iCmd = THERMCAM_SET_COLOR;
		int nData = ParseAuthorityDataToInt(authorityData);
		cmd.dArrParam[0] = nData;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;
	}


	case CMDTYPE_THERMCAM_NUC:
		break;

	case CMDTYPE_THERMCAM_AGCMODE:
	{
		cmd.iCmd = THERMCAM_SET_AGCMODE;
		int nData = ParseAuthorityDataToInt(authorityData);
		cmd.dArrParam[0] = nData;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
	}
	break;
	case CMDTYPE_THERMCAM_AGCMODE_REQ:
		break;

	case CMDTYPE_THERMCAM_CONTRAST:
	{
		cmd.iCmd = THERMCAM_SET_CON;
		int nData = ParseAuthorityDataToInt(authorityData);
		cmd.dArrParam[0] = nData;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
	}
	break;
	case CMDTYPE_THERMCAM_CONTRAST_REQ:
		cmd.iCmd = THERMCAM_REQ_CON;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;

	case CMDTYPE_THERMCAM_BRIGHTNESS:
	{
		cmd.iCmd = THERMCAM_SET_BRI;
		int nData = ParseAuthorityDataToInt(authorityData);
		cmd.dArrParam[0] = nData;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
	}
	break;
	case CMDTYPE_THERMCAM_BRIGHTNESS_REQ:
		cmd.iCmd = THERMCAM_REQ_BRI;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;

	case CMDTYPE_THERMCAM_DDE:
	{
		cmd.iCmd = THERMCAM_SET_DDEMODE;
		int nData = ParseAuthorityDataToInt(authorityData);
		cmd.dArrParam[0] = nData;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
	}
	break;
	case CMDTYPE_THERMCAM_DDE_REQ:
		break;

	case CMDTYPE_THERMCAM_ACE:
		break;
	case CMDTYPE_THERMCAM_ACE_REQ:
		break;

	case CMDTYPE_THERMCAM_SSO:
		break;
	case CMDTYPE_THERMCAM_SSO_REQ:
		break;
	default:
		break;
	}
}
void ProcessCmdGroupETCFunc(int nCh, BYTE byCmdType, AUTHORITY_DATA & authorityData)
{
	/*
	CMD cmd;
	switch (byCmdType)
	{
	case CMDTYPE_ETCFUNC_PWR_CTL:
		if (ParseAuthorityDataToInt(authorityData) == 1)
			cmd.iCmd = PWR_ON;
		else if (ParseAuthorityDataToInt(authorityData) == 2)
			cmd.iCmd = PWR_OFF;

		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;
	case CMDTYPE_ETCFUNC_THERMCAM_PWR_CTL:
		cmd.iCmd = THERMCAM_SET_PWR;
		if (ParseAuthorityDataToInt(authorityData) == 1)
			cmd.dArrParam[0] = 1;
		else if (ParseAuthorityDataToInt(authorityData) == 2)
			cmd.dArrParam[0] = 2;

		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;
	case CMDTYPE_ETCFUNC_PANTILT_INIT:

		//g_queueSendToPTZCommand[nCh - 1] = AfxBeginThread(PTZInitializeThread, &m_arrPTZThreadInfo[nCh - 1], THREAD_PRIORITY_NORMAL);

		break;
	case CMDTYPE_ETCFUNC_PRESET_CTL:
	{

#if 1
		CString strParsedData = ParseAuthorityData2(authorityData);

		if (strParsedData == _T("1") || strParsedData == _T("2"))//1 : 선택된 한개 프리셋 이동 시작, //2 : 프리셋 순회 이동 시작 확인필요
		{
			//StartPresetMoving(nCh);
		}
		else if (strParsedData == _T("3"))//3 : 이동 중단
		{
			//StopPresetMoving(nCh);

		}
#endif
	}
	break;
	case CMDTYPE_ETCFUNC_SET_PAN_OFFSET:
		break;
	case CMDTYPE_ETCFUNC_SET_TILT_OFFSET:
		break;
	case CMDTYPE_ETCFUNC_REQ_GPS_VAL:
		break;
	case CMDTYPE_ETCFUNC_REQ_GPS_LAT:
		break;
	case CMDTYPE_ETCFUNC_REQ_GPS_LONG:
		break;
	case CMDTYPE_ETCFUNC_SET_LAT_POS:
		break;
	case CMDTYPE_ETCFUNC_SET_LONG_POS:
		break;
	default:
		break;
	}

	*/
}

void ProcessCmdGroupETCDevice(int nCh, BYTE byCmdType, AUTHORITY_DATA & authorityData)
{
	CMD cmd;
	switch (byCmdType)
	{
	case CMDTYPE_ETC_HIGHLENS_FILTER:
		
		int data = ParseAuthorityDataToInt(authorityData);
		cmd.iCmd = HIGHCAM_LENSFILTER;
		cmd.dArrParam[0] = data;
		g_queueSendToPTZCommand[nCh - 1].push(cmd);
		break;
	}
}