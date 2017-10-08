// Hawkeye_PTZClient_AuthorityServer.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Hawkeye_PTZClient_AuthorityServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ������ ���� ���α׷� ��ü�Դϴ�.

CWinApp theApp;



//yeun
//CClientSocketPTZ g_sockArrPTZClient[MAX_CHANNEL_NUM];
//CServerSocketAuthority g_sockArrAuthServer[MAX_CHANNEL_NUM]; 


extern CRITICAL_SECTION g_csArrSendToAuthorityClient[MAX_CHANNEL_NUM];

queue<PACKET_LENGTH> g_queueReceivedPacket[MAX_CHANNEL_NUM];



CWinThread * g_pArrSendToPTZThread[MAX_CHANNEL_NUM];
BOOL g_bArrExitSendToPTZThread[MAX_CHANNEL_NUM] = { FALSE, };



CIniIPSetup g_iniIPSetup;
//���̴� ���� ����
BOOL m_bArrRadarTempAuthorityInuseNotification[MAX_CHANNEL_NUM];//����� �뺸 �����ִ��� Ȯ�� �� �� �ִ� �÷���
BOOL m_bArrRadarTempAuthority[MAX_CHANNEL_NUM];//���̴��� �������α׷��� ����ϴ� �ӽ� ����� ��� ����
int m_nArrRadarTempAuthorityTimeout[MAX_CHANNEL_NUM];//���̴� �������α׷����� ����� �뺸�� �ȿð�� Ÿ�̸ӷ� 1�ʸ��� ī��Ʈ ����
IP_PORT m_arrAuthorizedClientIPPort[MAX_CHANNEL_NUM];//������� �ο����� Ŭ���̾�Ʈ�� IP Port


unsigned int message;//��ε�ĳ��Ʈ�޼���

//��Ƽĳ��Ʈ ����
SOCKET sd;
sockaddr_in send_addr;
//

#include <crtdbg.h>
#include <WinUser.h>






//////////////////////////////////////////////////////////////////////
//SendToPTZServer, ReceiveFromPTZServer

//////////////////////////////////////////////////////////////////////

//AuthorityServer

//////////////////////////////////////////////////////////////////////


int main()
{
	int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // MFC�� �ʱ�ȭ�մϴ�. �ʱ�ȭ���� ���� ��� ������ �μ��մϴ�.
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: ���� �ڵ带 �ʿ信 ���� �����մϴ�.
            wprintf(L"�ɰ��� ����: MFC�� �ʱ�ȭ���� ���߽��ϴ�.\n");
            nRetCode = 1;
        }
        else
        {
			// TODO: ���� ���α׷��� ������ ���⿡�� �ڵ��մϴ�.
			// �޽��� ���
			message = RegisterWindowMessage(_T("Hawkeye_PTZClient_AuthorityServer"));

			ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
#if 0
			if (!AfxSocketInit())
			{
				AfxMessageBox(_T("Windows sockets initialization failed."));
				return FALSE;
			}
#endif

#if 1
			//The WSAStartup function initiates use of the Winsock DLL by a process.
			WSADATA wsaData;
			int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (result != NO_ERROR)
			{
				wprintf(L"WSAStartup function failed with error: %d\n", result);
				return FALSE;
			}
			//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

#if 0
			_CrtSetBreakAlloc(310);
		  _CrtSetBreakAlloc(304);
		  _CrtSetBreakAlloc(298);
		  _CrtSetBreakAlloc(292);
		  _CrtSetBreakAlloc(286);

			_CrtMemDumpAllObjectsSince(0);
#endif

			/////////////////////////////////////////////////////////////////////////////////////////
			
			InitializeApp();
			
			InitializeAuthorityServerSockets();
			InitializePTZClientSockets();

			//��ε�ĳ��Ʈ�� �Ϸ� ��ȣ ������(��ó���� �����Ͽ� ó���ҷ���)
			// �޽��� ������
			//::PostMessage(HWND_BROADCAST, message, 0, 1);//1 is Completed, 2 is not Completed

			SendMsgToLauncher( _T("PTZClient_AuthorityServer Mainfunction is blocked") );

			while (1)
			{
				int ch = getch();
				if (ch == 'q' || ch == 'Q')
					break;
				else if (ch == 'c' || ch == 'C')
				{
					system("cls");				
				}
			}

			UnInitializePTZClientSockets();
			//UnInitializePTZClientSockets();

			WSACleanup();
        }
    }
    else
    {
        // TODO: ���� �ڵ带 �ʿ信 ���� �����մϴ�.
        wprintf(L"�ɰ��� ����: GetModuleHandle ����\n");
        nRetCode = 1;
    }

    return nRetCode;
}





