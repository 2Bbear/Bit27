using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PowoerPoint_0413
{
    //Delegate 
    public delegate void CreateEvent(object obj, PowerPointCreateLogEventArg e);
    public delegate void DeleteEvent(object obj, PowerPointDeleteLogEventArg e);
    public delegate void EditEvent(object obj, PowerPointEditLogEventArg e);
    //EventClass
    public class PowerPointCreateLogEventArg : EventArgs
    {

        private PowerPoint ppt;
        private DateTime logtime;

        
        public DateTime Logtime { get => logtime; private set => logtime = value; }
        internal PowerPoint Ppt { get => ppt; set => ppt = value; }

        internal PowerPointCreateLogEventArg(PowerPoint _ppt)
        {
            ppt = _ppt;
            Logtime = DateTime.Now;
        }
    }
    public class PowerPointDeleteLogEventArg : EventArgs
    {

        private PowerPoint ppt;
        private DateTime logtime;


        public DateTime Logtime { get => logtime; private set => logtime = value; }
        internal PowerPoint Ppt { get => ppt; set => ppt = value; }

        internal PowerPointDeleteLogEventArg(PowerPoint _ppt)
        {
            ppt = _ppt;
            Logtime = DateTime.Now;
        }
    }
    public class PowerPointEditLogEventArg : EventArgs
    {

        private PowerPoint ppt;
        private DateTime logtime;


        public DateTime Logtime { get => logtime; private set => logtime = value; }
        internal PowerPoint Ppt { get => ppt; set => ppt = value; }

        internal PowerPointEditLogEventArg(PowerPoint _ppt)
        {
            ppt = _ppt;
            Logtime = DateTime.Now;
        }
    }

    class PowerPointLog
    {
        #region SingleTone
        private static PowerPointLog singletone;
        public List<String> logList=new List<String>();

        internal static PowerPointLog Singletone { get => singletone; private set => singletone = value; }

        private PowerPointLog()
        {
            //Binding
            Control control = Control.SingleTone;
            control.CreatePPT += CreatePPTEventHandler;
            control.DeletePPT += DeletePPTEventHandler;
            control.EditPPT += EditPPTEventHandler;
            //list Init
            LoadLogListFile();
        }
        static PowerPointLog()
        {
            Singletone = new PowerPointLog();
        }
        #endregion
       

        public void CreatePPTEventHandler(object obj, PowerPointCreateLogEventArg e)
        {
            string str = string.Format(
               " [PPT 생성로그] 파일명 : {0} 시간 : {1}", e.Ppt.FileName,e.Logtime);
            //저장
            logList.Add(str);
            SaveLogListFile();
            Console.WriteLine(str);
        }
        public void DeletePPTEventHandler(object obj, PowerPointDeleteLogEventArg e)
        {
            string str = string.Format(
              " [PPT 삭제로그] 파일명 : {0} 시간 : {1}", e.Ppt.FileName, e.Logtime);
            //저장
            logList.Add(str);
            SaveLogListFile();
            Console.WriteLine(str);
        }
        public void EditPPTEventHandler(object obj, PowerPointEditLogEventArg e)
        {
            string str = string.Format(
              " [PPT 수정로그] 파일명 : {0} 시간 : {1}", e.Ppt.FileName, e.Logtime);
            //저장
            logList.Add(str);
            SaveLogListFile();
            Console.WriteLine(str);
        }

        private void SaveLogListFile()
        {
            FileIOControl.SaveFile(logList);
        }
        private void LoadLogListFile()
        {
            FileIOControl.LoadFile(logList);
        }

    }
}
