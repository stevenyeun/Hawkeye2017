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
using System.Windows.Shapes;

namespace Hawkeye_Panorama
{
    /// <summary>
    /// PanoramaSetup.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class PanoramaSetup : Window
    {
        private int m_nCh;
        private MainWindow mainWndPtr;
     

        public PanoramaSetup()
        {
            InitializeComponent();
        }

        public void SetChinfo(int nCh, PanoramaInfo info, MainWindow mainWndPtr)
        {
            m_nCh = nCh;
            this.mainWndPtr = mainWndPtr;

            ChannelStatusLabel.Content = String.Format("채널 {0:d2}", nCh);

            string strFovHeight = String.Format("{0:00.0}", info.dPanoImgFovH);

            this.PanoImageFovHeightTextBox.Text = strFovHeight;
        
            string strTilt = String.Format("{0:+00.0000;-00.0000;+00.0000}", info.dPanoImgTiltPivotDeg);
            this.PanoImageTiltDegTextBox.Text = strTilt;

            this.ZoomAbsTextBox.Text = info.nPanoCaptureZoomAbs.ToString();
        }
      
        public void SetPanoramaStatus(string strStatus)
        {
            //string strTilt = String.Format("{0:+00.####;-00.####;+00.0000 }", dTilt);
            //PanoImageTiltDegTextBox.Text = strTilt;


            if (!this.PanoramaStatusLabel.Dispatcher.CheckAccess())
            {
                this.PanoramaStatusLabel.Dispatcher.Invoke(
                  System.Windows.Threading.DispatcherPriority.Normal,
                  new Action(
                    delegate ()
                    {
                        this.PanoramaStatusLabel.Content = strStatus;
                    }
                ));
            }
            else
            {
                this.PanoramaStatusLabel.Content = strStatus;
            }


            
        }
        public void SetTilt(double dTilt)
        {
            if( AutoInputTiltDegChkBox.IsChecked == false)
            {
                return;
            }


            string strTilt = String.Format("{0:+00.####;-00.####;+00.0000 }", dTilt);
            //PanoImageTiltDegTextBox.Text = strTilt;


            if (!this.PanoImageTiltDegTextBox.Dispatcher.CheckAccess())
            {
                this.PanoImageTiltDegTextBox.Dispatcher.Invoke(
                  System.Windows.Threading.DispatcherPriority.Normal,
                  new Action(
                    delegate ()
                    {
                        this.PanoImageTiltDegTextBox.Text = strTilt;
                    }
                ));
            }
            else
            {
                this.PanoImageTiltDegTextBox.Text = strTilt;
            }
        }

        private void SaveBtn_Click(object sender, RoutedEventArgs e)
        {
            PanoramaInfoIni panoInfoIni = new PanoramaInfoIni("PanoramaInfo");
            panoInfoIni.ReadIni(m_nCh);

            try
            {
                panoInfoIni.dPanoImgFovH = double.Parse(this.PanoImageFovHeightTextBox.Text);
                panoInfoIni.nPanoCaptureZoomAbs = int.Parse(this.ZoomAbsTextBox.Text);
                panoInfoIni.dPanoImgTiltPivotDeg = double.Parse(PanoImageTiltDegTextBox.Text);
            }
            catch (Exception ee)
            {
                MessageBox.Show( String.Format("채널 {0} 잘못된 값이 입력 되었습니다.", m_nCh) );
            }

            panoInfoIni.WriteIni(m_nCh);
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;
            this.Hide();            
        }

        private void PanoramaCaptureStart_Click(object sender, RoutedEventArgs e)
        {
            PanoramaInfo info = new PanoramaInfo();

            try
            {
                info.dPanoImgFovH = double.Parse(this.PanoImageFovHeightTextBox.Text);
                info.nPanoCaptureZoomAbs = int.Parse(this.ZoomAbsTextBox.Text);
                info.dPanoImgTiltPivotDeg = double.Parse(PanoImageTiltDegTextBox.Text);
            }
            catch(Exception eee)
            {
                MessageBox.Show("입력된 값이 잘못되었습니다.");
                return;
            }

            mainWndPtr.PanoramaCaptureStart(m_nCh, info);
        }

        private void PanoramaCaptureStop_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
