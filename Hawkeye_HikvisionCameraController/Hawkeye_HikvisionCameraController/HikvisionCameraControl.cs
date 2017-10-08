using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Xml;

namespace HikvisionCameraController
{
    class HikvisionCameraControl
    {
        private string strIP;
        private string strID;
        private string strPW;

        public HikvisionCameraControl(string ip, string id, string pw)
        {
            strIP = ip;
            strID = id;
            strPW = pw;
        }
        private string GetXML(string strURI)
        {
            string strXML = string.Empty;
            try
            {
                HttpWebResponse myHttpWebResponse;
                HttpWebRequest myHttpWebRequest;

                myHttpWebRequest = (HttpWebRequest)WebRequest.Create(strURI);
                myHttpWebRequest.Method = "GET";
                //myHttpWebRequest.Method = method;
                myHttpWebRequest.ContentType = "application/xml";
                myHttpWebRequest.Credentials = new NetworkCredential(strID, strPW);

                myHttpWebRequest.Timeout = 1000;
                myHttpWebResponse = (HttpWebResponse)myHttpWebRequest.GetResponse();
                Stream stream = myHttpWebResponse.GetResponseStream();
                StreamReader streamReader = new StreamReader(stream, Encoding.Default);
                strXML = streamReader.ReadToEnd();
            }
            catch(Exception ex)
            {
                strXML = ex.ToString();
            }    

            return strXML;
        }
        private string PutXML(string strURI, string strPutXML)
        {
           
            string strXML = string.Empty;

            try
            {
                Stream responseStream;
             

                HttpWebRequest httpWebRequest = (HttpWebRequest)WebRequest.Create(strURI);

                byte[] byPutXML = Encoding.Default.GetBytes(strPutXML);
                httpWebRequest.Method = "PUT";
                httpWebRequest.ContentType = "application/xml";

                httpWebRequest.Credentials = new NetworkCredential(strID, strPW);
                Stream requestStream = httpWebRequest.GetRequestStream();

                requestStream.Write(byPutXML, 0, byPutXML.Length);
                requestStream.Close();

                HttpWebResponse httpWebResponse = (HttpWebResponse)httpWebRequest.GetResponse();
                responseStream = httpWebResponse.GetResponseStream();

                StreamReader streamReader = new StreamReader(responseStream, Encoding.Default);
                strXML = streamReader.ReadToEnd();
            }
            catch (Exception ex)
            {
                //Common.WriteLog("Milesight.SetDay : " + ex.Message);

                return ex.ToString();
            }
            return strXML;
        }

        public bool GetImageEnhancement(out string enabled, out string ImageEnhancementLevel)
        {
            enabled = string.Empty;
            ImageEnhancementLevel = string.Empty;

            string strXML = string.Empty;
            try
            {
                strXML = GetXML("http://" + strIP + "/ISAPI/Image/channels/1/imageenhancement");
                

                XmlDocument xml = new XmlDocument(); // XmlDocument 생성
                xml.LoadXml(strXML);
                XmlNodeList xnList = xml.GetElementsByTagName("ImageEnhancement"); //접근할 노드

                foreach (XmlNode xn in xnList)
                {
                    enabled = xn["enabled"].InnerText;
                    ImageEnhancementLevel = xn["ImageEnhancementLevel"].InnerText;
                }

            }
            catch (Exception ex)
            {
                //Common.WriteLog("Milesight.SetDay : " + ex.Message);

                return false;
            }

            return true;
        }


        public bool GetDehaze(out string dehazeMode, out string dehazeLevel)
        {
            dehazeMode = string.Empty;
            dehazeLevel = string.Empty;

            string strXML = string.Empty;
            try
            {
                strXML = GetXML("http://" + strIP + "/ISAPI/Image/channels/1/dehaze");


                XmlDocument xml = new XmlDocument(); // XmlDocument 생성
                xml.LoadXml(strXML);
                XmlNodeList xnList = xml.GetElementsByTagName("Dehaze"); //접근할 노드

                foreach (XmlNode xn in xnList)
                {
                    dehazeMode = xn["DehazeMode"].InnerText;
                    dehazeLevel = xn["DehazeLevel"].InnerText;
                }

            }
            catch (Exception ex)
            {
                //Common.WriteLog("Milesight.SetDay : " + ex.Message);

                return false;
            }

            return true;
        }


