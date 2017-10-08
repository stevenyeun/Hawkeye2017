#pragma once

#include <U2SRProtoDef.h>
#include <U2SRProtoParser.h>
#include <ProtoFlirTau2.h>
typedef struct _CMD
{
	_CMD(void)
	{
		ZeroMemory(dArrParam, sizeof(DARR_PARAM));
		pVoid = NULL;
		iCmd = 0;
		iChIndex = 0;
		bQueue = FALSE;
		bEmergency = FALSE;
	}
	//CString strCmd;
	DARR_PARAM dArrParam;
	int iCmd;
	int iChIndex;
	void * pVoid;

	//  [4/12/2014 Yeun]
	BOOL bQueue;
	BOOL bEmergency;
	//
	//int iNumOfParam;
}CMD;

class CStandardCommandToProtocol;

const int MAX_FUNC_PTR_ARR = 500;
typedef int (CStandardCommandToProtocol::*FUNC_PTR_ARR[MAX_FUNC_PTR_ARR])(CMD, PBYTE);

class CStandardCommandToProtocol
{
public:
	CStandardCommandToProtocol();
	~CStandardCommandToProtocol();
public:
	int StdCmdToProtocolPacket(CMD cmd, PBYTE pByte);
public:
	void SetHighCamProto(int iProto);
	void SetThermCamProto(int iProto);
	void SetLrfProto(int iProto);
	void SetCh1X(CMD cmd, PBYTE pByte);//yeun20150129
private:
	CU2SRProtoParser m_protoU2srParser;

	//ProtoRr25 m_protoOpgal;//  [4/6/2014 Yeun]		
	int m_iProtoHighCam;
	int m_iProtoThermCam;
	int m_iProtoLrf;
	BYTE m_byBuffer[PROTO_BUFFER_SIZE];

	FUNC_PTR_ARR m_FuncPtrArr;
	///////////////////////////////////////
private:
	int ReqCurPanTiltPos1(CMD cmd, PBYTE pByte);
	int ReqCurPanTiltPos2(CMD cmd, PBYTE pByte);

	int MoveRight(CMD cmd, PBYTE pByte);
	int MoveLeft(CMD cmd, PBYTE pByte);
	int MoveUp(CMD cmd, PBYTE pByte);
	int MoveDown(CMD cmd, PBYTE pByte);
	int QuitLeft(CMD cmd, PBYTE pByte);
	int QuitRight(CMD cmd, PBYTE pByte);
	int QuitUp(CMD cmd, PBYTE pByte);
	int QuitDown(CMD cmd, PBYTE pByte);
	int SetPreset(CMD cmd, PBYTE pByte);
	int GetPreset(CMD cmd, PBYTE pByte);
	int LinkPreset(CMD cmd, PBYTE pByte);
	int SyncPreset(CMD cmd, PBYTE pByte);
	int MovePreset(CMD cmd, PBYTE pByte);
	int MovePanTiltHome(CMD cmd, PBYTE pByte);
	int ReqPanTiltHomeStatus(CMD cmd, PBYTE pByte);
	int ReqPanStatus(CMD cmd, PBYTE pByte);
	int ReqTiltStatus(CMD cmd, PBYTE pByte);
	int PowerOff(CMD cmd, PBYTE pByte);
	int PowerOn(CMD cmd, PBYTE pByte);
	int PresetTour(CMD cmd, PBYTE pByte);
	int PresetStop(CMD cmd, PBYTE pByte);
	int PanTiltInit(CMD cmd, PBYTE pByte);
	int ReqPowerStatus(CMD cmd, PBYTE pByte);
	int HighZoomTele(CMD cmd, PBYTE pByte);
	int HighZoomWide(CMD cmd, PBYTE pByte);
	int HighZoomStop(CMD cmd, PBYTE pByte);
	int HighFocusNear(CMD cmd, PBYTE pByte);
	int HighFocusFar(CMD cmd, PBYTE pByte);
	int HighFocusStop(CMD cmd, PBYTE pByte);
	int HighReqCurZFPos(CMD cmd, PBYTE pByte);
	int HighAutoFocus(CMD cmd, PBYTE pByte)/* [8/19/2014 Yeun] */;
	int HighLensFilter(CMD cmd, PBYTE pByte);//  [8/19/2014 Yeun] 
	int HighColorMode(CMD cmd, PBYTE pByte);//  [8/19/2014 Yeun] 
	int HighExtenderMode(CMD cmd, PBYTE pByte);//yeun 161230
	int HighIrisMode(CMD cmd, PBYTE pByte);//yeun170924
	int HighMenuOpen(CMD cmd, PBYTE pByte);
	int HighMenuEnter(CMD cmd, PBYTE pByte);
	int HighMenuLeft(CMD cmd, PBYTE pByte);
	int HighMenuRight(CMD cmd, PBYTE pByte);
	int HighMenuUp(CMD cmd, PBYTE pByte);
	int HighMenuDown(CMD cmd, PBYTE pByte);
	int HighSetZoomSpd(CMD cmd, PBYTE pByte);
	int HighSetFocusSpd(CMD cmd, PBYTE pByte);

