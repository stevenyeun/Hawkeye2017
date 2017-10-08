#pragma once

//  [3/29/2014 Yeun]
// 지도 상에서 그린정보를 저장하기 위해 정의됨

class CFileDrawingInfo
{
protected:
	CFile * m_pFile;
	CString	m_strFileName;
	CString	m_strDefaultPath;
public:
	CString GetFileName() const { return m_strFileName; }
	//void FileName(CString val) { m_strFileName = val; }
public:
	VEC2D_STYLISH_POINT LoadFileInfo( CString strFileName );	
	VEC2D_STYLISH_POINT LoadFileInfo();

	BOOL CreateNewFile();
	void AddVectorInfo( VEC_STYLISH_POINT veccamtotargetpos );
	
protected:
		
public:
	CFileDrawingInfo( CString strDefaultPath );
	~CFileDrawingInfo(void);
	
};
