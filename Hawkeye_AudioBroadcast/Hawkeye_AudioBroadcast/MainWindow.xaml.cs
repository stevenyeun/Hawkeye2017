using ReadWriteIni;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
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
using Microsoft.VisualBasic;
using System.Windows.Threading;
using Microsoft.Win32;
using TVSLib;
using System.Windows.Interop;
using Ownskit.Applications.DrawAnywhere.Utils;

namespace Hawkeye_AudioBroadcast
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    /// 
 

    public partial class MainWindow : Window
    {
        [DllImport("winmm.dll", EntryPoint = "mciSendStringA", CharSet = CharSet.Ansi, SetLastError = true, ExactSpelling = true)]
        private static extern int mciSendString(string lpstrCommand, string lpstrReturnString, int uReturnLength, int hwndCallback);

      
        public MainWindow()
        {
            InitializeComponent();

           

            Minimize();

        }

        private uint message;
        private IntPtr handle;

        public const uint HWND_BROADCAST = 0xffff;

        [DllImport("user32.dll", CharSet = CharSet.Unicode)]
        public static extern uint RegisterWindowMessage(string lpString);

        [DllImport("user32.dll", CharSet = CharSet.Unicode)]
        public static extern bool PostMessage(IntPtr hWnd, uint Msg, uint wParam, uint lParam);

        public AudioFile audioIni = new AudioFile("AudioFile");
        public WindowInfoIni winInfoIni = new WindowInfoIni("AudioBroadcastWindowInfo");//윈도우정보
        Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();

        string[] pathArr;
        string path;
        int ch = -1;
        

        private bool ck_record = false;



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
            inputbox.Visibility = Visibility.Hidden;
            Topmost = true;

            WindowHideFromTaskListExt.HideFromTaskList(this);
        }

        private void Maximize()
        {


            WindowStyle = WindowStyle.ToolWindow;


            Height = winInfoIni.maximizeHeight;
            Width = winInfoIni.maximizeWidth;

            Top = System.Windows.SystemParameters.PrimaryScreenHeight / 2 - Height / 2;
            Left = System.Windows.SystemParameters.PrimaryScreenWidth / 2 - Width / 2;


            MaximizeButton.Visibility = Visibility.Hidden;
            ChannelGroup.Visibility = Visibility.Visible;
            ButtonGroup.Visibility = Visibility.Visible;

            //ch1Btn.IsChecked = true;

            //MaximizeButton.Visibility = Visibility.Hidden;

            //ChannelGroup.Visibility = Visibility.Visible;
            //ButtonGroup.Visibility = Visibility.Visible;
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

            ch1Btn.IsChecked = true;
            ch = 1;
            audioIni.ReadIni(ch);
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

        private void MaximizeButton_Click(object sender, RoutedEventArgs e)
        {
            Maximize();
        }

        private void ch1Btn_Checked(object sender, RoutedEventArgs e)
        {
            ch = 1;
            unpack();
        }
        private void ch2Btn_Checked(object sender, RoutedEventArgs e)
        {
            ch = 2;
            unpack();
        }
        private void ch3Btn_Checked(object sender, RoutedEventArgs e)
        {
            ch = 3;
            unpack();
        }
        private void ch4Btn_Checked(object sender, RoutedEventArgs e)
        {
            ch = 4;
            unpack();
        }
        private void ch5Btn_Checked(object sender, RoutedEventArgs e)
        {
            ch = 5;
            unpack();
        }

        private void unpack()
        {
            audioIni.ReadIni(ch);
            pathArr = audioIni.fileName.Split('\\');

            path = pathArr.Last().ToString();
            

            if (path == "") SelectedFile.Content = "선택된 파일이 없습니다";
            else SelectedFile.Content = path;

        }

        private void RecordButton_Click(object sender, RoutedEventArgs e)
        {
            if (!ck_record)
            {
                ck_record = true;
                SendButton.IsEnabled = false;
                RecordButton.Content = "녹음 중지";
                mciSendString("open new Type waveaudio Alias recsound", null, 0, 0);
                mciSendString("record recsound", null, 0, 0);
                Console.WriteLine();
                Console.ReadLine();
            }
            else if(ck_record)
            {
                ck_record = false;
                inputbox.Visibility = Visibility.Visible;
                ButtonGroup.Visibility = Visibility.Hidden;
                fileName.Text = DateTime.Now.AddDays(0).ToString("yyyyMMddHHmmss") + "_"  ;


            }


        }

        protected override void OnSourceInitialized(EventArgs e)
        {
            base.OnSourceInitialized(e);

            handle = new WindowInteropHelper(this).Handle;
            message = RegisterWindowMessage("Hawkeye_AudioBroadcast");
            ComponentDispatcher.ThreadFilterMessage += new ThreadMessageEventHandler(ComponentDispatcher_ThreadFilterMessage);
        }

        void ComponentDispatcher_ThreadFilterMessage(ref MSG msg, ref bool handled)
        {
            if (msg.message == message && msg.wParam != handle)
            {
                MessageBox.Show("Message : " + msg.lParam.ToString());
            }
        }

        private void SendButton_Click(object sender, RoutedEventArgs e)
        {
            PostMessage((IntPtr)HWND_BROADCAST, message, (uint)handle, (uint)ch);
        }

        private void ok_Click(object sender, RoutedEventArgs e)
        {
            RecordButton.Content = "녹음 시작";
            SendButton.IsEnabled = true;

            path = fileName.Text;
           // mciSendString("save recsound \.\\"+ "" + path + ""+".wav", null, 0, 0);
            mciSendString("save recsound \".\\"+path+".wav\"", null, 0, 0);

            //AppDomain.CurrentDomain.BaseDirectory

            mciSendString("close recsound ", null, 0, 0);
            SelectedFile.Content = path + ".wav";

            audioIni.fileName = AppDomain.CurrentDomain.BaseDirectory + path+".wav";


            audioIni.WriteIni(ch);

            inputbox.Visibility = Visibility.Hidden;
            ButtonGroup.Visibility = Visibility.Visible;
        }

        private void cancle_Click(object sender, RoutedEventArgs e)
        {
            RecordButton.Content = "녹음 시작";
            SendButton.IsEnabled = true;
            inputbox.Visibility = Visibility.Hidden;
            ButtonGroup.Visibility = Visibility.Visible;
        }

        private void loadFile_Click(object sender, RoutedEventArgs e)
        {
            dlg.DefaultExt = ".txt";
            dlg.Filter = "WAV | *.wav";

            Nullable<bool> result = dlg.ShowDialog();

            // Get the selected file name and display in a TextBox 
            if (result == true)
            {
                // Open document 

                pathArr = dlg.FileName.Split('\\');

                SelectedFile.Content = pathArr.Last().ToString();

                audioIni.fileName = dlg.FileName.ToString();


                audioIni.WriteIni(ch);

            }
        }
    }
}
