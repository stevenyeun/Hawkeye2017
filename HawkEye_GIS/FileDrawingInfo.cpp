#include "StdAfx.h"
#include "FileDrawingInfo.h"





CFileDrawingInfo::CFileDrawingInfo( CString strDefaultPath )
{
	m_pFile=NULL;
	m_strDefaultPath = strDefaultPath;
}

CFileDrawingInfo::~CFileDrawingInfo(void)
{
	if( m_pFile != NULL )
	{
		m_pFile->Close();
		delete m_pFile;
	}
}


VEC2D_STYLISH_POINT CFileDrawingInfo::LoadFileInfo()
{
	TCHAR szFilters[]= _T("Drawing Files (*.DRW)|*.DRW|All Files (*.*)|*.*||");

/*
			CFileDialog fileDlg(TRUE, _T("DRW"), _T("*.DRW"),
				OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);*/
		

	CFileDialog fileDlg(TRUE, _T("DRW"), m_strDefaultPath,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

	// Display the file dialog. When user clicks OK, fileDlg.DoModal() 
	// returns IDOK.
	

	

	if(fileDlg.DoModal() == IDOK)
	{
		CString pathName = fileDlg.GetPathName();

		// Implement opening and reading file in here.

		//Change the window's title to the opened file's title.
		CString fileName = fileDlg.GetPathName();		
		
		if( m_pFile != NULL )
			m_pFile->Close();

		return LoadFileInfo( fileName );
	}
	
	//비어있는 이차원벡터를 리턴 한다.
	VEC2D_STYLISH_POINT vec2d;
	return vec2d;
}
VEC2D_STYLISH_POINT CFileDrawingInfo::LoadFileInfo( CString strFileName )
{
	SAFE_DELETE( m_pFile );
	m_pFile = new CFile( strFileName, CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate | CFile::typeBinary );


	UINT uLen = (UINT)m_pFile->GetLength();//파일의 길이를 얻어와
	UINT ullNumOfEle = uLen / sizeof(VEC_STYLISH_POINT);//총 몇개의 구조체가 저장되었는지 계산


	int iRowCnt=-1;
	VEC2D_STYLISH_POINT vec2d;//이차원벡터를 생성한다.
	VEC_STYLISH_POINT vec;
	for ( UINT i=0; i<ullNumOfEle; i++ )
	{
		STYLISH_POINT temp;
		m_pFile->Read( &temp, sizeof(STYLISH_POINT) );//구조체 1개 만큼 읽어온다.


		vec.push_back( temp );//한 행의 1 저장

		if( temp.bRowEnd == TRUE )//
		{
			vec2d.push_back( vec );//한 행 저장
			vec.clear();
		}
	}
	
	m_strFileName = strFileName;

	return vec2d;
}
void CFileDrawingInfo::AddVectorInfo( VEC_STYLISH_POINT vec )
{		
	//char pbufWrite[100];
	int iNumOfEle = vec.size();


	STYLISH_POINT temp;
	for ( int i=0; i<iNumOfEle; i++ )
	{
		temp = vec[i];
		m_pFile->Write ( &temp, sizeof(temp) );  
	}
	
}

BOOL CFileDrawingInfo::CreateNewFile()
{
	TCHAR szFilters[]= _T("Drawing Files (*.DRW)|*.DRW|All Files (*.*)|*.*||");


	/*CFileDialog fileDlg(FALSE, _T("DRW"), _T("*.DRW"),
	OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
	*/
	CFileDialog fileDlg(FALSE, _T("DRW"), m_strDefaultPath,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

	// Display the file dialog. When user clicks OK, fileDlg.DoModal() 
	// returns IDOK.
	if(fileDlg.DoModal() == IDOK)
	{
		//CString pathName = fileDlg.GetPathName();

		// Implement opening and reading file in here.

		//Change the window's title to the opened file's title.
		CString fileName = fileDlg.GetPathName();
		m_strFileName = fileName;
		SAFE_DELETE( m_pFile );
		m_pFile = new CFile( fileName, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate | CFile::typeBinary );
		return TRUE;
	}
	else
		return FALSE;
}