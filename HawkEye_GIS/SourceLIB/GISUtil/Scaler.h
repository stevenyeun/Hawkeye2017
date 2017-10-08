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
	
	//���� �̹��� rect
	CRect m_rcMapPixel;

	//�ȼ���ǥ => ������ǥ ����� ���� ���� ����Ʈ
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

	
	// �����׸��� ���� ��� 
	double mox , moy ;					// ���� ������
	double mxMin, myMin, mxMax, myMax;	// ���� Extent
	double sox , soy ;					// ȭ�� ������
	double sxMin, syMin, sxMax, syMax;	// ȭ�� Extent

	// ĵ���� 1������ �������� �� - �Ÿ���(��������/ĵ��������)
	double nowRatio;		

};

#endif

