#include "stdafx.h"
#include "QTRegistry.h"
#include <shlwapi.h>


#define CLASS_NAME_LENGTH 255

/* IMPORTANT NOTES ABOUT CQTRegistry:
	
	CQTRegistry never keeps a key open past the end of a function call.
	This is incase the application crashes before the next call to close
	the registry 
	
	INCLUDE FILES
	"winreg.h" and "afxdisp.h" must be included in "stdafx.h"

	KEY NAMES:
	Key names must not begin with a \ and only absolute strings are accepted
	
*/



CQTRegistry::CQTRegistry()
{
	m_hRootKey = HKEY_CURRENT_USER;
	m_bLazyWrite = TRUE;
	m_nLastError = ERROR_SUCCESS;
}

CQTRegistry::~CQTRegistry()
{
	ClearKey();
}


BOOL CQTRegistry::ClearKey()
{
	/* Call CloseKey to write the current key to the registry and close the 
	key. An application should not keep keys open any longer than necessary. 
	Calling CloseKey when there is no current key has no effect.*/

	m_strCurrentPath.Empty();
	m_hRootKey = HKEY_CURRENT_USER;
	m_bLazyWrite = TRUE;
	return TRUE;
}



BOOL CQTRegistry::SetRootKey(HKEY hRootKey)
{
	// sets the root key
	// make sure to set it to a valid key
	if (hRootKey != HKEY_CLASSES_ROOT &&
			hRootKey != HKEY_CURRENT_USER &&
			hRootKey != HKEY_LOCAL_MACHINE &&
			hRootKey != HKEY_USERS) return FALSE;

	m_hRootKey = hRootKey;
	return TRUE;
}


BOOL CQTRegistry::CreateKey(LPCTSTR strKey)
{
	/* Use CreateKey to add a new key to the registry. 
		Key is the name of the key to create. Key must be 
		an absolute name. An absolute key 
		begins with a backslash (\) and is a subkey of 
		the root key. */

	ASSERT(strKey[0] != '\\');
	HKEY hKey;

	DWORD dwDisposition = 0;

	if (::RegCreateKeyEx(m_hRootKey, LPCTSTR(strKey), 0, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey,
			&dwDisposition)	!= ERROR_SUCCESS) return FALSE;
	
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	m_strCurrentPath = strKey;
	return TRUE;
}


BOOL CQTRegistry::DeleteKey(LPCTSTR strKey,BOOL bDescendent)
{
	if(bDescendent)
		return DeleteKeyDescendent(strKey);

	/* Call DeleteKey to remove a specified key and its associated data, 
	if any, from the registry. Returns FALSE is there are subkeys
	Subkeys must be explicitly deleted by separate calls to DeleteKey.
	DeleteKey returns True if key deletion is successful. On error, 
	DeleteKey returns False. */

	if (!KeyExists(strKey)) // 존재하는 키가 없다면 삭제는 성공한 것으로 본다. 
		return TRUE;

	HKEY hKey;
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,DELETE , &hKey) != ERROR_SUCCESS) 
		return FALSE;

	ASSERT(strKey[0] != '\\');

	if (::RegDeleteKey(m_hRootKey, strKey) != ERROR_SUCCESS) 
		return FALSE;
	return TRUE;
}


BOOL CQTRegistry::DeleteKeyDescendent(LPCTSTR strKey)
{
	strKey;

//	DWORD dwRet = SHDeleteKey(m_hRootKey,strKey);
//	if(dwRet == ERROR_SUCCESS )
//		return TRUE;
//	else 
		return FALSE;
}


BOOL CQTRegistry::DeleteValue(LPCTSTR strName)
{
	/* Call DeleteValue to remove a specific data value 
		associated with the current key. Name is string 
		containing the name of the value to delete. Keys can contain 
		multiple data values, and every value associated with a key 
		has a unique name. */

	ASSERT(m_strCurrentPath.GetLength() > 0);
	HKEY hKey;
	LONG lResult;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_SET_VALUE, &hKey) != ERROR_SUCCESS) return FALSE;

	lResult = ::RegDeleteValue(hKey, LPCTSTR(strName));
	::RegCloseKey(hKey);

	if (lResult == ERROR_SUCCESS) return TRUE;
	return FALSE;
}


