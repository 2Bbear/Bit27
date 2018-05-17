using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Automation;

namespace WMPRemoteControl_0516
{
    /// <summary>
    /// InvokePattern의 자동화 요소 래핑 클래스
    /// </summary>
    public class WrapInvoke
    {
        public static int increase = 0;
        int buttonID;
        /// <summary>
        /// 자동화 요소 - 가져오기
        /// </summary>
        public AutomationElement AE { get; private set; }
        /// <summary>
        /// 자동화 요소의 이름 - 가져오기
        /// </summary>
        public string Name
        {
            get
            {
                return AE.Current.Name;
            }
        }
        /// <summary>
        /// 자동화 요소의 지역화 컨트롤 타입명 - 가져오기
        /// </summary>
        public string ControlType
        {
            get
            {
                return AE.Current.LocalizedControlType;
            }
        }
        /// <summary>
        /// 생성자
        /// </summary>
        /// <param name="ae">래핑할 자동화 요소</param>
        public WrapInvoke(AutomationElement ae)
        {
            AE = ae;
            buttonID = increase;
            increase++;
        }
        /// <summary>
        /// 래핑한 InvokePattern의 Invoke 메서드 호출
        /// </summary>
        public void Invoke()
        {
            try
            {
                InvokePattern inv_pat = AE.GetCurrentPattern(
                                       InvokePattern.Pattern) as InvokePattern;
                inv_pat.Invoke();
            }
            catch { }
        }
        /// <summary>
        /// ToString 메서드 재정의
        /// </summary>
        /// <returns>ControlType 속성과 Name 속성을 합한 문자열</returns>
        public override string ToString()
        {
            return ControlType + ":" + Name;
        }
    }
}
