// Scaler.cpp: implementation of the Scaler class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Scaler.h"
#include <math.h>


Scaler::Scaler()
{
	m_byInitRefPointInit = 0x00;
}

void Scaler::WorldToDevice(double mx, double my, double *sx, double *sy)
{
	ASSERT(FALSE);
	double m_lfnowXRatio = (mxMax-mxMin) / (sxMax-sxMin) ;  // X��ô
	double m_lfnowYRatio = (myMax-myMin) / (syMax-syMin) ;  // Y��ô

	// ��Ⱦ�� ����
	if(m_lfnowXRatio > m_lfnowYRatio)
		nowRatio  =  m_lfnowXRatio;
	else
		nowRatio  =  m_lfnowYRatio;

	// �߽����� ���������� ����
	mox = (mxMax+mxMin) /2;
	moy = (myMax+myMin) /2;
	sox = (sxMax+sxMin) /2;
	soy = (syMax+syMin) /2;

	*sx=(mx-mox)/nowRatio+sox;
	*sy=(moy-my)/nowRatio+soy;
}
void Scaler::WorldToDevice(double mx, double my, int &sx, int &sy)
{
	//���� ȭ�� �ȼ� ����Ʈ�� ���� ��ǥ�� ��ȯ
	//(mxMax - mxMin) : m_rcMapPixel.Width() = (mx - mxMin) : X
	int iPixelX = m_rcMapPixel.Width() * (mx - mxMin) / (mxMax - mxMin);
	sx = iPixelX;

	//���� ȭ�� �ȼ� ����Ʈ�� ���� ��ǥ�� ��ȯ
	//(myMax - myMin) : m_rcMapPixel.Height() = (myMax - my) : X
	//6628 : 11700 = 3476 : x
	int iPixelY = m_rcMapPixel.Height() * (myMax - my) / (myMax - myMin);
	sy = iPixelY;
}

