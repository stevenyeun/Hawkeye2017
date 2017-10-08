#pragma once

#include <vector>

#define MAX_REG_KEY_NAME		512
#define MAX_REG_KEY_VALUE		32767

struct RegData
{
    char	*pData;
	DWORD	dwData;
	CString	strData;
};

class RegKeyDetail
{
public:
	CString	strRegKeyName;
	DWORD	dwRegType;
    RegData	m_RegData;
};

class CQTRegistry
{
public:
	CQTRegistry();
	~CQTRegistry();

int m_nLastError;

// CQTRegistry properties	
protected:
	HKEY m_hRootKey;
	BOOL m_bLazyWrite;
	CString m_strCurrentPath;
	char	m_szValueTemp[255];

public:
	inline BOOL PathIsValid() {
		return (m_strCurrentPath.GetLength() > 0); }
	inline CString GetCurrentPath() {
		return m_strCurrentPath; }
	inline HKEY GetRootKey() {
		return m_hRootKey; }


//CQTRegistry	methods
public:
	BOOL ClearKey();
	BOOL SetRootKey(HKEY hRootKey);
	BOOL CreateKey(LPCTSTR strKey);
	BOOL DeleteKey(LPCTSTR strKey,BOOL bDescendent = FALSE);
	BOOL DeleteKeyDescendent(LPCTSTR strKey);

	BOOL DeleteValue(LPCTSTR strName);
	int GetDataSize(LPCTSTR strValueName);
	DWORD GetDataType(LPCTSTR strValueName);
	int GetSubKeyCount();
	int GetValueCount();
	BOOL KeyExists(LPCTSTR strKey, HKEY hRootKey = NULL);
	BOOL SetKey(LPCTSTR strKey, BOOL bCanCreate);
	BOOL ValueExists(LPCTSTR strName);
	void RenameValue(LPCTSTR strOldName, LPCTSTR strNewName);

	// data reading functions
	COleDateTime ReadDateTime(LPCTSTR strName, COleDateTime dtDefault);
	double ReadFloat(LPCTSTR strName, double fDefault);
	char * ReadString(LPCTSTR strName, LPCTSTR strDefault);
	int ReadInt(LPCTSTR strName, int nDefault);
	BOOL ReadBool(LPCTSTR strName, BOOL bDefault);
	COLORREF ReadColor(LPCTSTR strName, COLORREF rgbDefault);
	BOOL ReadFont(LPCTSTR strName, CFont* pFont);
	BOOL ReadPoint(LPCTSTR strName, CPoint* pPoint);
	BOOL ReadSize(LPCTSTR strName, CSize* pSize);
	BOOL ReadRect(LPCTSTR strName, CRect* pRect);
	DWORD ReadDword(LPCTSTR strName, DWORD dwDefault);

	// data writing functions
	BOOL WriteBool(LPCTSTR strName, BOOL bValue);
	BOOL WriteDateTime(LPCTSTR strName, COleDateTime dtValue);
	BOOL WriteString(LPCTSTR strName, LPCTSTR strValue);
	BOOL WriteFloat(LPCTSTR strName, double fValue);
	BOOL WriteInt(LPCTSTR strName, int nValue);
	BOOL WriteColor(LPCTSTR strName, COLORREF rgbValue);
	BOOL WriteFont(LPCTSTR strName, CFont* pFont);
	BOOL WritePoint(LPCTSTR strName, CPoint* pPoint);
	BOOL WriteSize(LPCTSTR strName, CSize* pSize);
	BOOL WriteRect(LPCTSTR strName, CRect* pRect);
	BOOL WriteDword(LPCTSTR strName, DWORD dwValue);

	void EnumRegistryKey(HKEY hKey, LPCTSTR strKeyName, std::vector< CString >& ListEnumKey);
	void EnumRegistryKeyValue(HKEY hKey, LPCTSTR strKeyName, std::vector< RegKeyDetail >& ListEnumKey);


};// end of CQTRegistry class definition


