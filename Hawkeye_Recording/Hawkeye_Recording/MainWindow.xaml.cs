using ReadWriteIni;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
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

//
namespace Hawkeye_Recording
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public WindowInfoIni winInfoIni = new WindowInfoIni("RecordingWindowInfo");//윈도우정보
        public SystemIpAddrInfo recordingIPAddrInfo = new SystemIpAddrInfo("RecordingIpAddrInfo");//IP 정보(전체시스템에서이용)

        private Process[,] arrProcFFMPEG = new Process[5, 2];
        private Button[,] arrBtnStart = new Button[5, 2];
        private Button[,] arrBtnFinish = new Button[5, 2];
        private TextBlock[,] arrStatusTextBlock = new TextBlock[5, 2];
        private TextBox[,] arrCamURITextBlock = new TextBox[5, 2];

        public MainWindow()
        {
            InitializeComponent();

            Process[] processes = Process.GetProcessesByName("ffmpeg");
            Process currentProcess = Process.GetCurrentProcess();
            foreach (Process proc in processes)
            {
                if (proc.Id != currentProcess.Id)
                    proc.Kill();
            }

            recordingIPAddrInfo.ReadIni(1);
            Ch1Cam1URITextBox.Text = recordingIPAddrInfo.mainVideoUriInfo.uri;
            Ch1Cam2URITextBox.Text = recordingIPAddrInfo.subVideoUriInfo.uri;
            
            Minimize();

            for(int i=0; i<5; i++)
            {
                for (int j = 0; j < 2; j++)
                    arrProcFFMPEG[i, j] = new Process();
            }

            arrBtnStart[0, 0] = Ch1Cam1Start;
            arrBtnStart[0, 1] = Ch1Cam1Start;
            arrBtnStart[1, 0] = Ch2Cam1Start;
            arrBtnStart[1, 1] = Ch2Cam2Start;
            arrBtnStart[2, 0] = Ch3Cam1Start;
            arrBtnStart[2, 1] = Ch3Cam2Start;
            arrBtnStart[3, 0] = Ch4Cam1Start;
            arrBtnStart[3, 1] = Ch4Cam2Start;
            arrBtnStart[4, 0] = Ch5Cam1Start;
            arrBtnStart[4, 1] = Ch5Cam2Start;


            arrBtnFinish[0, 0] = Ch1Cam1Finish;
            arrBtnFinish[0, 1] = Ch1Cam2Finish;
            arrBtnFinish[1, 0] = Ch2Cam1Finish;
            arrBtnFinish[1, 1] = Ch2Cam2Finish;
            arrBtnFinish[2, 0] = Ch3Cam1Finish;
            arrBtnFinish[2, 1] = Ch3Cam2Finish;
            arrBtnFinish[3, 0] = Ch4Cam1Finish;
            arrBtnFinish[3, 1] = Ch4Cam2Finish;
            arrBtnFinish[4, 0] = Ch5Cam1Finish;
            arrBtnFinish[4, 1] = Ch5Cam2Finish;


            arrStatusTextBlock[0, 0] = Ch1Cam1Status;
            arrStatusTextBlock[0, 1] = Ch1Cam2Status;
            arrStatusTextBlock[1, 0] = Ch2Cam1Status;
            arrStatusTextBlock[1, 1] = Ch2Cam2Status;
            arrStatusTextBlock[2, 0] = Ch3Cam1Status;
            arrStatusTextBlock[2, 1] = Ch3Cam2Status;
            arrStatusTextBlock[3, 0] = Ch4Cam1Status;
            arrStatusTextBlock[3, 1] = Ch4Cam2Status;
            arrStatusTextBlock[4, 0] = Ch5Cam1Status;
            arrStatusTextBlock[4, 1] = Ch5Cam2Status;

            arrCamURITextBlock[0, 0] = Ch1Cam1URITextBox;
            arrCamURITextBlock[0, 1] = Ch1Cam2URITextBox;
            arrCamURITextBlock[1, 0] = Ch2Cam1URITextBox;
            arrCamURITextBlock[1, 1] = Ch2Cam2URITextBox;
            arrCamURITextBlock[2, 0] = Ch3Cam1URITextBox;
            arrCamURITextBlock[2, 1] = Ch3Cam2URITextBox;
            arrCamURITextBlock[3, 0] = Ch4Cam1URITextBox;
            arrCamURITextBlock[3, 1] = Ch4Cam2URITextBox;
            arrCamURITextBlock[4, 0] = Ch5Cam1URITextBox;
            arrCamURITextBlock[4, 1] = Ch5Cam2URITextBox;

            for (int i = 0; i < 5; i++)
            {
                recordingIPAddrInfo.ReadIni(i + 1);

                arrCamURITextBlock[i, 0].Text = recordingIPAddrInfo.mainVideoUriInfo.uri;
                arrCamURITextBlock[i, 1].Text = recordingIPAddrInfo.subVideoUriInfo.uri; 

            }

        }

        private void enable_Click(object sender, RoutedEventArgs e)
        {
            arrCamURITextBlock[0, 0].IsEnabled = true;
            arrCamURITextBlock[0, 1].IsEnabled = true;
            arrCamURITextBlock[1, 0].IsEnabled = true;
            arrCamURITextBlock[1, 1].IsEnabled = true;
            arrCamURITextBlock[2, 0].IsEnabled = true;
            arrCamURITextBlock[2, 1].IsEnabled = true;
            arrCamURITextBlock[3, 0].IsEnabled = true;
            arrCamURITextBlock[3, 1].IsEnabled = true;
            arrCamURITextBlock[4, 0].IsEnabled = true;
            arrCamURITextBlock[4, 1].IsEnabled = true;

         

            save.IsEnabled = true;
            enable.IsEnabled = false;
        }
        private void save_Click(object sender, RoutedEventArgs e)
        {
            arrCamURITextBlock[0, 0].IsEnabled = false;
            arrCamURITextBlock[0, 1].IsEnabled = false;
            arrCamURITextBlock[1, 0].IsEnabled = false;
            arrCamURITextBlock[1, 1].IsEnabled = false;
            arrCamURITextBlock[2, 0].IsEnabled = false;
            arrCamURITextBlock[2, 1].IsEnabled = false;
            arrCamURITextBlock[3, 0].IsEnabled = false;
            arrCamURITextBlock[3, 1].IsEnabled = false;
            arrCamURITextBlock[4, 0].IsEnabled = false;
            arrCamURITextBlock[4, 1].IsEnabled = false;

            for (int i = 0; i < 5; i++)
            {
                recordingIPAddrInfo.mainVideoUriInfo.uri = arrCamURITextBlock[i, 0].Text;
                recordingIPAddrInfo.subVideoUriInfo.uri = arrCamURITextBlock[i, 1].Text;

                recordingIPAddrInfo.WriteIni(i + 1);
            }
           


            save.IsEnabled = false;
            enable.IsEnabled = true;
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;
            //축소
            Minimize();
        }

        private void MaximizeButton_Click(object sender, RoutedEventArgs e)
        {
            Maximize();
        }
        private void Maximize()
        {
            MaximizeButton.Visibility = Visibility.Hidden;

            WindowStyle = WindowStyle.ToolWindow;


            Height = winInfoIni.maximizeHeight;
            Width = winInfoIni.maximizeWidth;

            Top = System.Windows.SystemParameters.PrimaryScreenHeight / 2 - Height / 2;
            Left = System.Windows.SystemParameters.PrimaryScreenWidth / 2 - Width / 2;

#if false
            ChannelGroup.Visibility = Visibility.Visible;
            PTZConnectionGroup.Visibility = Visibility.Visible;
            dayTimeGroup.Visibility = Visibility.Visible;
            thermalImageryGroup.Visibility = Visibility.Visible;
            iondayTimeConnectGroup.Visibility = Visibility.Visible;
            MicConnectionGroup.Visibility = Visibility.Visible;
#else
            Ch1Group.Visibility = Visibility.Visible;
#endif
            Topmost = true;
            //ch1Btn.IsChecked = true;
            //systemIPAddrInfo.ReadIni(1);
            //PackText();

            //WindowHideFromTaskListExt.HideFromTaskList(this);
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
#if false
            ChannelGroup.Visibility = Visibility.Hidden;
            PTZConnectionGroup.Visibility = Visibility.Hidden;
            dayTimeGroup.Visibility = Visibility.Hidden;
            thermalImageryGroup.Visibility = Visibility.Hidden;
            iondayTimeConnectGroup.Visibility = Visibility.Hidden;
            MicConnectionGroup.Visibility = Visibility.Hidden;
#else

#endif
            Topmost = true;
      

            //WindowHideFromTaskListExt.HideFromTaskList(this);
        }

        public string GetTimeNow()
        {
            return DateTime.Now.ToString("yyyyMMddHHmmss");
        }


        private void WriteFileFromSteam(int nCh, int nCameraNum, string streamURI, string dstFile, string fps, string recordingTime)
        {
           
            //, Ch1Cam1Start, Ch1Cam1Finish
            //ffmpeg -rtsp_transport tcp -i rtsp://184.72.239.149/vod/mp4:BigBuckBunny_175k.mov -r 30 -vcodec copy -an -t 900 %RECpath%/%name%.mp4

            try
            {
                string strFFMPEGOut;
                ProcessStartInfo psiProcInfo = new ProcessStartInfo();
                TimeSpan estimatedTime = TimeSpan.MaxValue;

                StreamReader srFFMPEG;
                //string strFFMPEGCmd = " -i \"" + srcFile + "\" -ar 44100 " + videoRateOption + videoSizeOption + " -y \"" + dstFile + "\"";
                string strFFMPEGCmd = " -rtsp_transport " + "tcp" + " -i \"" + streamURI + "\"" + " -r " + fps + " -vcodec copy -an -t " + recordingTime + " \"" + dstFile + "\"";


                psiProcInfo.FileName = System.AppDomain.CurrentDomain.BaseDirectory + ((IntPtr.Size == 8) ? "x64" : "x86") + "\\ffmpeg.exe";
                psiProcInfo.Arguments = strFFMPEGCmd;
                psiProcInfo.UseShellExecute = false;
                psiProcInfo.WindowStyle = ProcessWindowStyle.Hidden;
                psiProcInfo.RedirectStandardError = true;
                psiProcInfo.RedirectStandardOutput = true;
                psiProcInfo.RedirectStandardInput = true;
                psiProcInfo.CreateNoWindow = true;

                arrProcFFMPEG[nCh - 1, nCameraNum - 1].StartInfo = psiProcInfo;

                arrProcFFMPEG[nCh - 1, nCameraNum - 1].Start();

                srFFMPEG = arrProcFFMPEG[nCh - 1, nCameraNum - 1].StandardError;


                do
                {
                    strFFMPEGOut = srFFMPEG.ReadLine();
                    if (strFFMPEGOut != null)
                    {

                        string status = "";

                        string findWord = "fps=";
                        string curFPS = "";
                        int findPos = strFFMPEGOut.TrimStart().IndexOf(findWord);
                        if (findPos != -1)
                        {
                            try
                            {
                                string text = strFFMPEGOut.TrimStart().Substring(findPos + findWord.Length, 3);
                                //int pos = text.IndexOf(",");
                                curFPS = text;
                            }
                            catch
                            {
                            }
                        }
                        findWord = "time=";
                        string curTime = "";
                        findPos = strFFMPEGOut.TrimStart().IndexOf(findWord);
                        if (findPos != -1)
                        {
                            try
                            {
                                string text = strFFMPEGOut.TrimStart().Substring(findPos + findWord.Length, 11);
                                //int pos = text.IndexOf(",");
                                curTime = text;
                            }
                            catch
                            {
                            }
                        }
                        status = "FPS=" + curFPS + " Time=" + curTime;
                        if (curFPS != "" && curTime != "")
                        {
                            if (!arrStatusTextBlock[nCh - 1, nCameraNum - 1].Dispatcher.CheckAccess())
                            {
                                this.Dispatcher.Invoke(
                                  System.Windows.Threading.DispatcherPriority.Normal,
                                  new Action(
                                    delegate ()
                                    {
                                        arrStatusTextBlock[nCh - 1, nCameraNum - 1].Text = status;
                                    }
                                ));
                            }
                            else
                            {
                                arrStatusTextBlock[nCh - 1, nCameraNum - 1].Text = status;
                            }
                        }


#if false
                        if (estimatedTime != TimeSpan.MaxValue)
                        {
                            // 예측 시간이 나왔으면.
                            string time = "time=";
                            int startPos = strFFMPEGOut.IndexOf(time);
                            if (startPos != -1)
                            {
                                string text = strFFMPEGOut.Substring(startPos + time.Length);
                                int pos = text.IndexOf(" ");
                                string current = text.Substring(0, pos);

                                TimeSpan currentTime = TimeSpan.Parse(current);

                                int progresss = (int)(currentTime.TotalMilliseconds * 100 / estimatedTime.TotalMilliseconds);


                                if (!outputTextBlock.Dispatcher.CheckAccess())
                                {
                                    this.Dispatcher.Invoke(
                                      System.Windows.Threading.DispatcherPriority.Normal,
                                      new Action(
                                        delegate ()
                                        {
                                            outputTextBlock.Text = "";
                                        }
                                    ));
                                }
                                else
                                {
                                    outputTextBlock.Text = "";
                                }
                                /*
                                this.BeginInvoke(new MethodInvoker(() =>
                                {
                                    this.progressBar1.Value = progresss;
                                }));
                                */
                            }

                        }
#endif
                        Console.WriteLine(strFFMPEGOut);
                    }

                } while (arrProcFFMPEG[nCh - 1, nCameraNum - 1].HasExited == false);

            }
            finally
            {
                if (!arrStatusTextBlock[nCh - 1, nCameraNum - 1].Dispatcher.CheckAccess())
                {
                    this.Dispatcher.Invoke(
                      System.Windows.Threading.DispatcherPriority.Normal,
                      new Action(
                        delegate ()
                        {
                            arrStatusTextBlock[nCh - 1, nCameraNum - 1].Text = "녹화 종료";
                            arrBtnStart[nCh - 1, nCameraNum - 1].IsEnabled = true;
                            arrBtnFinish[nCh - 1, nCameraNum - 1].IsEnabled = false;
                        }
                    ));
                }
                else
                {
                    arrStatusTextBlock[nCh - 1, nCameraNum - 1].Text = "녹화 종료";
                    arrBtnStart[nCh - 1, nCameraNum - 1].IsEnabled = true;
                    arrBtnFinish[nCh - 1, nCameraNum - 1].IsEnabled = false;
                }
                /*
                this.BeginInvoke(new MethodInvoker(() =>
                {
                    this.Text = "Done!";
                    this.btnStart.Enabled = true;
                    this.progressBar1.Value = 100;
                }));
                */
            }

        }
        private void StartRecord(int nCh, int nCameraNum)
        {
            this.arrBtnStart[nCh - 1, nCameraNum - 1].IsEnabled = false;
            this.arrBtnFinish[nCh - 1, nCameraNum - 1].IsEnabled = true;

            this.arrStatusTextBlock[nCh - 1, nCameraNum - 1].Text = "스트림 여는중...";

            string folderName = String.Format("Video\\Ch{0:d2}\\Cam{1:d2}\\", nCh, nCameraNum);
         
            string dstFile = folderName + GetTimeNow() + ".mp4";

            string streamURI = arrCamURITextBlock[nCh - 1, nCameraNum - 1].Text;
            ThreadPool.QueueUserWorkItem((object state) =>
            {
                //"3600" 1hour
                WriteFileFromSteam(nCh, nCameraNum, streamURI, dstFile, "30", "3600");
            });
        }
        private void FinishRecord(int nCh, int nCameraNum)
        {
            //종료커맨드전송          
            StreamWriter swFFMPEG;
            swFFMPEG = arrProcFFMPEG[nCh - 1, nCameraNum - 1].StandardInput;
            swFFMPEG.WriteLine("q");
        } 
        private void Ch1Cam1Start_Click(object sender, RoutedEventArgs e)
        {
            int nCh = 1;
            int nCameraNum = 1;

            StartRecord(nCh, nCameraNum);
#if false
            this.Ch1Cam1Start.IsEnabled = false;
            this.Ch1Cam1Finish.IsEnabled = true;

            this.Ch1Cam1Status.Text = "Loading...";

            string dstFile = AppDomain.CurrentDomain.BaseDirectory + "Video\\Ch01\\Cam01\\" + UnixTimeNow() + ".mp4";
            
            string streamURI = Ch1Cam1URITextBox.Text;
            ThreadPool.QueueUserWorkItem((object state) =>
            {            
                //"3600"
                WriteFileFromSteam(1, 1, streamURI, dstFile, "30", "3600");
            });
#endif
        }

        private void Ch1Cam1Finish_Click(object sender, RoutedEventArgs e)
        {
            int nCh = 1;
            int nCameraNum = 1;
            FinishRecord(nCh, nCameraNum);          
        }

        private void Ch1Cam2Start_Click(object sender, RoutedEventArgs e)
        {
            int nCh = 1;
            int nCameraNum = 2;

            StartRecord(nCh, nCameraNum);
        }

        private void Ch1Cam2Finish_Click(object sender, RoutedEventArgs e)
        {
            int nCh = 1;
            int nCameraNum = 2;
            FinishRecord(nCh, nCameraNum);
        }
        
        private void Ch2Cam1Start_Click(object sender, RoutedEventArgs e)
        {
            int nCh = 2;
            int nCameraNum = 1;

            StartRecord(nCh, nCameraNum);
        }

        private void Ch2Cam1Finish_Click(object sender, RoutedEventArgs e)
        {
            int nCh = 2;
            int nCameraNum = 1;
            FinishRecord(nCh, nCameraNum);
        }

        private void Ch2Cam2Start_Click(object sender, RoutedEventArgs e)
        {
            int nCh = 2;
            int nCameraNum = 2;

            StartRecord(nCh, nCameraNum);
        }

        private void Ch2Cam2Finish_Click(object sender, RoutedEventArgs e)
        {
            int nCh = 2;
            int nCameraNum = 2;
            FinishRecord(nCh, nCameraNum);
        }

        private void Ch3Cam1Start_Click(object sender, RoutedEventArgs e)
        {
            int nCh = 3;
            int nCameraNum = 1;

            StartRecord(nCh, nCameraNum);
        }

        private void Ch3Cam1Finish_Click(object sender, RoutedEventArgs e)
        {
            int nCh = 3;
            int nCameraNum = 1;
            FinishRecord(nCh, nCameraNum);
        }

        private void Ch3Cam2Start_Click(object sender, RoutedEventArgs e)
        {
            int nCh = 3;
            int nCameraNum = 2;

            StartRecord(nCh, nCameraNum);
        }

        private void Ch3Cam2Finish_Click(object sender, RoutedEventArgs e)
        {
            int nCh = 3;
            int nCameraNum = 2;
            FinishRecord(nCh, nCameraNum);
        }

        private void Ch4Cam1Start_Click(object sender, RoutedEventArgs e)
        {
            int nCh = 4;
            int nCameraNum = 1;

            StartRecord(nCh, nCameraNum);
        }

        private void Ch4Cam1Finish_Click(object sender, RoutedEventArgs e)
        {
            int nCh = 4;
            int nCameraNum = 1;
            FinishRecord(nCh, nCameraNum);
        }

        private void Ch4Cam2Start_Click(object sender, RoutedEventArgs e)
        {
            int nCh = 4;
            int nCameraNum = 2;

            StartRecord(nCh, nCameraNum);
        }

        private void Ch4Cam2Finish_Click(object sender, RoutedEventArgs e)
        {
            int nCh = 4;
            int nCameraNum = 2;
            FinishRecord(nCh, nCameraNum);
        }

        private void Ch5Cam1Start_Click(object sender, RoutedEventArgs e)
        {
            int nCh = 5;
            int nCameraNum = 1;

            StartRecord(nCh, nCameraNum);
        }

        private void Ch5Cam1Finish_Click(object sender, RoutedEventArgs e)
        {
            int nCh = 5;
            int nCameraNum = 1;
            FinishRecord(nCh, nCameraNum);
        }

        private void Ch5Cam2Start_Click(object sender, RoutedEventArgs e)
        {
            int nCh = 5;
            int nCameraNum = 2;

            StartRecord(nCh, nCameraNum);
        }

        private void Ch5Cam2Finish_Click(object sender, RoutedEventArgs e)
        {
            int nCh = 5;
            int nCameraNum = 2;
            FinishRecord(nCh, nCameraNum);
        }
    }
}