BOOL InitializeApp()
{
	// Default values
	int ttlValue = 1;					// TTL
	int dscpValue = 32;				// DiffServ
	int destPort = 2222;				// UDP Port
	int	waitValue = 500;				// Pause
	int updateTime = 0;				// Update time on receiver on/off
	PCHAR destAddress = "239.0.0.222";	// Multicast Address
	char val;						// Send or Receive
	int onscreen = 1;					// On screen ?
	int counter = 0;					// Packet count

	int err;
	WSADATA WSAData;

	err = WSAStartup(MAKEWORD(2, 2), &WSAData);
	if (err)
	{
		printf("WSAStartup Failed (%d) Exiting\n", err);
		exit(err);
	}

	// Create a normal UDP socket for sending data
	sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sd == INVALID_SOCKET)
	{
		err = GetLastError();
		printf("\"Socket\" failed with error %d\n", err);
		exit(-1);
	}


	memset(&send_addr, 0, sizeof(SOCKADDR_IN));
	send_addr.sin_family = AF_INET;
	send_addr.sin_addr.s_addr = inet_addr(destAddress);					// this is our test destination IP
	send_addr.sin_port = htons(destPort);

	// Set the Time-to-Live of the multicast
	if (setsockopt(sd, IPPROTO_IP, IP_MULTICAST_TTL, (char *)&ttlValue, sizeof(int)) == SOCKET_ERROR)
	{
		printf("Error: Setting TTL value: error - %d\n", WSAGetLastError());
		closesocket(sd);
		exit(-1);
	}
	//printf("\nSuccess: Setting TTL value - %d\n", ttlValue);

	printf("\ndestAddress = %s\n", destAddress);
	printf("destPort    = %d\n", destPort);
	printf("dscpValue   = %d\n", dscpValue);
	printf("ttlValue    = %d\n", ttlValue);
	printf("waitValue   = %d ms\n", waitValue);

	// Get System Local Time and send a Multicast packet
	printf("\nSending...\n");

	return 0;
}

void InitializePTZClientSockets()
{
	for (int i = 0; i < MAX_CHANNEL_NUM; i++)
	{

		g_strArrServerIP[i].Format(
			_T("%s.%s.%s.%s"), g_iniIPSetup.m_s.tstrPTZServerIPAddrFirst[i],
			g_iniIPSetup.m_s.tstrPTZServerIPAddrSecond[i],
			g_iniIPSetup.m_s.tstrPTZServerIPAddrThird[i],
			g_iniIPSetup.m_s.tstrPTZServerIPAddrForth[i]
		);
		
		g_nArrServerPort[i] = (UINT)g_iniIPSetup.m_s.nArrPTZServerPort[i];

	
		bool bRet = CreateTCPClientSocket(i + 1, (CStringA)g_strArrServerIP[i], (u_short)g_nArrServerPort[i]);
		if (bRet == true)
		{
			printf("ä��=%d TCPŬ���̾�Ʈ PTZ����(%s, %d)�� ���� ���� \n", i + 1, (CStringA)g_strArrServerIP[i], (u_short)g_nArrServerPort[i]);
			CString str; str.Format(_T("ä��=%d TCPŬ���̾�Ʈ PTZ����(%s, %d)�� ���� ����"), i + 1, g_strArrServerIP[i], (u_short)g_nArrServerPort[i]);
			SendMsgToLauncher((TCHAR*)(LPCTSTR)str);
		}
		else
		{
			printf("ä��=%d TCPŬ���̾�Ʈ PTZ����(%s, %d)�� ���� ����!! \n", i + 1, (CStringA)g_strArrServerIP[i], (u_short)g_nArrServerPort[i]);
			CString str; str.Format(_T("ä��=%d TCPŬ���̾�Ʈ PTZ����(%s, %d)�� ���� ����!!"), i + 1, g_strArrServerIP[i], (u_short)g_nArrServerPort[i]);
			SendMsgToLauncher((TCHAR*)(LPCTSTR)str);
		}
		//::PostMessage(HWND_BROADCAST, message, 0, 2);//1 is Completed, 2 is not Completed
	}
}
void InitializeAuthorityServerSockets()
{
	for (int i = 0; i < MAX_CHANNEL_NUM; i++)
	{
		InitializeCriticalSection(&g_csArrSendToAuthorityClient[i]);
		UINT uPort = (UINT)g_iniIPSetup.m_s.nArrAuthorityServerPort[i];
		int nCh = i + 1;
		CreateTCPServerSocket(nCh, (u_short)uPort);
		//printf("CreateTCPServerSocket(%d %d) \n", i + 1, (u_short)uPort);
		
		g_pArrProcessReceivedPacketFromAuthorityClientThread[i] = AfxBeginThread(ProcessReceivedPacketThread, &nCh, THREAD_PRIORITY_NORMAL);
	
		Sleep(1000);
		CString str; str.Format(_T("ä��=%d �������ϻ���!!"), i + 1);
		SendMsgToLauncher((TCHAR*)(LPCTSTR)str);
		//::PostMessage(HWND_BROADCAST, message, 0, 2);//1 is Completed, 2 is not Completed
		

		CreateMulticastSenderReceiverSocket(i+1, "239.1.1.1", 40001+i, 50001 + i);
	}

}

