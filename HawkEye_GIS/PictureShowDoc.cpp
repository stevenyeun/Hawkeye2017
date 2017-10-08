// PictureShowDoc.cpp : implementation of the CPictureShowDoc class
//

#include "stdafx.h"
#include "PictureShow.h"
#include "PictureShowDoc.h"

//  [3/28/2014 Yeun]
#include "OptCommonInfo.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPictureShowDoc

IMPLEMENT_DYNCREATE(CPictureShowDoc, CDocument)

	BEGIN_MESSAGE_MAP(CPictureShowDoc, CDocument)
		//{{AFX_MSG_MAP(CPictureShowDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPictureShowDoc construction/destruction

//-----------------------------------------------------------------------------
CPictureShowDoc::CPictureShowDoc()
//=============================================================================
{
	CPictureShowApp* pApp = (CPictureShowApp*)::AfxGetApp();
	

	
	//yeun disable
	/*
	m_FilePathName.Format("%s", pApp->m_lpCmdLine);

	if(m_FilePathName.GetLength() != 0)
		{
		//AfxMessageBox(m_FilePathName);
		m_Picture.Load(m_FilePathName);
		m_FilePathNameLast = "";
		}
	else
		{
		m_Picture.Load(IDR_DEFAULT, "JPG");
		m_FilePathName = "";
		m_FilePathNameLast = "";
		}

	CreateFilesList(); // Create a Picture Files List If Picture Files Exists
	*/

	//SetTitle( _T("HWAKEYE_GIS") );
	
}

//-----------------------------------------------------------------------------
CPictureShowDoc::~CPictureShowDoc()
//=============================================================================
{
	COptCommonInfo OptCommonInfo;
	strcpy( OptCommonInfo.m_s.strMapFilePathName, m_strMapPathName );
	OptCommonInfo.Write();
}

//-----------------------------------------------------------------------------
BOOL CPictureShowDoc::OnNewDocument()
//=============================================================================
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPictureShowDoc serialization
//-----------------------------------------------------------------------------
void CPictureShowDoc::Serialize(CArchive& ar)
//=============================================================================
{
	if(ar.IsStoring())
	{
	// OnFileSaveAs() Is On CPictureShowDoc
	}
	else
	{
	// OnFileOpen() Is On CPictureShowDoc
	}

}

/////////////////////////////////////////////////////////////////////////////
// CPictureShowDoc diagnostics

#ifdef _DEBUG
//-----------------------------------------------------------------------------
void CPictureShowDoc::AssertValid() const
//=============================================================================
{
	CDocument::AssertValid();
}

//-----------------------------------------------------------------------------
void CPictureShowDoc::Dump(CDumpContext& dc) const
//=============================================================================
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPictureShowDoc commands

//-----------------------------------------------------------------------------
void CPictureShowDoc::OnFileOpen()
//=============================================================================
{
	//  [3/29/2014 Yeun]
	/*
		CString strFilter = "Picture Files (bmp.dib.emf.gif.ico.jpg.wmf)|*.bmp;dib;emf;gif;ico;*.jpg;wmf|BMP (*.bmp)|*.bmp|DIB (*.dib)|*.dib|EMF (*.emf)|*.emf|GIF (*.gif)|*.gif|ICO (*.ico)|*.ico|JPG (*.jpg)|*.jpg|WMF (*.wmf)|*.wmf|All Files (*.*)|*.*||";
			CFileDialog OpenFileDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
			OpenFileDialog.m_ofn.lpstrTitle = "Open a picture file";
		
			if(OpenFileDialog.DoModal() == IDOK)
				{
				m_FilePathName.Format("%s", OpenFileDialog.m_ofn.lpstrFile);
				UpdateAllViews(NULL);
				
				CreateFilesList(); // Read Files At The Current Directory As It Changes
				}*/
		
}

//-----------------------------------------------------------------------------
void CPictureShowDoc::OnFileSaveAs() 
//=============================================================================
{
	//  [3/29/2014 Yeun]
/*
	CString sFilter = "BMP - Bitmap picture (*.bmp)|*.bmp;ico|ICO - 16 Color Icon (*.ico)|*.ico;bmp||";
	CFileDialog OpenFileDialog(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sFilter);
	OpenFileDialog.m_ofn.lpstrTitle = "Save picture as a Bitmap (BMP/ICO) file";

	if(OpenFileDialog.DoModal() == IDOK)
		{
		// Update File Name And Extention...
		CString Extentions[2] = {"bmp","ico"};
		m_FilePathName.Format("%s.%s", OpenFileDialog.m_ofn.lpstrFile, Extentions[OpenFileDialog.m_ofn.nFilterIndex-1]);
		if(!m_Picture.SaveAsBitmap(m_FilePathName)) m_FilePathName = "";
		UpdateAllViews(NULL); // Make Sure File Is Loaded Again...

		CreateFilesList(); // Read Files At The Current Directory As It Changes
		}*/

	
}

