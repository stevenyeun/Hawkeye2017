using Ownskit.Applications.DrawAnywhere.Utils;
using ReadWriteIni;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Hawkeye_BIT
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        int m_nCh;

        public WindowInfoIni winInfoIni = new WindowInfoIni("BITWindowInfo");
        public SystemIpAddrInfo systemIPAddrInfo = new SystemIpAddrInfo("SystemIpAddrInfo");//IP 정보(전체시스템에서이용)

        public MainWindow()
        {
        


            InitializeComponent();

            winInfoIni.ReadIni();

            ch1Btn.IsChecked = true;

            //Minimize();
            Maximize();
        }

        private void MaximizeButton_Click(object sender, RoutedEventArgs e)
        {
            Maximize();

        }
        private void Maximize()
        {
            MaximizeButton.Visibility = Visibility.Hidden;

            //WindowStyle = WindowStyle.ToolWindow;




            Height = winInfoIni.maximizeHeight;//maximizeSize.Height;
            Width = winInfoIni.maximizeWidth;//maximizeSize.Width;

            Top = System.Windows.SystemParameters.PrimaryScreenHeight / 2 - Height / 2;
            Left = System.Windows.SystemParameters.PrimaryScreenWidth / 2 - Width / 2;


            MaximizeButton.Visibility = Visibility.Hidden;

            ChannelGroup.Visibility = Visibility.Visible;
            DeviceServerPingGroup.Visibility = Visibility.Visible;
            SystemPowerGroup.Visibility = Visibility.Visible;
            DayCamPingGroup.Visibility = Visibility.Visible;
            ThermCamPingGroup.Visibility = Visibility.Visible;
            ThermCamPowerGroup.Visibility = Visibility.Visible;

            /*
            ConnectionGroup.Visibility = Visibility.Visible;
            IrCutFilterGroup.Visibility = Visibility.Visible;
            EISGroup.Visibility = Visibility.Visible;
            ConnectionGroup.Visibility = Visibility.Visible;
            DehazeGroup.Visibility = Visibility.Visible;
            BottomButtons.Visibility = Visibility.Visible;
            */

            Topmost = true;

            WindowHideFromTaskListExt.HideFromTaskList(this);
        }
        private void Minimize()
        {
            //WindowStyle = WindowStyle.None;
            //WindowStyle = WindowStyle.SingleBorderWindow;

            //MessageBox.Show(this.minimizePoint.Y.ToString() + this.minimizePoint.X, this.minimizeSize.Height.ToString() + this.minimizeSize.Width.ToString());


            Top = winInfoIni.minimizeY;//this.minimizePoint.Y;
            Left = winInfoIni.minimizeX;
            Height = winInfoIni.minimizeHeight;
            Width = winInfoIni.minimizeWidth;

            MaximizeButton.Visibility = Visibility.Visible;

            ChannelGroup.Visibility = Visibility.Hidden;
            DeviceServerPingGroup.Visibility = Visibility.Hidden;
            SystemPowerGroup.Visibility = Visibility.Hidden;
            DayCamPingGroup.Visibility = Visibility.Hidden;
            ThermCamPingGroup.Visibility = Visibility.Hidden;
            ThermCamPowerGroup.Visibility = Visibility.Hidden;

      
            /*
            ConnectionGroup.Visibility = Visibility.Hidden;
            IrCutFilterGroup.Visibility = Visibility.Hidden;
            EISGroup.Visibility = Visibility.Hidden;
            ConnectionGroup.Visibility = Visibility.Hidden;
            DehazeGroup.Visibility = Visibility.Hidden;
            BottomButtons.Visibility = Visibility.Hidden;
            */
            //StateChanged
            // Activate();
            Topmost = true;
            //Topmost = false;

            /*
            var hWnd = new WindowInteropHelper(this).Handle;          

            Win32API.SetWindowPos(hWnd, HWND.TopMost, 0, 0, 0, 0,
                 SWP.NOMOVE);
            */
            
            WindowHideFromTaskListExt.HideFromTaskList(this);

        }
        private void Ch1Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 1;
            UpdateIpAddrPortInfo(m_nCh);
            StopPingTest(1);
            StopPingTest(2);
            StopPingTest(3);
            StopDeviceTest();
            InitStatusUI();
        }

        private void Ch2Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 2;
            UpdateIpAddrPortInfo(m_nCh);
            StopPingTest(1);
            StopPingTest(2);
            StopPingTest(3);
            StopDeviceTest();
            InitStatusUI();
        }

        private void Ch3Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 3;
            UpdateIpAddrPortInfo(m_nCh);
            StopPingTest(1);
            StopPingTest(2);
            StopPingTest(3);
            StopDeviceTest();
            InitStatusUI();
        }

        private void Ch4Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 4;
            UpdateIpAddrPortInfo(m_nCh);
            StopPingTest(1);
            StopPingTest(2);
            StopPingTest(3);
            StopDeviceTest();
            InitStatusUI();
        }

        private void Ch5Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 5;
            UpdateIpAddrPortInfo(m_nCh);        
            StopPingTest(1);
            StopPingTest(2);
            StopPingTest(3);
            StopDeviceTest();
            InitStatusUI();
        }

        private void UpdateIpAddrPortInfo(int nCh)
        {
            systemIPAddrInfo.ReadIni(nCh);

            //디바이스 서버
            string strIpAddr1 = String.Format("{0}.{1}.{2}.{3}",
                systemIPAddrInfo.ptzServerInfo.ipAddrFirst,
                systemIPAddrInfo.ptzServerInfo.ipAddrSecond,
                systemIPAddrInfo.ptzServerInfo.ipAddrThird,
                systemIPAddrInfo.ptzServerInfo.ipAddrFourth);

            DeviceServerIPAddrLabel.Content = strIpAddr1;

            DeviceServerPortLabel.Content = systemIPAddrInfo.ptzServerInfo.port.ToString();

            //주간 카메라
            string strIpAddr2 = String.Format("{0}.{1}.{2}.{3}",
              systemIPAddrInfo.dayCamCtlUriInfo.ipAddrFirst,
              systemIPAddrInfo.dayCamCtlUriInfo.ipAddrSecond,
              systemIPAddrInfo.dayCamCtlUriInfo.ipAddrThird,
              systemIPAddrInfo.dayCamCtlUriInfo.ipAddrFourth);

            DayCamIPAddrLabel.Content = strIpAddr2;

            //열상 카메라
            string strIpAddr3 = String.Format("{0}.{1}.{2}.{3}",
              systemIPAddrInfo.micCtlUriInfo.ipAddrFirst,
              systemIPAddrInfo.micCtlUriInfo.ipAddrSecond,
              systemIPAddrInfo.micCtlUriInfo.ipAddrThird,
              systemIPAddrInfo.micCtlUriInfo.ipAddrFourth);

            ThermCamIPAddrLabel.Content = strIpAddr3;
        }


        //핑 테스트
        private bool []m_bPingTestThread = { false, false, false };//핑 테스트 스레드 상태
        private void StopPingTest(int threadNumber)
        {
            m_bPingTestThread[threadNumber-1] = false;
        }
        private void StartPingTest(string strIpAddr, int threadNumber, Label label )
        {
            if (m_bPingTestThread[threadNumber - 1] == true)//이미 스레드가 돌고있으면 시작 안함
                return;

            Task.Run(() =>
            {
                m_bPingTestThread[threadNumber - 1] = true;//스레가 시작 되었음을 체크

                Ping pingSender = new Ping();
                PingOptions options = new PingOptions();

                // Use the default Ttl value which is 128,
                // but change the fragmentation behavior.
                options.DontFragment = true;

                // Create a buffer of 32 bytes of data to be transmitted.
                string data = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
                byte[] buffer = Encoding.ASCII.GetBytes(data);
                int timeout = 120;
                int nCount = 0;
                while (true)
                {
                    Thread.Sleep(1000);

                    bool bException = false;
                    string statusMessage = "";
                    if (m_bPingTestThread[threadNumber - 1] == false)
                    {
                        break;
                    }

                    PingReply reply = null;
                    try
                    {
                        reply = pingSender.Send(strIpAddr, timeout, buffer, options);
                    }
                    catch( Exception e)
                    {
                        System.Console.WriteLine(e.Message);
                        statusMessage = e.Message;
                        bException = true;
                      
                    }

                    if (bException == true)
                    {

                    }
                    else if (reply.Status == IPStatus.Success)
                    {
                        statusMessage = (++nCount).ToString() +"회 " + reply.RoundtripTime.ToString() + " ms";

                        //Console.WriteLine("Address: {0}", reply.Address.ToString());
                        //Console.WriteLine("RoundTrip time: {0}", reply.RoundtripTime);
                        //Console.WriteLine("Time to live: {0}", reply.Options.Ttl);
                        //Console.WriteLine("Don't fragment: {0}", reply.Options.DontFragment);
                        //Console.WriteLine("Buffer size: {0}", reply.Buffer.Length);

                    }
                    else//응답 실패?
                    {
                        statusMessage = (++nCount).ToString() + "회 " + "Ping 응답 실패";
                    }

                    if (!label.Dispatcher.CheckAccess())
                    {
                        this.Dispatcher.Invoke(
                          System.Windows.Threading.DispatcherPriority.Normal,
                          new Action(
                            delegate ()
                            {
                                label.Content = statusMessage;
                            }
                        ));
                    }
                    else
                    {
                        label.Content = statusMessage;
                    }


                }
            });
        }
        //





        //장비 상태 점검
        // 바이트 배열을 String으로 변환
        private string ByteToString(byte[] strByte)
        {
            string str = Encoding.Default.GetString(strByte);
            return str;
        }
        // String을 바이트 배열로 변환
        private byte[] StringToByte(string str)
        {
            byte[] StrByte = Encoding.UTF8.GetBytes(str);
            return StrByte;
        }



        //출처: http://zephie.tistory.com/11 [zephie DebugHolic]
        private bool m_bDeviceTestThread = false;//핑 테스트 스레드 상태

        private void UpdateStatusUI(Label label, string text)
        {
            if (!label.Dispatcher.CheckAccess())
            {
                this.Dispatcher.Invoke(
                  System.Windows.Threading.DispatcherPriority.Normal,
                  new Action(
                    delegate ()
                    {
                        label.Content = text;
                    }
                ));
            }
            else
            {
                label.Content = text;
            }
        }
        private void InitStatusUI()
        {
            UpdateStatusUI(PingStatusLabel, "Ping 미 수신");
            UpdateStatusUI(DayCamPingStatusLabel, "Ping 미 수신");
            UpdateStatusUI(ThermCamPingStatusLabel, "Ping 미 수신");

            UpdateStatusUI(systemPowerStatusLabel, "상태 미 수신");
            UpdateStatusUI(motorStatusLabel, "상태 미 수신");
            UpdateStatusUI(thermPowerStatusLabel, "상태 미 수신");
        }
        static string GetIntBinaryString(int n)
        {
            char[] b = new char[8];
            int pos = 7;
            int i = 0;

            while (i < 8)
            {
                if ((n & (1 << i)) != 0)
                {
                    b[pos] = '1';
                }
                else
                {
                    b[pos] = '0';
                }
                pos--;
                i++;
            }
            return new string(b);
        }

        private void StartDeviceTest(string strIpAddr, int port, Label systemPowerStatus, Label motorStatus, Label thermPowerStatus)
        {
#if true

            if (m_bDeviceTestThread == true)//이미 스레드가 돌고있으면 시작 안함
                return;

            Task.Run(() =>
            {
                m_bDeviceTestThread = true;
                int nCountSocket = 0;
                while (true)
                {
                 
                    if (m_bDeviceTestThread == false)
                    {
                        break;
                    }

                    //TCP 송신스레드
                    TcpClient tcpClient = null;
                    NetworkStream stream = null;
                    try
                    {
                        tcpClient = new TcpClient(strIpAddr, port);
                        stream = tcpClient.GetStream();
                        stream.ReadTimeout = 1000;
                        //System.Console.WriteLine("채널={0} TCP 클라이언트 소켓 원격포트={1}에 접속 성공  ", nCh, nRemotePort);
                    }
                    catch (Exception e)
                    {
                        //System.Console.WriteLine("채널={0} TCP 클라이언트 소켓 원격포트={1}에 접속 실패 " + e.Message, nCh, nRemotePort);
                        string msg = String.Format("원격포트:{0} 접속실패", port);
                        nCountSocket++;
                        UpdateStatusUI(systemPowerStatusLabel, (nCountSocket).ToString() + "회 " + msg);
                        UpdateStatusUI(thermPowerStatusLabel, (nCountSocket).ToString() + "회 " + msg);
                        UpdateStatusUI(motorStatusLabel, (nCountSocket).ToString() + "회 " + msg);
                        Thread.Sleep(1000);
                        continue;
                    }

#region 
                    InitStatusUI();
                    int nCount1 = 0;
                    int nCount2 = 0;
                    int nCount3 = 0;
                    while (true)
                    {
                      
                        if (m_bDeviceTestThread == false)
                        {
                            break;
                        }
                        string systemPowerOn = "PW=O\r";
                        string thermcamPowerOn = "TP=O\r";
                        string systemPowerCheck = "PW=?\r";
                        string motorStatusCheck = "GS=P\r";
                        string thermcamPowerCheck = "TP=?\r";

                        const int bufferSize = 1024;
                        Byte[] recvBuffer = new Byte[bufferSize];
                        string parsedCMD = "";
                       
                        try
                        {
                            //System.Console.WriteLine("TCP Send RemotePort={0}", arrAuthorityServerRemoteUdpPort[nChIndex]);

                            //시스템 전원 켜기
                            Byte[] packet1 = StringToByte(systemPowerOn);//
                            stream.Write(packet1, 0, packet1.Length);
                            Thread.Sleep(1000);
                            //패킷 분석
                            Int32 bytes = stream.Read(recvBuffer, 0, recvBuffer.Length);
                            int askFrm = U2SRProtocol.ByteToU2SRCmd(recvBuffer, out parsedCMD);
                            if (askFrm != -1 && askFrm == 1)//Get 명령만 사용 
                            {                                
                                //System.Console.WriteLine(parsedCMD);
                            }

#if true
                            //열상 전원 켜기
                            Byte[] packet2 = StringToByte(thermcamPowerOn);//
                            stream.Write(packet2, 0, packet2.Length);
                            Thread.Sleep(1000);
                            //패킷 분석
                            bytes = stream.Read(recvBuffer, 0, recvBuffer.Length);
                            askFrm = U2SRProtocol.ByteToU2SRCmd(recvBuffer, out parsedCMD);
                            if (askFrm != -1 && askFrm == 1)//Get 명령만 사용 
                            {
                               
                                //System.Console.WriteLine(parsedCMD);
                            }

                            //시스템 전원 상태 체크
                            Byte[] packet3 = StringToByte(systemPowerCheck);//
                            stream.Write(packet3, 0, packet3.Length);
                            Thread.Sleep(1000);
                            //패킷 분석
                            bytes = stream.Read(recvBuffer, 0, recvBuffer.Length);
                            askFrm = U2SRProtocol.ByteToU2SRCmd(recvBuffer, out parsedCMD);
                            if (askFrm != -1 && askFrm == 1)//Get 명령만 사용 
                            {
                                 
                                if (parsedCMD == "PW=O")
                                {
                                    UpdateStatusUI(systemPowerStatusLabel, (++nCount1).ToString() + "회 " + "전원 켜짐");
                                }
                                else if (parsedCMD == "PW=F")
                                {
                                    UpdateStatusUI(systemPowerStatusLabel, (++nCount1).ToString() + "회 " + "전원 꺼짐");
                                }
                                else
                                    UpdateStatusUI(systemPowerStatusLabel, (++nCount1).ToString() + "회 " + "상태 인식 실패");
                            }

                            //열상 전원 상태 체크
                            Byte[] packet4 = StringToByte(thermcamPowerCheck);//
                            stream.Write(packet4, 0, packet4.Length);
                            Thread.Sleep(1000);
                            //패킷 분석
                            bytes = stream.Read(recvBuffer, 0, recvBuffer.Length);
                            askFrm = U2SRProtocol.ByteToU2SRCmd(recvBuffer, out parsedCMD);
                            if (askFrm != -1 && askFrm == 1)//Get 명령만 사용 
                            {
                                if (parsedCMD == "TP=O")
                                {
                                    UpdateStatusUI(thermPowerStatusLabel, (++nCount2).ToString() + "회 " + "전원 켜짐");
                                }
                                else if (parsedCMD == "TP=F")
                                {
                                    UpdateStatusUI(thermPowerStatusLabel, (++nCount2).ToString() + "회 " + "전원 꺼짐");
                                }
                                else
                                    UpdateStatusUI(thermPowerStatusLabel, (++nCount2).ToString() + "회 " + "상태 인식 실패");
                                //System.Console.WriteLine(parsedCMD);
                            }

                            //모터 상태 인식 체크
                            Byte[] packet5 = StringToByte(motorStatusCheck);//
                            stream.Write(packet5, 0, packet5.Length);
                            Thread.Sleep(1000);

                            //패킷 분석
                            bytes = stream.Read(recvBuffer, 0, recvBuffer.Length);
                            askFrm = U2SRProtocol.ByteToU2SRCmd(recvBuffer, out parsedCMD);
                            if (askFrm != -1 && askFrm == 1)//Get 명령만 사용 
                            {
                                // [40] => [64]                              
                                int value = Convert.ToInt32(parsedCMD, 16);//Hexa to Dec                          

                                // [64] => [00000010]
                                string binary = GetIntBinaryString(value);//Dec to Bin
                                string panMotorInitStatus = binary.Substring(5, 1);
                                if (panMotorInitStatus == "1")
                                {
                                    UpdateStatusUI(motorStatusLabel, (++nCount3).ToString() + "회 " + "초기화 미완료");
                                }
                                else if (panMotorInitStatus == "0")
                                {
                                    UpdateStatusUI(motorStatusLabel, (++nCount3).ToString() + "회 " + "초기화 완료");
                                }
                                else
                                    UpdateStatusUI(motorStatusLabel, (++nCount3).ToString() + "회 " + "상태 인식 실패");

                            }
#endif






                            //System.Console.WriteLine("채널={0} TCP 클라이언트 소켓 원격 포트={1}에 패킷 전송함", nCh, nRemotePort);
                        }
                        catch (Exception e)
                        {
                            System.Console.WriteLine(e.Message);
                            //System.Console.WriteLine("TCP Send Exception RemotePort={0} " + e.Message, arrAuthorityServerRemoteUdpPort[nChIndex]);
                            //System.Console.WriteLine("채널={0} TCP 클라이언트 소켓 송신 스레드 Exception 원격 포트={1}" + e.Message, nCh, nRemotePort);
                        }




                        Thread.Sleep(1000);
                    }
#endregion
                }


            });
#endif
                        }
        private void StopDeviceTest()
        {
            m_bDeviceTestThread = false;
        }

        private void StatusCheckStart_Click(object sender, RoutedEventArgs e)
        {
            int nCh = m_nCh;

            //채널에 맞늗 아이피 읽어오기
            systemIPAddrInfo.ReadIni(nCh);


            //디바이스 서버 핑 테스트 시작
            string strIpAddr = String.Format("{0}.{1}.{2}.{3}",
                systemIPAddrInfo.ptzServerInfo.ipAddrFirst,
                systemIPAddrInfo.ptzServerInfo.ipAddrSecond,
                systemIPAddrInfo.ptzServerInfo.ipAddrThird,
                systemIPAddrInfo.ptzServerInfo.ipAddrFourth);                    
            
            StartPingTest(strIpAddr, 1, PingStatusLabel);
            ////////////////////////////////////////////////////////////

            //주간카메라 핑테스트 시작
            strIpAddr = String.Format("{0}.{1}.{2}.{3}",
           systemIPAddrInfo.dayCamCtlUriInfo.ipAddrFirst,
           systemIPAddrInfo.dayCamCtlUriInfo.ipAddrSecond,
           systemIPAddrInfo.dayCamCtlUriInfo.ipAddrThird,
           systemIPAddrInfo.dayCamCtlUriInfo.ipAddrFourth);

            StartPingTest(strIpAddr, 2, DayCamPingStatusLabel);
            //////////////////////////////////////////////////////////////////

            //비디오서버 핑테스트 시작
            strIpAddr = String.Format("{0}.{1}.{2}.{3}",
      systemIPAddrInfo.micCtlUriInfo.ipAddrFirst,
      systemIPAddrInfo.micCtlUriInfo.ipAddrSecond,
      systemIPAddrInfo.micCtlUriInfo.ipAddrThird,
      systemIPAddrInfo.micCtlUriInfo.ipAddrFourth);

            StartPingTest(strIpAddr, 3, ThermCamPingStatusLabel);
            ///////////////////////////////////////////////////////////////////////


            //장비 상태 점검 시작      
            strIpAddr = String.Format("{0}.{1}.{2}.{3}",
                systemIPAddrInfo.ptzServerInfo.ipAddrFirst,
                systemIPAddrInfo.ptzServerInfo.ipAddrSecond,
                systemIPAddrInfo.ptzServerInfo.ipAddrThird,
                systemIPAddrInfo.ptzServerInfo.ipAddrFourth);
            int port = 0;
            try
            {
                port = int.Parse(systemIPAddrInfo.ptzServerInfo.port);
            }
            catch
            {

            }       

            StartDeviceTest( strIpAddr, port, systemPowerStatusLabel, motorStatusLabel, thermPowerStatusLabel );
            
        }

        private void StatusCheckStop_Click(object sender, RoutedEventArgs e)
        {
            StopPingTest(1);
            StopPingTest(2);
            StopPingTest(3);

            StopDeviceTest();
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            //e.Cancel = true;
            StopPingTest(1);
            StopPingTest(2);
            StopPingTest(3);

            StopDeviceTest();
            //Minimize();
        }

        private void CloseBtn_Click(object sender, RoutedEventArgs e)
        {

            App.Current.MainWindow.Close();
            // Application.Current.Shutdown();
        }
    }
}
