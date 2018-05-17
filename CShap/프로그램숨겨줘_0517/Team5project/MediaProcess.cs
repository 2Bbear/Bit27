using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Automation;
using System.Windows.Forms;
using WMPRemoteControl_0516;

namespace Team5project
{
    class MediaProcess
    {
        #region DllImport
        [DllImport("user32.dll")]
        public static extern int FindWindow(string lpClassName, string lpWindowName);

        [DllImport("USER32.DLL")]
        public static extern bool SetForegroundWindow(int hWnd);
        #endregion

        #region 생성자
        int hwnd;
        Process thisproc;

        public MediaProcess()
        {
            hwnd = FindWindow(null, "Windows Media Player");
        }
        public MediaProcess(Process _proc,int _hwnd)
        {
            thisproc = _proc;
            hwnd = _hwnd;
        }
        #endregion
        
        public void Action(string _act)
        {
            switch (_act)
            {
                case "처음재생":
                    {
                        SetForegroundWindow(hwnd);
                        Thread.Sleep(500);
                        SendKeys.SendWait("^3");
                        Thread.Sleep(500);
                        SendKeys.SendWait("\t"); Thread.Sleep(100);
                        SendKeys.SendWait("{ENTER}");
                        break;
                    }
                case "재생":
                    {
                        WrapProcess target_WrapProcess = new WrapProcess(thisproc);

                        AutomationElement target_AutomationElement = target_WrapProcess.RootElement;

                        WrapInvoke target_WrapInvoke = new WrapInvoke(target_AutomationElement);
                        bool flag = false;
                        if (target_WrapInvoke == null)
                        {
                            return;
                        }

                        System.Windows.Automation.Condition cond = new PropertyCondition(AutomationElement.IsInvokePatternAvailableProperty, true);
                        //해당 프로세스의 모든 ui를 Collection 형태로 받아옴
                        AutomationElementCollection aec = target_WrapInvoke.AE.FindAll(TreeScope.Subtree, cond);
                       
                        //선택된 프로세스에 대해서 모든 ui를 리스트에 추가하는 과정
                        foreach (AutomationElement ae in aec)
                        {
                            WrapInvoke winvoke = new WrapInvoke(ae);
                            //lbox_inv_elem.Items.Add(new WrapInvoke(ae));
                            if(winvoke.ToString().Equals("단추:재생") && flag == false)
                            {
                                flag = true;
                            }
                            if (winvoke.ToString().Equals("단추:재생") && flag == true)
                            {
                                
                                
                                winvoke.Invoke();
                                


                            }
                        }
                        WrapInvoke.increase = 0;

                        //SetForegroundWindow(hwnd);
                        //Thread.Sleep(500);
                        //SendKeys.SendWait("^p");
                        break;
                    }
                case "일시정지":
                    SetForegroundWindow(hwnd);
                    Thread.Sleep(500);
                    SendKeys.SendWait("^p");
                    break;
                case "중지":
                    SetForegroundWindow(hwnd);
                    Thread.Sleep(500);
                    SendKeys.SendWait("^s");
                    break;
                case "재생속도 빠름":
                    SetForegroundWindow(hwnd);
                    Thread.Sleep(500);
                    SendKeys.SendWait("^+g");
                    break;
                case "재생속도 보통":
                    SetForegroundWindow(hwnd);
                    Thread.Sleep(500);
                    SendKeys.SendWait("^+n");
                    break;
                case "재생속도 느림":
                    SetForegroundWindow(hwnd);
                    Thread.Sleep(500);
                    SendKeys.SendWait("^+s");
                    break;
                case "이전":
                    SetForegroundWindow(hwnd);
                    Thread.Sleep(500);
                    SendKeys.SendWait("^b");
                    break;
                case "다음":
                    SetForegroundWindow(hwnd);
                    Thread.Sleep(500);
                    SendKeys.SendWait("^f");
                    break;
                case "되감기":
                    SetForegroundWindow(hwnd);
                    Thread.Sleep(500);
                    SendKeys.SendWait("^+b");
                    break;
                case "빨리감기":
                    SetForegroundWindow(hwnd);
                    Thread.Sleep(500);
                    SendKeys.SendWait("^+f");
                    break;
                case "순서섞기":
                    SetForegroundWindow(hwnd);
                    Thread.Sleep(500);
                    SendKeys.SendWait("^h");
                    break;
                case "반복":
                    SetForegroundWindow(hwnd);
                    Thread.Sleep(500);
                    SendKeys.SendWait("^t");
                    break;
                case "볼륨 크게":
                    SetForegroundWindow(hwnd);
                    Thread.Sleep(500);
                    SendKeys.SendWait("{F9}");
                    break;
                case "볼륨 작게":
                    SetForegroundWindow(hwnd);
                    Thread.Sleep(500);
                    SendKeys.SendWait("{F8}");
                    break;
                case "음소거":
                    SetForegroundWindow(hwnd);
                    Thread.Sleep(500);
                    SendKeys.SendWait("{F7}");
                    break;
            }
        }
    }

}
