using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WMP_RemoteControl
{
    class NomalProcesscs
    {
        //dll
        #region 일반 process 접근용
        [DllImport("user32.dll")]
        public static extern int FindWindow(string lpClassName, string lpWindowName); // 현재 켜져있는 프로세스 검색
        [DllImport("user32.dll")]
        public static extern int FindWindowEx(int hWnd1, int hWnd2, string lpsz1, string lpsz2); // 해당 프로세스 내부에 있는 자식 프로세스 검색
        [DllImport("user32")]
        public static extern int SendMessage(int hwnd, int wMsg, int wParam, int lParam); // 메세지 보내는 함수
        #endregion


        //title bar name으로 현재 윈도우를 찾는 함수
        private void StartProgram(string programpath)
        {
            int nhwnd = FindWindow(null, programpath);    // 윈도우 창 제목
            MessageBox.Show(nhwnd.ToString());

            int hw1 = FindWindowEx(nhwnd, 0, "Edit", "");
            MessageBox.Show(hw1.ToString());
            SendMessage(hw1, 0X000C, 0, 0);
        }
    }
    
}

