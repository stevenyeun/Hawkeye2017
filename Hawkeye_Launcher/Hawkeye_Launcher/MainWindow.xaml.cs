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
using System.Diagnostics;
using ReadWriteIni;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Interop;
using Hawkeye_LIB;
using System.Windows.Threading;
using System.IO;
using System.Net.Sockets;
using System.Net;

namespace Hawkeye_Launcher
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    /// 	
    public class Taskbar
    {
        [DllImport("user32.dll")]
        private static extern int FindWindow(string className, string windowText);
        [DllImport("user32.dll")]
        private static extern int ShowWindow(int hwnd, int command);

        private const int SW_HIDE = 0;
        private const int SW_SHOW = 1;

        protected static int Handle
        {
            get
            {
                return FindWindow("Shell_TrayWnd", "");
            }
        }

        private Taskbar()
        {
            // hide ctor
        }

        public static void Show()
        {
            ShowWindow(Handle, SW_SHOW);
        }

        public static void Hide()
        {
            ShowWindow(Handle, SW_HIDE);
        }
    }
  



    public partial class MainWindow : Window
    {
        public MainWindow()
        {  
            InitializeComponent();

            KillAllProcess();

            Maximize();
                     
            launcherSetup.ReadIni();

            Taskbar.Hide();
            
            Task.Run(() =>
            {
                UdpClient client = new UdpClient();

                client.ExclusiveAddressUse = false;
                IPEndPoint localEp = new IPEndPoint(IPAddress.Any, 2222);

                client.Client.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, true);
                client.ExclusiveAddressUse = false;

                client.Client.Bind(localEp);

                IPAddress multicastaddress = IPAddress.Parse("239.0.0.222");
                client.JoinMulticastGroup(multicastaddress);

                Console.WriteLine("Listening this will quit");

                while (true)
                {
                    byte[] data = client.Receive(ref localEp);
                    //string strData = Encoding.Unicode.GetString(data, 0, data.Length);
                    string strData = Encoding.Unicode.GetString(data).TrimEnd('\0');
                   
                    Console.WriteLine("received data : {0}", strData);
                    string text = "";
                    text = strData;
                    if (strData == "PTZClient_AuthorityServer Mainfunction is blocked")
                    {
                        //text = String.Format(strData+"({0})", ++Hawkeye_PTZClient_AuthorityServer_Message_Count);
                        m_bHawkeye_PTZClient_AuthorityServer_Booting = true;
                        continue;                       
                    }
                    if (strData == "RelayServer Mainfunction is blocked")
                    {
                        //text = String.Format(strData+"({0})", ++Hawkeye_PTZClient_AuthorityServer_Message_Count);
                        m_bHawkeye_RelayServer_Booting = true;
                        continue;
                    }
                    this.Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
                    {
                        logTextBox.Text = text;
                    }));
                    if (strData == "quit")
                        break;
                }

                Console.WriteLine("quit the program to ENTER");
                Console.ReadLine();
            });

        }
   
     

        public WindowInfoIni winInfoIni = new WindowInfoIni("LauncherWindowInfo");
        static public LauncherSetup launcherSetup = new LauncherSetup("LauncherSetupInfo");

        private void Maximize()
        {


            WindowStyle = WindowStyle.None;



            Height = winInfoIni.maximizeHeight;
            Width = winInfoIni.maximizeWidth;

            Top = System.Windows.SystemParameters.PrimaryScreenHeight / 2 - Height / 2;
            Left = System.Windows.SystemParameters.PrimaryScreenWidth / 2 - Width / 2;
            minBtn.Visibility = Visibility.Hidden;

            img.Visibility = Visibility.Visible;
            logTextBox.Visibility = Visibility.Visible;
            StartBtn.Visibility = Visibility.Visible;
            ExitBtn.Visibility = Visibility.Visible;
            imgBorder.Visibility = Visibility.Visible;


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

        }

        private void Minimize()
        {
            this.Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
            {
                //MessageBox.Show("aa");
                WindowStyle = WindowStyle.None;
                //WindowStyle = WindowStyle.SingleBorderWindow;

                //MessageBox.Show(this.minimizePoint.Y.ToString() + this.minimizePoint.X, this.minimizeSize.Height.ToString() + this.minimizeSize.Width.ToString());
                minBtn.Visibility = Visibility.Visible;
                img.Visibility = Visibility.Hidden;
                logTextBox.Visibility = Visibility.Hidden;
                StartBtn.Visibility = Visibility.Hidden;
                ExitBtn.Visibility = Visibility.Hidden;
                imgBorder.Visibility = Visibility.Hidden;

                Top = winInfoIni.minimizeY;
                Left = winInfoIni.minimizeX;
                Height = winInfoIni.minimizeHeight;// this.minimizeSize.Height;
                Width = winInfoIni.minimizeWidth; //this.minimizeSize.Width;


                Topmost = true;
            }));

            
        }



        static public bool IsRunProcess(string name)
        {


            for (int i = 0; i < 10; i++)
            {
                Process[] localByName = Process.GetProcessesByName(name);
                if (localByName.Count() > 0)
                    return true;
                Thread.Sleep(100);
            }
            return false;
        }

        static void LaunchCommandLineApp()
        {
            ProcessStartInfo start = new ProcessStartInfo();

            start.Arguments = "Hawkeye_PTZClient_AuthorityServer";
            start.FileName = ".\\Hawkeye_PTZClient_AuthorityServer\\Hawkeye_PTZClient_AuthorityServer.exe";
            try
            {
                Process.Start(start);
            }
            catch(Exception e)
            {

            }



            start.Arguments = "Hawkeye_RelayServer";
            start.FileName = ".\\Hawkeye_RelayServer\\Hawkeye_RelayServer.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }

            if(launcherSetup.showMap == true.ToString())
            {
                start.Arguments = "Hawkeye_GIS";
                start.FileName = ".\\Hawkeye_GIS\\Hawkeye_GIS.exe";
                try
                {
                    Process.Start(start);
                }
                catch (Exception e)
                {

                }
            }
            else
            {

            }

#if false
            start.Arguments = "Hawkeye_BIT";
            start.FileName = ".\\Hawkeye_BIT\\Hawkeye_BIT.exe";
            try
            {
                Process.Start(start);
            }
            catch(Exception e)
            {

            }
#endif
            start.Arguments = "Hawkeye_ThermalCamera";
            start.FileName = ".\\Hawkeye_ThermalCamera\\Hawkeye_ThermalCamera.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }



            start.Arguments = "Hawkeye_DayCamLensController";
            start.FileName = ".\\Hawkeye_DayCamLensController\\Hawkeye_DayCamLensController.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }





            start.Arguments = "Hawkeye_IPSetup";
            start.FileName = ".\\Hawkeye_IPSetup\\Hawkeye_IPSetup.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }

            start.Arguments = "Hawkeye_HikvisionCameraController";
            start.FileName = ".\\Hawkeye_HikvisionCameraController\\Hawkeye_HikvisionCameraController.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }

            start.Arguments = "Hawkeye_HanwhaCameraController";
            start.FileName = ".\\Hawkeye_HanwhaCameraController\\Hawkeye_HanwhaCameraController.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }

            start.Arguments = "Hawkeye_Panorama";
            start.FileName = ".\\Hawkeye_Panorama\\Hawkeye_Panorama.exe";
            try
            {
                Process.Start(start);

            }
            catch (Exception e)
            {

            }
            start.Arguments = "Hawkeye_PowerPanTiltInitSetup";
            start.FileName = ".\\Hawkeye_PowerPanTiltInitSetup\\Hawkeye_PowerPanTiltInitSetup.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }






            start.Arguments = "Hawkeye_PTZController";
            start.FileName = ".\\Hawkeye_PTZController\\Hawkeye_PTZController.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }

            start.Arguments = "Hawkeye_PTZEnvSetup";
            start.FileName = ".\\Hawkeye_PTZEnvSetup\\Hawkeye_PTZEnvSetup.exe";
            try
            {
                Process.Start(start);

            }
            catch (Exception e)
            {

            }




            start.Arguments = "Hawkeye_Preset";
                start.FileName = ".\\Hawkeye_Preset\\Hawkeye_Preset.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }

            start.Arguments = "Hawkeye_KeyboardHooker";
            start.FileName = ".\\Hawkeye_KeyboardHooker\\Hawkeye_KeyboardHooker.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }

            start.Arguments = "Hawkeye_AudioBroadcast";
            start.FileName = ".\\Hawkeye_AudioBroadcast\\Hawkeye_AudioBroadcast.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }

            start.Arguments = "Hawkeye_Recording";
            start.FileName = ".\\Hawkeye_Recording\\Hawkeye_Recording.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }

            //비디오 뷰어 띄우기
            try
            {
                int nMax = int.Parse(launcherSetup.numberOfVideo);
                for (int i = 0; i < nMax; i++)
                {
                    start.Arguments = (i + 1).ToString();
                    start.FileName = ".\\Hawkeye_VideoPlayer\\Hawkeye_VideoPlayer.exe";
                    try
                    {
                        Process.Start(start);
                    }
                    catch (Exception e)
                    {

                    }
                }
            }
            catch
            {

            }


#if false
            start.Arguments = "1";
            start.FileName = ".\\Hawkeye_VideoPlayer\\Hawkeye_VideoPlayer.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }
            start.Arguments = "2";
            start.FileName = ".\\Hawkeye_VideoPlayer\\Hawkeye_VideoPlayer.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }
            start.Arguments = "3";
            start.FileName = ".\\Hawkeye_VideoPlayer\\Hawkeye_VideoPlayer.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }
            start.Arguments = "4";
            start.FileName = ".\\Hawkeye_VideoPlayer\\Hawkeye_VideoPlayer.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }
            start.Arguments = "5";
            start.FileName = ".\\Hawkeye_VideoPlayer\\Hawkeye_VideoPlayer.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }
#endif
            Thread.Sleep(200);

            start.Arguments = "1";
            start.FileName = ".\\Hawkeye_AudioSender\\Hawkeye_AudioSender.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }

            Thread.Sleep(200);

            start.Arguments = "2";
            start.FileName = ".\\Hawkeye_AudioSender\\Hawkeye_AudioSender.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }

            start.Arguments = "3";
            start.FileName = ".\\Hawkeye_AudioSender\\Hawkeye_AudioSender.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }

            start.Arguments = "4";
            start.FileName = ".\\Hawkeye_AudioSender\\Hawkeye_AudioSender.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }

            start.Arguments = "5";
            start.FileName = ".\\Hawkeye_AudioSender\\Hawkeye_AudioSender.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception e)
            {

            }





        }
        private void Image_Loaded(object sender, RoutedEventArgs e)
        {
            // ... Create a new BitmapImage.
            BitmapImage b = new BitmapImage();
            b.BeginInit();


            try
            {
                b.UriSource = new Uri(AppDomain.CurrentDomain.BaseDirectory + "logo.jpg");
                b.EndInit();

                // ... Get Image reference from sender.
                var image = sender as Image;
                // ... Assign Source.
                image.Source = b;
            }
            catch
            {

            }
        }

      

        bool m_bClickStartBtn = false;
        private void StartBtn_Click(object sender, RoutedEventArgs e)
        {
            if (m_bClickStartBtn == true)
                return;
            m_bClickStartBtn = true;

            KillAllProcess();
            LaunchCommandLineApp();

            //프로그램 동작 감시
            Task.Run(() =>
            {
                while (true)
                {
                    if( m_bHawkeye_PTZClient_AuthorityServer_Booting == true && m_bHawkeye_RelayServer_Booting == true)
                    {
                        Minimize();
                        m_bClickStartBtn = false;
                        m_bHawkeye_PTZClient_AuthorityServer_Booting = false;
                        m_bHawkeye_RelayServer_Booting = false;
                        Hawkeye_PTZClient_AuthorityServer_Message_Count = 0;
                        Hawkeye_RelayServer_Message_Count = 0;
                        return;
                    }

                    this.Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
                    {
                        if (!this.IsVisible)
                        {
                            this.Show();
                        }

                        if (this.WindowState == WindowState.Minimized)
                        {
                            this.WindowState = WindowState.Normal;
                        }

                        this.Activate();
                        this.Topmost = false; // important
                        this.Topmost = true;  // important                        
                        this.Focus();         // important
                    }));
                    Thread.Sleep(500);
                }
            });
          
        }

        private void ExitBtn_Click(object sender, RoutedEventArgs e)
        {
            if (MessageBox.Show("런처를 종료하시겠습니까?", "호크아이 런처", MessageBoxButton.YesNo, MessageBoxImage.Warning) == MessageBoxResult.No)
            {
                //do no stuff
            }
            else
            {
                Taskbar.Show();
                this.Close();
            }

        }

        private void KillAllProcess()
        {
            Process[] processes = Process.GetProcessesByName("Hawkeye_KeyboardHooker");
            Process currentProcess = Process.GetCurrentProcess();
            foreach (Process proc in processes)
            {
                if (proc.Id != currentProcess.Id)
                    proc.Kill();
            }
#if false
            processes = Process.GetProcessesByName("Hawkeye_BIT");
            currentProcess = Process.GetCurrentProcess();
            foreach (Process proc in processes)
            {
                if (proc.Id != currentProcess.Id)
                    proc.Kill();
            }
#endif
            processes = Process.GetProcessesByName("Hawkeye_RelayServer");
            currentProcess = Process.GetCurrentProcess();
            foreach (Process proc in processes)
            {
                if (proc.Id != currentProcess.Id)
                    proc.Kill();
            }

            processes = Process.GetProcessesByName("Hawkeye_PTZClient_AuthorityServer");
            currentProcess = Process.GetCurrentProcess();
            foreach (Process proc in processes)
            {
                if (proc.Id != currentProcess.Id)
                    proc.Kill();
            }


            processes = Process.GetProcessesByName("Hawkeye_DayCamLensController");
            currentProcess = Process.GetCurrentProcess();
            foreach (Process proc in processes)
            {
                if (proc.Id != currentProcess.Id)
                    proc.Kill();
            }

            processes = Process.GetProcessesByName("Hawkeye_GIS");
            currentProcess = Process.GetCurrentProcess();
            foreach (Process proc in processes)
            {
                if (proc.Id != currentProcess.Id)
                    proc.Kill();
            }

            processes = Process.GetProcessesByName("Hawkeye_HikvisionCameraController");
            currentProcess = Process.GetCurrentProcess();
            foreach (Process proc in processes)
            {
                if (proc.Id != currentProcess.Id)
                    proc.Kill();
            }

            processes = Process.GetProcessesByName("Hawkeye_HanwhaCameraController");
            currentProcess = Process.GetCurrentProcess();
            foreach (Process proc in processes)
            {
                if (proc.Id != currentProcess.Id)
                    proc.Kill();
            }

            processes = Process.GetProcessesByName("Hawkeye_IPSetup");
            currentProcess = Process.GetCurrentProcess();
            foreach (Process proc in processes)
            {
                if (proc.Id != currentProcess.Id)
                    proc.Kill();
            }

            processes = Process.GetProcessesByName("Hawkeye_Panorama");
            currentProcess = Process.GetCurrentProcess();
            foreach (Process proc in processes)
            {
                if (proc.Id != currentProcess.Id)
                    proc.Kill();
            }

            processes = Process.GetProcessesByName("Hawkeye_PowerPanTiltInitSetup");
            currentProcess = Process.GetCurrentProcess();
            foreach (Process proc in processes)
            {
                if (proc.Id != currentProcess.Id)
                    proc.Kill();
            }

            processes = Process.GetProcessesByName("Hawkeye_Preset");
            currentProcess = Process.GetCurrentProcess();
            foreach (Process proc in processes)
            {
                if (proc.Id != currentProcess.Id)
                    proc.Kill();
            }



            processes = Process.GetProcessesByName("Hawkeye_PTZController");
            currentProcess = Process.GetCurrentProcess();
            foreach (Process proc in processes)
            {
                if (proc.Id != currentProcess.Id)
                    proc.Kill();
            }

            processes = Process.GetProcessesByName("Hawkeye_PTZEnvSetup");
            currentProcess = Process.GetCurrentProcess();
            foreach (Process proc in processes)
            {
                if (proc.Id != currentProcess.Id)
                    proc.Kill();
            }



            processes = Process.GetProcessesByName("Hawkeye_ThermalCamera");
            currentProcess = Process.GetCurrentProcess();
            foreach (Process proc in processes)
            {
                if (proc.Id != currentProcess.Id)
                    proc.Kill();
            }

            processes = Process.GetProcessesByName("Hawkeye_VideoPlayer");
            currentProcess = Process.GetCurrentProcess();
            foreach (Process proc in processes)
            {
                if (proc.Id != currentProcess.Id)
                    proc.Kill();
            }

            processes = Process.GetProcessesByName("Hawkeye_AudioSender");
            currentProcess = Process.GetCurrentProcess();
            foreach (Process proc in processes)
            {
                if (proc.Id != currentProcess.Id)
                    proc.Kill();
            }


            processes = Process.GetProcessesByName("Hawkeye_AudioBroadcast");
            currentProcess = Process.GetCurrentProcess();
            foreach (Process proc in processes)
            {
                if (proc.Id != currentProcess.Id)
                    proc.Kill();
            }

            processes = Process.GetProcessesByName("Hawkeye_Recording");
            currentProcess = Process.GetCurrentProcess();
            foreach (Process proc in processes)
            {
                if (proc.Id != currentProcess.Id)
                    proc.Kill();
            }

            processes = Process.GetProcessesByName("ffmpeg");
            currentProcess = Process.GetCurrentProcess();
            foreach (Process proc in processes)
            {
                if (proc.Id != currentProcess.Id)
                    proc.Kill();
            }
        }
        private void minBtn_Click(object sender, RoutedEventArgs e)
        {

            logTextBox.Text = "";
            m_bClickStartBtn = false;
            m_bHawkeye_PTZClient_AuthorityServer_Booting = false;
            m_bHawkeye_RelayServer_Booting = false;
            Hawkeye_PTZClient_AuthorityServer_Message_Count = 0;
            Hawkeye_RelayServer_Message_Count = 0;
            KillAllProcess();

            Maximize();


            
        }
        private void Window_Closed(object sender, EventArgs e)
        {
            
        }
        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
