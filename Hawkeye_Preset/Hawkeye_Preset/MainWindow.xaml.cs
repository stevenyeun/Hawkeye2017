using AuthorityComm;
using Hawkeye_PTZController;
using Microsoft.Win32;
using Ownskit.Applications.DrawAnywhere.Utils;
using ReadWriteIni;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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

namespace Hawkeye_Preset
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        public WindowInfoIni winInfoIni = new WindowInfoIni("PresetWindowInfo");
        private int m_nCh = 0;
        private int m_SelectedIndex = -1;
        private bool[] m_bPresetStart = { false, false, false, false, false };
        private bool[] m_bPresetThreadStop = { false, false, false, false, false };
        private int[] m_nArrPresetSpd = { 100, 100, 100, 100, 100 };

        private PresetReadWrite[] m_arrPresetListReadWrite = new PresetReadWrite[] {new PresetReadWrite() , new PresetReadWrite(), new PresetReadWrite(), new PresetReadWrite(), new PresetReadWrite() };

        PresetChannelInfoReadWrite m_presetChInfoIni = new PresetChannelInfoReadWrite("PresetChInfo");

        public UDPSocketForRelayServerComm udpSock = new UDPSocketForRelayServerComm(30002);

        public bool ALT_F4 { get; private set; }

        public MainWindow()
        {
            InitializeComponent();

            winInfoIni.ReadIni();

         

            for (int i=0; i<5; i++)
            {
                LoadPresetInfo(i + 1);
                //프리셋 속도 명령
                SendAuthorityCmd(i+1, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_PRESET_SPEED, "100");
            }

            InitAppUI();

            udpSock.CreateUDPSocket();

            Minimize();
        }
        private void InitAppUI()
        {

            ch1Btn.IsChecked = true;
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
            FileCtlBorder.Visibility = Visibility.Visible;
            PresetListBorder.Visibility = Visibility.Visible;
            PresetListCtlButtonsBorder.Visibility = Visibility.Visible;
            PresetMovingButtonsBorder.Visibility = Visibility.Visible;
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
            WindowStyle = WindowStyle.None;
            //WindowStyle = WindowStyle.SingleBorderWindow;

            //MessageBox.Show(this.minimizePoint.Y.ToString() + this.minimizePoint.X, this.minimizeSize.Height.ToString() + this.minimizeSize.Width.ToString());
            Top = winInfoIni.minimizeY;//this.minimizePoint.Y;
            Left = winInfoIni.minimizeX;
            Height = winInfoIni.minimizeHeight;
            Width = winInfoIni.minimizeWidth;

            MaximizeButton.Visibility = Visibility.Visible;

            ChannelGroup.Visibility = Visibility.Hidden;
            FileCtlBorder.Visibility = Visibility.Hidden;
            PresetListBorder.Visibility = Visibility.Hidden;
            PresetListCtlButtonsBorder.Visibility = Visibility.Hidden;
            PresetMovingButtonsBorder.Visibility = Visibility.Hidden;
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
           
            //WindowStyle = WindowStyle.ToolWindow;
            //WindowStyle = WindowStyle.None;
        }


        //private ObservableCollection<PresetListRow> presetList = new ObservableCollection<PresetListRow>();
   
        private void Window_Closed(object sender, EventArgs e)
        {

        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {

            e.Cancel = true;

            Minimize();

        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
           
        }

        private void Window_Activated(object sender, EventArgs e)
        {

        }

        private void Window_Deactivated(object sender, EventArgs e)
        {

        }

        private void MaximizeButton_Click(object sender, RoutedEventArgs e)
        {
            Maximize();
        }


        private void LoadChInfo(int nCh)//화면에 뿌릴 정보를 읽어와서 뿌림
        {
            m_SelectedIndex = -1;//선택된 리스트의 Row 번호를 초기화 시킴.

            int nIndex = nCh - 1;

            m_presetChInfoIni.ReadIni(nCh);//현재 채널의 프리셋 파일 경로를 불러온다. 

            if (m_presetChInfoIni.presetPathName != "")
            {
                //파일 이름만 추출
                int index1 = m_presetChInfoIni.presetPathName.LastIndexOf('\\');
                int index2 = m_presetChInfoIni.presetPathName.LastIndexOf('.');
                FileNameLabel.Content = m_presetChInfoIni.presetPathName.Substring(index1 + 1, (index2 - 1) - index1);//불러온 파일이름을 화면에 보여준다.

                PresetListView.ItemsSource = m_arrPresetListReadWrite[nIndex].GetPresetList();
            }
            else
            {
                PresetListView.ItemsSource = null;
                FileNameLabel.Content = "...";
            }
        }
        private void LoadPresetInfo(int nCh)
        {
            int nIndex = nCh - 1;
            m_presetChInfoIni.ReadIni(nCh);//현재 채널의 프리셋 파일 경로를 불러온다.   

            if (m_presetChInfoIni.presetPathName != "")
            {
                bool bRet = m_arrPresetListReadWrite[nIndex].LoadFIle(m_presetChInfoIni.presetPathName);//해당 파일을 불러온다.       
                if(bRet == false)//경로는 저장 되어있지만 실제 파일은 삭제됨
                {
                    m_presetChInfoIni.presetPathName = "";
                    m_presetChInfoIni.WriteIni(nCh);
                }
                //PresetListView.ItemsSource = presetListReadWrite[nIndex].GetPresetList(); //리스트를 초기화 한다.
            }
            else
            {
                //FileNameLabel.Content = "...";
            }

        }
        private void UpdateChInfo()
        {
            sliderPresetSpd.Value = m_nArrPresetSpd[m_nCh - 1];
            PresetSpdLabel.Content = m_nArrPresetSpd[m_nCh - 1].ToString();
        }
        private void Ch1Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 1;
            
            LoadChInfo(m_nCh);
            SetPresetStatus(m_nCh, "");

            UpdateChInfo();
        }

        private void Ch2Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 2;

            LoadChInfo(m_nCh);
            SetPresetStatus(m_nCh, "");

            UpdateChInfo();
        }

        private void Ch3Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 3;

            LoadChInfo(m_nCh);
            SetPresetStatus(m_nCh, "");

            UpdateChInfo();
        }

        private void Ch4Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 4;

            LoadChInfo(m_nCh);
            SetPresetStatus(m_nCh, "");

            UpdateChInfo();
        }

        private void Ch5Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 5;

            LoadChInfo(m_nCh);
            SetPresetStatus(m_nCh, "");

            UpdateChInfo();
        }

        private void PresetList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            /* 선택된 참조점명, 섹션 뽑기 */
            ListView lv = sender as ListView;
            int nIndex = lv.SelectedIndex;
            if (nIndex < 0)
                return;

            m_SelectedIndex = nIndex;

            int curChIndex = m_nCh - 1;
            PresetListRow row = m_arrPresetListReadWrite[curChIndex].GetRow(nIndex);

            //화면에 업데이트
            No.Content = row.No.ToString();
            Time.Text = row.Time.ToString();
            PanAbs.Text = row.PanAbs.ToString();
            TiltAbs.Text = row.TiltAbs.ToString();
            Zoom.Text = row.Zoom.ToString();
            Focus.Text = row.Focus.ToString();
        }
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


        private AUTHORITY_PACKET RecvAuthorityCmd(int nCh)//큐에 쌓인 것을 읽어온다.
        {
            const int nTimeout = 5;
            int nCount = 0;
            while (true)
            {
                //if (udpSock.queuePacketFromRelayServer.Count > 0)
                if (udpSock.GetNumberOfPacket(nCh) > 0)
                {

                    //IPEndPoint ep = udpSock.queueIPEndPointFromRelayServer.Dequeue();

                    Console.WriteLine("Parse Packet");
                    byte[] packet = udpSock.PopPacket(nCh);
                    string str = Encoding.UTF8.GetString(packet);
                    //Console.WriteLine("Port={0} Received={1}", ep.Port, str.Length);

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
        private void AddPresetRow_Click(object sender, RoutedEventArgs e)
        {
            int nIndex = m_nCh - 1;
            int nCh = m_nCh;
            //패킷 전송
            SendAuthorityCmd(m_nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_REQ);
         

            //패킷 수신 및 분석
            string strPanAbs = "";
            string strTiltAbs = "";
            string strZoom = "";
            string strFocus = "";

            while (true)//다른 메세지도 같이 오기 때문에 계속 읽어오면서 필터링
            {
                AUTHORITY_PACKET AuthPacket = RecvAuthorityCmd(nCh);

                if (AuthPacket.bySTX == 0 || AuthPacket.byETX == 0)
                    break;
                if (AuthPacket.byCmdGroup == CommandPTZReqResp.CMDGROUP_PTZREQ)
                {
                    if (AuthPacket.byCmdType == CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_RESP)
                    {
                        string receivedName = AuthorityCommUtil.ByteToString(AuthPacket.srcName.name);
                        string receiveddata = AuthorityCommUtil.ByteToString(AuthPacket.authorityData.data);

                        int index1 = receiveddata.IndexOf(';');
                        //index1 += 1;
                        strPanAbs = receiveddata.Substring(0, index1);
                        strTiltAbs = receiveddata.Substring(index1+1, receiveddata.Length - index1-1);
                        
                        SendAuthorityCmd(m_nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_DAYZF_POS_REQ);
                    }
                    if (AuthPacket.byCmdType == CommandPTZReqResp.CMDTYPE_PTZREQ_DAYZF_POS_RESP)
                    {
                        string receivedName = AuthorityCommUtil.ByteToString(AuthPacket.srcName.name);
                        string receiveddata = AuthorityCommUtil.ByteToString(AuthPacket.authorityData.data);

                        int index1 = receiveddata.IndexOf(';');
                        //index1 += 1;                       
                        strZoom = receiveddata.Substring(0, index1);
                        strFocus = receiveddata.Substring(index1 + 1, receiveddata.Length - index1 - 1);
                    }
                }
            }
            if (strPanAbs != "" && strTiltAbs != "" && strZoom != "" && strFocus != "")
            {
                //화면에 업데이트
                this.Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
                {
                    this.PanAbs.Text = strPanAbs;
                    this.TiltAbs.Text = strTiltAbs;
                    this.Zoom.Text = strZoom;
                    this.Focus.Text = strFocus;
                }));
            }
            else
            {
                MessageBox.Show("팬/틸트 줌/포커스 값 수신 실패");
                return;
            }
            
            /////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////
            //프리셋 리스트 저장

            int no = m_arrPresetListReadWrite[nIndex].GetNumberOfPreset();
            string name = Name.Text;
            int time = 0;
            double panAbs = 0;
            double tiltAbs = 0;
            int zoom = 0;
            int focus = 0;

            try
            {
                //수동 입력
                /* 
                time     = int.Parse(Time.Text);
                panAbs   = double.Parse(PanAbs.Text);
                tiltAbs  = double.Parse(TiltAbs.Text);
                zoom     = int.Parse(Zoom.Text);
                focus    = int.Parse(Focus.Text);
                */

                //리스트에 저장할 변수들
                time = int.Parse(Time.Text);//수동 입력
                panAbs = double.Parse(strPanAbs);
                tiltAbs = double.Parse(strTiltAbs);
                zoom = int.Parse(strZoom);
                focus = int.Parse(strFocus);
            }
            catch(Exception ee)
            {
                //MessageBox.Show(ee.ToString());
                MessageBox.Show("입력된 값이 잘못되었습니다.");
                return;
            }
            
            PresetListRow row = new PresetListRow(Name.Text, time, panAbs, tiltAbs, zoom, focus);

            bool ret = m_arrPresetListReadWrite[nIndex].AddPresetRow(row);
            if (ret == false)
            {
                MessageBox.Show("프리셋 그룹 파일이 없습니다.");//프리셋 추가 실패
                return;
            }


            PresetListView.ItemsSource = m_arrPresetListReadWrite[nIndex].GetPresetList();
        }

        private void NewGroupBtn_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.SaveFileDialog dlg = new Microsoft.Win32.SaveFileDialog();

            // Set filter for file extension and default file extension
            dlg.DefaultExt = ".txt";
            //dlg.Filter = "JPEG Files (*.jpeg)|*.jpeg|PNG Files (*.png)|*.png|JPG Files (*.jpg)|*.jpg|GIF Files (*.gif)|*.gif";
            dlg.Filter = "INI Files (*.ini)|*.ini";

            string ch = string.Format("ch{0:d2}", m_nCh);

            string initPath = AppDomain.CurrentDomain.BaseDirectory + ch;

            dlg.InitialDirectory = initPath;
       
            // Display OpenFileDialog by calling ShowDialog method
            Nullable<bool> result = dlg.ShowDialog();

            // Get the selected file name and display in a TextBox
            if (result == true)
            {
               
                string selectedFilePathName = dlg.FileName;

                //불러온경로를 저장
                
                m_presetChInfoIni.presetPathName = selectedFilePathName;
                m_presetChInfoIni.WriteIni(m_nCh);


                //파일 이름만 추출
                int index1 = dlg.FileName.LastIndexOf('\\');
                int index2 = dlg.FileName.LastIndexOf('.');
                FileNameLabel.Content = dlg.FileName.Substring(index1+1, (index2-1) - index1);//불러온 파일이름을 화면에 보여준다.

                
                //저장

                //이미 존재 하는 파일이면 삭제
                // Delete a file by using File class static method...
                if (System.IO.File.Exists(selectedFilePathName))
                {
                    // Use a try block to catch IOExceptions, to
                    // handle the case of the file already being
                    // opened by another process.
                    try
                    {
                        System.IO.File.Delete(selectedFilePathName);
                    }
                    catch (System.IO.IOException ee)
                    {
                        Console.WriteLine(ee.Message);
                        return;
                    }
                }
                /////////////////////////////////////////////////

                //파일 만듬
                int nIndex = m_nCh - 1;
                m_arrPresetListReadWrite[nIndex].CreateNewFile(dlg.FileName);
                
                //리스트를 초기화 한다.
                PresetListView.ItemsSource = m_arrPresetListReadWrite[nIndex].GetPresetList();

            }
        }

        private void LoadGroupBtn_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();

            // Set filter for file extension and default file extension
            dlg.DefaultExt = ".txt";
            //dlg.Filter = "JPEG Files (*.jpeg)|*.jpeg|PNG Files (*.png)|*.png|JPG Files (*.jpg)|*.jpg|GIF Files (*.gif)|*.gif";
            dlg.Filter = "INI Files (*.ini)|*.ini";

            string ch = string.Format("ch{0:d2}", m_nCh);

            string initPath = AppDomain.CurrentDomain.BaseDirectory + ch;

            dlg.InitialDirectory = initPath;

            // Display OpenFileDialog by calling ShowDialog method
            Nullable<bool> result = dlg.ShowDialog();

            // Get the selected file name and display in a TextBox
            if (result == true)
            {
                
                string selectedFilePathName = dlg.FileName;

                //불러온경로를 저장
                m_presetChInfoIni.presetPathName = selectedFilePathName;
                m_presetChInfoIni.WriteIni(m_nCh);

                //파일 이름만 추출
                int index1 = dlg.FileName.LastIndexOf('\\');
                int index2 = dlg.FileName.LastIndexOf('.');
                FileNameLabel.Content = dlg.FileName.Substring(index1 + 1, (index2 - 1) - index1);

                int nIndex = m_nCh - 1;
                //파일 불러오기
                m_arrPresetListReadWrite[nIndex].LoadFIle(dlg.FileName);


                //리스트를 초기화 한다.
                PresetListView.ItemsSource = m_arrPresetListReadWrite[nIndex].GetPresetList();

            }
        }

        private void EditPresetRow_Click(object sender, RoutedEventArgs e)
        {
            if(m_SelectedIndex < 0)
            {
                MessageBox.Show("선택된 항목이 없습니다.");
                return;
            }
            int nIndex = m_nCh-1;


            int no;        
            string name;   
            int time;      
            double panAbs; 
            double tiltAbs;
            int zoom;      
            int focus;     

            try
            {
                no = int.Parse(No.Content.ToString());
                name = Name.Text;
                time = int.Parse(Time.Text);
                panAbs = double.Parse(PanAbs.Text);
                tiltAbs = double.Parse(TiltAbs.Text);
                zoom = int.Parse(Zoom.Text);
                focus = int.Parse(Focus.Text);
            }
            catch(Exception ee)
            {
                MessageBox.Show("입력된 값이 잘못되었습니다.");
                return;
            }
         

             
            PresetListRow row = new PresetListRow(no, Name.Text, time, panAbs, tiltAbs, zoom, focus);
            
            m_arrPresetListReadWrite[nIndex].SetRow(m_SelectedIndex, row);
          
        }

        private void DeletePresetRow_Click(object sender, RoutedEventArgs e)
        {
            if (m_SelectedIndex < 0)
            {
                MessageBox.Show("선택된 항목이 없습니다.");
                return;
            }
            int nIndex = m_nCh - 1;

            m_arrPresetListReadWrite[nIndex].DeleteRow(m_SelectedIndex);

            PresetListView.ItemsSource = null;
            PresetListView.ItemsSource = m_arrPresetListReadWrite[nIndex].GetPresetList();
        }

        private void DeleteAllPresetRow_Click(object sender, RoutedEventArgs e)
        {
            int nIndex = m_nCh - 1;

            m_arrPresetListReadWrite[nIndex].DeleteAllRow();
        }

        private void SetPresetStatus(int nCh, string strStatus)
        {
            if (nCh != m_nCh)
                return;

            if (!this.PresetStatusLabel.Dispatcher.CheckAccess())
            {
                this.PresetStatusLabel.Dispatcher.Invoke(
                  System.Windows.Threading.DispatcherPriority.Normal,
                  new Action(
                    delegate ()
                    {
                        this.PresetStatusLabel.Content = strStatus;
                    }
                ));
            }
            else
            {
                this.PresetStatusLabel.Content = strStatus;
            }
        }
        private void SelectedRowMove_Click(object sender, RoutedEventArgs e)
        {
            //이동
            int nCh = m_nCh;

            if (m_bPresetStart[nCh-1] == true)
            {
                string temp = String.Format("채널 {0} 이미 프리셋 진행 중입니다.", m_nCh);
                MessageBox.Show(temp);
                return;
            }
          
            if (m_SelectedIndex < 0)
            {
                MessageBox.Show("선택된 항목이 없습니다.");
                return;
            }

            //선택된 프리셋 값 읽어오기
            int nIndex = m_nCh - 1;

            int no;
            string name;
            int time;
            double panAbs;
            double tiltAbs;
            int zoom;
            int focus;

            try
            {
                no = int.Parse(No.Content.ToString());
                name = Name.Text;
                time = int.Parse(Time.Text);
                panAbs = double.Parse(PanAbs.Text);
                tiltAbs = double.Parse(TiltAbs.Text);
                zoom = int.Parse(Zoom.Text);
                focus = int.Parse(Focus.Text);
            }
            catch (Exception ee)
            {
                MessageBox.Show("입력된 값이 잘못되었습니다.");
                return;
            }

            string status = String.Format("채널 {0} 프리셋 시작", m_nCh);
            this.PresetStatusLabel.Content = status;
            this.m_bPresetStart[nCh - 1] = true;

            //선택이동 스레드
            #region
            Task.Run(() =>
            {
                const int nTimeOut = 10;
                int nCount = 0;
                int nTimeStamp = 1;
                string strPresetStatus = "";

                while (true)
                {

                    string strPTZF = String.Format("001;{0:000.####};{1:+00.####;-00.####;+00.0000 };{2:00000};{3:00000}", panAbs, tiltAbs, zoom, focus);

                    SendAuthorityCmd(nCh, CommandPTZFAbsMove.CMDGROUP_PTZFABSMOVE, CommandPTZFAbsMove.CMDTYPE_PTZFABSMOVE_MOVE, strPTZF);


                   
                    while (true)
                    {
                        Thread.Sleep(1000);
                        SendAuthorityCmd(nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PAN_MOTORSTATUS_REQ);                        
                        string strStatus = GetPanMoveStatus(nCh);
                        
                        if (strStatus == "1")
                        {
                            nCount = 0;
                            //System.Console.WriteLine("프리셋 이동중...");
                            strPresetStatus = String.Format("채널 {0} 프리셋 이동중({1})", nCh, nTimeStamp);
                        }
                        else if (strStatus == "2")
                        {
                            nCount = 0;
                            //System.Console.WriteLine("프리셋 이동 완료...");
                            strPresetStatus = String.Format("채널 {0} 프리셋 이동 정지({1})", nCh, nTimeStamp);
                            break;
                        }
                        else
                        {
                            strPresetStatus = String.Format("채널 {0} 프리셋 상태 인식 실패({1})", nCh, nTimeStamp);
                        }

                        SetPresetStatus(nCh, strPresetStatus);

                        SendAuthorityCmd(nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_REQ);
                        //Thread.Sleep(1000);

                        nCount++;
                        nTimeStamp++;
                        if (nCount >= nTimeOut)
                            break;
                    }
                    //

                    //Thread.Sleep(1000);
                    //SendAuthorityCmd(nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PAN_MOTORSTATUS_REQ);
                    //string strMotorStatus = GetPanMotorStatus();
                    //UpdatePanMotorStatusUI(nCh, strMotorStatus, true);
                    break;
                }
                SendAuthorityCmd(nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_REQ);
                strPresetStatus = String.Format("채널 {0} 프리셋 이동 완료({1})", nCh, nTimeStamp);
                SetPresetStatus(nCh, strPresetStatus);
                this.m_bPresetStart[m_nCh - 1] = false;
            });
            #endregion
        }


        private string GetPanMoveStatus(int nCh)
        {
            #region
            string strStatus = "";
            while (true)//다른 메세지도 같이 오기 때문에 계속 읽어오면서 필터링
            {
                AUTHORITY_PACKET AuthPacket = RecvAuthorityCmd(nCh);

                if (AuthPacket.bySTX == 0 || AuthPacket.byETX == 0)
                    break;
                if (AuthPacket.byCmdGroup == CommandPTZReqResp.CMDGROUP_PTZREQ)
                {
                    if (AuthPacket.byCmdType == CommandPTZReqResp.CMDTYPE_PTZREQ_PAN_MOVESTATUS_RESP)
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
#if false
        private string GetPanMoveStatus()
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
                    if (AuthPacket.byCmdType == CommandPTZReqResp.CMDTYPE_PTZREQ_PAN_MOVESTATUS_RESP)
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
#endif


        private string GetSavePosStatus(int nCh)
        {
#region
            string strStatus = "";
            while (true)//다른 메세지도 같이 오기 때문에 계속 읽어오면서 필터링
            {
                AUTHORITY_PACKET AuthPacket = RecvAuthorityCmd(nCh);

                if (AuthPacket.bySTX == 0 || AuthPacket.byETX == 0)
                    break;
                if (AuthPacket.byCmdGroup == CommandPTZFAbsMove.CMDGROUP_PTZFABSMOVE)
                {
                    if (AuthPacket.byCmdType == CommandPTZFAbsMove.CMDTYPE_PTZFABSMOVE_RESP_SAVEPOS)
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

        private void AllRowMove_Click(object sender, RoutedEventArgs e)
        {
            //이동
            int nCh = m_nCh;

            if (m_bPresetStart[nCh - 1] == true)
            {
                string temp = String.Format("채널 {0} 이미 프리셋 진행 중입니다.", nCh);
                MessageBox.Show(temp);
                return;
            }

            int nNumOfPreset = m_arrPresetListReadWrite[nCh - 1].GetNumberOfPreset();
       

            if (nNumOfPreset < 0)
            {
                string temp = String.Format("채널 {0} 프리셋 리스트 항목이 없습니다.", nCh);
                MessageBox.Show(temp);
                return;
            }

            //프리셋 저장
            for(int i=0; i<nNumOfPreset; i++)
            {

                //int nIndex = m_nCh - 1;
                PresetListRow row = m_arrPresetListReadWrite[nCh - 1].GetRow(i);          

                string strPTZF = String.Format("{0:000};{1:000.####};{2:+00.####;-00.####;+00.0000 };{3:00000};{4:00000}", i+1, row.PanAbs, row.TiltAbs, row.Zoom, row.Focus);

                SendAuthorityCmd(nCh, CommandPTZFAbsMove.CMDGROUP_PTZFABSMOVE, CommandPTZFAbsMove.CMDTYPE_PTZFABSMOVE_SAVE_POS, strPTZF);
            }

            Thread.Sleep(500);
            //저장된 리스트 확인         
#if false//170423 저장된 리스트에 대한 응답이 비정상적으로옴 일단 주석처리하고 나중에 확인 해야 할 듯
            for (int i = 0; i < nNumOfPreset; i++)
            {
              
                //int nIndex = m_nCh - 1;
                PresetListRow row = m_arrPresetListReadWrite[nCh - 1].GetRow(i);

                string strNo = String.Format("{0:000};", i + 1);

                SendAuthorityCmd(nCh, CommandPTZFAbsMove.CMDGROUP_PTZFABSMOVE, CommandPTZFAbsMove.CMDTYPE_PTZFABSMOVE_REQ_SAVEPOS, strNo);
                string strRecvStatus = GetSavePosStatus(nCh);
                System.Console.WriteLine(strRecvStatus);

                //잘 저장 되었는지 검증
                if(strRecvStatus == "")
                {
                    string temp = String.Format("채널 {0} 팬틸트에 저장된 프리셋 항목({1})이 수신 실패.", nCh, i+1);
                    MessageBox.Show(temp);
                    return;
                }
                string[] arrRecvString = strRecvStatus.Split(';');
                string strRecvPan = arrRecvString[0].Substring(0, arrRecvString[0].Length - 1);
                string strRecvTilt = arrRecvString[1].Substring(0, arrRecvString[1].Length - 1);
                string strRecvZoom = arrRecvString[2];//.Substring(0, arrRecvString[2].Length - 1);
                string strRecvFocus = arrRecvString[3];//.Substring(0, arrRecvString[3].Length - 1);

                //string strPTZF = String.Format("{0:000.####};{1:+00.####;-00.####;+00.0000 };{2:00000};{3:00000}", row.PanAbs, row.TiltAbs, row.Zoom, row.Focus
                string strPan = String.Format("{0:000.####}", row.PanAbs);
                strPan = strPan.Substring(0, strPan.Length - 1);
                string strTilt = String.Format("{0:+00.####;-00.####;+00.0000}", row.TiltAbs);
                strTilt = strTilt.Substring(0, strTilt.Length - 1);

                string strZoom = String.Format("{0:00000}", row.Zoom);
                string strFocus = String.Format("{0:00000}", row.Focus);
                //MessageBox.Show("a" + strRecvFocus);
                //MessageBox.Show("b" + strFocus);

                if (strRecvPan == strPan &&
                    strRecvTilt == strTilt &&
                    strRecvZoom == strZoom &&
                    strRecvFocus == strFocus)
                {
                  
                }
                else
                {                  
                    string temp = String.Format("채널 {0} 팬틸트에 프리셋 항목({1})이 비정상 저장됨.", nCh, i + 1);                
                    MessageBox.Show(temp);
                    //temp = strRecvPan +" "+ strPan + " " + strRecvTilt + " " + strTilt + " " + strRecvZoom + " " + strZoom + " " + strRecvFocus + " " + strFocus;
                    //MessageBox.Show(temp);
                    return;
                }
            }
#endif
            string status = String.Format("채널 {0} 프리셋 시작", nCh);
            this.PresetStatusLabel.Content = status;
            this.m_bPresetStart[nCh - 1] = true;
            this.m_bPresetThreadStop[nCh - 1] = false;
#if true
            //선택이동 스레드
#region
            Task.Run(() =>
            {
                const int nTimeOut = 20;
                int nCount = 0;
                int nTimeStamp = 1;
                string strPresetStatus = "";

                bool bForward = true;
                int nPresetNo = 0;
                while (true)
                {
                    if (m_bPresetThreadStop[nCh - 1] == true)
                        break;

                    nTimeStamp = 1;

                    if (bForward == true)
                        nPresetNo++;
                    else
                        nPresetNo--;

                    if (nPresetNo == nNumOfPreset)
                        bForward = false;
                    else if (nPresetNo == 1)
                        bForward = true;

                    SendAuthorityCmd(nCh, CommandPTZFAbsMove.CMDGROUP_PTZFABSMOVE, CommandPTZFAbsMove.CMDTYPE_PTZFABSMOVE_MOVE_SAVEPOS, nPresetNo.ToString());
                    strPresetStatus = string.Format("채널 {0} 프리셋({1}) 이동시작({2})", nCh, nPresetNo, nTimeStamp);
                    SetPresetStatus(nCh, strPresetStatus);
                    Thread.Sleep(1000);

                    while (true)
                    {
                        if (m_bPresetThreadStop[nCh-1] == true)
                            break;
                                                
                        SendAuthorityCmd(nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PAN_MOTORSTATUS_REQ);
                        Thread.Sleep(1000);
                        string strStatus = GetPanMoveStatus(nCh);

                        if (strStatus == "1")
                        {
                            nCount = 0;
                            //System.Console.WriteLine("프리셋 이동중...");
                            strPresetStatus = string.Format("채널 {0} 프리셋({1}) 이동중({2})", nCh, nPresetNo, nTimeStamp);
                       
                        }
                        else if (strStatus == "2")
                        {
                            nCount = 0;
                            //System.Console.WriteLine("프리셋 이동 완료...");
                            strPresetStatus = string.Format("채널 {0} 프리셋({1}) 이동 정지({2})", nCh, nPresetNo, nTimeStamp);
                         
                            break;
                        }
                        else
                        {
                            strPresetStatus = string.Format("채널 {0} 프리셋({1}) 상태 인식 실패({2})", nCh, nPresetNo, nTimeStamp);
                           
                        }

                        SetPresetStatus(nCh, strPresetStatus);
                        Thread.Sleep(1);
                        SendAuthorityCmd(nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_REQ);
                        //Thread.Sleep(1000);
                        Thread.Sleep(500);

                        nCount++;
                        nTimeStamp++;
                        if (nCount >= nTimeOut)
                            break;
                    }
                    if (m_bPresetThreadStop[nCh - 1] == true)
                        break;

                    //대기 시간 
                    PresetListRow row = m_arrPresetListReadWrite[nCh-1].GetRow(nPresetNo-1);
                    strPresetStatus = string.Format("채널 {0} 프리셋({1}) 대기중({2}초)", nCh, nPresetNo, row.Time);
                    SetPresetStatus(nCh, strPresetStatus);

                    for (int i = 0; i < row.Time; i++)
                    {                        
                        Thread.Sleep(1000);
                        strPresetStatus = string.Format("채널 {0} 프리셋({1}) 대기중({2}초)", nCh, nPresetNo, row.Time-(i+1));
                        SetPresetStatus(nCh, strPresetStatus);
                        if (m_bPresetThreadStop[nCh-1] == true)
                            break;
                    }                         
                }
                SendAuthorityCmd(nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_REQ);
                strPresetStatus = String.Format("채널 {0} 프리셋 이동 종료({1})", nCh, nTimeStamp);
                SetPresetStatus(nCh, strPresetStatus);
                this.m_bPresetStart[nCh - 1] = false;
                this.m_bPresetThreadStop[nCh - 1] = false;

            });
#endregion

#endif
        }

        private void StopMove_Click(object sender, RoutedEventArgs e)
        {
            m_bPresetThreadStop[m_nCh - 1] = true;
        }

        private void sliderBrightness_DragCompleted(object sender, RoutedEventArgs e)
        {
            var slider = sender as Slider;
            double value = slider.Value;
            m_nArrPresetSpd[m_nCh - 1] = ((int)(value));
            
            //프리셋 속도 명령
            SendAuthorityCmd(m_nCh, CommandPTZ.CMDGROUP_PTZCTRL, CommandPTZ.CMDTYPE_PTZCTRL_PRESET_SPEED, ((int)(value)).ToString());
        }

        private void sliderPresetSpd_DragDelta(object sender, RoutedEventArgs e)
        {
            var slider = sender as Slider;
            // ... Get Value.
            double value = slider.Value;
            PresetSpdLabel.Content = ((int)(value)).ToString();
        }

        private void PresetUpBtn_Click(object sender, RoutedEventArgs e)
        {

        }

        private void PresetDownBtn_Click(object sender, RoutedEventArgs e)
        {

        }
    } 
}
