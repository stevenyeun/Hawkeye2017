// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.
#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS         // ��ȭ ���ڿ��� MFC ��Ʈ�ѿ� ���� ������ �����մϴ�.

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include <afx.h>
#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <iostream>



// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
//#include <afxsock.h>            // MFC socket extensions


#include "CommonDefine.h"
#include "ErrorDefine.h"

#include "StandardCommandToProtocol.h"
#include "AuthorityPacket.h"
#include "MultiSensorCommdef.h"
#include "IniIPSetup.h"
#include <vector>
#include <queue>
#include <Windows.h>
#include <WinSock2.h>

#pragma comment(lib, "Ws2_32.lib")
#include <afxwin.h>
#include <string>
//#include <thread>
#include <ppl.h>
#include <WS2tcpip.h>
#include <conio.h>
using namespace std;

//SOCKET arrSockTCPClient[MAX_CHANNEL_NUM]{ INVALID_SOCKET, };