 // Scaler.h: interface for the Scaler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(SCALER_H)
#define SCALER_H

#include "../CoordApp/CoordApp.h"

class Scaler : public CCoordApp
{

public:
	Scaler();
	void DeviceToWorld(double sx, double sy, double *mx, double *my);
	void WorldToDevice(double mx, double my, double *sx, double *sy);
	void WorldToDevice(double mx, double my, int &sx, int &sy);

	void SetScrRect(CRect rc);	
	void SetRectMapTm(double dTmMinX, double dTmMaxX, double dTmMinY, double dTmMaxY);
	void SetRectMapPixel(CRect rc);
	void SetRefPoint(UINT uNum, double dLat, double dLong, int iRefPointPixelX, int iRefPointPixelY);
	//////////////////////////////
protected:
	
	//지도 이미지 rect
	CRect m_rcMapPixel;

	//픽셀좌표 => 실제좌표 계산을 위한 참조 포인트
	double m_dRefPointTmX1;
	double m_dRefPointTmY1;

	int m_iRefPointPixelX1;//Img abs pixel point
	int m_iRefPointPixelY1;

	
	
	double m_dRefPointTmX2;
	double m_dRefPointTmY2;
	int m_iRefPointPixelX2;
	int m_iRefPointPixelY2;
	BYTE m_byInitRefPointInit;
	//

	
	// 지도그리기 관련 멤버 
	double mox , moy ;					// 지도 기준점
	double mxMin, myMin, mxMax, myMax;	// 지도 Extent
	double sox , soy ;					// 화면 기준점
	double sxMin, syMin, sxMax, syMax;	// 화면 Extent

	// 캔버스 1단위당 실제길이 값 - 거리비(실제길이/캔버스길이)
	double nowRatio;		

};

#endif

