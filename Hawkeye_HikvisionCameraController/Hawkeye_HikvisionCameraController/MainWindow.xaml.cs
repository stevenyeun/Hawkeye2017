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
using Ini;
using System.Threading.Tasks;
using System.Threading;
using System.Windows.Threading;
using System.Windows.Interop;
using System.Runtime.InteropServices;
using ReadWriteIni;
using System.IO;
using Ownskit.Applications.DrawAnywhere.Utils;
//https://www.codeproject.com/articles/1966/an-ini-file-handling-class-using-c
namespace HikvisionCameraController
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        //private IniFile ini = new IniFile(AppDomain.CurrentDomain.BaseDirectory + "HikvisionCameraInfo.ini");
        public WindowInfoIni winInfoIni = new WindowInfoIni("HikvisionCameraControllerWindowInfo");
        public SystemIpAddrInfo systemIpAddrInfo = new SystemIpAddrInfo("SystemIpAddrInfo");
     

        private HikvisionCameraControl hikvisionCameraControl;

        //private Point minimizePoint;
        //private Size minimizeSize;
        //private Size maximizeSize;

        private bool ALT_F4 = false;
        //private readonly int MAX_CHANNEL = 4;


        public MainWindow()
        {

            InitializeComponent();

            ShowInTaskbar = false;

            string name = this.GetType().Name;

            this.StateChanged += new EventHandler(MainWindow_StateChanged);
            //this.StateChanged += MainWindow_StateChanged;

            winInfoIni.ReadIni();
            systemIpAddrInfo.ReadIni(1);
            //ReadIni();

            ch1Btn.IsChecked = true;//라디오 버튼이 선택된거와같이 이벤트가 발생함 ch1Btn_Checked
            //ReadIniChannelInfo(1);

            Minimize();



        }

        private void MainWindow_StateChanged(object sender, EventArgs e)
        {
            //MessageBox.Show("1");
            //throw new NotImplementedException();
        }

        //http://shine10e.tistory.com/92
        private uint message;
        private IntPtr handle;
        [DllImport("user32.dll", CharSet = CharSet.Unicode)]
        public static extern uint RegisterWindowMessage(string lpString);
        protected override void OnSourceInitialized(EventArgs e)
        {
            base.OnSourceInitialized(e);

            handle = new WindowInteropHelper(this).Handle;
            message = RegisterWindowMessage("User Message");
            ComponentDispatcher.ThreadFilterMessage += new ThreadMessageEventHandler(ComponentDispatcher_ThreadFilterMessage);
        }
        void ComponentDispatcher_ThreadFilterMessage(ref MSG msg, ref bool handled)
        {
            //if (msg.message == message)
             //   MessageBox.Show("");//System.Console.WriteLine(msg.message.ToString() + " " + msg.wParam.ToString());
            if (msg.message == message && msg.wParam != handle)
            {
                //MessageBox.Show("MFC Message : " + msg.lParam.ToString());
                if (msg.lParam.ToString() == "1")
                {
                    ch1Btn.IsChecked = true;
                    ch2Btn.IsChecked = false;
                }
                else if (msg.lParam.ToString() == "2")
                {
                    ch1Btn.IsChecked = false;
                    ch2Btn.IsChecked = true;
                }


            }
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*
        private void ReadIniChannelInfo(int channel)
        {
            //for (int i = 0; i < MAX_CHANNEL; i++)
            //{
                string ch = string.Format("ch{0:d2}", channel);
                ipAddrFirst.Text = ini.IniReadValue(ch, "ipaddrFirst");
                ipAddrSecond.Text = ini.IniReadValue(ch, "ipaddrSencond");
                ipAddrThird.Text = ini.IniReadValue(ch, "ipaddrThird");
                ipAddrFourth.Text = ini.IniReadValue(ch, "ipaddrForth");

                id.Text = ini.IniReadValue(ch, "id");
                pw.Password = ini.IniReadValue(ch, "pw");
            //}
        }
        private void WriteIniChannelInfo(int channel)
        {
            string ch = string.Format("ch{0:d2}", channel);
            ini.IniWriteValue(ch, "ipaddrFirst", ipAddrFirst.Text);
            ini.IniWriteValue(ch, "ipaddrSencond", ipAddrSecond.Text);
            ini.IniWriteValue(ch, "ipaddrThird", ipAddrThird.Text);
            ini.IniWriteValue(ch, "ipaddrForth", ipAddrFourth.Text);

            ini.IniWriteValue(ch, "id", id.Text);
            ini.IniWriteValue(ch, "pw", pw.Password);
        }
        */
        /*
        private void ReadIni()
        {
            //MessageBox.Show(ini.path);

            
            ipAddrFirst.Text = ini.IniReadValue("connection", "ipaddrFirst");
            ipAddrSecond.Text = ini.IniReadValue("connection", "ipaddrSencond");
            ipAddrThird.Text = ini.IniReadValue("connection", "ipaddrThird");
            ipAddrFourth.Text = ini.IniReadValue("connection", "ipaddrForth");
            
            id.Text = ini.IniReadValue("connection", "id");
            pw.Password = ini.IniReadValue("connection", "pw");
            

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
            catch(Exception e)
            {

            }

        }
*/
        private void WriteIni()
        {
            /*
            ini.IniWriteValue("connection", "ipaddrFirst", ipAddrFirst.Text);
            ini.IniWriteValue("connection", "ipaddrSencond", ipAddrSecond.Text);
            ini.IniWriteValue("connection", "ipaddrThird", ipAddrThird.Text);
            ini.IniWriteValue("connection", "ipaddrForth", ipAddrFourth.Text);

            ini.IniWriteValue("connection", "id", id.Text);
            ini.IniWriteValue("connection", "pw", pw.Password);
            */

            /*
            ini.IniWriteValue("window", "minimizeX", minimizePoint.X.ToString());
            ini.IniWriteValue("window", "minimizeY", minimizePoint.Y.ToString());
            ini.IniWriteValue("window", "minimizeWidth", minimizeSize.Width.ToString());
            ini.IniWriteValue("window", "minimizeHeight", minimizeSize.Height.ToString());

            ini.IniWriteValue("window", "maximizeWidth", maximizeSize.Width.ToString());
            ini.IniWriteValue("window", "maximizeHeight", maximizeSize.Height.ToString());
            */
        }
        private void Maximize()
        {
            MaximizeButton.Visibility = Visibility.Hidden;

            WindowStyle = WindowStyle.ToolWindow;




            Height = winInfoIni.maximizeHeight;//maximizeSize.Height;
            Width = winInfoIni.maximizeWidth;//maximizeSize.Width;

            Top = System.Windows.SystemParameters.PrimaryScreenHeight / 2 - Height/2;
            Left = System.Windows.SystemParameters.PrimaryScreenWidth / 2 - Width/2;



            //ConnectionGroup.Visibility = Visibility.Visible;
            IrCutFilterGroup.Visibility = Visibility.Visible;
            EISGroup.Visibility = Visibility.Visible;
            //ConnectionGroup.Visibility = Visibility.Visible;
            DehazeGroup.Visibility = Visibility.Visible;
            BottomButtons.Visibility = Visibility.Visible;

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

            //ConnectionGroup.Visibility = Visibility.Hidden;
            IrCutFilterGroup.Visibility = Visibility.Hidden;
            EISGroup.Visibility = Visibility.Hidden;
            //ConnectionGroup.Visibility = Visibility.Hidden;
            DehazeGroup.Visibility = Visibility.Hidden;
            BottomButtons.Visibility = Visibility.Hidden;

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


    private async void refresh_Click(object sender, RoutedEventArgs e)
        {
            //string ip = ipAddrFirst.Text + "." + ipAddrSecond.Text + "." + ipAddrThird.Text + "." + ipAddrFourth.Text;
            //hikvisionCameraControl = new HikvisionCameraControl(ip, id.Text, pw.Password);

            //Refresh();

            
            await BaseRefreshAsync();
        }

        private void DehazeModeOpen_Click(object sender, RoutedEventArgs e)
        {        
            hikvisionCameraControl.SetDehaze("open", "7");
            Refresh();
        }

        private void DehazeModeAuto_Click(object sender, RoutedEventArgs e)
        {           
            hikvisionCameraControl.SetDehaze("auto", "7");
            Refresh();
        }

        private void DehazeModeClose_Click(object sender, RoutedEventArgs e)
        {  
            hikvisionCameraControl.SetDehaze("close", "7");
            Refresh();
        }

        private void IrCutFilterDay_Click(object sender, RoutedEventArgs e)
        {
            hikvisionCameraControl.SetIrCutFilter("day");
            Refresh();
        }

        private void IrCutFilterNight_Click(object sender, RoutedEventArgs e)
        {
            hikvisionCameraControl.SetIrCutFilter("night");
            Refresh();
        }

        private void EISOn_Click(object sender, RoutedEventArgs e)
        {
            hikvisionCameraControl.SetEIS("true");
            Refresh();
        }

        private void EISOff_Click(object sender, RoutedEventArgs e)
        {
            hikvisionCameraControl.SetEIS("false");
            Refresh();
        }

        private void save_Click(object sender, RoutedEventArgs e)
        {
            int ch = 0;

            if (ch1Btn.IsChecked == true)
                ch = 1;
            if (ch2Btn.IsChecked == true)
                ch = 2;

            if (ch == 0)
                MessageBox.Show("채널이 선택 되지않았습니다.");

            //WriteIniChannelInfo(ch);

            /*
            ipAddrFirst.IsEnabled = false;
            ipAddrSecond.IsEnabled = false;
            ipAddrThird.IsEnabled = false;
            ipAddrFourth.IsEnabled = false;
            id.IsEnabled = false;
            pw.IsEnabled = false;
            save.IsEnabled = false;
            */
            SetCameraInfo();
            /*
            string ip = ipAddrSecond.Text + "." + ipAddrSecond.Text + "." + ipAddrThird.Text + "." + ipAddrFourth.Text;
            hikvisionCameraControl = new HikvisionCameraControl(ip, id.Text, pw.Password);
        */
            }

        private void enable_Click(object sender, RoutedEventArgs e)
        {
            /*
            ipAddrFirst.IsEnabled = true;
            ipAddrSecond.IsEnabled = true;
            ipAddrThird.IsEnabled = true;
            ipAddrFourth.IsEnabled = true;
            id.IsEnabled = true;
            pw.IsEnabled = true;
            save.IsEnabled = true;
            */
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
            //}

           
        }

        //아이콘 모드에서 버튼을 클릭 할 경우
        private void MaximizeButton_Click(object sender, RoutedEventArgs e)
        {
            Maximize();
            
            //SetCameraInfo();

            //await BaseRefreshAsync();
        }
        private void Refresh()
        {

            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
            string IrcutFilterType;
            string nightToDayFilterLevel;
            string nightToDayFilterTime;
            bool bReturn1 = hikvisionCameraControl.GetIrCutFilter(out IrcutFilterType, out nightToDayFilterLevel, out nightToDayFilterTime);

            Dispatcher.Invoke(DispatcherPriority.Normal, new Action(delegate
            {
                if (bReturn1)
                {
                    if (IrcutFilterType == "day")
                        IrcutFilterType = "주간";
                    else if (IrcutFilterType == "night")
                        IrcutFilterType = "야간";
                    IrCutFilterType.Content = IrcutFilterType;
                }
                else
                    IrCutFilterType.Content = "연결안됨";
            }));
            ////////////////////////////////////////////////////////////////////////////////////////////////


            ////////////////////////////////////////////////////////////////////////////
            string enabledEIS;
            string EISLevel;
            bool bReturn2 = hikvisionCameraControl.GetEIS(out enabledEIS, out EISLevel);

            Dispatcher.Invoke(DispatcherPriority.Normal, new Action(delegate
            {
                if (bReturn2)
                {
                    if (enabledEIS == "true")
                        enabledEIS = "켜짐";
                    else if(enabledEIS == "false")
                        enabledEIS = "꺼짐";

                    EISEnabled.Content = enabledEIS;
                }
                else
                    EISEnabled.Content = "연결안됨";
            }));
            ////////////////////////////////////////////////////////////////////////////

            /*
            string enabledImhEnc;
            string ImageEnhancementLevel;
            ctl.GetImageEnhancement(out enabledImhEnc, out ImageEnhancementLevel);
            */

            //////////////////////////////////////////////////////////////////////////////
            string dehazeMode;
            string dehazeLevel;

            bool bReturn3 = hikvisionCameraControl.GetDehaze(out dehazeMode, out dehazeLevel);

            Dispatcher.Invoke(DispatcherPriority.Normal, new Action(delegate
            {
                if (bReturn3)
                {
                    if (dehazeMode == "open")
                        dehazeMode = "켜짐";
                    else if (dehazeMode == "close")
                        dehazeMode = "꺼짐";

                    DehazeMode.Content = dehazeMode;
                }
                else
                    DehazeMode.Content = "연결안됨";

        }));
            ///////////////////////////////////////////////////////////////////////////////

            Dispatcher.Invoke(DispatcherPriority.Normal, new Action(delegate
            {
                //refreshTime.Content = string.Format("{0:HH:mm:ss tt}", DateTime.Now);
                refreshTime.Content = string.Format("{0:yyyy/MM/dd HH:mm:ss}", DateTime.Now);
            }));

        }
        public Task RefreshAsync()//동기메서드를 비동기로 동작시키게 만드는 메서드
        {
            return Task.Run(() => Refresh());
        }
        public async Task BaseRefreshAsync()//RefreshAsync를 호출 하는 메서드
        {
            await RefreshAsync();
            //Console.WriteLine(result);           
        }
        ///////////////////////////////////////////////////////////////////////////////////////////
       
            //http://blog.naver.com/vactorman/220340600110
        public async Task<string> GetBaseUrlAsync(string url)
        {
            var result = await GetUrlAsync(url);
            Console.WriteLine(result);
            return result;
        }
        public string GetUrl(string url)
        {
            Thread.Sleep(500);
            return url;
        }
        public Task<string> GetUrlAsync(string url)
        {
            return Task.Run(() => GetUrl(url));
        }
        //
       


        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            if (Keyboard.Modifiers == ModifierKeys.Alt && e.SystemKey == Key.F4)
            {             
                //e.Handled = true;
                ALT_F4 = true;
            }
            /*
            var alt = e.KeyboardDevice.Modifiers.(ModifierKeys.Alt);

            bool f4 = e.Key.Equals(Key.F4);
            bool lAlt = e.SystemKey.Equals(Key.LeftAlt);
            Console.Out.WriteLine(lAlt + " " + f4);
            */
            //ALT_F4 =  && e.Key.Equals(Key.LeftAlt));
        }

        private void Window_Activated(object sender, EventArgs e)
        {
            System.Console.WriteLine("활성화");
            //System.Console.WriteLine(IsActive.ToString());
        }

        private void Window_Deactivated(object sender, EventArgs e)
        {
            System.Console.WriteLine("비활성화");

    
            //while (IsActive == false)
            //    Activate();
            //if(IsActive == false)
            //     Activate();
            // System.Console.WriteLine(IsActive.ToString());
        }

        private void SetCameraInfo()
        {
            //string ip = ipAddrFirst.Text + "." + ipAddrSecond.Text + "." + ipAddrThird.Text + "." + ipAddrFourth.Text;
            string ip = systemIpAddrInfo.dayCamCtlUriInfo.ipAddrFirst + "." + systemIpAddrInfo.dayCamCtlUriInfo.ipAddrSecond + "." + systemIpAddrInfo.dayCamCtlUriInfo.ipAddrThird + "." + systemIpAddrInfo.dayCamCtlUriInfo.ipAddrFourth;
            hikvisionCameraControl = new HikvisionCameraControl(ip, systemIpAddrInfo.dayCamCtlUriInfo.id, systemIpAddrInfo.dayCamCtlUriInfo.pw);
            //MessageBox.Show(ip);


        }
        private async void Ch1Btn_Checked(object sender, RoutedEventArgs e)
        {
            //ReadIniChannelInfo(1);
            systemIpAddrInfo.ReadIni(1);
            SetCameraInfo();

            await BaseRefreshAsync();
        }
        private async void Ch2Btn_Checked(object sender, RoutedEventArgs e)
        {
            //ReadIniChannelInfo(2);

            systemIpAddrInfo.ReadIni(2);
            SetCameraInfo();

            await BaseRefreshAsync();
        }

        private async void Ch3Btn_Checked(object sender, RoutedEventArgs e)
        {
            systemIpAddrInfo.ReadIni(3);
            SetCameraInfo();

            await BaseRefreshAsync();
        }

        private async void Ch4Btn_Checked(object sender, RoutedEventArgs e)
        {
            systemIpAddrInfo.ReadIni(4);
            SetCameraInfo();

            await BaseRefreshAsync();
        }

        private async void Ch5Btn_Checked(object sender, RoutedEventArgs e)
        {
            systemIpAddrInfo.ReadIni(5);
            SetCameraInfo();

            await BaseRefreshAsync();
        }
    }
}
