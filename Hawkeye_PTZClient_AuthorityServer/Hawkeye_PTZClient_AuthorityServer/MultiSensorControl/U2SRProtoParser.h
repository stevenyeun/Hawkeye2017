#pragma once



#define PROTO_BUFFER_SIZE		128

#define PROTO_CHAR_FINISH		0x0D
#define __PCF__					PROTO_CHAR_FINISH

#define PROTO_HEADER_SIZE		0
#define __PHS__					PROTO_HEADER_SIZE

#define PROTO_TAIL_SIZE			1
#define __PTS__					PROTO_TAIL_SIZE

////////////////////////////////////////////////////////////////////////////////
// I. 개요
////////////////////////////////////////////////////////////////////////////////
//
// 1. 설정
//     9600 bit/sec
//     data= 8
//     parity = none
//     stop = 1
//     flow control = none
//
// 2. 명령 
//     보내는 명령의 끝에 0x0D를 붙여야 됨.
//     리턴값이 2바이트 이상인 경우 끝에 0x0D가 붙음.
//
// 3. 주의사항
//     리턴되는 값들은 모두 ASCII 문자임(숫자 아님)
//
//** PCB BOARD INIT **
//** Memory : use HyperTerminal "mem" or use hardware 'cpu dipswitch'
//** Mortor : use HyperTerminal "init"
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// II. 문자값 / 초기값 등
////////////////////////////////////////////////////////////////////////////////

#define CST_UNKNOWN_CHR				'#'				// no response
#define CST_UNKNOWN_INT				-1				// no response
#define CST_TIME_OUT				'9'				// serial time out

#define CST_CMD_OK					'0'				// command success
#define CST_CMD_FALSE				'1'				// command fail

#define CST_CH1						'1'				// 채널1
#define CST_CH2						'2'				// 채널2

#define CST_CAM_M					'M'				// 고배율
#define CST_CAM_A					'A'				// 저배율
#define CST_CAM_R					'R'				// 열영상
#define CST_CAM_X					'X'				// 연결안됨

#define CST_SPEED_H					'H'				// 고속
#define CST_SPEED_M					'M'				// 중속
#define CST_SPEED_L					'L'				// 저속
#define CST_SPEED_T					'T'				// auto tracking

#define CST_FOCUS_LIMIT_OUT			'O'				// out limit
#define CST_FOCUS_LIMIT_IN			'I'				// in limit
#define CST_FOCUS_LIMIT_UNLIMIT		'?'				// un-limit

#define CST_ZOOM_LIMIT_TELE			'T'				// tele limit
#define CST_ZOOM_LIMIT_WIDE			'W'				// wide limit
#define CST_ZOOM_LIMIT_UNLIMIT		'?'				// un-limit

#define CST_POWER_ON				'O'				// power on
#define CST_POWER_OFF				'F'				// power off

#define CST_POINT_HOME_BEG_PAN		'P'				// pan home 시작
#define CST_POINT_HOME_BEG_TILT		'T'				// titl home 시작
#define CST_POINT_HOME_END			'0'				// pan/titl home 끝
#define CST_POINT_HOME_FAIL			'1'				// pan/tilt home fail

////////////////////////////////////////////////////

//#define CST_DEF_ANGLE_SPEED_H_MAX	1000			// 1200넘으면 장치 죽습니다!!
#define CST_DEF_ANGLE_SPEED_H_MAX	800			// 20071207 ikson
#define CST_DEF_ANGLE_SPEED_CI_INIT 800			// 20071210 hschoi   CI 시에 PAN 속도
#define CST_DEF_ANGLE_SPEED_H_DEF	700				// 바꾸지 마세요. 초기화에서 사용.
#define CST_DEF_ANGLE_SPEED_H_REG	550				// 바꾸지 마세요. 표적이동에서 사용.
#define CST_DEF_ANGLE_SPEED_H_MIN	501

#define CST_DEF_ANGLE_SPEED_M_MAX	500
#define CST_DEF_ANGLE_SPEED_M_DEF	200
#define CST_DEF_ANGLE_SPEED_M_REG	101
#define CST_DEF_ANGLE_SPEED_M_MIN	101

#define CST_DEF_ANGLE_SPEED_L_MAX	100
#define CST_DEF_ANGLE_SPEED_L_DEF	40
#define CST_DEF_ANGLE_SPEED_L_REG	10				// 바꾸지 마세요. 표적이동에서 사용.
#define CST_DEF_ANGLE_SPEED_L_MIN	2

//#define CST_DEF_ZF_SPEED_H_MAX		99
//#define CST_DEF_ZF_SPEED_H_REG		90
//#define CST_DEF_ZF_SPEED_H_MIN		67

//#define CST_DEF_ZF_SPEED_M_MAX		66
//#define CST_DEF_ZF_SPEED_M_REG		50
//#define CST_DEF_ZF_SPEED_M_MIN		34

//#define CST_DEF_ZF_SPEED_L_MAX		33
//#define CST_DEF_ZF_SPEED_L_REG		10
//#define CST_DEF_ZF_SPEED_L_MIN		1

//20071207 ikson------------------------------
#define CST_DEF_ZF_SPEED_H_MAX		180
#define CST_DEF_ZF_SPEED_H_REG		160
#define CST_DEF_ZF_SPEED_H_MIN		100

#define CST_DEF_ZF_SPEED_M_MAX		99
#define CST_DEF_ZF_SPEED_M_REG		80
#define CST_DEF_ZF_SPEED_M_MIN		51

#define CST_DEF_ZF_SPEED_L_MAX		50
#define CST_DEF_ZF_SPEED_L_REG		10
#define CST_DEF_ZF_SPEED_L_MIN		1
//20071207 ikson------------------------------




