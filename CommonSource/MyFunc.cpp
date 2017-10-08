#include "StdAfx.h"
#include "MyFunc.h"

CMyFunc::CMyFunc(void)
{
}

CMyFunc::~CMyFunc(void)
{
}

CString _STR(long n)
{
	CString str;
	str.Format(_T("%d"), n);
	return str;
}
CString GetProgramDir()
{
	//  경로명의 맨 뒤에 '\'가 붙음
	CString str;
	TCHAR szPath[1024];
	GetModuleFileName(NULL, szPath, 1024);
	str.Format(_T("%s"), szPath);
	str = str.Left(str.ReverseFind(_T('\\')) + 1);	
	return str;
}


//UNICODE  by glay
void MTOW(LPCSTR sz, LPTSTR _tsz, int nLen)
{
#ifdef _UNICODE
    MultiByteToWideChar( CP_ACP, 0, sz, -1, _tsz, nLen);
#else
	strncpy(_tsz, sz, nLen);
#endif
}
void WTOM(LPCWSTR wsz, LPTSTR _tsz, int nLen)
{
#ifdef _UNICODE
	//wcsncpy(_tsz, wsz, nLen);//  [12/9/2011 Yeun Edit for Unicode]
	wcsncpy_s(_tsz, MAX_PATH-1, wsz, nLen);
#else
	WideCharToMultiByte( CP_ACP, 0,	wsz, -1, _tsz, nLen, NULL,NULL ); 
#endif
}

//WritePrivateProfileString
BOOL WPPS(CString strSec, CString strKey, CString strValue, CString strFile)
{
	strKey.MakeLower();
	return WritePrivateProfileString(strSec, strKey, strValue, strFile);
}

BOOL WPPS(CString strSec, CString strKey, int nValue, CString strFile)
{
	strKey.MakeLower();
	CString strValue;
	strValue.Format(_T("%d"), nValue);
	return WritePrivateProfileString(strSec, strKey, strValue, strFile);
}
BOOL WPPS(CString strSec, CString strKey, UINT uValue, CString strFile)
{
	strKey.MakeLower();
	CString strValue;
	strValue.Format(_T("%d"), uValue);
	return WritePrivateProfileString(strSec, strKey, strValue, strFile);
}
BOOL WPPS(CString strSec, CString strKey, double dValue, CString strFile)
{
	strKey.MakeLower();
	CString strValue;
	strValue.Format(_T("%lf"), dValue);
	return WritePrivateProfileString(strSec, strKey, strValue, strFile);
}

