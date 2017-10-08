#include "stdafx.h"
#include "StandardCommandToProtocol.h"

//yeun
#include "U2SRProtoDef.h"
#include "MultiSensorCommDef.h"
#include "ProtoFlirTau2.h"
/////////////////////////
CStandardCommandToProtocol::CStandardCommandToProtocol()
{
	for (int i = 0; i<MAX_FUNC_PTR_ARR; i++)
	{
		m_FuncPtrArr[i] = NULL;
	}

	m_FuncPtrArr[PANTILT_REQ_CUR_POS1] = &CStandardCommandToProtocol::ReqCurPanTiltPos1;

	m_FuncPtrArr[PANTILT_REQ_CUR_POS2] = &CStandardCommandToProtocol::ReqCurPanTiltPos2;
	//m_FuncPtrArr[PANTILT_REQ_CUR_ALLSTATUS] = &CStandardCommandToProtocol::ReqPanTiltStatus;
	m_FuncPtrArr[PANTILT_REQ_CUR_PANSTATUS] = &CStandardCommandToProtocol::ReqPanStatus;
	m_FuncPtrArr[PANTILT_REQ_CUR_TILTSTATUS] = &CStandardCommandToProtocol::ReqTiltStatus;
	m_FuncPtrArr[PANTILT_REQ_HOMESTATUS] = &CStandardCommandToProtocol::ReqPanTiltHomeStatus;


	m_FuncPtrArr[PANTILT_MOVE_LEFT] = &CStandardCommandToProtocol::MoveLeft;
	m_FuncPtrArr[PANTILT_MOVE_RIGHT] = &CStandardCommandToProtocol::MoveRight;
	m_FuncPtrArr[PANTILT_MOVE_UP] = &CStandardCommandToProtocol::MoveUp;
	m_FuncPtrArr[PANTILT_MOVE_DOWN] = &CStandardCommandToProtocol::MoveDown;
	m_FuncPtrArr[PANTILT_QUIT_LEFT] = &CStandardCommandToProtocol::QuitLeft;
	m_FuncPtrArr[PANTILT_QUIT_RIGHT] = &CStandardCommandToProtocol::QuitRight;
	m_FuncPtrArr[PANTILT_QUIT_UP] = &CStandardCommandToProtocol::QuitUp;
	m_FuncPtrArr[PANTILT_QUIT_DOWN] = &CStandardCommandToProtocol::QuitDown;

	m_FuncPtrArr[PANTILT_PRESET_SET] = &CStandardCommandToProtocol::SetPreset;
	m_FuncPtrArr[PANTILT_PRESET_LINK] = &CStandardCommandToProtocol::LinkPreset;
	m_FuncPtrArr[PANTILT_PRESET_SYNC] = &CStandardCommandToProtocol::SyncPreset;
	m_FuncPtrArr[PANTILT_PRESET_MOVE] = &CStandardCommandToProtocol::MovePreset;
	m_FuncPtrArr[PANTILT_PRESET_GET] = &CStandardCommandToProtocol::GetPreset;
	

	m_FuncPtrArr[PANTILT_SPD] = &CStandardCommandToProtocol::SetPanTiltSpd;
	m_FuncPtrArr[PANTILT_PRESET_SPD] = &CStandardCommandToProtocol::SetPanTiltPresetSpd;

	m_FuncPtrArr[PANTILT_PRESET_TOUR] = &CStandardCommandToProtocol::PresetTour;
	m_FuncPtrArr[PANTILT_PRESET_STOP] = &CStandardCommandToProtocol::PresetStop;

	m_FuncPtrArr[PANTILT_MOVE_HOME] = &CStandardCommandToProtocol::MovePanTiltHome;
	m_FuncPtrArr[PANTILT_INIT] = &CStandardCommandToProtocol::PanTiltInit;

	m_FuncPtrArr[HIGHCAM_ZOOM_TELE] = &CStandardCommandToProtocol::HighZoomTele;
	m_FuncPtrArr[HIGHCAM_ZOOM_WIDE] = &CStandardCommandToProtocol::HighZoomWide;
	m_FuncPtrArr[HIGHCAM_ZOOM_STOP] = &CStandardCommandToProtocol::HighZoomStop;

	m_FuncPtrArr[HIGHCAM_FOCUS_FAR] = &CStandardCommandToProtocol::HighFocusFar;
	m_FuncPtrArr[HIGHCAM_FOCUS_NEAR] = &CStandardCommandToProtocol::HighFocusNear;
	m_FuncPtrArr[HIGHCAM_FOCUS_STOP] = &CStandardCommandToProtocol::HighFocusStop;
	m_FuncPtrArr[HIGHCAM_REQ_CUR_ZFPOS] = &CStandardCommandToProtocol::HighReqCurZFPos;

	m_FuncPtrArr[HIGHCAM_MENU_OPEN] = &CStandardCommandToProtocol::HighMenuOpen;
	m_FuncPtrArr[HIGHCAM_MENU_ENTER] = &CStandardCommandToProtocol::HighMenuEnter;

	m_FuncPtrArr[HIGHCAM_MENU_UP] = &CStandardCommandToProtocol::HighMenuUp;
	m_FuncPtrArr[HIGHCAM_MENU_DOWN] = &CStandardCommandToProtocol::HighMenuDown;
	m_FuncPtrArr[HIGHCAM_MENU_LEFT] = &CStandardCommandToProtocol::HighMenuLeft;
	m_FuncPtrArr[HIGHCAM_MENU_RIGHT] = &CStandardCommandToProtocol::HighMenuRight;

	m_FuncPtrArr[HIGHCAM_ZOOM_SPD] = &CStandardCommandToProtocol::HighSetZoomSpd;
	m_FuncPtrArr[HIGHCAM_FOCUS_SPD] = &CStandardCommandToProtocol::HighSetFocusSpd;

	m_FuncPtrArr[HIGHCAM_AUTOFOCUS] = &CStandardCommandToProtocol::HighAutoFocus;
	m_FuncPtrArr[HIGHCAM_LENSFILTER] = &CStandardCommandToProtocol::HighLensFilter;
	m_FuncPtrArr[HIGHCAM_COLORMODE] = &CStandardCommandToProtocol::HighColorMode;
	m_FuncPtrArr[HIGHCAM_EXTENDER] = &CStandardCommandToProtocol::HighExtenderMode;
	m_FuncPtrArr[HIGHCAM_IRIS] = &CStandardCommandToProtocol::HighIrisMode;

	m_FuncPtrArr[LOWCAM_ZOOM_TELE] = &CStandardCommandToProtocol::LowZoomTele;
	m_FuncPtrArr[LOWCAM_ZOOM_WIDE] = &CStandardCommandToProtocol::LowZoomWide;
	m_FuncPtrArr[LOWCAM_ZOOM_STOP] = &CStandardCommandToProtocol::LowZoomStop;

	m_FuncPtrArr[LOWCAM_FOCUS_FAR] = &CStandardCommandToProtocol::LowFocusFar;
	m_FuncPtrArr[LOWCAM_FOCUS_NEAR] = &CStandardCommandToProtocol::LowFocusNear;
	m_FuncPtrArr[LOWCAM_FOCUS_STOP] = &CStandardCommandToProtocol::LowFocusStop;
	m_FuncPtrArr[LOWCAM_ABSZOOM_MOVE] = &CStandardCommandToProtocol::LowAbsZoomMove;

	m_FuncPtrArr[LOWCAM_MENU_OPEN] = &CStandardCommandToProtocol::LowMenuOpen;
	m_FuncPtrArr[LOWCAM_MENU_ENTER] = &CStandardCommandToProtocol::LowMenuEnter;

	m_FuncPtrArr[LOWCAM_MENU_UP] = &CStandardCommandToProtocol::LowMenuUp;
	m_FuncPtrArr[LOWCAM_MENU_DOWN] = &CStandardCommandToProtocol::LowMenuDown;
	m_FuncPtrArr[LOWCAM_MENU_LEFT] = &CStandardCommandToProtocol::LowMenuLeft;
	m_FuncPtrArr[LOWCAM_MENU_RIGHT] = &CStandardCommandToProtocol::LowMenuRight;


	m_FuncPtrArr[THERMCAM_ZOOM_TELE] = &CStandardCommandToProtocol::ThermZoomTele;
	m_FuncPtrArr[THERMCAM_ZOOM_WIDE] = &CStandardCommandToProtocol::ThermZoomWide;
	m_FuncPtrArr[THERMCAM_ZOOM_STOP] = &CStandardCommandToProtocol::ThermZoomStop;

	m_FuncPtrArr[THERMCAM_FOCUS_FAR] = &CStandardCommandToProtocol::ThermFocusFar;
	m_FuncPtrArr[THERMCAM_FOCUS_NEAR] = &CStandardCommandToProtocol::ThermFocusNear;
	m_FuncPtrArr[THERMCAM_FOCUS_STOP] = &CStandardCommandToProtocol::ThermFocusStop;

	m_FuncPtrArr[THERMCAM_FOCUS_FARFINE] = &CStandardCommandToProtocol::ThermFocusFarFine;
	m_FuncPtrArr[THERMCAM_FOCUS_NEARFINE] = &CStandardCommandToProtocol::ThermFocusNearFine;



	m_FuncPtrArr[THERMCAM_FOCUS_AUTO] = &CStandardCommandToProtocol::ThermSetAutoFocus;

	m_FuncPtrArr[THERMCAM_SET_PWR] = &CStandardCommandToProtocol::ThermSetPwr;
	m_FuncPtrArr[THERMCAM_GET_PWR] = &CStandardCommandToProtocol::ThermGetPwr;
	

	m_FuncPtrArr[THERMCAM_REQ_DZOOM] = &CStandardCommandToProtocol::ThermReqDZoom;
	m_FuncPtrArr[THERMCAM_SET_DZOOM] = &CStandardCommandToProtocol::ThermSetDZoom;

	m_FuncPtrArr[THERMCAM_SET_WHITEHOT] = &CStandardCommandToProtocol::ThermSetWhiteHot;
	m_FuncPtrArr[THERMCAM_SET_BLACKHOT] = &CStandardCommandToProtocol::ThermSetBlackHot;
	m_FuncPtrArr[THERMCAM_REQ_POLARITY] = &CStandardCommandToProtocol::ThermReqPolarity;

	m_FuncPtrArr[THERMCAM_SET_DDEMODE] = &CStandardCommandToProtocol::ThermSetDdeMode;
	m_FuncPtrArr[THERMCAM_SET_DDEGAIN] = &CStandardCommandToProtocol::ThermSetDdeGain;
	m_FuncPtrArr[THERMCAM_SET_DDETHRESHOLD] = &CStandardCommandToProtocol::ThermSetDdeThreshold;

	m_FuncPtrArr[THERMCAM_SET_BRI] = &CStandardCommandToProtocol::ThermSetBri;
	m_FuncPtrArr[THERMCAM_SET_CON] = &CStandardCommandToProtocol::ThermSetCon;
	m_FuncPtrArr[THERMCAM_AUTO_BRI_ON] = &CStandardCommandToProtocol::ThermSetBriAuto;
	m_FuncPtrArr[THERMCAM_AUTO_CON_ON] = &CStandardCommandToProtocol::ThermSetConAuto;

	m_FuncPtrArr[THERMCAM_REQ_BRI] = &CStandardCommandToProtocol::ThermReqBri;
	m_FuncPtrArr[THERMCAM_REQ_CON] = &CStandardCommandToProtocol::ThermReqCon;

	m_FuncPtrArr[THERMCAM_SET_COLOR] = &CStandardCommandToProtocol::ThermSetColor;

	m_FuncPtrArr[THERMCAM_SET_AGCMODE] = &CStandardCommandToProtocol::ThermAGCMode;
	
	m_FuncPtrArr[CH1_CAM1] = &CStandardCommandToProtocol::SetCh1Cam1;
	m_FuncPtrArr[CH1_CAM2] = &CStandardCommandToProtocol::SetCh1Cam2;
	m_FuncPtrArr[CH1_CAM3] = &CStandardCommandToProtocol::SetCh1Cam3;

	m_FuncPtrArr[CH2_CAM1] = &CStandardCommandToProtocol::SetCh2Cam1;
	m_FuncPtrArr[CH2_CAM2] = &CStandardCommandToProtocol::SetCh2Cam2;
	m_FuncPtrArr[CH2_CAM3] = &CStandardCommandToProtocol::SetCh2Cam3;

	//m_FuncPtrArr[CH1_X] = &CStandardCommandToProtocol::SetCh1X;

	m_FuncPtrArr[PWR_ON] = &CStandardCommandToProtocol::PowerOn;
	m_FuncPtrArr[PWR_OFF] = &CStandardCommandToProtocol::PowerOff;
	m_FuncPtrArr[PWR_REQ_STATUS] = &CStandardCommandToProtocol::ReqPowerStatus;

	m_FuncPtrArr[GPS_REQ_VAL] = &CStandardCommandToProtocol::ReqGPS;
	m_FuncPtrArr[MAINBOARD_REQ_VER] = &CStandardCommandToProtocol::ReqMainBoardVer;
	m_FuncPtrArr[DMC_REQ_VAL] = &CStandardCommandToProtocol::ReqDmc;


	m_FuncPtrArr[LRF_PWR_ON] = &CStandardCommandToProtocol::LrfPowerOn;
	m_FuncPtrArr[LRF_PWR_OFF] = &CStandardCommandToProtocol::LrfPowerOff;


	m_FuncPtrArr[LRF_SHOT] = &CStandardCommandToProtocol::LrfReqDistance;
	m_FuncPtrArr[LRF_STATUS] = &CStandardCommandToProtocol::LrfReqStatus;
	m_FuncPtrArr[LRF_GET_RANGE_GATE] = &CStandardCommandToProtocol::LrfReqRangeGate;

	m_FuncPtrArr[LRF_PT_LEFT] = &CStandardCommandToProtocol::LrfMoveLeft;
	m_FuncPtrArr[LRF_PT_RIGHT] = &CStandardCommandToProtocol::LrfMoveRight;
	m_FuncPtrArr[LRF_PT_UP] = &CStandardCommandToProtocol::LrfMoveUp;
	m_FuncPtrArr[LRF_PT_DOWN] = &CStandardCommandToProtocol::LrfMoveDown;
	m_FuncPtrArr[LRF_PT_STOP] = &CStandardCommandToProtocol::LrfMoveStop;

	m_iProtoThermCam = THERMCAM_FLIR;
}