int CQTRegistry::GetDataSize(LPCTSTR strValueName)
{
	/* Call GetDataSize to determine the size, in bytes, of 
	a data value associated with the current key. ValueName 
	is a string containing the name of the data value to query.
	On success, GetDataSize returns the size of the data value. 
	On failure, GetDataSize returns -1. */

	HKEY hKey;
	ASSERT(m_strCurrentPath.GetLength() > 0);
	LONG lResult;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS) return -1;

	DWORD dwSize = 1;
	lResult = ::RegQueryValueEx(hKey, LPCTSTR(strValueName),
		NULL, NULL, NULL, &dwSize);
	::RegCloseKey(hKey);

	if (lResult != ERROR_SUCCESS) return -1;
	return (int)dwSize;
}

DWORD CQTRegistry::GetDataType(LPCTSTR strValueName)
{
	HKEY hKey;
	ASSERT(m_strCurrentPath.GetLength() > 0);

	m_nLastError = ::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_QUERY_VALUE, &hKey);

	if (m_nLastError != ERROR_SUCCESS) return 0;

	DWORD dwType = 1;
	m_nLastError = ::RegQueryValueEx(hKey, LPCTSTR(strValueName),
		NULL, &dwType, NULL, NULL);
	::RegCloseKey(hKey);		

	if (m_nLastError == ERROR_SUCCESS) return dwType;

	return 0;
}



int CQTRegistry::GetSubKeyCount()
{
	/* Call this function to determine the number of subkeys.
		the function returns -1 on error */
	HKEY hKey;
	ASSERT(m_strCurrentPath.GetLength() > 0);

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS) return -1;

	LONG lResult;
	DWORD dwSubKeyCount, dwValueCount, dwClassNameLength,
		dwMaxSubKeyName, dwMaxValueName, dwMaxValueLength;
	FILETIME ftLastWritten;

	_TCHAR szClassBuffer[CLASS_NAME_LENGTH];
		
	dwClassNameLength = CLASS_NAME_LENGTH;
	lResult = ::RegQueryInfoKey(hKey, szClassBuffer, &dwClassNameLength,
		NULL, &dwSubKeyCount, &dwMaxSubKeyName, NULL, &dwValueCount,
		&dwMaxValueName, &dwMaxValueLength, NULL, &ftLastWritten);
				
	::RegCloseKey(hKey);
	if (lResult != ERROR_SUCCESS) return -1;

	return (int)dwSubKeyCount;
}


int CQTRegistry::GetValueCount()
{
	/* Call this function to determine the number of subkeys.
		the function returns -1 on error */
	HKEY hKey;
	ASSERT(m_strCurrentPath.GetLength() > 0);

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS) return -1;

	LONG lResult;
	DWORD dwSubKeyCount, dwValueCount, dwClassNameLength,
		dwMaxSubKeyName, dwMaxValueName, dwMaxValueLength;
	FILETIME ftLastWritten;

	_TCHAR szClassBuffer[CLASS_NAME_LENGTH];
		
	dwClassNameLength = CLASS_NAME_LENGTH;
	lResult = ::RegQueryInfoKey(hKey, szClassBuffer, &dwClassNameLength,
		NULL, &dwSubKeyCount, &dwMaxSubKeyName, NULL, &dwValueCount,
		&dwMaxValueName, &dwMaxValueLength, NULL, &ftLastWritten);
				
	::RegCloseKey(hKey);
	if (lResult != ERROR_SUCCESS) return -1;

	return (int)dwValueCount;
}