BOOL WPPS(CString strSec, CString strKey, CRect rect, CString strFile)
{
	strKey.MakeLower();
	CString strValue;
	strValue.Format(_T("%d,%d,%d,%d"), rect.left, rect.top, rect.right, rect.bottom);
	return WritePrivateProfileString(strSec, strKey+_T("(string)"), strValue, strFile);

	//RECT rc;
	//rc.left = rect.left;
	//rc.top = rect.top;
	//rc.right = rect.right;
	//rc.bottom = rect.bottom;
	//return WritePrivateProfileStruct(strSec, strKey, &rc, sizeof(RECT), strFile);
}
BOOL WPPC(CString strSec, CString strKey, COLORREF clr, CString strFile)
{
	strKey.MakeLower();
	CString strValue;
	strValue.Format(_T("%d,%d,%d"), GetRValue(clr), GetGValue(clr), GetBValue(clr));
	return WritePrivateProfileString(strSec, strKey+_T("(string)"), strValue, strFile);

	//strValue.Format(_T("%d"), clr);
	//return WritePrivateProfileString(strSec, strKey, strValue, strFile);
}
//GetPrivateProfileString
DWORD GPPS(CString strSec, CString strKey, LPTSTR lpszValue, int nSize, CString strFile)
{
	strKey.MakeLower();
	DWORD dw = ::GetPrivateProfileString(strSec, strKey, lpszValue, lpszValue, nSize, strFile);
	return dw;
}
DWORD GPPS(CString strSec, CString strKey, CString &strValue, CString strFile)
{
	strKey.MakeLower();
	TCHAR lpszValue[4096];
	DWORD dw = ::GetPrivateProfileString(strSec, strKey, strValue, lpszValue, SIZE(lpszValue), strFile);
	strValue = lpszValue;
	return dw;
}
DWORD GPPS(CString strSec, CString strKey, int &nValue, CString strFile)
{
	strKey.MakeLower();
	TCHAR lpszValue[4096];
	DWORD dw = ::GetPrivateProfileString(strSec, strKey, _STR(nValue), lpszValue, SIZE(lpszValue), strFile);
	nValue = _ttoi(lpszValue);
	return dw;
}
DWORD GPPS(CString strSec, CString strKey, int &iValue, int iDefValue, CString strFile)//  [1/3/2012 Yeun]
{
	strKey.MakeLower();
	TCHAR lpszValue[4096];
	DWORD dw = ::GetPrivateProfileString(strSec, strKey, _STR(iDefValue), lpszValue, SIZE(lpszValue), strFile);
	iValue = _ttoi(lpszValue);
	return dw;
}
DWORD GPPS(CString strSec, CString strKey, UINT &uValue, CString strFile)
{
	strKey.MakeLower();
	TCHAR lpszValue[4096];
	DWORD dw = ::GetPrivateProfileString(strSec, strKey, _STR(uValue), lpszValue, SIZE(lpszValue), strFile);
	uValue = _ttoi(lpszValue);
	return dw;
}
DWORD GPPS(CString strSec, CString strKey, BYTE &byValue, CString strFile)
{
	strKey.MakeLower();
	TCHAR lpszValue[4096];
	DWORD dw = ::GetPrivateProfileString(strSec, strKey, _STR(byValue), lpszValue, SIZE(lpszValue), strFile);
	byValue = _ttoi(lpszValue);
	return dw;
}
DWORD GPPS(CString strSec, CString strKey, double &dValue, CString strFile)
{
	strKey.MakeLower();
	TCHAR lpszValue[4096];
	DWORD dw = ::GetPrivateProfileString(strSec, strKey, _STR((long)dValue), lpszValue, SIZE(lpszValue), strFile);
	dValue = _wtof(lpszValue);
	return dw;
}
DWORD GPPS(CString strSec, CString strKey, long &nValue, CString strFile)
{
	strKey.MakeLower();
	TCHAR lpszValue[4096];
	DWORD dw = ::GetPrivateProfileString(strSec, strKey, _STR(nValue), lpszValue, SIZE(lpszValue), strFile);
	nValue = _ttoi(lpszValue);
	return dw;
}
DWORD GPPS(CString strSec, CString strKey, CRect &rect, CString strFile)
{
	//strKey.MakeLower();
	//RECT rc;
	//DWORD dw = ::GetPrivateProfileStruct(strSec, strKey, &rc, sizeof(RECT), strFile);
	//rect = rc;

	strKey.MakeLower();
	RECT rc; memset(&rc, 0, sizeof(RECT));
	TCHAR lpszValue[4096];
	DWORD dw = ::GetPrivateProfileString(strSec, strKey+_T("(string)"), lpszValue, lpszValue, SIZE(lpszValue), strFile);

	//_stscanf(lpszValue, _T("%d,%d,%d,%d"), &rc.left, &rc.top, &rc.right, &rc.bottom);//  [12/9/2011 Yeun Edit for Unicode]
	swscanf_s(lpszValue, _T("%d,%d,%d,%d"), &rc.left, &rc.top, &rc.right, &rc.bottom);
	rect = rc;

	return dw;
}
DWORD GPPC(CString strSec, CString strKey, COLORREF &clr, CString strFile)
{
	//strKey.MakeLower();
	//TCHAR lpszValue[4096];
	//DWORD dw = ::GetPrivateProfileString(strSec, strKey, _STR(clr), lpszValue, SIZE(lpszValue), strFile);
	//clr = _ttoi(lpszValue);

	strKey.MakeLower();
	int r = 0, g = 0, b = 0; 
	TCHAR lpszValue[4096];
	DWORD dw = ::GetPrivateProfileString(strSec, strKey+_T("(string)"), lpszValue, lpszValue, SIZE(lpszValue), strFile);
	//_stscanf(lpszValue, _T("%d,%d,%d"), &r, &g, &b);//  [12/9/2011 Yeun Edit for Unicode]
	swscanf_s(lpszValue, _T("%d,%d,%d"), &r, &g, &b);
	clr = RGB(r,g,b);

	return dw;
}


