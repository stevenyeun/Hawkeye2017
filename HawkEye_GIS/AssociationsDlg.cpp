// AssociationsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PictureShow.h"
#include "AssociationsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAssociationsDlg dialog


//-----------------------------------------------------------------------------
CAssociationsDlg::CAssociationsDlg(CWnd* pParent /*=NULL*/)
 : CDialog(CAssociationsDlg::IDD, pParent)
//=============================================================================
{
	//{{AFX_DATA_INIT(CAssociationsDlg)
	m_AssociateBMP = FALSE;
	m_AssociateDIB = FALSE;
	m_AssociateEMF = FALSE;
	m_AssociateGIF = FALSE;
	m_AssociateICO = FALSE;
	m_AssociateJPG = FALSE;
	m_AssociateWMF = FALSE;
	m_AssociateALL = FALSE;
	//}}AFX_DATA_INIT
}


//-----------------------------------------------------------------------------
void CAssociationsDlg::DoDataExchange(CDataExchange* pDX)
//=============================================================================
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAssociationsDlg)
	DDX_Check(pDX, IDC_CHECK_BMP, m_AssociateBMP);
	DDX_Check(pDX, IDC_CHECK_DIB, m_AssociateDIB);
	DDX_Check(pDX, IDC_CHECK_EMF, m_AssociateEMF);
	DDX_Check(pDX, IDC_CHECK_GIF, m_AssociateGIF);
	DDX_Check(pDX, IDC_CHECK_ICO, m_AssociateICO);
	DDX_Check(pDX, IDC_CHECK_JPG, m_AssociateJPG);
	DDX_Check(pDX, IDC_CHECK_WMF, m_AssociateWMF);
	DDX_Check(pDX, IDC_CHECK_ALL, m_AssociateALL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAssociationsDlg, CDialog)
	//{{AFX_MSG_MAP(CAssociationsDlg)
	ON_BN_CLICKED(IDC_BUTTON_ASSOCIATE, OnButtonAssociate)
	ON_BN_CLICKED(IDC_CHECK_ALL, OnCheckAll)
	ON_BN_CLICKED(IDC_CHECK_BMP, OnCheckBmp)
	ON_BN_CLICKED(IDC_CHECK_DIB, OnCheckDib)
	ON_BN_CLICKED(IDC_CHECK_EMF, OnCheckEmf)
	ON_BN_CLICKED(IDC_CHECK_GIF, OnCheckGif)
	ON_BN_CLICKED(IDC_CHECK_ICO, OnCheckIco)
	ON_BN_CLICKED(IDC_CHECK_JPG, OnCheckJpg)
	ON_BN_CLICKED(IDC_CHECK_WMF, OnCheckWmf)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAssociationsDlg message handlers

