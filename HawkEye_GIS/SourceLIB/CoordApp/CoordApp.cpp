#include "StdAfx.h"
#include "CoordApp.h"

#define PI 3.14159265358979
#include <math.h>
CCoordApp::CCoordApp(void)
{
}

CCoordApp::~CCoordApp(void)
{
}
void CCoordApp::CamInfoToTargetInfo(
						 double dLatCam, double dLongCam, float fPan, WORD wDistance,
						 double &dLatTarget, double &dLongTarget
						 )
{	
	double dOutLon, dOutLat;

	//카메라위치(kWgs84, kGeographic) => 카메라위치(kBessel1984, kTmMid)
	//타원체 선택
	SetSrcType((GeoEllips)kWgs84, (GeoSystem)kGeographic);//입력좌표
	//좌표 계 선택
	SetDstType((GeoEllips)kBessel1984, (GeoSystem)kTmMid);//출력좌표
	
	// Display Result
	// 입력 좌표계 : kGeographic -> 출력 좌표계 : kTmMid
	Conv(dLongCam, dLatCam, dOutLon, dOutLat);

	//팬값구하기
	double dRadianPan = (fPan * PI) / 180;//<<<-----------------각도를 라디안으로 변환.

	double dX = wDistance*sin(dRadianPan);//<<--------------------------한변의 길이 구함.
	double dY = wDistance*cos(dRadianPan);//<<--------------------------또다른 한변의 길이 구함.

	double dTargetX = dOutLon + dX;//<<---------------------현위치에서 표적 위치 ADD
	double dTargetY = dOutLat + dY;


	//계산된 표적좌표를 다시 경위도(Deg)로 변환
	//표적위치(kBessel1984, kWgs84) => 카메라위치(kGeographic, kTmMid)
	//타원체 선택
	SetSrcType((GeoEllips)kBessel1984, (GeoSystem)kTmMid);//입력좌표
	//좌표 계 선택
	SetDstType((GeoEllips)kWgs84, (GeoSystem)kGeographic);//출력좌표
	// 우선 경위도로 변환
	// Display Result
	// 입력 좌표계 : kTmMid -> 출력 좌표계 : kGeographic
	Conv(dTargetX, dTargetY, dLongTarget, dLatTarget);
}

void CCoordApp::CamInfoToTargetInfo(
									double dTmCamX, double dTmCamY, float fPan, int iDistance,
									double &dTmTargetX, double &dTmTargetY
									)
{	
		//팬값구하기
	double dRadianPan = (fPan * PI) / 180;//<<<-----------------각도를 라디안으로 변환.

	double dX = iDistance*sin(dRadianPan);//<<--------------------------한변의 길이 구함.
	double dY = iDistance*cos(dRadianPan);//<<--------------------------또다른 한변의 길이 구함.

	dTmTargetX = dTmCamX + dX;//<<---------------------현위치에서 표적 위치 ADD
	dTmTargetY = dTmCamY + dY;
}


/*
double CCoordApp::GetDistance(double dLat1, double dLong1, double dLat2, double dLong2)
{
	double dX1=0, dY1=0, dX2=0, dY2=0;

	//카메라위치(kWgs84, kGeographic) => 카메라위치(kBessel1984, kTmMid)
	//타원체 선택
	SetSrcType((GeoEllips)kWgs84, (GeoSystem)kGeographic);//입력좌표
	//좌표 계 선택
	SetDstType((GeoEllips)kBessel1984, (GeoSystem)kTmMid);//출력좌표

	// Display Result
	// 입력 좌표계 : kGeographic -> 출력 좌표계 : kTmMid
	Conv(dLong1, dLat1, dX1, dY1);

	Conv(dLong2, dLat2, dX2, dY2);

	
	double dCalcX=0, dCalcY=0;

	dCalcX  = dX1 - dX2;
	dCalcY  = dY1 - dY2;

	return sqrt((dCalcX * dCalcX)+(dCalcY * dCalcY));
}
*/
int CCoordApp::GetDistance(int iPixelX1, int iPixelY1, int iPixelX2, int iPixelY2)
{
	double dCalcX=0, dCalcY=0;

	dCalcX  = iPixelX1 - iPixelX2;
	dCalcY  = iPixelY1 - iPixelY2;

	return (int)sqrt((dCalcX * dCalcX)+(dCalcY * dCalcY));
}
double CCoordApp::GetDistance(double dTmX1, double dTmY1, double dTmX2, double dTmY2)
{
	double dCalcX=0, dCalcY=0;

	dCalcX  = dTmX1 - dTmX2;
	dCalcY  = dTmY1 - dTmY2;

	return sqrt((dCalcX * dCalcX)+(dCalcY * dCalcY));
}
double CCoordApp::DMS2Deg(int iDeg, int iMin, double Sec)
{
	//DMS to DEG
	double dDeg	= (double)iDeg + iMin/60.0 + Sec/3600.0;
	return dDeg;	

	//dCamLong	= (double)atoi(strCamLong.Mid(2, 3)) + atoi(strCamLong.Mid(6, 2))/60.0 + atof(strCamLong.Mid( 9, 5))/3600.0;
	//dCamLat		= (double)atoi(strCamLat.Mid(2, 2)) + atoi(strCamLat.Mid(5, 2))/60.0 + atof(strCamLat.Mid(8, 5))/3600.0;
}


