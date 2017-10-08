#pragma once

#include "resource.h"




int main();
BOOL InitializeApp();
void InitializePTZClientSockets();
void InitializeAuthorityServerSockets();
void UnInitializePTZClientSockets();
void UnInitializeAuthorityServerSockets();
void SendMsgToLauncher(TCHAR * msg);

//Multicast SenderReciver
void CreateMulticastSenderReceiverSocket(int nCh, char * destAddress, int destPort, int srcPort);
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
//TCP Client
////////////////////////////////////////////////////////////////////////////////////////////

extern CString g_strArrServerIP[MAX_CHANNEL_NUM];
extern int g_nArrServerPort[MAX_CHANNEL_NUM];

bool CreateTCPClientSocket(int nCh, const char * ipAddr, u_short nPort);
bool ReleaseTCPClientSocket(int nCh);

void SendToPTZServerThread(void * pParam);
void ReceiveFromPTZServerThread(void * pParam);

extern CStandardCommandToProtocol g_arrStdCmdToProtocol[MAX_CHANNEL_NUM];
extern queue<CMD> g_queueSendToPTZCommand[MAX_CHANNEL_NUM];
extern HANDLE arrSendToPTZServerThread[MAX_CHANNEL_NUM];
extern HANDLE arrReceiveFromPTZServerThread[MAX_CHANNEL_NUM];
extern SOCKET arrSockTCPClient[MAX_CHANNEL_NUM];
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////////////////////////////////
//TCP Server
////////////////////////////////////////////////////////////////////////////////////////////
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

extern SOCKET_THREAD_INFO g_arrTCPServerInfo[MAX_CHANNEL_NUM];
extern SOCKET_THREAD_INFO g_arrTCPServerClientInfo[MAX_CHANNEL_NUM];
extern HANDLE arrTCPServerThread[MAX_CHANNEL_NUM];
extern HANDLE arrSendToAuthorityClientThread[MAX_CHANNEL_NUM];
extern HANDLE arrReceiveFromAuthorityClientThread[MAX_CHANNEL_NUM];

extern SOCKET arrSockTCPServer[MAX_CHANNEL_NUM];

extern CWinThread * g_pArrProcessReceivedPacketFromAuthorityClientThread[MAX_CHANNEL_NUM];
extern BOOL g_bArrExitrProcessReceivedPacketFromAuthorityClientThread[MAX_CHANNEL_NUM];

extern queue<AUTHORITY_PACKET> g_queuePakcetReceivedPakcetFromAuthorityClient[MAX_CHANNEL_NUM];
extern queue<AUTHORITY_PACKET> g_queuePakcetSendToAuthorityClient[MAX_CHANNEL_NUM];

void CreateTCPServerSocket(int nCh, u_short port);
void ErrorHandling(char *message);
UINT ProcessReceivedPacketThread(void * pParam);
DWORD WINAPI SendToAuthorityClientThread(PVOID lpParam);
DWORD WINAPI ReceiveFromAuthorityClientThread(PVOID lpParam);
DWORD WINAPI TCPServerThread(PVOID lpParam);
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////








void ProcessClientPacket(int nReceivedCh, const PACKET_LENGTH & packetLength);
//제어권클라이언트에서 온 명령어 Parsing
/*
void ProcessCmdGroupAuthority(int nCh, const AUTHORITY_PACKET* pAuthorityPacket, DWORD dwIPAddr, UINT uPort);
void ProcessCmdGroupPTZCtrl(int nCh, BYTE byCmdType, AUTHORITY_DATA& authorityData);
void ProcessCmdGroupPTZReqResp(int nCh, BYTE byCmdType, AUTHORITY_DATA& authorityData);
*/
UINT PTZCommThread(void* pParam);

UINT ProcessReceivedPacketThread(void* pParam);