CStandardCommandToProtocol::~CStandardCommandToProtocol()
{
}
void CStandardCommandToProtocol::SetHighCamProto(int iProto)
{
	m_iProtoHighCam = iProto;
}

void CStandardCommandToProtocol::SetThermCamProto(int iProto)
{
	m_iProtoThermCam = iProto;
}

void CStandardCommandToProtocol::SetLrfProto(int iProto)
{
	m_iProtoLrf = iProto;
}

int CStandardCommandToProtocol::ReqCurPanTiltPos1(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.GetAngle(pByte);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, cmd.bQueue, cmd.bEmergency, (int)cmd.dArrParam[0] );
}
int CStandardCommandToProtocol::ReqCurPanTiltPos2(CMD cmd, PBYTE pByte)
{
	//SetSentReqCmd(cmd.iCmd);//어떤 명령을 보냈는지 수신측에서 파싱할때 사용
	//다른명령과 같이 쓸려면 //SetSentReqCmd 를 사용하는 명령만 써야됨 
	int  iLen = m_protoU2srParser.GetAngle(pByte);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, FALSE );
}
int CStandardCommandToProtocol::MoveRight(CMD cmd, PBYTE pByte)
{
	//theApp.m_bPanUsed = TRUE;
	int  iLen = m_protoU2srParser.MoveRight(pByte);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, cmd.bQueue, cmd.bEmergency );
}

