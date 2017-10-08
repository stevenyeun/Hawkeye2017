#pragma once



#define PROTO_BUFFER_SIZE		128

#define PROTO_CHAR_FINISH		0x0D
#define __PCF__					PROTO_CHAR_FINISH

#define PROTO_HEADER_SIZE		0
#define __PHS__					PROTO_HEADER_SIZE

#define PROTO_TAIL_SIZE			1
#define __PTS__					PROTO_TAIL_SIZE

////////////////////////////////////////////////////////////////////////////////
// I. ����
////////////////////////////////////////////////////////////////////////////////
//
// 1. ����
//     9600 bit/sec
//     data= 8
//     parity = none
//     stop = 1
//     flow control = none
//
// 2. ��� 
//     ������ ����� ���� 0x0D�� �ٿ��� ��.
//     ���ϰ��� 2����Ʈ �̻��� ��� ���� 0x0D�� ����.
//
// 3. ���ǻ���
//     ���ϵǴ� ������ ��� ASCII ������(���� �ƴ�)
//
//** PCB BOARD INIT **
//** Memory : use HyperTerminal "mem" or use hardware 'cpu dipswitch'
//** Mortor : use HyperTerminal "init"
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// II. ���ڰ� / �ʱⰪ ��
////////////////////////////////////////////////////////////////////////////////

#define CST_UNKNOWN_CHR				'#'				// no response
#define CST_UNKNOWN_INT				-1				// no response
#define CST_TIME_OUT				'9'				// serial time out

#define CST_CMD_OK					'0'				// command success
#define CST_CMD_FALSE				'1'				// command fail

#define CST_CH1						'1'				// ä��1
#define CST_CH2						'2'				// ä��2

#define CST_CAM_M					'M'				// �����
#define CST_CAM_A					'A'				// ������
#define CST_CAM_R					'R'				// ������
#define CST_CAM_X					'X'				// ����ȵ�

#define CST_SPEED_H					'H'				// ���
#define CST_SPEED_M					'M'				// �߼�
#define CST_SPEED_L					'L'				// ����
#define CST_SPEED_T					'T'				// auto tracking

#define CST_FOCUS_LIMIT_OUT			'O'				// out limit
#define CST_FOCUS_LIMIT_IN			'I'				// in limit
#define CST_FOCUS_LIMIT_UNLIMIT		'?'				// un-limit

#define CST_ZOOM_LIMIT_TELE			'T'				// tele limit
#define CST_ZOOM_LIMIT_WIDE			'W'				// wide limit
#define CST_ZOOM_LIMIT_UNLIMIT		'?'				// un-limit

#define CST_POWER_ON				'O'				// power on
#define CST_POWER_OFF				'F'				// power off

#define CST_POINT_HOME_BEG_PAN		'P'				// pan home ����
#define CST_POINT_HOME_BEG_TILT		'T'				// titl home ����
#define CST_POINT_HOME_END			'0'				// pan/titl home ��
#define CST_POINT_HOME_FAIL			'1'				// pan/tilt home fail

////////////////////////////////////////////////////

//#define CST_DEF_ANGLE_SPEED_H_MAX	1000			// 1200������ ��ġ �׽��ϴ�!!
#define CST_DEF_ANGLE_SPEED_H_MAX	800			// 20071207 ikson
#define CST_DEF_ANGLE_SPEED_CI_INIT 800			// 20071210 hschoi   CI �ÿ� PAN �ӵ�
#define CST_DEF_ANGLE_SPEED_H_DEF	700				// �ٲ��� ������. �ʱ�ȭ���� ���.
#define CST_DEF_ANGLE_SPEED_H_REG	550				// �ٲ��� ������. ǥ���̵����� ���.
#define CST_DEF_ANGLE_SPEED_H_MIN	501

#define CST_DEF_ANGLE_SPEED_M_MAX	500
#define CST_DEF_ANGLE_SPEED_M_DEF	200
#define CST_DEF_ANGLE_SPEED_M_REG	101
#define CST_DEF_ANGLE_SPEED_M_MIN	101

#define CST_DEF_ANGLE_SPEED_L_MAX	100
#define CST_DEF_ANGLE_SPEED_L_DEF	40
#define CST_DEF_ANGLE_SPEED_L_REG	10				// �ٲ��� ������. ǥ���̵����� ���.
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
// III. ��əV ����
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// 3-1. Pan/Tilt Motor Speed Step ����

	//   [RS=nnnn]     set speed of ǥ���̵� 				range=[1000] ~ [501]  default=550  hschoi
