#pragma once

#define SIZE(n) sizeof(n)/sizeof(n[0])

CString _STR(long n);
//CString _STR(double d);//  [12/21/2011 Yeun]
CString GetProgramDir();
void MTOW(LPCSTR sz, LPTSTR _tsz, int nLen);
void WTOM(LPCWSTR wsz, LPTSTR _tsz, int nLen);

//WritePrivateProfileString
BOOL WPPS(CString strSec, CString strKey, CString strValue, CString strFile);
BOOL WPPS(CString strSec, CString strKey, int nValue, CString strFile);
BOOL WPPS(CString strSec, CString strKey, UINT uValue, CString strFile);
BOOL WPPS(CString strSec, CString strKey, double dValue, CString strFile);
BOOL WPPS(CString strSec, CString strKey, CRect rect, CString strFile);
BOOL WPPC(CString strSec, CString strKey, COLORREF clr, CString strFile);
//GetPrivateProfileString
DWORD GPPS(CString strSec, CString strKey, LPTSTR lpszValue, int nSize, CString strFile);
DWORD GPPS(CString strSec, CString strKey, CString &strValue, CString strFile);
DWORD GPPS(CString strSec, CString strKey, int &nValue, CString strFile);
DWORD GPPS(CString strSec, CString strKey, int &iValue, int iDefValue, CString strFile);//  [1/3/2012 Yeun]
DWORD GPPS(CString strSec, CString strKey, UINT &uValue, CString strFile);//  [12/20/2011 Yeun]
DWORD GPPS(CString strSec, CString strKey, BYTE &byValue, CString strFile);//  [12/20/2011 Yeun]
DWORD GPPS(CString strSec, CString strKey, double &dValue, CString strFile);//  [12/21/2011 Yeun]
DWORD GPPS(CString strSec, CString strKey, long &nValue, CString strFile);
DWORD GPPS(CString strSec, CString strKey, CRect &rect, CString strFile);
DWORD GPPC(CString strSec, CString strKey, COLORREF &clr, CString strFile);

void ProperPath(CString &strPath);
void UnProperPath(CString &strPath);
void ProperURL(CString &strPath);
void UnProperURL(CString &strPath);
void ProperURL_F(CString &strPath);
void UnProperURL_F(CString &strPath);
void ProperPath(LPSTR szPath);
void UnProperPath(LPSTR szPath);
void ProperURL(LPSTR szPath);
void UnProperURL(LPSTR szPath);
void ProperURL_F(LPSTR szPath);
void UnProperURL_F(LPSTR szPath);
BOOL FindFile(CString filename,BOOL bFolder);



CString STR_NOW();
CString STR_NOW2();
CString STR_NOW_NOHIPEN();

BOOL CreateDirectories(LPCTSTR lpszDirectory);//폴더 생성

int CopyDir( TCHAR *pSrc, TCHAR *pDst );//폴더 copy
int RemoveDir(CString strDir);//폴더 삭제
int ExecWait(LPTSTR lpszFilePath, LPTSTR lpszParameter, HWND hWndOwner);//외부 실행파일이 작업을 끝마칠 때까지 기다린다
BOOL make_process( TCHAR *pszImageName ,TCHAR *pszCmdLine, BOOL bWait);

/*


#define OPEN_ALL	0
#define OPEN_IMAGE	1
#define OPEN_SOUND	2



CString GetFileName(LPCTSTR full); //경로로부터 파일명 잘라내기
CString GetFileNameNoExt(LPCTSTR full); //경로로부터 파일명 잘라내기 확장자 뺌
CString	GetSubPath(LPCTSTR full);//전체경로가 아닌Root 경로를 제외한 경로.
void SetFocusSetSel(CWnd *wnd, UINT nID);

CString RectToStr(CRect rect);
CString PointToStr(CPoint point);
BOOL OnOpenFileDlg(LPTSTR lpszFileName, int nType);
BOOL OnSaveFileDlg(LPTSTR lpszFileName, int nType);
void ProperPath(CString &strPath);
void UnProperPath(CString &strPath);

void DrawBitmap(CDC* pDC, UINT nID, CRect rect, BOOL bStretch);//리소스 비트맵 그리기
BOOL GetBitmapSize(UINT nID, CSize &size);//리소스 비트맵의 사이즈를 구하기

CString		GetSystemDir();//윈도우즈 시스템 폴더의 경로를 반환

CString TimeToStr(int t);//시간값을 문자열표시 00:00:00
void GetTimeToHMS(int t, int &h, int &m, int &s);// int time 값 => h,m,s
int GetHMSToTime(int h, int m, int s);// h,m,s => int time 값

//
*/

class CMyFunc
{
public:
	CMyFunc(void);
	~CMyFunc(void);
};