#define CST_DEF_ZOOM_PMETER_MAX		1023
#define CST_DEF_FOCUS_PMETER_MAX	1023

#define CST_DEF_BROAD_ID			"sniper"
#define CST_DEF_BROAD_PWD			"sniper"

////////////////////////////////////////////////////

#define CST_ERR_DMC					361
#define CST_ERR_GPS					"000000.000,0000.0000,?,00000.0000,?"
#define CST_ERR_PAN					"000.0000"
#define CST_ERR_TILT				"+00.0000"
#define CST_ERR_FOCUS				"00000"
#define CST_ERR_ZOOM				"00000"
#define CST_ERR_PMETER				"0000,0000"
#define CST_ERR_PMETER0				"0000"
#define CST_ERR_ANGLE				"000.0000 +00.0000 00000 00000"

////////////////////////////////////////////////////

#define CST_POS_PAN					( 0)
#define CST_POS_TILT				( 9)
#define CST_POS_FOCUS				(18)
#define CST_POS_ZOOM				(24)

#define CST_LEN_DMC					( 3)
#define CST_LEN_GPS					(74)
#define CST_LEN_PAN					( 8)
#define CST_LEN_TILT				( 8)
#define CST_LEN_FOCUS				( 5)
#define CST_LEN_ZOOM				( 5)
#define CST_LEN_PMETER				( 9)
#define CST_LEN_PMETER0				( 4)
#define CST_LEN_ANGLE				(8+1+8+1+5)	// 29
//#define CST_LEN_ANGLE				(8+1+8+1+5+1+1)	// 26

////////////////////////////////////////////////////

#define CST_STR_ANGLE_PANB(csA)		(csA.Right(CST_LEN_ANGLE-CST_POS_TILT))
#define CST_STR_ANGLE_PAN(csA)		(csA.Mid(CST_POS_PAN  , CST_LEN_PAN  ))
#define CST_STR_ANGLE_TILT(csA)		(csA.Mid(CST_POS_TILT , CST_LEN_TILT ))
#define CST_STR_ANGLE_FOCUS(csA)	(csA.Mid(CST_POS_FOCUS, CST_LEN_FOCUS))
#define CST_STR_ANGLE_ZOOM(csA)		(csA.Mid(CST_POS_ZOOM , CST_LEN_ZOOM ))

////////////////////////////////////////////////////////////////////////////////
// III. 명령셑 정의
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// 3-1. Pan/Tilt Motor Speed Step 설정

	//   [RS=nnnn]     set speed of 표적이동 				range=[1000] ~ [501]  default=550  hschoi
#define CMD_SET_ANGLE_SPEED_FOR_S		_T("RS=%04d")
	//   [RH=nnnn]     set speed of 고속모드				range=[2000] ~ [501]  default=1200
#define CMD_SET_ANGLE_SPEED_FOR_H		_T("RH=%04d")
	//   [RM=nnn]      set speed of 중속모드				range=[500]  ~ [101]  default=200
#define CMD_SET_ANGLE_SPEED_FOR_M		_T("RM=%03d")
	//   [RL=nn]       set speed of 저속모드				range=[100]  ~ [2]    default=40
#define CMD_SET_ANGLE_SPEED_FOR_L		_T("RL=%02d")

//   [RS=nnnn]     set speed of 표적이동 					range=[1000] ~ [501]  default=550  hschoi
#define CMD_SET_ANGLE_PRESETSPEED_FOR		_T("RP=%04d")

	//   [RH=?]        get speed of 고속모드				return=[1000] ~ [501]   default=550  hschoi
#define CMD_GET_ANGLE_SPEED_FOR_S		_T("RS=?")
	//   [RH=?]        get speed of 고속모드				return=[2000] ~ [501]
#define CMD_GET_ANGLE_SPEED_FOR_H		_T("RH=?")
	//   [RM=?]        get speed of 중속모드				return=[500]  ~ [101]
#define CMD_GET_ANGLE_SPEED_FOR_M		_T("RM=?")
	//   [RL=?]        get speed of 저속모드				return=[100]  ~ [2]
#define CMD_GET_ANGLE_SPEED_FOR_L		_T("RL=?")

	//   [RH]          장치대의 이동속도를 고속모드로 설정
#define CMD_SET_ANGLE_SPEED_H			_T("RH")
	//   [RM]          장치대의 이동속도를 중속모드로 설정
#define CMD_SET_ANGLE_SPEED_M			_T("RM")
	//   [RL]          장치대의 이동속도를 저속모드로 설정
#define CMD_SET_ANGLE_SPEED_L			_T("RL")

	//   [R?]          장치대의 이동속도를 읽기				return=[H],[M],[L],[T]
#define CMD_GET_ANGLE_SPEED_Q			_T("R?")
   
//////////////////////////////////////////////////////////////////////
// 3-2. Pan/Tilt 구동명령

	//   [ML]          장치대가 왼쪽으로 회전 시작      
#define CMD_MOVE_LEFT					_T("ML")
	//   [MR]          장치대가 오른쪽으로 회전 시작    
#define CMD_MOVE_RIGHT					_T("MR")
	//   [QL][QR]      좌,우회전 정지 
#define CMD_QUIT_LEFT					_T("QL")
#define CMD_QUIT_RIGHT					_T("QR")
   
	//   [MU]          장치대가 윗쪽으로 회전 시작
#define CMD_MOVE_UP						_T("MU")
	//   [MD]          장치대가 아래쪽으로 회전 시작
#define CMD_MOVE_DOWN					_T("MD")
	//   [QU][QD]      상,하회전 정지
#define CMD_QUIT_UP						_T("QU")
#define CMD_QUIT_DOWN					_T("QD")

