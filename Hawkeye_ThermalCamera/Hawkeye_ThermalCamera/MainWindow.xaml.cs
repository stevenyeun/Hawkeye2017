using AuthorityComm;
using Hawkeye_PTZController;
using Ownskit.Applications.DrawAnywhere.Utils;
using ReadWriteIni;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
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
using System.Windows.Threading;

namespace Hawkeye_ThermalCamera
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();


            Minimize();

            udpSock.CreateUDPSocket();
            for (int i = 0; i < 5; i++) CreatePacketParsingThread(i + 1);
#if false
            for (int i = 0; i < 5; i++) CreatePacketParsingThread(i + 1);
            this.sliderContrast.ValueChanged += new RoutedPropertyChangedEventHandler<double>(sliderContrast_ValueChanged);
            this.sliderBrightness.ValueChanged += new RoutedPropertyChangedEventHandler<double>(sliderBrightness_ValueChanged);
            this.sliderDDE.ValueChanged += new RoutedPropertyChangedEventHandler<double>(sliderDDE_ValueChanged);
            this.sliderACE.ValueChanged += new RoutedPropertyChangedEventHandler<double>(sliderACE_ValueChanged);
            this.sliderSSO.ValueChanged += new RoutedPropertyChangedEventHandler<double>(sliderSSO_ValueChanged);