void ProperPath(CString &strPath)
{
	if(strPath.Right(1) != _T("\\"))
		strPath += _T("\\");
}
void UnProperPath(CString &strPath)
{
	if(strPath.Right(1)==_T("\\"))
		strPath = strPath.Left(strPath.GetLength()-1);
}
void ProperURL(CString &strPath)
{
	if(strPath.Right(1) != _T("/"))
		strPath += _T("/");
}
void UnProperURL(CString &strPath)
{
	if(strPath.Right(1)==_T("/"))
		strPath = strPath.Left(strPath.GetLength()-1);
}
void ProperURL_F(CString &strPath)
{
	if(strPath.Left(1) != _T("/"))
		strPath.Insert(0, _T("/"));
}
void UnProperURL_F(CString &strPath)
{
	if(strPath.Left(1)==_T("/"))
		strPath = strPath.Mid(1);
}
void ProperPath(LPSTR szPath)
{
	int n = (int) strlen(szPath);
	if(szPath[n-1] != '\\')	{
		//strcat(szPath, "\\");//  [12/9/2011 Yeun Edit for Unicode]
		strcat_s(szPath, n, "\\");
	}
}
void UnProperPath(LPSTR szPath)
{
	int n = (int) strlen(szPath);
	if(szPath[n-1] == '\\')	{
		szPath[n-1]=0;
	}
}
void ProperURL(LPSTR szPath)
{
	int n = (int) strlen(szPath);
	if(szPath[n-1] != '/')	{
		//strcat(szPath, "/");//  [12/9/2011 Yeun Edit for Unicode]
		strcat_s(szPath, n, "/");
	}
}
void UnProperURL(LPSTR szPath)
{
	int n = (int) strlen(szPath);
	if(szPath[n-1] == '/')	{
		szPath[n-1]=0;
	}
}
void ProperURL_F(LPSTR szPath)
{
	char sz[1024];

	if(szPath[0] != '/')	{
		//strcpy(sz, szPath);//  [12/9/2011 Yeun Edit for Unicode]
		strcpy_s(sz, 1024, szPath);

		//strcat(sz, "/");
		strcat_s(sz, 1024, "/");

		//strcpy(szPath, sz);//	[12/9/2011 Yeun Edit for Unicode]
		strcpy_s(szPath, 1024, sz);

	}
}
void UnProperURL_F(LPSTR szPath)
{
	char sz[1024];

	if(szPath[0] == '/')	{
		//strcpy(sz, szPath+1);//  [12/9/2011 Yeun Edit for Unicode]
		strcpy_s(sz, 1024, szPath+1);

		//strcpy(szPath, sz);//	[12/9/2011 Yeun Edit for Unicode]
		strcpy_s(szPath, 1024, sz);
	}
}