//LRF 모터 조정
#define CMD_MOVE_LRF_UP					_T("Lp=U")
#define CMD_MOVE_LRF_DOWN				_T("Lp=D")
#define CMD_MOVE_LRF_LEFT				_T("Lp=L")
#define CMD_MOVE_LRF_RIGHT				_T("Lp=R")
#define CMD_MOVE_LRF_STOP				_T("Lp=Q")
//LRF 전원 제어
#define CMD_SET_LRFPWR_ON				_T("LP=O")
#define CMD_SET_LRFPWR_OFF				_T("LP=F")
#define CMD_GET_LRFPWR					_T("LP=?")

//HW 필터적용
#define CMD_SET_HIGHCAM_HWFILTER_ON		_T("VF=O")
#define CMD_SET_HIGHCAM_HWFILTER_OFF	_T("VF=F")
#define CMD_GET_HIGHCAM_HWFILTER		_T("VF=?")

//카메라 메뉴제어
#define CMD_HIGHCAMMENU_UP					_T("VM=U")
#define CMD_HIGHCAMMENU_DOWN				_T("VM=D")
#define CMD_HIGHCAMMENU_LEFT				_T("VM=L")
#define CMD_HIGHCAMMENU_RIGHT				_T("VM=R")
#define CMD_HIGHCAMMENU_ENTER				_T("VM=C")
#define CMD_HIGHCAMMENU_OPEN				_T("VM=O")

#define CMD_LOWCAMMENU_UP					_T("AM=U")
#define CMD_LOWCAMMENU_DOWN					_T("AM=D")
#define CMD_LOWCAMMENU_LEFT					_T("AM=L")
#define CMD_LOWCAMMENU_RIGHT				_T("AM=R")
#define CMD_LOWCAMMENU_ENTER				_T("AM=C")
#define CMD_LOWCAMMENU_OPEN					_T("AM=O")

//////////////////////////////////////////////////////////////////////
// 3-3. 현재상태의 방위각/고저각 값 읽기

	//   [GC=P]        현재 관측지점 방위각 읽기			return=[DDD.CCCC]
#define CMD_GET_VAL_P					_T("GC=P")
	//   [GC=T]        현재 관측지점 고저각 읽기			return=[sDD.CCCC]
#define CMD_GET_VAL_T					_T("GC=T")
	//   [GC=F]        현재 관측지점 초점 상대위치값 읽기	return=[FFFFF]			// 모터 값.
#define CMD_GET_VAL_F					_T("GC=F")
	//   [GC=Z]        현재 관측지점 줌 상대위치값 읽기		return=[ZZZZZ]			// 모터 값.
#define CMD_GET_VAL_Z					_T("GC=Z")

	//   [GC=C]        현재 관측지점 DMC값 읽기				return [DDD]
#define CMD_GET_VAL_DMC					_T("GC=C")
	//   [GC=G]        현재 관측지점 GPS값 읽기				return=[000618.980,0000.0000,N,00000.0000,E]
#define CMD_GET_VAL_GPS					_T("GC=G")

	//   [GC=M]        현재 고배율 절대위치값 읽기			return=[FFFF,ZZZZ]		// potentio-meter 값.
#define CMD_GET_PMETER_M				_T("GC=M")
	//   [GC=A]        현재 저배율 절대위치값 읽기			return=[FFFF,ZZZZ]		// potentio-meter 값.
#define CMD_GET_PMETER_A				_T("GC=A")

	//   [GC=L]        현재 방위각, 고저각, 초점값, 줌값	return=[DDD.CCCC,sDD.CCCC,FFFFF,ZZZZZ]
#define CMD_GET_ANGLE					_T("GC=L")
#define CMD_GET_ANGLE_F_Z				_T("GC")

//** 방위각, 고저각, 초점모터값, 줌모터값은 전원을 OFF하여도 값을 유지하고 있음

//////////////////////////////////////////////////////////////////////
// 3-4. BIT용 상태표시

	//   [GS=P]        현재 방위각 모터 상태 읽기			return=[HH]
#define CMD_GET_STATUS_P				_T("GS=P")
	//   [GS=T]        현재 고저각 모터 상태 읽기			return=[hh]
#define CMD_GET_STATUS_T				_T("GS=T")

	//   [GS=M]        현재 고배율 상태 읽기				return=[hh]
#define CMD_GET_STATUS_M				_T("GS=M")
	//   [GS=A]        현재 저배율 상태 읽기				return=[hh]
#define CMD_GET_STATUS_A				_T("GS=A")

//** 리턴값은 1바이트 unsigned char를 hexa string으로 변환한 것임
//** 자세한 사항은 문서 참조

//////////////////////////////////////////////////////////////////////
// 3-5. Video Control

	//   [VO=1]       주영상을 CH1에 연결, 보조영상은 자동을 CH2에 연결
#define CMD_SET_VO_V1C1					_T("VO=1")
	//   [VO=2]       주영상을 CH2에 연결, 보조영상은 자동을 CH1에 연결  
#define CMD_SET_VO_V1C2					_T("VO=2")
	//	 [VO=?]       주영상 연결상태 읽기					return = [1]:CH1, [2]:CH2 
#define CMD_GET_VO_V1CQ					_T("VO=?")

#if 0
	//   [VM=S]       고배율 영상 = 주간카메라 연결
#define CMD_SET_VM_S					"VM=S"
	//   [VM=D]       고배율 영상 = 야간카메라 연결
#define CMD_SET_VM_D					"VM=D"
	//   [VM=?]       고배율 연결상태 읽기					return = [S]:주간카메라, [D]:야간카메라  
