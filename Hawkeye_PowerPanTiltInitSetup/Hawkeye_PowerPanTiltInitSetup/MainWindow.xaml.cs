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

namespace Hawkeye_PowerPanTiltInitSetup
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        public UDPSocketForRelayServerComm udpSock = new UDPSocketForRelayServerComm(30003);
        public WindowInfoIni winInfoIni = new WindowInfoIni("PowerPanTiltSetupWindowInfo");
        private int m_nCh = 0;
        private bool[] m_bStartPanTiltInit = { false, false, false, false, false };
        
        public MainWindow()
        {
            InitializeComponent();


            udpSock.CreateUDPSocket();

            InitAppUI();

            Minimize();


        }
        private void InitAppUI()
        {
            ch1Btn.IsChecked = true;
        }

        private void MaximizeButton_Click(object sender, RoutedEventArgs e)
        {
            Maximize();
        }

        private void Maximize()
        {
            MaximizeButton.Visibility = Visibility.Hidden;

            WindowStyle = WindowStyle.ToolWindow;




            Height = winInfoIni.maximizeHeight;//maximizeSize.Height;
            Width = winInfoIni.maximizeWidth;//maximizeSize.Width;

            Top = System.Windows.SystemParameters.PrimaryScreenHeight / 2 - Height / 2;
            Left = System.Windows.SystemParameters.PrimaryScreenWidth / 2 - Width / 2;


            MaximizeButton.Visibility = Visibility.Hidden;

            ChannelGroup.Visibility = Visibility.Visible;
            InitSetupGroup.Visibility = Visibility.Visible;
            SystemPowerGroup.Visibility = Visibility.Visible;



            Topmost = true;

            WindowHideFromTaskListExt.HideFromTaskList(this);
        }
        private void Minimize()
        {
            WindowStyle = WindowStyle.None;
            //WindowStyle = WindowStyle.SingleBorderWindow;

            //MessageBox.Show(this.minimizePoint.Y.ToString() + this.minimizePoint.X, this.minimizeSize.Height.ToString() + this.minimizeSize.Width.ToString());
            Top = winInfoIni.minimizeY;//this.minimizePoint.Y;
            Left = winInfoIni.minimizeX;
            Height = winInfoIni.minimizeHeight;
            Width = winInfoIni.minimizeWidth;

            MaximizeButton.Visibility = Visibility.Visible;

            ChannelGroup.Visibility = Visibility.Hidden;
            InitSetupGroup.Visibility = Visibility.Hidden;
            SystemPowerGroup.Visibility = Visibility.Hidden;

            Topmost = true;


            WindowHideFromTaskListExt.HideFromTaskList(this);
        }
        private bool SendAuthorityCmd(int nCh, byte byCmdGroup, byte byCmdType, string authData = "")
        {
            AUTHORITY_PACKET authorityPacket = AuthorityCommUtil.MakeAuthorityPacket("PowerPanTiltSetup",
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

        private AUTHORITY_PACKET RecvAuthorityCmd()
        {
            const int nTimeout = 5;
            int nCount = 0;
            while (true)
            {
                //if (udpSock.queuePacketFromRelayServer.Count > 0)
                if (udpSock.GetNumberOfPacket() > 0)
                {
                    IPEndPoint ep = udpSock.queueIPEndPointFromRelayServer.Dequeue();

                    Console.WriteLine("Parse Packet");
                    byte[] packet = udpSock.PopPacket();
                    string str = Encoding.UTF8.GetString(packet);
                    Console.WriteLine("Port={0} Received={1}", ep.Port, str.Length);

                    AUTHORITY_PACKET AuthPacket;
                    //AuthPacket.GetType()
                    //typeof(AUTHORITY_PACKET)
                    AuthPacket = (AUTHORITY_PACKET)AuthorityCommUtil.ByteToStructure(packet, typeof(AUTHORITY_PACKET));

                    return AuthPacket;
                }

                Thread.Sleep(100);
                nCount++;
                if (nCount >= nTimeout)
                    return new AUTHORITY_PACKET();
            }
        }
        private string GetPanMotorStatus()
        {
            #region
            string strStatus = "";
            while (true)//다른 메세지도 같이 오기 때문에 계속 읽어오면서 필터링
            {
                AUTHORITY_PACKET AuthPacket = RecvAuthorityCmd();

                if (AuthPacket.bySTX == 0 || AuthPacket.byETX == 0)
                    break;
                if (AuthPacket.byCmdGroup == CommandPTZReqResp.CMDGROUP_PTZREQ)
                {
                    if (AuthPacket.byCmdType == CommandPTZReqResp.CMDTYPE_PTZREQ_PAN_INITSTATUS_RESP)
                    {
                        string receivedName = AuthorityCommUtil.ByteToString(AuthPacket.srcName.name);
                        string receiveddata = AuthorityCommUtil.ByteToString(AuthPacket.authorityData.data);

                        strStatus = receiveddata;
                        break;
                    }
                }
            }
            return strStatus;
            #endregion
        }
        private void UpdatePanMotorStatusUI(int nCh, string strStatus, bool showMessagebox = false)
        {
            if (m_nCh != nCh)
                return;

            string strCh = String.Format("채널 {0} 초기화 상태", nCh);

            string updateStatus = "";
            if (strStatus != "")
            {
                if (strStatus == "1")
                    updateStatus = strCh + "(완료)";
                else if (strStatus == "2")
                    updateStatus = strCh + "(미 완료)";
                else
                {
                    if (showMessagebox)
                        MessageBox.Show(strCh + " 인식 실패");
                }
                
            }
            else
            {              
                updateStatus = strCh+ "(수신 실패)";
              
                if(showMessagebox)
                    MessageBox.Show(strCh + " 수신 실패");
            }
            
      
            if (!this.InitStatus.Dispatcher.CheckAccess())
            {
                this.InitStatus.Dispatcher.Invoke(
                  System.Windows.Threading.DispatcherPriority.Normal,
                  new Action(
                    delegate ()
                    {
                        this.InitStatus.Content = updateStatus;
                    }
                ));
            }
            else
            {
                this.InitStatus.Content = updateStatus;
            }
        }
        private bool UpdateinitializingStatus(int nCh)
        {
            if (m_bStartPanTiltInit[m_nCh - 1] == true)
            {
                string status = String.Format("채널 {0} 초기화 진행 중", m_nCh);
                this.InitStatus.Content = status;
                return true;
            }
            return false;
        }

        private string GetSysPowerStatus()
        {
            #region
            string strStatus = "";
            while (true)//다른 메세지도 같이 오기 때문에 계속 읽어오면서 필터링
            {
                AUTHORITY_PACKET AuthPacket = RecvAuthorityCmd();

                if (AuthPacket.bySTX == 0 || AuthPacket.byETX == 0)
                    break;
                if (AuthPacket.byCmdGroup == CommandPowerMgt.CMDGROUP_POWERMGT)
                {
                    if (AuthPacket.byCmdType == CommandPowerMgt.CMDTYPE_POWERMGT_SYS_PWR_STATUS)
                    {
                        string receivedName = AuthorityCommUtil.ByteToString(AuthPacket.srcName.name);
                        string receiveddata = AuthorityCommUtil.ByteToString(AuthPacket.authorityData.data);

                        strStatus = receiveddata;
                        break;
                    }
                }
            }
            return strStatus;
            #endregion
        }
        private void UpdateSysPowerStatusUI(int nCh, string strStatus, bool showMessagebox = false)
        {            
            if (strStatus != "")
            {
                //화면에 업데이트

                if (strStatus == "1")
                    this.SystemPowerStatus.Content = "전원 상태(On)";
                else if (strStatus == "2")
                    this.SystemPowerStatus.Content = "전원 상태(Off)";
                else
                {
                    if (showMessagebox)
                        MessageBox.Show("전원 상태 인식 실패");
                }
            }
            else
            {
                this.SystemPowerStatus.Content = "전원 상태()";
                if (showMessagebox)
                    MessageBox.Show("시스템 전원 상태 수신 실패");
                return;
            }
        }

        private string GetThermCamPowerStatus()
        {
            #region
            string strStatus = "";
            while (true)//다른 메세지도 같이 오기 때문에 계속 읽어오면서 필터링
            {
                AUTHORITY_PACKET AuthPacket = RecvAuthorityCmd();

                if (AuthPacket.bySTX == 0 || AuthPacket.byETX == 0)
                    break;
                if (AuthPacket.byCmdGroup == CommandPowerMgt.CMDGROUP_POWERMGT)
                {
                    if (AuthPacket.byCmdType == CommandPowerMgt.CMDTYPE_POWERMGT_THERMCAM_PWR_STATUS)
                    {
                        string receivedName = AuthorityCommUtil.ByteToString(AuthPacket.srcName.name);
                        string receiveddata = AuthorityCommUtil.ByteToString(AuthPacket.authorityData.data);

                        strStatus = receiveddata;
                        break;
                    }
                }
            }
            return strStatus;
            #endregion
        }
        private void UpdateThermcamPowerStatusUI(int nCh, string strStatus, bool showMessagebox = false)
        {
            if (strStatus != "")
            {
                //화면에 업데이트

                if (strStatus == "1")
                    this.ThermCamPowerStatus.Content = "전원 상태(On)";
                else if (strStatus == "2")
                    this.ThermCamPowerStatus.Content = "전원 상태(Off)";
                else
                {
                    if (showMessagebox)
                        MessageBox.Show("열상 전원 상태 인식 실패");
                }
            }
            else
            {
                this.ThermCamPowerStatus.Content = "전원 상태()";
                if (showMessagebox)
                    MessageBox.Show("열상 전원 상태 수신 실패");
                return;
            }
        }

        private void GetSendRecvAllStatus(bool showMessagebox = false)
        {
            SendAuthorityCmd(m_nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PAN_MOTORSTATUS_REQ);
            string strStatus1 = GetPanMotorStatus();
            UpdatePanMotorStatusUI(m_nCh, strStatus1, showMessagebox);

            SendAuthorityCmd(m_nCh, CommandPowerMgt.CMDGROUP_POWERMGT, CommandPowerMgt.CMDTYPE_POWERMGT_SYS_PWR_STATUS);
            string strStatus2 = GetSysPowerStatus();
            UpdateSysPowerStatusUI(m_nCh, strStatus2, showMessagebox);

            SendAuthorityCmd(m_nCh, CommandPowerMgt.CMDGROUP_POWERMGT, CommandPowerMgt.CMDTYPE_POWERMGT_THERMCAM_PWR_STATUS);
            string strStatus3 = GetThermCamPowerStatus();
            UpdateThermcamPowerStatusUI(m_nCh, strStatus3, showMessagebox);
        }
        private void InitStatus_Click(object sender, RoutedEventArgs e)
        {
            SendAuthorityCmd(m_nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PAN_MOTORSTATUS_REQ);

            string strStatus = GetPanMotorStatus();
            UpdatePanMotorStatusUI(m_nCh, strStatus);
        }
                
        private string GetPanTiltHomeStatus()
        {
            #region
            string strStatus = "";
            while (true)//다른 메세지도 같이 오기 때문에 계속 읽어오면서 필터링
            {
                AUTHORITY_PACKET AuthPacket = RecvAuthorityCmd();

                if (AuthPacket.bySTX == 0 || AuthPacket.byETX == 0)
                    break;
                if (AuthPacket.byCmdGroup == CommandPanTiltInit.CMDGROUP_PANTILTINIT)
                {
                    if (AuthPacket.byCmdType == CommandPanTiltInit.CMDTYPE_PANTILTINIT_RESP_HOMEPOS)
                    {
                        string receivedName = AuthorityCommUtil.ByteToString(AuthPacket.srcName.name);
                        string receiveddata = AuthorityCommUtil.ByteToString(AuthPacket.authorityData.data);

                        strStatus = receiveddata;
                        break;
                    }
                }
            }
            return strStatus;
            #endregion
        }
        private void InitStart_Click(object sender, RoutedEventArgs e)
        {
            int nCh = m_nCh;

            if( UpdateinitializingStatus(nCh) == true)
            {
                MessageBox.Show("이미 팬틸트 초기화 진행 중입니다.");
                return;
            }           
            else
            {
                string status = String.Format("채널 {0} 초기화 진행 중", m_nCh);
                this.InitStatus.Content = status;
            }    
          
#if true
            Task.Run(() =>
            {
                const int nTimeOut = 10;
                int nCount = 0;
                this.m_bStartPanTiltInit[nCh - 1] = true;

                while (true)
                {
                    SendAuthorityCmd(nCh, CommandPanTiltInit.CMDGROUP_PANTILTINIT, CommandPanTiltInit.CMDTYPE_PANTILTINIT_MOVE_HOMEPOS);

                    while (true)
                    {
                        SendAuthorityCmd(nCh, CommandPanTiltInit.CMDGROUP_PANTILTINIT, CommandPanTiltInit.CMDTYPE_PANTILTINIT_REQ_HOMEPOS);

                        string strStatus = GetPanTiltHomeStatus();

                        if (strStatus == "1")
                        {
                            nCount = 0;
                            System.Console.WriteLine("홈 이동중...");
                        }

                        else if (strStatus == "2")
                        {
                            nCount = 0;
                            System.Console.WriteLine("홈 이동 완료...");
                            break;
                        }
                        Thread.Sleep(1000);
                        nCount++;
                        if (nCount >= nTimeOut)
                            break;
                    }

                    //
                    SendAuthorityCmd(nCh, CommandPanTiltInit.CMDGROUP_PANTILTINIT, CommandPanTiltInit.CMDTYPE_PANTILTINIT_SYNC_HOMEPOS);
                    Thread.Sleep(1000);
                    SendAuthorityCmd(nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PAN_MOTORSTATUS_REQ);
                    string strMotorStatus = GetPanMotorStatus();
                    UpdatePanMotorStatusUI(nCh, strMotorStatus, true);                   
                    break;                   
                }
                this.m_bStartPanTiltInit[m_nCh - 1] = false;
            });
#endif
        }




        private void SystemPowerOn_Click(object sender, RoutedEventArgs e)
        {
            //패킷 전송
            SendAuthorityCmd(m_nCh, CommandPowerMgt.CMDGROUP_POWERMGT, CommandPowerMgt.CMDTYPE_POWERMGT_SYS_PWR_CTL, "1");


            string strStatus = GetSysPowerStatus();
            UpdateSysPowerStatusUI(m_nCh, strStatus);
        }

        private void SystemPowerOff_Click(object sender, RoutedEventArgs e)
        {
            SendAuthorityCmd(m_nCh, CommandPowerMgt.CMDGROUP_POWERMGT, CommandPowerMgt.CMDTYPE_POWERMGT_SYS_PWR_CTL, "2");


            string strStatus = GetSysPowerStatus();
            UpdateSysPowerStatusUI(m_nCh, strStatus);
        }

        private void SystemPowerStatus_Click(object sender, RoutedEventArgs e)
        {
           

            SendAuthorityCmd(m_nCh, CommandPowerMgt.CMDGROUP_POWERMGT, CommandPowerMgt.CMDTYPE_POWERMGT_SYS_PWR_STATUS);

            string strStatus = GetSysPowerStatus();
            UpdateSysPowerStatusUI(m_nCh, strStatus);
        }






        private void ThermCamPowerOn_Click(object sender, RoutedEventArgs e)
        {
            SendAuthorityCmd(m_nCh, CommandPowerMgt.CMDGROUP_POWERMGT, CommandPowerMgt.CMDTYPE_POWERMGT_THERMCAM_PWR_CTL, "1");

            string strStatus = GetThermCamPowerStatus();
            UpdateThermcamPowerStatusUI(m_nCh, strStatus);
        }
        private void ThermCamPowerOff_Click(object sender, RoutedEventArgs e)
        {
            SendAuthorityCmd(m_nCh, CommandPowerMgt.CMDGROUP_POWERMGT, CommandPowerMgt.CMDTYPE_POWERMGT_THERMCAM_PWR_CTL, "2");
            string strStatus = GetThermCamPowerStatus();
            UpdateThermcamPowerStatusUI(m_nCh, strStatus);
        }
        private void ThermCamPowerStatus_Click(object sender, RoutedEventArgs e)
        {
            SendAuthorityCmd(m_nCh, CommandPowerMgt.CMDGROUP_POWERMGT, CommandPowerMgt.CMDTYPE_POWERMGT_THERMCAM_PWR_STATUS);
            string strStatus = GetThermCamPowerStatus();
            UpdateThermcamPowerStatusUI(m_nCh, strStatus);
        }

        private void Ch1Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 1;

            //초기화 진행 중이 아닌 경우에 전체 상태 요청
            if (UpdateinitializingStatus(m_nCh) == false)//true : 초기화 진행중          
                GetSendRecvAllStatus(false);
        }

        private void Ch2Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 2;
            //초기화 진행 중이 아닌 경우에 전체 상태 요청
            if (UpdateinitializingStatus(m_nCh) == false)//true : 초기화 진행중          
                GetSendRecvAllStatus(false);
        }

        private void Ch3Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 3;
            //초기화 진행 중이 아닌 경우에 전체 상태 요청
            if (UpdateinitializingStatus(m_nCh) == false)//true : 초기화 진행중          
                GetSendRecvAllStatus(false);
        }

        private void Ch4Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 4;
            //초기화 진행 중이 아닌 경우에 전체 상태 요청
            if (UpdateinitializingStatus(m_nCh) == false)//true : 초기화 진행중          
                GetSendRecvAllStatus(false);
        }

        private void Ch5Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 5;
            //초기화 진행 중이 아닌 경우에 전체 상태 요청
            if (UpdateinitializingStatus(m_nCh) == false)//true : 초기화 진행중          
                GetSendRecvAllStatus(false);
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;

            Minimize();
        }
    }
}
