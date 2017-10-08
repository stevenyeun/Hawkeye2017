#ifndef MULTISENSORCOMM_H
#define MULTISENSORCOMM_H



#define PANTILT_REQ_CMD 0

#define PANTILT_CTL_CMD 20

#define PANTILT_SETUP_CMD 40

#define PWR_CTL_CMD	50

#define CH_CTL_CMD 60

#define HIGHCAM_CTL_CMD 70
#define LOWCAM_CTL_CMD 90
#define THERMCAM_CTL_CMD 110

#define LRF_CTL_CMD 140

#define ETC_CTL_CMD 170

//req
#define PANTILT_REQ_CUR_POS1				PANTILT_REQ_CMD+1//수신측에서 계속 요청하게 하는 명령(정지명령시중단)
#define PANTILT_REQ_CUR_POS2				PANTILT_REQ_CMD+2//1회 요청 스레드에서 사용
/*#define PANTILT_REQ_CUR_ALLSTATUS			PANTILT_REQ_CMD+3*/ //별도로 전송하기 위해 두개로 분리함
#define PANTILT_REQ_CUR_PANSTATUS			PANTILT_REQ_CMD+4
#define PANTILT_REQ_CUR_TILTSTATUS			PANTILT_REQ_CMD+5
#define PANTILT_REQ_HOMESTATUS				PANTILT_REQ_CMD+6

//basic
#define PANTILT_MOVE_LEFT					PANTILT_CTL_CMD+1
#define PANTILT_MOVE_RIGHT					PANTILT_CTL_CMD+2
#define PANTILT_MOVE_UP						PANTILT_CTL_CMD+3
#define PANTILT_MOVE_DOWN					PANTILT_CTL_CMD+4

#define PANTILT_QUIT_LEFT					PANTILT_CTL_CMD+5
#define PANTILT_QUIT_RIGHT					PANTILT_CTL_CMD+6
#define PANTILT_QUIT_UP						PANTILT_CTL_CMD+7
#define PANTILT_QUIT_DOWN					PANTILT_CTL_CMD+8

//preset setting
#define PANTILT_PRESET_SET					PANTILT_CTL_CMD+9
#define PANTILT_PRESET_LINK 				PANTILT_CTL_CMD+10
#define PANTILT_PRESET_SYNC 				PANTILT_CTL_CMD+11
#define PANTILT_PRESET_MOVE 				PANTILT_CTL_CMD+12

#define PANTILT_PRESET_TOUR 				PANTILT_CTL_CMD+13
#define PANTILT_PRESET_STOP 				PANTILT_CTL_CMD+14

//Util
#define PANTILT_MOVE_HOME 					PANTILT_CTL_CMD+15
#define PANTILT_INIT						PANTILT_CTL_CMD+16

#define PANTILT_PRESET_GET	 				PANTILT_CTL_CMD+17

//setup
#define PANTILT_SPD							PANTILT_SETUP_CMD+1
#define PANTILT_PRESET_SPD					PANTILT_SETUP_CMD+2



//Power Control
#define PWR_ON								PWR_CTL_CMD+1
#define PWR_OFF 							PWR_CTL_CMD+2
#define PWR_REQ_STATUS						PWR_CTL_CMD+3

//Channel Ctl

#define CH1_CAM1							CH_CTL_CMD+1
#define CH1_CAM2							CH_CTL_CMD+2
#define CH1_CAM3							CH_CTL_CMD+3


#define CH2_CAM1							CH_CTL_CMD+4
#define CH2_CAM2							CH_CTL_CMD+5
#define CH2_CAM3							CH_CTL_CMD+6

#define CH1_X								CH_CTL_CMD+7//yeun20150129

#if 0
//Camera Control

#define PWR_ON								PWR_CTL_CMD+1
#define PWR_OFF 							PWR_CTL_CMD+2
#define PWR_REQ_STATUS						PWR_CTL_CMD+3
#endif

#define HIGHCAM_ZOOM_TELE					HIGHCAM_CTL_CMD+1
#define HIGHCAM_ZOOM_WIDE					HIGHCAM_CTL_CMD+2
#define HIGHCAM_ZOOM_STOP					HIGHCAM_CTL_CMD+3

#define HIGHCAM_FOCUS_NEAR					HIGHCAM_CTL_CMD+4
#define HIGHCAM_FOCUS_FAR					HIGHCAM_CTL_CMD+5
#define HIGHCAM_FOCUS_STOP					HIGHCAM_CTL_CMD+6
#define HIGHCAM_REQ_CUR_ZFPOS				HIGHCAM_CTL_CMD+7

#define HIGHCAM_MENU_OPEN					HIGHCAM_CTL_CMD+8
#define HIGHCAM_MENU_ENTER					HIGHCAM_CTL_CMD+9
#define HIGHCAM_MENU_LEFT					HIGHCAM_CTL_CMD+10
#define HIGHCAM_MENU_RIGHT					HIGHCAM_CTL_CMD+11
#define HIGHCAM_MENU_UP						HIGHCAM_CTL_CMD+12
#define HIGHCAM_MENU_DOWN					HIGHCAM_CTL_CMD+13

#define HIGHCAM_ZOOM_SPD					HIGHCAM_CTL_CMD+14
#define HIGHCAM_FOCUS_SPD					HIGHCAM_CTL_CMD+15

