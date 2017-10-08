using System;
using System.Text;
using System.IO;
using System.Net;

namespace HanwhaCameraController
{
    public class HanwhaCameraControl : IDisposable
    {
        //private string strIP;
        private bool mIsDisposed = false;

        private string strIP;
        private string strID;
        private string strPW;

        public HanwhaCameraControl(string ip, string id, string pw)
        {
            strIP = ip;
            strID = id;
            strPW = pw;
        }

        ~HanwhaCameraControl()
        {
            Dispose(false);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(true);
        }

        protected virtual void Dispose(bool b)
        {
            if (mIsDisposed)
            {
                return;
            }
            if (b)
            {
            }
            // Free any unmanaged resources in this section
            mIsDisposed = true;
        }

        public void SetDay(bool b)
        {
            StreamReader d;
            HttpWebResponse p;
            HttpWebRequest r;
            Stream t;
            string z = string.Empty;

            try
            {
                if (b)
                {
                    r = (HttpWebRequest)WebRequest.Create("http://" + strIP + "/cgi-bin/system.cgi?msubmenu=camera&action=apply&daynight=0");
                }
                else
                {
                    r = (HttpWebRequest)WebRequest.Create("http://" + strIP + "/cgi-bin/system.cgi?msubmenu=camera&action=apply&daynight=1");
                }
                r.Method = "GET";
                r.Credentials = new NetworkCredential(strID, strPW);
                p = (HttpWebResponse)r.GetResponse();
                t = p.GetResponseStream();
                d = new StreamReader(t, Encoding.Default);
                z = d.ReadToEnd();
            }
            catch (Exception ex)
            {
                //Common.WriteLog("HanwhaCamera.ZoomIn : " + ex.Message);
            }
        }

        public void ZoomIn()
        {
            StreamReader d;
            HttpWebResponse p;
            HttpWebRequest r;
            Stream t;
            string z = string.Empty;

            try
            {
                r = (HttpWebRequest)WebRequest.Create("http://" + strIP + "/cgi-bin/ptz.cgi?zoom=in");
                r.Method = "GET";
                r.Credentials = new NetworkCredential(strID, strPW);
                p = (HttpWebResponse)r.GetResponse();
                t = p.GetResponseStream();
                d = new StreamReader(t, Encoding.Default);
                z = d.ReadToEnd();

                System.Console.WriteLine("ZoomIn");
            }
            catch (Exception ex)
            {
                //Common.WriteLog("HanwhaCamera.ZoomIn : " + ex.Message);
            }
        }

        public void ZoomOut()
        {
            StreamReader d;
            HttpWebResponse p;
            HttpWebRequest r;
            Stream t;
            string z = string.Empty;

            try
            {
                r = (HttpWebRequest)WebRequest.Create("http://" + strIP + "/cgi-bin/ptz.cgi?zoom=out");
                r.Method = "GET";
                r.Credentials = new NetworkCredential(strID, strPW);
                p = (HttpWebResponse)r.GetResponse();
                t = p.GetResponseStream();
                d = new StreamReader(t, Encoding.Default);
                z = d.ReadToEnd();
                System.Console.WriteLine("ZoomOut");
            }
            catch (Exception ex)
            {
                //Common.WriteLog("HanwhaCamera.ZoomOut : " + ex.Message);
            }
        }

        public void ZoomStop()
        {
            StreamReader d;
            HttpWebResponse p;
            HttpWebRequest r;
            Stream t;
            string z = string.Empty;

            try
            {
                r = (HttpWebRequest)WebRequest.Create("http://" + strIP + "/cgi-bin/ptz.cgi?zoom=stop");
                r.Method = "GET";
                r.Credentials = new NetworkCredential(strID, strPW);
                p = (HttpWebResponse)r.GetResponse();
                t = p.GetResponseStream();
                d = new StreamReader(t, Encoding.Default);
                z = d.ReadToEnd();

                System.Console.WriteLine("ZoomStop");
            }
            catch (Exception ex)
            {
                //Common.WriteLog("HanwhaCamera.ZoomStop : " + ex.Message);
            }
        }

        public void FocusStop()
        {
            StreamReader d;
            HttpWebResponse p;
            HttpWebRequest r;
            Stream t;
            string z = string.Empty;

            try
            {
                r = (HttpWebRequest)WebRequest.Create("http://" + strIP + "/cgi-bin/ptz.cgi?focus=stop");
                r.Method = "GET";
                r.Credentials = new NetworkCredential(strID, strPW);
                p = (HttpWebResponse)r.GetResponse();
                t = p.GetResponseStream();
                d = new StreamReader(t, Encoding.Default);
                z = d.ReadToEnd();
            }
            catch (Exception ex)
            {
                //Common.WriteLog("HanwhaCamera.FocusStop : " + ex.Message);
            }
        }

        public void FocusNear()
        {
            StreamReader d;
            HttpWebResponse p;
            HttpWebRequest r;
            Stream t;
            string z = string.Empty;

            try
            {
                r = (HttpWebRequest)WebRequest.Create("http://" + strIP + "/cgi-bin/ptz.cgi?focus=near");
                r.Method = "GET";
                r.Credentials = new NetworkCredential(strID, strPW);
                p = (HttpWebResponse)r.GetResponse();
                t = p.GetResponseStream();
                d = new StreamReader(t, Encoding.Default);
                z = d.ReadToEnd();
                System.Console.WriteLine("FocusNear");
            }
            catch (Exception ex)
            {
                //Common.WriteLog("HanwhaCamera.FocusNear : " + ex.Message);
            }
        }

        public void FocusFar()
        {
            StreamReader d;
            HttpWebResponse p;
            HttpWebRequest r;
            Stream t;
            string z = string.Empty;

            try
            {
                r = (HttpWebRequest)WebRequest.Create("http://" + strIP + "/cgi-bin/ptz.cgi?focus=far");
                r.Method = "GET";
                r.Credentials = new NetworkCredential(strID, strPW);
                p = (HttpWebResponse)r.GetResponse();
                t = p.GetResponseStream();
                d = new StreamReader(t, Encoding.Default);
                z = d.ReadToEnd();
            }
            catch (Exception ex)
            {
                //Common.WriteLog("HanwhaCamera.FocusFar : " + ex.Message);
            }
        }

        public void AutoFocus()
        {
            StreamReader d;
            HttpWebResponse p;
            HttpWebRequest r;
            Stream t;
            string z = string.Empty;

            try
            {
                r = (HttpWebRequest)WebRequest.Create("http://" + strIP + "/cgi-bin/ptz.cgi?runautofocus=on");
                r.Method = "GET";
                r.Credentials = new NetworkCredential(strID, strPW);
                p = (HttpWebResponse)r.GetResponse();
                t = p.GetResponseStream();
                d = new StreamReader(t, Encoding.Default);
                z = d.ReadToEnd();
                //Common.WriteLog("AutoFocus=>" + z);
                System.Console.WriteLine("AutoFocus");

            }
            catch (Exception ex)
            {
                //Common.WriteLog("HanwhaCamera.AutoFocus : " + ex.Message);
            }
        }
    }
}