BOOL CQTRegistry::KeyExists(LPCTSTR strKey, HKEY hRootKey)
{
	/* Call KeyExists to determine if a key of a specified name exists.
		 Key is the name of the key for which to search. */

	ASSERT(strKey[0] != '\\');
	HKEY hKey;

	if (hRootKey == NULL) hRootKey = m_hRootKey;
	
	LONG lResult = ::RegOpenKeyEx(hRootKey, LPCTSTR(strKey), 0,
		KEY_ALL_ACCESS, &hKey);
	::RegCloseKey(hKey);
	if (lResult == ERROR_SUCCESS) return TRUE;
	return FALSE;
}

BOOL CQTRegistry::SetKey(LPCTSTR strKey, BOOL bCanCreate)
{
	/* Call SetKey to make a specified key the current key. Key is the 
		name of the key to open. If Key is null, the CurrentKey property 
		is set to the key specified by the RootKey property.

		CanCreate specifies whether to create the specified key if it does 
		not exist. If CanCreate is True, the key is created if necessary.

		Key is opened or created with the security access value KEY_ALL_ACCESS. 
		OpenKey only creates non-volatile keys, A non-volatile key is stored in 
		the registry and is preserved when the system is restarted. 

		OpenKey returns True if the key is successfully opened or created */

	ASSERT(strKey[0] != '\\');
	HKEY hKey;


	// close the current key if it is open
	if (CString(strKey).GetLength() == 0)
	{
		m_strCurrentPath.Empty();
		return TRUE;
	}

	DWORD dwDisposition;
	if (bCanCreate) // open the key with RegCreateKeyEx
	{
		if (::RegCreateKeyEx(m_hRootKey, LPCTSTR(strKey), 0, NULL, 
			REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey,
				&dwDisposition) != ERROR_SUCCESS) return FALSE;
		m_strCurrentPath = strKey;
		if (!m_bLazyWrite) ::RegFlushKey(hKey);
		::RegCloseKey(hKey);	
		return TRUE;
	}

	// otherwise, open the key without creating
	// open key requires no initial slash
	m_nLastError = ::RegOpenKeyEx(m_hRootKey, LPCTSTR(strKey), 0,
		KEY_ALL_ACCESS, &hKey);
	if (m_nLastError != ERROR_SUCCESS) return FALSE;
	m_strCurrentPath = strKey;
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return TRUE;
}


BOOL CQTRegistry::ValueExists(LPCTSTR strName)
{
	/* Call ValueExists to determine if a particular key exists in 
		the registry. Calling Value Exists is especially useful before 
		calling other TRegistry methods that operate only on existing keys.

		Name is the name of the data value for which to check.
	ValueExists returns True if a match if found, False otherwise. */

	HKEY hKey;
	LONG lResult;
	ASSERT(m_strCurrentPath.GetLength() > 0);

	
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS) return FALSE;

	lResult = ::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		NULL, NULL, NULL);
	::RegCloseKey(hKey);

	if (lResult == ERROR_SUCCESS) return TRUE;
	return FALSE;
}


void CQTRegistry::RenameValue(LPCTSTR strOldName, LPCTSTR strNewName)
{
	strOldName;
	strNewName;

	/* Call RenameValue to change the name of a data value associated 
		with the current key. OldName is a string containing the current 
		name of the data value. NewName is a string containing the replacement 
		name for the data value.
		
		If OldName is the name of an existing data value for the current key, 
		and NewName is not the name of an existing data value for the current 
		key, RenameValue changes the data value name as specified. Otherwise 
		the current name remains unchanged.
	*/
	ASSERT(FALSE); // functionality not yet implemented
}




COleDateTime CQTRegistry::ReadDateTime(LPCTSTR strName, COleDateTime dtDefault)
{
	/* Call ReadDate to read a date value from a specified data value 
	associated with the current key. Name is the name of the data value to read.
	If successful, ReadDate returns a Delphi TDateTime value. The integral part 
	of a TDateTime value is the number of days that have passed since 12/30/1899. 
	The fractional part of a TDateTime value is the time of day.
	On error, an exception is raised, and the value returned by this function 
	should be discarded. */

	DWORD dwType = REG_BINARY;
	COleDateTime dt;
	DWORD dwSize = sizeof(dt);
	HKEY hKey;

	ASSERT(m_strCurrentPath.GetLength() > 0);
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey) != ERROR_SUCCESS) return dtDefault;
	if (::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		&dwType, (LPBYTE)&dt, &dwSize) != ERROR_SUCCESS) dt = dtDefault;
	::RegCloseKey(hKey);	
	return dt;
}


