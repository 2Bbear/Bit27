using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Automation;

namespace WMPRemoteControl_0516
{
    /// <summary>
    /// InvokePattern의 자동화 요소 래핑 클래스
    /// </summary>
    public class WrapProcess
    {
        /// <summary>
        /// Process 개체 - 가져오기
        /// </summary>
        public Process Process { get; private set; }
        /// <summary>
        /// 프로세스 이름과 메인 윈도우의 캡션 - 가져오기
        /// </summary>
        public string Title
        {
            get
            {
                return Process.ProcessName + ":" + Process.MainWindowTitle;
            }
        }
        /// <summary>
        /// 메인 윈도우와 매핑하는 자동화 요소 - 가져오기
        /// </summary>
        public AutomationElement RootElement
        {
            get
            {
                if (Process.MainWindowHandle == IntPtr.Zero)
                {
                    return null;
                }
                return AutomationElement.FromHandle(Process.MainWindowHandle);
            }
        }
        /// <summary>
        /// 생성자
        /// </summary>
        /// <param name="process">래핑할 프로세스 개체</param>
        public WrapProcess(Process process)
        {
            Process = process;
        }
        /// <summary>
        /// ToString 메서드 재정의
        /// </summary>
        /// <returns>Title 속성</returns>
        public override string ToString()
        {
            return Title;
        }
    }
}
