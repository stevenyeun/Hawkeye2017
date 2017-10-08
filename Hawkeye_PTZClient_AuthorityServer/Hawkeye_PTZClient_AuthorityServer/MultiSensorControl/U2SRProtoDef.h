#ifndef U2SRPROTODEF_H
#define U2SRPROTODEF_H

//U2SR_��ɾ�_V2(101219).doc

//Idx 0
#define IDX0_STA_CODE 0
#define START_CODE '$'
//Idx 1
#define IDX1_SRC_ID 1
#define SRC_ID '0'

//Idx 2
#define IDX2_DEV_ID 2
#define DEV_ID '0'

//Idx 3 //Ask Frame //������ɿ����� ����
#define IDX3_ASK_FRM 3

	#define SET_OK '0'//�ֿܼ��� ������ Set ����� ���������� ó���� 
	#define SET_OK_INT 0

	#define GET_OK '1'//�ֿܼ��� ������ Get ��ɿ� ���� �������� ���� ���� ���� 
	#define GET_OK_INT 1

	#define ERR_CANT_PROC '2'//�ش����� ó���Ҽ�����
	#define ERR_CANT_PROC_INT 2


	#define ERR_NOTSUPP '3'// not support
	#define ERR_NOTSUPP_INT 3
	#define ERR_DEV_TIMEOUT '4' //DEVICE ���� �������
	#define ERR_DEV_NOTCONN '5' //�ش� ����̽��� ����Ǿ���������

	#define ERR_DEV_PWROFF '6' //�ش� ����̽��� ������ ���� ���� ����
	#define ERR_DEV_PWROFF_INT 6
	#define ERR_DEV_LIMIT	'7' //�ش� ��ɿ� ���� ���°� ����Ʈ ��

//Idx 4~5
#define IDX4_CMD_LEN 4
#define IDX5_CMD_LEN 5

//6~n is cmd
#define IDX6_CMD_DATA 6



//check sum

/*
Start Code + Device ID + Service code + Length + Cpmmand String �� ��� ���� ���� 
���� 1����Ʈ�� ASCII String ���� ��ȯ�� ��(2����Ʈ) �̴�
��) 0x03F5 ->0xF5,    check sum = "F5"
*/

#define ETX 0x0d

//  [3/14/2014 Yeun]
const int MAX_PARAM=10;
typedef double DARR_PARAM[MAX_PARAM];



//��� ����




#define BOXCAM_SAMSUNG 1
#define BOXCAM_HITACHI 2
#define BOXCAM_MINTRON 3

#define THERMCAM_CANTRONIC 1
#define THERMCAM_OPGAL	   2
#define THERMCAM_FLIR	   3

#define LRF_ZEISS 1
#define LRF_SHUMIT 2
#define LRF_INSTRO 3//  [9/2/2014 Yeun] 

//  [8/7/2014 Yeun] 
#define BOARD_TYPE_OYTO 1
#define BOARD_TYPE_TW68XX 2

#define HIGHZOOM_AF_USED TRUE
#define HIGHZOOM_AF_NOTUSED FALSE

#endif