        //서리제거(웹페이지상에나온한글이름)
        //dehazeLevel : 사용하지않음
        public bool SetDehaze(string dehazeMode, string dehazeLevel)
        {
            /*
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n
<Dehaze version=\"2.0\" xmlns=\"http://www.hikvision.com/ver20/XMLSchema\">\r\n
<DehazeMode>close</DehazeMode>\r\n
<DehazeLevel>0</DehazeLevel>\r\n
</Dehaze>\r\n"
*/
            try
            {
                string putXML = string.Empty;
                if (dehazeMode == "open")
                {
                    putXML = "<?xml version=\"1.0\"encoding=\"UTF-8\"?>" +
                "<Dehaze version=\"2.0\" xmlns=\"http://www.hikvision.com/ver20/XMLSchema\">" +
                "<DehazeMode>open</DehazeMode>" +
                "<DehazeLevel>0</DehazeLevel>" +
                "</Dehaze>";
                }
                else if (dehazeMode == "close")
                {
                    putXML = "<?xml version=\"1.0\"encoding=\"UTF-8\"?>" +
                   "<Dehaze version=\"2.0\" xmlns=\"http://www.hikvision.com/ver20/XMLSchema\">" +
                "<DehazeMode>close</DehazeMode>" +
                "<DehazeLevel>0</DehazeLevel>" +
                "</Dehaze>";
                }
                else if (dehazeMode == "auto")
                {
                    putXML = "<?xml version=\"1.0\"encoding=\"UTF-8\"?>" +
                   "<Dehaze version=\"2.0\" xmlns=\"http://www.hikvision.com/ver20/XMLSchema\">" +
                "<DehazeMode>auto</DehazeMode>" +
                "<DehazeLevel>0</DehazeLevel>" +
                "</Dehaze>";
                }
                string strXML = PutXML("http://" + strIP + "/ISAPI/Image/channels/1/dehaze", putXML);

                XmlDocument xml = new XmlDocument(); // XmlDocument 생성
                xml.LoadXml(strXML);
                XmlNodeList xnList = xml.GetElementsByTagName("ResponseStatus"); //접근할 노드

                /*
                <statusCode>1</statusCode>\n
                <statusString>OK</statusString>\n
                <subStatusCode>ok</subStatusCode>\n                
                */
            foreach (XmlNode xn in xnList)
                {
                    string a = xn["statusCode"].InnerText;
                    string b = xn["statusString"].InnerText;
                    string c = xn["subStatusCode"].InnerText;
                }

            }
            catch (Exception ex)
            {
                //Common.WriteLog("Milesight.SetDay : " + ex.Message);
                return false;
            }
            return true;
        }

        public bool SetEIS(string enabled)
        {           
            /*
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n
< EIS version =\"2.0\" xmlns=\"http://www.hikvision.com/ver20/XMLSchema\">\r\n
  < enabled > false </ enabled >
  \r\n </ EIS >\r\n"
  */  
            try
            {
                string putXML = string.Empty;
                if (enabled == "true")
                {
                    putXML = "<?xml version=\"1.0\"encoding=\"UTF-8\"?>" +
                "<EIS version=\"2.0\" xmlns=\"http://www.hikvision.com/ver20/XMLSchema\">" +
                "<enabled>true</enabled>" +
                "</EIS>";
                }
                else if (enabled == "false")
                {
                    putXML = "<?xml version=\"1.0\"encoding=\"UTF-8\"?>" +
                  "<EIS version=\"2.0\" xmlns=\"http://www.hikvision.com/ver20/XMLSchema\">" +
                  "<enabled>false</enabled>" +
                  "</EIS>";
                }
                string strXML = PutXML("http://" + strIP + "/ISAPI/Image/channels/1/EIS", putXML);

                XmlDocument xml = new XmlDocument(); // XmlDocument 생성
                xml.LoadXml(strXML);
                XmlNodeList xnList = xml.GetElementsByTagName("ResponseStatus"); //접근할 노드

                /*
                <statusCode>1</statusCode>\n
                <statusString>OK</statusString>\n
                <subStatusCode>ok</subStatusCode>\n                
                */
                foreach (XmlNode xn in xnList)
                {
                    string a = xn["statusCode"].InnerText;
                    string b = xn["statusString"].InnerText;
                    string c = xn["subStatusCode"].InnerText;                    
                }

            }
            catch (Exception ex)
            {
                //Common.WriteLog("Milesight.SetDay : " + ex.Message);
                return false;
            }
            return true;
        }

        //EISLevel 지원안함
        public bool GetEIS(out string enabled, out string EISLevel)
        {
            enabled = string.Empty;
            EISLevel = string.Empty;

            string strXML = string.Empty;
            try
            {
               strXML = GetXML("http://" + strIP + "/ISAPI/Image/channels/1/EIS"); ;


                XmlDocument xml = new XmlDocument(); // XmlDocument 생성
                xml.LoadXml(strXML);
                XmlNodeList xnList = xml.GetElementsByTagName("EIS"); //접근할 노드

                foreach (XmlNode xn in xnList)
                {
                    enabled = xn["enabled"].InnerText;               
                }

            }
            catch (Exception ex)
            {
                //Common.WriteLog("Milesight.SetDay : " + ex.Message);

                return false;
            }

            return true;
        }