#define CMD_SET_ANGLE_SPEED_FOR_S		_T("RS=%04d")
	//   [RH=nnnn]     set speed of ��Ӹ��				range=[2000] ~ [501]  default=1200
#define CMD_SET_ANGLE_SPEED_FOR_H		_T("RH=%04d")
	//   [RM=nnn]      set speed of �߼Ӹ��				range=[500]  ~ [101]  default=200
#define CMD_SET_ANGLE_SPEED_FOR_M		_T("RM=%03d")
	//   [RL=nn]       set speed of ���Ӹ��				range=[100]  ~ [2]    default=40
#define CMD_SET_ANGLE_SPEED_FOR_L		_T("RL=%02d")

//   [RS=nnnn]     set speed of ǥ���̵� 					range=[1000] ~ [501]  default=550  hschoi
#define CMD_SET_ANGLE_PRESETSPEED_FOR		_T("RP=%04d")

	//   [RH=?]        get speed of ��Ӹ��				return=[1000] ~ [501]   default=550  hschoi
#define CMD_GET_ANGLE_SPEED_FOR_S		_T("RS=?")
	//   [RH=?]        get speed of ��Ӹ��				return=[2000] ~ [501]
#define CMD_GET_ANGLE_SPEED_FOR_H		_T("RH=?")
	//   [RM=?]        get speed of �߼Ӹ��				return=[500]  ~ [101]
#define CMD_GET_ANGLE_SPEED_FOR_M		_T("RM=?")
	//   [RL=?]        get speed of ���Ӹ��				return=[100]  ~ [2]
#define CMD_GET_ANGLE_SPEED_FOR_L		_T("RL=?")

	//   [RH]          ��ġ���� �̵��ӵ��� ��Ӹ��� ����
#define CMD_SET_ANGLE_SPEED_H			_T("RH")
	//   [RM]          ��ġ���� �̵��ӵ��� �߼Ӹ��� ����
#define CMD_SET_ANGLE_SPEED_M			_T("RM")
	//   [RL]          ��ġ���� �̵��ӵ��� ���Ӹ��� ����
#define CMD_SET_ANGLE_SPEED_L			_T("RL")

	//   [R?]          ��ġ���� �̵��ӵ��� �б�				return=[H],[M],[L],[T]
#define CMD_GET_ANGLE_SPEED_Q			_T("R?")
   
//////////////////////////////////////////////////////////////////////
// 3-2. Pan/Tilt �������

	//   [ML]          ��ġ�밡 �������� ȸ�� ����      
#define CMD_MOVE_LEFT					_T("ML")
	//   [MR]          ��ġ�밡 ���������� ȸ�� ����    
#define CMD_MOVE_RIGHT					_T("MR")
	//   [QL][QR]      ��,��ȸ�� ���� 
#define CMD_QUIT_LEFT					_T("QL")
#define CMD_QUIT_RIGHT					_T("QR")
   
	//   [MU]          ��ġ�밡 �������� ȸ�� ����
#define CMD_MOVE_UP						_T("MU")
	//   [MD]          ��ġ�밡 �Ʒ������� ȸ�� ����
#define CMD_MOVE_DOWN					_T("MD")
	//   [QU][QD]      ��,��ȸ�� ����
#define CMD_QUIT_UP						_T("QU")
#define CMD_QUIT_DOWN					_T("QD")

//LRF ���� ����
#define CMD_MOVE_LRF_UP					_T("Lp=U")
#define CMD_MOVE_LRF_DOWN				_T("Lp=D")
#define CMD_MOVE_LRF_LEFT				_T("Lp=L")
#define CMD_MOVE_LRF_RIGHT				_T("Lp=R")
#define CMD_MOVE_LRF_STOP				_T("Lp=Q")
//LRF ���� ����
#define CMD_SET_LRFPWR_ON				_T("LP=O")
#define CMD_SET_LRFPWR_OFF				_T("LP=F")
#define CMD_GET_LRFPWR					_T("LP=?")

//HW ��������
#define CMD_SET_HIGHCAM_HWFILTER_ON		_T("VF=O")
#define CMD_SET_HIGHCAM_HWFILTER_OFF	_T("VF=F")
#define CMD_GET_HIGHCAM_HWFILTER		_T("VF=?")

//ī�޶� �޴�����
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
// 3-3. ��������� ������/������ �� �б�

	//   [GC=P]        ���� �������� ������ �б�			return=[DDD.CCCC]