void CCoordApp::Deg2Tm(double dLat, double dLong, double &dTmX, double &dTmY)
{
	//카메라위치(kWgs84, kGeographic) => 카메라위치(kBessel1984, kTmMid)
	//타원체 선택
	SetSrcType((GeoEllips)kWgs84, (GeoSystem)kGeographic);//입력좌표
	//좌표 계 선택
	SetDstType((GeoEllips)kBessel1984, (GeoSystem)kTmMid);//출력좌표

	// Display Result
	// 입력 좌표계 : kGeographic -> 출력 좌표계 : kTmMid
	Conv(dLong, dLat, dTmX, dTmY);
}
void CCoordApp::Tm2DMS(double x, double y,
			int &iLatDeg, int &iLatMin, double &dLatSec,
			int &iLongDeg, int &iLongMin, double &dLongSec
			)
{
	//계산된 표적좌표를 다시 경위도(Deg)로 변환
	//표적위치(kBessel1984, kWgs84) => 카메라위치(kGeographic, kTmMid)
	//타원체 선택
	SetSrcType((GeoEllips)kBessel1984, (GeoSystem)kTmMid);//입력좌표
	//좌표 계 선택
	SetDstType((GeoEllips)kWgs84, (GeoSystem)kGeographic);//출력좌표
	// 우선 경위도로 변환
	// Display Result
	// 입력 좌표계 : kTmMid -> 출력 좌표계 : kGeographic
	double dLat=0, dLong=0;
	Conv(x, y, dLong, dLat);

	D2Dms( dLat, iLatDeg, iLatMin, dLatSec );
	D2Dms( dLong, iLongDeg, iLongMin, dLongSec );
}

void CCoordApp::TwoLatLongToAzimuthAndDistance(
	BYTE byPoint1LatDeg, BYTE byPoint1LatMin, BYTE byPoint1LatSec, BYTE byPoint1LatSecFrac,
	BYTE byPoint1LongDeg, BYTE byPoint1LongMin, BYTE byPoint1LongSec, BYTE byPoint1LongSecFrac,
	BYTE byPoint2LatDeg, BYTE byPoint2LatMin, BYTE byPoint2LatSec, BYTE byPoint2LatSecFrac,
	BYTE byPoint2LongDeg, BYTE byPoint2LongMin, BYTE byPoint2LongSec, BYTE byPoint2LongSecFrac,
	double& dAzimuth, unsigned int& uDistance
)
{

	double dCamLat, dCamLong;
	double dTargetLat, dTargetLong;

	ByteCoordToDegCoord(byPoint1LatDeg, byPoint1LatMin, byPoint1LatSec, byPoint1LatSecFrac,
		byPoint1LongDeg, byPoint1LongMin, byPoint1LongSec, byPoint1LongSecFrac,
		dCamLat, dCamLong);

	ByteCoordToDegCoord(byPoint2LatDeg, byPoint2LatMin, byPoint2LatSec, byPoint2LatSecFrac,
		byPoint2LongDeg, byPoint2LongMin, byPoint2LongSec, byPoint2LongSecFrac,
		dTargetLat, dTargetLong);

	//x is long, y is lat
	double dCamXmeter, dCamYmeter;
	double dTargetXmeter, dTargetYmeter;

	AngleToGRS80(dCamLat, dCamLong, dCamXmeter, dCamYmeter);
	AngleToGRS80(dTargetLat, dTargetLong, dTargetXmeter, dTargetYmeter);

	//미터법으로 거리와 각도 계산.
	double dDTPX = dTargetXmeter - dCamXmeter;
	double dDTPY = dTargetYmeter - dCamYmeter;
	double dRange = sqrt((dDTPX*dDTPX) + (dDTPY*dDTPY));

	double Hbias;
	Hbias = (acos(dDTPY / dRange))*57.29578;
	if (dRange == 0)
		Hbias = 0;
	if (dDTPX < 0)//음수면
	{
		Hbias = Hbias * -1;
	}

	double dAngle = Hbias;
	if (dAngle < 0)
		dAngle = dAngle + 360;

	dAzimuth = dAngle;
	uDistance = (unsigned int)dRange;
}
void CCoordApp::AngleToGRS80(double dAngleLat, double dAngleLong, double &dGRS80X, double &dGRS80Y)
{
	//카메라위치(kWgs84, kGeographic) => 카메라위치(kBessel1984, kTmMid)
	//타원체 선택
	SetSrcType((GeoEllips)kWgs84, (GeoSystem)kGeographic);//입력좌표
														  //좌표 계 선택
	SetDstType((GeoEllips)kBessel1984, (GeoSystem)kTmMid);//출력좌표

														  // Display Result
														  // 입력 좌표계 : kGeographic -> 출력 좌표계 : kTmMid
	Conv(dAngleLong, dAngleLat, dGRS80X, dGRS80Y);
}
void CCoordApp::ByteCoordToDegCoord(
	byte byLatDeg, byte byLatMin, byte byLatSec, byte byLatSecFrac,
	byte byLongDeg, byte byLongMin, byte byLongSec, byte byLongSecFrac,
	double &dLat, double &dLong
)
{
	double dLatSec = (int)byLatSec + ((int)byLatSecFrac / 100.0);
	dLat = (int)byLatDeg + ((int)byLatMin / 60.0) + (dLatSec / 3600);

	double dLongSec = (int)byLongSec + ((int)byLongSecFrac / 100.0);
	dLong = (int)byLongDeg + ((int)byLongMin / 60.0) + (dLongSec / 3600);

}

double CCoordApp::PanDecToOffsetCalc(double dDec, double dOffsetDec)
{
	double dCalcDec = dDec + dOffsetDec;

	if (dCalcDec < 0)//음수일경우
	{
		if (dOffsetDec < 0)
		{
			dCalcDec = 360 + dCalcDec;
		}
		else if (dOffsetDec > 0)
		{
			dCalcDec = 360 - dCalcDec;
		}

	}
	else if (dCalcDec > 360)//양수
	{
		dCalcDec = dCalcDec - 360;
	}

	return dCalcDec;

}
