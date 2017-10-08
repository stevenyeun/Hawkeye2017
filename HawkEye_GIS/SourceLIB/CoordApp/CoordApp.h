#pragma once
#include "GeoCoordConv.h"

class CCoordApp :
	public CGeoCoordConv
{
public:
	//카메라정보(Lat Long Deg(10진법), pan, distance) => 표적좌표(Lat Long Deg)로 변환
	void CamInfoToTargetInfo(
		double dLatCam, double dLongCam, float fPan, WORD wDistance,
		double &dLatTarget, double &dLongTarget
		);

	//카메라 정보 tm => 표적좌표 tm
	void CamInfoToTargetInfo(
		double dTmCamX, double dTmCamY, float fPan, int iDistance,
		double &dTmTargetX, double &dTmTargetY
		);

	//두개의 좌표로 방위각과 거리구하기
	void TwoLatLongToAzimuthAndDistance(
		BYTE byPoint1LatDeg, BYTE byPoint1LatMin, BYTE byPoint1LatSec, BYTE byPoint1LatSecFrac,
		BYTE byPoint1LongDeg, BYTE byPoint1LongMin, BYTE byPoint1LongSec, BYTE byPoint1LongSecFrac,
		BYTE byPoint2LatDeg, BYTE byPoint2LatMin, BYTE byPoint2LatSec, BYTE byPoint2LatSecFrac,
		BYTE byPoint2LongDeg, BYTE byPoint2LongMin, BYTE byPoint2LongSec, BYTE byPoint2LongSecFrac,
		double& dAzimuth, unsigned int& uDistance
	);
	
	//double GetDistance(double dLat1, double dLong1, double dLat2, double dLong2);
	static double GetDistance(double dTmX1, double dTmY1, double dTmX2, double dTmY2);

	int GetDistance(int iPixelX1, int iPixelY1, int iPixelX2, int iPixelY2);

	double DMS2Deg(int iDeg, int iMin, double Sec);	
	void Deg2Tm(double dLat, double dLong, double &dTmX, double &dTmY);
	void Tm2DMS(double x, double y,
		int &iLatDeg, int &iLatMin, double &dLatSec,
		int &iLongDeg, int &iLongMin, double &dLongSec);

public:
	void AngleToGRS80(double dAngleLat, double dAngleLong, double &dGRS80X, double &dGRS80Y);
	void ByteCoordToDegCoord(
		byte byLatDeg, byte byLatMin, byte byLatSec, byte byLatSecFrac,
		byte byLongDeg, byte byLongMin, byte byLongSec, byte byLongSecFrac,
		double &dLat, double &dLong
	);

	static double PanDecToOffsetCalc(double dDec, double dOffsetDec);
	
			
public:
	CCoordApp(void);
	~CCoordApp(void);
};