#define CMD_GET_VAL_P					_T("GC=P")
	//   [GC=T]        ���� �������� ������ �б�			return=[sDD.CCCC]
#define CMD_GET_VAL_T					_T("GC=T")
	//   [GC=F]        ���� �������� ���� �����ġ�� �б�	return=[FFFFF]			// ���� ��.
#define CMD_GET_VAL_F					_T("GC=F")
	//   [GC=Z]        ���� �������� �� �����ġ�� �б�		return=[ZZZZZ]			// ���� ��.
#define CMD_GET_VAL_Z					_T("GC=Z")

	//   [GC=C]        ���� �������� DMC�� �б�				return [DDD]
#define CMD_GET_VAL_DMC					_T("GC=C")
	//   [GC=G]        ���� �������� GPS�� �б�				return=[000618.980,0000.0000,N,00000.0000,E]
#define CMD_GET_VAL_GPS					_T("GC=G")

	//   [GC=M]        ���� ����� ������ġ�� �б�			return=[FFFF,ZZZZ]		// potentio-meter ��.
#define CMD_GET_PMETER_M				_T("GC=M")
	//   [GC=A]        ���� ������ ������ġ�� �б�			return=[FFFF,ZZZZ]		// potentio-meter ��.
#define CMD_GET_PMETER_A				_T("GC=A")

	//   [GC=L]        ���� ������, ������, ������, �ܰ�	return=[DDD.CCCC,sDD.CCCC,FFFFF,ZZZZZ]
#define CMD_GET_ANGLE					_T("GC=L")
#define CMD_GET_ANGLE_F_Z				_T("GC")

//** ������, ������, �������Ͱ�, �ܸ��Ͱ��� ������ OFF�Ͽ��� ���� �����ϰ� ����

//////////////////////////////////////////////////////////////////////
// 3-4. BIT�� ����ǥ��

	//   [GS=P]        ���� ������ ���� ���� �б�			return=[HH]
#define CMD_GET_STATUS_P				_T("GS=P")
	//   [GS=T]        ���� ������ ���� ���� �б�			return=[hh]
#define CMD_GET_STATUS_T				_T("GS=T")

	//   [GS=M]        ���� ����� ���� �б�				return=[hh]
#define CMD_GET_STATUS_M				_T("GS=M")
	//   [GS=A]        ���� ������ ���� �б�				return=[hh]
#define CMD_GET_STATUS_A				_T("GS=A")

//** ���ϰ��� 1����Ʈ unsigned char�� hexa string���� ��ȯ�� ����
//** �ڼ��� ������ ���� ����

//////////////////////////////////////////////////////////////////////
// 3-5. Video Control

	//   [VO=1]       �ֿ����� CH1�� ����, ���������� �ڵ��� CH2�� ����
#define CMD_SET_VO_V1C1					_T("VO=1")
	//   [VO=2]       �ֿ����� CH2�� ����, ���������� �ڵ��� CH1�� ����  
#define CMD_SET_VO_V1C2					_T("VO=2")
	//	 [VO=?]       �ֿ��� ������� �б�					return = [1]:CH1, [2]:CH2 
#define CMD_GET_VO_V1CQ					_T("VO=?")

#if 0
	//   [VM=S]       ����� ���� = �ְ�ī�޶� ����
#define CMD_SET_VM_S					"VM=S"
	//   [VM=D]       ����� ���� = �߰�ī�޶� ����
#define CMD_SET_VM_D					"VM=D"
	//   [VM=?]       ����� ������� �б�					return = [S]:�ְ�ī�޶�, [D]:�߰�ī�޶�  
#define CMD_GET_VM_Q					"VM=?"
#else//  [8/19/2014 Yeun] 
//   [VM=S]       ����� ���� = �÷����
#define CMD_SET_VM_S					_T("VS=C")
//   [VM=D]       ����� ���� = B/W���
#define CMD_SET_VM_D					_T("VS=B")
//   [VM=?]       ����� ������� �б�					return=[VS=C],[VS=B]
#define CMD_GET_VM_Q					_T("VS=?")

#endif

	//   [VA=S]       ������ ���� = �ְ�ī�޶� ����
#define CMD_SET_VA_S					_T("VA=S")
	//   [VA=D]       ������ ���� = �߰�ī�޶� ����
#define CMD_SET_VA_D					_T("VA=D")
	//   [VA=?]       ������ ������� �б�					return = [S]:�ְ�ī�޶�, [D]:�߰�ī�޶�   
