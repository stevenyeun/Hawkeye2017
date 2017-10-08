using Ini;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.NetworkInformation;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace ReadWriteIni
{
    //모든프로그램공통
    public class WindowInfoIni
    {
        private IniFile ini;

        //아이콘 모양일때 위치/크기
        public double minimizeX = 0;
        public double minimizeY = 0;
        public double minimizeWidth = 0;
        public double minimizeHeight = 0;

        //창모드일때 위치/크기
        public double maximizeX = 0;
        public double maximizeY = 0;
        public double maximizeWidth = 0;
        public double maximizeHeight = 0;


        public WindowInfoIni(string name)//현재경로 + name + .ini
        {
            string filePath = AppDomain.CurrentDomain.BaseDirectory + name + ".ini";

            try
            {
                ini = new IniFile(filePath);

                //파일이 존재하는지 확인
                // See if this file exists in the same directory.
                if (File.Exists(filePath) == true)//파일이 존재
                {
                    Console.WriteLine("파일이 존재합니다.");

                    ReadIni();
                }
                else
                {
                    Console.WriteLine("파일을 찾을수없습니다.");

                    //파일이 없는경우 기본값으로 파일에 쓴다.
                    this.minimizeX = 0;
                    this.minimizeY = 0;
                    this.minimizeWidth = 80;
                    this.minimizeHeight = 80;

                    this.maximizeX = 0;
                    this.maximizeY = 0;
                    this.maximizeWidth = 400;
                    this.maximizeHeight = 700;

                    WriteIni();//파일쓰기
                }
            }
            catch(Exception e)
            {

            }
       


        }
        public void ReadIni()
        {
            string minimizeX = ini.IniReadValue("window", "minimizeX");
            string minimizeY = ini.IniReadValue("window", "minimizeY");
            string minimizeWidth = ini.IniReadValue("window", "minimizeWidth");
            string minimizeHeight = ini.IniReadValue("window", "minimizeHeight");

            string maximizeX = ini.IniReadValue("window", "maximizeX");
            string maximizeY = ini.IniReadValue("window", "maximizeY");
            string maximizeWidth = ini.IniReadValue("window", "maximizeWidth");
            string maximizeHeight = ini.IniReadValue("window", "maximizeHeight");

            try
            {
                this.minimizeX = double.Parse(minimizeX);
                this.minimizeY = double.Parse(minimizeY);
                this.minimizeWidth = double.Parse(minimizeWidth);
                this.minimizeHeight = double.Parse(minimizeHeight);

                this.maximizeX = double.Parse(maximizeX);
                this.maximizeY = double.Parse(maximizeY);
                this.maximizeWidth = double.Parse(maximizeWidth);
                this.maximizeHeight = double.Parse(maximizeHeight);
            }
            catch (Exception e)
            {

            }
        }
        public void WriteIni()
        {
            try
            {
                ini.IniWriteValue("window", "minimizeX", this.minimizeX.ToString());
                ini.IniWriteValue("window", "minimizeY", this.minimizeY.ToString());
                ini.IniWriteValue("window", "minimizeWidth", this.minimizeWidth.ToString());
                ini.IniWriteValue("window", "minimizeHeight", this.minimizeHeight.ToString());

                ini.IniWriteValue("window", "maximizeX", this.maximizeX.ToString());
                ini.IniWriteValue("window", "maximizeY", this.maximizeY.ToString());
                ini.IniWriteValue("window", "maximizeWidth", this.maximizeWidth.ToString());
                ini.IniWriteValue("window", "maximizeHeight", this.maximizeHeight.ToString());
            }
            catch (Exception e)
            {

            }
        }
    }

    public class STR_IP_PORT
    {
        public STR_IP_PORT()
        {
            ipAddrFirst = "";
            ipAddrSecond = "";
            ipAddrThird = "";
            ipAddrFourth = "";

            uri = "";
            port = "";

            id = "";
            pw = "";
        }
        public string ipAddrFirst;
        public string ipAddrSecond;
        public string ipAddrThird;
        public string ipAddrFourth;

        public string uri;
        public string port;

        public string id;
        public string pw;

    }

    //아이피설정
    public class SystemIpAddrInfo
    {
        private IniFile ini;

        public STR_IP_PORT ptzServerInfo = new STR_IP_PORT();
        public STR_IP_PORT authorityServerInfo = new STR_IP_PORT();
        public STR_IP_PORT mainVideoUriInfo = new STR_IP_PORT();
        public STR_IP_PORT subVideoUriInfo = new STR_IP_PORT();

        public STR_IP_PORT dayCamCtlUriInfo = new STR_IP_PORT();
        public STR_IP_PORT micCtlUriInfo = new STR_IP_PORT();

        public SystemIpAddrInfo(string name)//절대경로
        {
            int nIndex = AppDomain.CurrentDomain.BaseDirectory.LastIndexOf('\\');
            string newPath = AppDomain.CurrentDomain.BaseDirectory.Substring(0, nIndex);
            nIndex = newPath.LastIndexOf('\\');
            newPath = newPath.Substring(0, nIndex + 1);

            ini = new IniFile(newPath + name + ".ini");

            //파일이 존재하는지 확인
            // See if this file exists in the same directory.
            if (File.Exists(newPath) == true)//파일이 존재
            {
                Console.WriteLine("파일이 존재합니다.");

                //ReadIni(1);
            }
            else
            {
                Console.WriteLine("파일을 찾을수없습니다.");

                //파일이 없는경우 기본값으로 파일에 쓴다.

                //authorityServerInfo;
                //mainVideoUriInfo;
                //subVideoUriInfo;

                //dayCamCtlUriInfo;
                //micCtlUriInfo;

                //WriteIni(1);//파일쓰기

            }
        }

        public void WriteIni(int nCh)
        {
            string ch = string.Format("ch{0:d2}", nCh);

            ini.IniWriteValue(ch, "ptzserver_ipaddrFirst", this.ptzServerInfo.ipAddrFirst);
            ini.IniWriteValue(ch, "ptzserver_ipaddrSencond", this.ptzServerInfo.ipAddrSecond);
            ini.IniWriteValue(ch, "ptzserver_ipaddrThird", this.ptzServerInfo.ipAddrThird);
            ini.IniWriteValue(ch, "ptzserver_ipaddrForth", this.ptzServerInfo.ipAddrFourth);

            ini.IniWriteValue(ch, "ptzserver_port", this.ptzServerInfo.port);

            ///////////////////////////////////////////////////////////////////////////////////////////////////////
            ini.IniWriteValue(ch, "authorityserver_ipaddrFirst", this.authorityServerInfo.ipAddrFirst);
            ini.IniWriteValue(ch, "authorityserver_ipaddrSencond", this.authorityServerInfo.ipAddrSecond);
            ini.IniWriteValue(ch, "authorityserver_ipaddrThird", this.authorityServerInfo.ipAddrThird);
            ini.IniWriteValue(ch, "authorityserver_ipaddrForth", this.authorityServerInfo.ipAddrFourth);

            ini.IniWriteValue(ch, "authorityserver_port", this.authorityServerInfo.port);

            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            ini.IniWriteValue(ch, "main_rtsp_url", this.mainVideoUriInfo.uri);
            ini.IniWriteValue(ch, "sub_rtsp_url", this.subVideoUriInfo.uri);

            ///////////////////////////////////////////////////////////////////////////////////////////////////////
            ini.IniWriteValue(ch, "daycCamCtl_ipaddrFirst", this.dayCamCtlUriInfo.ipAddrFirst);
            ini.IniWriteValue(ch, "daycCamCtl_ipaddrSencond", this.dayCamCtlUriInfo.ipAddrSecond);
            ini.IniWriteValue(ch, "daycCamCtl_ipaddrThird", this.dayCamCtlUriInfo.ipAddrThird);
            ini.IniWriteValue(ch, "daycCamCtl_ipaddrForth", this.dayCamCtlUriInfo.ipAddrFourth);

            ini.IniWriteValue(ch, "daycCamCtl_id", this.dayCamCtlUriInfo.id);
            ini.IniWriteValue(ch, "daycCamCtl_pw", this.dayCamCtlUriInfo.pw);
            ///////////////////////////////////////////////////////////////////////////////////////////////////////
            ini.IniWriteValue(ch, "mic_ipaddrFirst", this.micCtlUriInfo.ipAddrFirst);
            ini.IniWriteValue(ch, "mic_ipaddrSencond", this.micCtlUriInfo.ipAddrSecond);
            ini.IniWriteValue(ch, "mic_ipaddrThird", this.micCtlUriInfo.ipAddrThird);
            ini.IniWriteValue(ch, "mic_ipaddrForth", this.micCtlUriInfo.ipAddrFourth);

            ini.IniWriteValue(ch, "mic_id", this.micCtlUriInfo.id);
            ini.IniWriteValue(ch, "mic_pw", this.micCtlUriInfo.pw);
            ///////////////////////////////////////////////////////////////////////////////////////////////////////

        }
        public void ReadIni(int nCh)
        {
            string ch = string.Format("ch{0:d2}", nCh);

            this.ptzServerInfo.ipAddrFirst = ini.IniReadValue(ch, "ptzserver_ipaddrFirst");
            this.ptzServerInfo.ipAddrSecond = ini.IniReadValue(ch, "ptzserver_ipaddrSencond");
            this.ptzServerInfo.ipAddrThird = ini.IniReadValue(ch, "ptzserver_ipaddrThird");
            this.ptzServerInfo.ipAddrFourth = ini.IniReadValue(ch, "ptzserver_ipaddrForth");

            this.ptzServerInfo.port = ini.IniReadValue(ch, "ptzserver_port");

            ///////////////////////////////////////////////////////////////////////////////////////////////////////
            this.authorityServerInfo.ipAddrFirst = ini.IniReadValue(ch, "authorityserver_ipaddrFirst");
            this.authorityServerInfo.ipAddrSecond = ini.IniReadValue(ch, "authorityserver_ipaddrSencond");
            this.authorityServerInfo.ipAddrThird = ini.IniReadValue(ch, "authorityserver_ipaddrThird");
            this.authorityServerInfo.ipAddrFourth = ini.IniReadValue(ch, "authorityserver_ipaddrForth");

            this.authorityServerInfo.port = ini.IniReadValue(ch, "authorityserver_port");

            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            this.mainVideoUriInfo.uri = ini.IniReadValue(ch, "main_rtsp_url");
            this.subVideoUriInfo.uri = ini.IniReadValue(ch, "sub_rtsp_url");

            ///////////////////////////////////////////////////////////////////////////////////////////////////////
            this.dayCamCtlUriInfo.ipAddrFirst = ini.IniReadValue(ch, "daycCamCtl_ipaddrFirst");
            this.dayCamCtlUriInfo.ipAddrSecond = ini.IniReadValue(ch, "daycCamCtl_ipaddrSencond");
            this.dayCamCtlUriInfo.ipAddrThird = ini.IniReadValue(ch, "daycCamCtl_ipaddrThird");
            this.dayCamCtlUriInfo.ipAddrFourth = ini.IniReadValue(ch, "daycCamCtl_ipaddrForth");
            this.dayCamCtlUriInfo.id = ini.IniReadValue(ch, "daycCamCtl_id");
            this.dayCamCtlUriInfo.pw = ini.IniReadValue(ch, "daycCamCtl_pw");

            ///////////////////////////////////////////////////////////////////////////////////////////////////////
            this.micCtlUriInfo.ipAddrFirst = ini.IniReadValue(ch, "mic_ipaddrFirst");
            this.micCtlUriInfo.ipAddrSecond = ini.IniReadValue(ch, "mic_ipaddrSencond");
            this.micCtlUriInfo.ipAddrThird = ini.IniReadValue(ch, "mic_ipaddrThird");
            this.micCtlUriInfo.ipAddrFourth = ini.IniReadValue(ch, "mic_ipaddrForth");
            this.micCtlUriInfo.id = ini.IniReadValue(ch, "mic_id");
            this.micCtlUriInfo.pw = ini.IniReadValue(ch, "mic_pw");
            ///////////////////////////////////////////////////////////////////////////////////////////////////////


        }
    }

    //팬틸트환경설정
    public class Speed
    {
        public Speed()
        {
            High = "";
            Mid = "";
            Low = "";
        }
        public string High;
        public string Mid;
        public string Low;
    }

    public class Gps
    {
        public Gps()
        {
            degrees = "";
            minute = "";
            second = "";
            secondDot = "";
        }
        public string degrees;
        public string minute;
        public string second;
        public string secondDot;
    }

    public class PTZEnvSetup
    {
        private IniFile ini;

        public Speed PanTiltSpeed = new Speed();
        public Speed HighZoomSpeed = new Speed();
        public Speed HighFocusSpeed = new Speed();
        public string azimuth = "";
        public string angleOfElevation = "";
        public string maxFocus = "";
        public string minFocus = "";
        public string ptLowSpeedZoomVal = "";
        public string ptMidSpeedZoomVal = "";
        public string ptHighSpeedZoomVal = "";
        public string rangeSurveillance = "";
        public string area = "";
        public string zoomPanTiltInterLocking = "";

        public Gps Lat = new Gps();
        public Gps Long = new Gps();



        public PTZEnvSetup(string name)//절대경로
        {
            int nIndex = AppDomain.CurrentDomain.BaseDirectory.LastIndexOf('\\');
            string newPath = AppDomain.CurrentDomain.BaseDirectory.Substring(0, nIndex);
            nIndex = newPath.LastIndexOf('\\');
            newPath = newPath.Substring(0, nIndex + 1);

            ini = new IniFile(newPath + name + ".ini");

            //파일이 존재하는지 확인
            // See if this file exists in the same directory.
            if (File.Exists(newPath) == true)//파일이 존재
            {
                Console.WriteLine("파일이 존재합니다.");
            }
            else
            {
                Console.WriteLine("파일을 찾을수없습니다.");

            }
        }
        public void WriteIni(int nCh)
        {
            string ch = string.Format("ch{0:d2}", nCh);

            ini.IniWriteValue(ch, "PanTiltHighSpeed", this.PanTiltSpeed.High);
            ini.IniWriteValue(ch, "PanTiltMidSpeed", this.PanTiltSpeed.Mid);
            ini.IniWriteValue(ch, "PanTiltLowSpeed", this.PanTiltSpeed.Low);

            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            ini.IniWriteValue(ch, "HighZoomHighSpeed", this.HighZoomSpeed.High);
            ini.IniWriteValue(ch, "HighZoomMidSpeed", this.HighZoomSpeed.Mid);
            ini.IniWriteValue(ch, "HighZoomLowSpeed", this.HighZoomSpeed.Low);

            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            ini.IniWriteValue(ch, "HighFocusHighSpeed", this.HighFocusSpeed.High);
            ini.IniWriteValue(ch, "HighFocusMidSpeed", this.HighFocusSpeed.Mid);
            ini.IniWriteValue(ch, "HighFocusLowSpeed", this.HighFocusSpeed.Low);

            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            ini.IniWriteValue(ch, "azimuth", this.azimuth);

            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            ini.IniWriteValue(ch, "angleOfElevation", this.angleOfElevation);

            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            ini.IniWriteValue(ch, "maxFocus", this.maxFocus);
            ini.IniWriteValue(ch, "minFocus", this.minFocus);

            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            ini.IniWriteValue(ch, "ptLowSpeedZoomVal", this.ptLowSpeedZoomVal);
            ini.IniWriteValue(ch, "ptMidSpeedZoomVal", this.ptMidSpeedZoomVal);
            ini.IniWriteValue(ch, "ptHighSpeedZoomVal", this.ptHighSpeedZoomVal);

            ini.IniWriteValue(ch, "zoomPanTiltInterLocking", zoomPanTiltInterLocking);
                        
            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            ini.IniWriteValue(ch, "rangeSurveillance", this.rangeSurveillance);

            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            ini.IniWriteValue(ch, "area", this.area);

            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            ini.IniWriteValue(ch, "latitudeDegrees", this.Lat.degrees);
            ini.IniWriteValue(ch, "latitudeMinute", this.Lat.minute);
            ini.IniWriteValue(ch, "latitudeSecond", this.Lat.second);
            ini.IniWriteValue(ch, "latitudeSecondDot", this.Lat.secondDot);

            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            ini.IniWriteValue(ch, "longitudeDegrees", this.Long.degrees);
            ini.IniWriteValue(ch, "longitudeMinute", this.Long.minute);
            ini.IniWriteValue(ch, "longitudeSecond", this.Long.second);
            ini.IniWriteValue(ch, "longitudeSecondDot", this.Long.secondDot);



    }
        public void ReadIni(int nCh)
        {

            string ch = string.Format("ch{0:d2}", nCh);

            this.PanTiltSpeed.High = ini.IniReadValue(ch, "PanTiltHighSpeed");
            this.PanTiltSpeed.Mid = ini.IniReadValue(ch, "PanTiltMidSpeed");
            this.PanTiltSpeed.Low = ini.IniReadValue(ch, "PanTiltLowSpeed");

            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            this.HighZoomSpeed.High = ini.IniReadValue(ch, "HighZoomHighSpeed");
            this.HighZoomSpeed.Mid = ini.IniReadValue(ch, "HighZoomMidSpeed");
            this.HighZoomSpeed.Low = ini.IniReadValue(ch, "HighZoomLowSpeed");


            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            this.HighFocusSpeed.High = ini.IniReadValue(ch, "HighFocusHighSpeed");
            this.HighFocusSpeed.Mid = ini.IniReadValue(ch, "HighFocusMidSpeed");
            this.HighFocusSpeed.Low = ini.IniReadValue(ch, "HighFocusLowSpeed");

            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            this.azimuth = ini.IniReadValue(ch, "azimuth");

            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            this.angleOfElevation = ini.IniReadValue(ch, "angleOfElevation");

            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            this.maxFocus = ini.IniReadValue(ch, "maxFocus");

            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            this.minFocus = ini.IniReadValue(ch, "minFocus");

            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            this.ptLowSpeedZoomVal = ini.IniReadValue(ch, "ptLowSpeedZoomVal");
            this.ptMidSpeedZoomVal = ini.IniReadValue(ch, "ptMidSpeedZoomVal");
            this.ptHighSpeedZoomVal = ini.IniReadValue(ch, "ptHighSpeedZoomVal");

            this.zoomPanTiltInterLocking = ini.IniReadValue(ch, "zoomPanTiltInterLocking");
           

            ///////////////////////////////////////////////////////////////////////////////////////////////////////
            this.rangeSurveillance = ini.IniReadValue(ch, "rangeSurveillance");

            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            this.area = ini.IniReadValue(ch, "area");

            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            this.Lat.degrees = ini.IniReadValue(ch, "latitudeDegrees");
            this.Lat.minute = ini.IniReadValue(ch, "latitudeMinute");
            this.Lat.second = ini.IniReadValue(ch, "latitudeSecond");
            this.Lat.secondDot = ini.IniReadValue(ch, "latitudeSecondDot");

            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            this.Long.degrees = ini.IniReadValue(ch, "longitudeDegrees");
            this.Long.minute = ini.IniReadValue(ch, "longitudeMinute");
            this.Long.second = ini.IniReadValue(ch, "longitudeSecond");
            this.Long.secondDot = ini.IniReadValue(ch, "longitudeSecondDot");

        }
    }
    
    public class PanoramaInfoIni
    {
        private IniFile ini;

        public int nPanoImgFovW;//파노라마 가로 화각	
        public double dPanoImgFovH;//파노라마 세로 화각		

        public double dPanoImgTiltPivotDeg;//파노라마 촬영시 세로 중심각
                                           //double	dPanoImgTopDeg;//파노라마 영상의 상측 각도
                                           //double	dPanoImgBottomDeg;//파노라마 영상의 하측 각도
                                           //  [5/9/2014 Yeun]
        public double dPanoImgStartPan;//이미지의 x=0 일때 의 팬값 리미트가 있는 팬틸트는 x=0을 0도로 촬영 못함

        public int nPanoCaptureZoomAbs;//촬영 시 줌값

        public string[] arrPanoImagePathName = {
            "", "", "", "", "", "",
            "", "", "", "", "", "",
            "", "", "", "", "", ""};

        public PanoramaInfoIni(string name)//현재경로 + name + .ini
        {
            string filePath = AppDomain.CurrentDomain.BaseDirectory + name + ".ini";
            ini = new IniFile(filePath);

            //파일이 존재하는지 확인
            // See if this file exists in the same directory.
            if (File.Exists(filePath) == true)//파일이 존재
            {
                Console.WriteLine("파일이 존재합니다.");


            }
            else
            {
                Console.WriteLine("파일을 찾을수없습니다.");

            }


        }
        public void WriteIni(int nCh)
        {
            string ch = string.Format("ch{0:d2}", nCh);

            ini.IniWriteValue(ch, "PanoImageFovWidth", this.nPanoImgFovW.ToString());
            ini.IniWriteValue(ch, "PanoImageFovHeight", this.dPanoImgFovH.ToString());
            ini.IniWriteValue(ch, "PanoImageTiltPivotDeg", this.dPanoImgTiltPivotDeg.ToString());
            ini.IniWriteValue(ch, "PanoCaptureZoomAbs", this.nPanoCaptureZoomAbs.ToString());
            
            for (int i = 0; i < 15; i++)
            {
                string strKey = String.Format("PanoImagePathName{0:d2}", i);
                ini.IniWriteValue(ch, strKey, this.arrPanoImagePathName[i]);
            }
        }

        public void ReadIni(int nCh)
        {
            string ch = string.Format("ch{0:d2}", nCh);

            string panoImageFovWidth = ini.IniReadValue(ch, "PanoImageFovWidth");
            string panoImageFovHeight = ini.IniReadValue(ch, "PanoImageFovHeight");
            string panoImageTiltPivotDeg = ini.IniReadValue(ch, "PanoImageTiltPivotDeg");
            string panoCaptureZoomAbs = ini.IniReadValue(ch, "PanoCaptureZoomAbs");
            
            string dPanoImgStartPan = ini.IniReadValue(ch, "PanoImageStartPan"); //이미지의 x=0 일때 의 팬값 리미트가 있는 팬틸트는 x=0을 0도로 촬영 못기 때문에 필요

            for (int i = 0; i < 15; i++)
            {
                string strKey = String.Format("PanoImagePathName{0:d2}", i);

                string pathName = ini.IniReadValue(ch, strKey);
                arrPanoImagePathName[i] = pathName;
            }
            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            try
            {
                nPanoImgFovW = int.Parse(panoImageFovWidth);
                dPanoImgFovH = double.Parse(panoImageFovHeight);
                dPanoImgTiltPivotDeg = double.Parse(panoImageTiltPivotDeg);
                nPanoCaptureZoomAbs = int.Parse(panoCaptureZoomAbs);
            }
            catch (Exception e)
            {

            }


        }
    }

    public class AudioFile
    {
        private IniFile ini;

        public string fileName = "";
     



        public AudioFile(string name)//절대경로
        {
            int nIndex = AppDomain.CurrentDomain.BaseDirectory.LastIndexOf('\\');
            string newPath = AppDomain.CurrentDomain.BaseDirectory.Substring(0, nIndex);
            nIndex = newPath.LastIndexOf('\\');
            newPath = newPath.Substring(0, nIndex + 1);

            ini = new IniFile(newPath + name + ".ini");

            //파일이 존재하는지 확인
            // See if this file exists in the same directory.
            if (File.Exists(newPath) == true)//파일이 존재
            {
                Console.WriteLine("파일이 존재합니다.");
            }
            else
            {
                Console.WriteLine("파일을 찾을수없습니다.");

            }
        }
        public void WriteIni(int nCh)
        {
            string ch = string.Format("ch{0:d2}", nCh);


            ini.IniWriteValue(ch, "fileName", this.fileName);
            


        }
        public void ReadIni(int nCh)
        {

            string ch = string.Format("ch{0:d2}", nCh);

          

            this.fileName = ini.IniReadValue(ch, "fileName");

           

        }
    }

    //런처 설정
    public class LauncherSetup
    {
        private IniFile ini;

    
        public string numberOfVideo = "";
        public string showMap = "";
        
        public LauncherSetup(string name)//절대경로
        {
            int nIndex = AppDomain.CurrentDomain.BaseDirectory.LastIndexOf('\\');
            string newPath = AppDomain.CurrentDomain.BaseDirectory.Substring(0, nIndex);
            //nIndex = newPath.LastIndexOf('\\');
            //newPath = newPath.Substring(0, nIndex + 1);

            ini = new IniFile(newPath + "\\" + name + ".ini");

            //파일이 존재하는지 확인
            // See if this file exists in the same directory.
            if (File.Exists(newPath) == true)//파일이 존재
            {
                Console.WriteLine("파일이 존재합니다.");
            }
            else
            {
                Console.WriteLine("파일을 찾을수없습니다.");

            }
        }
        public void WriteIni()
        {
            ini.IniWriteValue("Common", "numberOfVideo", this.numberOfVideo);
            ini.IniWriteValue("Common", "showMap", this.showMap);
        }
        public void ReadIni()
        {
            this.numberOfVideo = ini.IniReadValue("Common", "numberOfVideo");
            this.showMap = ini.IniReadValue("Common", "showMap");
        }
    }

}
