using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

//add using
using System.Runtime.InteropServices;

using System.Diagnostics;



namespace DLLInjection_0515
{
    public partial class Form1 : Form
    {
        #region dll 임포트

        /*
         IntPtr 은 c#용 포인터
             */
        //add member 
        [DllImport("kernel32")]
        public static extern IntPtr LoadLibrary(String fileName);
        [DllImport("kernel32.dll")]
        static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, IntPtr dwSize, uint Alloc_T, uint old_P);
        [DllImport("kernel32.dll")]
        static extern int WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] buffer, uint size, out int w_b);
        [DllImport("kernel32.dll")]
        static extern int CloseHandle(IntPtr hObject);
        [DllImport("kernel32.dll")]
        static extern IntPtr GetProcAddress(IntPtr hModule, string lpProcName);
        [DllImport("kernel32.dll")]
        static extern IntPtr GetModuleHandle(string lpModuleName);
        [DllImport("kernel32.dll")]
        static extern IntPtr CreateRemoteThread(IntPtr hProcess, IntPtr lpThreadAttribute, IntPtr dwStackSize, IntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, IntPtr lpThreadId);
        [DllImport("kernel32")]
        public static extern uint GetLastError();


        #endregion

        IntPtr INTPTR_ZERO = (IntPtr)0;
        Process starcraft;

        private void MsgBox(string msg)
        {
            MessageBox.Show(msg);
        }

        //add method
        private void dllInjection(object o, EventArgs e)
        {
            getStarcraft();
            string dll_path = Application.StartupPath + "\\Dll1.dll";//startuppath 응용프로그램을 시작한 실행 파일의 경로를 가져옵니다.

            //자신의 프로세스의 로드된 kernel32.dll에 있는 LoadLivrary 함수의 주소를 가져온다.
            IntPtr LoadLibraryAddress = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
            if (LoadLibraryAddress == INTPTR_ZERO)
            {
                MsgBox("GetProcAddress  에서 오류가 났습니다.");
                return;
            }
            //스타크래프트 프로세스의 빈 메모리 주소 공간를 0으로 할당
            IntPtr DLLPath_Address = VirtualAllocEx(starcraft.Handle, INTPTR_ZERO, (IntPtr)dll_path.Length, (0x1000 | 0x2000), 0x40);//0x1000 커밋, 0x2000예약 ???
            if(DLLPath_Address == INTPTR_ZERO)
            {
                MsgBox("VirtualAllocEx 에서 오류가 났습니다.");
                return;
            }
            //경로를 바이트화시키는 코드
            byte[] bytes = Encoding.ASCII.GetBytes(dll_path);
            int a;
            //0으로 초기화 한 메모리에 자신의 데이터를 넘김
            //(프로세스 핸들,주소,넘길 데이터, 데이터의 크기,기타)
            if(WriteProcessMemory(starcraft.Handle,DLLPath_Address,bytes,(uint)bytes.Length,out a)==0)
            {
                MsgBox("WriteProcessMemory 에서 오류가 났습니다.");
                return;
            }

            if(CreateRemoteThread(starcraft.Handle,INTPTR_ZERO,INTPTR_ZERO,LoadLibraryAddress,DLLPath_Address,0,INTPTR_ZERO)==INTPTR_ZERO)
            {
                MsgBox("CreateRemoteThread 에서 오류가 났습니다.");
                return;
            }

            CloseHandle(starcraft.Handle);
        }

        

        private void getStarcraft()
        {
            listBox1.Items.Clear();
            foreach (Process pro in Process.GetProcesses())
            {
                
                listBox1.Items.Add(pro.ProcessName);
                //MessageBox.Show(pro.ProcessName);
                if(pro.ProcessName == "notepad") // 프로세스의 이름 비교
                {
                    starcraft = pro;
                }
            }
        }

        public Form1()
        {
            InitializeComponent();
        }
    }
}
