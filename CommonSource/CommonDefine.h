#pragma once
#ifndef COMMONDEFINE_H
#define COMMONDEFINE_H

#define MAX_CHANNEL_NUM 5

#define TIMER_POWERON 1
#define TIMER_POWERON_PERIOD 5000

#define TIMER_RADAR_USINGTIME 2
#define TIMER_RADAR_USINGTIME_PERIOD 1000
#define RADAR_USINGTIME_TIMEOUT 20//20√ 

typedef struct _IP_PORT
{
	_IP_PORT(void)
	{
		dwIPAddr = 0;
		uPort = 0;
	}
	DWORD dwIPAddr;
	UINT  uPort;
}IP_PORT;


typedef struct _PACKET_LENGTH
{
	IP_PORT srcIPPort;
	LPBYTE lpData;
	int nLen;
}PACKET_LENGTH;



#ifndef SAFE_DELETE
#define SAFE_DELETE(x)  { if (x) delete x; x = NULL; }
#endif

#endif