void Scaler::DeviceToWorld(double sx, double sy, double *mx, double *my)
{
	
#if 0
	double m_lfnowXRatio = (mxMax-mxMin) / (sxMax-sxMin) ; // X��ô
	double m_lfnowYRatio = (myMax-myMin) / (syMax-syMin) ; // Y��ô

	// ��Ⱦ�� ����
	if(m_lfnowXRatio > m_lfnowYRatio)
		nowRatio  =  m_lfnowXRatio;
	else
		nowRatio  =  m_lfnowYRatio;


	// �߽����� ���������� ����
	mox = (mxMax+mxMin) /2;
	moy = (myMax+myMin) /2;
	sox = (sxMax+sxMin) /2;
	soy = (syMax+syMin) /2;


	*mx = mox + (sx - sox) * nowRatio;
	*my = moy - (sy - soy) *  nowRatio;
#else

	//���� ȭ�� �ȼ� ����Ʈ�� ���� ��ǥ�� ��ȯ
	//m_rcMapPixel.Width() : (mxMax - mxMin) = sx : X
	double dTmX = (mxMax - mxMin) * sx / m_rcMapPixel.Width();
	*mx = mxMin + dTmX;

	//���� ȭ�� �ȼ� ����Ʈ�� ���� ��ǥ�� ��ȯ
	//m_rcMapPixel.Height() : (myMax - myMin) = sy : X
	double dTmY = (myMax - myMin) * sy / m_rcMapPixel.Height();
	*my = myMax - dTmY;	
#endif
}
void Scaler::SetScrRect(CRect rc)
{
	sxMin = rc.left;
	syMin = rc.top;
	sxMax = rc.right;
	syMax = rc.bottom;

	// ȭ���� ���� 
	sox = (sxMax + sxMin) / 2;
	soy = (syMax + syMin) / 2;	
}
void Scaler::SetRectMapTm(double dTmMinX, double dTmMaxX, double dTmMinY, double dTmMaxY)
{
	mxMin = dTmMinX;
	myMin = dTmMinY;
	mxMax = dTmMaxX;
	myMax = dTmMaxY;
	mox = (mxMax + mxMin) / 2;
	moy = (myMax + myMin) / 2;
}
void Scaler::SetRectMapPixel(CRect rc)
{
	m_rcMapPixel = rc;
	SetScrRect(m_rcMapPixel);//��ũ��ȭ�������
}
void Scaler::SetRefPoint(UINT uNum, double dRefPointLat, double dRefPointLong, int iRefPointPixelX, int iRefPointPixelY)
{
	switch (uNum)
	{
	case 1:
		{
			Deg2Tm( dRefPointLat, dRefPointLong, m_dRefPointTmX1, m_dRefPointTmY1);			

			CString strText;
			strText.Format(_T("1pointX : %lf, 1pointY : %lf\r\n"),
				m_dRefPointTmX1,
				m_dRefPointTmY1);
			TRACE(strText);

			m_iRefPointPixelX1	= iRefPointPixelX;
			m_iRefPointPixelY1	= iRefPointPixelY;

			//0000 0000
			//0000 0001 or
			m_byInitRefPointInit = m_byInitRefPointInit | 0x01;
		}
		break;
	case 2:
		{			
			Deg2Tm( dRefPointLat, dRefPointLong, m_dRefPointTmX2, m_dRefPointTmY2);	

			CString strText;
			strText.Format(_T("2pointX : %lf, 2pointY : %lf\r\n"),
				m_dRefPointTmX2,
				m_dRefPointTmY2);
			TRACE(strText);

			m_iRefPointPixelX2	= iRefPointPixelX;
			m_iRefPointPixelY2	= iRefPointPixelY;

			//0000 0000
			//0000 0010 or
			m_byInitRefPointInit = m_byInitRefPointInit | 0x02;
		}	
		break;
	default:
		ASSERT(FALSE);
	}

	//0000 0011
	//0000 0011 and

	//0000 0001
	//0000 0011 and
	//0000 0001
			 

	if((m_byInitRefPointInit & 0x03) == 0x03)
	{
		//1���� 2���� ������ �Ÿ� ���ϱ�
		//���� ���� ���̸� ���ϱ� ���ؼ� Y�� ����
		double dTmXBetween1and2 = GetDistance(m_dRefPointTmX1, m_dRefPointTmY1, m_dRefPointTmX2, m_dRefPointTmY1);																								 
		int iPixelXBetween1and2	= GetDistance(m_iRefPointPixelX1, m_iRefPointPixelY1, m_iRefPointPixelX2, m_iRefPointPixelY1 );

		//1���� 2���� ������ �Ÿ� ���ϱ�
		//���� ���� ���̸� ���ϱ� ���ؼ� X�� ����
		double dTmYBetween1and2 = GetDistance(m_dRefPointTmX1, m_dRefPointTmY1, m_dRefPointTmX1, m_dRefPointTmY2);																								 
		int iPixelYBetween1and2	= GetDistance(m_iRefPointPixelX1, m_iRefPointPixelY1, m_iRefPointPixelX1, m_iRefPointPixelY2 );

/*		
		//���� X�� ��ǥ ���� ���ϱ�
		//iPixelTwoPointDistance : dTmTwoPointDistance = (m_rcMapPixel.left - m_rcMapPixel.right) : x
		
		int iTmSizeX = dTmTwoPointDistance * (m_rcMapPixel.right - m_rcMapPixel.left) / iPixelTwoPointDistance;
		int iTmSizeY = dTmTwoPointDistance * (m_rcMapPixel.bottom - m_rcMapPixel.top) / iPixelTwoPointDistance;
*/

		
		//left ���� 1���� ���� �Ÿ� ���ϱ�
		//iPixelXBetween1and2 : dTmXBetween1and2 = m_iRefPointPixelX1 : x		 
		double dTmBetweenLeftAnd1PointX = (dTmXBetween1and2 *  m_iRefPointPixelX1 / iPixelXBetween1and2);
		//Left ���� ���ϱ�
		double dTmMinX = m_dRefPointTmX1 - dTmBetweenLeftAnd1PointX;

		//Right ���� 1���� ���� �Ÿ� ���ϱ�
		//iPixelXBetween1and2 : dTmXBetween1and2 = (m_rcMapPixel.right - m_iRefPointPixelX1) : x
		double dTmBetweenRightAnd1PointX = dTmXBetween1and2 * (m_rcMapPixel.right - m_iRefPointPixelX1) / iPixelXBetween1and2;
		//Right ���� ���ϱ�
		double dTmMaxX = m_dRefPointTmX1 + dTmBetweenRightAnd1PointX;


		//Top ���� 1���� ���� �Ÿ� ���ϱ�
		//iPixelYBetween1and2 : dTmYBetween1and2 = m_iRefPointPixelY1 : x
		double dTmBetweenTopAnd1PointY = (dTmYBetween1and2 * m_iRefPointPixelY1) / iPixelYBetween1and2;
		//Top ���� ���ϱ�
		double dTmMaxY = m_dRefPointTmY1 + dTmBetweenTopAnd1PointY;


		//Bottom ���� 1���� ���� �Ÿ� ���ϱ�
		//iPixelYBetween1and2 : dTmYBetween1and2 = (m_rcMapPixel.bottom - m_iRefPointPixelY1) : x
		double dTmBetweenBottomAnd1PointY = dTmYBetween1and2 * (m_rcMapPixel.bottom - m_iRefPointPixelY1) / iPixelYBetween1and2;
		//Bottom ���� ���ϱ�
		double dTmMinY = m_dRefPointTmY1 - dTmBetweenBottomAnd1PointY;

		SetRectMapTm(dTmMinX, dTmMaxX, dTmMinY, dTmMaxY);


		CString strText;
		double dTmX=0.0, dTmY=0.0;

		int iDegLatD, iDegLatM;
		double iDegLatS;
		int iDegLongD, iDegLongM;
		double iDegLongS;

		Tm2DMS( dTmMinX, dTmMinY,
			iDegLatD, iDegLatM, iDegLatS,
			iDegLongD, iDegLongM, iDegLongS);

		strText.Format(_T("Bottom : %d��%d��%05.02lf�� Left : %d��%d��%05.02lf��\r\n"),
			iDegLatD, iDegLatM, iDegLatS,
			iDegLongD, iDegLongM, iDegLongS);
		TRACE(strText);

		strText.Format(_T("Bottom : %lf Left : %lf\r\n"),
			dTmMinY,
			dTmMinX);
		TRACE(strText);		

		Tm2DMS( dTmMaxX, dTmMaxY,
			iDegLatD, iDegLatM, iDegLatS,
			iDegLongD, iDegLongM, iDegLongS);

		strText.Format(_T("Top : %d��%d��%05.02lf�� Right : %d��%d��%05.02lf��\r\n"),
			iDegLatD, iDegLatM, iDegLatS,
			iDegLongD, iDegLongM, iDegLongS);
		TRACE(strText);

		strText.Format(_T("Top : %lf Right : %lf\r\n"),
			dTmMaxY,
			dTmMaxX);
		TRACE(strText);	

/*
		double mox , moy ;					// ���� ������
		double mxMin, myMin, mxMax, myMax;	// ���� Extent
*/		
	}
}