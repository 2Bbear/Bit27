using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Forms;
using System.Threading;

namespace WMPRemoteControl_0516
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {


        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            PlayButton("", "");
            //WMPProcess t1 = new WMPProcess();
            //t1.StartProgram();
            //t1.FindProcess();
            //t1.SendMessageProcess();
        }

        AutomationEventHandler MyEventHandler;
       

        //lbox_process 리스트의 현재 선택된 인덱스의 요소를 반환한다.
        private WrapInvoke SelectedWrapAE()
        {
            if (lbox_process.SelectedIndex == -1)
            {
                return null;
            }

            WrapProcess wp = lbox_process.SelectedItem as WrapProcess;
            AutomationElement ae = wp.RootElement;
            return new WrapInvoke(ae);
        }

       

        delegate void MyDele(AutomationElement ae);
        //이 이벤트 추가 되었을 때
        private void AddEvent(AutomationElement ae)
        {
            //System.Windows.Forms.ListBox dd= new System.Windows.Forms.ListBox();

            //만약 리스트 상자의 InvokeRequired 속성이 참이면 현재 수행하는 스레드와 리스트 상자의 스레드가 서로 다름을 의미합니다. 
            //이 때는 인자를 object 배열 개체로 생성하고 대리자 개체를 생성하여 리스트 상자의 Invoke 메서드를 호출합니다.
            //이는 Windows Forms 응용 프로그램의 어떠한 컨트롤에서도 같은 방법으로 크로스 스레드 문제를 해결할 수 있습니다.
            if (Dispatcher.CheckAccess())//lbox_history.InvokeRequired
            {
                object[] objs = new object[1] { ae };
                lbox_history.Dispatcher.Invoke(new MyDele(AddEvent), objs);
            }
            else
            {
                lbox_history.Items.Add(ae.Current.Name + " 클릭");
            }
        }

        /// <summary>
        /// 모든 프로세스를 받아오는 메소드
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btn_refresh_Click(object sender, RoutedEventArgs e)
        {
            lbox_process.Items.Clear();
            Process[] processes = Process.GetProcesses();

            foreach (Process pro in processes)
            {
                if (pro.MainWindowHandle != IntPtr.Zero)
                {
                    //리스트에 wrapprocess형태를 계속 담음
                    lbox_process.Items.Add(new WrapProcess(pro));
                }
            }
        }

        private void lbox_process_SelectedIndexChanged(object sender, SelectionChangedEventArgs e)
        {
            //list 항목 재 설정
            lbox_inv_elem.Items.Clear();
            //프로세스 리스트 상자의 서택 항목에서 래핑한 invokepattern 자동화 요소 개체를 얻어온다.
            WrapInvoke wae = SelectedWrapAE();
            if (wae == null)
            {
                return;
            }
            //Automation 클래스 이벤트 핸들러에 커스텀으로 만든 이벤트 핸들러 메소드를 연결 시킨다. (인보크패턴,target프로그램의 WrapInvoke.AE , ??? , 자신이 만든 핸들러 )
            Automation.AddAutomationEventHandler(InvokePattern.InvokedEvent,wae.AE, TreeScope.Subtree,MyEventHandler = new AutomationEventHandler(OnUIAutomationEvent));

            System.Windows.Automation.Condition cond = new PropertyCondition(AutomationElement.IsInvokePatternAvailableProperty, true);
            //해당 프로세스의 모든 ui를 Collection 형태로 받아옴
            AutomationElementCollection aec = wae.AE.FindAll(TreeScope.Subtree, cond);

            //선택된 프로세스에 대해서 모든 ui를 리스트에 추가하는 과정
            foreach (AutomationElement ae in aec)
            {
                lbox_inv_elem.Items.Add(new WrapInvoke(ae));
            }
        }
        //Invoke관련 이벤트를 감지하였을 때 처리할 이벤트 핸들러를 정의한 메소드
        private void OnUIAutomationEvent(object src, AutomationEventArgs e)
        {
            AutomationElement ae = src as AutomationElement;
            AddEvent(ae);
        }

        //lbox_inv_elem 의 요소가 선택되었을 때
        private void lbox_inv_elem_SelectedIndexChanged(object sender, SelectionChangedEventArgs e)
        {
            //선택 항목이 없으면 이벤트 핸들러를 종료합니다.
            if (lbox_inv_elem.SelectedIndex == -1)
            {
                return;
            }
            //선택항목을 WrapInvoke 형식으로 참조하여 Invoke 메서드를 호출합니다.
            WrapInvoke winvoke = lbox_inv_elem.SelectedItem as WrapInvoke;
            winvoke.Invoke();
        }

        private void PlayButton(string filename, string arg)
        {
            //Process 찾기
            Process target_Process;
            ProcessStartInfo psi;
            if (arg.Length != 0)
            {
                psi = new ProcessStartInfo("C:\\Program Files (x86)\\Windows Media Player\\wmplayer.exe", arg);
            }

            else
                psi = new ProcessStartInfo("C:\\Program Files (x86)\\Windows Media Player\\wmplayer.exe");



            target_Process = Process.Start(psi);
            Thread.Sleep(500);
            //찾은 Process
            //wrapprocess형태를 담음
            WrapProcess target_WrapProcess = new WrapProcess(target_Process);

            AutomationElement target_AutomationElement = target_WrapProcess.RootElement;

            WrapInvoke target_WrapInvoke = new WrapInvoke(target_AutomationElement);
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
                
                if (winvoke.ToString().Equals("단추:재생:36"))
                {
                    
                    winvoke.Invoke();
                }
            }



        }
        //Invoke관련 이벤트를 감지하였을 때 처리할 이벤트 핸들러를 정의한 메소드
        private void MyOnUIAutomationEvent(object src, AutomationEventArgs e)
        {
            AutomationElement ae = src as AutomationElement;
            AddEvent(ae);
        }

    }
}
