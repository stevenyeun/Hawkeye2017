// ByteCollector.cpp : 구현 파일입니다.
//

#include "stdafx.h"
//#include "Hawkeye_PTZClient_AuthServer.h"
#include "ByteCollector.h"


// CByteCollector

IMPLEMENT_DYNAMIC(CByteCollector, CWnd)

CByteCollector::CByteCollector()
{
	m_bStartCollectByte = FALSE;
	m_byRecvDataStartPattern = 0x00;
	m_byRecvDataFinishPattern = 0x00;
	m_iRecvDataSize = 0;
	m_iTimeoutCnt = 0;
}

CByteCollector::~CByteCollector()
{
}


BEGIN_MESSAGE_MAP(CByteCollector, CWnd)
END_MESSAGE_MAP()



// CByteCollector 메시지 처리기입니다.

#if 0//yeun
int CByteCollector::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	return 0;
}
#endif
BOOL CByteCollector::CollectByte(LPBYTE lpData, int nLen, vector<BYTE>& vecPacket)
{
	//	TRACE("======CollectByte() 진입======\r\n");
	if (m_iRecvDataSize == 0 && m_byRecvDataStartPattern == 0x00 && m_byRecvDataFinishPattern == 0x00)//들어오는순서대로 받기를 원할때
	{
		//리시브 윈도우로 전송
#if 0
		PACKET_LENGTH DataAndLen;
		DataAndLen.lpData = lpData;
		DataAndLen.iLen = iLen;
		m_pPacketSendRecvWnd->SendMessage(m_UWM_RECVPACKET_MSG, 0, (LPARAM)&DataAndLen);
#endif
		return FALSE;
	}


	for (int i = 0; i<nLen; i++)
	{
		//		TRACE("for loop Len=%d i=%d, data = %02X\r\n", iLen, i,lpData[i]);
		if (lpData[i] == m_byRecvDataStartPattern)//들어온 바이트가 HEADER인경우
		{
			m_bStartCollectByte = TRUE;//데이터를 모으기 시작하자.

			m_dwStartTicks = GetTickCount();
			//Timeout Check Start			
			//스레드로 타임아웃 처리 해야함 UINT_PTR ptr = SetTimer(1, 1, NULL);
			int a = 0;
		}
		if (m_bStartCollectByte == TRUE)
		{
			m_VectorBuffer.push_back(lpData[i]);//1byte씩 큐에 담는다.
												//TRACE("m_VectorBuffer.push_back()\r\n");

												//원하는 바이트 사이즈가 되었는지 체크
			if (m_iRecvDataSize != 0 && m_VectorBuffer.size() == m_iRecvDataSize)
			{
				if (m_VectorBuffer.front() == m_byRecvDataStartPattern)
				{
#if 0//yeun
					BYTE * pByPacket = new BYTE[m_iRecvDataSize];

					ZeroMemory(pByPacket, m_iRecvDataSize);
					copy(m_VectorBuffer.begin(), m_VectorBuffer.end(), pByPacket);


					PACKET_LENGTH DataAndLen;
					DataAndLen.lpData = pByPacket;
					DataAndLen.iLen = m_iRecvDataSize;


					//ParentWnd로 전송
					/*
					TRACE("RECV : %02X %02X %02X %02X %02X %02X %02X\r\n",
					DataAndLen.lpData[0], DataAndLen.lpData[1], DataAndLen.lpData[2],
					DataAndLen.lpData[3], DataAndLen.lpData[4], DataAndLen.lpData[5], DataAndLen.lpData[6]);
					*/
					m_pPacketSendRecvWnd->SendMessage(m_UWM_RECVPACKET_MSG, 0, (LPARAM)&DataAndLen);
#endif


					DWORD dwCurTickCnt = GetTickCount();
					DWORD dwElapsed = dwCurTickCnt - m_dwStartTicks;
					//TRACE( "======CollectByte() 완료되어 RECVWND 로 패킷을전송[ %dms ]======\r\n", dwElapsed);
				
					
					vecPacket = m_VectorBuffer;
					vecPacket.push_back(0x00);

					ResetBuffer();
#if 0
					if (pByPacket != NULL)
					{
						delete[]pByPacket;
						pByPacket = NULL;
					}
#endif
					return TRUE;
				}
				else if ((int)m_VectorBuffer.size() > m_iRecvDataSize)
				{
					TRACE("LEN = %d Overflow Error!!!!\r\n", m_VectorBuffer.size());
					ResetBuffer();
					
					return FALSE;
				}

				else//원하는 바이트 숫자인데 첫번째 바이트가 헤더가 아니면 처음부터 다시시작.
				{
					TRACE("LEN = %d Packet Error!!!!\r\n", m_VectorBuffer.size());
					ResetBuffer();

					return FALSE;
				}

			}
			//현재 들어온 바이트가 패킷의 끝인지 확인
			else if (m_iRecvDataSize == 0 && lpData[i] == m_byRecvDataFinishPattern)
			{
#if 0//yeun
				BYTE * pByPacket = new BYTE[1024];

				ZeroMemory(pByPacket, 1024);
				copy(m_VectorBuffer.begin(), m_VectorBuffer.end(), pByPacket);


				PACKET_LENGTH DataAndLen;
				DataAndLen.lpData = pByPacket;

				//  [3/14/2014 Yeun]
				//DataAndLen.iLen		= 1024;
				DataAndLen.nLen = m_VectorBuffer.size();//현재 들어온 패킷길이를 전송
#endif
				DWORD dwCurTickCnt = GetTickCount();
				DWORD dwElapsed = dwCurTickCnt - m_dwStartTicks;
				CString str;
#ifdef UNICODE
				//yeun str.Format(_T("======CollectByte() 완료 RECVWND 로 패킷을전송[ %dms ] ==> %s"), dwElapsed, Multi2Wide2((char*)pByPacket));
				TRACE(str);
#else
				str.Format(_T("======CollectByte() 완료 RECVWND 로 패킷을전송[ %dms ] ==> %s"), dwElapsed, ((char*)pByPacket));
#endif
				//yeun m_pPacketSendRecvWnd->SendMessage(m_UWM_RECVPACKET_MSG, 0, (LPARAM)&DataAndLen);
				vecPacket = m_VectorBuffer;
				vecPacket.push_back(0x00);
				ResetBuffer();

#if 0
				if (pByPacket != NULL)
				{
					delete[]pByPacket;
					pByPacket = NULL;
				}
#endif
				return TRUE;
			}
		}
	}
	if (m_iRecvDataSize == 0)
	{
		return FALSE;
	}

	//리시브되었으나 원하는 데이터가 아님
	//패킷이 깨져있을수도있음
	//리시브 윈도우로 전송
	TRACE("RECV : %02X %02X %02X %02X %02X %02X %02X\r\n",
		lpData[0], lpData[1], lpData[2],
		lpData[3], lpData[4], lpData[5], lpData[6]);

#if 0//yeun
	PACKET_LENGTH DataAndLen;
	DataAndLen.lpData = lpData;
	DataAndLen.iLen = iLen;
	m_pPacketSendRecvWnd->SendMessage(m_UWM_RECVPACKET_MSG, IDX_RECVPACKET_CANT_COLLECT_DATA, (LPARAM)&DataAndLen);
#endif

	return FALSE;
}
void CByteCollector::ResetBuffer()
{
	m_VectorBuffer.clear();
	m_bStartCollectByte = FALSE;
	//스레드로 처리해야함 KillTimer(1);
	m_iTimeoutCnt = 0;
}
void CByteCollector::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nIDEvent)
	{
	case IDX_TIMER_COLLECT_TIMEOUT:
	{
		m_iTimeoutCnt++;
		//			TRACE("Collect TimeOut Count = %d\r\n", m_iTimeoutCnt);			
		if (m_iTimeoutCnt >= RECVTIMEOUT)
			//			if(m_iTimeoutCnt >= 1000)
		{
			TRACE("Collect TimeOut!!!!\r\n");

			DWORD dwCurTickCnt = GetTickCount();
			DWORD dwElapsed = dwCurTickCnt - m_dwStartTicks;
			TRACE("Collect TimeOut Time = %dms\r\n", dwElapsed);
			ResetBuffer();
		}
	}
	break;
	}
	CWnd::OnTimer(nIDEvent);
}

void CByteCollector::SetProtocolStyle(BYTE byStartPattern, BYTE byFinishPattern, int iDataSize, DWORD nRcvMaxLen, DWORD nSndMaxLen)
{
	m_byRecvDataStartPattern = byStartPattern;
	m_byRecvDataFinishPattern = byFinishPattern;
	m_iRecvDataSize = iDataSize;
	DWORD m_dwStartTicks;
}

