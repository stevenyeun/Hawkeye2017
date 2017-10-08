using AuthorityComm;
using Hawkeye_PTZController;
using Ownskit.Applications.DrawAnywhere.Utils;
using ReadWriteIni;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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

namespace Hawkeye_DayCamLensContlloer
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

            ch1Btn.IsChecked = true;
            m_nCh = 1;

        }
        public WindowInfoIni winInfoIni = new WindowInfoIni("DayCamLensControllerWindowInfo");//윈도우정보

        public UDPSocketForRelayServerComm udpSock = new UDPSocketForRelayServerComm(30009);

        private int m_nCh = -1;

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
            ChannelGroup.Visibility = Visibility.Hidden;
            ButtonGroup.Visibility = Visibility.Hidden;
            Topmost = true;

            WindowHideFromTaskListExt.HideFromTaskList(this);
        }

        private void Maximize()
        {
            MaximizeButton.Visibility = Visibility.Hidden;

            WindowStyle = WindowStyle.ToolWindow;


            Height = winInfoIni.maximizeHeight;
            Width = winInfoIni.maximizeWidth;

            Top = System.Windows.SystemParameters.PrimaryScreenHeight / 2 - Height / 2;
            Left = System.Windows.SystemParameters.PrimaryScreenWidth / 2 - Width / 2;

            ch1Btn.IsChecked = true;

            ChannelGroup.Visibility = Visibility.Visible;
            ButtonGroup.Visibility = Visibility.Visible;

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

        private void ch1Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 1;
        }

        private void ch2Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 2;
        }

        private void ch3Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 3;
        }

        private void ch4Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 4;
        }

        private void ch5Btn_Checked(object sender, RoutedEventArgs e)
        {
            m_nCh = 5;
        }

        private void MaximizeButton_Click(object sender, RoutedEventArgs e)
        {
            Maximize();
        }

        private void RButton_Click(object sender, RoutedEventArgs e)
        {
            SendAuthorityCmd(m_nCh, ETCDevice.CMDGROUP_ETC_DEVICE, ETCDevice.CMDTYPE_ETC_HIGHLENS_FILTER,"0");
        }

        private void OneButton_Click(object sender, RoutedEventArgs e)
        {
            SendAuthorityCmd(m_nCh, ETCDevice.CMDGROUP_ETC_DEVICE, ETCDevice.CMDTYPE_ETC_HIGHLENS_FILTER, "1");
        }

        private void TwoButton_Click(object sender, RoutedEventArgs e)
        {
            SendAuthorityCmd(m_nCh, ETCDevice.CMDGROUP_ETC_DEVICE, ETCDevice.CMDTYPE_ETC_HIGHLENS_FILTER, "2");
        }

        private void ThreeButton_Click(object sender, RoutedEventArgs e)
        {
            SendAuthorityCmd(m_nCh, ETCDevice.CMDGROUP_ETC_DEVICE, ETCDevice.CMDTYPE_ETC_HIGHLENS_FILTER, "3");
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

        private void IrisOpen_Click(object sender, RoutedEventArgs e)
        {
            SendAuthorityCmd(m_nCh, CommandDayCam.CMDGROUP_DAYCAM, CommandDayCam.CMDTYPE_DAYCAM_IRIS, "1");
        }

        private void IrisClose_Click(object sender, RoutedEventArgs e)
        {
            SendAuthorityCmd(m_nCh, CommandDayCam.CMDGROUP_DAYCAM, CommandDayCam.CMDTYPE_DAYCAM_IRIS, "2");
        }
    }
}