#define CMD_GET_VM_Q					"VM=?"
#else//  [8/19/2014 Yeun] 
//   [VM=S]       고배율 영상 = 컬러모드
#define CMD_SET_VM_S					_T("VS=C")
//   [VM=D]       고배율 영상 = B/W모드
#define CMD_SET_VM_D					_T("VS=B")
//   [VM=?]       고배율 연결상태 읽기					return=[VS=C],[VS=B]
#define CMD_GET_VM_Q					_T("VS=?")

#endif

	//   [VA=S]       저배율 영상 = 주간카메라 연결
#define CMD_SET_VA_S					_T("VA=S")
	//   [VA=D]       저배율 영상 = 야간카메라 연결
#define CMD_SET_VA_D					_T("VA=D")
	//   [VA=?]       저배율 연결상태 읽기					return = [S]:주간카메라, [D]:야간카메라   
#define CMD_GET_VA_Q					_T("VA=?")

	//   [V1=M]        주영상 = 고배율에 연결 
#define CMD_SET_V1_M					_T("V1=M")
	//   [V1=A]        주영상 = 저배율(주간)에 연결
#define CMD_SET_V1_A					_T("V1=A")
	//   [V1=R]        주영상 = 열영상에 연결
#define CMD_SET_V1_R					_T("V1=T")
	//   [V1=X]        주영상 = 연결해제
#define CMD_SET_V1_X					_T("V1=X")
	//   [V1=?]        주영상 연결상태 읽기					return = [M]:고배율, [A]:저배율, [R]:열영상, [X]:연결안됨.
#define CMD_GET_V1_Q					_T("V1=?")

	//   [V2=M]        보조영상 = 고배율에 연결 
#define CMD_SET_V2_M					_T("V2=M")
	//   [V2=A]        보조영상 = 저배율에 연결 
#define CMD_SET_V2_A					_T("V2=A")
	//   [V2=R]        보조영상 = 열영상에 연결
#define CMD_SET_V2_R					_T("V2=T")
	//   [V2=X]        보조영상 = 연결해제
#define CMD_SET_V2_X					_T("V2=X")
	//   [V2=?]        보조영상 연결상태 읽기				return = [M]:고배율, [A]:저배율, [R]:열영상, [X]:연결안됨.
#define CMD_GET_V2_Q					_T("V2=?")

//////////////////////////////////////////////////////////////////////
// 3-6. 고배율 Lense control

	//   [Fi]          start focus in  
#define CMD_M_LENSE_FOCUS_IN			_T("Fi")
	//   [Fo]          start focus out 
#define CMD_M_LENSE_FOCUS_OUT			_T("Fo")
	//   [Fq]          stop focus
#define CMD_M_LENSE_FOCUS_STOP			_T("Fq")

	//   [Fa=?]        get absolute focus position			return=[F]~[FFFF]
#define CMD_M_LENSE_GET_FOCUS_PMETER	_T("Fa=?")

	//   [Fr=FFFFF]    move relative focus  
#define CMD_M_LENSE_MOVE_FOCUS			_T("Fr=%05d")
	//   [Fa=FFFF]    move potential focus  
#define CMD_M_LENSE_MOVE_PFOCUS			_T("Fa=%04d")
	//   [Fr=?]        get relative focus position			return=[FFFFF]
#define CMD_M_LENSE_GET_FOCUS			_T("Fr=?")

	//   [FS=nn]       set focus speed						range=[01]~[99] 
//#define CMD_M_LENSE_SET_FOCUS_SPEED		"FS=%02d"
//#define CMD_M_LENSE_SET_FOCUS_SPEED		"FS=%03d"//20071208 ikson
#define CMD_M_LENSE_SET_FOCUS_SPEED		_T("FS=%03d\r")//  [4/10/2014 Yeun]
	//   [FS=?]        get focus speed						return=[nn]   

#define CMD_M_LENSE_GET_FOCUS_SPEED		_T("FS=?")
 
	//   [FL=?]        get focus limit flag					return=[O]:out limit ,[I]:in limit, [?]:un-limit   
#define CMD_M_LENSE_GET_FOCUS_LIMIT		_T("FL=?")


	//   [Zt]          start zoom tele 
#define CMD_M_LENSE_ZOOM_TELE			_T("Zt")
	//   [Zw]          start zoom wide
#define CMD_M_LENSE_ZOOM_WIDE			_T("Zw")
	//   [Zq]          stop zoom
#define CMD_M_LENSE_ZOOM_STOP			_T("Zq")

	//   [Za=?]        get absolute zoom position			return=[F]~[FFFF]
#define CMD_M_LENSE_GET_ZOOM_PMETER		_T("Za=?")

	//   [Zr=ZZZZZ]    move relative zoom
#define CMD_M_LENSE_MOVE_ZOOM			_T("Zr=%05d")
	//   [Za=ZZZZ]    move potential zoom
#define CMD_M_LENSE_MOVE_PZOOM			_T("Za=%04d")
	//   [Zr=?]        get relative zoom position			return=[ZZZZZ]
#define CMD_M_LENSE_GET_ZOOM			_T("Zr=?")

	//   [ZS=nn]       set zoom speed						range=[01]~[99]  
//#define CMD_M_LENSE_SET_ZOOM_SPEED		"ZS=%02d"
//#define CMD_M_LENSE_SET_ZOOM_SPEED		"ZS=%03d"//20071208 ikson
#define CMD_M_LENSE_SET_ZOOM_SPEED		_T("ZS=%03d\r")//  [4/10/2014 Yeun]
	//   [ZS=?]        get zoom speed						return=[nn]  
#define CMD_M_LENSE_GET_ZOOM_SPEED		_T("ZS=?")

	//   [ZL=?]        get zoom limit flag					return=[T]:tele limit, [W]:wide limit, [?]:un-limit   
