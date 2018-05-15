using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace WMP_RemoteControl
{
    class NotePadProcess
    {
        #region Imports
        [DllImport("user32.dll")]
        public static extern IntPtr FindWindowEx(IntPtr hwndParent, IntPtr hwndChildAfter, string lpszClass, string lpszWindow);

        [DllImport("User32.dll")]
        private static extern int SendMessage(IntPtr hWnd, int uMsg, int wParam, string lParam);

        //this is a constant indicating the window that we want to send a text message
        const int WM_SETTEXT = 0X000C;
        #endregion


        public Process StartProgram(string insulttxt)
        {
            Process notepad = Process.Start(@"notepad.exe");
            System.Threading.Thread.Sleep(500);
            IntPtr notepadTextbox = FindWindowEx(notepad.MainWindowHandle, IntPtr.Zero, "Edit", null);
            //SendMessage(notepadTextbox, Convert.ToInt32("0X000C",16), 0, insulttxt);
            SendMessage(notepadTextbox, 0X000C, 0, insulttxt);
            return notepad;
            //SendMessage(notepadTextbox, WM_SETTEXT, 0, insulttxt);
            //SendMessage(notepadTextbox, 0101, Convert.ToInt32("00000044",16), "C0200001");
        }
    }
}