int CStandardCommandToProtocol::MoveLeft(CMD cmd, PBYTE pByte)
{
	//theApp.m_bPanUsed = TRUE;
	int  iLen = m_protoU2srParser.MoveLeft(pByte);
	//pByte = m_byBuffer;
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, cmd.bQueue, cmd.bEmergency );
}
int CStandardCommandToProtocol::MoveUp(CMD cmd, PBYTE pByte)
{
	//theApp.m_bTiltUsed = TRUE;
	int  iLen = m_protoU2srParser.MoveUp(pByte);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, cmd.bQueue, cmd.bEmergency );
}
int CStandardCommandToProtocol::MoveDown(CMD cmd, PBYTE pByte)
{
	//theApp.m_bTiltUsed = TRUE;
	int  iLen = m_protoU2srParser.MoveDown(pByte);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, cmd.bQueue, cmd.bEmergency );
}
int CStandardCommandToProtocol::QuitLeft(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.QuitLeft(pByte);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, cmd.bQueue, cmd.bEmergency );
}
int CStandardCommandToProtocol::QuitRight(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.QuitRight(pByte);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, cmd.bQueue, cmd.bEmergency );	
}
int CStandardCommandToProtocol::QuitUp(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.QuitUp(pByte);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, cmd.bQueue, cmd.bEmergency );	
}
int CStandardCommandToProtocol::QuitDown(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.QuitDown(pByte);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, cmd.bQueue, cmd.bEmergency );
}
int CStandardCommandToProtocol::SetPreset(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.PutPreset(pByte, cmd.dArrParam);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, FALSE );
}
int CStandardCommandToProtocol::GetPreset(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.GetPreset(pByte, cmd.dArrParam);
	return iLen;
}
int CStandardCommandToProtocol::LinkPreset(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.LinkPreset(pByte, cmd.dArrParam);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, FALSE );
}
int CStandardCommandToProtocol::SyncPreset(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.SyncPreset(pByte);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, FALSE );
}
int CStandardCommandToProtocol::MovePreset(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.MovePreset(pByte);

	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, FALSE );
}
int CStandardCommandToProtocol::MovePanTiltHome(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.MovePanTiltHome(pByte);

	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, FALSE );
}
int CStandardCommandToProtocol::ReqPanTiltHomeStatus(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.ReadPanTiltHome_Status(pByte);

	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, FALSE, 2 );//전송시 딜레이를 줌(전송을 늦게함)
}
int CStandardCommandToProtocol::ReqPanStatus(CMD cmd, PBYTE pByte)
{
	//SetSentReqCmd( PANTILT_REQ_CUR_PANSTATUS );
	int  iLen = m_protoU2srParser.PanGetStatus(pByte);

	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, FALSE );	
}
int CStandardCommandToProtocol::ReqTiltStatus(CMD cmd, PBYTE pByte)
{
	//SetSentReqCmd( PANTILT_REQ_CUR_TILTSTATUS );
	int  iLen = m_protoU2srParser.TiltGetStatus(pByte);

	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, FALSE  );


}
int CStandardCommandToProtocol::PowerOff(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.PowerOff(pByte);

	return iLen;
	//  [4/9/2014 Yeun] //m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, FALSE, 2 );	
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, FALSE );
}
int CStandardCommandToProtocol::PowerOn(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.PowerOn(pByte);

	return iLen;
	//  [4/9/2014 Yeun] //m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, FALSE, 2 );
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, FALSE );
}
int CStandardCommandToProtocol::LrfPowerOn(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.SetLRFPwr(pByte, true);
	//pByte = m_byBuffer;
	return iLen;
	//  [4/9/2014 Yeun] //m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, FALSE, 2 );
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, FALSE );
}
int CStandardCommandToProtocol::LrfPowerOff(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.SetLRFPwr(pByte, false);
	//pByte = m_byBuffer;
	return iLen;
	//  [4/9/2014 Yeun] //m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, FALSE, 2 );
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, FALSE );
}

int CStandardCommandToProtocol::ReqPowerStatus(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.GetPower(pByte);
	//pByte = m_byBuffer;
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, FALSE, 2 );
}

int CStandardCommandToProtocol::HighZoomTele(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.MLense_ZoomTeleStart(pByte);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, TRUE );
}
int CStandardCommandToProtocol::HighZoomWide(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.MLense_ZoomWideStart(pByte);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, TRUE );
}
int CStandardCommandToProtocol::HighZoomStop(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.MLense_ZoomStop(pByte);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}
int CStandardCommandToProtocol::HighFocusNear(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.MLense_FocusInStart(pByte);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, TRUE );
}
int CStandardCommandToProtocol::HighFocusFar(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.MLense_FocusOutStart(pByte);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, TRUE );
}
int CStandardCommandToProtocol::HighFocusStop(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.MLense_FocusStop(pByte);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, FALSE );
}
int CStandardCommandToProtocol::HighReqCurZFPos(CMD cmd, PBYTE pByte)
{
	//SetSentReqCmd(cmd.iCmd);//어떤 명령을 보냈는지 수신측에서 파싱할때 사용
	//다른명령과 같이 쓸려면 //SetSentReqCmd 를 사용하는 명령만 써야됨 
	int  iLen = m_protoU2srParser.MLense_GetPMeter(pByte);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen);
}
int CStandardCommandToProtocol::HighSetZoomSpd(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.MLense_ZoomSetSpeed(pByte, cmd.dArrParam[0]);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen);

}
int CStandardCommandToProtocol::HighSetFocusSpd(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.MLense_FocusSetSpeed(pByte, cmd.dArrParam[0]);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen);
}