#define CMD_M_LENSE_GET_ZOOM_LIMIT		_T("ZL=?")


	//   [Fz=zzzzz,fffff] move relative ZOOM(first) and FOCUS(last)
#define CMD_M_LENSE_MOVE_ZOOM_FOCUS		_T("Fz=%s")				// %s : zzzzz fffff

//** 줌과 포커스는 모터 하나를 공유 -> 줌 이동시키면 포커스도 같이 이동된다.
//   => 때문에 줌을 먼저 이동시킨 후 포커스를 이동시켜야 한다.

//////////////////////////////////////////////////////////////////////
// 3-7. 저배율 Lense control

// 3-7-1. Kowa Zoom Lense control

	//   [Ei]          start focus in  
#define CMD_A_LENSE_STOP_ZOOM			_T("Aq")
	//   [Ei]          start focus in  
#define CMD_A_LENSE_FOCUS_IN			_T("Ai")
	//   [Eo]           start focus out 
#define CMD_A_LENSE_FOCUS_OUT			_T("Ao")

	//   [Et]          start zoom tele
#define CMD_A_LENSE_ZOOM_TELE			_T("At")
	//   [Ew]          start zoom wide 
#define CMD_A_LENSE_ZOOM_WIDE			_T("Aw")

	//   [Eq]          stop focus/zoom
#define CMD_A_LENSE_STOP_FOCUS_ZOOM		_T("Aq")

	//   [Ep]          stop zoom
#define CMD_A_LENSE_STOP_ZOOM			_T("Aq")


	//   [Ef=FFFF]     move absolute focus  
#define CMD_A_LENSE_MOVE_FOCUS			_T("Ef=%04d")
	//	[Ef=?]	       get absolute focus position			return=[FFFF]
#define CMD_A_LENSE_GET_FOCUS_PMETER	_T("Ef=?")

	//   [Ez=ZZZZ]     move absolute zoom
#define CMD_A_LENSE_MOVE_ZOOM			_T("Az=%04d")
	//	[Ez=?]	       get absolute zoom position			return=[ZZZZ]
#define CMD_A_LENSE_GET_ZOOM_PMETER		_T("Ez=?")

	//	[ES=nnn]	   set focus & zoom speed				range=[1]~[100]
#define CMD_A_LENSE_SET_SPEED			_T("ES=%03d")
	//	[ES=?]		   get focus & zoom speed				return=[1]~[100]
#define CMD_A_LENSE_GET_SPEED			_T("ES=?")

// 3-7-2. Samsung Zoom Lense control (SCC-Cxxxx5)

//#define CMD_A_LENSE_FOCUS_IN			"Ei"				// can't use.
//#define CMD_A_LENSE_FOCUS_OUT			"Eo"				// can't use.
//#define CMD_A_LENSE_ZOOM_TELE			"Et"				// can use.
//#define CMD_A_LENSE_ZOOM_WIDE			"Ew"				// can use.
//#define CMD_A_LENSE_STOP_FOCUS_ZOOM	"Eq"				// can use.

	//	[EC=cmd]	   bypass camera command				// see camera manual for [cmd] & [return] value.
#define CMD_A_LENSE_BYPASS_CMD			_T("EC=")

//** 저배율 카메라를 삼성카메라를 사용하면서 Kowa 명령은 사용 못함.
//** [EC=cmd]를 사용하면 PCB는 카메라 명령 bypass 해줌.

//////////////////////////////////////////////////////////////////////
//열영상 렌즈 전압제어
#define CMD_T_LENSE_FOCUS_NEAR			_T("Ti")
#define CMD_T_LENSE_FOCUS_FAR			_T("To")
#define CMD_T_LENSE_FOCUS_STOP			_T("Tq")

//////////////////////////////////////////////////////////////////////////
// 3-8. 열영상 Camera control TR-3600

#define CMD_T_LENSE_FOCUS_AUTO			_T("TC=S:610D")	// b

#define CMD_T_LENSE_FOCUS_IN			_T("TC=S:620D")	// b
#define CMD_T_LENSE_FOCUS_OUT			_T("TC=S:660D")	// f

#define CMD_T_LENSE_FOCUS_FINE_IN		_T("TC=S:420D")	// B
#define CMD_T_LENSE_FOCUS_FINE_OUT		_T("TC=S:460D")	// F

#define CMD_T_LENSE_ZOOM_1				_T("TC=S:6E207A6F6D20310D")			// n zom 1
#define CMD_T_LENSE_ZOOM_2				_T("TC=S:6E207A6F6D20320D")			// n zom 2
#define CMD_T_LENSE_ZOOM_4				_T("TC=S:6E207A6F6D20340D")			// n zom 4
#define CMD_T_LENSE_ZOOM_GET			_T("TC=?:6E207A6F6D0D")				// n zom


#define CMD_T_LENSE_AUTO_BRIGHT_ON		_T("TC=S:6E2061627274206F6E0D")		// n abrt on
#define CMD_T_LENSE_AUTO_CONTRAST_ON	_T("TC=S:6E2061636E74206F6E0D")		// n acnt on
#define CMD_T_LENSE_AUTO_NUCMODE_ON		_T("TC=S:6E206166706E206F6E0D")		// n afpn on
#define CMD_T_LENSE_AUTO_NUCMODE_OFF	_T("TC=S:6E206166706E206F66660D")	// n afpn off
#define CMD_T_LENSE_POL_BW				_T("TC=S:6E20706F6C2062770D")		// n pol bw
#define CMD_T_LENSE_POL_WB				_T("TC=S:6E20706F6C2077620D")		// n pol wb
#define CMD_T_LENSE_POL_GET				_T("TC=?:6E20706F6C0D")				// n pol
#define CMD_T_LENSE_POWER_ON			_T("TP=O")							// Power On
#define CMD_T_LENSE_POWER_OFF			_T("TP=F")							// Power Off

	//	[TC=cmd]	   bypass camera command				// see camera manual for [cmd] & [return] value.