#define CMD_GET_VA_Q					_T("VA=?")

	//   [V1=M]        �ֿ��� = ������� ���� 
#define CMD_SET_V1_M					_T("V1=M")
	//   [V1=A]        �ֿ��� = ������(�ְ�)�� ����
#define CMD_SET_V1_A					_T("V1=A")
	//   [V1=R]        �ֿ��� = ������ ����
#define CMD_SET_V1_R					_T("V1=T")
	//   [V1=X]        �ֿ��� = ��������
#define CMD_SET_V1_X					_T("V1=X")
	//   [V1=?]        �ֿ��� ������� �б�					return = [M]:�����, [A]:������, [R]:������, [X]:����ȵ�.
#define CMD_GET_V1_Q					_T("V1=?")

	//   [V2=M]        �������� = ������� ���� 
#define CMD_SET_V2_M					_T("V2=M")
	//   [V2=A]        �������� = �������� ���� 
#define CMD_SET_V2_A					_T("V2=A")
	//   [V2=R]        �������� = ������ ����
#define CMD_SET_V2_R					_T("V2=T")
	//   [V2=X]        �������� = ��������
#define CMD_SET_V2_X					_T("V2=X")
	//   [V2=?]        �������� ������� �б�				return = [M]:�����, [A]:������, [R]:������, [X]:����ȵ�.
#define CMD_GET_V2_Q					_T("V2=?")

//////////////////////////////////////////////////////////////////////
// 3-6. ����� Lense control

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

//** �ܰ� ��Ŀ���� ���� �ϳ��� ���� -> �� �̵���Ű�� ��Ŀ���� ���� �̵��ȴ�.
//   => ������ ���� ���� �̵���Ų �� ��Ŀ���� �̵����Ѿ� �Ѵ�.

//////////////////////////////////////////////////////////////////////
// 3-7. ������ Lense control

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

//** ������ ī�޶� �Ｚī�޶� ����ϸ鼭 Kowa ����� ��� ����.
//** [EC=cmd]�� ����ϸ� PCB�� ī�޶� ��� bypass ����.

//////////////////////////////////////////////////////////////////////
//������ ���� ��������
#define CMD_T_LENSE_FOCUS_NEAR			_T("Ti")
#define CMD_T_LENSE_FOCUS_FAR			_T("To")
#define CMD_T_LENSE_FOCUS_STOP			_T("Tq")

//////////////////////////////////////////////////////////////////////////
// 3-8. ������ Camera control TR-3600

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
// 3.9 ��Ÿ Command

	//   [PW=O]        remote power ON 
#define CMD_POWER_ON					_T("PW=O")
	//   [PW=F]        remote power OFF  
#define CMD_POWER_OFF					_T("PW=F")
	//   [PW=?]        get power flag						return=[O]:on, [F]:off
#define CMD_POWER_Q						_T("PW=?")
  
//////////////////////////////////////////////////////////////////////
// 3.10. Target Preset �� Auto Focusing ���
#define CMD_PS_POINT_HOME_PANTILT		_T("HM=C")	
#define CMD_PS_POINT_HOME_QRY			_T("HM=?")				// return=[P]:����, [T]:ƿƮ��, [C]:�����̵��Ϸ�, [O]:�������̵��Ϸ�, [X]:���� ���� 	
	//   [PH=T]        Tilt Home ��ġ�� �̵�				
#define CMD_PS_POINT_HOME_ZEROPOS		_T("HM=0")	
#define CMD_PS_POINT_SET_ZEROPOS		_T("HP=S")	


	//   [PL=nn]       nn ��ȣ�� ��ǥ�� �ٷΰ���� ����		return=[0]:ok, [1]:false, range=[00]~[99]
#define CMD_PS_POINT_LINK				_T("PL=%03d")
	//   [PS=nn]       nn ��ȣ�� ���� ��ǥ�� ����			return=[0]:ok, [1]:false
#define CMD_PS_POINT_SET				_T("PS=%03d")
	//   [PG=nn]       nn ��ȣ�� ��ǥ�� �б�				return=[DDD.CCCC,sDD.CCCC,FFFFF,ZZZZZ]
#define CMD_PS_POINT_GET				_T("PG=%03d")
	//   [PP=nn:DDD.CCCC,sDD.CCCC,FFFFF,ZZZZZ]
	//				   nn ��ȣ�� �����ϴ� ��ǥ�� ����		return=[0]:ok, [1]:false                                       
