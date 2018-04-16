using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.Diagnostics;


namespace ThreadTest_0416
{
    class Program:Form
    {
        private TextBox textBox1;
        #region 풀을 이용한 쓰레드
        //static int i = 0;

        //// 첫번째 스레드
        //public static void Print1(object obj)
        //{
        //    for (i = 0; i < 3; i++)
        //    {
        //        Console.WriteLine("첫번째 Thread : {0} ***", i);
        //        Thread.Sleep(100);
        //    }
        //}

        //// 두번째 스레드
        //public void Print2(object obj)
        //{
        //    for (i = 0; i < 3; i++)
        //    {
        //        Console.WriteLine("두번째 Thread : {0} ***", i);
        //        Thread.Sleep(100);
        //    }
        //}

        //static void Main(string[] args)
        //{
        //    // static method를 이용한 ThreadPool에대한 작업 요청
        //    ThreadPool.QueueUserWorkItem(new WaitCallback(Print1), null);

        //    // method를 이용한 ThreadPool에대한 작업 요청
        //    ThreadPool.QueueUserWorkItem(new WaitCallback(
        //        (new Program()).Print2), null);

        //    for (int i = 0; i < 10; i++)
        //    {
        //        Console.WriteLine("main : {0}", i);
        //        Thread.Sleep(100);

        //    }
        //}
        #endregion

        #region Thread use Timer
        //public static void Print1(object obj)
        //{
        //    Console.WriteLine("첫 번째 Thread : ***");
        //}

        //public void Print2(object obj)
        //{
        //    Console.WriteLine("두 번째 Thread : ***");
        //}

        //public static void Main()
        //{
        //    // timer를 이용해 0.2초마다 static 형 Print1메서드 호출 // (?,?,딜레이 시간, 간격)
        //    System.Threading.Timer timer = new System.Threading.Timer(new TimerCallback(Print1), null, 0, 100);

        //    // 0.2초마다 Print2 메서드 호출
        //    timer = new System.Threading.Timer(new TimerCallback((new Program()).Print2), null, 0, 200);

        //    Thread.Sleep(2000);   // Main 스레드를 곧바로 종료하지 않고 0.5초간 중지시킴

        //    timer.Dispose();  //Timer 를 종료
        //}
        #endregion

        #region Find Current Process List 
        //public static void Main()
        //{
        //    try
        //    {
        //        Process proc = Process.GetCurrentProcess();  // 현재 파일 즉, ProcessInfo 의 
        //        string processName = proc.ProcessName;     // 프로세스 정보 얻어옴  
        //        DateTime startTime = proc.StartTime;        // 프로세스 시작 시간
        //        int proID = proc.Id;                           // 프로세스 PID(운영체제 식별번호)
        //        int memory = proc.VirtualMemorySize;        // 메모리 사용량

        //        Console.WriteLine("******* 현재 프로세스 정보 *****");
        //        Console.WriteLine(" Process: {0}\n ID: {1}\n 시작시간: {2}\n 메모리:{3}\n",
        //                processName, proID, startTime, memory);


        //        Console.WriteLine("\n******* 모든 프로세스 정보 *****");
        //        Process[] allProc = Process.GetProcesses();  // 시스템에서 실행되는 모든 프로세스
        //        Console.WriteLine("시스템에서 실행중인 프로세스의 수: {0}", allProc.Length);
        //        int index = 1;  // 프로세스 번호 출력

        //        foreach (Process pro in allProc)
        //        {
        //            Console.WriteLine("***** {0}번째 프로세스 *****", index++);
        //            processName = pro.ProcessName;    // 프로세스 이름
        //            startTime = pro.StartTime;         // 프로세스 시작시간
        //            proID = pro.Id;                 // 프로세스 PID
        //            memory = pro.VirtualMemorySize; // 메모리 사용량

        //            Console.WriteLine(" Process: {0}\n ID: {1}\n 시작시간: {2}\n 메모리:{3}\n",
        //                    processName, proID, startTime, memory);
        //        }
        //    }
        //    catch (Exception e)
        //    {
        //        Console.WriteLine("프로세스 검사도중 예외 발생!!!");
        //        Console.WriteLine(e.Message);
        //    }
        //}
        #endregion

