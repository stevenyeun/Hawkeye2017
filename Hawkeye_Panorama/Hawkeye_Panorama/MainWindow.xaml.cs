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


using ReadWriteIni;
using Hawkeye_PTZController;
using System.Net;
using AuthorityComm;
using System.Threading;
using System.Windows.Threading;
using System.Diagnostics;
using System.IO;
using System.Windows.Interop;
using Hawkeye_LIB;
using Ownskit.Applications.DrawAnywhere.Utils;

namespace Hawkeye_Panorama
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    /// 
    public class PanoramaInfo
    {
        public PanoramaInfo()
        {
            nPanoImgFovW = 360;
            dPanoImgFovH = 11.5;

            //dPanoImgTopDeg	= +5.75;
            //dPanoImgBottomDeg = -5.75;
            dPanoImgTiltPivotDeg = 0.0;

            dPanoImgStartPan = 0.0;

            nPanoCaptureZoomAbs = 0;
        }

        public int nPanoImgFovW;//파노라마 가로 화각	
        public double dPanoImgFovH;//파노라마 세로 화각		

        public double dPanoImgTiltPivotDeg;//파노라마 촬영시 세로 중심각
                                           //double	dPanoImgTopDeg;//파노라마 영상의 상측 각도
                                           //double	dPanoImgBottomDeg;//파노라마 영상의 하측 각도
                                           //  [5/9/2014 Yeun]
        public double dPanoImgStartPan;//이미지의 x=0 일때 의 팬값 리미트가 있는 팬틸트는 x=0을 0도로 촬영 못함

        public int nPanoCaptureZoomAbs;
    }
    public class PanoramaMoveInfo
    {
        public PanoramaMoveInfo()
        {
            dPan = 0.0;
            dTilt = 0.0;
            nZoomAbs = 0;
        }
        public double dPan;
        public double dTilt;
        public int nZoomAbs;
    }

    public partial class MainWindow : Window
    {
        static public readonly int MAX_CHANNEL = 5;
        private WindowInfoIni winInfoIni = new WindowInfoIni("PanoramaWindowInfo");
        private PanoramaInfoIni panoInfoIni = new PanoramaInfoIni("PanoramaInfo");
        public PTZEnvSetup systemPTZEnvSetup = new PTZEnvSetup("PTZEnvSetup");
        private PanoramaInfo[] arrPanoInfo = new PanoramaInfo[MAX_CHANNEL];
        private bool[] m_bPresetStart = { false, false, false, false, false };
        private bool[] m_bPresetThreadStop = { false, false, false, false, false };
        private UDPSocketForRelayServerComm udpSock = new UDPSocketForRelayServerComm(30005);
        private double m_panoCanvasWidth;
        private double m_panoCanvasHeight;

        public MainWindow()
        {
            InitializeComponent();

            winInfoIni.ReadIni();

            PanoramaCanvas[] arrCanvas = { panoramaCanvas1, panoramaCanvas2, panoramaCanvas3, panoramaCanvas4, panoramaCanvas5 };
            PanBeltCanvas[] arrPanBeltCanvas = { panBeltCanvas1, panBeltCanvas2, panBeltCanvas3, panBeltCanvas4, panBeltCanvas5 };

            for (int i = 0; i < MAX_CHANNEL; i++)
            {
                panoInfoIni.ReadIni(i + 1);
                
                // string imgName = "20170408141214.jpg";
                //string baseDir = AppDomain.CurrentDomain.BaseDirectory;

                arrPanoInfo[i] = new PanoramaInfo();
                arrPanoInfo[i].nPanoImgFovW = panoInfoIni.nPanoImgFovW;
                arrPanoInfo[i].dPanoImgFovH = panoInfoIni.dPanoImgFovH;
                arrPanoInfo[i].dPanoImgTiltPivotDeg = panoInfoIni.dPanoImgTiltPivotDeg;
                arrPanoInfo[i].nPanoCaptureZoomAbs = panoInfoIni.nPanoCaptureZoomAbs;
                for (int k = 0; k < 15; k++)
                {
                    //panoInfoIni.arrPanoImagePathName[k] = baseDir + imgName;
                    arrCanvas[i].SetImagePathName(k, panoInfoIni.arrPanoImagePathName[k]);

                }
                //////////////////////////////////
                //팬 벨트 보정값
                systemPTZEnvSetup.ReadIni(i + 1);
                double dPanOffset = double.Parse(systemPTZEnvSetup.azimuth);
                arrPanBeltCanvas[i].SetPanOffset(dPanOffset);

                SetAreaName(i + 1, systemPTZEnvSetup.area);

                //panoInfoIni.WriteIni(i+1);
            }

            udpSock.CreateUDPSocket();
            for (int i = 0; i < MAX_CHANNEL; i++)
            {
                CreatePacketParsingThread(i + 1);
            }

            Minimize();

            



            m_panoCanvasWidth = panoramaCanvas1.Width;
            m_panoCanvasHeight= panoramaCanvas1.Height;



            panoramaCanvas1.SetChInfo(1, arrPanoInfo[0], this);
            panoramaCanvas1.MouseLeftButtonUp += (sender, e) =>
            {
                System.Console.WriteLine("MainWindow MouseLeftButtonUp");
            };

         
            panoramaCanvas2.SetChInfo(2, arrPanoInfo[1], this);
            panoramaCanvas2.MouseLeftButtonUp += (sender, e) =>
            {
                System.Console.WriteLine("MainWindow MouseLeftButtonUp");
            };

          
            panoramaCanvas3.SetChInfo(3, arrPanoInfo[2], this);
            panoramaCanvas3.MouseLeftButtonUp += (sender, e) =>
            {
                System.Console.WriteLine("MainWindow MouseLeftButtonUp");
            };

           
            panoramaCanvas4.SetChInfo(4, arrPanoInfo[3], this);
            panoramaCanvas4.MouseLeftButtonUp += (sender, e) =>
            {
                System.Console.WriteLine("MainWindow MouseLeftButtonUp");
            };

          
            panoramaCanvas5.SetChInfo(5, arrPanoInfo[4], this);
            panoramaCanvas5.MouseLeftButtonUp += (sender, e) =>
            {
                System.Console.WriteLine("MainWindow MouseLeftButtonUp");
            };



            //BitmapImage bmp = new BitmapImage( new Uri("20170408141214.jpg") );
            //WriteableBitmap 
            //Image img;
            //Bitmap 은 Abstract Image 클래스 에서 상속받습니다.

            /*
            string imgName = "20170408141214.jpg";
            string baseDir = AppDomain.CurrentDomain.BaseDirectory;
            Image img = new Image();
            img.ur
            BitmapSource bmpSrc = new BitmapSource();

            WriteableBitmap maskBmp = new WriteableBitmap(bmpSrc);
            */



            // panoramaCanvas.ren

            //DrawingImage MyDrawingImage = new DrawingImage(MyDrawing);

        }


        private uint message;
        private IntPtr handle;
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
                //string ch = msg.lParam.ToString();
                int nCh = (int)msg.lParam;

                systemPTZEnvSetup.ReadIni(nCh);

                PanBeltCanvas[] arrCanvas = { panBeltCanvas1, panBeltCanvas2, panBeltCanvas3, panBeltCanvas4, panBeltCanvas5 };

                double dPanOffset = double.Parse(systemPTZEnvSetup.azimuth);
                arrCanvas[nCh - 1].SetPanOffset(dPanOffset);
                SetAreaName(nCh, systemPTZEnvSetup.area);

                //MessageBox.Show("MFC Message : " + msg.lParam.ToString());
            }
        }
        private void MaximizeButton_Click(object sender, RoutedEventArgs e)
        {
            Maximize();
        }

        private void Maximize()
        {
            MaximizeButton.Visibility = Visibility.Hidden;

            WindowStyle = WindowStyle.ToolWindow;




            Height = winInfoIni.maximizeHeight;//maximizeSize.Height;
            Width = winInfoIni.maximizeWidth;//maximizeSize.Width;

            Top = System.Windows.SystemParameters.PrimaryScreenHeight / 2 - Height / 2;
            Left = System.Windows.SystemParameters.PrimaryScreenWidth / 2 - Width / 2;


            MaximizeButton.Visibility = Visibility.Hidden;

            panoramaLabel1.Visibility = Visibility.Visible;
            panoramaLabel2.Visibility = Visibility.Visible;
            panoramaLabel3.Visibility = Visibility.Visible;
            panoramaLabel4.Visibility = Visibility.Visible;
            panoramaLabel5.Visibility = Visibility.Visible;

            panoramaCanvas1.Visibility = Visibility.Visible;
            panoramaCanvas2.Visibility = Visibility.Visible;
            panoramaCanvas3.Visibility = Visibility.Visible;
            panoramaCanvas4.Visibility = Visibility.Visible;
            panoramaCanvas5.Visibility = Visibility.Visible;

            panBeltCanvas1.Visibility = Visibility.Visible;
            panBeltCanvas2.Visibility = Visibility.Visible;
            panBeltCanvas3.Visibility = Visibility.Visible;
            panBeltCanvas4.Visibility = Visibility.Visible;
            panBeltCanvas5.Visibility = Visibility.Visible;



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

            panoramaLabel1.Visibility = Visibility.Hidden;
            panoramaLabel2.Visibility = Visibility.Hidden;
            panoramaLabel3.Visibility = Visibility.Hidden;
            panoramaLabel4.Visibility = Visibility.Hidden;
            panoramaLabel5.Visibility = Visibility.Hidden;


            panoramaCanvas1.Visibility = Visibility.Hidden;
            panoramaCanvas2.Visibility = Visibility.Hidden;
            panoramaCanvas3.Visibility = Visibility.Hidden;
            panoramaCanvas4.Visibility = Visibility.Hidden;
            panoramaCanvas5.Visibility = Visibility.Hidden;

            panBeltCanvas1.Visibility = Visibility.Hidden;
            panBeltCanvas2.Visibility = Visibility.Hidden;
            panBeltCanvas3.Visibility = Visibility.Hidden;
            panBeltCanvas4.Visibility = Visibility.Hidden;
            panBeltCanvas5.Visibility = Visibility.Hidden;


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
        public void SetAreaName(int ch, string name)
        {
            Label[] arrLabel = { panoramaLabel1, panoramaLabel2, panoramaLabel3, panoramaLabel4, panoramaLabel5 };
            Label label = arrLabel[ch - 1];

            if (!label.Dispatcher.CheckAccess())
            {
                label.Dispatcher.Invoke(
                  System.Windows.Threading.DispatcherPriority.Normal,
                  new Action(
                    delegate ()
                    {
                        label.Content = "채널" + ch.ToString() + " " + name;
                    }
                ));
            }
            else
            {
                label.Content = "채널" + ch.ToString() + " " + name;
            }
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


        //패킷 파싱 스레드 종료 및 상태
        ////////////////////////////////////////////////////////////////////////////////////////
        private bool[] m_bDestroyPacketParsingThread = { false, false, false, false, false };
        private void DestroyPacketParsingThread(int nCh)
        {
            m_bDestroyPacketParsingThread[nCh - 1] = true;
       
        }//스레드 종료 시작
        private bool IsDestroyPacketParsingThread(int nCh)
        {
            return m_bDestroyPacketParsingThread[nCh - 1];
        }
        //
        //패킷 파싱 스레드 동작 상태
        private bool[] m_bRunPacketParsingThread = { false, false, false, false, false };
        private void SetPacketParsingThread(int nCh, bool bRun){
            m_bRunPacketParsingThread[nCh-1] = bRun;
        }
        private bool IsRunPacketParsingThread(int nCh)
        {
            return m_bRunPacketParsingThread[nCh-1];
        }
        //
        private void CreatePacketParsingThread(int nCh)
        {
            int nCurThreadCh = nCh;
            m_bDestroyPacketParsingThread[nCh - 1] = false;
            PanoramaCanvas[] arrCanvas = { panoramaCanvas1, panoramaCanvas2, panoramaCanvas3, panoramaCanvas4, panoramaCanvas5 };
            Task.Run(() =>
            {
                SetPacketParsingThread(nCurThreadCh, true);//상태 체크
                while (true)
                {
                    //if (udpSock.queuePacketFromRelayServer.Count > 0)
                    if (udpSock.GetNumberOfPacket(nCurThreadCh) > 0)
                    {
                        //IPEndPoint ep = udpSock.queueIPEndPointFromRelayServer.Dequeue();

                        Console.WriteLine("Ch={0} PopPacket Packet", nCurThreadCh);
                        byte[] packet = udpSock.PopPacket(nCurThreadCh);
                        if (packet == null)
                            continue;

                        string str = Encoding.UTF8.GetString(packet);
                        //Console.WriteLine("Port={0} Received={1}", ep.Port, str.Length);



                        AUTHORITY_PACKET AuthPacket;
                        //AuthPacket.GetType()
                        //typeof(AUTHORITY_PACKET)
                        AuthPacket = (AUTHORITY_PACKET)AuthorityCommUtil.ByteToStructure(packet, typeof(AUTHORITY_PACKET));
                        string name = AuthorityCommUtil.ByteToString(AuthPacket.srcName.name);
                        string data = AuthorityCommUtil.ByteToString(AuthPacket.authorityData.data);
                        //System.Console.WriteLine(data.Replace('\0', ' '));
                        //System.Console.WriteLine(name.Replace('\0', ' '));

                        if (AuthPacket.byCmdGroup == CommandPTZReqResp.CMDGROUP_PTZREQ)
                        {
                            if (AuthPacket.byCmdType == CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_RESP)
                            {
                                this.Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
                                {
                                    int index1 = data.IndexOf(';');
                                    string strPan = data.Substring(0, index1);
                                    string strTilt = data.Substring(index1 + 1, data.Length - (index1 + 1));
                                    double pan = double.Parse(strPan);
                                    double tilt = double.Parse(strTilt);

                                    int x = 0;
                                    int y = 0;

                                    PanTiltPosToImgAbsPos(pan, tilt, ref x, ref y, arrPanoInfo[nCh - 1]);
                                    arrCanvas[nCurThreadCh - 1].DrawPanTiltDirectionPoint(x, y);
                                    arrCanvas[nCurThreadCh - 1].panoSetupWindow.SetTilt(tilt);

                                    //int index2 = data.IndexOf('\0');
                                    //PanLabel.Content = "방위각 " + data.Substring(0, index1);
                                    //TiltLabel.Content = "고저각 " + data.Substring(index1 + 1, data.Length - (index1 + 1));
                                }));
                            }
                            else if (AuthPacket.byCmdType == CommandPTZReqResp.CMDTYPE_PTZREQ_MAINBOARD_STATUS_RESP)
                            {
                                System.Console.WriteLine(data);
                            }
                        }
                    }
                    if (IsDestroyPacketParsingThread(nCurThreadCh) == true)//스레드 종료 
                    {
                        break;
                    }


                    Thread.Sleep(1);
                }
                SetPacketParsingThread(nCurThreadCh, false);//상태 체크
            });
        }
        ////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////


        /*
    private void CreatePacketParsingThread()
    {
        //Parse
        Task.Run(() =>
        {
            while (true)
            {
                //if (udpSock.queuePacketFromRelayServer.Count > 0)
                if (udpSock.GetNumberOfPacket() > 0)
                {
                    IPEndPoint ep = udpSock.queueIPEndPointFromRelayServer.Dequeue();

                    Console.WriteLine("Parse Packet");
                    byte[] packet = udpSock.PopPacket();
                    if (packet == null)
                        continue;

                    string str = Encoding.UTF8.GetString(packet);
                    Console.WriteLine("Port={0} Received={1}", ep.Port, str.Length);



                    AUTHORITY_PACKET AuthPacket;
                    //AuthPacket.GetType()
                    //typeof(AUTHORITY_PACKET)
                    AuthPacket = (AUTHORITY_PACKET)AuthorityCommUtil.ByteToStructure(packet, typeof(AUTHORITY_PACKET));
                    string name = AuthorityCommUtil.ByteToString(AuthPacket.srcName.name);
                    string data = AuthorityCommUtil.ByteToString(AuthPacket.authorityData.data);
                    //System.Console.WriteLine(data.Replace('\0', ' '));
                    //System.Console.WriteLine(name.Replace('\0', ' '));

                    if (AuthPacket.byCmdGroup == CommandPTZReqResp.CMDGROUP_PTZREQ)
                    {
                        if (AuthPacket.byCmdType == CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_RESP)
                        {
                            this.Dispatcher.Invoke(DispatcherPriority.Normal, (Action)(() =>
                            {
                                int index1 = data.IndexOf(';');
                                //int index2 = data.IndexOf('\0');
                                //PanLabel.Content = "방위각 " + data.Substring(0, index1);
                                //TiltLabel.Content = "고저각 " + data.Substring(index1 + 1, data.Length - (index1 + 1));
                            }));
                        }
                        else if (AuthPacket.byCmdType == CommandPTZReqResp.CMDTYPE_PTZREQ_MAINBOARD_STATUS_RESP)
                        {
                            System.Console.WriteLine(data);
                        }
                    }


                }

                Thread.Sleep(1);
            }
        });
    }
    */
        private AUTHORITY_PACKET RecvAuthorityCmd(int nCh)//큐에 쌓인 것을 읽어온다.
        {
            const int nTimeout = 5;
            int nCount = 0;
            while (true)
            {
                //if (udpSock.queuePacketFromRelayServer.Count > 0)
                if (udpSock.GetNumberOfPacket(nCh) > 0)
                {

                    //IPEndPoint ep = udpSock.queueIPEndPointFromRelayServer.Dequeue();

                    Console.WriteLine("Parse Packet");
                    byte[] packet = udpSock.PopPacket(nCh);
                    string str = Encoding.UTF8.GetString(packet);
                    //Console.WriteLine("Port={0} Received={1}", ep.Port, str.Length);

                    AUTHORITY_PACKET AuthPacket;
                    //AuthPacket.GetType()
                    //typeof(AUTHORITY_PACKET)
                    AuthPacket = (AUTHORITY_PACKET)AuthorityCommUtil.ByteToStructure(packet, typeof(AUTHORITY_PACKET));

                    return AuthPacket;
                }

                Thread.Sleep(100);
                nCount++;
                if (nCount >= nTimeout)
                    return new AUTHORITY_PACKET();
            }
        }

        private string GetPanMoveStatus(int nCh)
        {
            #region
            string strStatus = "";
            while (true)//다른 메세지도 같이 오기 때문에 계속 읽어오면서 필터링
            {
                AUTHORITY_PACKET AuthPacket = RecvAuthorityCmd(nCh);

                if (AuthPacket.bySTX == 0 || AuthPacket.byETX == 0)
                    break;
                if (AuthPacket.byCmdGroup == CommandPTZReqResp.CMDGROUP_PTZREQ)
                {
                    if (AuthPacket.byCmdType == CommandPTZReqResp.CMDTYPE_PTZREQ_PAN_MOVESTATUS_RESP)
                    {
                        string receivedName = AuthorityCommUtil.ByteToString(AuthPacket.srcName.name);
                        string receiveddata = AuthorityCommUtil.ByteToString(AuthPacket.authorityData.data);

                        strStatus = receiveddata;
                        break;
                    }
                }
            }
            return strStatus;
            #endregion
        }
        private string GetPanTIltDeg(int nCh)
        {
            #region
            string strStatus = "";
            while (true)//다른 메세지도 같이 오기 때문에 계속 읽어오면서 필터링
            {
                AUTHORITY_PACKET AuthPacket = RecvAuthorityCmd(nCh);

                if (AuthPacket.bySTX == 0 || AuthPacket.byETX == 0)
                    break;
                if (AuthPacket.byCmdGroup == CommandPTZReqResp.CMDGROUP_PTZREQ)
                {
                    if (AuthPacket.byCmdType == CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_RESP)
                    {
                        string receivedName = AuthorityCommUtil.ByteToString(AuthPacket.srcName.name);
                        string receiveddata = AuthorityCommUtil.ByteToString(AuthPacket.authorityData.data);

                        strStatus = receiveddata;
                        break;
                    }
                }
            }
            return strStatus;
            #endregion
        }
        void PanoImgInfoToTopBottomDeg(PanoramaInfo panoimginfo, ref double dTopDeg, ref double dBottomDeg)
        {
            dTopDeg = dBottomDeg = panoimginfo.dPanoImgFovH / 2;
            dBottomDeg *= -1;

            dTopDeg += panoimginfo.dPanoImgTiltPivotDeg;
            dBottomDeg += panoimginfo.dPanoImgTiltPivotDeg;

        }
        private void ImgPosToPanTiltPos(int x, int y, ref double dPan, ref double dTilt, PanoramaInfo panoimginfo)
        {
#if true
            //이미지총가로픽셀 : 이미지Pan의전체각도(360˚) = 클릭한X좌표(iX)	: ?
            dPan = (panoimginfo.nPanoImgFovW * x) / (double)m_panoCanvasWidth;

            //세로이미지의전체각도 구하기
            double dPanoImgFovH = panoimginfo.dPanoImgFovH;// panoimginfo.dPanoImgTopDeg - panoimginfo.dPanoImgBottomDeg;

            double dPanoImgTopDeg = 0.0, dPanoImgBottomDeg = 0.0;
            PanoImgInfoToTopBottomDeg(panoimginfo, ref dPanoImgTopDeg, ref dPanoImgBottomDeg);

            //수평각도구하기
            double dTiltHorizon = dPanoImgFovH + dPanoImgBottomDeg;

            //이미지총세로픽셀 : 이미지의Tilt의각도 = 클릭한Y좌표(iY)	: ?
            dTilt = (dPanoImgFovH * y) / (double)m_panoCanvasHeight;

            //틸트 총각도는 360도 이나 촬영된 이미지는 360도 아니다.
            //틸트값 보정
            dTilt -= dTiltHorizon;
            dTilt *= -1;
            if (dTilt < dTiltHorizon)// +각도
            {
                //TRACE("+ \r\n");
            }
            else if (dTilt > dTiltHorizon)// -각도
            {
                //TRACE("- \r\n");
            }
            else
            {   //TRACE("0점 \r\n");
            }

            //  [5/9/2014 Yeun]
            dPan += panoimginfo.dPanoImgStartPan;
#endif
        }
        private void PanTiltPosToImgAbsPos(double dPan, double dTilt, ref int X, ref int Y, PanoramaInfo panoimginfo)//팬틸트 값 -> 이미지 절대 좌표
        {
            //이미지Pan의 총 각도(360˚) : 이미지총가로픽셀 = dPan : ?
            X = (int)(m_panoCanvasWidth * dPan / panoimginfo.nPanoImgFovW);

            double dPanoImgTopDeg = 0.0, dPanoImgBottomDeg = 0.0;
            PanoImgInfoToTopBottomDeg(panoimginfo, ref dPanoImgTopDeg, ref dPanoImgBottomDeg);

            //세로이미지의전체각도 구하기
            double dPanoImgFovH = panoimginfo.dPanoImgFovH;

            //이미지Tilt의 총 각도 : 이미지총세로픽셀 = dTilt : ?	 
            Y = (int)(m_panoCanvasHeight * dTilt / dPanoImgFovH);

            //수평각도구하기
            double dTiltHorizon = dPanoImgFovH + dPanoImgBottomDeg;

            //이미지Tilt의 총 각도 : 이미지총세로픽셀 = dTiltHorizon : ?	 
            int iHorizonPxY = (int)(m_panoCanvasHeight * dTiltHorizon / dPanoImgFovH);

            //보정
            Y = iHorizonPxY - Y;
        }
        private bool CheckPresetRunStatus(int nCh)
        {
            if (m_bPresetStart[nCh - 1] == true)
            {
                string temp = String.Format("채널 {0} 이미 프리셋 진행 중입니다.", nCh);
                MessageBox.Show(temp);
                return true;//이동중
            }
            return false;
        }
        private void SetPresetRunStatus(int nCh, bool bRun)
        {
            m_bPresetStart[nCh - 1] = bRun;
        }

        public void MovePanTilt(int nCh, int x, int y)//클릭 위치 이동
        {
            //이동
            if (CheckPresetRunStatus(nCh) == true)//이미 진행 중
                return;
       
            string status = String.Format("채널 {0} 프리셋 시작", nCh);
            //this.PresetStatusLabel.Content = status;
            //this.m_bPresetStart[nCh - 1] = true;
            SetPresetRunStatus(nCh, true);

            //선택이동 스레드
            double panAbs = 180;
            double tiltAbs = 0;
            int zoom = 50000;
            int focus = 50000;

            ImgPosToPanTiltPos(x, y, ref panAbs, ref tiltAbs, arrPanoInfo[nCh-1]);

            DestroyPacketParsingThread(nCh);

            PanoramaCanvas[] arrCanvas = { panoramaCanvas1, panoramaCanvas2, panoramaCanvas3, panoramaCanvas4, panoramaCanvas5 };
            #region
            Task.Run(() =>
            {
                const int nTimeOut = 10;
                int nCount = 0;
                int nTimeStamp = 1;
                string strPresetStatus = "";

                while (true)
                {

                    string strPTZF = String.Format("001;{0:000.####};{1:+00.####;-00.####;+00.0000 };{2:00000};{3:00000}", panAbs, tiltAbs, zoom, focus);

                    SendAuthorityCmd(nCh, CommandPTZFAbsMove.CMDGROUP_PTZFABSMOVE, CommandPTZFAbsMove.CMDTYPE_PTZFABSMOVE_MOVE, strPTZF);
                    
                    while (true)
                    {
                        Thread.Sleep(1000);
                        SendAuthorityCmd(nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PAN_MOTORSTATUS_REQ);
                        string strStatus = GetPanMoveStatus(nCh);

                        if (strStatus == "1")
                        {
                            nCount = 0;
                            //System.Console.WriteLine("프리셋 이동중...");
                            strPresetStatus = String.Format("채널 {0} 프리셋 이동중({1})", nCh, nTimeStamp);
                        }
                        else if (strStatus == "2")
                        {
                            nCount = 0;
                            //System.Console.WriteLine("프리셋 이동 완료...");
                            strPresetStatus = String.Format("채널 {0} 프리셋 이동 정지({1})", nCh, nTimeStamp);
                            break;
                        }
                        else
                        {
                            strPresetStatus = String.Format("채널 {0} 프리셋 상태 인식 실패({1})", nCh, nTimeStamp);
                        }

                        //SetPresetStatus(nCh, strPresetStatus);

                        SendAuthorityCmd(nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_REQ);
                        string strPanTilt = GetPanTIltDeg(nCh);

                    

                        try
                        {
                            int index1 = strPanTilt.IndexOf(';');
                            //index1 += 1;
                            string strPanAbs = strPanTilt.Substring(0, index1);
                            string strTiltAbs = strPanTilt.Substring(index1 + 1, strPanTilt.Length - index1 - 1);

                            double dPan = 0;
                            double dTilt = 0;
                            dPan = double.Parse(strPanAbs);
                            dTilt = double.Parse(strTiltAbs);
                            int camX=0;
                            int camY = 0;
                            PanTiltPosToImgAbsPos(dPan, dTilt, ref camX, ref camY, arrPanoInfo[nCh - 1]);
                            arrCanvas[nCh - 1].DrawPanTiltDirectionPoint(camX, camY);
                        }
                        catch(Exception ee)
                        {

                        }
                    
                        //Thread.Sleep(1000);

                        nCount++;
                        nTimeStamp++;
                        if (nCount >= nTimeOut)
                            break;
                    }
                    //

                    //Thread.Sleep(1000);
                    //SendAuthorityCmd(nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PAN_MOTORSTATUS_REQ);
                    //string strMotorStatus = GetPanMotorStatus();
                    //UpdatePanMotorStatusUI(nCh, strMotorStatus, true);
                    break;
                }
                SendAuthorityCmd(nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_REQ);
                strPresetStatus = String.Format("채널 {0} 프리셋 이동 완료({1})", nCh, nTimeStamp);
                //SetPresetStatus(nCh, strPresetStatus);
                //this.m_bPresetStart[nCh - 1] = false;
                SetPresetRunStatus(nCh, false);
                CreatePacketParsingThread(nCh);
            });
            #endregion
        }


        public PanoramaMoveInfo[] CalcPanoramaPanPostion(PanoramaInfo info)
        {
        
            //m_list.clear();
            int nFrameDeg = 24;//한프레임당 30도

            //int iTotalFrame = 360 / m_nLGTD_PerFrame;
            int iTotalFrame = info.nPanoImgFovW / nFrameDeg;
            PanoramaMoveInfo[] arrMoveInfo = new PanoramaMoveInfo[iTotalFrame];

        //CString str; str.Format("%d 장", iTotalFrame);
        //GetDlgItem(IDC_STATIC_SET_NUMOFFRAME)->SetWindowText(str);
        //((CSliderCtrl*)GetDlgItem(IDC_SLIDER1))->SetRange(0, iTotalFrame);
            double dCapturePanDeg = nFrameDeg / 2.0;
            //dCapturePanDeg += 5;//  [4/11/2014 Yeun]

            //PRESETDATA presetdata;
            //presetdata.panoinfo.uPanoImgFovW = 360;//파노라마 가로 전체 각도
            //presetdata.panoinfo.dPanoImgFovH = m_nLGTD_PerFrame * 0.8;//임시
            //presetdata.panoinfo.dPanoImgTiltPivotDeg = theApp.m_dTiltDeg;

            //presetdata.bPanoCap = TRUE;

            //  [5/9/2014 Yeun]
            //double dPanoImgStartPan = (m_nLGTD_PerFrame - dCapturePanDeg) / 2;

            //CString strSetPan;
            for (int i = 0; i < iTotalFrame; i++)
            {
                PanoramaMoveInfo moveInfo = new PanoramaMoveInfo();
                moveInfo.dPan = dCapturePanDeg;
                moveInfo.dTilt = info.dPanoImgTiltPivotDeg;

                arrMoveInfo[i] = moveInfo;

                //CString strPan;
                //strPan.Format("%05.1lf, ", dCapturePanDeg);
                //strSetPan += strPan;
                // presetdata.dPanAbsV = dCapturePanDeg;
                //presetdata.dTiltAbsV = theApp.m_dTiltDeg;

                // presetdata.panoinfo.dPanoImgStartPan = dPanoImgStartPan;//  [5/9/2014 Yeun]
                // m_list.push_back(presetdata);

                dCapturePanDeg += nFrameDeg;
            }
            return arrMoveInfo;
        }
        public void PanoramaCaptureStart(int nCh, PanoramaInfo panoInfo)
        {
            //이동
            if (CheckPresetRunStatus(nCh) == true)//이미 진행 중
                return;

            string status = String.Format("채널 {0} 프리셋 시작", nCh);
            //this.PresetStatusLabel.Content = status;
            //this.m_bPresetStart[nCh - 1] = true;
        

            

            //ImgPosToPanTiltPos(x, y, ref panAbs, ref tiltAbs, arrPanoInfo[nCh - 1]);
            PanoramaMoveInfo[] moveInfo = CalcPanoramaPanPostion(panoInfo);


            DestroyPacketParsingThread(nCh);//종료 시도
            for (int i = 0; i < 50; i++)
            {
                if (IsRunPacketParsingThread(nCh) == false)//종료되었는지 확인
                {
                    //패킷 파싱 스레드 종료
                    //이제 부터 동기적으로 송수신
                    break;
                }
                Thread.Sleep(100);
            }
            #region

            PanoramaCanvas[] arrCanvas = { panoramaCanvas1, panoramaCanvas2, panoramaCanvas3, panoramaCanvas4, panoramaCanvas5 };

            Task.Run(() =>
            {
                SetPresetRunStatus(nCh, true);
                const int nTimeOut = 10;
                int nCount = 0;
                int nTimeStamp = 1;
                string strPresetStatus = "";

                while (true)
                {               

                    for(int i=0; i< moveInfo.Count(); i++ )//12장 촬영
                    {
                        nTimeStamp = 0;
                        //선택이동 스레드
                        double panAbs = moveInfo[i].dPan;
                        double tiltAbs = moveInfo[i].dTilt;
                        int zoom = moveInfo[i].nZoomAbs;
                        int focus = 50000;


                        string strPTZF = String.Format("001;{0:000.####};{1:+00.####;-00.####;+00.0000 };{2:00000};{3:00000}", panAbs, tiltAbs, zoom, focus);
                        arrCanvas[nCh - 1].panoSetupWindow.SetPanoramaStatus(strPTZF);
                        SendAuthorityCmd(nCh, CommandPTZFAbsMove.CMDGROUP_PTZFABSMOVE, CommandPTZFAbsMove.CMDTYPE_PTZFABSMOVE_MOVE, strPTZF);

                        Thread.Sleep(1000);

                        while(true)//상태확인
                        {
                            SendAuthorityCmd(nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PAN_MOTORSTATUS_REQ);
                            string strStatus = GetPanMoveStatus(nCh);

                            if (strStatus == "1")
                            {
                                nCount = 0;
                                //System.Console.WriteLine("프리셋 이동중...");
                                strPresetStatus = String.Format("채널 {0} 파노라마 프레임{1} 이동중({2})", nCh, i+1, nTimeStamp);
                            }
                            else if (strStatus == "2")
                            {
                                nCount = 0;
                                //System.Console.WriteLine("프리셋 이동 완료...");
                                strPresetStatus = String.Format("채널 {0} 파노라마 프레임{1} 이동 정지({2})", nCh, i + 1, nTimeStamp);
                                break;
                            }
                            else
                            {
                                strPresetStatus = String.Format("채널 {0} 파노라마 프레임{1} 상태 인식 실패({2})", nCh, i + 1, nTimeStamp);
                            }

                            arrCanvas[nCh - 1].panoSetupWindow.SetPanoramaStatus(strPresetStatus);
                            //SetPresetStatus(nCh, strPresetStatus);

                            SendAuthorityCmd(nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_REQ);
                            Thread.Sleep(1000);

                            nCount++;
                            nTimeStamp++;
                            if (nCount >= nTimeOut)
                                break;
                        }

                        //캡처.
                                           
                        string imgName = DateTime.Now.ToString("yyyyMMddHHmmss") + "_"+ i.ToString() + ".jpg";
                        string baseDir = AppDomain.CurrentDomain.BaseDirectory;
                        string chFolder = String.Format("Ch{0:d2}\\", nCh);
                        string strFilePathName = baseDir + chFolder +imgName;
                        Process[] procByName = Process.GetProcessesByName("Hawkeye_VideoPlayer");
                        
                        if (procByName.Length > 0)
                        {
                            string msg = strFilePathName;
                            byte[] buff = System.Text.Encoding.Default.GetBytes(msg);

                            Win32API.COPYDATASTRUCT cds = new Win32API.COPYDATASTRUCT();
                            cds.dwData = (IntPtr)nCh;
                            cds.cbData = buff.Length + 1;
                            cds.lpData = msg;

                            for(int j=0; j< procByName.Length; j++)
                            {
                                Win32API.SendMessage(procByName[j].MainWindowHandle, Win32API.WM_COPYDATA, 0, ref cds);
                            }                           
                        }
                        Thread.Sleep(1000);
                        if (File.Exists(strFilePathName) == true)//파일이 존재
                        {
                            Console.WriteLine("파일이 존재합니다.");
                            arrCanvas[nCh - 1].SetImagePathName(i, strFilePathName);
                            strPresetStatus = String.Format("채널 {0} 파노라마 프레임{1} 캡처 성공", nCh, i + 1);

                            panoInfoIni.ReadIni(nCh);
                            panoInfoIni.arrPanoImagePathName[i] = strFilePathName;
                            panoInfoIni.WriteIni(nCh);
                        }
                        else
                        {
                            Console.WriteLine("파일을 찾을수없습니다.");
                            strPresetStatus = String.Format("채널 {0} 파노라마 프레임{1} 캡처 실패", nCh, i + 1);
                        }
                        arrCanvas[nCh - 1].panoSetupWindow.SetPanoramaStatus(strPresetStatus);

                    }
                  
                    //

                    //Thread.Sleep(1000);
                    //SendAuthorityCmd(nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PAN_MOTORSTATUS_REQ);
                    //string strMotorStatus = GetPanMotorStatus();
                    //UpdatePanMotorStatusUI(nCh, strMotorStatus, true);
                    break;
                }
                SendAuthorityCmd(nCh, CommandPTZReqResp.CMDGROUP_PTZREQ, CommandPTZReqResp.CMDTYPE_PTZREQ_PANTILT_POS_REQ);
                strPresetStatus = String.Format("채널 {0} 파노라마 촬영 완료({1})", nCh, nTimeStamp);
                arrCanvas[nCh - 1].panoSetupWindow.SetPanoramaStatus(strPresetStatus);
                //SetPresetStatus(nCh, strPresetStatus);
                //this.m_bPresetStart[nCh - 1] = false;
                SetPresetRunStatus(nCh, false);
                CreatePacketParsingThread(nCh);
            });
            #endregion
        }
        public void PanoramaCaptureStop()
        {

        }
        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;

            Minimize();
        }
    }
}