double CQTRegistry::ReadFloat(LPCTSTR strName, double fDefault)
{
	/* Call ReadFloat to read a float value from a specified 
		data value associated with the current key. Name is the name 
		of the data value to read.
		
		If successful, ReadFloat returns a double value. 
		On error, an exception is raised, and the value returned by 
		this function should be discarded. */

	DWORD dwType = REG_BINARY;
	double d;
	DWORD dwSize = sizeof(d);
	HKEY hKey;

	ASSERT(m_strCurrentPath.GetLength() > 0);
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey) != ERROR_SUCCESS) return fDefault;

	if (::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		&dwType, (LPBYTE)&d, &dwSize) != ERROR_SUCCESS) d = fDefault;
	::RegCloseKey(hKey);	
	return d;
}

char * CQTRegistry::ReadString(LPCTSTR strName, LPCTSTR strDefault)
{
	memset(m_szValueTemp,0,255);

	DWORD dwType = REG_SZ;
	DWORD dwSize = 255;
	BOOL bSuccess = TRUE;

	HKEY hKey;
	
								 
	ASSERT(m_strCurrentPath.GetLength() > 0);

	// make sure it is the proper type
	dwType = GetDataType(strName);
	
	if (dwType != REG_SZ && dwType != REG_EXPAND_SZ)
	{
		return (char *)strDefault;
	}

	m_nLastError = ::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey);
	if (m_nLastError != ERROR_SUCCESS) 
		return (char *)strDefault;

	m_nLastError = ::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		&dwType, (LPBYTE)m_szValueTemp, &dwSize);
	if (m_nLastError != ERROR_SUCCESS) bSuccess = FALSE;
	::RegCloseKey(hKey);	
	
	if (!bSuccess) 
		return (char *)strDefault;
	return m_szValueTemp;
}

DWORD CQTRegistry::ReadDword(LPCTSTR strName, DWORD dwDefault)
{
	DWORD dwType = REG_DWORD;
	DWORD dw;
	DWORD dwSize = sizeof(dw);
	HKEY hKey;

	ASSERT(m_strCurrentPath.GetLength() > 0);
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey) != ERROR_SUCCESS) return dwDefault;

	if (::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		&dwType, (LPBYTE)&dw, &dwSize) != ERROR_SUCCESS) dw = dwDefault;
	::RegCloseKey(hKey);	
	return dw;
}



int CQTRegistry::ReadInt(LPCTSTR strName, int nDefault)
{
	DWORD dwType = REG_BINARY;
	int n;
	DWORD dwSize = sizeof(n);
	HKEY hKey;

	ASSERT(m_strCurrentPath.GetLength() > 0);
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey) != ERROR_SUCCESS) return nDefault;

	if (::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,&dwType, (LPBYTE)&n, &dwSize) != ERROR_SUCCESS) 
		n = nDefault;
	::RegCloseKey(hKey);	
	return n;
}

BOOL CQTRegistry::ReadBool(LPCTSTR strName, BOOL bDefault)
{
	DWORD dwType = REG_BINARY;
	BOOL b;
	DWORD dwSize = sizeof(b);
	HKEY hKey;

	ASSERT(m_strCurrentPath.GetLength() > 0);
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey) != ERROR_SUCCESS) return bDefault;

	if (::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		&dwType, (LPBYTE)&b, &dwSize) != ERROR_SUCCESS) b = bDefault;
	::RegCloseKey(hKey);	
	return b;
}