#endif
        }

        private void sliderContrast_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
          //  textContrast.Content = ((int)e.NewValue).ToString();
        }

        private void sliderBrightness_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
          //  textBrightness.Content = ((int)e.NewValue).ToString();
        }

        private void sliderDDE_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
           // textDDE.Content = ((int)e.NewValue).ToString();
        }

        private void sliderACE_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            //textACE.Content = ((int)e.NewValue).ToString();
        }

        private void sliderSSO_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
          //  textSSO.Content = ((int)e.NewValue).ToString();
        }


        public WindowInfoIni winInfoIni = new WindowInfoIni("ThermalCameraWindowInfo");//윈도우정보

        public UDPSocketForRelayServerComm udpSock = new UDPSocketForRelayServerComm(30007);

        private int m_nCh = -1;
        private string m_color = "";
        private double zoom = 1;
        private string Scontrast = "";
        private string Sbright = "";
        private string Sdde = "";
        private string Sace = "";
        private string Ssso = "";



        private void MaximizeButton_Click(object sender, RoutedEventArgs e)
        {
            Maximize();

        

            //SetCameraInfo();

            //await BaseRefreshAsync();
        }
        
        private void Maximize()
        {
            MaximizeButton.Visibility = Visibility.Hidden;

            WindowStyle = WindowStyle.SingleBorderWindow;


            Height = winInfoIni.maximizeHeight;
            Width = winInfoIni.maximizeWidth;

            Top = System.Windows.SystemParameters.PrimaryScreenHeight / 2 - Height / 2;
            Left = System.Windows.SystemParameters.PrimaryScreenWidth / 2 - Width / 2;

            m_nCh = 1;
            CreatePacketParsingThread(m_nCh);
            ch1Btn.IsChecked = true;

            /*
            ChannelGroup.Visibility = Visibility.Visible;
            panSpeedGroup.Visibility = Visibility.Visible;
            zoomSpeedGroup.Visibility = Visibility.Visible;
            focusSpeedGroup.Visibility = Visibility.Visible;
            cameraAngleGroup.Visibility = Visibility.Visible;
            focusAreaGroup.Visibility = Visibility.Visible;
            rangeSurveillanceGroup.Visibility = Visibility.Visible;           
            ch1Btn.IsChecked = true;
            */
            Topmost = true;

            WindowHideFromTaskListExt.HideFromTaskList(this);
        }
      
        private void Window_Closed(object sender, EventArgs e)
        {

        }
        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            //if (ALT_F4)
            //{

            //}
            //else
            //{
            e.Cancel = true;
            //축소
            Minimize();
        }


        private void Minimize()
        {
            WindowStyle = WindowStyle.None;
            //WindowStyle = WindowStyle.SingleBorderWindow;

            //MessageBox.Show(this.minimizePoint.Y.ToString() + this.minimizePoint.X, this.minimizeSize.Height.ToString() + this.minimizeSize.Width.ToString());
            Top = winInfoIni.minimizeY;
            Left = winInfoIni.minimizeX;
            Height = winInfoIni.minimizeHeight;// this.minimizeSize.Height;
            Width = winInfoIni.minimizeWidth; //this.minimizeSize.Width;

            MaximizeButton.Visibility = Visibility.Visible;
            /*
            ChannelGroup.Visibility = Visibility.Hidden;
            panSpeedGroup.Visibility = Visibility.Hidden;
            zoomSpeedGroup.Visibility = Visibility.Hidden;
            focusSpeedGroup.Visibility = Visibility.Hidden;
            cameraAngleGroup.Visibility = Visibility.Hidden;
            focusAreaGroup.Visibility = Visibility.Hidden;
            rangeSurveillanceGroup.Visibility = Visibility.Hidden;
            //StateChanged
            // Activate();
            
            //Topmost = false;

            

            
            var hWnd = new WindowInteropHelper(this).Handle;          

            Win32API.SetWindowPos(hWnd, HWND.TopMost, 0, 0, 0, 0,
                 SWP.NOMOVE);
            */
            Topmost = true;

            WindowHideFromTaskListExt.HideFromTaskList(this);
        }


        private void ch1Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 1;
            SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_DZOOM_REQ);

        }

        private void ch2Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 2;
            SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_DZOOM_REQ);

        }

        private void ch3Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 3;
            SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_DZOOM_REQ);

        }

        private void ch4Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 4;
            SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_DZOOM_REQ);

        }

        private void ch5Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 5;
            SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_DZOOM_REQ);

        }

        //제어권 커맨드 전송 함수
        private bool SendAuthorityCmd(int nCh, byte byCmdGroup, byte byCmdType, string authData = "")
        {
            AUTHORITY_PACKET authorityPacket = AuthorityCommUtil.MakeAuthorityPacket("Preset",
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
                return false;
            }
            return true;
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



                        AUTHORITY_PACKET AuthPacket;//제어권 패킷을 저장 할 변수
                        //AuthPacket.GetType()
                        //typeof(AUTHORITY_PACKET)
                        AuthPacket = (AUTHORITY_PACKET)AuthorityCommUtil.ByteToStructure(packet, typeof(AUTHORITY_PACKET));//바이트로 들어온걸 구조체로 변환


                        string name = AuthorityCommUtil.ByteToString(AuthPacket.srcName.name);
                        string data = AuthorityCommUtil.ByteToString(AuthPacket.authorityData.data);
                        //System.Console.WriteLine(data.Replace('\0', ' '));
                        //System.Console.WriteLine(name.Replace('\0', ' '));

                       
                        if (AuthPacket.byCmdGroup == CommandThermCam.CMDGROUP_THERMCAM)
                        {
                            if (AuthPacket.byCmdType == CommandThermCam.CMDTYPE_THERMCAM_AGCMODE_RESP)
                            {
                                this.Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
                                {
                                    //if (data == "1") ManualBtn.IsChecked = true;
                                    //if (data == "2") AutoBtn.IsChecked = true;
                                }));
                            }

                            if (AuthPacket.byCmdType == CommandThermCam.CMDTYPE_THERMCAM_CONTRAST_RESP)
                            {
                                this.Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
                                {
                                    //Scontrast = data;
                                    //textContrast.Content = data;
                                    //sliderContrast.Value = Int32.Parse(data);
                                }));
                            }
                                

                            if (AuthPacket.byCmdType == CommandThermCam.CMDTYPE_THERMCAM_BRIGHTNESS_RESP)
                            {
                                this.Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
                                {
                                    //Sbright = data;
                                    //textBrightness.Content = data;
                                    //sliderBrightness.Value = Int32.Parse(data);
                                }));
                            }

                            if (AuthPacket.byCmdType == CommandThermCam.CMDTYPE_THERMCAM_DDE_RESP)
                            {
                                this.Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
                                {
                                    //Sdde = data;
                                    //textDDE.Content = data;
                                    //sliderDDE.Value = Int32.Parse(data);
                                }));
                            }

                            if (AuthPacket.byCmdType == CommandThermCam.CMDTYPE_THERMCAM_ACE_RESP)
                            {
                                this.Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
                                {
                                    Sace = data;
                                    //textACE.Content = data;
                                   // sliderACE.Value = Int32.Parse(data);
                                }));
                            }

                            if (AuthPacket.byCmdType == CommandThermCam.CMDTYPE_THERMCAM_SSO_RESP)
                            {
                                this.Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
                                {
                                    Ssso = data;
                                   // textSSO.Content = data;
                                   // sliderSSO.Value = Int32.Parse(data);
                                }));
                            }

                            if (AuthPacket.byCmdType == CommandThermCam.CMDTYPE_THERMCAM_DZOOM_RESP)
                            {
                                this.Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
                                {
                                    zoom = double.Parse(data);
                                    textZoom.Content = data;
                                }));
                            }



                            else if (AuthPacket.byCmdType == CommandPTZReqResp.CMDTYPE_PTZREQ_MAINBOARD_STATUS_RESP)
                            {
                                System.Console.WriteLine(data);
                            }

                        }


                    }

                    Thread.Sleep(1);
                    //Console.WriteLine("GetNumberOfPacket Sleep {0}", nCh);
                }
            });
        }
        private void NUCButton_Click(object sender, RoutedEventArgs e)
        {
        
           
        }

        private void whButton_Click(object sender, RoutedEventArgs e)
        {
            //채널
            //명령어 그룹
            //명령어 종류          
            SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_WHITE_HOT);
           
        }

        private void bhButton_Click(object sender, RoutedEventArgs e)
        {
            SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_BLACK_HOT);
        }

        private void color_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            //m_color = color.SelectedIndex.ToString();
            //SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_COLOR,m_color);
        }

        private void plusButton_Click(object sender, RoutedEventArgs e)
        {
            if (zoom >= 4.0) MessageBox.Show("DigitalZoom의 최대 값은 4.0 입니다");
            else
            {
                zoom += 0.1;
                SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_DZOOM, zoom.ToString());
                textZoom.Content = zoom.ToString();
            }

        }

        private void minusButton_Click(object sender, RoutedEventArgs e)
        {
            if (zoom <= 1.0)  MessageBox.Show("DigitalZoom의 최소 값은 1.0 입니다"); 
            else
            {
                zoom -= 0.1;
                SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_DZOOM, zoom.ToString());
                textZoom.Content = zoom.ToString();
            } 
        }

        private void ManualBtn_Checked(object sender, RoutedEventArgs e)
        {
            SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_AGCMODE, "1");
        }

        private void AutoBtn_Checked(object sender, RoutedEventArgs e)
        {
            SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_AGCMODE, "2");
        }

        private void sliderContrast_DragCompleted(object sender, RoutedEventArgs e)
        {
         //   Scontrast = ((int)sliderContrast.Value).ToString();
            SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_CONTRAST, Scontrast);
        }

        private void sliderBrightness_DragCompleted(object sender, RoutedEventArgs e)
        {
          //  Sbright = ((int)sliderBrightness.Value).ToString();
            SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_BRIGHTNESS, Sbright);
        }

        private void sliderDDE_DragCompleted(object sender, RoutedEventArgs e)
        {
           // Sdde = ((int)sliderDDE.Value).ToString();
            SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_DDE, Sdde);
        }

        private void sliderACE_DragCompleted(object sender, RoutedEventArgs e)
        {
          //  Sace = ((int)sliderACE.Value).ToString();
            SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_ACE, Sace);
        }

        private void sliderSSO_DragCompleted(object sender, RoutedEventArgs e)
        {
          //  Ssso = ((int)sliderSSO.Value).ToString();
            SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_SSO, Ssso);
        }

        private void rainbowButton_Click(object sender, RoutedEventArgs e)
        {
            SendAuthorityCmd(m_nCh, CommandThermCam.CMDGROUP_THERMCAM, CommandThermCam.CMDTYPE_THERMCAM_COLOR, "2");
        }
    }
}
