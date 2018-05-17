using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Forms;

//0517
using System.Windows.Automation;


namespace WMPRemoteControl_0516
{
    class WMPProcess
    {
        [DllImport("user32.dll")]
        public static extern int FindWindow(string lpClassName, string lpWindowName);

        //[DllImport("user32.dll")]
        //public static extern int FindWindowEx(int hWnd1, int hWnd2, string lpsz1, string lpsz2);
        [DllImport("user32.dll")]
        public static extern IntPtr FindWindowEx(IntPtr hwndParent, IntPtr hwndChildAfter, string lpszClass, string lpszWindow);
        [DllImport("user32")]
        public static extern int SendMessage(int hwnd, int wMsg, int wParam, int lParam);
        //[DllImport("User32.dll")]
        //public static extern int SendMessage(IntPtr hWnd, int uMsg, int wParam, int lParam);

        [DllImport("USER32.DLL")]
        public static extern bool SetForegroundWindow(int hWnd);

        Process targetprocess=null;
        int targetprocess_int = 0;
        public void FindProcess()
        {
            targetprocess_int=FindWindow(null,"Windows Media Player");
            //MessageBox.Show(targetprocess_int.ToString());
        }
        public void StartProgram()
        {
            doProgram("C:\\Program Files (x86)\\Windows Media Player\\wmplayer.exe", "");
        }
        static Process temp;
        // 프로세스 실행
        private static void doProgram(string filename, string arg)
        {
            ProcessStartInfo psi;
            if (arg.Length != 0)
            {
                psi = new ProcessStartInfo(filename, arg);
            }

            else
                psi = new ProcessStartInfo(filename);



            temp = Process.Start(psi);


        }
        public void SendMessageProcess()
        {
            //SetForegroundWindow(targetprocess_int);
            ////SendKeys.SendWait("^p");
            //Thread.Sleep(500);
            //SendKeys.SendWait("^3");
            //Thread.Sleep(500);
            //SendKeys.SendWait("{TAB}");
            //Thread.Sleep(500);
            //SendKeys.SendWait("{ENTER}");



        }

    }
}