	int LowZoomTele(CMD cmd, PBYTE pByte);
	int LowZoomWide(CMD cmd, PBYTE pByte);
	int LowZoomStop(CMD cmd, PBYTE pByte);
	int LowFocusNear(CMD cmd, PBYTE pByte);
	int LowFocusFar(CMD cmd, PBYTE pByte);
	int LowFocusStop(CMD cmd, PBYTE pByte);
	int LowAbsZoomMove(CMD cmd, PBYTE pByte);
	int LowMenuOpen(CMD cmd, PBYTE pByte);
	int LowMenuEnter(CMD cmd, PBYTE pByte);
	int LowMenuLeft(CMD cmd, PBYTE pByte);
	int LowMenuRight(CMD cmd, PBYTE pByte);
	int LowMenuUp(CMD cmd, PBYTE pByte);
	int LowMenuDown(CMD cmd, PBYTE pByte);

	int SetCh1Cam1(CMD cmd, PBYTE pByte);
	int SetCh1Cam2(CMD cmd, PBYTE pByte);
	int SetCh1Cam3(CMD cmd, PBYTE pByte);
	int SetCh2Cam1(CMD cmd, PBYTE pByte);
	int SetCh2Cam2(CMD cmd, PBYTE pByte);
	int SetCh2Cam3(CMD cmd, PBYTE pByte);

	int SetPanTiltSpd(CMD cmd, PBYTE pByte);
	int SetPanTiltPresetSpd(CMD cmd, PBYTE pByte);

	int ThermZoomTele(CMD cmd, PBYTE pByte);
	int ThermZoomWide(CMD cmd, PBYTE pByte);
	int ThermZoomStop(CMD cmd, PBYTE pByte);
	int ThermFocusNear(CMD cmd, PBYTE pByte);
	int ThermFocusFar(CMD cmd, PBYTE pByte);
	int ThermFocusStop(CMD cmd, PBYTE pByte);
	int ThermSetAutoFocus(CMD cmd, PBYTE pByte);
	int ThermReqDZoom(CMD cmd, PBYTE pByte);
	int ThermSetDZoom(CMD cmd, PBYTE pByte);
	int ThermSetPwr(CMD cmd, PBYTE pByte);
	int ThermGetPwr(CMD cmd, PBYTE pByte);
	int ThermSetWhiteHot(CMD cmd, PBYTE pByte);
	int ThermSetBlackHot(CMD cmd, PBYTE pByte);
	int ThermReqPolarity(CMD cmd, PBYTE pByte);
	int ThermSetDdeMode(CMD cmd, PBYTE pByte);
	int ThermSetDdeGain(CMD cmd, PBYTE pByte);
	int ThermSetDdeThreshold(CMD cmd, PBYTE pByte);
	int ThermSetBriAuto(CMD cmd, PBYTE pByte);
	int ThermSetConAuto(CMD cmd, PBYTE pByte);
	int ThermFocusNearFine(CMD cmd, PBYTE pByte);
	int ThermFocusFarFine(CMD cmd, PBYTE pByte);
	int ThermSetBri(CMD cmd, PBYTE pByte);
	int ThermSetCon(CMD cmd, PBYTE pByte);
	int ThermReqBri(CMD cmd, PBYTE pByte);
	int ThermReqCon(CMD cmd, PBYTE pByte);
	int ThermSetColor(CMD cmd, PBYTE pByte);
	int ThermAGCMode(CMD cmd, PBYTE pByte);


	int LrfReqDistance(CMD cmd, PBYTE pByte);
	int LrfReqStatus(CMD cmd, PBYTE pByte);
	int LrfReqRangeGate(CMD cmd, PBYTE pByte);

	int LrfPowerOn(CMD cmd, PBYTE pByte);
	int LrfPowerOff(CMD cmd, PBYTE pByte);
	int LrfMoveRight(CMD cmd, PBYTE pByte);
	int LrfMoveLeft(CMD cmd, PBYTE pByte);
	int LrfMoveUp(CMD cmd, PBYTE pByte);
	int LrfMoveDown(CMD cmd, PBYTE pByte);
	int LrfMoveStop(CMD cmd, PBYTE pByte);

	int ReqGPS(CMD cmd, PBYTE pByte);
	int ReqMainBoardVer(CMD cmd, PBYTE pByte);
	int ReqDmc(CMD cmd, PBYTE pByte);
};


