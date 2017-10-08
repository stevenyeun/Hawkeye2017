#ifndef ERRORDEFINE_H
#define ERRORDEFINE_H

CString GetSocketCreationError(int iErr);
CString GetSocketConnectError(int iErr);
CString GetSocketListenError(int iErr);

CString GetSocketSendError(int iErr);

CString GetSocketCloseError(int nErr);
#endif