        public bool SetIrCutFilter(string IrcutFilterType)
        {
            byte[] a;
            StreamReader d;
            HttpWebResponse p = null;
            HttpWebRequest r = null;
            Stream s;
            Stream t;
            string w = string.Empty;
            string z = string.Empty;

            try
            {
                if (IrcutFilterType == "day")
                {
                    r = (HttpWebRequest)WebRequest.Create("http://" + strIP + "/ISAPI/Image/channels/1/ircutfilter");
                    w = "<?xml version=\"1.0\"encoding=\"UTF-8\"?><IrcutFilter version=\"2.0\" xmlns=\"http://www.hikvision.com/ver20/XMLSchema\"><IrcutFilterType>day</IrcutFilterType></IrcutFilter>";
                }
                else if(IrcutFilterType == "night")
                {
                    r = (HttpWebRequest)WebRequest.Create("http://" + strIP + "/ISAPI/Image/channels/1/ircutfilter");
                    w = "<?xml version=\"1.0\"encoding=\"UTF-8\"?><IrcutFilter><IrcutFilterType>night</IrcutFilterType></IrcutFilter>";
                }
                a = Encoding.Default.GetBytes(w);
                r.Method = "PUT";
                r.ContentType = "application/xml";

                r.Credentials = new NetworkCredential(strID, strPW);
                s = r.GetRequestStream();
                s.Write(a, 0, a.Length);
                s.Close();
                p = (HttpWebResponse)r.GetResponse();
                t = p.GetResponseStream();
                d = new StreamReader(t, Encoding.Default);
                z = d.ReadToEnd();
            }
            catch (Exception ex)
            {
                //Common.WriteLog("Milesight.SetDay : " + ex.Message);
                return false;
            }
            return true;
        }
        public bool GetIrCutFilter(out string IrcutFilterType, out string nightToDayFilterLevel, out string nightToDayFilterTime)
        {                    
            IrcutFilterType = string.Empty;
            nightToDayFilterLevel = string.Empty;
            nightToDayFilterTime = string.Empty;

            string strXML = string.Empty;
            try
            {


                /*
                myHttpWebRequest = (HttpWebRequest)WebRequest.Create("http://" + strIP + "/ISAPI/Image/channels/1/ircutfilter");
              
                myHttpWebRequest.Method = "GET";
                myHttpWebRequest.ContentType = "application/xml";
                myHttpWebRequest.Credentials = new NetworkCredential(strID, strPW);
              
                myHttpWebResponse = (HttpWebResponse)myHttpWebRequest.GetResponse();
                Stream stream = myHttpWebResponse.GetResponseStream();
                StreamReader streamReader = new StreamReader(stream, Encoding.Default);
                string strXML = streamReader.ReadToEnd();
               */

                strXML = GetXML("http://" + strIP + "/ISAPI/Image/channels/1/ircutfilter");
                XmlDocument xml = new XmlDocument(); // XmlDocument 생성
                xml.LoadXml(strXML);
                XmlNodeList xnList = xml.GetElementsByTagName("IrcutFilter"); //접근할 노드

                
                foreach (XmlNode xn in xnList)
                {
                    IrcutFilterType = xn["IrcutFilterType"].InnerText;
                    nightToDayFilterLevel = xn["nightToDayFilterLevel"].InnerText;
                    nightToDayFilterTime = xn["nightToDayFilterTime"].InnerText;
                }
                
            }
            catch (Exception ex)
            {
                //Common.WriteLog("Milesight.SetDay : " + ex.Message);
               
                return false;
            }

            return true;
        }


        public void SetDay(bool b, string mIP, string ID, string PW)
        {
            byte[] a;
            StreamReader d;
            HttpWebResponse p;
            HttpWebRequest r;
            Stream s;
            Stream t;
            string w;
            string z = string.Empty;

            try
            {
                if (b)
                {
                    r = (HttpWebRequest)WebRequest.Create("http://" + strIP + "/ISAPI/Image/channels/1/ircutfilter");
                    w = "<?xml version=\"1.0\"encoding=\"UTF-8\"?><IrcutFilter><IrcutFilterType>day</IrcutFilterType></IrcutFilter>";
                }
                else
                {
                    r = (HttpWebRequest)WebRequest.Create("http://" + strIP + "/ISAPI/Image/channels/1/ircutfilter");
                    w = "<?xml version=\"1.0\"encoding=\"UTF-8\"?><IrcutFilter><IrcutFilterType>night</IrcutFilterType></IrcutFilter>";
                }
                a = Encoding.Default.GetBytes(w);
                r.Method = "PUT";
                r.ContentType = "application/xml";
                //r.Credentials = new NetworkCredential("admin", "u2sru2sr");
                r.Credentials = new NetworkCredential(strID, strPW);
                s = r.GetRequestStream();
                s.Write(a, 0, a.Length);
                s.Close();
                p = (HttpWebResponse)r.GetResponse();
                t = p.GetResponseStream();
                d = new StreamReader(t, Encoding.Default);
                z = d.ReadToEnd();
            }
            catch (Exception ex)
            {
                //Common.WriteLog("Milesight.SetDay : " + ex.Message);
            }
        }
    }
}