BOOL FindFile(CString filename,BOOL bFolder)
{
	WIN32_FIND_DATA fd;
    HANDLE hFind;
	BOOL bResult = FALSE;

	if(bFolder){
#if defined(_WIN32_WCE)
		ProperPath(filename);
#else
		UnProperPath(filename);
#endif
	}else{
		UnProperPath(filename);
	}

    hFind = FindFirstFile (filename, &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
		if(bFolder){
			if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) bResult = TRUE;
		}else{
			if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) bResult = TRUE;
		}
		FindClose (hFind);
    } else {
		bResult = FALSE;
    }
    return bResult;
}
CString STR_NOW()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString str;
	str.Format(_T("%04d-%02d-%02d %s %02d:%02d:%02d")
			, st.wYear
			, st.wMonth
			, st.wDay
			,(st.wHour >= 12) ? _T("오후") : _T("오전")
			,(st.wHour % 12 == 0) ? 12 : (st.wHour % 12)
			, st.wMinute
			, st.wSecond);
	return str;
}
CString STR_NOW2()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString str;
	str.Format(_T("%04d-%02d-%02d %s %02d:%02d:%02d")
			, st.wYear
			, st.wMonth
			, st.wDay
			,(st.wHour >= 12) ? _T("PM") : _T("AM")
			,(st.wHour % 12 == 0) ? 12 : (st.wHour % 12)
			, st.wMinute
			, st.wSecond);
	return str;
}
CString STR_NOW_NOHIPEN()
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	CString str;
	str.Format(_T("%04d%02d%02d%02d%02d%02d")
			, st.wYear
			, st.wMonth
			, st.wDay
			, st.wHour
			, st.wMinute
			, st.wSecond);
	return str;
	
}
//
// Function name : CreateDirectories							
// Description   : Create directory tree.							
//
BOOL CreateDirectories(LPCTSTR lpszDirectory)
{
	CString strResult = lpszDirectory;

	if (strResult.Right(1) != _T('\\'))
		strResult += _T('\\');
	
	CString strDir;
	BOOL bResult;
	// create directory structure one part at a time
	while (strResult != _T(""))
	{
		strDir += strResult.Left(strResult.Find(_T("\\"))+1);
		strResult = strResult.Mid(strResult.Find(_T("\\"))+1);
		bResult = CreateDirectory(strDir, 0);
	}
	return bResult;
}



// pSrc폴더 내부의 모든 폴더와 파일을 pDst폴더로 copy한다. 
//	@param	pSrc 복사할 원본 경로
//	@param  pDst 복사할 목적 경로
//	@return int
int CopyDir( TCHAR *pSrc, TCHAR *pDst )
{
	SHFILEOPSTRUCT fop;

	fop.hwnd	= NULL;
	fop.wFunc	= FO_COPY;
	fop.pFrom	= pSrc;
	fop.pTo		= pDst;
	fop.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI;
	fop.fAnyOperationsAborted	= NULL;
	fop.hNameMappings			= NULL;
	fop.lpszProgressTitle		= NULL;

	return SHFileOperation( &fop );
}
// pDir폴더 내부의 모든 폴더와 파일을 아무런 메세지 없이 강제로 지운다. 
// 
//	@param	pDir 지울 디렉토리	
//	@return int
//
int RemoveDir(CString strDir)
{
	UnProperPath(strDir);

    CFileFind finder;
    BOOL bWorking = TRUE;
    CString strDirFile;
	strDirFile.Format(_T("%s\\*.*"), strDir );

    bWorking = finder.FindFile(strDirFile);
	if(!bWorking) return 1;

    while(bWorking)
    {
        bWorking = finder.FindNextFile();

        if(finder.IsDots()) continue;

        if(finder.IsDirectory())   
		{
			RemoveDir( finder.GetFilePath() );
		}
        else
		{
			::DeleteFile(finder.GetFilePath());
		}
    }

    finder.Close();

    return ::RemoveDirectory(strDir);

}


// 외부 실행파일이 작업을 끝마칠 때까지 기다린다.
//
//	@param lpszFilePath  실행시킬 외부 파일명
//	@param lpszParameter 부가 파라미터
//	@param hWndOwner     윈도우 핸들
//	@return int
//
int ExecWait(LPTSTR lpszFilePath, LPTSTR lpszParameter, HWND hWndOwner)
{
    SHELLEXECUTEINFO sExecInfo;
    BOOL bExecuted = FALSE, bWaitForExit = TRUE;
    DWORD dwExitCode = 0;

    memset(&sExecInfo, 0, sizeof(SHELLEXECUTEINFO));

    // set struct
    sExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    sExecInfo.hwnd = hWndOwner;
    sExecInfo.lpFile = lpszFilePath;
    sExecInfo.lpParameters = lpszParameter;
    sExecInfo.hProcess = NULL;
    sExecInfo.nShow = SW_HIDE; // SW_SHOWNORMAL;
    sExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;

    bExecuted = ShellExecuteEx(&sExecInfo);

    if(bExecuted != TRUE) {
        return -1;
    }

    if(sExecInfo.hProcess == NULL) {
        return -2;
    }

    // Give the process time to execute and finish
    WaitForSingleObject(sExecInfo.hProcess, INFINITE);


    bWaitForExit = TRUE;

    while(bWaitForExit) 
	{
        if (GetExitCodeProcess(sExecInfo.hProcess, &dwExitCode))
        {
            // Process Status...
            switch(dwExitCode)
            {
            case STILL_ACTIVE:
                break;

            default:
                bWaitForExit = FALSE;
                break;
            }
        }

        Sleep(50);
    }

    return 0;

}