#define CMD_T_LENSE_BYPASS_CMD			_T("TC=")

//////////////////////////////////////////////////////////////////////
// 3.9 기타 Command

	//   [PW=O]        remote power ON 
#define CMD_POWER_ON					_T("PW=O")
	//   [PW=F]        remote power OFF  
#define CMD_POWER_OFF					_T("PW=F")
	//   [PW=?]        get power flag						return=[O]:on, [F]:off
#define CMD_POWER_Q						_T("PW=?")
  
//////////////////////////////////////////////////////////////////////
// 3.10. Target Preset 및 Auto Focusing 운용
#define CMD_PS_POINT_HOME_PANTILT		_T("HM=C")	
#define CMD_PS_POINT_HOME_QRY			_T("HM=?")				// return=[P]:팬중, [T]:틸트중, [C]:센터이동완료, [O]:기준점이동완료, [X]:동작 없음 	
	//   [PH=T]        Tilt Home 위치로 이동				
#define CMD_PS_POINT_HOME_ZEROPOS		_T("HM=0")	
#define CMD_PS_POINT_SET_ZEROPOS		_T("HP=S")	


	//   [PL=nn]       nn 번호의 좌표를 바로가기로 설정		return=[0]:ok, [1]:false, range=[00]~[99]
#define CMD_PS_POINT_LINK				_T("PL=%03d")
	//   [PS=nn]       nn 번호에 현재 좌표를 저장			return=[0]:ok, [1]:false
#define CMD_PS_POINT_SET				_T("PS=%03d")
	//   [PG=nn]       nn 번호의 좌표를 읽기				return=[DDD.CCCC,sDD.CCCC,FFFFF,ZZZZZ]
#define CMD_PS_POINT_GET				_T("PG=%03d")
	//   [PP=nn:DDD.CCCC,sDD.CCCC,FFFFF,ZZZZZ]
	//				   nn 번호에 지정하는 좌표를 저장		return=[0]:ok, [1]:false                                       
#define CMD_PS_POINT_PUT				_T("PP=%03d:%s")
	//   [PM]          바로가기 실행(방위,고도,줌,초점)		return=[0]:ok, [1]:false
#define CMD_PS_POINT_MOVE				_T("PM")
	//   [PZ]          바로가기 동기화						return=[0]:ok, [1]:좌표 없음, [2]:고도 불가능, [3]:방위/고도 실패, [4]:초점 실패
#define CMD_PS_POINT_ZONE				_T("PZ")
	//   [PR]          최근 운용 좌표. <GC=L과 동일>		return=[DDD.CCCC,sDD.CCCC,FFFFF,ZZZZZ] 
#define CMD_PS_POINT_READ				_T("PR")
	//   [PH=P]        Pan Home 위치로 이동					return=[P]:시작, [0]:끝, [1]:Fail




#define CMD_PS_POINT_HOME_TILT			_T("PH=T")
	//   [CI]          init magnetic compass
#define CMD_COMPASS_INIT				_T("CI")

//** 바로가기 좌표는 NV-RAM에 저장되므로 전원이 OFF되어도 데이타 유지됨
//** [PH=P]을 실행하면 Pan 왼쪽 리미트에서 180도 위치로 이동하고 좌표값을 000.0000으로 초기화
//** [PH=T]을 실행하면 Tilt를 수평으로(기울기 센서 이용) 위치하고 좌표값을 +00.0000으로 초기화
//** 동기화   실행 순서 = [PH=P]->[PH=T]->[zoom]->[focus] => [PP=00:~]->[PL=00]->[PZ]
//** 바로가기 실행 순서 = [PP=nn:~]->[PL=nn]->[PM]

//////////////////////////////////////////////////////////////////////
// 3.11 Target Preset 및 Auto Focusing 응용

	//	[Sp=DDD.CCCC]  바로가기 방위각을 [DDD.CCCC]로 설정	return=[0]:ok, [1]:false
#define CMD_SET_DIRECT_PAN				_T("Sp=%s")
	//	[St=sDD.CCCC]  바로가기 고저각을 [sDD.CCCC]로 설정	return=[0]:ok, [1]:false
#define CMD_SET_DIRECT_TILT				_T("St=%s")
	//	[Sf=FFFFF]     바로가기 초점값을 [FFFFF]로 설정		return=[0]:ok, [1]:false
#define CMD_SET_DIRECT_FOCUS			_T("Sf=%s")
	//	[Sz=ZZZZZ]     바로가기 줌값을  [ZZZZZ]로 설정		return=[0]:ok, [1]:false
#define CMD_SET_DIRECT_ZOOM				_T("Sz=%s")
	//	[Sc]           바로가기 설정지정 좌표값 모두 설정	return=[0]:ok, [1]:false
#define CMD_SET_DIRECT_ALL				_T("Sc=%s")

	//	[Gp]            바로가기 방위각 읽기				return=[DDD.CCCC]
#define CMD_GET_DIRECT_PAN				_T("Gp")
	//	[Gt]            바로가기 고저각 읽기				return=[sDD.CCCC]
#define CMD_GET_DIRECT_TILT				_T("Gt")
	//	[Gf]          바로가기 초점값 읽기					return=[FFFFF]
#define CMD_GET_DIRECT_FOCUS			_T("Gf")
	//	[Gz]         바로가기 줌값 읽기						return=[ZZZZZ]