#define HIGHCAM_AUTOFOCUS					HIGHCAM_CTL_CMD+16

#define HIGHCAM_LENSFILTER					HIGHCAM_CTL_CMD+17

#define HIGHCAM_COLORMODE					HIGHCAM_CTL_CMD+18

#define HIGHCAM_EXTENDER					HIGHCAM_CTL_CMD+19
#define HIGHCAM_IRIS						HIGHCAM_CTL_CMD+20



#define LOWCAM_ZOOM_TELE					LOWCAM_CTL_CMD+1
#define LOWCAM_ZOOM_WIDE					LOWCAM_CTL_CMD+2
#define LOWCAM_ZOOM_STOP					LOWCAM_CTL_CMD+3

#define LOWCAM_FOCUS_NEAR					LOWCAM_CTL_CMD+4
#define LOWCAM_FOCUS_FAR					LOWCAM_CTL_CMD+5
#define LOWCAM_FOCUS_STOP					LOWCAM_CTL_CMD+6
#define LOWCAM_ABSZOOM_MOVE					LOWCAM_CTL_CMD+7

#define LOWCAM_MENU_OPEN					LOWCAM_CTL_CMD+8
#define LOWCAM_MENU_ENTER					LOWCAM_CTL_CMD+9
#define LOWCAM_MENU_LEFT					LOWCAM_CTL_CMD+10
#define LOWCAM_MENU_RIGHT					LOWCAM_CTL_CMD+11
#define LOWCAM_MENU_UP						LOWCAM_CTL_CMD+12
#define LOWCAM_MENU_DOWN					LOWCAM_CTL_CMD+13


#define THERMCAM_ZOOM_TELE					THERMCAM_CTL_CMD+1
#define THERMCAM_ZOOM_WIDE					THERMCAM_CTL_CMD+2
#define THERMCAM_ZOOM_STOP					THERMCAM_CTL_CMD+3

#define THERMCAM_FOCUS_NEAR					THERMCAM_CTL_CMD+4
#define THERMCAM_FOCUS_FAR					THERMCAM_CTL_CMD+5
#define THERMCAM_FOCUS_STOP					THERMCAM_CTL_CMD+6
#define THERMCAM_FOCUS_AUTO					THERMCAM_CTL_CMD+7

#define THERMCAM_SET_PWR					THERMCAM_CTL_CMD+8


#define THERMCAM_REQ_DZOOM					THERMCAM_CTL_CMD+9
#define THERMCAM_SET_DZOOM					THERMCAM_CTL_CMD+10

#define THERMCAM_REQ_POLARITY				THERMCAM_CTL_CMD+11
#define THERMCAM_SET_WHITEHOT				THERMCAM_CTL_CMD+12
#define THERMCAM_SET_BLACKHOT				THERMCAM_CTL_CMD+14

#define THERMCAM_SET_DDEMODE				THERMCAM_CTL_CMD+15
#define THERMCAM_SET_DDETHRESHOLD			THERMCAM_CTL_CMD+16
#define THERMCAM_SET_DDEGAIN				THERMCAM_CTL_CMD+17

#define THERMCAM_FOCUS_NEARFINE				THERMCAM_CTL_CMD+18
#define THERMCAM_FOCUS_FARFINE				THERMCAM_CTL_CMD+19

#define THERMCAM_AUTO_BRI_ON				THERMCAM_CTL_CMD+20
#define THERMCAM_AUTO_CON_ON				THERMCAM_CTL_CMD+21
#define THERMCAM_SET_BRI					THERMCAM_CTL_CMD+22
#define THERMCAM_SET_CON					THERMCAM_CTL_CMD+23
#define THERMCAM_REQ_BRI					THERMCAM_CTL_CMD+24
#define THERMCAM_REQ_CON					THERMCAM_CTL_CMD+25
#define THERMCAM_SET_COLOR					THERMCAM_CTL_CMD+26

#define THERMCAM_GET_PWR					THERMCAM_CTL_CMD+27

#define THERMCAM_SET_AGCMODE				THERMCAM_CTL_CMD+28

#define LRF_PWR_ON							LRF_CTL_CMD+1
#define LRF_PWR_OFF							LRF_CTL_CMD+2
#define LRF_PT_LEFT							LRF_CTL_CMD+3
#define LRF_PT_RIGHT						LRF_CTL_CMD+4
#define LRF_PT_UP							LRF_CTL_CMD+5
#define LRF_PT_DOWN							LRF_CTL_CMD+6
#define LRF_PT_STOP							LRF_CTL_CMD+7
#define LRF_SHOT							LRF_CTL_CMD+8
//-
#define LRF_STATUS							LRF_CTL_CMD+9//  [9/5/2014 Yeun] Instro LRF
#define LRF_LOWPWR_INTO_STANBY				LRF_CTL_CMD+10//  [9/5/2014 Yeun] Instro LRF
#define LRF_GET_RANGE_GATE					LRF_CTL_CMD+11//  [9/10/2014 Yeun] Instro LRF

#define GPS_REQ_VAL							ETC_CTL_CMD+1
#define MAINBOARD_REQ_VER					ETC_CTL_CMD+2
#define DMC_REQ_VAL							ETC_CTL_CMD+3 



#endif
