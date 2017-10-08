#include "stdafx.h"
#include "ErrorDefine.h"

CString GetSocketCreationError(int iErr)
{
	CString returnMsg;
	switch (iErr)
	{
	case WSANOTINITIALISED:
		TRACE("A successful AfxSocketInit must occur before using this API.\r\n");
		returnMsg = (_T("A successful AfxSocketInit must occur before using this API."));
		break;
	case WSAENETDOWN:
		TRACE("The Windows Sockets implementation detected that the network subsystem failed.\r\n");
		returnMsg = _T("The Windows Sockets implementation detected that the network subsystem failed.");
		break;
	case WSAEAFNOSUPPORT:
		TRACE("The specified address family is not supported.\r\n");
		returnMsg = _T("The specified address family is not supported.");
		break;
	case WSAEINPROGRESS:
		TRACE("A blocking Windows Sockets operation is in progress.\r\n");
		returnMsg = _T("A blocking Windows Sockets operation is in progress.");
		break;
	case WSAEMFILE:
		TRACE("No more file descriptors are available.\r\n");
		returnMsg = _T("No more file descriptors are available.");
		break;
	case WSAENOBUFS:			
		TRACE("No buffer space is available. The socket cannot be created.\r\n");
		returnMsg = _T("No buffer space is available. The socket cannot be created.");
		break;
	case WSAEPROTONOSUPPORT:
		TRACE("The specified port is not supported.\r\n");
		returnMsg = _T("The specified port is not supported.");
		break;
	case WSAEPROTOTYPE:
		TRACE("The specified port is the wrong type for this socket.\r\n");
		returnMsg = _T("The specified port is the wrong type for this socket.");
		break;
	case WSAESOCKTNOSUPPORT:
		TRACE("The specified socket type is not supported in this address family.\r\n");
		returnMsg = _T("The specified socket type is not supported in this address family.");
		break;
	default:
		returnMsg = _T("정의되어 있지 않은 에러메시지.");
		break;
	}
	return _T("SOCKET CREATION ERROR-") + returnMsg;
}

CString GetSocketConnectError(int iErr)
{
	CString returnMsg;
	switch (iErr)
	{			
	case WSANOTINITIALISED:
		TRACE("A successful AfxSocketInit must occur before using this API.\r\n");
		returnMsg = (_T("A successful AfxSocketInit must occur before using this API."));
		break;
	case WSAENETDOWN:
		TRACE("The Windows Sockets implementation detected that the network subsystem failed.\r\n");
		returnMsg = _T("The Windows Sockets implementation detected that the network subsystem failed.");
		break;
	case WSAEADDRINUSE:
		TRACE("The specified address is already in use.\r\n");
		returnMsg = _T("The specified address is already in use.");
		break;
	case WSAEINPROGRESS:
		TRACE("A blocking Windows Sockets call is in progress.\r\n");
		returnMsg = _T("A blocking Windows Sockets call is in progress.");
		break;
	case WSAEADDRNOTAVAIL:
		TRACE("The specified address is not available from the local machine.\r\n");
		returnMsg = _T("The specified address is not available from the local machine.");
		break;
	case WSAEAFNOSUPPORT:
		TRACE("Addresses in the specified family cannot be used with this socket.\r\n");
		returnMsg = _T("Addresses in the specified family cannot be used with this socket.");
		break;
	case WSAECONNREFUSED:
		TRACE("The attempt to connect was rejected.\r\n");
		returnMsg = _T("The attempt to connect was rejected.");
		break;
	case WSAEDESTADDRREQ:
		TRACE("A destination address is required.\r\n");
		returnMsg = _T("A destination address is required.");
		break;
	case WSAEFAULT:
		TRACE(_T("The nSockAddrLen argument is incorrect.\r\n"));
		returnMsg = _T("The nSockAddrLen argument is incorrect.");
		break;
	case WSAEINVAL:
		TRACE("Invalid host address.\r\n");
		returnMsg = _T("Invalid host address.");
		break;
	case WSAEISCONN:
		TRACE("The socket is already connected.\r\n");
		returnMsg = _T("The socket is already connected.");
		break;
	case WSAEMFILE:
		TRACE("No more file descriptors are available.\r\n");
		returnMsg = _T("No more file descriptors are available.");
		break;
	case WSAENETUNREACH:
		TRACE("The network cannot be reached from this host at this time.\r\n");
		returnMsg = _T("The network cannot be reached from this host at this time.");
		break;
	case WSAENOBUFS:
		TRACE("No buffer space is available. The socket cannot be connected. \r\n");
		returnMsg = _T("No buffer space is available. The socket cannot be connected.");
		break;
	case WSAENOTSOCK:
		TRACE("The descriptor is not a socket.\r\n");
		returnMsg = _T("The descriptor is not a socket.");
		break;
	case WSAETIMEDOUT:
		TRACE("Attempt to connect timed out without establishing a connection.\r\n");
		returnMsg = _T("Attempt to connect timed out without establishing a connection.");
		break;
	case WSAEWOULDBLOCK:
		TRACE("The socket is marked as nonblocking and the connection cannot be completed immediately.\r\n");
		returnMsg =("The socket is marked as nonblocking and the connection cannot be completed immediately.");					
		break;
	default:
		returnMsg = _T("정의되어 있지 않은 에러메시지.");
		break;
	}
	return _T("SOCKET CONNECTION ERROR-") + returnMsg;
}

