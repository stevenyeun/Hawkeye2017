#pragma once


//yeun
#include <vector>
using namespace std;

#define NORMALBLOCK		2048
#define IDX_TIMER_COLLECT_TIMEOUT		1
#define RECVTIMEOUT 50
/////////////////////////////////////
// CByteCollector

class CByteCollector : public CWnd
{
	DECLARE_DYNAMIC(CByteCollector)

public:
	CByteCollector();
	virtual ~CByteCollector();
private:
	BOOL m_bStartCollectByte;
	int m_iTimeoutCnt;
	vector<BYTE> m_VectorBuffer;

	BYTE m_byRecvDataStartPattern;
	BYTE m_byRecvDataFinishPattern;
	int m_iRecvDataSize;
	DWORD m_dwStartTicks;
protected:
	DECLARE_MESSAGE_MAP()
public:
#if 0
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
#endif
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void SetProtocolStyle(BYTE byStartPattern, BYTE byFinishPattern,
		int iDataSize, DWORD nRcvMaxLen = NORMALBLOCK, DWORD nSndMaxLen = NORMALBLOCK);

	BOOL CollectByte(LPBYTE lpData, int nLen, vector<BYTE>& vecPacket);
	inline void ResetBuffer();
};