#define CMD_GET_DIRECT_ZOOM				_T("Gz")
	//	[Gl]          바로가기 좌표 읽기					return=[DDD.CCCC,sDD.CCCC,FFFFF,ZZZZZ] 
#define CMD_GET_DIRECT_ALL				_T("Gc")

//////////////////////////////////////////////////////////////////////
// 3.12 Auto Tracking 응용

#define CMD_TRACKING_ON					_T("AS")
//						트랙킹 모드 켜기
#define CMD_TRACKING_OFF				_T("AQ")
//						트랙킹 모드 끄기
#define CMD_PAN_MOVEAUTO				_T("AP=%s%03d")
//		[AP=sNNN]		팬 자동 이동.
#define CMD_TILT_MOVEAUTO				_T("AT=%s%03d")
//		[AT=sNNN]		틸트 자동 이동.

#include "U2SRProtoDef.h"

class CU2SRProtoParser
{
public:
	CU2SRProtoParser(void);
	~CU2SRProtoParser(void);
public:
	static int m_iDZoom;
	static void SetCurDZoom(int iZoom);
	static int GetCurDZoom();
public:
	static int GetCmd(LPBYTE lpData, CString& strParsedCmd);

	int SetWrappingHighProto( BYTE* pbyBuffer, int iSrcLen );//  [4/6/2014 Yeun]
	int SetWrappingThermProto( BYTE* pbyBuffer, int iSrcLen, BOOL bRecv = FALSE );//  [4/6/2014 Yeun]
	int SetWrappingLrfProto( BYTE* pbyBuffer, int iSrcLen, BOOL bRecv = FALSE );//  [4/6/2014 Yeun]

	void FillHeader( BYTE* pbyBuffer );
	int FillTail( BYTE* pbyBuffer, int iDataLen = 0 );

	int SetAnglePresetSpeedVal(BYTE* pbyBuffer, int nSpeed);
	int SetAngleSpeed( BYTE* pbyBuffer, int nSpeed );

	int MoveLeft( BYTE* pbyBuffer );
	int MoveRight( BYTE* pbyBuffer );
	int QuitLeft( BYTE* pbyBuffer );
	int QuitRight( BYTE* pbyBuffer );
	int MoveUp( BYTE* pbyBuffer );
	int MoveDown( BYTE* pbyBuffer );
	int QuitUp( BYTE* pbyBuffer );
	int QuitDown( BYTE* pbyBuffer);
	int LRFMoveLeft( BYTE* pbyBuffer );
	int LRFMoveRight( BYTE* pbyBuffer );
	int LRFMoveUp( BYTE* pbyBuffer );
	int LRFMoveDown( BYTE* pbyBuffer );
	int LRFMoveStop( BYTE* pbyBuffer );
	int GetLRFPwr( BYTE* pbyBuffer );
	int SetLRFPwr(BYTE* pbyBuffer, BOOL bOn);
	int GetHighCamHWFilter( BYTE* pbyBuffer );
	int SetHighCamHWFilter( BYTE* pbyBuffer, BOOL bOn);
	int ReqLrfDistance( BYTE* pbyBuffer );
	UINT ParsingLRFRangeCmd(CString strRecvedCmd);
	int HighCamMenuUp( BYTE* pbyBuffer );
	int HighCamMenuLeft( BYTE* pbyBuffer );
	int HighCamMenuRight( BYTE* pbyBuffer );
	int HighCamMenuEnter( BYTE* pbyBuffer );
	int HighCamMenuOpen( BYTE* pbyBuffer );
	int LowCamMenuUp( BYTE* pbyBuffer );
	int LowCamMenuDown(BYTE* pbyBuffer);
	int LowCamMenuLeft( BYTE* pbyBuffer );
	int LowCamMenuRight( BYTE* pbyBuffer );
	int LowCamMenuEnter( BYTE* pbyBuffer );
	int LowCamMenuOpen( BYTE* pbyBuffer );
	void ConvertByteToHexa(BYTE * pByData, int iLength, CString &strHexa);
	void StringHexaToByteHexa(byte* pSrc, byte* pDest, int iDestLen);
	static void StringHexaToByteHexa(CString strSrc, byte* pDest, int iDestLen);//170423 yeun

	void String2Ascii(char *pArr, CString strSrc, int nLen);
	static BYTE Code2Ascii(char cData);
	static BYTE Code2Ascii(wchar_t cData);
	static BYTE StringHexaToAscii(CString csHexa);
	BYTE StringHexaToAscii_Rev(CString csHexa);
	int PanGetValue( BYTE* pbyBuffer );
	int Com03_TiltGetValue( BYTE* pbyBuffer );
	int GetDMCValue( BYTE* pbyBuffer );
	int GPSGetValue( BYTE* pbyBuffer );
	int MLense_GetPMeter( BYTE* pbyBuffer );
	int AngleGetValue( BYTE* pbyBuffer );
	int PanGetStatus( BYTE* pbyBuffer );
	int TiltGetStatus( BYTE* pbyBuffer );
	int MLense_GetStatus( BYTE* pbyBuffer );
	int ALense_GetStatus( BYTE* pbyBuffer );
	int SetVideoConnect1( BYTE* pbyBuffer );
	int SetVideoConnect2( BYTE* pbyBuffer );
	int GetVideoConnect( BYTE* pbyBuffer );
	int SetHighColor( BYTE* pbyBuffer );
	int SetHighExtender(BYTE* pbyBuffer, BOOL bOn);
	int SetHighIris(BYTE* pbyBuffer, BOOL bOn);
	int SetHighBW( BYTE* pbyBuffer );
	int GetHigh( BYTE* pbyBuffer );
	int SetLowColor( BYTE* pbyBuffer );
	int SetLowBW( BYTE* pbyBuffer );
	int GetLow( BYTE* pbyBuffer );
	int SetCH1High( BYTE* pbyBuffer );
	int SetCH1Low( BYTE* pbyBuffer );
	int SetCH1Thermal( BYTE* pbyBuffer );
	int SetCH1Free( BYTE* pbyBuffer );
	int GetCH1( BYTE* pbyBuffer );
	int SetCH2High( BYTE* pbyBuffer );
	int SetCH2Low( BYTE* pbyBuffer );
	int SetCH2Thermal( BYTE* pbyBuffer );
	int SetCH2Free( BYTE* pbyBuffer );
	int GetCH2( BYTE* pbyBuffer );