CString GetSocketListenError(int iErr)
{
	CString returnMsg;

	switch (iErr)
	{			
	case WSANOTINITIALISED:
		TRACE("A successful AfxSocketInit must occur before using this API.\r\n");
		returnMsg = (_T("A successful AfxSocketInit must occur before using this API."));
		break;
	case WSAENETDOWN:
		TRACE("The Windows Sockets implementation detected that the network subsystem failed.\r\n");
		returnMsg = _T("The Windows Sockets implementation detected that the network subsystem failed.");
		break;
	case WSAEADDRINUSE:
		TRACE("An attempt has been made to listen on an address in use.\r\n");
		returnMsg = _T("An attempt has been made to listen on an address in use.");
		break;
	case WSAEINPROGRESS:
		TRACE("A blocking Windows Sockets operation is in progress. \r\n");
		returnMsg = _T("A blocking Windows Sockets operation is in progress. ");
		break;
	case WSAEINVAL:
		TRACE("The socket has not been bound with Bind or is already connected.");
		returnMsg = _T("The socket has not been bound with Bind or is already connected.");
		break;
	case WSAEISCONN:
		TRACE("The socket is already connected.");
		returnMsg = _T("The socket is already connected.");
		break;
	case WSAEMFILE:
		TRACE("No more file descriptors are available.");
		returnMsg = _T("No more file descriptors are available.");
		break;
	case WSAENOBUFS:
		TRACE("No buffer space is available.");
		returnMsg = _T("No buffer space is available.");
		break;
	case WSAENOTSOCK:
		TRACE("The descriptor is not a socket.");
		returnMsg = _T("The descriptor is not a socket.");
		break;
	case WSAEOPNOTSUPP:
		TRACE("The referenced socket is not of a type that supports the Listen operation.");
		returnMsg = _T("The referenced socket is not of a type that supports the Listen operation.");
		break;
	default:
		returnMsg = _T("정의되어 있지 않은 에러메시지.");
		break;
	}
	return _T("SOCKET LISTEN ERROR-") + returnMsg;
}