void UnInitializePTZClientSockets()
{
	for (int i = 0; i < MAX_CHANNEL_NUM; i++)
	{
		ReleaseTCPClientSocket(i + 1);

		/*
		if (g_pArrSendToPTZThread[i] != NULL)
		{
		g_bArrExitSendToPTZThread[i] = TRUE;
		DWORD dw = WaitForSingleObject(g_pArrSendToPTZThread[i]->m_hThread, 50000);
		if (dw == WAIT_OBJECT_0)
		{
		//The state of the specified object is signaled.
		printf("Ch = %d PTZClientSocket Thread Safe Exit \n", i+1);
		///AfxMessageBox(_T("WAIT_OBJECT_0"));
		}
		else if (dw == WAIT_TIMEOUT)//�־��� �ð� ���� ��ٸ�
		{
		//AfxMessageBox(_T("WAIT_TIMEOUT"));
		printf("Ch = %d PTZClientSocket Thread Timeout Exit \n", i + 1);
		}
		g_pArrSendToPTZThread[i] = NULL;

		}
		*/
	}
}

void UnInitializeAuthorityServerSockets()
{
#if 0
	for (int i = 0; i < MAX_CHANNEL_NUM; i++)
	{

		if (g_pArrProcessReceivedPacketThread[i] != NULL)
		{
			g_bArrExitrProcessReceivedPacketThread[i] = TRUE;
			DWORD dw = WaitForSingleObject(g_pArrProcessReceivedPacketThread[i]->m_hThread, 50000);
			if (dw == WAIT_OBJECT_0)
			{
				///AfxMessageBox(_T("WAIT_OBJECT_0"));
				printf("Ch = %d ProcessReceivedPacket Thread Safe Exit \n", i + 1);
			}
			else if (dw == WAIT_TIMEOUT)//�־��� �ð� ���� ��ٸ�
			{
				//AfxMessageBox(_T("WAIT_TIMEOUT"));
				printf("Ch = %d ProcessReceivedPacket Thread Timeout Exit \n", i + 1);
			}
			g_pArrProcessReceivedPacketThread[i] = NULL;
		}
	}
#endif
}

void SendMsgToLauncher(TCHAR * msg)
{
#if 1
	wchar_t buffer[512] = { 0, };
	wcscpy(buffer, msg);
	int len = sizeof(buffer);
	if (sendto(sd, (char *)&buffer, len, MSG_DONTROUTE, (sockaddr*)&send_addr, sizeof(send_addr)) == INVALID_SOCKET)
	{
		printf("\nError in Sending data on the socket - %d", WSAGetLastError());
		WSACleanup();
		exit(-1);
	}
#endif
}


#if 0
	int nCh = (int)pParam;
	int nChIndex = nCh - 1;
	while (1)
	{
		SOCKET client;
		sockaddr_in from;
		int fromlen = sizeof(from);

		while (true)
		{
			client = accept(arrSockTCPServer[nChIndex],
				(struct sockaddr*)&from, &fromlen);

			arrSendToAuthorityClientThread[nChIndex] = new thread(ClientThread, (LPVOID)client);
		}
	}

	return 0;

}
#endif