//-----------------------------------------------------------------------------
BOOL CPictureShowDoc::CreateFilesList()
//=============================================================================
{
	//  [3/29/2014 Yeun]
	/*
		m_Finding = m_Finder.FindFile("*.*"); // Finds All Files (By Name)
		
			CString Extention;
		
			m_FilesList.RemoveAll(); // Clear - In Case We Created Another List...
			m_FilesList.GetHeadPosition();
		
			while(m_Finding == TRUE)
				{
				if(m_Finder.IsDots() || m_Finder.IsDirectory())	m_Finding = m_Finder.FindNextFile();
				else // It Is a File...
					{
					// Get The Extention Of The Current Handled File
					Extention.Format("%s", FileExtentionOnly(m_Finder.GetFileName()));
					Extention.MakeUpper(); // Just In Case (Sensitive)...
		
					// Add To The List
					if(IsWantedExtention(Extention)) m_FilesList.AddTail(m_Finder.GetFileName());
		
					m_Finding = m_Finder.FindNextFile();
					}
				}
			
			// Handle The Last File...
			Extention.Format("%s", FileExtentionOnly(m_Finder.GetFileName()));
			Extention.MakeUpper(); // Just In Case (Sensitive)...
		
			if(IsWantedExtention(Extention)) m_FilesList.AddTail(m_Finder.GetFileName());
		
			m_Finder.Close();
		
			// Get First Object On The List
			// Do Not Use pApp->m_lpCmdLine Coz It Will Not Get Updated When OnFileOpen...
			m_FilesListPosition = m_FilesList.GetHeadPosition();
			m_FilesListPos = 1; // Coz We Are On The First Object On The List...
			m_FilesListCount = m_FilesList.GetCount();
		
			CString Clicked; // Make Sure We Count Spaces And UNICode...
			Clicked.Format("%s", m_FilePathName);
		
			// If File Was Clicked - Begin List Count From This File
			if(Clicked.GetLength() > 0)
				{
				// Take Out Path Info...(Leave Only FileName)
				Clicked.Format("%s", FileNameOnly(Clicked));
		
				// Check If We Talking About a Wanted Extention
				Extention.Format("%s", FileExtentionOnly(Clicked));
				Extention.MakeUpper(); // Just In Case (Sensitive)...
		
				// Check If It One Of These
				if(IsWantedExtention(Extention))
					{
					for(int I=1; I < m_FilesListCount; I++) // Coz Starting From 1
						{
						Extention.Format("%s", m_FilesList.GetAt(m_FilesListPosition));
		
						if(Clicked.CompareNoCase(Extention) == 0) break; // We Got It
		
						m_FilesList.GetNext(m_FilesListPosition); // Move On The List
						m_FilesListPos++;
						}
					}
				}*/
		


	/* DEBUG
	CString S;

	// Be Careful - Can READ List Objects If Not Exists
	if(m_FilesListCount > 0)
		{
		S.Format("%d Picture Items On This Directory\t\nClicked = %d", m_FilesListCount, m_FilesListPos);
		AfxMessageBox(S);
		S.Format("First = \"%s\"", m_FilesList.GetAt(m_FilesListPosition));
		AfxMessageBox(S);
		}

	if(m_FilesListCount > 1)
		{
		S.Format("Last = \"%s\"", m_FilesList.GetTail());
		AfxMessageBox(S);
		}
	*/

	return(TRUE);
}

//-----------------------------------------------------------------------------
CString CPictureShowDoc::FileNameOnly(CString sFilePathName)
//=============================================================================
{
	if(sFilePathName.IsEmpty()) return("");
	CString sFileNameOnly;

	sFileNameOnly.Format("%s", sFilePathName);
	sFileNameOnly.MakeReverse(); // To Find The Last "\"
	int nLastSlash = sFileNameOnly.Find("\\", 0);
	sFileNameOnly.Format("%s", sFilePathName); // Get Original Again...
	sFileNameOnly.Delete(0, sFileNameOnly.GetLength() - nLastSlash); // Cut Out The Path

	return(sFileNameOnly);
}

//-----------------------------------------------------------------------------
CString CPictureShowDoc::FileExtentionOnly(CString sFilePathName)
//=============================================================================
{
	if(sFilePathName.IsEmpty()) return("");
	CString sFileExtentionOnly;

	sFileExtentionOnly.Format("%s", sFilePathName);
	sFileExtentionOnly.MakeReverse(); // To Find The Last "."
	int nLastDot = sFileExtentionOnly.Find(".", 0); // Get The Extention (After The Dot)
	sFileExtentionOnly.Format("%s", sFilePathName); // Get Original Again...
	sFileExtentionOnly.Delete(0, sFileExtentionOnly.GetLength() - nLastDot); // Cut The Rest

	return(sFileExtentionOnly);
}

//-----------------------------------------------------------------------------
BOOL CPictureShowDoc::IsWantedExtention(CString sExtention)
//=============================================================================
{
	if((sExtention == "BMP")||
	   (sExtention == "DIB")||
	   (sExtention == "EMF")||
	   (sExtention == "GIF")||
	   (sExtention == "ICO")||
	   (sExtention == "JPG")||
	   (sExtention == "WMF")) return(TRUE);

	return(FALSE);
}