//-----------------------------------------------------------------------------
// Does:   Associate The Chosen Extentions (Marked On The Dialog),
// ~~~~    So When File With This Extention Is Cliked - Windows Will Open This
//         Application With The Clicked FileName As a Parameter
//
// Note:   Some Registry Functions Does Not Work The Same On Windows9x And NT
// ~~~~    Or Not Always Supported - SHDeleteKey(), RecurseDeleteKey()
//         So I Use My Custom RegExterminateKey() - Works On Windows9x + NT
//
// OutPut: TRUE If Succeeded...
// ~~~~~~
//-----------------------------------------------------------------------------
void CAssociationsDlg::OnButtonAssociate() 
//=============================================================================
{
	BOOL Chosen = FALSE;
	BOOL AnswerYES = TRUE;

	CString sKey;  // Key + Sub Keys...
	CString sType; // Type (Extention)
	CString sName; // Program Name Associated
	CString sIcon; // Icon To Associate
	CString sExec; // Shell Execute "String %1"

	HWND hWnd = AfxGetApp()->GetMainWnd()->m_hWnd;

	UpdateData(TRUE); // This Will Suck The Data From The Marked Check Box...

	CAssociationsDlg::OnOK(); // Close The Dialog...

	// YES_NO Question Box (R U Sure ?)
	if(MessageBoxEx(hWnd, "This will change the registry\n(File extentions will open with this application in the future)\t\n\nDo you wish to continue ?\t", "Attention", MB_YESNO | MB_ICONINFORMATION, LANG_ENGLISH) == IDYES)
	for(int Association = 1; Association <= 7; Association++) // Check One By One...
		{
		// Skip To Next Association If Not Needed Here...
		if(Association == 1 && !m_AssociateBMP) continue;
		if(Association == 2 && !m_AssociateDIB) continue;
		if(Association == 3 && !m_AssociateEMF) continue;
		if(Association == 4 && !m_AssociateGIF) continue;
		if(Association == 5 && !m_AssociateICO) continue;
		if(Association == 6 && !m_AssociateJPG) continue;
		if(Association == 7 && !m_AssociateWMF) continue;

		Chosen = TRUE; // If We Got Here - At Least One Extention Was Chosen

		// Associate Specific...
		switch(Association)
			{
			case 1: // BMP
					sType = _T(".bmp");
					sName = _T(".bmp");
					sIcon; sIcon.Format("%s,1", _pgmptr);
					sExec; sExec.Format("%s %c1", _pgmptr, '%');
					break;
			case 2: // DIB
					sType = _T(".dib");
					sName = _T(".dib");
					sIcon; sIcon.Format("%s,2", _pgmptr);
					sExec; sExec.Format("%s %c1", _pgmptr, '%');
					break;
			case 3: // EMF
					sType = _T(".emf");
					sName = _T(".emf");
					sIcon; sIcon.Format("%s,3", _pgmptr);
					sExec; sExec.Format("%s %c1", _pgmptr, '%');
					break;
			case 4: // GIF
					sType = _T(".gif");
					sName = _T(".gif");
					sIcon; sIcon.Format("%s,4", _pgmptr);
					sExec; sExec.Format("%s %c1", _pgmptr, '%');
					break;
			case 5: // ICO
					sType = _T(".ico");
					sName = _T(".ico");
					sIcon; sIcon.Format("%s,5", _pgmptr);
					sExec; sExec.Format("%s %c1", _pgmptr, '%');
					break;
			case 6: // JPG
					sType = _T(".jpg");
					sName = _T(".jpg");
					sIcon; sIcon.Format("%s,6", _pgmptr);
					sExec; sExec.Format("%s %c1", _pgmptr, '%');
					break;
			case 7: // WMF
					sType = _T(".wmf");
					sName = _T(".wmf");
					sIcon; sIcon.Format("%s,7", _pgmptr);
					sExec; sExec.Format("%s %c1", _pgmptr, '%');
					break;
			} // switch(Association)

		HKEY hKey;
		// Check If The Key Exists - So We Can Delete It Later (Only KEY_READ)
		if(RegOpenKeyEx(HKEY_CLASSES_ROOT, sType, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
			{
			// Try To Delete It - (Only When The Key Does Exist)
			if(!RegExterminateKey(HKEY_CLASSES_ROOT, sType, NULL))
				{
				RegCloseKey(hKey);
				MessageBoxEx(hWnd, "Can not recursively delete the registry key\t\n(You may not have permission to WRITE into registry)\t\nMission aborted\t", "Access Violation", MB_OK | MB_ICONSTOP, LANG_ENGLISH);
				break;
				}
			RegCloseKey(hKey);
			}
		// Continue Creating Key (Do Need To Report a Open Error - Coz It Might Not Exist Yet)

		if((sExec.GetLength() > 255 - 4)||
		   (sIcon.GetLength() > 255 - 4)||
		   (sType.GetLength() > 255 - sType.GetLength()))
			{
			MessageBoxEx(hWnd, "Can not associate path longer than 255 characters\t\nTo associate - Put this file in a shorter path on your hard drive and try again\t", "Error - Path is too long", MB_OK | MB_ICONSTOP, LANG_ENGLISH);
			break; // Stop Messing With Registry...
			}
		else // Create Key...
			{
			if(RegCreateKey(HKEY_CLASSES_ROOT, sType, &hKey) == ERROR_SUCCESS)
				{
				// I Guess Some Programs Uses This (Exp: Windows Commander)
				RegSetValue(hKey, NULL, REG_SZ, sName, strlen(sName)+1);

				sKey.Format("%s\\DefaultIcon", sType);
				RegCreateKey(HKEY_CLASSES_ROOT, sKey, &hKey);
				RegSetValue(hKey, NULL, REG_SZ, sIcon, strlen(sIcon)+1);

				sKey.Format("%s\\Shell\\Open\\Command", sType);
				RegCreateKey(HKEY_CLASSES_ROOT, sKey, &hKey);
				RegSetValue(hKey, NULL, REG_SZ, sExec, strlen(sExec)+1);

				sKey.Format("%s\\Shell\\View with The Yovav (Horror) PictureShow\\Command", sType);
				RegCreateKey(HKEY_CLASSES_ROOT, sKey, &hKey);
				RegSetValue(hKey, NULL, REG_SZ, sExec, strlen(sExec)+1);

				RegCloseKey(hKey);
				}
			else 
				{
				MessageBoxEx(hWnd, "Can not gain WRITE accesss to the registry\t\nPlease try to login windows with more permissions\t", "Access Violation", MB_OK | MB_ICONSTOP, LANG_ENGLISH);
				break;
				}
			}

	} // IDYES
	else AnswerYES = FALSE; // Coz We Only Get Chosen After The Loop Is Made...

	if(Chosen == FALSE && AnswerYES == TRUE) MessageBoxEx(hWnd, "No extentions were chosen - Nothing to associate\t", "Attention", MB_OK | MB_ICONINFORMATION, LANG_ENGLISH);

}

//-----------------------------------------------------------------------------
// Does:   Clear The Chosen Extentions (Marked On The Dialog),
// ~~~~    Remove Association By Deleting The Whole Key
//
// Note:   Some Registry Functions Does Not Work The Same On Windows9x And NT
// ~~~~    Or Not Always Supported - SHDeleteKey(), RecurseDeleteKey()
//         So I Use My Custom RegExterminateKey() - Works On Windows9x + NT
//
// OutPut: TRUE If Succeeded...
// ~~~~~~
//-----------------------------------------------------------------------------
void CAssociationsDlg::OnButtonClear() 
//=============================================================================
{
	BOOL Chosen = FALSE;
	BOOL AnswerYES = TRUE;

	CString sKey;  // Key + Sub Keys...
	CString sType; // Type (Extention)

	HWND hWnd = AfxGetApp()->GetMainWnd()->m_hWnd;

	UpdateData(TRUE); // This Will Suck The Data From The Marked Check Box...

	CAssociationsDlg::OnOK(); // Close The Dialog...

	// YES_NO Question Box (R U Sure ?)
	if(MessageBoxEx(hWnd, "This will CLEAR associations from registry\n(File extentions will NOT open when clicked)\t\n\nDo you wish to continue ?\t", "Attention", MB_YESNO | MB_ICONINFORMATION, LANG_ENGLISH) == IDYES)
	for(int Association = 1; Association <= 7; Association++) // Check One By One...
		{
		// Skip To Next Association If Not Needed Here...
		if(Association == 1 && !m_AssociateBMP) continue;
		if(Association == 2 && !m_AssociateDIB) continue;
		if(Association == 3 && !m_AssociateEMF) continue;
		if(Association == 4 && !m_AssociateGIF) continue;
		if(Association == 5 && !m_AssociateICO) continue;
		if(Association == 6 && !m_AssociateJPG) continue;
		if(Association == 7 && !m_AssociateWMF) continue;

		Chosen = TRUE; // If We Got Here - At Least One Extention Was Chosen

		// Associate Specific...
		switch(Association)
			{
			case 1: sType = _T(".bmp"); break;
			case 2: sType = _T(".dib"); break;
			case 3: sType = _T(".emf"); break;
			case 4: sType = _T(".gif"); break;
			case 5: sType = _T(".ico"); break;
			case 6: sType = _T(".jpg"); break;
			case 7: sType = _T(".wmf"); break;
			} // switch(Association)

		HKEY hKey;
		// Check If The Key Exists - So We Can Delete It Later (Only KEY_READ)
		if(RegOpenKeyEx(HKEY_CLASSES_ROOT, sType, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
			{
			// Try To Delete It - (Only When The Key Does Exist)
			if(!RegExterminateKey(HKEY_CLASSES_ROOT, sType, NULL))
				{
				RegCloseKey(hKey);
				MessageBoxEx(hWnd, "Can not recursively delete the registry key\t\n(You may not have permission to WRITE into registry)\t\nMission aborted\t", "Access Violation", MB_OK | MB_ICONSTOP, LANG_ENGLISH);
				break;
				}
			RegCloseKey(hKey);
			}
		else // If Key Is Marked For Deletion - But Does Not Exist - Popup a Message...
			{
			CString sError;
			sError.Format("Can not OPEN the selected registry key \"%s\"\t\nKey does not exist OR more access permissions needed\t", sType);
			MessageBoxEx(hWnd, sError, "Access Violation", MB_OK | MB_ICONSTOP, LANG_ENGLISH);
			}

	} // IDYES
	else AnswerYES = FALSE; // Coz We Only Get Chosen After The Loop Is Made...

	if(Chosen == FALSE && AnswerYES == TRUE) MessageBoxEx(hWnd, "No extentions were chosen - No associations to clear\t", "Attention", MB_OK | MB_ICONINFORMATION, LANG_ENGLISH);
		
}

//-----------------------------------------------------------------------------
BOOL CAssociationsDlg::AllChecked()
//=============================================================================
{
	UpdateData(TRUE);

	if(m_AssociateBMP &&
	   m_AssociateDIB &&
	   m_AssociateEMF &&
	   m_AssociateGIF &&
	   m_AssociateICO &&
	   m_AssociateJPG &&
	   m_AssociateWMF) return(TRUE);

	return(FALSE);
}

//-----------------------------------------------------------------------------
void CAssociationsDlg::OnCheckAll() 
//=============================================================================
{
	UpdateData(TRUE);

	m_AssociateBMP = m_AssociateALL;
	m_AssociateDIB = m_AssociateALL;
	m_AssociateEMF = m_AssociateALL;
	m_AssociateGIF = m_AssociateALL;
	m_AssociateICO = m_AssociateALL;
	m_AssociateJPG = m_AssociateALL;
	m_AssociateWMF = m_AssociateALL;

	UpdateData(FALSE);
}

//-----------------------------------------------------------------------------
void CAssociationsDlg::OnCheckBmp() 
//=============================================================================
{
	UpdateData(TRUE);
	
	if(AllChecked()) m_AssociateALL = TRUE; else m_AssociateALL = FALSE;

	UpdateData(FALSE);
	
}

//-----------------------------------------------------------------------------
void CAssociationsDlg::OnCheckDib() 
//=============================================================================
{
	UpdateData(TRUE);
	
	if(AllChecked()) m_AssociateALL = TRUE; else m_AssociateALL = FALSE;

	UpdateData(FALSE);
}

//-----------------------------------------------------------------------------
void CAssociationsDlg::OnCheckEmf() 
//=============================================================================
{
	UpdateData(TRUE);
	
	if(AllChecked()) m_AssociateALL = TRUE; else m_AssociateALL = FALSE;

	UpdateData(FALSE);
}

//-----------------------------------------------------------------------------
void CAssociationsDlg::OnCheckGif() 
//=============================================================================
{
	UpdateData(TRUE);
	
	if(AllChecked()) m_AssociateALL = TRUE; else m_AssociateALL = FALSE;

	UpdateData(FALSE);
}

//-----------------------------------------------------------------------------
void CAssociationsDlg::OnCheckIco() 
//=============================================================================
{
	UpdateData(TRUE);
	
	if(AllChecked()) m_AssociateALL = TRUE; else m_AssociateALL = FALSE;

	UpdateData(FALSE);

	if(m_AssociateICO)
		{
		HWND hWnd = AfxGetApp()->GetMainWnd()->m_hWnd;
		MessageBoxEx(hWnd, "It is NOT recommended to associate this extention\t\n(It may have effect on some other programs)\t\nPlease uncheck it - unless you feel like a real expert\t", "Warning", MB_OK | MB_ICONWARNING, LANG_ENGLISH);
		}

//PersistentHandler -> {098f2470-bae0-11cd-b579-08002b30bfeb}
}

//-----------------------------------------------------------------------------
void CAssociationsDlg::OnCheckJpg() 
//=============================================================================
{
	UpdateData(TRUE);
	
	if(AllChecked()) m_AssociateALL = TRUE; else m_AssociateALL = FALSE;

	UpdateData(FALSE);
}

//-----------------------------------------------------------------------------
void CAssociationsDlg::OnCheckWmf() 
//=============================================================================
{
	UpdateData(TRUE);
	
	if(AllChecked()) m_AssociateALL = TRUE; else m_AssociateALL = FALSE;

	UpdateData(FALSE);
}

//-----------------------------------------------------------------------------
BOOL CAssociationsDlg::RegExterminateKey(HKEY hKey, LPCTSTR SubKey, LPCTSTR Value)
//=============================================================================
{
	LONG lRes;
	HKEY hSubKey;
	
	if(RegOpenKeyEx(hKey, SubKey, 0, KEY_WRITE | KEY_READ,	&hSubKey) != ERROR_SUCCESS) 
	return(FALSE); // Can Not Open Key - (Do Not Stop Here With a Message...)

	if(Value) 
		{
		// Try To Delete The Given Value
		lRes = RegDeleteValue(hSubKey, Value);
		RegCloseKey(hSubKey);
		RegCloseKey(hKey );
		if(lRes != ERROR_SUCCESS) return(FALSE); // Could Not Delete...
		}
	else // Delete The Whole Key And All Sub Keys...
		{
		DWORD SubKeysNumber = 0 ;
		do // Remove All Keys (Recursively)
			{
			DWORD MaxSubKey;
			if(RegQueryInfoKey(hSubKey,0,0,0,&SubKeysNumber,&MaxSubKey,0,0,0,0,0,0) != ERROR_SUCCESS)
				{
				RegCloseKey(hSubKey);
				return(FALSE);
				}

			if(SubKeysNumber > 0) 
				{
				LPTSTR KeyName = new TCHAR[MaxSubKey + 1];
				DWORD  KeyNameLen = MaxSubKey;

				if(RegEnumKey(hSubKey, 0, KeyName, KeyNameLen+1) != ERROR_SUCCESS)
					{
					delete [] KeyName;
					RegCloseKey(hSubKey);
					return(FALSE);
					}

				// Call ItSelf Until All Keys Are Exterminated (Recursively)
				if(!RegExterminateKey(hSubKey, KeyName, Value))
					{
					delete [] KeyName;
					RegCloseKey(hSubKey);
					return(FALSE);
					}
				delete [] KeyName;
				}
			}
		while(SubKeysNumber > 0);
		
		RegCloseKey(hSubKey);

		if(RegDeleteKey(hKey, SubKey) != ERROR_SUCCESS)	return(FALSE);
		}

	return(TRUE);

}
