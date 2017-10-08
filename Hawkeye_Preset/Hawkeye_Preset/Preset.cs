using Ini;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Hawkeye_Preset
{

    /*
       <GridViewColumn Header="NO" Width="24" DisplayMemberBinding="{Binding No}"/>
                        <GridViewColumn Header="이름" Width="60" DisplayMemberBinding="{Binding Name}"/>
                        <GridViewColumn Header="시간" Width="30" DisplayMemberBinding="{Binding Time}"/>

                        <GridViewColumn Header="방위각(Abs)" Width="60" DisplayMemberBinding="{Binding PanAbs}"/>
                        <GridViewColumn Header="고저각(Abs)" Width="60" DisplayMemberBinding="{Binding TiltAbs}"/>
                 
                        <GridViewColumn Header="줌" Width="40" DisplayMemberBinding="{Binding Zoom}"/>
                        <GridViewColumn Header="포커스" Width="40" DisplayMemberBinding="{Binding Zoom}"/>
    */

    public class PresetChannelInfoReadWrite
    {
        public string presetPathName;
        private IniFile ini = null;
        public PresetChannelInfoReadWrite(string name)
        {
            /*
            int nIndex = AppDomain.CurrentDomain.BaseDirectory.LastIndexOf('\\');
            string newPath = AppDomain.CurrentDomain.BaseDirectory.Substring(0, nIndex);
            nIndex = newPath.LastIndexOf('\\');
            newPath = newPath.Substring(0, nIndex + 1);

            ini = new IniFile(newPath + name + ".ini");
            */
            string filePath = AppDomain.CurrentDomain.BaseDirectory + name + ".ini";
            ini = new IniFile(filePath);
        }
        public void WriteIni(int nCh)
        {
            string ch = string.Format("ch{0:d2}", nCh);

            ini.IniWriteValue(ch, "presetPathName", this.presetPathName);
        }
        public void ReadIni(int nCh)
        {
            string ch = string.Format("ch{0:d2}", nCh);

            this.presetPathName = ini.IniReadValue(ch, "presetPathName");
        }
    }

    public class PresetReadWrite
    {
      
        private ObservableCollection<PresetListRow> presetList = new ObservableCollection<PresetListRow>();
        private IniFile ini = null;
        public void CreateNewFile(string name)
        {
            ini = new IniFile(name);
        
            ini.IniWriteValue("Common", "NumberOfPreset", presetList.Count.ToString());//파일을 새로 만들려면 아무 데이터나 파일에 쓴다.

            //파일을 새로 만들었으니 리스트를 초기화 시킨다.
            presetList.Clear();
        }
        public bool LoadFIle(string filePathName)
        {
            ini = new IniFile(filePathName);
            
            string temp = ini.IniReadValue("common", "NumberOfPreset");
            if (temp == "")
                return false;

            int numberOfPreset = int.Parse(temp);

            presetList.Clear();

            for (int i = 0; i < numberOfPreset; i++)
            {
                string num = string.Format("Num{0:d2}", i + 1);

                //string _no = ini.IniReadValue(num, "no");
                string _no = (i+1).ToString();
                string _name = ini.IniReadValue(num, "name"); 
                string _time = ini.IniReadValue(num, "time"); 
                string _panAbs = ini.IniReadValue(num, "pan"); 
                string _tiltAbs = ini.IniReadValue(num, "tilt"); 
                string _zoom = ini.IniReadValue(num, "zoom");
                string _focus = ini.IniReadValue(num, "focus");

                try
                {
                    int no = int.Parse(_no);
                    string name = _name;
                    int time = int.Parse(_time);
                    double panAbs = double.Parse(_panAbs);
                    double tiltAbs = double.Parse(_tiltAbs);
                    int zoom = int.Parse(_zoom);
                    int focus = int.Parse(_focus);
                    PresetListRow row = new PresetListRow(no, name, time, panAbs, tiltAbs, zoom, focus);
                    presetList.Add(row);
                }                      
                catch(Exception e)
                {

                }
                
              

             
            }

            return true;
        }
        public int GetNumberOfPreset()
        {
            return presetList.Count();
        }
        public bool AddPresetRow(PresetListRow presetRow)//Add 할땐 No를 할당 하지 않는다.
        {
            if (ini == null)
                return false;

            //현재 프리셋 개수를 얻어와서 (No)넘버를 부여 한다.
            int count = presetList.Count();
            presetRow.No = count + 1;

            presetList.Add(presetRow);
            
            AsyncIniWritePresetList();

            return true;
        }
        public ObservableCollection<PresetListRow> GetPresetList()
        {
            return presetList;
        }
        public PresetListRow GetRow(int nIndex)
        {
            if (nIndex < 0 || this.presetList.Count == 0)
                return null;

            return this.presetList[nIndex];
        }
        public void ReNumbering()
        {
            int Size = this.presetList.Count;
            for (int i=0; i< Size; i++)
            {
                this.presetList[i].No = i + 1;
            }            
        }
        public void DeleteAllRow()
        {
            this.presetList.Clear();
            AsyncIniWritePresetList();
        }
        public void DeleteRow(int nIndex)
        {
            this.presetList.RemoveAt(nIndex);
            ReNumbering();
            AsyncIniWritePresetList();
        }
        public void SetRow(int nIndex, PresetListRow row)
        {
            this.presetList[nIndex] = row;

            AsyncIniWritePresetList();
        }
        private object lockObject = new object();
        private async void AsyncIniWritePresetList()
        {
            //MainWindow.bRefPointViewChanged = true;
            //Console.WriteLine("Code Block #1");

            string strPath = ini.path;
            bool bExists = File.Exists(strPath);
            if(bExists == true)
            {
                await IniWritePresetList();
            }
     

            //Console.WriteLine("Code Block #2");
        }
        private Task IniWritePresetList()
        {
            return Task.Run(() =>
            {
                /*
                this.Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, (Action)(() =>
                {
                    this.list.ScrollIntoView(this.list.SelectedItem);
                }));
                */


                //파일이 존재하지 않으면?

                lock (lockObject)
                {
                    //string strPath = System.IO.Directory.GetCurrentDirectory() + "\\presetlist.ini";

                    ini.IniWriteValue("common", "NumberOfPreset", presetList.Count().ToString());

                    for (int i=0; i< presetList.Count(); i++)
                    {
                        string num = string.Format("Num{0:d2}", i+1);

                        //ini.IniWriteValue(num, "no", (i+1).ToString());
                        ini.IniWriteValue(num, "name", presetList[i].Name);
                        ini.IniWriteValue(num, "time", presetList[i].Time.ToString());
                        ini.IniWriteValue(num, "pan", presetList[i].PanAbs.ToString());
                        ini.IniWriteValue(num, "tilt", presetList[i].TiltAbs.ToString());
                        ini.IniWriteValue(num, "zoom", presetList[i].Zoom.ToString());
                        ini.IniWriteValue(num, "focus", presetList[i].Focus.ToString());
                    }
                    

#if false
                      IniFile ini = new IniFile();
                    if (bExists)
                    {
                        //파일이 이미 존재하는경우

                        ini.Load(strPath);

                        ini.RemoveAllSections();
                    }
                    for (int i = 0; i < this.presetList.Count(); i++)
                    {
                        string sectionName = "PRESET_" + i.ToString();
                        ini.AddSection(sectionName).AddKey(PresetInfo.STR_ID).Value = presetList[i].ID.ToString();
                        ini.AddSection(sectionName).AddKey(PresetInfo.STR_NAME).Value = presetList[i].Name.ToString();
                        ini.AddSection(sectionName).AddKey(PresetInfo.STR_SEC).Value = presetList[i].Sec.ToString();

                        ini.AddSection(sectionName).AddKey(PresetInfo.STR_X).Value = presetList[i].X.ToString();
                        ini.AddSection(sectionName).AddKey(PresetInfo.STR_Y).Value = presetList[i].Y.ToString();
                        ini.AddSection(sectionName).AddKey(PresetInfo.STR_ZOOM).Value = presetList[i].Zoom.ToString();
                        ini.AddSection(sectionName).AddKey(PresetInfo.STR_GROUP).Value = presetList[i].Group.ToString();

                        ini.AddSection(sectionName).AddKey(PresetInfo.STR_PANABS).Value = presetList[i].PanAbs.ToString();
                        ini.AddSection(sectionName).AddKey(PresetInfo.STR_TILTABS).Value = presetList[i].TiltAbs.ToString();
                        ini.AddSection(sectionName).AddKey(PresetInfo.STR_PANREL).Value = presetList[i].PanRel.ToString();
                        ini.AddSection(sectionName).AddKey(PresetInfo.STR_TILTREL).Value = presetList[i].TiltRel.ToString();
                        ini.AddSection(sectionName).AddKey(PresetInfo.STR_TARDIST).Value = presetList[i].TargetDistance.ToString();
                        ini.AddSection(sectionName).AddKey(PresetInfo.STR_TARLAT).Value = presetList[i].TargetLatitude;
                        ini.AddSection(sectionName).AddKey(PresetInfo.STR_TARLONG).Value = presetList[i].TargetLongitude;


                        ini.AddSection(sectionName).AddKey(PresetInfo.STR_PATHIMG1).Value = presetList[i].PathImg1;
                        ini.AddSection(sectionName).AddKey(PresetInfo.STR_PATHIMG2).Value = presetList[i].PathImg2;


                    }
                    System.Console.WriteLine("=========파일 쓰기 시작===========");
                    ini.Save(strPath);
                    System.Console.WriteLine("=========파일 쓰기 끝==========="); 
#endif
                }
            }
            );
        }
        private void IniLoadPresetList()
        {
            //파일이 존재하지 않으면?
            string strPath = System.IO.Directory.GetCurrentDirectory() + "\\presetlist.ini";

            bool bExists = File.Exists(strPath);
#if false
            IniFile ini = new IniFile();

            if (bExists)
            {
                ini.Load(strPath);

                //for (int i = 0; i < this.presetList.Count(); i++)
                int i = 0;
                while (true)
                {
                    string sectionName = "PRESET_" + i.ToString();
                    IniFile.IniSection section = ini.GetSection(sectionName);
                    if (section == null)
                        break;

                    int id; int.TryParse(ini.GetKeyValue(sectionName, PresetInfo.STR_ID), out id);
                    string name = ini.GetKeyValue(sectionName, PresetInfo.STR_NAME);
                    int sec; int.TryParse(ini.GetKeyValue(sectionName, PresetInfo.STR_SEC), out sec);

                    float x; float.TryParse(ini.GetKeyValue(sectionName, PresetInfo.STR_X), out x);
                    float y; float.TryParse(ini.GetKeyValue(sectionName, PresetInfo.STR_Y), out y);
                    float zoom; float.TryParse(ini.GetKeyValue(sectionName, PresetInfo.STR_ZOOM), out zoom);

                    string group = ini.GetKeyValue(sectionName, PresetInfo.STR_GROUP);

                    float panabs; float.TryParse(ini.GetKeyValue(sectionName, PresetInfo.STR_PANABS), out panabs);
                    float tiltabs; float.TryParse(ini.GetKeyValue(sectionName, PresetInfo.STR_TILTABS), out tiltabs);
                    float panrel; float.TryParse(ini.GetKeyValue(sectionName, PresetInfo.STR_PANREL), out panrel);
                    float tiltrel; float.TryParse(ini.GetKeyValue(sectionName, PresetInfo.STR_TILTREL), out tiltrel);

                    int tardist; int.TryParse(ini.GetKeyValue(sectionName, PresetInfo.STR_TARDIST), out tardist);

                    string tarlat = ini.GetKeyValue(sectionName, PresetInfo.STR_TARLAT);
                    string tarlong = ini.GetKeyValue(sectionName, PresetInfo.STR_TARLONG);

                    string pathimg1 = ini.GetKeyValue(sectionName, PresetInfo.STR_PATHIMG1);
                    string pathimg2 = ini.GetKeyValue(sectionName, PresetInfo.STR_PATHIMG2);

                    PresetInfo presetInfo = new PresetInfo(id, name, sec, x, y, zoom, group,
                        panabs, tiltabs, panrel, tiltrel, tardist, tarlat, tarlong, pathimg1, pathimg2);
                    presetList.Add(presetInfo);
                    i++;
                }

                printList();
            }
#endif
        }
    }

    public class PresetListRow
    {


        public PresetListRow(string name, int time, double panAbs, double tiltAbs, int zoom, int focus )
        {
            //this.no = no;
            this.name = name;
            this.time = time;
            this.panAbs = panAbs;
            this.tiltAbs = tiltAbs;
            this.zoom = zoom;
            this.focus = focus;
        }

        public PresetListRow(int no, string name, int time, double panAbs, double tiltAbs, int zoom, int focus)
        {
            this.no = no;
            this.name = name;
            this.time = time;
            this.panAbs = panAbs;
            this.tiltAbs = tiltAbs;
            this.zoom = zoom;
            this.focus = focus;
        }
        private int no;//INI에 저장하지 않음. 리스트뷰에 업데이트 할때만 사용
        public int No
        {
            get { return no; }
            set { no = value; }
        }

        private string name;
        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        private int time;
        public int Time
        {
            get { return time; }
            set { time = value; }
        }

        private int zoom;
        public int Zoom
        {
            get { return zoom; }
            set { zoom = value; }
        }

        private int focus;
        public int Focus
        {
            get { return focus; }
            set { focus = value; }
        }

        private double panAbs;
        public double PanAbs
        {
            get { return panAbs; }
            set { panAbs = value; }
        }

        private double tiltAbs;
        public double TiltAbs
        {
            get { return tiltAbs; }
            set { tiltAbs = value; }
        }

        /*
        public int ID
        { get; set; }
        public string Name
        { get; set; }
        public int Sec
        { get; set; }
        public float X
        { get; set; }
        public float Y
        { get; set; }
        public float Zoom
        { get; set; }
        public string Group
        { get; set; }
        */
        public static readonly string STR_ID = "ID";
        public static readonly string STR_NAME = "NAME";
        public static readonly string STR_SEC = "SEC";
        public static readonly string STR_X = "X";
        public static readonly string STR_Y = "Y";
        public static readonly string STR_ZOOM = "ZOOM";
        public static readonly string STR_GROUP = "GROUP";

      /*
        public float PanAbs { get; set; }
        public float TiltAbs { get; set; }
        public float PanRel { get; set; }
        public float TiltRel { get; set; }
        public int TargetDistance { get; set; }
        public string TargetLatitude { get; set; }
        public string TargetLongitude { get; set; }

        public string PathImg1 { get; set; }
        public string PathImg2 { get; set; }
        */
        public static readonly string STR_PANABS = "PANABS";
        public static readonly string STR_TILTABS = "TILTABS";
        public static readonly string STR_PANREL = "PANREL";
        public static readonly string STR_TILTREL = "TILTREL";

        public static readonly string STR_TARDIST = "TARDIST";
        public static readonly string STR_TARLONG = "TARLONG";
        public static readonly string STR_TARLAT = "TARLAT";

        public static readonly string STR_PATHIMG1 = "PATHIMG1";
        public static readonly string STR_PATHIMG2 = "PATHIMG2";





    }
}