BOOL make_process( TCHAR *pszImageName ,TCHAR *pszCmdLine, BOOL bWait)
{
	BOOL b;

#if defined(_WIN32_WCE)//#ifdef UNDER_CE

	PROCESS_INFORMATION pi;
	memset (&pi, 0, sizeof(pi));
	b = CreateProcess(pszImageName, pszCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, NULL, &pi);

#else

	STARTUPINFO si;
	memset (&si, 0, sizeof (STARTUPINFO));
	PROCESS_INFORMATION pi;
//	memset (&pi, 0, sizeof(pi));
	memset (&pi, 0, sizeof (PROCESS_INFORMATION));
	si.cb = sizeof (STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;
	b = CreateProcess(pszImageName, pszCmdLine,
		NULL, NULL, FALSE, (DWORD) NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);

#endif

	if(bWait){
		WaitForSingleObject(pi.hThread, INFINITE);
	}

	CloseHandle(pi.hThread);

	return b;
}
/*

CString GetFileName(LPCTSTR full)
{
	CString str = full;
	str = str.Mid(str.ReverseFind(_T('\\')) + 1);
	return str;
}

CString GetFileNameNoExt(LPCTSTR full)
{
	CString str = full;
	str = str.Mid(str.ReverseFind(_T('\\')) + 1);
	str = str.Left(str.ReverseFind(_T('.')) + 0);
	return str;
}
//전체경로가 아닌Root 경로를 제외한 경로.
CString	GetSubPath(LPCTSTR full)
{
	CString str = full;
	CString root = GetProgramDir();

	if(str.Find(root) != -1){
		str.Replace(root, _T(""));
	}
	return str;
}

void ProperPath(CString &strPath)
{
	if(strPath.Right(1)!="\\")
		strPath+="\\";
}
void UnProperPath(CString &strPath)
{
	if(strPath.Right(1)=="\\")
		strPath = strPath.Left(strPath.GetLength()-1);
}
BOOL FindFile(CString filename,BOOL bFolder)
{
	WIN32_FIND_DATA fd;
    HANDLE hFind;
	BOOL bResult = FALSE;

	if(bFolder){
#if defined(_WIN32_WCE)
		ProperPath(filename);
#else
		UnProperPath(filename);
#endif
	}else{
		UnProperPath(filename);
	}

    hFind = FindFirstFile (filename, &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
		if(bFolder){
			if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) bResult = TRUE;
		}else{
			if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) bResult = TRUE;
		}
		FindClose (hFind);
    } else {
		bResult = FALSE;
    }
    return bResult;
}
void SetFocusSetSel(CWnd *wnd, UINT nID)
{
	CEdit *edit = (CEdit*)wnd->GetDlgItem(nID);
	if(edit){
		edit->SetFocus();
		edit->SetSel(0, -1);
	}
}

CString RectToStr(CRect rect)
{
	CString str;
	str.Format(_T("%d,%d,%d,%d"),rect.left, rect.top, rect.right, rect.bottom);
	return str;
}

CString PointToStr(CPoint point)
{
	CString str;
	str.Format(_T("%d,%d"),point.x, point.y);
	return str;
}
//////////////////////////////////////////////////////////////////////
// 파일열기 대화상자.
//////////////////////////////////////////////////////////////////////
BOOL OnOpenFileDlg(LPTSTR lpszFileName, int nType)
{
	CString  strDefExt = _T("");
	CString  strFileName = _T("");
	CString  strFilter = _T("");
	
	switch(nType)
	{
	case OPEN_ALL:
		strDefExt = _T("All");
		strFileName = _T("*.*");
		strFilter = _T("ALL FILE(*.*)|*.*|");
		break;
	case OPEN_IMAGE:
		strDefExt = _T("JPG");
		strFileName = _T("*.jpg");
		strFilter = _T("JPG FILE(*.jpg)|*.jpg|BMP FILE(*.bmp)|*.bmp|");
		break;
	case OPEN_SOUND:
		strDefExt = _T("MP3");
		strFileName = _T("*.mp3");
		strFilter = _T("MP3 FILE(*.mp3)|*.mp3|WAV FILE(*.wav)|*.wav|");
		break;
	}

	CFileDialog dlg(TRUE,strDefExt,strFileName
		,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT
		,strFilter);

	if(dlg.DoModal()==IDOK){
		_tcscpy(lpszFileName, dlg.GetPathName());
		return TRUE;
	}


	return FALSE;
}
//////////////////////////////////////////////////////////////////////
// 파일저장 대화상자.
//////////////////////////////////////////////////////////////////////
BOOL OnSaveFileDlg(LPTSTR lpszFileName, int nType)
{
	CFileDialog dlg(FALSE,_T("All"),_T("*.*"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
	_T("ALL FILE(*.*)|*.*|"));

	if(dlg.DoModal()==IDOK){
		_tcscpy(lpszFileName, dlg.GetPathName());
		return TRUE;
	}

	return FALSE;
}
//리소스 비트맵 그리기
void DrawBitmap(CDC* pDC, UINT nID, CRect rect, BOOL bStretch)
{
	CBitmap		cb, *oldBitmap;
	CDC			memDC;
	BITMAP		bm;
	int			x,y;

	if(cb.LoadBitmap(nID) == FALSE) return ;
	if(cb.GetBitmap(&bm) == FALSE) return ;

	if(memDC.CreateCompatibleDC(pDC) == FALSE) return ;
	oldBitmap = memDC.SelectObject(&cb);

	x = rect.left;
	y = rect.top;

	if(bStretch){
		pDC->StretchBlt(x, y, rect.Width(), rect.Height(), &memDC, 0, 0, 
							bm.bmWidth, bm.bmHeight, SRCCOPY);
	}else{
		pDC->BitBlt(x,y,bm.bmWidth,bm.bmHeight,&memDC,0,0,SRCCOPY);
	}

	memDC.SelectObject(oldBitmap);
	
	cb.DeleteObject();
}
//리소스 비트맵의 사이즈를 구하기
BOOL GetBitmapSize(UINT nID, CSize &size)
{
	CBitmap		cb;
	BITMAP		bm;

	if(cb.LoadBitmap(nID) == FALSE) return FALSE;
	if(cb.GetBitmap(&bm) == FALSE) return FALSE;

	size.cx = bm.bmWidth;
	size.cy = bm.bmHeight;

	cb.DeleteObject();

	return TRUE;
}
//윈도우즈 시스템 폴더의 경로를 반환
CString GetSystemDir()
{
	TCHAR szPath[MAX_PATH];
	::GetSystemDirectory(szPath,MAX_PATH);

	return szPath;
}
//시간값을 문자열표시 00:00:00
CString TimeToStr(int t)
{
	CString str;
	int h=0,m=0,s=0;
	GetTimeToHMS(t, h, m, s);
	str.Format(_T("%02d:%02d:%02d"), h,m,s);
	return str;
}
// int time 값 => h,m,s
void GetTimeToHMS(int t, int &h, int &m, int &s)
{
	s = t % 60;
	t = t / 60;
	m = t % 60;
	h = t / 60;
}
// h,m,s => int time 값
int GetHMSToTime(int h, int m, int s)
{
	return h*3600 + m*60 + s;
}

*/