int CStandardCommandToProtocol::HighAutoFocus(CMD cmd, PBYTE pByte)//  [8/19/2014 Yeun] 
{
	int  iLen = m_protoU2srParser.MLense_AutoFocus(pByte);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen);
}

int CStandardCommandToProtocol::HighLensFilter(CMD cmd, PBYTE pByte)//  [8/19/2014 Yeun] 
{
	int  iLen = m_protoU2srParser.MLense_LensFilter(pByte, (int)cmd.dArrParam[0]);
	return iLen;

	//-140914 Yeun
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, FALSE, 10 );//전송시 딜레이를 줌(전송을 늦게함)
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}



int CStandardCommandToProtocol::HighColorMode(CMD cmd, PBYTE pByte)//  [8/19/2014 Yeun] 
{



	if ((int)cmd.dArrParam[0] == 1)//color
	{
		int  iLen = m_protoU2srParser.SetHighColor(pByte);
		return iLen;
		//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
	}
	else if ((int)cmd.dArrParam[0] == 2)//B/W
	{
		int  iLen = m_protoU2srParser.SetHighBW(pByte);
		return iLen;
		//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
	}

}

int CStandardCommandToProtocol::HighExtenderMode(CMD cmd, PBYTE pByte)
{
	if ((int)cmd.dArrParam[0] == 1)//on
	{
		int  iLen = m_protoU2srParser.SetHighExtender(pByte, TRUE);
		return iLen;
	}
	else if ((int)cmd.dArrParam[0] == 2)//off
	{
		int  iLen = m_protoU2srParser.SetHighExtender(pByte, FALSE);
		return iLen;
	}
	else
		ASSERT(FALSE);
}
int CStandardCommandToProtocol::HighIrisMode(CMD cmd, PBYTE pByte)
{
	if ((int)cmd.dArrParam[0] == 1)//on
	{
		int  iLen = m_protoU2srParser.SetHighIris(pByte, TRUE);
		return iLen;
	}
	else if ((int)cmd.dArrParam[0] == 2)//off
	{
		int  iLen = m_protoU2srParser.SetHighIris(pByte, FALSE);
		return iLen;
	}
	else
		ASSERT(FALSE);
}

int CStandardCommandToProtocol::HighMenuOpen(CMD cmd, PBYTE pByte)
{
	switch (m_iProtoHighCam)
	{
	case BOXCAM_SAMSUNG:
	{
		int  iLen = m_protoU2srParser.HighCamMenuOpen(pByte);
		return iLen;
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
	}
	break;
	case BOXCAM_HITACHI:
	{
#if 0 //161110 임시 사용 안함
		int  iLen = CProtoHitachi::SetMenuOn(m_byBuffer);
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
#endif
	}
	break;

	}

}
int CStandardCommandToProtocol::HighMenuEnter(CMD cmd, PBYTE pByte)
{
	switch (m_iProtoHighCam)
	{
	case BOXCAM_SAMSUNG:
	{
		int  iLen = m_protoU2srParser.HighCamMenuEnter(pByte);
		return iLen;
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
	}
	break;
	case BOXCAM_HITACHI:
	{
#if 0 //161110 임시 사용 안함
		int  iLen = CProtoHitachi::SetMenuSet(m_byBuffer);
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
#endif
	}
	break;
	}

}
int CStandardCommandToProtocol::HighMenuLeft(CMD cmd, PBYTE pByte)
{
	switch (m_iProtoHighCam)
	{
	case BOXCAM_SAMSUNG:
	{
		int  iLen = m_protoU2srParser.HighCamMenuLeft(pByte);
		return iLen;
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
	}
	break;
	case BOXCAM_HITACHI:
	{
#if 0 //161110 임시 사용 안함
		int  iLen = CProtoHitachi::SetMenuUpAndDown(m_byBuffer);
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
#endif
	}
	break;
	}

}
int CStandardCommandToProtocol::HighMenuRight(CMD cmd, PBYTE pByte)
{
	switch (m_iProtoHighCam)
	{
	case BOXCAM_SAMSUNG:
	{
		int  iLen = m_protoU2srParser.HighCamMenuRight(pByte);
		return iLen;
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
	}
	break;
	case BOXCAM_HITACHI:
	{
#if 0 //161110 임시 사용 안함
		int  iLen = CProtoHitachi::SetMenuUpAndDown(m_byBuffer);
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
#endif
	}
	break;
	}
}
int CStandardCommandToProtocol::HighMenuUp(CMD cmd, PBYTE pByte)
{
	switch (m_iProtoHighCam)
	{
	case BOXCAM_SAMSUNG:
	{
		int  iLen = m_protoU2srParser.HighCamMenuUp(pByte);
		return iLen;
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
	}
	break;
	case BOXCAM_HITACHI:
	{
#if 0 //161110 임시 사용 안함
		int  iLen = CProtoHitachi::SetMenuUp(m_byBuffer);
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
#endif
	}
	break;
	}
}
int CStandardCommandToProtocol::HighMenuDown(CMD cmd, PBYTE pByte)
{
	switch (m_iProtoHighCam)
	{
	case BOXCAM_SAMSUNG:
	{
		int  iLen = m_protoU2srParser.HighCamMenuDown(m_byBuffer);
		pByte = m_byBuffer;
		return iLen;
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
	}
	break;
	case BOXCAM_HITACHI:
	{
#if 0 //161110 임시 사용 안함
		int  iLen = CProtoHitachi::SetMenuDown(m_byBuffer);
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
#endif
	}
	break;

	}
}

