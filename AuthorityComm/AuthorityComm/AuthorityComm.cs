
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace AuthorityComm
{
    public class AuthorityCommUtil
    {
        //http://technodori.tistory.com/entry/C-byte-%EA%B5%AC%EC%A1%B0%EC%B2%B4-%EA%B5%AC%EC%A1%B0%EC%B2%B4-byte
        //byte 배열을 구조체로
        public static object ByteToStructure(byte[] data, Type type)
        {
            IntPtr buff = Marshal.AllocHGlobal(data.Length); // 배열의 크기만큼 비관리 메모리 영역에 메모리를 할당한다.
            Marshal.Copy(data, 0, buff, data.Length); // 배열에 저장된 데이터를 위에서 할당한 메모리 영역에 복사한다.
            object obj = Marshal.PtrToStructure(buff, type); // 복사된 데이터를 구조체 객체로 변환한다.
            Marshal.FreeHGlobal(buff); // 비관리 메모리 영역에 할당했던 메모리를 해제함

            if (Marshal.SizeOf(obj) != data.Length)// (((PACKET_DATA)obj).TotalBytes != data.Length) // 구조체와 원래의 데이터의 크기 비교
            {
                return null; // 크기가 다르면 null 리턴
            }
            return obj; // 구조체 리턴
        }


        // 구조체를 byte 배열로
        public static byte[] StructureToByte(object obj)
        {
            int datasize = Marshal.SizeOf(obj);//((PACKET_DATA)obj).TotalBytes; // 구조체에 할당된 메모리의 크기를 구한다.
            IntPtr buff = Marshal.AllocHGlobal(datasize); // 비관리 메모리 영역에 구조체 크기만큼의 메모리를 할당한다.
            Marshal.StructureToPtr(obj, buff, false); // 할당된 구조체 객체의 주소를 구한다.
            byte[] data = new byte[datasize]; // 구조체가 복사될 배열
            Marshal.Copy(buff, data, 0, datasize); // 구조체 객체를 배열에 복사
            Marshal.FreeHGlobal(buff); // 비관리 메모리 영역에 할당했던 메모리를 해제함
            return data; // 배열을 리턴
        }

        // 바이트 배열을 String으로 변환 
        public static string ByteToString(byte[] strByte)
        {
            string str = Encoding.Default.GetString(strByte).Trim('\0');            
            return str;
        }
        // String을 바이트 배열로 변환 
        public static byte[] StringToByte(string str)
        {
            byte[] StrByte = Encoding.UTF8.GetBytes(str);
            return StrByte;
        }

        public static AUTHORITY_PACKET MakeAuthorityPacket(string srcName, byte byCmdGroup, byte byCmdType, string data)
        {
            //http://www.csharpstudy.com/DevNote/Article/10
            AUTHORITY_PACKET authorityPacket = new AUTHORITY_PACKET();
          
            authorityPacket.bySTX = AuthorityDefine.PROTO_STX;
                  
            authorityPacket.srcName.name = new byte[AuthorityDefine.SRC_NAME_LEN];
            byte[] myName = AuthorityCommUtil.StringToByte(srcName);
            Buffer.BlockCopy(myName, 0, authorityPacket.srcName.name, 0, myName.Length);

           
            authorityPacket.byCmdGroup = byCmdGroup;
            authorityPacket.byCmdType = byCmdType;
            authorityPacket.byETX = AuthorityDefine.PROTO_ETX;


            authorityPacket.authorityData.data = new byte[AuthorityDefine.AUTHORITY_DATA_LEN];
            byte[] myData = AuthorityCommUtil.StringToByte(data);
            Buffer.BlockCopy(myData, 0, authorityPacket.authorityData.data, 0, myData.Length);
       

            return authorityPacket;

        }
    }

    public class AuthorityPacketMaker
    {

        public AUTHORITY_PACKET MakeAuthorityPacket(int nCh, SOURCE_NAME srcName, byte byCmdGroup, byte byCmdType, AUTHORITY_DATA authorityData)
        {
            //http://www.csharpstudy.com/DevNote/Article/10
            AUTHORITY_PACKET authorityPacket = new AUTHORITY_PACKET();
            //int size = Marshal.SizeOf(typeof(AUTHORITY_PACKET));
            //byte[] buffer = new byte[size];

            authorityPacket.bySTX = AuthorityDefine.PROTO_STX;

            //Buffer.BlockCopy(SourceName, 0, authorityPacket.srcName.name, 0, AuthorityDefine.SRC_NAME_LEN);
            //sprintf(authorityPacket.srcName.name, "%s", (CStringA)m_strSourceName);
            authorityPacket.srcName = srcName;

            authorityPacket.byCmdGroup = byCmdGroup;
            authorityPacket.byCmdType = byCmdType;
            authorityPacket.byETX = AuthorityDefine.PROTO_ETX;


            authorityPacket.authorityData = authorityData;
            //authorityPacket.authorityData = authorityData;
            //Buffer.BlockCopy(authorityPacket.authorityData.data, 0, authorityPacket.authorityData.data, 0, AuthorityDefine.AUTHORITY_DATA_LEN);
            //memcpy(&authorityPacket.authorityData, &authorityData, sizeof(AUTHORITY_DATA));

            /*
                 IntPtr ptr = Marshal.AllocHGlobal(size);

                 Marshal.StructureToPtr(authorityPacket, ptr, true);
                 Marshal.Copy(ptr, buffer, 0, size);
                 */

            return authorityPacket;

        }
    }

    //[StructLayout(LayoutKind.Sequential, Pack = 1)]
    //[Serializable]

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct AUTHORITY_PACKET
    {
        public byte bySTX;
        public SOURCE_NAME srcName;
        public byte byCmdGroup;
        public byte byCmdType;
        public AUTHORITY_DATA authorityData;
        public byte byETX;
    }
    
    //[StructLayout(LayoutKind.Sequential, Pack = 1)]
    //[Serializable]

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct SOURCE_NAME
    {

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = AuthorityDefine.SRC_NAME_LEN)]
        public byte[] name; 
    }
    public class CommandAuthority
    {
        /////////////////////////////////////////////////////
        //byCmdGroup
        public const byte CMDGROUP_AUTHORITY = 0x01;

        public const byte CMDTYPE_AUTHORITY_LOGIN = 1;
        public const byte CMDTYPE_AUTHORITY_REQUEST = 2;
        public const byte CMDTYPE_AUTHORITY_AUTHORIZATION = 3;
        public const byte CMDTYPE_AUTHORITY_DEPRIVATION = 4;
        public const byte CMDTYPE_AUTHORITY_TEMPAUTHORITY_USE_NOTIFICATION = 5;
        public const byte CMDTYPE_AUTHORITY_TEMPAUTHORITY_RETURN_NOTIFICATION = 6;
        public const byte CMDTYPE_AUTHORITY_TEMPAUTHORITY_INUSE_NOTIFICATION = 7;
        //////////////////////////////////////////        

    }
    public class CommandPTZ//기본적인 PTZ 기능
    {
        public const byte CMDGROUP_PTZCTRL = 0x02;
        //Control Client -> Control Server
        public const byte CMDTYPE_PTZCTRL_PAN_LEFT = 1;
        public const byte CMDTYPE_PTZCTRL_PAN_RIGHT = 2;
        public const byte CMDTYPE_PTZCTRL_TILT_UP = 3;
        public const byte CMDTYPE_PTZCTRL_TILT_DOWN = 4;
        public const byte CMDTYPE_PTZCTRL_PT_LU = 5;
        public const byte CMDTYPE_PTZCTRL_PT_RU = 6;
        public const byte CMDTYPE_PTZCTRL_PT_LD = 7;
        public const byte CMDTYPE_PTZCTRL_PT_RD = 8;
        public const byte CMDTYPE_PTZCTRL_PAN_STOP = 9;
        public const byte CMDTYPE_PTZCTRL_TILT_STOP = 10;
        public const byte CMDTYPE_PTZCTRL_PT_STOP = 11;

        public const byte CMDTYPE_PTZCTRL_ZOOM_TELE = 12;
        public const byte CMDTYPE_PTZCTRL_ZOOM_WIDE = 13;
        public const byte CMDTYPE_PTZCTRL_ZOOM_STOP = 14;
        public const byte CMDTYPE_PTZCTRL_FOCUS_NEAR = 15;
        public const byte CMDTYPE_PTZCTRL_FOCUS_FAR = 16;
        public const byte CMDTYPE_PTZCTRL_FOCUS_STOP = 17;

        public const byte CMDTYPE_PTZCTRL_PT_SPEED = 18;
        public const byte CMDTYPE_PTZCTRL_ZOOM_SPEED = 19;
        public const byte CMDTYPE_PTZCTRL_FOCUS_SPEED = 20;
        public const byte CMDTYPE_PTZCTRL_PRESET_SPEED = 21;
        //////////////////////////////////////////



        /*
        Day Zoom Pos Req
        Day Zoom Pos Resp
        Day Focus Pos Req
        Day Focus Pos Resp
        Pan Status Req
        Pan Status Resp
        Tilt Status Req
        Tilt Status Resp
        Day Z / F Status Req
        Day Z / F Status Resp
        */
        //////////////////////////////////////////
    }
    public class CommandPTZReqResp
    {
        public const byte CMDGROUP_PTZREQ = 0x03;
        public const byte CMDTYPE_PTZREQ_PANTILT_POS_REQ = 1;
        public const byte CMDTYPE_PTZREQ_PANTILT_POS_RESP = 2;

        public const byte CMDTYPE_PTZREQ_DAYZF_POS_REQ = 3;
        public const byte CMDTYPE_PTZREQ_DAYZF_POS_RESP = 4;

        public const byte CMDTYPE_PTZREQ_PAN_MOTORSTATUS_REQ = 5;

        public const byte CMDTYPE_PTZREQ_PAN_INITSTATUS_RESP = 6;
        public const byte CMDTYPE_PTZREQ_PAN_MOVESTATUS_RESP = 7;

        public const byte CMDTYPE_PTZREQ_TILT_STATUS_REQ = 8;
        public const byte CMDTYPE_PTZREQ_TILT_STATUS_RESP = 9;

        public const byte CMDTYPE_PTZREQ_ZF_STATUS_REQ = 10;
        public const byte CMDTYPE_PTZREQ_ZF_STATUS_RESP = 11;
        public const byte CMDTYPE_PTZREQ_MAINBOARD_STATUS_RESP = 12;
    }

    public class CommandDayCam
    {
        public const byte CMDGROUP_DAYCAM = 0x04;
        public const byte CMDTYPE_DAYCAM_EXTENDTER = 1;
        public const byte CMDTYPE_DAYCAM_IRIS = 2;
        //public  const int CMDTYPE_DAYCAM_COLOR_MODE 1
        //public  const int CMDTYPE_DAYCAM_BW_MODE 2
        //////////////////////////////////////////
    }
    public class CommandThermCam
    {
        //Thermal Camera
        public const byte CMDGROUP_THERMCAM = 0x05;
        public const byte CMDTYPE_THERMCAM_WHITE_HOT = 1;
        public const byte CMDTYPE_THERMCAM_BLACK_HOT = 2;

        public const byte CMDTYPE_THERMCAM_COLOR = 3;

        public const byte CMDTYPE_THERMCAM_DZOOM = 4;
        public const byte CMDTYPE_THERMCAM_DZOOM_REQ = 5;
        public const byte CMDTYPE_THERMCAM_DZOOM_RESP = 6;

        public const byte CMDTYPE_THERMCAM_NUC = 7;

        public const byte CMDTYPE_THERMCAM_AGCMODE = 8;
        public const byte CMDTYPE_THERMCAM_AGCMODE_REQ = 9;
        public const byte CMDTYPE_THERMCAM_AGCMODE_RESP = 10;

        public const byte CMDTYPE_THERMCAM_CONTRAST = 11;
        public const byte CMDTYPE_THERMCAM_CONTRAST_REQ = 12;
        public const byte CMDTYPE_THERMCAM_CONTRAST_RESP = 13;

        public const byte CMDTYPE_THERMCAM_BRIGHTNESS = 14;
        public const byte CMDTYPE_THERMCAM_BRIGHTNESS_REQ = 15;
        public const byte CMDTYPE_THERMCAM_BRIGHTNESS_RESP = 16;

        public const byte CMDTYPE_THERMCAM_DDE = 17;
        public const byte CMDTYPE_THERMCAM_DDE_REQ = 18;
        public const byte CMDTYPE_THERMCAM_DDE_RESP = 19;

        public const byte CMDTYPE_THERMCAM_ACE = 20;
        public const byte CMDTYPE_THERMCAM_ACE_REQ = 21;
        public const byte CMDTYPE_THERMCAM_ACE_RESP = 22;

        public const byte CMDTYPE_THERMCAM_SSO = 23;
        public const byte CMDTYPE_THERMCAM_SSO_REQ = 24;
        public const byte CMDTYPE_THERMCAM_SSO_RESP = 25;
        //////////////////////////////////////////
    }
    public class CommandPowerMgt
    {
        //전원 관리 기능
        //////////////////////////////////////////
        public const byte CMDGROUP_POWERMGT = 0x06;
        public const byte CMDTYPE_POWERMGT_SYS_PWR_CTL = 1;
        public const byte CMDTYPE_POWERMGT_SYS_PWR_STATUS = 2;
        public const byte CMDTYPE_POWERMGT_THERMCAM_PWR_CTL = 3;
        public const byte CMDTYPE_POWERMGT_THERMCAM_PWR_STATUS = 4;
    }

    public class CommandPanTiltInit
    {
        //팬틸트 초기화 기능
        //////////////////////////////////////////
        public const byte CMDGROUP_PANTILTINIT = 0x07;
        public const byte CMDTYPE_PANTILTINIT_MOVE_HOMEPOS = 1;
        public const byte CMDTYPE_PANTILTINIT_REQ_HOMEPOS = 2;
        public const byte CMDTYPE_PANTILTINIT_RESP_HOMEPOS = 3;
        public const byte CMDTYPE_PANTILTINIT_SYNC_HOMEPOS = 4;
    }

    public class CommandPTZFAbsMove
    {
        //PTZF 이동 기능
        //////////////////////////////////////////
        public const byte CMDGROUP_PTZFABSMOVE = 0x08;
        public const byte CMDTYPE_PTZFABSMOVE_MOVE = 1;
        public const byte CMDTYPE_PTZFABSMOVE_SAVE_POS = 2;
        public const byte CMDTYPE_PTZFABSMOVE_MOVE_SAVEPOS = 3;
        public const byte CMDTYPE_PTZFABSMOVE_REQ_SAVEPOS = 4;
        public const byte CMDTYPE_PTZFABSMOVE_RESP_SAVEPOS = 5;
    }

    public class CommandETC
    {
        //기타기능
        //////////////////////////////////////////
        public const byte CMDGROUP_ETCFUNC = 0x09;
                
        public const byte CMDTYPE_ETCFUNC_PANTILT_INIT = 1;
        public const byte CMDTYPE_ETCFUNC_PANTILT_INIT_STATUS = 2;
        public const byte CMDTYPE_ETCFUNC_PANTILT_MOTOR_ADJUSTMENT_STATUS = 3;
        public const byte CMDTYPE_ETCFUNC_PRESET_CTL = 4;
        public const byte CMDTYPE_ETCFUNC_PRESET_STATUS = 5;
        public const byte CMDTYPE_ETCFUNC_SET_PAN_OFFSET = 6;
        public const byte CMDTYPE_ETCFUNC_SET_TILT_OFFSET = 7;
        public const byte CMDTYPE_ETCFUNC_REQ_GPS_VAL = 8;
        public const byte CMDTYPE_ETCFUNC_REQ_GPS_LAT = 9;
        public const byte CMDTYPE_ETCFUNC_REQ_GPS_LONG = 10;
        public const byte CMDTYPE_ETCFUNC_SET_LAT_POS = 11;
        public const byte CMDTYPE_ETCFUNC_SET_LONG_POS = 12;
        //////////////////////////////////////////
    }
    public class ETCDevice
    {
        //ETC Device
        public const byte CMDGROUP_ETC_DEVICE = 0x0A;
        public const byte CMDTYPE_ETC_HIGHLENS_FILTER = 1;      
    }

    //////////////////////////////////////////
    /*
    public class CommandStatusMsg
    {
        public const byte CMDGROUP_ETC_LINK = 0x08;
        //////////////////////////////////////////

        //cmdval1
        public const byte CMDVAL_CONTROLING = 0x01;
        public const byte CMDVAL_WAITING = 0x02;
    }
    */


    public class AuthorityDefine
    {
        //IDX
        public const byte IDX_STX = 0;
        public const byte IDX_LEN = 1;
        public const byte IDX_SENDDEV = 2;
        public const byte IDX_CMDGROUP = 3;
        public const byte IDX_CMDTYPE = 4;
        public const byte IDX_CMDVAL1 = 5;
        public const byte IDX_CMDVAL2 = 6;
        public const byte IDX_ETX = 7;

        //Length
        public const int SRC_NAME_LEN = 20;
        public const int AUTHORITY_DATA_LEN = 40;
        // Data Field Define
        //
        public const byte PROTO_STX = 0x02;
        public const byte PROTO_ETX = 0x03;
    }

     //[StructLayout(LayoutKind.Sequential, Pack = 1)]
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct AUTHORITY_DATA
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = AuthorityDefine.AUTHORITY_DATA_LEN)]
        public byte[] data;

    }
}