COLORREF CQTRegistry::ReadColor(LPCTSTR strName, COLORREF rgbDefault)
{
	DWORD dwType = REG_BINARY;
	COLORREF rgb;
	DWORD dwSize = sizeof(rgb);
	HKEY hKey;

	ASSERT(m_strCurrentPath.GetLength() > 0);
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey) != ERROR_SUCCESS) return rgbDefault;

	if (::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		&dwType, (LPBYTE)&rgb, &dwSize) != ERROR_SUCCESS) rgb = rgbDefault;
	::RegCloseKey(hKey);	
	return rgb;
}

BOOL CQTRegistry::ReadFont(LPCTSTR strName, CFont* pFont)
{
	DWORD dwType = REG_BINARY;
	DWORD dwSize = sizeof(LOGFONT);
	BOOL bSuccess = TRUE;
	HKEY hKey;
	LOGFONT lf;

	ASSERT(m_strCurrentPath.GetLength() > 0);
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey) != ERROR_SUCCESS) return FALSE;

	if (::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		&dwType, (LPBYTE)&lf, &dwSize) != ERROR_SUCCESS) bSuccess = FALSE;
	::RegCloseKey(hKey);	
	if (bSuccess)
	{
		pFont->Detach();
		pFont->CreateFontIndirect(&lf);
	}
	return bSuccess;
}


BOOL CQTRegistry::ReadPoint(LPCTSTR strName, CPoint* pPoint)
{
	DWORD dwType = REG_BINARY;
	DWORD dwSize = sizeof(CPoint);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	ASSERT(m_strCurrentPath.GetLength() > 0);
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey) != ERROR_SUCCESS) return FALSE;

	if (::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		&dwType, (LPBYTE)pPoint, &dwSize) != ERROR_SUCCESS) bSuccess = FALSE;
	::RegCloseKey(hKey);	
	return bSuccess;
}

BOOL CQTRegistry::ReadSize(LPCTSTR strName, CSize* pSize)
{
	DWORD dwType = REG_BINARY;
	DWORD dwSize = sizeof(CSize);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	ASSERT(m_strCurrentPath.GetLength() > 0);
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey) != ERROR_SUCCESS) return FALSE;

	if (::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		&dwType, (LPBYTE)pSize, &dwSize) != ERROR_SUCCESS) bSuccess = FALSE;
	::RegCloseKey(hKey);	
	return bSuccess;
}

BOOL CQTRegistry::ReadRect(LPCTSTR strName, CRect* pRect)
{
	DWORD dwType = REG_BINARY;
	DWORD dwSize = sizeof(CRect);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	ASSERT(m_strCurrentPath.GetLength() > 0);
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey) != ERROR_SUCCESS) return FALSE;

	if (::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		&dwType, (LPBYTE)pRect, &dwSize) != ERROR_SUCCESS) bSuccess = FALSE;
	::RegCloseKey(hKey);	
	return bSuccess;
}




BOOL CQTRegistry::WriteBool(LPCTSTR strName, BOOL bValue)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_BINARY, (LPBYTE)&bValue, sizeof(bValue))
		 != ERROR_SUCCESS) bSuccess = FALSE;
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}

BOOL CQTRegistry::WriteDateTime(LPCTSTR strName, COleDateTime dtValue)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_BINARY, (LPBYTE)&dtValue, sizeof(dtValue))
		 != ERROR_SUCCESS) bSuccess = FALSE;
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}


BOOL CQTRegistry::WriteString(LPCTSTR strName, LPCTSTR strValue)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;
	_TCHAR sz[255];
	
	if (CString(strValue).GetLength() > 254) return FALSE;

#ifdef _UNICODE
	wstrcpy(sz, LPCTSTR(strValue));
#else
	strcpy(sz, LPCTSTR(strValue));
#endif

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
#ifdef _UNICODE
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_SZ, (LPBYTE)sz, wstrlen(sz) + 1)
		 != ERROR_SUCCESS) bSuccess = FALSE;
#else
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_SZ, (LPBYTE)sz, (int)strlen(sz) + 1)
		 != ERROR_SUCCESS) bSuccess = FALSE;