int CStandardCommandToProtocol::LowZoomTele(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.ALense_ZoomTeleStart(m_byBuffer);
	pByte = m_byBuffer;
	return iLen;
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, TRUE );
}
int CStandardCommandToProtocol::LowZoomWide(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.ALense_ZoomWideStart(m_byBuffer);
	pByte = m_byBuffer;
	return iLen;
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, TRUE );
}
int CStandardCommandToProtocol::LowZoomStop(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.ALense_ZFStop(m_byBuffer);
	pByte = m_byBuffer;
	return iLen;
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, FALSE );
}
int CStandardCommandToProtocol::LowFocusNear(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.ALense_FocusInStart(m_byBuffer);
	pByte = m_byBuffer;
	return iLen;
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, TRUE );
}
int CStandardCommandToProtocol::LowFocusFar(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.ALense_FocusOutStart(m_byBuffer);
	pByte = m_byBuffer;
	return iLen;
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, TRUE );
}
int CStandardCommandToProtocol::LowFocusStop(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.ALense_ZFStop(m_byBuffer);
	pByte = m_byBuffer;
	return iLen;
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}
int CStandardCommandToProtocol::LowAbsZoomMove(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.ALense_ZoomMoveTo(m_byBuffer, cmd.dArrParam);
	pByte = m_byBuffer;
	return iLen;
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}
int CStandardCommandToProtocol::LowMenuOpen(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.LowCamMenuOpen(m_byBuffer);
	pByte = m_byBuffer;
	return iLen;
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}
int CStandardCommandToProtocol::LowMenuEnter(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.LowCamMenuEnter(m_byBuffer);
	pByte = m_byBuffer;
	return iLen;
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}
int CStandardCommandToProtocol::LowMenuLeft(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.LowCamMenuLeft(m_byBuffer);
	pByte = m_byBuffer;
	return iLen;
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}
int CStandardCommandToProtocol::LowMenuRight(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.LowCamMenuRight(m_byBuffer);
	pByte = m_byBuffer;
	return iLen;
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}
int CStandardCommandToProtocol::LowMenuUp(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.LowCamMenuUp(m_byBuffer);
	pByte = m_byBuffer;
	return iLen;
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}
int CStandardCommandToProtocol::LowMenuDown(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.LowCamMenuDown(m_byBuffer);
	pByte = m_byBuffer;
	return iLen;
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}

//////////////////////////////////////////////////////////////////////////
//열영상카메라
int CStandardCommandToProtocol::ThermZoomTele(CMD cmd, PBYTE pByte)
{
	//열상은 광학줌이 없어서 디지털 줌으로 대체
	switch (m_iProtoThermCam)
	{
	case THERMCAM_CANTRONIC:
	{
#if 0 //161110 임시 사용 안함
		int  iLen = CProtoCantronic::SetDZoom(m_byBuffer, cmd.dArrParam[0]);
		//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen);
#endif
	}
	break;
	case THERMCAM_OPGAL:
	{
		if ((int)cmd.dArrParam[0] == 1)
			cmd.dArrParam[0] = 0;
		else if ((int)cmd.dArrParam[0] == 2)
			cmd.dArrParam[0] = 1;
		else if ((int)cmd.dArrParam[0] == 4)
			cmd.dArrParam[0] = 2;
#if 0 //161110 임시 사용 안함
		int  iLen = m_protoOpgal.SetZoom(m_byBuffer, cmd.dArrParam[0]);
#endif
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen);
	}
	break;
	case THERMCAM_FLIR:
	{
		double dZoom = cmd.dArrParam[0];
		if (dZoom == 2)
			dZoom = 1.5;
		else if (dZoom == 4)
			dZoom = 2.0;
		else if (dZoom == 6)
			dZoom = 6.0;
		else if (dZoom == 8)
			dZoom = 8.0;

#if 0 //161110 임시 사용 안함
		int  iLen = CProtoFlirTau2::SetDigitalZoom(m_byBuffer, dZoom);
		iLen = m_protoU2srParser.SetWrappingThermProto(m_byBuffer, iLen);
#endif

		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen);
	}
	break;
	}
	return 0;
}
int CStandardCommandToProtocol::ThermZoomWide(CMD cmd, PBYTE pByte)
{
	//열상은 광학줌이 없어서 디지털 줌으로 대체
	switch (m_iProtoThermCam)
	{
	case THERMCAM_CANTRONIC:
	{
#if 0 //161110 임시 사용 안함
		int  iLen = CProtoCantronic::SetDZoom(m_byBuffer, cmd.dArrParam[0]);
#endif
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen);
	}
	break;
	case THERMCAM_OPGAL:
	{
#if 0 //161110 임시 사용 안함
		int  iLen = m_protoOpgal.SetZoom(m_byBuffer, cmd.dArrParam[0]);
#endif
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen);
	}
	break;
	case THERMCAM_FLIR:
	{
		double dZoom = cmd.dArrParam[0];
		if (dZoom == 2)
			dZoom = 1.5;
		else if (dZoom == 4)
			dZoom = 2.0;
#if 0 //161110 임시 사용 안함
		int  iLen = CProtoFlirTau2::SetDigitalZoom(m_byBuffer, dZoom);

		iLen = m_protoU2srParser.SetWrappingThermProto(m_byBuffer, iLen);
#endif

		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen);
	}
	}
	return 0;
}
int CStandardCommandToProtocol::ThermZoomStop(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.TLense_ZoomStop(pByte);
	return iLen;
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, FALSE );
}
int CStandardCommandToProtocol::ThermFocusNear(CMD cmd, PBYTE pByte)
{
	switch (m_iProtoThermCam)
	{
	case THERMCAM_CANTRONIC:
	{
#if 0 //161110 임시 사용 안함
		int  iLen = CProtoCantronic::SetFocusNear(m_byBuffer);
#endif
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, TRUE );
	}
	break;
	case THERMCAM_OPGAL:
	{
#if 0 //161110 임시 사용 안함
		//전압제어
		int  iLen = m_protoU2srParser.TLense_FocusIn(m_byBuffer);
#endif
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, TRUE );
	}
	case THERMCAM_FLIR:
	{
		//전압제어
		int  iLen = m_protoU2srParser.TLense_FocusIn(pByte);
		return iLen;
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, TRUE );
	}
	break;
	default:
		ASSERT(FALSE);
	}
	return 0;
}
int CStandardCommandToProtocol::ThermFocusFar(CMD cmd, PBYTE pByte)
{
	switch (m_iProtoThermCam)
	{
	case THERMCAM_CANTRONIC:
	{
#if 0 //161110 임시 사용 안함
		int  iLen = CProtoCantronic::SetFocusFar(m_byBuffer);
#endif
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, TRUE );
	}
	break;
	case THERMCAM_OPGAL:
	{
		int  iLen = m_protoU2srParser.TLense_FocusOut(m_byBuffer);
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, TRUE );
	}
	break;
	case THERMCAM_FLIR:
	{
		//전압제어
		int  iLen = m_protoU2srParser.TLense_FocusOut(pByte);
		return iLen;
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, TRUE );
	}
	break;
	default:
		ASSERT(FALSE);
	}
}
int CStandardCommandToProtocol::ThermFocusNearFine(CMD cmd, PBYTE pByte)
{
	switch (m_iProtoThermCam)
	{
	case THERMCAM_CANTRONIC:
	{
#if 0 //161110 임시 사용 안함
		int  iLen = CProtoCantronic::SetFocusFineNear(m_byBuffer);
#endif
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, TRUE );
	}
	break;
	case THERMCAM_OPGAL:
	{
		ASSERT(FALSE);
	}
	break;
	case THERMCAM_FLIR:
	{
		ASSERT(FALSE);
	}
	break;
	default:
		ASSERT(FALSE);
	}
	return 0;
}
int CStandardCommandToProtocol::ThermFocusFarFine(CMD cmd, PBYTE pByte)
{
	switch (m_iProtoThermCam)
	{
	case THERMCAM_CANTRONIC:
	{
#if 0 //161110 임시 사용 안함
		int  iLen = CProtoCantronic::SetFocusFineFar(m_byBuffer);
#endif
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, TRUE );
	}
	break;
	case THERMCAM_OPGAL:
	{
		ASSERT(FALSE);
	}
	break;
	case THERMCAM_FLIR:
	{
		ASSERT(FALSE);
	}
	break;
	default:
		ASSERT(FALSE);
	}
	return 0;
}
int CStandardCommandToProtocol::ThermFocusStop(CMD cmd, PBYTE pByte)
{
	switch (m_iProtoThermCam)
	{
	case THERMCAM_CANTRONIC:
	{
#if 0 //161110 임시 사용 안함
		int  iLen = CProtoCantronic::SetFocusStop(m_byBuffer);
#endif
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, TRUE );
	}
	break;
	case THERMCAM_OPGAL:
	{
		int  iLen = m_protoU2srParser.TLense_FocusStop(m_byBuffer);
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
	}
	break;
	case THERMCAM_FLIR:
	{
		int  iLen = m_protoU2srParser.TLense_FocusStop(pByte);
		return iLen;
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
	}
	break;
	default:
		ASSERT(FALSE);
	}

	return 0;
}
int CStandardCommandToProtocol::ThermSetAutoFocus(CMD cmd, PBYTE pByte)
{
	return 0;
	switch (m_iProtoThermCam)
	{
	case THERMCAM_CANTRONIC:
	{
#if 0 //161110 임시 사용 안함
		int  iLen = CProtoCantronic::SetAutoFocus(m_byBuffer);
#endif
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
	}
	break;
	case THERMCAM_OPGAL:
	{

	}
	break;
	case THERMCAM_FLIR:
	{

	}
	break;
	default:
		ASSERT(FALSE);
	}
	return 0;
}
int CStandardCommandToProtocol::ThermReqDZoom(CMD cmd, PBYTE pByte)
{
	int  nLen = CProtoFlirTau2::ReqDigitalZoom(pByte);
	nLen = m_protoU2srParser.SetWrappingThermProto(pByte, nLen, TRUE);
	pByte[nLen] = 0x00;
	return nLen;
	/*

	int  iLen = m_protoU2srParser.TLense_GetDZoom( m_byBuffer );
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );*/

}