	int MLense_AutoFocus(BYTE* pbyBuffer);
	int MLense_LensFilter(BYTE* pbyBuffer, int nFilterNum);

	int MLense_FocusInStart( BYTE* pbyBuffer );
	int MLense_FocusOutStart( BYTE* pbyBuffer );
	int MLense_FocusStop( BYTE* pbyBuffer );
	int MLense_PFocusMoveTo(BYTE* pbyBuffer, int nPosition);
	int MLense_FocusSetSpeed(BYTE* pbyBuffer, int iSpeed);
	int MLense_ZoomTeleStart(BYTE* pbyBuffer);
	int MLense_ZoomWideStart(BYTE* pbyBuffer);
	int MLense_ZoomStop(BYTE* pbyBuffer);
	int MLense_ZoomSetSpeed(BYTE* pbyBuffer, int iSpeed);
	int ALense_FocusInStart( BYTE* pbyBuffer );
	int ALense_FocusOutStart( BYTE* pbyBuffer );
	int ALense_ZoomTeleStart( BYTE* pbyBuffer );
	int ALense_ZoomWideStart( BYTE* pbyBuffer );
	int ALense_ZFStop( BYTE* pbyBuffer );
	int ALense_ZoomMoveTo(BYTE* pbyBuffer, DARR_PARAM dArrParam);
	int ALense_CmdByPass(BYTE* pCmd, int nLen, BYTE* pRecvBuf, int nRecvLen);
	

	int TLense_FocusIn( BYTE* pbyBuffer );
	int TLense_FocusOut( BYTE* pbyBuffer );
	int TLense_FocusStop( BYTE* pbyBuffer );

	int TLense_FocusFineIn( BYTE* pbyBuffer );
	int TLense_FocusFineOut( BYTE* pbyBuffer );

	int TLense_GetDZoom( BYTE* pbyBuffer );	
	int TLense_SetDZoom( BYTE* pbyBuffer, int iDZoom );
	int TLense_ZoomTele( BYTE* pbyBuffer );
	int TLense_ZoomWide( BYTE* pbyBuffer );
	int TLense_ZoomStop( BYTE* pbyBuffer );
	int TLense_GetPolarity( BYTE* pbyBuffer );
	int TLense_Polarity_Change( BYTE* pbyBuffer );
	int TLense_SetPolarity(BYTE* pbyBuffer, int iBlackHot)/* 1-White hot, 0-Black hot */;
	int TLense_Power_ON( BYTE* pbyBuffer );
	int TLense_Power_OFF(BYTE* pbyBuffer);
	int TLense_CmdByPass(BYTE* pCmd, int nLen, BYTE* pRecvBuf, int nRecvLen);

	int PowerOn( BYTE* pbyBuffer );
	int PowerOff( BYTE* pbyBuffer );
	int GetPower( BYTE* pbyBuffer );
	int MovePanTiltHome( BYTE* pbyBuffer );
	int SetPanTiltZeroPos( BYTE* pbyBuffer );
	int ReadPanTiltHome_Status( BYTE* pbyBuffer );
	int MovePanTiltZeroPos( BYTE* pbyBuffer );

	int LinkPreset(BYTE* pbyBuffer, int nPoint);
	int LinkPreset(BYTE* pbyBuffer, DARR_PARAM dArrParam );

	int SetPreset(BYTE* pbyBuffer, int nPoint);
	int GetPreset(BYTE* pbyBuffer, DARR_PARAM dArrParam);
	int PutPreset(BYTE* pbyBuffer, int nPoint, CString strAngle);

	int PutPreset(BYTE* pbyBuffer, DARR_PARAM dArrParam );

	int MovePreset( BYTE* pbyBuffer );
	int SyncPreset( BYTE* pbyBuffer );
	int MoveTiltHome( BYTE* pbyBuffer );
	int GetAngle(BYTE* pbyBuffere);
	int GetAngleFocusZoom( BYTE* pbyBuffer );
	int PresetSync(BYTE* pbyBuffer, CString strAngle, int nPoint);
	int MoveToTarget(BYTE* pbyBuffer, int nPoint);
	int AutoTrackingON( BYTE* pbyBuffer );
	int AutoTrackingOFF( BYTE* pbyBuffer );
	int AutoTILTMove(BYTE* pbyBuffer, int Direction, int Speed);
	int AutoPANMove(BYTE* pbyBuffer, int Direction, int Speed);
	int HighCamMenuDown( BYTE* pbyBuffer );
	int MLense_PZoomMoveTo(BYTE* pbyBuffer, int nPosition);
	int ReqMainBoardVersion(BYTE* pbyBuffer);
	//  [3/14/2014 Yeun] copy
	static CString Util_GetBinaryData(CString csValue);
	static CString Util_ConvertAscii2Hexa(CString csValue);
	static int Util_GetDecimalValue(char c);
	static CString Multi2Wide( char *pszSrc );
	
};