#endif
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}


BOOL CQTRegistry::WriteFloat(LPCTSTR strName, double fValue)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_BINARY, (LPBYTE)&fValue, sizeof(fValue))
		 != ERROR_SUCCESS) bSuccess = FALSE;
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}

BOOL CQTRegistry::WriteInt(LPCTSTR strName, int nValue)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_BINARY, (LPBYTE)&nValue, sizeof(nValue))
		 != ERROR_SUCCESS) bSuccess = FALSE;
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}

BOOL CQTRegistry::WriteDword(LPCTSTR strName, DWORD dwValue)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_DWORD, (LPBYTE)&dwValue, sizeof(dwValue))
		 != ERROR_SUCCESS) bSuccess = FALSE;
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}

BOOL CQTRegistry::WriteColor(LPCTSTR strName, COLORREF rgbValue)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_BINARY, (LPBYTE)&rgbValue, sizeof(rgbValue))
		 != ERROR_SUCCESS) bSuccess = FALSE;
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}


BOOL CQTRegistry::WriteFont(LPCTSTR strName, CFont* pFont)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	LOGFONT lf;
	pFont->GetLogFont(&lf);

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_BINARY, (LPBYTE)&lf, sizeof(lf))
		 != ERROR_SUCCESS) bSuccess = FALSE;
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}


BOOL CQTRegistry::WritePoint(LPCTSTR strName, CPoint* pPoint)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_BINARY, (LPBYTE)pPoint, sizeof(CPoint))
		 != ERROR_SUCCESS) bSuccess = FALSE;
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}


BOOL CQTRegistry::WriteSize(LPCTSTR strName, CSize* pSize)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_BINARY, (LPBYTE)pSize, sizeof(CSize))
		 != ERROR_SUCCESS) bSuccess = FALSE;
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}

BOOL CQTRegistry::WriteRect(LPCTSTR strName, CRect* pRect)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_BINARY, (LPBYTE)pRect, sizeof(CRect))
		 != ERROR_SUCCESS) bSuccess = FALSE;
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}



void CQTRegistry::EnumRegistryKey(HKEY hKey, LPCTSTR strKeyName, std::vector< CString >& ListEnumKey)
{
	LONG retcode = ERROR_SUCCESS;
	HKEY hOpenKey = NULL;
	char str[MAX_PATH];
	memset( str, '\0', sizeof(str));
	ListEnumKey.clear();
	
	if(CString(strKeyName).GetLength()>0)
        retcode = RegOpenKey( hKey, strKeyName, &hOpenKey);
	else
		hOpenKey = hKey;

	if( retcode != (DWORD)ERROR_SUCCESS )
		return;

	for (int i = 0, retCode = ERROR_SUCCESS; 
            retCode == ERROR_SUCCESS; i++) 
    {
        retCode = RegEnumKey(hOpenKey, 
                     i, 
                     str, 
                     MAX_PATH
					); 

        if (retCode == (DWORD)ERROR_SUCCESS) 
        {
			CString sNewKeyName;
			sNewKeyName = str;
			
			if(sNewKeyName.GetLength()>0)
                ListEnumKey.push_back( sNewKeyName );
        }
    }

	if(hKey)
		RegCloseKey( hOpenKey );
}