int CStandardCommandToProtocol::ThermSetDZoom(CMD cmd, PBYTE pByte)
{	
	double dZoom = cmd.dArrParam[0];


	if (dZoom == 1)
		dZoom = 1;
	else if (dZoom == 2)
		dZoom = 2.0;
	else if (dZoom == 3)
		dZoom = 3.0;
	else if (dZoom == 4)
		dZoom = 4.0;

	int  nLen = CProtoFlirTau2::SetDigitalZoom(pByte, dZoom);
	nLen = m_protoU2srParser.SetWrappingThermProto(pByte, nLen);
	pByte[nLen] = 0x00;
	return nLen;

	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );*/

}

int CStandardCommandToProtocol::ThermSetPwr(CMD cmd, PBYTE pByte)
{
	int  iLen = 0;
	if ((int)cmd.dArrParam[0] == 1)
		iLen = m_protoU2srParser.TLense_Power_ON(pByte);
	else
		iLen = m_protoU2srParser.TLense_Power_OFF(pByte);
	
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}
int CStandardCommandToProtocol::ThermGetPwr(CMD cmd, PBYTE pByte)
{

	int i = 0;
	pByte[i++] = 'T';
	pByte[i++] = 'P';
	pByte[i++] = '=';
	pByte[i++] = '?';
	pByte[i++] = 0x0d;

	return i;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}
int CStandardCommandToProtocol::ThermSetWhiteHot(CMD cmd, PBYTE pByte)
{
	switch (m_iProtoThermCam)
	{
	case THERMCAM_CANTRONIC:
	{
#if 0 //161110 임시 사용 안함
		int  iLen = CProtoCantronic::SetWhiteHot(m_byBuffer);
#endif
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
	}
	break;
	case THERMCAM_OPGAL:
	{
#if 0 //161110 임시 사용 안함
		int  iLen = m_protoOpgal.SetPolarity(m_byBuffer, 1);
		iLen = m_protoU2srParser.SetWrappingThermProto(m_byBuffer, iLen);
#endif
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
	}
	break;
	case THERMCAM_FLIR:
	{
#if 1
		int  iLen = CProtoFlirTau2::SetVideoPalette(pByte, 0);
		iLen = m_protoU2srParser.SetWrappingThermProto(pByte, iLen);
		return iLen;
#endif
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
	}
	break;
	}
	return 0;
}
int CStandardCommandToProtocol::ThermSetBlackHot(CMD cmd, PBYTE pByte)
{
	
	switch (m_iProtoThermCam)
	{
	case THERMCAM_CANTRONIC:
	{
#if 0 //161110 임시 사용 안함
		int  iLen = CProtoCantronic::SetBlackHot(m_byBuffer);
#endif
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
	}
	break;
	case THERMCAM_OPGAL:
	{
#if 0 //161110 임시 사용 안함
		int  iLen = m_protoOpgal.SetPolarity(m_byBuffer, 0);
		iLen = m_protoU2srParser.SetWrappingThermProto(m_byBuffer, iLen);
#endif
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
	}
	break;
	case THERMCAM_FLIR:
	{
#if 1
		int  iLen = CProtoFlirTau2::SetVideoPalette(pByte, 1);
		iLen = m_protoU2srParser.SetWrappingThermProto(pByte, iLen);
		return iLen;
#endif
		////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
	}
	break;
	}
	return 0;
}
int CStandardCommandToProtocol::ThermReqPolarity(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.TLense_GetPolarity(pByte);
	return 0;
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}
int CStandardCommandToProtocol::ThermSetDdeMode(CMD cmd, PBYTE pByte)
{
	//Bytes 0 - 1:   0x0000 – 0x000F = manually specified threshold
	//0x0100 – 0x013F automatic threshold(0 to 63)
#if 1 
	int  iLen = CProtoFlirTau2::SetDdeMode(pByte, (WORD)cmd.dArrParam[0]);
	iLen = m_protoU2srParser.SetWrappingThermProto(pByte, iLen);
	return iLen;
#endif
	
}
int CStandardCommandToProtocol::ThermSetDdeGain(CMD cmd, PBYTE pByte)
{
	int  iLen = CProtoFlirTau2::SetDdeGain(pByte, (WORD)cmd.dArrParam[0]);
	iLen = m_protoU2srParser.SetWrappingThermProto(pByte, iLen);

	return iLen;

}
int CStandardCommandToProtocol::ThermSetDdeThreshold(CMD cmd, PBYTE pByte)
{
	return 0;
#if 0 //161110 임시 사용 안함
	int  iLen = CProtoFlirTau2::SetDdeThreshold(m_byBuffer, (WORD)cmd.dArrParam[0]);
	iLen = m_protoU2srParser.SetWrappingThermProto(m_byBuffer, iLen);
#endif
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}

