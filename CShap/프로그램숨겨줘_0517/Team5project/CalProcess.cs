using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;

namespace Team5project
{
    class CalProcess
    {
        #region DllImport
        [DllImport("user32.dll")]
        public static extern int FindWindow(string lpClassName, string lpWindowName);
        [DllImport("user32.dll")]
        public static extern IntPtr FindWindowEx(int hwndParent, int hwndChildAfter, string lpszClass, string lpszWindow);

        [DllImport("User32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int uMsg, int wParam, int lParam);

        #endregion

        #region 멤버 변수
        //실행될 프로그램의 프로세스
        Process thisprocess = null;
        int hwnd = 0;
        const int BM_CLICK = 0x00F5;
        string programpath = @"D:\calc2.exe";
        #endregion

        #region 생성자
        public CalProcess()
        {
            Thread.Sleep(500);
            
            //hwnd = FindWindow("SciCalc", null);
            
        }
        public CalProcess(Process _proc,int _hwnd)
        {
            Thread.Sleep(500);
            thisprocess = _proc;
            hwnd = _hwnd;
            //hwnd = FindWindow("SciCalc", null);
            if (thisprocess==null)
            {
                throw new Exception(" thisprocess Process 복사에 실패 했습니다.");
            }
            if(hwnd==0)
            {
                throw new Exception("계산기의 핸들값이 잡히지가 않습니다.");
            }
        }
        #endregion

        #region 외부 접근 메소드
        /// <summary>
        /// 문자열에 따른 프로그램 행동을 정의하는 메소드
        /// </summary>
        /// <param name="_act"></param>
        public void Action(string _act)
        {
            try
            {
                switch (_act)
                {
                    #region 숫자 번호
                    case "일":
                        {
                            SendMessage(FindWindowEx(hwnd, 0, "Button", "1"), BM_CLICK, 0, 1);
                            
                            break;
                        }
                    case "이":
                        {
                            SendMessage(FindWindowEx(hwnd, 0, "Button", "2"), BM_CLICK, 0, 1);
                            break;
                        }
                    case "삼":
                        {
                            SendMessage(FindWindowEx(hwnd, 0, "Button", "3"), BM_CLICK, 0, 1);
                            break;
                        }
                    case "사":
                        {
                            SendMessage(FindWindowEx(hwnd, 0, "Button", "4"), BM_CLICK, 0, 1);
                            break;
                        }
                    case "오":
                        {
                            SendMessage(FindWindowEx(hwnd, 0, "Button", "5"), BM_CLICK, 0, 1);
                            break;
                        }
                    case "육":
                        {
                            SendMessage(FindWindowEx(hwnd, 0, "Button", "6"), BM_CLICK, 0, 1);
                            break;
                        }
                    case "칠":
                        {
                            SendMessage(FindWindowEx(hwnd, 0, "Button", "7"), BM_CLICK, 0, 1);
                            break;
                        }
                    case "팔":
                        {
                            SendMessage(FindWindowEx(hwnd, 0, "Button", "8"), BM_CLICK, 0, 1);
                            break;
                        }
                    case "구":
                        {
                            SendMessage(FindWindowEx(hwnd, 0, "Button", "9"), BM_CLICK, 0, 1);
                            break;
                        }
                    case "영":
                        {
                            SendMessage(FindWindowEx(hwnd, 0, "Button", "0"), BM_CLICK, 0, 1);
                            break;
                        }
                    #endregion

                    #region 사칙연산
                    case "더하기":
                        {
                            SendMessage(FindWindowEx(hwnd, 0, "Button", "+"), BM_CLICK, 0, 1);
                            break;
                        }
                    case "빼기":
                        {
                            SendMessage(FindWindowEx(hwnd, 0, "Button", "-"), BM_CLICK, 0, 1);
                            break;
                        }
                    case "나누기":
                        {
                            SendMessage(FindWindowEx(hwnd, 0, "Button", "/"), BM_CLICK, 0, 1);
                            break;
                        }
                    case "곱하기":
                        {
                            SendMessage(FindWindowEx(hwnd, 0, "Button", "*"), BM_CLICK, 0, 1);
                            break;
                        }
                    case "결과":
                        {
                            SendMessage(FindWindowEx(hwnd, 0, "Button", "="), BM_CLICK, 0, 1);
                            break;
                        }
                    #endregion

                    #region 기능키
                    case "지워":
                        {
                            SendMessage(FindWindowEx(hwnd, 0, "Button", "Backspace"), BM_CLICK, 0, 1);
                            break;
                        }
                    case "초기화":
                        {
                            SendMessage(FindWindowEx(hwnd, 0, "Button", "C"), BM_CLICK, 0, 1);
                            break;
                        }
                    case "소수점":
                        {
                            SendMessage(FindWindowEx(hwnd, 0, "Button", "."), BM_CLICK, 0, 1);
                            break;
                        }
                    
                        #endregion
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            finally
            {
            }
            
        }
        #endregion

        #region 내부 접근 메소드
        
        private  void StartProcess()
        {
            System.Diagnostics.Process abc = new System.Diagnostics.Process();
            abc.StartInfo.UseShellExecute = false;
            abc.StartInfo.FileName = programpath;
            abc.Start();

            Thread.Sleep(500);//프로세스가 온전히 실행 되기 까지 기다림
            hwnd = abc.HandleCount;
        }
       
        
        #endregion

    }
}