void CQTRegistry::EnumRegistryKeyValue(HKEY hKey, LPCTSTR strKeyName, std::vector< RegKeyDetail >& ListEnumKey)
{
	LONG retcode = ERROR_SUCCESS;
	HKEY hOpenKey = NULL;
	DWORD dwType = REG_SZ;
	char str[MAX_REG_KEY_NAME];
	memset( str, '\0', sizeof(str));
	
	if(CString(strKeyName).GetLength()>0)
        retcode = RegOpenKeyEx(hKey, strKeyName, 0, KEY_READ, &hOpenKey);
	else
		hOpenKey = hKey;

	if( retcode != (DWORD)ERROR_SUCCESS )
		return;

	BYTE *data;
	data = new BYTE[MAX_REG_KEY_VALUE];
	memset( data, '\0', sizeof(data));

	ListEnumKey.clear();

	DWORD Size;
//	DWORD dwNo = 0;

	RegKeyDetail KeyValue;


	// name 이 "" 인 value (Default 값) 를 구함.
	SetRootKey(hKey);
	SetKey(strKeyName,FALSE);
	CString strDefValue	= ReadString("","");

	KeyValue.strRegKeyName		= "(Default)";
	KeyValue.dwRegType			= REG_SZ;
	KeyValue.m_RegData.strData	= strDefValue;
	ListEnumKey.push_back( KeyValue );

	for (int i = 0, retCode = ERROR_SUCCESS; 
            retCode == ERROR_SUCCESS; i++) 
    {
		Size = MAX_REG_KEY_NAME;
		DWORD dwNo = MAX_REG_KEY_VALUE;
        
		retCode = RegEnumValue(hOpenKey,
                     i,
                     str,
                     &Size,
					 NULL,
					 &dwType,
					 data,
					 &dwNo
					);

		// 초기화
		KeyValue.strRegKeyName		= "";
		KeyValue.dwRegType			= 0;
		KeyValue.m_RegData.strData	= "";
		KeyValue.m_RegData.pData	= NULL;
		KeyValue.m_RegData.dwData	= 0;

		if (retCode != (DWORD) ERROR_NO_MORE_ITEMS)// && retCode != ERROR_INSUFFICIENT_BUFFER)
		{
			KeyValue.strRegKeyName = str;
			KeyValue.dwRegType = dwType;

			if(dwType==REG_SZ)
			{
				if( dwNo >0 )
				{
					data[(dwNo-1)] = '\0';
                    KeyValue.m_RegData.strData = (char*)data;
				}
				else
				{
					KeyValue.m_RegData.strData = "";
				}
			}
			else if(dwType==REG_EXPAND_SZ)
			{
				if( dwNo >0 )
				{
					data[(dwNo-1)] = '\0';
                    KeyValue.m_RegData.strData = (char*)data;
				}
				else
				{
					KeyValue.m_RegData.strData = "";
				}
			}
			else if(dwType==REG_MULTI_SZ)
			{
				if( dwNo >1 )
				{
					for(int i=0;i<(int)dwNo;i++)
					{
						if( data[i]=='\0' )
						{
                            data[i] = '\r';
						}
					}

					data[(dwNo-1)] = '\0';
					data[(dwNo-2)] = '\0';

                    KeyValue.m_RegData.strData = (char*)data;
				}
				else
				{
					KeyValue.m_RegData.strData = "";
				}
			}
			else if( (dwType==REG_BINARY)|| (dwType==REG_RESOURCE_LIST) || (dwType==REG_FULL_RESOURCE_DESCRIPTOR) || (dwType==REG_RESOURCE_REQUIREMENTS_LIST) )
			{
				if( dwNo >0 )
				{
					char temp[4];
					memset(temp, '\0', sizeof(temp));

                    KeyValue.m_RegData.pData = new char[dwNo*3 + 10];
					memset( KeyValue.m_RegData.pData, '\0', (dwNo*3 + 10) );

					for(int j=0; j<(int)dwNo; j++)
					{
						sprintf(temp, "%02X ", (long int)data[j]);
                        lstrcat( KeyValue.m_RegData.pData, temp );
					}
				}
				else
				{
					KeyValue.m_RegData.pData = NULL;
				}
			}
			else if(dwType==REG_DWORD)
			{
				memcpy( &KeyValue.m_RegData.dwData, data, sizeof(DWORD));
			}
//			else
//			{
//				int i = 0;
//			}
			
			if(KeyValue.strRegKeyName.GetLength() > 0)
                ListEnumKey.push_back( KeyValue );

			retCode = ERROR_SUCCESS;
        }
    }

	if(hKey)
		RegCloseKey( hOpenKey );

	delete[] data;
}