#define CMD_PS_POINT_PUT				_T("PP=%03d:%s")
	//   [PM]          �ٷΰ��� ����(����,��,��,����)		return=[0]:ok, [1]:false
#define CMD_PS_POINT_MOVE				_T("PM")
	//   [PZ]          �ٷΰ��� ����ȭ						return=[0]:ok, [1]:��ǥ ����, [2]:�� �Ұ���, [3]:����/�� ����, [4]:���� ����
#define CMD_PS_POINT_ZONE				_T("PZ")
	//   [PR]          �ֱ� ��� ��ǥ. <GC=L�� ����>		return=[DDD.CCCC,sDD.CCCC,FFFFF,ZZZZZ] 
#define CMD_PS_POINT_READ				_T("PR")
	//   [PH=P]        Pan Home ��ġ�� �̵�					return=[P]:����, [0]:��, [1]:Fail




#define CMD_PS_POINT_HOME_TILT			_T("PH=T")
	//   [CI]          init magnetic compass
#define CMD_COMPASS_INIT				_T("CI")

//** �ٷΰ��� ��ǥ�� NV-RAM�� ����ǹǷ� ������ OFF�Ǿ ����Ÿ ������
//** [PH=P]�� �����ϸ� Pan ���� ����Ʈ���� 180�� ��ġ�� �̵��ϰ� ��ǥ���� 000.0000���� �ʱ�ȭ
//** [PH=T]�� �����ϸ� Tilt�� ��������(���� ���� �̿�) ��ġ�ϰ� ��ǥ���� +00.0000���� �ʱ�ȭ
//** ����ȭ   ���� ���� = [PH=P]->[PH=T]->[zoom]->[focus] => [PP=00:~]->[PL=00]->[PZ]
//** �ٷΰ��� ���� ���� = [PP=nn:~]->[PL=nn]->[PM]

//////////////////////////////////////////////////////////////////////
// 3.11 Target Preset �� Auto Focusing ����

	//	[Sp=DDD.CCCC]  �ٷΰ��� �������� [DDD.CCCC]�� ����	return=[0]:ok, [1]:false
#define CMD_SET_DIRECT_PAN				_T("Sp=%s")
	//	[St=sDD.CCCC]  �ٷΰ��� �������� [sDD.CCCC]�� ����	return=[0]:ok, [1]:false
#define CMD_SET_DIRECT_TILT				_T("St=%s")
	//	[Sf=FFFFF]     �ٷΰ��� �������� [FFFFF]�� ����		return=[0]:ok, [1]:false
#define CMD_SET_DIRECT_FOCUS			_T("Sf=%s")
	//	[Sz=ZZZZZ]     �ٷΰ��� �ܰ���  [ZZZZZ]�� ����		return=[0]:ok, [1]:false
#define CMD_SET_DIRECT_ZOOM				_T("Sz=%s")
	//	[Sc]           �ٷΰ��� �������� ��ǥ�� ��� ����	return=[0]:ok, [1]:false
#define CMD_SET_DIRECT_ALL				_T("Sc=%s")

	//	[Gp]            �ٷΰ��� ������ �б�				return=[DDD.CCCC]
#define CMD_GET_DIRECT_PAN				_T("Gp")
	//	[Gt]            �ٷΰ��� ������ �б�				return=[sDD.CCCC]
#define CMD_GET_DIRECT_TILT				_T("Gt")
	//	[Gf]          �ٷΰ��� ������ �б�					return=[FFFFF]
#define CMD_GET_DIRECT_FOCUS			_T("Gf")
	//	[Gz]         �ٷΰ��� �ܰ� �б�						return=[ZZZZZ]
#define CMD_GET_DIRECT_ZOOM				_T("Gz")
	//	[Gl]          �ٷΰ��� ��ǥ �б�					return=[DDD.CCCC,sDD.CCCC,FFFFF,ZZZZZ] 
#define CMD_GET_DIRECT_ALL				_T("Gc")

//////////////////////////////////////////////////////////////////////
// 3.12 Auto Tracking ����

#define CMD_TRACKING_ON					_T("AS")
//						Ʈ��ŷ ��� �ѱ�
#define CMD_TRACKING_OFF				_T("AQ")
//						Ʈ��ŷ ��� ����
#define CMD_PAN_MOVEAUTO				_T("AP=%s%03d")
//		[AP=sNNN]		�� �ڵ� �̵�.
#define CMD_TILT_MOVEAUTO				_T("AT=%s%03d")
//		[AT=sNNN]		ƿƮ �ڵ� �̵�.

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