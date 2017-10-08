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
//http://stackoverflow.com/questions/2168370/how-to-render-bitmap-into-canvas-in-wpf
namespace Hawkeye_Panorama
{
    /// <summary>
    /// PanoramaCanvas.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class PanoramaCanvas : Canvas
    {
        private const int srcFrameWidth = 1920;//한 프레임당 사이즈
        private const int srcFrameHeight = 1080;
        private const int destFrameWidth = srcFrameWidth / 16;//한 프레임당 사이즈
        private const int destFrameHeight = srcFrameHeight / 16;
        private const int nNumOfFrame = 15;

        private double mouseLbuttonX;
        private double mouseLbuttonY;

        private int m_nCh;
        public PanoramaSetup panoSetupWindow = new PanoramaSetup();
        public void SetChInfo(int nCh, PanoramaInfo info, MainWindow mainWndPrt)
        {
            m_nCh = nCh;
            this.mainWndPtr = mainWndPrt;
            panoSetupWindow.SetChinfo(nCh, info, mainWndPtr);
      
            panoSetupWindow.Topmost = true;           
        }

        private MainWindow mainWndPtr;
    
        public PanoramaCanvas()
        {
            InitializeComponent();

            this.Width = destFrameWidth * nNumOfFrame;
            this.Height = destFrameHeight;

            this.MouseLeave += (sender, e) =>
            {
                System.Console.WriteLine("MouseLeave");

                this.MouseMovePointHorizon.X1 = 0;
                this.MouseMovePointHorizon.Y1 = 0;
                this.MouseMovePointHorizon.X2 = 0;
                this.MouseMovePointHorizon.Y2 = 0;

                this.MouseMovePointVertical.X1 = 0;
                this.MouseMovePointVertical.Y1 = 0;
                this.MouseMovePointVertical.X2 = 0;
                this.MouseMovePointVertical.Y2 = 0;
            };
            this.MouseEnter += (sender, e) =>
            {
                System.Console.WriteLine("MouseEnter");
            };


            this.MouseLeftButtonUp += (sender, e) =>
            {
                System.Console.WriteLine("MouseLeftButtonUp");
            };

            this.MouseRightButtonUp += (sender, e) =>
            {
                System.Console.WriteLine("MouseRightButtonUp");
                double x = e.GetPosition(this).X;
                double y = e.GetPosition(this).Y;
                DrawMouseClickPoint(x, y);
            };

            this.MouseRightButtonDown += (sender, e) =>
            {

            };
            this.MouseLeftButtonDown += (sender, e) =>
             {
                 System.Console.WriteLine("MouseLeftButtonDown");
                 double x = e.GetPosition(this).X;
                 double y = e.GetPosition(this).Y;

                 if (e.ClickCount == 2)
                 {
                     MessageBox.Show("이동 시작");
                     //DrawArrow(x, y);
                     DrawMouseClickPoint(x, y);

                     mainWndPtr.MovePanTilt(m_nCh, (int)this.mouseLbuttonX, (int)this.mouseLbuttonY);
                 }

                 DrawMouseClickPoint(x, y);

             };
            this.MouseMove += (sender, e) =>
            {
                System.Console.WriteLine("MouseMove");

                double x = e.GetPosition(this).X;
                double y = e.GetPosition(this).Y;

                DrawMouseMovePoint(x, y);
            };
        }
        private string[] imagePathName = new string[] {
            "", "", "", "", "", "",
            "", "", "", "", "", "",
        "", "", "", "", "", "" };



        public void SetImagePathName(int nSeq, string imagePathName)
        {
            this.imagePathName[nSeq] = imagePathName;

            if (!this.Dispatcher.CheckAccess())
            {
                this.Dispatcher.Invoke(
                  System.Windows.Threading.DispatcherPriority.Normal,
                  new Action(
                    delegate ()
                    {
                        this.InvalidateVisual();
                    }
                ));
            }
            else
            {
                this.InvalidateVisual();
            }
            
        }
        public void DrawMouseMovePoint(double x, double y)
        {
            const int size = 30;
            this.MouseMovePointHorizon.X1 = x - size;
            this.MouseMovePointHorizon.Y1 = y;
            this.MouseMovePointHorizon.X2 = x + size;
            this.MouseMovePointHorizon.Y2 = y;

            this.MouseMovePointVertical.X1 = x;
            this.MouseMovePointVertical.Y1 = y - size;
            this.MouseMovePointVertical.X2 = x;
            this.MouseMovePointVertical.Y2 = y + size;

        }
        public void DrawMouseClickPoint(double x, double y)
        {
            const int size = 30;

            this.MouseClickPointHorizon.X1 = x - size;
            this.MouseClickPointHorizon.Y1 = y;
            this.MouseClickPointHorizon.X2 = x + size;
            this.MouseClickPointHorizon.Y2 = y;

            this.MouseClickPointVertical.X1 = x;
            this.MouseClickPointVertical.Y1 = y - size;
            this.MouseClickPointVertical.X2 = x;
            this.MouseClickPointVertical.Y2 = y + size;

            this.mouseLbuttonX = x;
            this.mouseLbuttonY = y;
        }
        public void DrawPanTiltDirectionPoint(double x, double y)
        {
            const int size = 30;


          


            if (!this.Dispatcher.CheckAccess())
            {
                this.Dispatcher.Invoke(
                  System.Windows.Threading.DispatcherPriority.Normal,
                  new Action(
                    delegate ()
                    {
                        Canvas.SetTop(CameraDirectionPoint, y - size / 2);
                        Canvas.SetLeft(CameraDirectionPoint, x - size / 2);

                        //this.InvalidateVisual();
                    }
                ));
            }
            else
            {
                Canvas.SetTop(CameraDirectionPoint, y - size / 2);
                Canvas.SetLeft(CameraDirectionPoint, x - size / 2);
                // this.InvalidateVisual();
            }

            //CameraDirectionPoint.Width = size;
            //CameraDirectionPoint.Height = size;
           

            /*
            this.CameraDirectionPointHorizon.X1 = x - size;
            this.CameraDirectionPointHorizon.Y1 = y;
            this.CameraDirectionPointHorizon.X2 = x + size;
            this.CameraDirectionPointHorizon.Y2 = y;

            this.CameraDirectionPointVertical.X1 = x;
            this.CameraDirectionPointVertical.Y1 = y - size;
            this.CameraDirectionPointVertical.X2 = x;
            this.CameraDirectionPointVertical.Y2 = y + size;
            */

        }
        protected override void OnRender(DrawingContext dc)
        {
            System.Console.WriteLine("OnRender");

            //Background = Brush.red;
            for (int i = 0; i < nNumOfFrame; i++)
            {
                if (imagePathName[i] != "")
                {
                    try
                    {
                        BitmapImage bmp = new BitmapImage(new Uri(imagePathName[i]));
                        if (bmp.Width == srcFrameWidth && bmp.Height == srcFrameHeight)
                        {

                            dc.DrawImage(bmp, new Rect(destFrameWidth * i, 0, destFrameWidth, destFrameHeight));
                        }
                    }
                    catch(Exception e)
                    {
                        dc.DrawRectangle(Brushes.Gray, null, new Rect(destFrameWidth * i, 0, destFrameWidth, destFrameHeight));
                    }                  
                }
                else
                {
                    dc.DrawRectangle(Brushes.Gray, null, new Rect(destFrameWidth * i, 0, destFrameWidth, destFrameHeight));

                }
            }
        }


        private void SelectedPointMoveMenu_Click(object sender, RoutedEventArgs e)
        {
            mainWndPtr.MovePanTilt(m_nCh, (int)this.mouseLbuttonX, (int)this.mouseLbuttonY);
        }

        private void PanoramaSetupMenu_Click(object sender, RoutedEventArgs e)
        {
            panoSetupWindow.Topmost = true;
            panoSetupWindow.Activate();
            panoSetupWindow.Show();
        }



        /*
        string imgName = "20170408141214.jpg";
        string baseDir = AppDomain.CurrentDomain.BaseDirectory;
        BitmapImage bmp = new BitmapImage(new Uri(baseDir + imgName));
        int width = bmp.PixelWidth / 5;
        int height = bmp.PixelHeight / 5;

        //BitmapImage img = new BitmapImage(new Uri("c:\\demo.jpg"));
        dc.DrawImage(bmp, new Rect(0, 0, width, height));

        dc.DrawImage(bmp, new Rect(width, 0, width, height));
        */
    }
}

