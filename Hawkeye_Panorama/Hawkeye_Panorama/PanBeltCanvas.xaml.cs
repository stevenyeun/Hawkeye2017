using System;
using System.Collections.Generic;
using System.Globalization;
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

namespace Hawkeye_Panorama
{
    /// <summary>
    /// PanBeltCanvas.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class PanBeltCanvas : Canvas
    {
        
        public PanBeltCanvas()
        {
            InitializeComponent();          
        }
        public double m_dPanOffset;


        public void SetPanOffset(double dPanOffset)
        {
            m_dPanOffset = dPanOffset;

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
        double PanDecToOffsetCalc(double dDec, double dOffsetDec)
        {
            double dCalcDec = dDec + dOffsetDec;

            if (dCalcDec < 0)//음수일경우
            {
                if (dOffsetDec < 0)
                {
                    dCalcDec = 360 + dCalcDec;
                }
                else if (dOffsetDec > 0)
                {
                    dCalcDec = 360 - dCalcDec;
                }

            }
            else if (dCalcDec > 360)//양수
            {
                dCalcDec = dCalcDec - 360;
            }

            return dCalcDec;

        }
        protected override void OnRender(DrawingContext dc)
        {
            var myPen = new Pen
            {
                Thickness = 0.4,
                Brush = Brushes.Gray,
            };
            myPen.Freeze();

            //this.Width : 360 : x : 30(도)
            double dCanvasWidth = this.Width;
            int nFrameDegWidth = 24;
            int nPixelOf30Deg = (int)dCanvasWidth * nFrameDegWidth / 360;
            int nNumOfLine = 360 / nFrameDegWidth;
            for(int i=0; i<= nNumOfLine; i++)
            {
                Point start = new Point(nPixelOf30Deg * i, 0);
                Point end = new Point(nPixelOf30Deg * i, this.Height);

                dc.DrawLine(myPen, start, end);

#if false
                string strPan = String.Format("{0:000}",  nFrameDegWidth * i);
#else
                double dOffsetedPan = PanDecToOffsetCalc(nFrameDegWidth * i, m_dPanOffset);
                string strPan = String.Format("{0:000}({1:000})", dOffsetedPan, nFrameDegWidth * i);
#endif
                //
                FormattedText formattedText = new FormattedText(strPan, CultureInfo.GetCultureInfo("en-us"),
                                                FlowDirection.LeftToRight,
                                                new Typeface(new FontFamily("Arial").ToString()),
                                                10, Brushes.WhiteSmoke);

                dc.DrawText(formattedText, new Point(nPixelOf30Deg * i-20, this.Height / 5));

            }


         



        }
    }
}