        #region Find Thread List & Process List
        //public static void Main()
        //{

        //    Process proc = Process.GetCurrentProcess();    // 현재 프로세스 정보 가져오기
        //    ProcessThreadCollection ths = proc.Threads;    // 스레드 정보 가져오기

        //    int threadID;                                  // 스레드 ID 번호
        //    DateTime startTime;                            // 스레드 시작 시간  
        //    int priority;                                  // 스레드 우선순위
        //    System.Diagnostics.ThreadState thstate;                           // 스레드 상태 

        //    int index = 1;                                  // 스레드 번호 출력 

        //    Console.WriteLine(" 현재 프로세스에서 실행중인 스레드 수: " + ths.Count);

        //    foreach (ProcessThread pth in ths)
        //    {
        //        threadID = pth.Id;
        //        startTime = pth.StartTime;
        //        priority = pth.BasePriority;
        //        thstate = pth.ThreadState;

        //        Console.WriteLine("******* {0} 스레드 정보 *****", index++);
        //        Console.WriteLine(" ID: {0}\n 시작시간: {1}\n Priority: {2}\n 스레드 상태:{3}\n",
        //                threadID, startTime, priority, thstate);
        //    }
        //}




        #endregion

        #region Thread State Control

        //public static void Print()    // 스레드로 실행될 메서드
        //{
        //    try
        //    {
        //        for (int i = 0; i < 1000; i++)
        //        {
        //            Console.WriteLine(" Print 스레드 : {0} ", i);
        //        }
        //    }
        //    catch (ThreadAbortException ex)
        //    {
        //        Console.WriteLine("스레드 에러: " + ex.Message);
        //    }
        //}

        //public static void TInfo(Thread th)
        //{
        //    Console.WriteLine("Thread ID : {0} \t 상태 : {1}", th.GetHashCode(), th.ThreadState);
        //}

        //public static void Main()
        //{
        //    string msg = null;   // 스레드 정보를 출력할 문자열 

        //    Thread th = new Thread(new ThreadStart(Print));
        //    TInfo(th);    // 스레드 정보 출력

        //    th.Start();           // 스레드 시작 (Stated 상태로 변화됨)
        //    Thread.Sleep(100);  // th 스레드가 시작될 때까지 잠시 대기함
        //    TInfo(th);           // 스레드 상태가 UnStarted에서 Started로 변경

        //    th.Suspend();        // 스레드 Suspend(일시정지) 
        //    Thread.Sleep(100);  // 스레드가 일시 정지될 시간적 여유를 줌

        //    // 콘솔 화면은 Print 스레드가 사용하기 때문에 MessageBox로 화면에 스레드 정보 출력
        //    msg = "Thread ID :" + th.GetHashCode() + "\t 상태 : " + th.ThreadState.ToString();
        //    System.Windows.Forms.MessageBox.Show(msg);
            
        //    th.Resume();            // Suspend 상태 스레드를 깨움
        //    Thread.Sleep(100);      // Resume 이 적용될 시간적 여유를 줌

        //    msg = "Thread ID :" + th.GetHashCode() + "\t 상태 : " + th.ThreadState.ToString();
        //    System.Windows.Forms.MessageBox.Show(msg);

        //    th.Abort();              // 스레드 종료 메시지 
        //    th.Join();               // 스레드가 완전히 정지될 때까지 기다림

        //    TInfo(th);         // 스레드 상태 정보 출력
        //}
        #endregion

        private void InitializeComponent()
        {
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // textBox1
            // 
            this.textBox1.AutoCompleteCustomSource.AddRange(new string[] {
            "asd",
            "asd",
            "asd",
            "asd"});
            this.textBox1.Location = new System.Drawing.Point(107, 60);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 25);
            this.textBox1.TabIndex = 0;
            this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // Program
            // 
            this.ClientSize = new System.Drawing.Size(282, 253);
            this.Controls.Add(this.textBox1);
            this.Name = "Program";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            
        }
    }
}