CString GetSocketSendError(int iErr)
{
	CString returnMsg;

	switch (iErr)
	{
	case WSANOTINITIALISED:
		TRACE("A successful AfxSocketInit must occur before using this API.\r\n");
		returnMsg = (_T("A successful AfxSocketInit must occur before using this API."));
		break;
	case WSAENETDOWN:
		TRACE("The Windows Sockets implementation detected that the network subsystem failed.\r\n");
		returnMsg = _T("The Windows Sockets implementation detected that the network subsystem failed.");
		break;
	case WSAEACCES:
		TRACE("The requested address is a broadcast address, but the appropriate flag was not set.\r\n");
		returnMsg = _T("The requested address is a broadcast address, but the appropriate flag was not set.");
		break;
	case WSAEINPROGRESS:
		TRACE("A blocking Windows Sockets operation is in progress. \r\n");
		returnMsg = _T("A blocking Windows Sockets operation is in progress. ");
		break;
	case WSAEFAULT:
		TRACE("The lpBuf argument is not in a valid part of the user address space.");
		returnMsg = _T("The lpBuf argument is not in a valid part of the user address space.");
		break;
	case WSAENETRESET:
		TRACE("The connection must be reset because the Windows Sockets implementation dropped it.");
		returnMsg = _T("The connection must be reset because the Windows Sockets implementation dropped it.");
		break;
	case WSAENOBUFS:
		TRACE("The Windows Sockets implementation reports a buffer deadlock.");
		returnMsg = _T("The Windows Sockets implementation reports a buffer deadlock.");
		break;
	case WSAENOTCONN:
		TRACE("The socket is not connected.");
		returnMsg = _T("The socket is not connected.");
		break;
	case WSAENOTSOCK:
		TRACE("The descriptor is not a socket.");
		returnMsg = _T("The descriptor is not a socket.");
		break;
	case WSAEOPNOTSUPP:
		TRACE("MSG_OOB was specified, but the socket is not of type SOCK_STREAM.");
		returnMsg = _T("MSG_OOB was specified, but the socket is not of type SOCK_STREAM.");
		break;
	case WSAESHUTDOWN:
		TRACE("The socket has been shut down; it is not possible to call Send on a socket after ShutDown has been invoked with nHow set to 1 or 2.");
		returnMsg = _T("The socket has been shut down; it is not possible to call Send on a socket after ShutDown has been invoked with nHow set to 1 or 2.");
		break;
	case WSAEWOULDBLOCK:
		TRACE("The socket is marked as nonblocking and the requested operation would block.");
		returnMsg = _T("The socket is marked as nonblocking and the requested operation would block.");
		break;
	case WSAEMSGSIZE:
		TRACE("The socket is of type SOCK_DGRAM, and the datagram is larger than the maximum supported by the Windows Sockets implementation.");
		returnMsg = _T("The socket is of type SOCK_DGRAM, and the datagram is larger than the maximum supported by the Windows Sockets implementation.");
		break;
	case WSAEINVAL:
		TRACE("The socket has not been bound with Bind.");
		returnMsg = _T("The socket has not been bound with Bind.");
		break;
	case WSAECONNABORTED:
		TRACE("The virtual circuit was aborted due to timeout or other failure.");
		returnMsg = _T("The virtual circuit was aborted due to timeout or other failure.");
		break;
	case WSAECONNRESET:
		TRACE("The virtual circuit was reset by the remote side.");
		returnMsg = _T("The virtual circuit was reset by the remote side.");
		break;
	default:
		returnMsg = _T("정의되어 있지 않은 에러메시지.");
		break;
	}
	return _T("SOCKET LISTEN ERROR-") + returnMsg;
}

CString GetSocketCloseError(int nErr)
{
	CString returnMsg;

	/*
	0 성공적으로 실행 하는 함수입니다.
WSAENETDOWN The Windows 소켓 구현이 네트워크 하위 시스템의 실패 했음을 감지 합니다.
WSAECONNRESET 연결이 원격측에서 재설정 되었습니다.
WSAECONNABORTED 연결이 시간 초과 또는 기타 오류로 인해 중단 되었습니다.
	*/
	switch (nErr)
	{
	case 0:
		returnMsg = _T("원격 서버가 종료되어 클라이언트 소켓을 정상 종료하였습니다.");
		break;
	case WSAENETDOWN:
		TRACE("The Windows Sockets implementation detected that the network subsystem failed.\r\n");
		returnMsg = _T("The Windows Sockets implementation detected that the network subsystem failed.");
		break;
	case WSAECONNRESET:
		TRACE("The virtual circuit was reset by the remote side.");
		returnMsg = _T("The virtual circuit was reset by the remote side.");
		break;
	case WSAECONNABORTED:
		TRACE("The virtual circuit was aborted due to timeout or other failure.");
		returnMsg = _T("The virtual circuit was aborted due to timeout or other failure.");
		break;
	default:
		break;
	}

	return _T("SOCKET CLOSE ERROR-") + returnMsg;
}
