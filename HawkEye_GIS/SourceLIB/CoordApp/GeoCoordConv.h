// GeoCoordConv.h: interface for the CGeoCoordConv class.
//
//////////////////////////////////////////////////////////////////////
// �� ���̺귯���� �Ż������ ����� ������ �ҽ��� �������� 
// Ÿ�� �ý����� �庴���� C++�� �ٲٸ鼭 Ŭ����ȭ �� ���Դϴ�.

// ������ �������� �����Դϴ�.
// ���α׷��� �̱� USGS���� ���� GCTP(General Cartographic Transformation Program)
// �� ���� �����Ͽ� ���� ���Դϴ�.
// C�� �ۼ��Ǿ� �ִ� GCTP ���α׷��� ftp://edcftp.cr.usgs.gov/pub/software/gctpc/
// �� ������ ���ø� ã���� �� �ֽ��ϴ�.
// Ÿ��ü ��ȯ ��ƾ�� �̱� NIMA�� ��� å���� �����Ͽ� ���� �ۼ��Ͽ����ϴ�.
// ��ȯ���� Molodensky Datum ��ȯ���� ����Ͽ����ϴ�.
//
  
// �� �ҽ��� ����� ������ �ƴ϶�� �����Ӱ� ����, �����Ͻ� �� �ֽ��ϴ�.
// �ٸ� ����� �������� ����� ��쿡�� �ݵ�� ��ó�� ����ϼž� �մϴ�.


#if !defined(AFX_GEOCOORDCONV_H__0111FA14_9C35_4356_A57F_4516F949DC5A__INCLUDED_)
#define AFX_GEOCOORDCONV_H__0111FA14_9C35_4356_A57F_4516F949DC5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define D2R(degree) (degree * PI / 180.0)
#define R2D(radian) (radian * 180.0 / PI)

enum GeoEllips {kBessel1984 = 0, kWgs84 = 1};
enum GeoSystem {kGeographic = 0, kTmWest = 1, kTmMid = 2, kTmEast = 3, kKatec = 4, kUtm52 = 5, kUtm51 = 6};

class CGeoCoordConv  
{
public:
	CGeoCoordConv(
		GeoEllips eSrcEllips = kBessel1984, 
		GeoSystem eSrcSystem = kGeographic,
		GeoEllips eDstEllips = kBessel1984, 
		GeoSystem eDstSystem = kTmMid
		);

	// Set Internal Values
	void SetSrcType(GeoEllips eEllips, GeoSystem eSystem);
	void SetDstType(GeoEllips eEllips, GeoSystem eSystem);

	// Main Convert Function
	void Conv(double dInX, double dInY, double& dOutX, double& dOutY);
	// Global Utility Function
	static void D2Dms(double dInDecimalDegree, int& iOutDegree, int& iOutMinute, double& dOutSecond);

protected:
	void DatumTrans(double dInLon, double dInLat, double& dOutLon, double& dOutLat);
	void Geo2Tm(double lon, double lat, double& x, double& y);
	void Tm2Geo(double x, double y, double& lon, double& lat);

	// Ellips/System Type
	GeoEllips m_eSrcEllips;
	GeoSystem m_eSrcSystem;
	GeoEllips m_eDstEllips;
	GeoSystem m_eDstSystem;

	// Ellips Factor List
	double m_arMajor[2];
	double m_arMinor[2];

	// System Factor List 
	double m_arScaleFactor[7];
	double m_arLonCenter[7];
	double m_arLatCenter[7];
	double m_arFalseNorthing[7];
	double m_arFalseEasting[7];
	
private:
	void InitDatumVar();
	double asinz(double value);
	double e0fn(double es);
	double e1fn(double es);
	double e2fn(double es);
	double e3fn(double es);
	double e4fn(double es);
	double mlfn(double e0, double e1, double e2, double e3, double phi);

	// Internal Value for Tm2Geo
	double m_dSrcE0, m_dSrcE1, m_dSrcE2, m_dSrcE3;
	double m_dSrcE, m_dSrcEs, m_dSrcEsp;
	double m_dSrcMl0, m_dSrcInd;

	// Internal Value for Geo2Tm
	double m_dDstE0, m_dDstE1, m_dDstE2, m_dDstE3;
	double m_dDstE, m_dDstEs, m_dDstEsp;
	double m_dDstMl0, m_dDstInd;

	// Internal Value for DatumTrans
	double m_dTemp;
	double m_dEsTemp;
	int m_iDeltaX;
	int m_iDeltaY;
	int m_iDeltaZ;
	double m_dDeltaA, m_dDeltaF;

};

#endif // !defined(AFX_GEOCOORDCONV_H__0111FA14_9C35_4356_A57F_4516F949DC5A__INCLUDED_)