#if false
            if (MessageBox.Show("Close Application?", "Question", MessageBoxButton.YesNo, MessageBoxImage.Warning) == MessageBoxResult.No)
            {
                //do no stuff
            }
            else
            {
                Taskbar.Show();
                this.Close();
            }
#endif
        }


        private uint Hawkeye_PTZClient_AuthorityServer_Message;
        private uint Hawkeye_RelayServer_Message;
        private IntPtr handle;
        private bool m_bHawkeye_PTZClient_AuthorityServer_Booting = false;
        private bool m_bHawkeye_RelayServer_Booting = false;

        protected override void OnSourceInitialized(EventArgs e)
        {
            base.OnSourceInitialized(e);

            handle = new WindowInteropHelper(this).Handle;
            Hawkeye_PTZClient_AuthorityServer_Message = Win32API.RegisterWindowMessage("Hawkeye_PTZClient_AuthorityServer");
            Hawkeye_RelayServer_Message = Win32API.RegisterWindowMessage("Hawkeye_RelayServer");




            ComponentDispatcher.ThreadFilterMessage += new ThreadMessageEventHandler(ComponentDispatcher_ThreadFilterMessage);
        }
        private int Hawkeye_PTZClient_AuthorityServer_Message_Count = 0;
        private int Hawkeye_RelayServer_Message_Count = 0;


        void ComponentDispatcher_ThreadFilterMessage(ref MSG msg, ref bool handled)
        {
#if false
            if (msg.message == Hawkeye_PTZClient_AuthorityServer_Message && msg.wParam != handle)
            {
                int nMessage = (int)msg.lParam;

                if (nMessage == 1)
                {
                    string text = String.Format("제어권 서버 부팅 완료({0})", ++Hawkeye_PTZClient_AuthorityServer_Message_Count);
                    logTextBox.Text = text;

                    m_bHawkeye_PTZClient_AuthorityServer_Booting = true;
                    
                }
                else if (nMessage == 2)
                {
                    string text = String.Format("제어권 서버 부팅중({0})", ++Hawkeye_PTZClient_AuthorityServer_Message_Count);
                    logTextBox.Text = text;
                }

                System.Console.WriteLine("제어권 서버" + Hawkeye_PTZClient_AuthorityServer_Message_Count);

                //MessageBox.Show("MFC Message : " + msg.lParam.ToString());
            }
            if (msg.message == Hawkeye_RelayServer_Message && msg.wParam != handle)
            {
                int nMessage = (int)msg.lParam;
                if (nMessage == 1)
                {
                    m_bHawkeye_RelayServer_Booting = true;
                    string text = String.Format("에이전트 서버 부팅 완료({0})", ++Hawkeye_RelayServer_Message_Count);
                    logTextBox.Text = text;

                    m_bHawkeye_PTZClient_AuthorityServer_Booting = true;
                }
                else if (nMessage == 2)
                {
                    string text = String.Format("에이전트 서버 부팅중({0})", ++Hawkeye_RelayServer_Message_Count);
                    logTextBox.Text = text;
                }

                //MessageBox.Show("MFC Message : " + msg.lParam.ToString());

                System.Console.WriteLine("에이전트 서버" + msg.lParam.ToString());
            }
#endif
        }

        private void BITBtn_Click(object sender, RoutedEventArgs e)
        {

            ProcessStartInfo start = new ProcessStartInfo();

            start.Arguments = "Hawkeye_BIT";
            start.FileName = ".\\Hawkeye_BIT\\Hawkeye_BIT.exe";
            try
            {
                Process.Start(start);
            }
            catch (Exception ee)
            {

            }
        }
    }
}