int CStandardCommandToProtocol::ThermSetBriAuto(CMD cmd, PBYTE pByte)
{
	


	return 0;
#if 0 //161110 임시 사용 안함
	int  iLen = CProtoCantronic::AutoBri(m_byBuffer);
#endif
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}

int CStandardCommandToProtocol::ThermSetConAuto(CMD cmd, PBYTE pByte)
{
	return 0;
#if 0 //161110 임시 사용 안함
	int  iLen = CProtoCantronic::AutoCon(m_byBuffer);
#endif
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}
int CStandardCommandToProtocol::ThermSetBri(CMD cmd, PBYTE pByte)
{
	int  iLen = CProtoFlirTau2::SetBrightness(pByte, (WORD)cmd.dArrParam[0]);
	iLen = m_protoU2srParser.SetWrappingThermProto(pByte, iLen);
	return iLen;


	//#define CMD_T_LENSE_AUTO_NUCMODE_OFF	"TC=S:6E206166706E 20 6F66660D"	// n afpn off
	//"TC=S:6E 20 61 63 6E 74 20 6F 6E 0D" 
	BYTE byTest[100];
	/*
	byTest[0] = 0x6E;
	byTest[1] = 0x20;
	byTest[2] = 0x61;
	byTest[3] = 0x63;
	byTest[4] = 0x6E;
	byTest[5] = 0x74;
	byTest[6] = 0x20;
	byTest[7] = 0x6F;
	byTest[8] = 0x6E;
	byTest[9] = 0x0d;
	*/

	//#define CMD_T_LENSE_POL_BW				"TC=S:6E20706F6C2062770D"		// n pol bw
	//#define CMD_T_LENSE_POL_WB				"TC=S:6E20706F6C2077620D"		// n pol wb
	//#define CMD_T_LENSE_ZOOM_1				"TC=S:6E 20 7A 6F 6D 20 31 0D"			// n zom 1
	//#define CMD_T_LENSE_ZOOM_2				"TC=S:6E207A6F6D20320D"			// n zom 2
	//#define CMD_T_LENSE_ZOOM_4				"TC=S:6E207A6F6D20340D"			// n zom 4

	byTest[0] = 0x6E;
	byTest[1] = 0x20;
	byTest[2] = 0x7A;
	byTest[3] = 0x6F;
	byTest[4] = 0x6D;
	byTest[5] = 0x20;
	byTest[6] = 0x31;
	byTest[7] = 0x0D;
#if 0 //161110 임시 사용 안함
	ZeroMemory(m_byBuffer, sizeof(m_byBuffer));
	int  iLen = CProtoCantronic::SetBri(m_byBuffer, cmd.dArrParam[0]);
	//CString stt
	/*
	CString strHexa;
	m_protoU2srParser.ConvertByteToHexa( m_byBuffer, iLen, strHexa );
	memcpy( m_byBuffer, strHexa, strHexa.GetLength() );*/



	iLen = m_protoU2srParser.SetWrappingThermProto(m_byBuffer, iLen);
#endif
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE );
}

int CStandardCommandToProtocol::ThermSetCon(CMD cmd, PBYTE pByte)
{

	int  iLen = CProtoFlirTau2::SetContrast(pByte, (WORD)cmd.dArrParam[0]);
	iLen = m_protoU2srParser.SetWrappingThermProto(pByte, iLen);
	return iLen;




#if 0 //161110 임시 사용 안함
	ZeroMemory(m_byBuffer, sizeof(m_byBuffer));
	int  iLen = CProtoCantronic::SetCon(m_byBuffer, cmd.dArrParam[0]);
	/*
	CString strHexa;
	m_protoU2srParser.ConvertByteToHexa( m_byBuffer, iLen, strHexa );
	memcpy( m_byBuffer, strHexa, strHexa.GetLength() );
	*/


	iLen = m_protoU2srParser.SetWrappingThermProto(m_byBuffer, iLen);
#endif
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE );
}

int CStandardCommandToProtocol::ThermReqBri(CMD cmd, PBYTE pByte)
{
	

	int  iLen = CProtoFlirTau2::ReqBrightness(pByte);
	iLen = m_protoU2srParser.SetWrappingThermProto(pByte, iLen);
	return iLen;

#if 0 //161110 임시 사용 안함
	ZeroMemory(m_byBuffer, sizeof(m_byBuffer));
	int  iLen = CProtoCantronic::ReqBri(m_byBuffer);
	iLen = m_protoU2srParser.SetWrappingThermProto(m_byBuffer, iLen, TRUE);
#endif
	////SetSentReqCmd( cmd.iCmd );
	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE );
}

int CStandardCommandToProtocol::ThermReqCon(CMD cmd, PBYTE pByte)
{
	int  iLen = CProtoFlirTau2::ReqContrast(pByte);
	iLen = m_protoU2srParser.SetWrappingThermProto(pByte, iLen);
	return iLen;



#if 0 //161110 임시 사용 안함
	ZeroMemory(m_byBuffer, sizeof(m_byBuffer));
	int  iLen = CProtoCantronic::ReqCon(m_byBuffer);
	iLen = m_protoU2srParser.SetWrappingThermProto(m_byBuffer, iLen, TRUE);
#endif
	////SetSentReqCmd( cmd.iCmd );
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE );
}

//added 20160128 for Tau2 
int CStandardCommandToProtocol::ThermSetColor(CMD cmd, PBYTE pByte)
{
	
#if 1 //161110 임시 사용 안함
	int  iLen = CProtoFlirTau2::SetVideoPalette(pByte, (WORD)cmd.dArrParam[0]);
	iLen = m_protoU2srParser.SetWrappingThermProto(pByte, iLen);
	return iLen;
#endif
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}
int CStandardCommandToProtocol::ThermAGCMode(CMD cmd, PBYTE pByte)
{
	//0x0000 = plateau histogram
	//0x0001 = once bright
	//0x0002 = auto bright
	//0x0003 = manual
	//0x0004 = not defined (returns error)
	//0x0005 = linear AGC
	//0x0009 = Information-based
	//0x000A = Information-based equalization  

	WORD word;
	if (cmd.dArrParam[0] == 1)	//1 : Manual
	{
		word = 0x0002;
	}
	else if (cmd.dArrParam[0] == 2)//2 : Auto
	{
		word = 0x0003;
	}

	int  iLen = CProtoFlirTau2::SetAGCMode(pByte, word);
	iLen = m_protoU2srParser.SetWrappingThermProto(pByte, iLen);

	return iLen;


}
//////////////////////////////////////////////////////////////////////////
int CStandardCommandToProtocol::SetCh1Cam1(CMD cmd, PBYTE pByte)
{
	return 0;
	int  iLen = m_protoU2srParser.SetCH1High(m_byBuffer);
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}
int CStandardCommandToProtocol::SetCh1Cam2(CMD cmd, PBYTE pByte)
{
	return 0;
	int  iLen = m_protoU2srParser.SetCH1Low(m_byBuffer);
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, FALSE, 4 );//yeun20150129
}
int CStandardCommandToProtocol::SetCh1Cam3(CMD cmd, PBYTE pByte)
{
	return 0;
	int  iLen = m_protoU2srParser.SetCH1Thermal(m_byBuffer);
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}
int CStandardCommandToProtocol::SetCh2Cam1(CMD cmd, PBYTE pByte)
{
	return 0;
	int  iLen = m_protoU2srParser.SetCH2High(m_byBuffer);
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}
int CStandardCommandToProtocol::SetCh2Cam2(CMD cmd, PBYTE pByte)
{
	return 0;
	int  iLen = m_protoU2srParser.SetCH2Low(m_byBuffer);
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}
int CStandardCommandToProtocol::SetCh2Cam3(CMD cmd, PBYTE pByte)
{
	return 0;
	int  iLen = m_protoU2srParser.SetCH2Thermal(m_byBuffer);
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}



