using AuthorityComm;
using Ini;
using Ownskit.Applications.DrawAnywhere.Utils;
using ReadWriteIni;
using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls.Primitives;
using System.Windows.Interop;
using System.Windows.Threading;

namespace Hawkeye_PTZController
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {

        //https://msdn.microsoft.com/ko-kr/library/system.net.sockets.udpclient.beginreceive(v=vs.110).aspx?cs-save-lang=1&cs-lang=csharp#code-snippet-2
        //https://gist.github.com/leandrosilva/656054
        //http://it-jerryfamily.tistory.com/entry/Program%EB%B9%84%EB%8F%99%EA%B8%B0-%EC%84%9C%EB%B2%84%ED%81%B4%EB%9D%BC%EC%9D%B4%EC%96%B8%ED%8A%B8-msdn-%EC%98%88%EC%A0%9C-%EC%9C%88%EB%8F%84%EC%9A%B0-%EB%B2%84%EC%A0%84

     
        public char[] srcName = new char[AuthorityDefine.SRC_NAME_LEN];

        public UDPSocketForRelayServerComm udpSock = new UDPSocketForRelayServerComm(30001);

        public WindowInfoIni winInfoIni = new WindowInfoIni("PTZControllerWindowInfo");
        public PTZEnvSetup systemPTZEnvSetup = new PTZEnvSetup("PTZEnvSetup");
        int m_nCh = 0;
        int m_nCameraType = 1;
        bool[] m_bArrPushPanTiltBtn = new bool[5];
        bool[] m_bArrPushZoomFocusBtn = new bool[5];
        double[] m_dArrDigitalZoom = new double[5];
        bool m_bDigitalZoomThreadRun = false; 

        int m_nPanTiltSpd = 0;
        int m_nFocusSpd = 0;

     
        public MainWindow()
        {
            InitializeComponent();

            InitAppUI();
            InitAppData();
            InitEventHandler();

            udpSock.CreateUDPSocket();

          



            for (int i = 0; i < 5; i++)
            {
                m_bArrPushPanTiltBtn[i] = false;
                m_bArrPushZoomFocusBtn[i] = false;
                m_dArrDigitalZoom[i] = 1;
                CreateReqPanTiltThread(i + 1);
                CreateReqZoomFocusThread(i + 1);
                CreatePacketParsingThread(i + 1);
            }


            winInfoIni.ReadIni();


            //PTZ 저장 속도 읽어오기

            //속도 셋팅
            //SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_PT_SPEED, "1000");
            //SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_ZOOM_SPEED, "500");
            //SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_FOCUS_SPEED, "500");

            WindowHideFromTaskListExt.HideFromTaskList(this);
        }

      

        private void InitAppUI()
        {
            
            Top = winInfoIni.maximizeY;
            Left = winInfoIni.maximizeX;
            Height = winInfoIni.maximizeHeight;
            Width = winInfoIni.maximizeWidth;            
        }

        private void InitAppData()
        {   
            ch1Btn.IsChecked = true;
            camera1Btn.IsChecked = true;
            //PanTiltHighSpdBtn.IsChecked = true;
            //FocusHighSpdBtn.IsChecked = true;


        }
        private void CheckPanTiltSpd(int nChoice)
        {
            switch (nChoice)
            {
                case 1:
                    PanTiltHighSpdBtn.IsChecked = true;
                    PanTiltMidSpdBtn.IsChecked = false;
                    PanTiltLowSpdBtn.IsChecked = false;
                    break;
                case 2:
                    PanTiltHighSpdBtn.IsChecked = false;
                    PanTiltMidSpdBtn.IsChecked = true;
                    PanTiltLowSpdBtn.IsChecked = false;
                    break;
                case 3:
                    PanTiltHighSpdBtn.IsChecked = false;
                    PanTiltMidSpdBtn.IsChecked = false;
                    PanTiltLowSpdBtn.IsChecked = true;
                    break;
            }
        }
        private void CheckFocusSpd(int nChoice)
        {
            switch (nChoice)
            {
                case 1:
                    FocusHighSpdBtn.IsChecked = true;
                    FocusMidSpdBtn.IsChecked = false;
                    FocusLowSpdBtn.IsChecked = false;
                    break;
                case 2:
                    FocusHighSpdBtn.IsChecked = false;
                    FocusMidSpdBtn.IsChecked = true;
                    FocusLowSpdBtn.IsChecked = false;
                    break;
                case 3:
                    FocusHighSpdBtn.IsChecked = false;
                    FocusMidSpdBtn.IsChecked = false;
                    FocusLowSpdBtn.IsChecked = true;
                    break;
            }
        }

        private void InitEventHandler()
        {
            PanTiltLeftUpBtn.AddHandler(UIElement.MouseLeftButtonDownEvent, new RoutedEventHandler(PanTiltLeftUpBtn_Click), true);
            PanTiltUpBtn.AddHandler(UIElement.MouseLeftButtonDownEvent, new RoutedEventHandler(PanTiltUpBtn_Click), true);
            PanTiltRightUpBtn.AddHandler(UIElement.MouseLeftButtonDownEvent, new RoutedEventHandler(PanTiltRightUpBtn_Click), true);
            PanTiltLeftBtn.AddHandler(UIElement.MouseLeftButtonDownEvent, new RoutedEventHandler(PanTiltLeftBtn_Click), true);
            PanTiltRightBtn.AddHandler(UIElement.MouseLeftButtonDownEvent, new RoutedEventHandler(PanTiltRightBtn_Click), true);
            PanTiltLeftDownBtn.AddHandler(UIElement.MouseLeftButtonDownEvent, new RoutedEventHandler(PanTiltLeftDownBtn_Click), true);
            PanTiltDownBtn.AddHandler(UIElement.MouseLeftButtonDownEvent, new RoutedEventHandler(PanTiltDownBtn_Click), true);
            PanTiltRightDownBtn.AddHandler(UIElement.MouseLeftButtonDownEvent, new RoutedEventHandler(PanTiltRightDownBtn_Click), true);

            PanTiltStopBtn.AddHandler(UIElement.MouseLeftButtonDownEvent, new RoutedEventHandler(PanTiltStopBtn_Click), true);

            PanTiltLeftUpBtn.AddHandler(UIElement.MouseLeftButtonUpEvent, new RoutedEventHandler(PanTiltStopBtn_Click), true);
            PanTiltUpBtn.AddHandler(UIElement.MouseLeftButtonUpEvent, new RoutedEventHandler(PanTiltStopBtn_Click), true);
            PanTiltRightUpBtn.AddHandler(UIElement.MouseLeftButtonUpEvent, new RoutedEventHandler(PanTiltStopBtn_Click), true);
            PanTiltLeftBtn.AddHandler(UIElement.MouseLeftButtonUpEvent, new RoutedEventHandler(PanTiltStopBtn_Click), true);
            PanTiltRightBtn.AddHandler(UIElement.MouseLeftButtonUpEvent, new RoutedEventHandler(PanTiltStopBtn_Click), true);
            PanTiltLeftDownBtn.AddHandler(UIElement.MouseLeftButtonUpEvent, new RoutedEventHandler(PanTiltStopBtn_Click), true);
            PanTiltDownBtn.AddHandler(UIElement.MouseLeftButtonUpEvent, new RoutedEventHandler(PanTiltStopBtn_Click), true);
            PanTiltRightDownBtn.AddHandler(UIElement.MouseLeftButtonUpEvent, new RoutedEventHandler(PanTiltStopBtn_Click), true);
            PanTiltDownBtn.AddHandler(UIElement.MouseLeftButtonUpEvent, new RoutedEventHandler(PanTiltStopBtn_Click), true);


            ZoomTeleBtn.AddHandler(UIElement.MouseLeftButtonDownEvent, new RoutedEventHandler(ZoomTeleBtn_Click), true);
            ZoomWideBtn.AddHandler(UIElement.MouseLeftButtonDownEvent, new RoutedEventHandler(ZoomWideBtn_Click), true);
            FocusNearBtn.AddHandler(UIElement.MouseLeftButtonDownEvent, new RoutedEventHandler(FocusNearBtn_Click), true);
            FocusFarBtn.AddHandler(UIElement.MouseLeftButtonDownEvent, new RoutedEventHandler(FocusFarBtn_Click), true);
            //zfstop.AddHandler(UIElement.MouseLeftButtonDownEvent, new RoutedEventHandler(zfStopBtn), true);

            ZoomTeleBtn.AddHandler(UIElement.MouseLeftButtonUpEvent, new RoutedEventHandler(ZFStopBtn_Click), true);
            ZoomWideBtn.AddHandler(UIElement.MouseLeftButtonUpEvent, new RoutedEventHandler(ZFStopBtn_Click), true);
            FocusNearBtn.AddHandler(UIElement.MouseLeftButtonUpEvent, new RoutedEventHandler(FocusStopBtn_Click), true);
            FocusFarBtn.AddHandler(UIElement.MouseLeftButtonUpEvent, new RoutedEventHandler(FocusStopBtn_Click), true);
        }
        private void CreateReqPanTiltThread(int nCh)
        {
            Task.Run(() =>
            {
                while (true)
                {
                    if (m_bArrPushPanTiltBtn[nCh - 1] == true)
                    {
                        //System.Console.WriteLine("버튼 눌림");
                        SendAuthorityCmd(nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_REQ);
                    }
                    else
                    {
                        //System.Console.WriteLine("버튼 안 눌림");
                    }

                    Thread.Sleep(2000);
                }
            });
        }
        private void CreateReqZoomFocusThread(int nCh)
        {
            Task.Run(() =>
            {
                while (true)
                {
                    if (m_bArrPushZoomFocusBtn[nCh - 1] == true)
                    {
                        //System.Console.WriteLine("버튼 눌림");
                        SendAuthorityCmd(nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_DAYZF_POS_REQ);
                    }
                    else
                    {
                        //System.Console.WriteLine("버튼 안 눌림");
                    }

                    Thread.Sleep(2000);
                }
            });
        }
        private void CreatePacketParsingThread(int nCh)
        {
            //Parse
            Task.Run(() =>
            {
                while (true)
                {
                    //if (udpSock.queuePacketFromRelayServer.Count > 0)
                    if (udpSock.GetNumberOfPacket(nCh) > 0)
                    {
                        //IPEndPoint ep = udpSock.queueIPEndPointFromRelayServer.Dequeue();

                        Console.WriteLine("Parse Packet {0}", nCh);
                        byte[] packet = udpSock.PopPacket(nCh);
                        if (packet == null)
                            continue;

                        if (m_nCh != nCh)//선택된 채널과 현재 스레드의 채널이 같을 경우에만 디스플레이
                        {
                            continue;
                        }

                        string str = Encoding.UTF8.GetString(packet);
                        //Console.WriteLine("Port={0} Received={1}", ep.Port, str.Length);
                        


                        AUTHORITY_PACKET AuthPacket;
                        //AuthPacket.GetType()
                        //typeof(AUTHORITY_PACKET)
                        AuthPacket = (AUTHORITY_PACKET)AuthorityCommUtil.ByteToStructure(packet, typeof(AUTHORITY_PACKET));
                        string name = AuthorityCommUtil.ByteToString(AuthPacket.srcName.name);
                        string data = AuthorityCommUtil.ByteToString(AuthPacket.authorityData.data);
                        //System.Console.WriteLine(data.Replace('\0', ' '));
                        //System.Console.WriteLine(name.Replace('\0', ' '));

                        if (AuthPacket.byCmdGroup == CommandPTZReqResp.CMDGROUP_PTZREQ)
                        {
                            if (AuthPacket.byCmdType == CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_RESP)
                            {
                                this.Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
                                {
                                    int index1 = data.IndexOf(';');
                                    //int index2 = data.IndexOf('\0');

                                    if( m_nCameraType == 1)
                                    {
                                        PanLabel.Content = "방위각 " + data.Substring(0, index1);
                                        TiltLabel.Content = "고저각 " + data.Substring(index1 + 1, data.Length - (index1 + 1));
                                    }
                                 
                                }));
                            }
                            else if (AuthPacket.byCmdType == CommandPTZReqResp.CMDTYPE_PTZREQ_DAYZF_POS_RESP)
                            {
                                this.Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
                                {
                                    if (m_nCameraType == 1)
                                    {
                                        int index1 = data.IndexOf(';');
                                        //int index2 = data.IndexOf('\0');
                                        ZoomLabel.Content = "줌 " + data.Substring(0, index1);
                                        FocusLabel.Content = "포커스 " + data.Substring(index1 + 1, data.Length - (index1 + 1));

                                        try
                                        {
                                            int nCurZoom = int.Parse(data.Substring(0, index1));
                                            int nPtHighSpdZoom = int.Parse(systemPTZEnvSetup.ptHighSpeedZoomVal);
                                            int nPtMidSpdZoom = int.Parse(systemPTZEnvSetup.ptMidSpeedZoomVal);
                                            int nPtLowSpdZoom = int.Parse(systemPTZEnvSetup.ptLowSpeedZoomVal);

                                            //nPtHighSpdZoom nPtMidSpdZoom ~ nPtLowSpdZoom
                                            //84   ~        500    ~       600 ~ 

                                            //줌값이랑 팬틸트 속도 연동
                                           
                                            if( systemPTZEnvSetup.zoomPanTiltInterLocking == "True" )
                                            {
                                                if (nCurZoom >= nPtLowSpdZoom && nCurZoom <= nPtMidSpdZoom)
                                                {
                                                    SetPTHighSpd();
                                                }
                                                else if (nCurZoom >= nPtMidSpdZoom && nCurZoom <= nPtHighSpdZoom)
                                                {
                                                    SetPTMidSpd();
                                                }
                                                else if (nCurZoom >= nPtHighSpdZoom)
                                                {
                                                    SetPTLowSpd();
                                                }
                                            }
                                         
                                        }
                                        catch (Exception e)
                                        {

                                        }
                                    }
                                    
                                   
                                }));

                                
                            }
                            else if (AuthPacket.byCmdType == CommandPTZReqResp.CMDTYPE_PTZREQ_MAINBOARD_STATUS_RESP)
                            {
                                System.Console.WriteLine(data);
                            }
                        }
                        else if(AuthPacket.byCmdGroup == CommandThermCam.CMDGROUP_THERMCAM)
                        {
                            if (AuthPacket.byCmdType == CommandThermCam.CMDTYPE_THERMCAM_DZOOM_RESP)
                            {
                                this.Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
                                {
                                    m_dArrDigitalZoom[m_nCh - 1] = double.Parse(data);
                                    string strZoom = String.Format("줌 {0:0.0}", m_dArrDigitalZoom[m_nCh - 1]);
                                    ZoomLabel.Content = strZoom;

                                }));
                            }
                        }

                    
                    }

                    Thread.Sleep(1);
                }
            });
        }
        private void SendAuthorityCmd(int nCh, byte byCmdGroup, byte byCmdType, string authData="")
        {
            AUTHORITY_PACKET authorityPacket = AuthorityCommUtil.MakeAuthorityPacket("stevenYeun",
          byCmdGroup, byCmdType,
          authData);

            byte[] packet = AuthorityCommUtil.StructureToByte(authorityPacket);

            try
            {
                udpSock.SendToRelayServer(nCh, packet);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }
        /*
        private void RecvAuthorityCmd()
        {
            AUTHORITY_PACKET authorityPacket;

            byte[] packet = AuthorityCommUtil.StructureToByte(authorityPacket);

            try
            {
                udpSock.ReceiveFromRelayServer(nCh, packet);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }
        */
        private void UpdateChangeChInfo()
        {
            if( m_nCameraType == 1 )
            {
             
                PanLabel.Content = "방위각 000.0000";
                TiltLabel.Content = "고저각 +00.0000";
                ZoomLabel.Content = "줌 00000";
                FocusLabel.Content = "포커스 00000";

                SendAuthorityCmd(m_nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_DAYZF_POS_REQ);

                CheckFocusSpd(2);
                m_nFocusSpd = 2;
                //저장되어있는 포커스 속도 읽기
                systemPTZEnvSetup.ReadIni(m_nCh);
                SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_FOCUS_SPEED, systemPTZEnvSetup.HighFocusSpeed.Mid);
            }
            else if(m_nCameraType == 2)
            {
                PanLabel.Content = "방위각 000.0000";
                TiltLabel.Content = "고저각 +00.0000";

                string strZoom = String.Format("줌 {0:0.0}", m_dArrDigitalZoom[m_nCh - 1]);
                ZoomLabel.Content = strZoom;
                FocusLabel.Content = "";

                SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_DZOOM_REQ);
            }
         

            SendAuthorityCmd(m_nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_REQ);
          
            CheckPanTiltSpd(2);
            m_nPanTiltSpd = 2;
            //저장되어있는 팬틸트 속도 읽기
            systemPTZEnvSetup.ReadIni(m_nCh);
            SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_PT_SPEED, systemPTZEnvSetup.PanTiltSpeed.Mid);

            
        }
        private void Ch1Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 1;

            UpdateChangeChInfo();
        }

        private void Ch2Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 2;

            UpdateChangeChInfo();
        }

        private void Ch3Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 3;

            UpdateChangeChInfo();
        }

        private void Ch4Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 4;
            UpdateChangeChInfo();
        }

        private void Ch5Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 5;
            UpdateChangeChInfo();
        }



        private void SetPTHighSpd()
        {
            CheckPanTiltSpd(1);
            m_nPanTiltSpd = 1;

            //저장되어있는 팬틸트 속도 읽기
            systemPTZEnvSetup.ReadIni(m_nCh);

            SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_PT_SPEED, systemPTZEnvSetup.PanTiltSpeed.High);
        }
        private void SetPTMidSpd()
        {
            CheckPanTiltSpd(2);
            m_nPanTiltSpd = 2;
            //저장되어있는 팬틸트 속도 읽기
            systemPTZEnvSetup.ReadIni(m_nCh);

            SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_PT_SPEED, systemPTZEnvSetup.PanTiltSpeed.Mid);
        }
        private void SetPTLowSpd()
        {
            CheckPanTiltSpd(3);
            m_nPanTiltSpd = 3;

            //저장되어있는 팬틸트 속도 읽기
            systemPTZEnvSetup.ReadIni(m_nCh);
            SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_PT_SPEED, systemPTZEnvSetup.PanTiltSpeed.Low);
        }
        private void PanTiltHighSpdBtn_Click(object sender, RoutedEventArgs e)
        {
            SetPTHighSpd();
        }

        private void PanTiltMidSpdBtn_Click(object sender, RoutedEventArgs e)
        {
            SetPTMidSpd();
        }

        private void PanTiltLowSpdBtn_Click(object sender, RoutedEventArgs e)
        {
            SetPTLowSpd();
        }

      
        private void FocusHighSpdBtn_Click(object sender, RoutedEventArgs e)
        {
          
            CheckFocusSpd(1);
            m_nFocusSpd = 1;
            //저장되어있는 팬틸트 속도 읽기
            systemPTZEnvSetup.ReadIni(m_nCh);
            SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_FOCUS_SPEED, systemPTZEnvSetup.HighFocusSpeed.High);
           
        }

        private void FocusMidSpdBtn_Click(object sender, RoutedEventArgs e)
        {
            CheckFocusSpd(2);
            m_nFocusSpd = 2;
            //저장되어있는 팬틸트 속도 읽기
            systemPTZEnvSetup.ReadIni(m_nCh);
            SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_FOCUS_SPEED, systemPTZEnvSetup.HighFocusSpeed.Mid);
        }

        private void FocusLowSpdBtn_Click(object sender, RoutedEventArgs e)
        {
            CheckFocusSpd(3);
            m_nFocusSpd = 3;
            //저장되어있는 팬틸트 속도 읽기
            systemPTZEnvSetup.ReadIni(m_nCh);
            SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_FOCUS_SPEED, systemPTZEnvSetup.HighFocusSpeed.Low);
        }

        //줌/포커스
        private void ZFStopBtn_Click(object sender, RoutedEventArgs e)
        {
            if (camera2Btn.IsChecked == true)
            {
                m_bDigitalZoomThreadRun = false;
            }
            else
            {
                m_bArrPushZoomFocusBtn[m_nCh - 1] = false;
                SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_ZOOM_STOP, m_nCameraType.ToString());
                Thread.Sleep(500);
                SendAuthorityCmd(m_nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_DAYZF_POS_REQ);
            }
        }
        //포커스
        private void FocusStopBtn_Click(object sender, RoutedEventArgs e)
        {
            SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_FOCUS_STOP, m_nCameraType.ToString());
        }

        private void ZoomTeleBtn_Click(object sender, RoutedEventArgs e)
        {
            if (camera2Btn.IsChecked == true)
            {
                if (m_bDigitalZoomThreadRun == true)
                    return;
                Task.Run(() =>
                {
                    m_bDigitalZoomThreadRun = true;
                    while (true)
                    {

                        if (m_dArrDigitalZoom[m_nCh - 1] >= 4.0)
                        {
                            m_bDigitalZoomThreadRun = false;
                            return;
                        }
                        else
                        {
                            m_dArrDigitalZoom[m_nCh - 1] += 0.1;
                            string strZoom = String.Format("{0:0.0}", m_dArrDigitalZoom[m_nCh - 1]);
                            SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_DZOOM, strZoom);

                            this.Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
                            {
                                ZoomLabel.Content = "줌 " + strZoom;
                                System.Console.WriteLine(strZoom);

                            }));
                            //textZoom.Content = zoom.ToString();
                        }

                        if (m_bDigitalZoomThreadRun == false)
                            return;
                        Thread.Sleep(200);
                        //Console.WriteLine("GetNumberOfPacket Sleep {0}", nCh);
                    }
                });

            }
            else
            {
                m_bArrPushZoomFocusBtn[m_nCh - 1] = true;
                SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_ZOOM_TELE, m_nCameraType.ToString());
            }

        }
        private void ZoomWideBtn_Click(object sender, RoutedEventArgs e)
        {
            if (camera2Btn.IsChecked == true)
            {
                if (m_bDigitalZoomThreadRun == true)
                    return;
                Task.Run(() =>
                {
                    m_bDigitalZoomThreadRun = true;
                    while (true)
                    {
                        if (m_dArrDigitalZoom[m_nCh - 1] <= 1.0)
                        {
                            m_bDigitalZoomThreadRun = false;
                            return;
                        }
                        else
                        {
                            m_dArrDigitalZoom[m_nCh - 1] -= 0.1;
                            string strZoom = String.Format("{0:0.0}", m_dArrDigitalZoom[m_nCh - 1]);
                            SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_DZOOM, strZoom);
                            //textZoom.Content = zoom.ToString();
                            this.Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
                            {
                                ZoomLabel.Content = "줌 " + strZoom;
                                System.Console.WriteLine(strZoom);
                            }));
                        }

                        if (m_bDigitalZoomThreadRun == false)
                            return;

                        Thread.Sleep(200);
                        //Console.WriteLine("GetNumberOfPacket Sleep {0}", nCh);
                    }
                });
            }
            else
            {
                m_bArrPushZoomFocusBtn[m_nCh - 1] = true;
                SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_ZOOM_WIDE, m_nCameraType.ToString());
            }
        }

        private void FocusNearBtn_Click(object sender, RoutedEventArgs e)
        {
            m_bArrPushZoomFocusBtn[m_nCh - 1] = true;
            SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_FOCUS_NEAR, m_nCameraType.ToString());
        }

        private void FocusFarBtn_Click(object sender, RoutedEventArgs e)
        {
            m_bArrPushZoomFocusBtn[m_nCh - 1] = true;
            SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_FOCUS_FAR, m_nCameraType.ToString());
        }

      

        //팬틸트
        private void PanTiltLeftUpBtn_Click(object sender, RoutedEventArgs e)
        {            
            m_bArrPushPanTiltBtn[m_nCh - 1] = true;
            SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_PT_LU);
            SendAuthorityCmd(m_nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_REQ);
        }

        private void PanTiltUpBtn_Click(object sender, RoutedEventArgs e)
        {
            m_bArrPushPanTiltBtn[m_nCh - 1] = true;
            SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_TILT_UP);
            SendAuthorityCmd(m_nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_REQ);
        }

        private void PanTiltRightUpBtn_Click(object sender, RoutedEventArgs e)
        {
            m_bArrPushPanTiltBtn[m_nCh - 1] = true;
            SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_PT_RU);
            SendAuthorityCmd(m_nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_REQ);
        }

        private void PanTiltLeftBtn_Click(object sender, RoutedEventArgs e)
        {
            m_bArrPushPanTiltBtn[m_nCh - 1] = true;
            SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_PAN_LEFT);
            SendAuthorityCmd(m_nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_REQ);
        }

        private void PanTiltRightBtn_Click(object sender, RoutedEventArgs e)
        {
            m_bArrPushPanTiltBtn[m_nCh - 1] = true;
            SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_PAN_RIGHT);
            SendAuthorityCmd(m_nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_REQ);
        }

        private void PanTiltLeftDownBtn_Click(object sender, RoutedEventArgs e)
        {
            m_bArrPushPanTiltBtn[m_nCh - 1] = true;
            SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_PT_LD);
            SendAuthorityCmd(m_nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_REQ);
        }

        private void PanTiltDownBtn_Click(object sender, RoutedEventArgs e)
        {
            m_bArrPushPanTiltBtn[m_nCh - 1] = true;
            SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_TILT_DOWN);
            SendAuthorityCmd(m_nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_REQ);
        }

        private void PanTiltRightDownBtn_Click(object sender, RoutedEventArgs e)
        {
            m_bArrPushPanTiltBtn[m_nCh - 1] = true;
            SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_PT_RD);
            SendAuthorityCmd(m_nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_REQ);
        }

        private void PanTiltStopBtn_Click(object sender, RoutedEventArgs e)
        {
            m_bArrPushPanTiltBtn[m_nCh - 1] = false;
            SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_PT_STOP);
            Thread.Sleep(500);
            SendAuthorityCmd(m_nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_REQ);
        }

        private void Camera1Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCameraType = 1;


            FocusHighSpdBtn.Visibility = Visibility.Visible;
            FocusMidSpdBtn.Visibility = Visibility.Visible;
            FocusLowSpdBtn.Visibility = Visibility.Visible;
            FocusLabel.Visibility = Visibility.Visible;

            UpdateChangeChInfo();
        }

        private void Camera2Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCameraType = 2;
         
            FocusHighSpdBtn.Visibility = Visibility.Hidden;
            FocusMidSpdBtn.Visibility = Visibility.Hidden;
            FocusLowSpdBtn.Visibility = Visibility.Hidden;
            FocusLabel.Visibility = Visibility.Hidden;
            SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_DZOOM_REQ);

            UpdateChangeChInfo();
        }









        /*
        byte[] getBytes(AUTHORITY_PACKET str)
        {
            int size = Marshal.SizeOf(str);
            byte[] arr = new byte[size];

            IntPtr ptr = Marshal.AllocHGlobal(size);
            Marshal.StructureToPtr(str, ptr, true);
            Marshal.Copy(ptr, arr, 0, size);
            Marshal.FreeHGlobal(ptr);
            return arr;
        }
      */

        /*
    private void Button_Click(object sender, RoutedEventArgs e)
    {
        int nCh = 1;




        AUTHORITY_PACKET authorityPacket = AuthorityCommUtil.MakeAuthorityPacket(1, "stevenYeun",
            CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_TILT_UP,
            "N37234502");

        byte[] packet = AuthorityCommUtil.StructureToByte(authorityPacket);
        //byte[] packet = ObjectToByte(authorityPacket);

        try
        {
            udpSock.SendToRelayServer(nCh, packet);
            //clientSocket.Send(buffer, buffer.Length, "127.255.255.255", 1472);
            //clientSocket.Send(packet, packet.Length, "127.0.0.1", 1472);
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.ToString());
        }
    }
    */
    }
}