#if 0
UINT PTZCommThread(void* pParam)
{
	while (1)
	{
		CClientSocketPTZ * clientsock = (CClientSocketPTZ*)pParam;
		int nCh = clientsock->GetCh();
		int nChIndex = nCh - 1;

#if 1
		if (g_bArrExitSendToPTZThread[nChIndex] == TRUE)
			break;

		if (m_queuePTZCommand[nChIndex].size() > 0)
		{
			CMD gotCMD = m_queuePTZCommand[nChIndex].front();
			m_queuePTZCommand[nChIndex].pop();

			BYTE byBuf[PROTO_BUFFER_SIZE];
			int nProtocolSize = m_arrStdCmdToProtocol[nChIndex].StdCmdToProtocolPacket(gotCMD, byBuf);
			if (nProtocolSize > 0)
			{
				//pDlg->SendToPTZServer(pInfo->nCh, byBuf, nProtocolSize);

				if (clientsock->Send(byBuf, nProtocolSize) < nProtocolSize)
				{
					int iErr = GetLastError();
					//m_dlgPTZCliAuthSvrConf.SetTextSendToPTZ(nCh, GetSocketSendError(iErr) + _T("\r\n"));
					//ASSERT(FALSE);
					TRACE(_T("send error\r\n"));
				}
				else
				{
					CString strPacket;
					strPacket = (char*)byBuf;
					//m_dlgPTZCliAuthSvrConf.SetTextSendToPTZ(nCh, strPacket + _T("\r\n"));
				}
			}
			//gotCMD.iChIndex

			//AfxMessageBox(_T(""));
			//TRACE("aaa\r\n");
		}
#endif
		Sleep(100);
	}

	return 0;
}
#endif




#if 0
CAsyncSocket * socket = g_sockArrPTZClient[i].FromHandle(g_sockArrPTZClient[i].m_hSocket);
BOOL bSocketAlloc = FALSE;
if (socket == NULL)//������ �̹� ���� �Ǿ����� Ȯ��
{
	g_sockArrPTZClient[i].SetCh(i + 1);
	BOOL bCreation = g_sockArrPTZClient[i].Create();
	if (bCreation)
	{
		printf("CH = %d PTZClientSocket Create() Success! \n", i + 1);
	}
	else
	{
		//AfxMessageBox(GetSocketCreationError(GetLastError()));
		CString temp = GetSocketCreationError(GetLastError());
		printf("CH = %d Create() failure! \n", i + 1);
		//printf("%s", temp);
	}

	//������ ���� �Ѵ�.

	BOOL bResult = g_sockArrPTZClient[i].Connect(strIPAddr, uPort);
	if (bResult)
	{
		_tprintf(_T("Ch = %d PTZClientSocket Connect Success! IP = %s, Port = %d \n"), i + 1, strIPAddr, uPort);
	}
	else
	{
		_tprintf(_T("Ch = %d PTZClientSocket Connect Failure! IP = %s, Port = %d \n"), i + 1, strIPAddr, uPort);
	}
	//OnConnect() �̺�Ʈ �Լ����� ���� �Ǿ����� Ȯ��
	//m_ClientSocket_Login.m_bLoginSocketCreation = TRUE;

	///////////////////////////////////////////////////////////////////////////////////////////

	//PTZ���� ����� ���� ������ ����
#if 1//temp
	//m_arrPTZThreadInfo[i].nCh = i + 1;
	//m_arrPTZThreadInfo[i].pWnd = this;
	g_pArrSendToPTZThread[i] = AfxBeginThread(PTZCommThread, &g_sockArrPTZClient[i], THREAD_PRIORITY_NORMAL);
#endif		
}
else
{
	printf("CH = %d Create() Aleready Creation! \n", i + 1);
}

CString temp = GetSocketCreationError(GetLastError());
printf("CH = %d PTZClientSocket Creation Success!(%s) %d \n", i + 1, temp, uPort);


#endif

#if 0
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

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(1001);

	// ���Ͽ� �ּ� �Ҵ�
	if (::bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		ErrorHandling("bind() error");
	}

	// ���� ��û ��� ����
	if (::listen(hServSock, 5) == SOCKET_ERROR)
	{
		ErrorHandling("listen() error");
	}

	// ���� ��û ����
	szClntAddr = sizeof(clntAddr);
	hClntSock = ::accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);
	if (hClntSock == INVALID_SOCKET)
	{
		ErrorHandling("accept() error");
	}
#endif
#if 0
	// ���� ���� ����
	arrSockTCPServer[nChIndex] = socket(PF_INET, SOCK_STREAM, 0);
	if (arrSockTCPServer[nChIndex] == INVALID_SOCKET)
	{
		//ErrorHandling("socket() error");
	}

	sockaddr_in host;
	host.sin_family = AF_INET;
	host.sin_port = htons(port);
	host.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(arrSockTCPServer[nChIndex], (LPSOCKADDR)&host, sizeof(host));

	SOCKET client;
	sockaddr_in from;
	int fromlen = sizeof(from);

	client = accept(arrSockTCPServer[nChIndex],
		(struct sockaddr*)&from, &fromlen);

	arrTCPServerThread[nChIndex] = new thread(TCPServerThread, (void*)nCh);

	/*
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(argv[1]));
	*/
	//////////////////////////////////////////////////////////////////////
}
#endif


