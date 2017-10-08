using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hawkeye_BIT
{
    static class U2SRProtocol
    {
        //Idx 0
        static readonly int IDX0_STA_CODE = 0;
        static readonly char START_CODE = '$';
        //Idx 1
        static readonly byte IDX1_SRC_ID = 1;
        static readonly char SRC_ID = '0';

        //Idx 2
        static readonly int IDX2_DEV_ID = 2;
        static readonly char DEV_ID = '0';

        //Idx 3 //Ask Frame //보낸명령에대한 응답
        static readonly int IDX3_ASK_FRM = 3;

        static readonly char SET_OK = '0';//콘솔에서 보내는 Set 명령이 정상적으로 처리됨 
        static readonly int SET_OK_INT = 0;

        static readonly char GET_OK = '1';//콘솔에서 보내는 Get 명령에 대한 정상적인 리턴 값을 받음 
        static readonly int GET_OK_INT = 1;

        static readonly char ERR_CANT_PROC = '2';//해당명령은 처리할수없음
        static readonly int ERR_CANT_PROC_INT = 2;


        static readonly char ERR_NOTSUPP = '3';// not support
        static readonly int ERR_NOTSUPP_INT = 3;
        static readonly int ERR_DEV_TIMEOUT = '4'; //DEVICE 에서 통신지연
        static readonly int ERR_DEV_NOTCONN = '5'; //해당 디바이스가 연결되어있지않음

        static readonly char ERR_DEV_PWROFF = '6'; //해당 디바이스가 전원이 켜져 있지 않음
        static readonly int ERR_DEV_PWROFF_INT = 6;
        static readonly char ERR_DEV_LIMIT = '7'; //해당 명령에 대한 상태가 리미트 임

        //Idx 4~5
        static readonly int IDX4_CMD_LEN = 4;
        static readonly int IDX5_CMD_LEN = 5;

        //6~n is cmd
        static readonly int IDX6_CMD_DATA = 6;

        static public int ByteToU2SRCmd(byte[] buffer, out string parsedCMD)
        {
            if (buffer[IDX0_STA_CODE] == START_CODE)
            {
                if (buffer[IDX1_SRC_ID] == SRC_ID)
                {
                    if (buffer[IDX2_DEV_ID] == DEV_ID)
                    {
                        //if( lpData[IDX3_ASK_FRM] == SET_OK || lpData[IDX3_ASK_FRM] == GET_OK )
                        //{

                        byte[] arrByte = { buffer[IDX4_CMD_LEN], buffer[IDX5_CMD_LEN] };
                        string strLen = System.Text.Encoding.Default.GetString(arrByte);
                        //string strLen = System.Text.Encoding.Default.GetString(buffer);
                        //string wcslen = String.Format("{0}{1}", buffer[IDX4_CMD_LEN], buffer[IDX5_CMD_LEN]);
                        //wcslen.Format(_T("%c%c"), , );

                        int iLen = int.Parse(strLen);// wcslen.Length;
                        string strCMD = System.Text.Encoding.Default.GetString(buffer);

                        parsedCMD = strCMD.Substring(IDX6_CMD_DATA, iLen);
                        System.Console.WriteLine(parsedCMD);
                        //for (int i = 0; i < iLen; i++)
                        //{
                        //    parsedCMD += buffer[IDX6_CMD_DATA + i];
                        //}

                        string askFrm = strCMD.Substring(IDX3_ASK_FRM, 1);
                        //byte[] chData = { buffer[IDX3_ASK_FRM] };
                        return int.Parse(askFrm);
                   
                    }
                }
            }
            parsedCMD = "";
            return -1;
        }
    }
}