int CStandardCommandToProtocol::SetPanTiltSpd(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.SetAngleSpeed(pByte, cmd.dArrParam[0]);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}
int CStandardCommandToProtocol::SetPanTiltPresetSpd(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.SetAnglePresetSpeedVal(pByte, cmd.dArrParam[0]);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
}

int CStandardCommandToProtocol::ReqGPS(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.GPSGetValue(pByte);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );

}
int CStandardCommandToProtocol::ReqMainBoardVer(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.ReqMainBoardVersion(pByte);
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );

}

int CStandardCommandToProtocol::ReqDmc(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.GetDMCValue(m_byBuffer);
	pByte = m_byBuffer;
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );

}

int CStandardCommandToProtocol::LrfReqStatus(CMD cmd, PBYTE pByte)
{
	return 0;
#if 0 //161110 임시 사용 안함
	int  iLen = 0;
	iLen = CProtoInstro::StatusDataRequest(m_byBuffer);
	iLen = m_protoU2srParser.SetWrappingLrfProto(m_byBuffer, iLen, TRUE);
#endif
	//  [9/10/2014 Yeun] //SetSentReqCmd(cmd.iCmd);

	////m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, FALSE, 2 );//전송시 딜레이를 줌(전송을 늦게함)
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, FALSE, 10 );		
}
int CStandardCommandToProtocol::LrfReqRangeGate(CMD cmd, PBYTE pByte)
{
	return 0;
#if 0 //161110 임시 사용 안함
	int  iLen = 0;
	iLen = CProtoInstro::GetRangeGate(m_byBuffer);
	iLen = m_protoU2srParser.SetWrappingLrfProto(m_byBuffer, iLen, TRUE);
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen, TRUE, FALSE, 10 );
#endif
}
int CStandardCommandToProtocol::LrfReqDistance(CMD cmd, PBYTE pByte)
{
	return 0;
#if 0 //161110 임시 사용 안함
	int  iLen = 0;
	switch (m_iProtoLrf)
	{
	case LRF_ZEISS:
	{
		iLen = m_protoU2srParser.ReqLrfDistance(m_byBuffer);
		//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
	}
	break;
	case LRF_INSTRO:
	{
		/*
		byte byBuffer[] = {'v', 'e', 'r', 0x0d};
		//m_pMultiPortComm->SendPacket( cmd.iChIndex, byBuffer, 4 );
		Sleep(1);
		*/

#if 0

		iLen = CProtoInstro::StanbyModeIntoLowPowerMode(m_byBuffer);
		iLen = m_protoU2srParser.SetWrappingLrfProto(m_byBuffer, iLen, TRUE);
		//SetSentReqCmd(cmd.iCmd);
		//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );			
#endif


		//Sleep(1);

#if 1
		iLen = CProtoInstro::LowPowerModeIntoStanbyMode(m_byBuffer);
		iLen = m_protoU2srParser.SetWrappingLrfProto(m_byBuffer, iLen, TRUE);
		//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
		//  [9/10/2014 Yeun] //SetSentReqCmd(cmd.iCmd);

#endif

#if 1
		iLen = CProtoInstro::MeasureRangeRequest(m_byBuffer);
		// iLen = CProtoInstro::StatusDataRequest( m_byBuffer );			
		iLen = m_protoU2srParser.SetWrappingLrfProto(m_byBuffer, iLen, TRUE);
		//  [9/10/2014 Yeun] //SetSentReqCmd(cmd.iCmd);
		//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );
#endif

#if 0			
		iLen = CProtoInstro::StatusDataRequest(m_byBuffer);
		iLen = m_protoU2srParser.SetWrappingLrfProto(m_byBuffer, iLen, TRUE);
		//SetSentReqCmd(cmd.iCmd);
		//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );			
		//Sleep(100);
#endif		
		//			Sleep(1);

	}
	break;
	default:
		return;
	}
#endif

}

int CStandardCommandToProtocol::LrfMoveRight(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.LRFMoveRight(m_byBuffer);
	pByte = m_byBuffer;
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );

}

int CStandardCommandToProtocol::LrfMoveLeft(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.LRFMoveLeft(m_byBuffer);
	pByte = m_byBuffer;
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );

}

int CStandardCommandToProtocol::LrfMoveUp(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.LRFMoveUp(m_byBuffer);
	pByte = m_byBuffer;
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );

}

int CStandardCommandToProtocol::LrfMoveDown(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.LRFMoveDown(m_byBuffer);
	pByte = m_byBuffer;
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );

}

int CStandardCommandToProtocol::LrfMoveStop(CMD cmd, PBYTE pByte)
{
	int  iLen = m_protoU2srParser.LRFMoveStop(m_byBuffer);
	pByte = m_byBuffer;
	return iLen;
	//m_pMultiPortComm->SendPacket( cmd.iChIndex, m_byBuffer, iLen );

}
//////////////////////////////////////////////////////////////////////////
int CStandardCommandToProtocol::PresetTour(CMD cmd, PBYTE pByte)
{
	return 0;
#if 0
	if (cmd.pVoid != NULL)
		m_pArrAutoMoveManager[cmd.iChIndex]->BeginPreset(
			*(PRESETDATALIST*)cmd.pVoid, cmd.dArrParam[0]);
#endif
}
int CStandardCommandToProtocol::PresetStop(CMD cmd, PBYTE pByte)
{
	return 0;
#if 0
	m_pArrAutoMoveManager[cmd.iChIndex]->StopPreset();
#endif
}
int CStandardCommandToProtocol::PanTiltInit(CMD cmd, PBYTE pByte)
{
#if 0
	m_pArrAutoMoveManager[cmd.iChIndex]->InitializePanTilt();
#endif

	return 0;
}



int CStandardCommandToProtocol::StdCmdToProtocolPacket(CMD cmd, PBYTE pByte)
{
#if 1
	if (m_FuncPtrArr[cmd.iCmd] != NULL)
	{
		int nProtocolSize = (this->*m_FuncPtrArr[cmd.iCmd])(cmd, pByte);
		return nProtocolSize;
	}
	else
		ASSERT(FALSE);
#endif
	return FALSE;
}

#if 0
BOOL CStandardCommandToProtocol::CloseComm(int iChIdx)
{
	return //m_pMultiPortComm->ClosePort( iChIdx );
}
#endif

