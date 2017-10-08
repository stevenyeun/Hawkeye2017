using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Ini;//https://www.codeproject.com/articles/1966/an-ini-file-handling-class-using-c
using System.Threading.Tasks;
using System.Threading;
using System.Windows.Threading;
using System.Windows.Interop;
using System.Runtime.InteropServices;
using ReadWriteIni;
using Ownskit.Applications.DrawAnywhere.Utils;

namespace Hawkeye_IPSetup
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        //private IniFile ini = new IniFile(AppDomain.CurrentDomain.BaseDirectory + "common.ini");//윈도우정보
        //private IniFile iniIPSetup = new IniFile(AppDomain.CurrentDomain.BaseDirectory + "IPSetup.ini");//IP 정보(전체시스템에서이용)
        //private Point minimizePoint;
        //private Size minimizeSize;
        //private Size maximizeSize;

        public WindowInfoIni winInfoIni = new WindowInfoIni("IPSetupWindowInfo");//윈도우정보
        public SystemIpAddrInfo systemIPAddrInfo = new SystemIpAddrInfo("SystemIpAddrInfo");//IP 정보(전체시스템에서이용)

        /*private void ReadIni()
        {
            //MessageBox.Show(ini.path);

  

            string minimizeX = ini.IniReadValue("window", "minimizeX");
            string minimizeY = ini.IniReadValue("window", "minimizeY");
            string minimizeWidth = ini.IniReadValue("window", "minimizeWidth");
            string minimizeHeight = ini.IniReadValue("window", "minimizeHeight");
            string maximizeWidth = ini.IniReadValue("window", "maximizeWidth");
            string maximizeHeight = ini.IniReadValue("window", "maximizeHeight");

            try
            {
                minimizePoint.X = double.Parse(minimizeX);
                minimizePoint.Y = double.Parse(minimizeY);
                minimizeSize.Width = double.Parse(minimizeWidth);
                minimizeSize.Height = double.Parse(minimizeHeight);
                maximizeSize.Width = double.Parse(maximizeWidth);
                maximizeSize.Height = double.Parse(maximizeHeight);
            }
            catch (Exception e)
            {

            }

        }*/
       

        private void Maximize()
        {
            MaximizeButton.Visibility = Visibility.Hidden;

            WindowStyle = WindowStyle.ToolWindow;


            Height = winInfoIni.maximizeHeight;
            Width = winInfoIni.maximizeWidth;

            Top = System.Windows.SystemParameters.PrimaryScreenHeight / 2 - Height / 2;
            Left = System.Windows.SystemParameters.PrimaryScreenWidth / 2 - Width / 2;


            ChannelGroup.Visibility = Visibility.Visible;
            PTZConnectionGroup.Visibility = Visibility.Visible;
            dayTimeGroup.Visibility = Visibility.Visible;
            thermalImageryGroup.Visibility = Visibility.Visible;
            iondayTimeConnectGroup.Visibility = Visibility.Visible;
            MicConnectionGroup.Visibility = Visibility.Visible;

            Topmost = true;
            ch1Btn.IsChecked=true;
            systemIPAddrInfo.ReadIni(1);
            PackText();

            WindowHideFromTaskListExt.HideFromTaskList(this);
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

            ChannelGroup.Visibility = Visibility.Hidden;
            PTZConnectionGroup.Visibility = Visibility.Hidden;
            dayTimeGroup.Visibility = Visibility.Hidden;
            thermalImageryGroup.Visibility = Visibility.Hidden;
            iondayTimeConnectGroup.Visibility = Visibility.Hidden;
            MicConnectionGroup.Visibility = Visibility.Hidden;
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
        public MainWindow()
        {
            InitializeComponent();

            winInfoIni.ReadIni();
            systemIPAddrInfo.ReadIni(1);
            //systemIPAddrInfo.ptzServerInfo.ipAddrFirst;
            //systemIPAddrInfo.ptzServerInfo.ipAddrSecond;
            //systemIPAddrInfo.ptzServerInfo.ipAddrSecond;
            //winInfoIni.WriteIni();

            winInfoIni.ReadIni();
            Minimize();
        }

        private void MaximizeButton_Click(object sender, RoutedEventArgs e)
        {
            Maximize();

            //SetCameraInfo();

            //await BaseRefreshAsync();
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

        private void PackText()
        {
            ipAddrFirst.Text = systemIPAddrInfo.ptzServerInfo.ipAddrFirst;
            ipAddrSecond.Text = systemIPAddrInfo.ptzServerInfo.ipAddrSecond;
            ipAddrThird.Text = systemIPAddrInfo.ptzServerInfo.ipAddrThird;
            ipAddrFourth.Text = systemIPAddrInfo.ptzServerInfo.ipAddrFourth;
            port.Text = systemIPAddrInfo.ptzServerInfo.port;

            dayTimeURI.Text = systemIPAddrInfo.mainVideoUriInfo.uri;

            thermalImageryURI.Text = systemIPAddrInfo.subVideoUriInfo.uri;

            dayTimeipAddrFirst.Text = systemIPAddrInfo.dayCamCtlUriInfo.ipAddrFirst;
            dayTimeipAddrSecond.Text = systemIPAddrInfo.dayCamCtlUriInfo.ipAddrSecond;
            dayTimeipAddrThird.Text = systemIPAddrInfo.dayCamCtlUriInfo.ipAddrThird;
            dayTimeipAddrFourth.Text = systemIPAddrInfo.dayCamCtlUriInfo.ipAddrFourth;
            idDay.Text = systemIPAddrInfo.dayCamCtlUriInfo.id;
            pwDay.Password = systemIPAddrInfo.dayCamCtlUriInfo.pw;

            MicipAddrFirst.Text = systemIPAddrInfo.micCtlUriInfo.ipAddrFirst;
            MicipAddrSecond.Text = systemIPAddrInfo.micCtlUriInfo.ipAddrSecond;
            MicipAddrThird.Text = systemIPAddrInfo.micCtlUriInfo.ipAddrThird;
            MicipAddrFourth.Text = systemIPAddrInfo.micCtlUriInfo.ipAddrFourth;
            idMic.Text = systemIPAddrInfo.micCtlUriInfo.id;
            pwMic.Password = systemIPAddrInfo.micCtlUriInfo.pw;
        }

        private void ch1Btn_Checked(object sender, RoutedEventArgs e)
        {
            systemIPAddrInfo.ReadIni(1);
            PackText();
        }

        private void ch2Btn_Checked(object sender, RoutedEventArgs e)
        {
            systemIPAddrInfo.ReadIni(2);
            PackText();
        }

        private void ch3Btn_Checked(object sender, RoutedEventArgs e)
        {
            systemIPAddrInfo.ReadIni(3);
            PackText();
        }

        private void ch4Btn_Checked(object sender, RoutedEventArgs e)
        {
            systemIPAddrInfo.ReadIni(4);
            PackText();
        }

        private void ch5Btn_Checked(object sender, RoutedEventArgs e)
        {
            systemIPAddrInfo.ReadIni(5);
            PackText();
        }

        private void enable_Click(object sender, RoutedEventArgs e)
        {
            ipAddrFirst.IsEnabled = true;
            ipAddrSecond.IsEnabled = true;
            ipAddrThird.IsEnabled = true;
            ipAddrFourth.IsEnabled = true;
            port.IsEnabled = true;
            dayTimeURI.IsEnabled = true;
            thermalImageryURI.IsEnabled = true;
            dayTimeipAddrFirst.IsEnabled = true;
            dayTimeipAddrSecond.IsEnabled = true;
            dayTimeipAddrThird.IsEnabled = true;
            dayTimeipAddrFourth.IsEnabled = true;
            idDay.IsEnabled = true;
            pwDay.IsEnabled = true;
            MicipAddrFirst.IsEnabled = true;
            MicipAddrSecond.IsEnabled = true;
            MicipAddrThird.IsEnabled = true;
            MicipAddrFourth.IsEnabled = true;
            idMic.IsEnabled = true;
            pwMic.IsEnabled = true;
            save.IsEnabled = true;
            enable.IsEnabled = false;
        }
        private void save_Click(object sender, RoutedEventArgs e)
        {
            int ch = 0;

            if (ch1Btn.IsChecked == true)
                ch = 1;
            if (ch2Btn.IsChecked == true)
                ch = 2;
            if(ch3Btn.IsChecked == true)
                ch = 3;
            if(ch4Btn.IsChecked == true)
                ch = 4;
            if(ch5Btn.IsChecked == true)
                ch = 5;

            if (ch == 0)
                MessageBox.Show("채널이 선택 되지않았습니다.");

            systemIPAddrInfo.ptzServerInfo.ipAddrFirst = ipAddrFirst.Text;
            systemIPAddrInfo.ptzServerInfo.ipAddrSecond = ipAddrSecond.Text;
            systemIPAddrInfo.ptzServerInfo.ipAddrThird = ipAddrThird.Text;
            systemIPAddrInfo.ptzServerInfo.ipAddrFourth = ipAddrFourth.Text;
            systemIPAddrInfo.ptzServerInfo.port = port.Text;

            systemIPAddrInfo.mainVideoUriInfo.uri = dayTimeURI.Text;

            systemIPAddrInfo.subVideoUriInfo.uri = thermalImageryURI.Text;

            systemIPAddrInfo.dayCamCtlUriInfo.ipAddrFirst = dayTimeipAddrFirst.Text;
            systemIPAddrInfo.dayCamCtlUriInfo.ipAddrSecond = dayTimeipAddrSecond.Text;
            systemIPAddrInfo.dayCamCtlUriInfo.ipAddrThird = dayTimeipAddrThird.Text;
            systemIPAddrInfo.dayCamCtlUriInfo.ipAddrFourth = dayTimeipAddrFourth.Text;
            systemIPAddrInfo.dayCamCtlUriInfo.id = idDay.Text;
            systemIPAddrInfo.dayCamCtlUriInfo.pw = pwDay.Password;

            systemIPAddrInfo.micCtlUriInfo.ipAddrFirst = MicipAddrFirst.Text;
            systemIPAddrInfo.micCtlUriInfo.ipAddrSecond = MicipAddrSecond.Text;
            systemIPAddrInfo.micCtlUriInfo.ipAddrThird = MicipAddrThird.Text;
            systemIPAddrInfo.micCtlUriInfo.ipAddrFourth = MicipAddrFourth.Text;
            systemIPAddrInfo.micCtlUriInfo.id = idMic.Text;
            systemIPAddrInfo.micCtlUriInfo.pw = pwMic.Password;

            systemIPAddrInfo.WriteIni(ch);

            ipAddrFirst.IsEnabled = false;
            ipAddrSecond.IsEnabled = false;
            ipAddrThird.IsEnabled = false;
            ipAddrFourth.IsEnabled = false;
            port.IsEnabled = false;
            dayTimeURI.IsEnabled = false;
            thermalImageryURI.IsEnabled = false;
            dayTimeipAddrFirst.IsEnabled = false;
            dayTimeipAddrSecond.IsEnabled = false;
            dayTimeipAddrThird.IsEnabled = false;
            dayTimeipAddrFourth.IsEnabled = false;
            idDay.IsEnabled = false;
            pwDay.IsEnabled = false;
            MicipAddrFirst.IsEnabled = false;
            MicipAddrSecond.IsEnabled = false;
            MicipAddrThird.IsEnabled = false;
            MicipAddrFourth.IsEnabled = false;
            idMic.IsEnabled = false;
            pwMic.IsEnabled = false;
            save.IsEnabled = false;
            enable.IsEnabled = true;
        }

    }
}
