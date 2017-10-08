using Hawkeye_LIB;
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
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Hawkeye_PTZEnvSetup
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        public WindowInfoIni winInfoIni = new WindowInfoIni("PTZEnvSetupWindowInfo");//윈도우정보
        public PTZEnvSetup systemPTZEnvSetup = new PTZEnvSetup("PTZEnvSetup");
        private uint message;
        private IntPtr handle;
        public MainWindow()
        {
            InitializeComponent();
            winInfoIni.ReadIni();
            Minimize();
            this.sliderPan.ValueChanged += new RoutedPropertyChangedEventHandler<double>(sliderHighPan_ValueChanged);
            this.sliderMiddlePan.ValueChanged += new RoutedPropertyChangedEventHandler<double>(sliderMiddlePan_ValueChanged);
            this.sliderLowPan.ValueChanged += new RoutedPropertyChangedEventHandler<double>(sliderLowPan_ValueChanged);

            this.sliderZoom.ValueChanged += new RoutedPropertyChangedEventHandler<double>(sliderHighZoom_ValueChanged);
            this.sliderMiddleZoom.ValueChanged += new RoutedPropertyChangedEventHandler<double>(sliderMiddleZoom_ValueChanged);
            this.sliderLowZoom.ValueChanged += new RoutedPropertyChangedEventHandler<double>(sliderLowZoom_ValueChanged);

            this.sliderFocus.ValueChanged += new RoutedPropertyChangedEventHandler<double>(sliderHighFocus_ValueChanged);
            this.sliderMiddleFocus.ValueChanged += new RoutedPropertyChangedEventHandler<double>(sliderMiddleFocus_ValueChanged);
            this.sliderLowFocus.ValueChanged += new RoutedPropertyChangedEventHandler<double>(sliderLowFocus_ValueChanged);

        }
        protected override void OnSourceInitialized(EventArgs e)
        {
            base.OnSourceInitialized(e);

            handle = new WindowInteropHelper(this).Handle;
            message = Win32API.RegisterWindowMessage("Hawkeye_PTZEnvSetup");
            ComponentDispatcher.ThreadFilterMessage += new ThreadMessageEventHandler(ComponentDispatcher_ThreadFilterMessage);
        }
        void ComponentDispatcher_ThreadFilterMessage(ref MSG msg, ref bool handled)
        {
            if (msg.message == message && msg.wParam != handle)
            {
                MessageBox.Show("MFC Message : " + msg.lParam.ToString());
            }
        }
        private void sliderHighPan_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            panHighSpeed.Text = ((int)e.NewValue).ToString();
        }
        private void sliderMiddlePan_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {

            panMiddleSpeed.Text = ((int)e.NewValue).ToString();
        }
        private void sliderLowPan_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {

            panLowSpeed.Text = ((int)e.NewValue).ToString();
        }




        private void sliderHighZoom_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {

            ZoomHighSpeed.Text = ((int)e.NewValue).ToString();
        }
        private void sliderMiddleZoom_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {

            ZoomMiddleSpeed.Text = ((int)e.NewValue).ToString();
        }
        private void sliderLowZoom_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {

            ZoomLowSpeed.Text = ((int)e.NewValue).ToString();
        }



        private void sliderHighFocus_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {

            FocusHighSpeed.Text = ((int)e.NewValue).ToString();
        }
        private void sliderMiddleFocus_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {

            FocusMiddleSpeed.Text = ((int)e.NewValue).ToString();
        }
        private void sliderLowFocus_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {

            FocusLowSpeed.Text = ((int)e.NewValue).ToString();
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
            panSpeedGroup.Visibility = Visibility.Hidden;
            zoomSpeedGroup.Visibility = Visibility.Hidden;
            focusSpeedGroup.Visibility = Visibility.Hidden;
            cameraAngleGroup.Visibility = Visibility.Hidden;
            focusAreaGroup.Visibility = Visibility.Hidden;
            rangeSurveillanceGroup.Visibility = Visibility.Hidden;
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
        private void MaximizeButton_Click(object sender, RoutedEventArgs e)
        {
            Maximize();

            //SetCameraInfo();

            //await BaseRefreshAsync();
        }

        private void Maximize()
        {
            MaximizeButton.Visibility = Visibility.Hidden;

            WindowStyle = WindowStyle.ToolWindow;


            Height = winInfoIni.maximizeHeight;
            Width = winInfoIni.maximizeWidth;

            Top = System.Windows.SystemParameters.PrimaryScreenHeight / 2 - Height / 2;
            Left = System.Windows.SystemParameters.PrimaryScreenWidth / 2 - Width / 2;


            ChannelGroup.Visibility = Visibility.Visible;
            panSpeedGroup.Visibility = Visibility.Visible;
            zoomSpeedGroup.Visibility = Visibility.Visible;
            focusSpeedGroup.Visibility = Visibility.Visible;
            cameraAngleGroup.Visibility = Visibility.Visible;
            focusAreaGroup.Visibility = Visibility.Visible;
            rangeSurveillanceGroup.Visibility = Visibility.Visible;
      

            Topmost = true;
            ch1Btn.IsChecked = true;

            WindowHideFromTaskListExt.HideFromTaskList(this);
        }

        private void ch1Btn_Checked(object sender, RoutedEventArgs e)
        {
            systemPTZEnvSetup.ReadIni(1);
            autoButton.IsEnabled = false;
            //handOperatedButton.IsEnabled = true;
            PackText();
        }

        private void ch2Btn_Checked(object sender, RoutedEventArgs e)
        {
            systemPTZEnvSetup.ReadIni(2);
            autoButton.IsEnabled = false;
            //handOperatedButton.IsEnabled = true;        
            PackText();
        }

        private void ch3Btn_Checked(object sender, RoutedEventArgs e)
        {
            systemPTZEnvSetup.ReadIni(3);
            autoButton.IsEnabled = false;
            //handOperatedButton.IsEnabled = true;
            PackText();
        }

        private void ch4Btn_Checked(object sender, RoutedEventArgs e)
        {
            systemPTZEnvSetup.ReadIni(4);
            autoButton.IsEnabled = false;
            //handOperatedButton.IsEnabled = true;
            PackText();
        }

        private void ch5Btn_Checked(object sender, RoutedEventArgs e)
        {
            systemPTZEnvSetup.ReadIni(5);
            autoButton.IsEnabled = false;
            //handOperatedButton.IsEnabled = true;
            PackText();
        }

        private void PackText()
        {
            panHighSpeed.Text = systemPTZEnvSetup.PanTiltSpeed.High;
            panMiddleSpeed.Text = systemPTZEnvSetup.PanTiltSpeed.Mid;
            panLowSpeed.Text = systemPTZEnvSetup.PanTiltSpeed.Low;



            ZoomHighSpeed.Text = systemPTZEnvSetup.HighZoomSpeed.High;
            ZoomMiddleSpeed.Text = systemPTZEnvSetup.HighZoomSpeed.Mid;
            ZoomLowSpeed.Text = systemPTZEnvSetup.HighZoomSpeed.Low;


            FocusHighSpeed.Text = systemPTZEnvSetup.HighFocusSpeed.High;
            FocusMiddleSpeed.Text = systemPTZEnvSetup.HighFocusSpeed.Mid;
            FocusLowSpeed.Text = systemPTZEnvSetup.HighFocusSpeed.Low;


            azimuth.Text = systemPTZEnvSetup.azimuth;
            angleOfElevation.Text = systemPTZEnvSetup.angleOfElevation;

            maxFocus.Text = systemPTZEnvSetup.maxFocus;
            minFocus.Text = systemPTZEnvSetup.minFocus;

            ptHighSpeedZoomValTextBox.Text = systemPTZEnvSetup.ptHighSpeedZoomVal;
            ptMidSpeedZoomValTextBox.Text = systemPTZEnvSetup.ptMidSpeedZoomVal;
            ptLowSpeedZoomValTextBox.Text = systemPTZEnvSetup.ptLowSpeedZoomVal;

            try
            {
                zoomPanTiltInterLocking.IsChecked = bool.Parse(systemPTZEnvSetup.zoomPanTiltInterLocking);
            }
            catch
            {
                zoomPanTiltInterLocking.IsChecked = false;
            }
         

              
            range.Text = systemPTZEnvSetup.rangeSurveillance;
            area.Text = systemPTZEnvSetup.area;

            latitudeDegrees.Text = systemPTZEnvSetup.Lat.degrees;
            latitudeMinute.Text = systemPTZEnvSetup.Lat.minute;
            latitudeSecond.Text = systemPTZEnvSetup.Lat.second;
            latitudeSecondDot.Text = systemPTZEnvSetup.Lat.secondDot;

            longitudeDegrees.Text = systemPTZEnvSetup.Long.degrees;
            longitudeMinute.Text = systemPTZEnvSetup.Long.minute;
            longitudeSecond.Text = systemPTZEnvSetup.Long.second;
            longitudeSecondDot.Text = systemPTZEnvSetup.Long.secondDot;

            if (panHighSpeed.Text != "") sliderPan.Value = Int32.Parse(panHighSpeed.Text);
            else { sliderPan.Value = 1001; panHighSpeed.Text = "1001"; }

            if (panMiddleSpeed.Text != "") sliderMiddlePan.Value = Int32.Parse(panMiddleSpeed.Text);
            else { sliderMiddlePan.Value = 501; panMiddleSpeed.Text = "501"; }

            if (panLowSpeed.Text != "") sliderLowPan.Value = Int32.Parse(panLowSpeed.Text);
            else { sliderLowPan.Value = 9; panLowSpeed.Text = "9"; }

            /////////////////////////////////////////////////////////////////////////////////

            if (ZoomHighSpeed.Text != "") sliderZoom.Value = Int32.Parse(ZoomHighSpeed.Text);
            else { sliderZoom.Value = 71; ZoomHighSpeed.Text = "71"; }

            if (ZoomMiddleSpeed.Text != "") sliderMiddleZoom.Value = Int32.Parse(ZoomMiddleSpeed.Text);
            else { sliderMiddleZoom.Value = 31; ZoomMiddleSpeed.Text = "31"; }

            if (ZoomLowSpeed.Text != "") sliderLowZoom.Value = Int32.Parse(ZoomLowSpeed.Text);
            else { sliderLowZoom.Value = 1; ZoomLowSpeed.Text = "1"; }

            //////////////////////////////////////////////////////////////////////////////

                if (FocusHighSpeed.Text != "") sliderFocus.Value = Int32.Parse(FocusHighSpeed.Text);
            else { sliderFocus.Value = 141; FocusHighSpeed.Text = "141"; }

            if (FocusMiddleSpeed.Text != "") sliderMiddleFocus.Value = Int32.Parse(FocusMiddleSpeed.Text);
            else { sliderMiddleFocus.Value = 61; FocusMiddleSpeed.Text = "61"; }

            if (FocusLowSpeed.Text != "") sliderLowFocus.Value = Int32.Parse(FocusLowSpeed.Text);
            else { sliderLowFocus.Value = 1; FocusLowSpeed.Text = "1"; }
            
        }
        private void enable_Click(object sender, RoutedEventArgs e)
        {
            sliderPan.IsEnabled = true;
            sliderMiddlePan.IsEnabled = true;
            sliderLowPan.IsEnabled = true;

            sliderZoom.IsEnabled = true;
            sliderMiddleZoom.IsEnabled = true;
            sliderLowZoom.IsEnabled = true;

            sliderFocus.IsEnabled = true;
            sliderMiddleFocus.IsEnabled = true;
            sliderLowFocus.IsEnabled = true;

            azimuth.IsEnabled = true;
            angleOfElevation.IsEnabled = true;

            maxFocus.IsEnabled = true;
            minFocus.IsEnabled = true;

            zoomPanTiltInterLocking.IsEnabled = true;
            ptLowSpeedZoomValTextBox.IsEnabled = true;
            ptMidSpeedZoomValTextBox.IsEnabled = true;
            ptHighSpeedZoomValTextBox.IsEnabled = true;

            range.IsEnabled = true;
            area.IsEnabled = true;

            //handOperatedButton.IsEnabled = true;

            enable.IsEnabled = false;
            save.IsEnabled = true;

            //
            latitudeDegrees.IsEnabled = true;
            latitudeMinute.IsEnabled = true;
            latitudeSecond.IsEnabled = true;
            latitudeSecondDot.IsEnabled = true;

            longitudeDegrees.IsEnabled = true;
            longitudeMinute .IsEnabled = true;
            longitudeSecond.IsEnabled = true;
            longitudeSecondDot.IsEnabled = true;
        }

        private void save_Click(object sender, RoutedEventArgs e)
        {
            int ch = 0;

            if (ch1Btn.IsChecked == true)
                ch = 1;
            if (ch2Btn.IsChecked == true)
                ch = 2;
            if (ch3Btn.IsChecked == true)
                ch = 3;
            if (ch4Btn.IsChecked == true)
                ch = 4;
            if (ch5Btn.IsChecked == true)
                ch = 5;

            if (ch == 0)
                MessageBox.Show("채널이 선택 되지않았습니다.");

            try
            {
                if (double.Parse(azimuth.Text) < 0 || double.Parse(azimuth.Text) > 360) MessageBox.Show("방위각 보정치 범위는 000.000 ~ 359.999 입니다");

                else if (Int32.Parse(angleOfElevation.Text) < -180 || Int32.Parse(angleOfElevation.Text) > 180) MessageBox.Show("고저각 보정치 범위는 -180 ~ 180 입니다");


                else if (Int32.Parse(range.Text) < 100 || Int32.Parse(range.Text) > 20000) MessageBox.Show("감시 거리 범위는 100 ~ 20000 입니다");

                else if (Int32.Parse(maxFocus.Text) < 0 || Int32.Parse(minFocus.Text) < 0) MessageBox.Show("최소 포커스 또는 최대 포커스 값이 0보다 작습니다");

                else if (Int32.Parse(minFocus.Text) > Int32.Parse(maxFocus.Text)) MessageBox.Show("최소 포커스 값이 최대 포커스 값보다 큽니다");

                else if (Int32.Parse(latitudeDegrees.Text) < 0 || Int32.Parse(latitudeDegrees.Text) > 179) MessageBox.Show("위도(시) 범위는 0 ~ 179 입니다");

                else if (Int32.Parse(latitudeMinute.Text) < 0 || Int32.Parse(latitudeMinute.Text) > 59) MessageBox.Show("위도(분) 범위는 0 ~ 59 입니다");

                else if (Int32.Parse(latitudeSecond.Text) < 0 || Int32.Parse(latitudeSecond.Text) > 59) MessageBox.Show("위도(초) 범위는 0 ~ 59 입니다");

                else if (Int32.Parse(latitudeSecondDot.Text) < 0 || Int32.Parse(latitudeSecondDot.Text) > 99) MessageBox.Show("위도(0.초) 범위는 0 ~ 99 입니다");

                else if (Int32.Parse(longitudeDegrees.Text) < 0 || Int32.Parse(longitudeDegrees.Text) > 179) MessageBox.Show("경도(시) 범위는 0 ~ 179 입니다");

                else if (Int32.Parse(longitudeMinute.Text) < 0 || Int32.Parse(longitudeMinute.Text) > 59) MessageBox.Show("경도(분) 범위는 0 ~ 59 입니다");

                else if (Int32.Parse(longitudeSecond.Text) < 0 || Int32.Parse(longitudeSecond.Text) > 59) MessageBox.Show("경도(초) 범위는 0 ~ 59 입니다");

                else if (Int32.Parse(longitudeSecondDot.Text) < 0 || Int32.Parse(longitudeSecondDot.Text) > 99) MessageBox.Show("경도(0.초) 범위는 0 ~ 99 입니다");

                else
                {
                    systemPTZEnvSetup.ptHighSpeedZoomVal = ptHighSpeedZoomValTextBox.Text;
                    systemPTZEnvSetup.ptMidSpeedZoomVal = ptMidSpeedZoomValTextBox.Text;
                    systemPTZEnvSetup.ptLowSpeedZoomVal = ptLowSpeedZoomValTextBox.Text;

                    
                    systemPTZEnvSetup.zoomPanTiltInterLocking = zoomPanTiltInterLocking.IsChecked.ToString();
                    systemPTZEnvSetup.PanTiltSpeed.High = panHighSpeed.Text;
                    systemPTZEnvSetup.PanTiltSpeed.Mid = panMiddleSpeed.Text;
                    systemPTZEnvSetup.PanTiltSpeed.Low = panLowSpeed.Text;

                    systemPTZEnvSetup.HighZoomSpeed.High = ZoomHighSpeed.Text;
                    systemPTZEnvSetup.HighZoomSpeed.Mid = ZoomMiddleSpeed.Text;
                    systemPTZEnvSetup.HighZoomSpeed.Low = ZoomLowSpeed.Text;

                    systemPTZEnvSetup.HighFocusSpeed.High = FocusHighSpeed.Text;
                    systemPTZEnvSetup.HighFocusSpeed.Mid = FocusMiddleSpeed.Text;
                    systemPTZEnvSetup.HighFocusSpeed.Low = FocusLowSpeed.Text;

                    systemPTZEnvSetup.azimuth = azimuth.Text;
                    systemPTZEnvSetup.angleOfElevation = angleOfElevation.Text;

                    systemPTZEnvSetup.maxFocus = maxFocus.Text;
                    systemPTZEnvSetup.minFocus = minFocus.Text;

                    systemPTZEnvSetup.area = area.Text;
                    systemPTZEnvSetup.rangeSurveillance = range.Text;

                    systemPTZEnvSetup.Lat.degrees = latitudeDegrees.Text;
                    systemPTZEnvSetup.Lat.minute = latitudeMinute.Text;
                    systemPTZEnvSetup.Lat.second = latitudeSecond.Text;
                    systemPTZEnvSetup.Lat.secondDot = latitudeSecondDot.Text;

                    systemPTZEnvSetup.Long.degrees = longitudeDegrees.Text;
                    systemPTZEnvSetup.Long.minute = longitudeMinute.Text;
                    systemPTZEnvSetup.Long.second = longitudeSecond.Text;
                    systemPTZEnvSetup.Long.secondDot = longitudeSecondDot.Text;


                    systemPTZEnvSetup.WriteIni(ch);



                    sliderPan.IsEnabled = false;
                    sliderMiddlePan.IsEnabled = false;
                    sliderLowPan.IsEnabled = false;

                    sliderZoom.IsEnabled = false;
                    sliderMiddleZoom.IsEnabled = false;
                    sliderLowZoom.IsEnabled = false;

                    sliderFocus.IsEnabled = false;
                    sliderMiddleFocus.IsEnabled = false;
                    sliderLowFocus.IsEnabled = false;

                    azimuth.IsEnabled = false;
                    angleOfElevation.IsEnabled = false;

                    FocusLowSpeed.IsEnabled = false;
                    FocusLowSpeed.IsEnabled = false;

                    maxFocus.IsEnabled = false;
                    minFocus.IsEnabled = false;

                    zoomPanTiltInterLocking.IsEnabled = false;
                    ptLowSpeedZoomValTextBox.IsEnabled = false;
                    ptMidSpeedZoomValTextBox.IsEnabled = false;
                    ptHighSpeedZoomValTextBox.IsEnabled = false;

                    range.IsEnabled = false;
                    area.IsEnabled = false;

                    save.IsEnabled = false;
                    enable.IsEnabled = true;

                    longitudeDegrees.IsEnabled = false;
                    longitudeMinute.IsEnabled = false;
                    longitudeSecond.IsEnabled = false;
                    longitudeSecondDot.IsEnabled = false;
                    
                    latitudeDegrees.IsEnabled = false;
                    latitudeMinute.IsEnabled = false;
                    latitudeSecond.IsEnabled = false;
                    latitudeSecondDot.IsEnabled = false;

                    //handOperatedButton.IsEnabled = false;
                    autoButton.IsEnabled = false;
                }
            }

            catch (System.Exception k) 
            {
                MessageBox.Show(k.Message);  // 예외의 메시지를 출력
            }

            Win32API.PostMessage((IntPtr)Win32API.HWND_BROADCAST, message, (uint)handle, (uint)ch);
        }

        private void auto_Click(object sender, RoutedEventArgs e)
        {

            autoButton.IsEnabled = false;
            //handOperatedButton.IsEnabled = true;
            latitudeDegrees.IsEnabled = false;
            latitudeMinute.IsEnabled = false;
            latitudeSecond.IsEnabled = false;
            latitudeSecondDot.IsEnabled = false;

            longitudeDegrees.IsEnabled = false;
            longitudeMinute.IsEnabled = false;
            longitudeSecond.IsEnabled = false;
            longitudeSecondDot.IsEnabled = false;
           
        }

        private void hand_Click(object sender, RoutedEventArgs e)
        {
            autoButton.IsEnabled = true;
            //handOperatedButton.IsEnabled = false;
            latitudeDegrees.IsEnabled = true;
            latitudeMinute.IsEnabled = true;
            latitudeSecond.IsEnabled = true;
            latitudeSecondDot.IsEnabled = true;

            longitudeDegrees.IsEnabled = true;
            longitudeMinute.IsEnabled = true;
            longitudeSecond.IsEnabled = true;
            longitudeSecondDot.IsEnabled = true;

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

    }
}
