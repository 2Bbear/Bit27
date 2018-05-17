using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//참조-Nuget패키지관리-Microsoft.speech.11추가
using Microsoft.Speech.Recognition;
using Microsoft.Speech.Synthesis;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Windows.Threading;
using System.Threading;
using System.Windows;
using System.IO;


namespace Team5project
{
    public class Listener
    {
       
        #region DLL Import
        [DllImport("user32.dll", SetLastError = true)]      //에러처리  //현재윈도우찾기
        private static extern int FindWindow(string lpClassName, string lpWindowName);

        [DllImport("User32.dll")]    //sendMessage
        public static extern int SendMessage(IntPtr hWnd, int uMsg, int wParam, string lParam);

        [DllImport("user32.dll")]   //윈도우찾기 개량형
        public static extern IntPtr FindWindowEx(IntPtr hwndParent, IntPtr hwndChildAfter, string lpszClass, string lpszWindow);

        [DllImport("USER32.DLL")]       //윈도우 강제 활성화
        public static extern bool SetForegroundWindow(int hWnd);
        #endregion

        #region 변수 및 객체 초기화
        SpeechSynthesizer tts;                                 // tts 객체
        bool memoNew = false;                                  //메모장중복방지
        bool paintNew = false;                                 //        |
        bool calNew = false;                                   //        |
        bool consoleNew = false;                               //        |
        bool playerNew = false;                                //        |
        bool its_me = false;                                   // 명령어 인식
        int time = 20;                                         // 명령어 인식 시간
        bool say = false;
        
        int currentProcessHandle;                              //현재 프로세스 핸들값
        Process Cur_process=null;                              //현재 프로세스 정보
        DispatcherTimer mytimer = new DispatcherTimer();       //타이머 객체생성
        Help help = new Help();                                //도움말 창 객체생성

        //이렇게 하면 크게 혼납니다.
        //MainWindow main = new MainWindow();
        //-->> public Listener(MainWindow _mainwindow)처럼 넘겨받을것
        MainWindow main=null;
        #endregion

        #region 모듈 초기화
        //RS 초기화 (음성인식초기화)
        public void initRS()
        {
            try
            {
                SpeechRecognitionEngine sre = new SpeechRecognitionEngine(new CultureInfo("ko-KR"));

                Grammar g = new Grammar("input.xml");   //자동실행때는 경로 직접지정
                sre.LoadGrammar(g);

                sre.SpeechRecognized += new EventHandler<SpeechRecognizedEventArgs>(Listen);

                sre.SetInputToDefaultAudioDevice();
                sre.RecognizeAsync(RecognizeMode.Multiple);
                
            }
            catch (Exception e)
            {
                main.label1.Content = "init RS Error : " + e.ToString();
            }
        }

        //TTS 초기화 (응답초기화)
        public void initTTS()
        {
            try
            {
                tts = new SpeechSynthesizer();
                tts.SelectVoice("Microsoft Server Speech Text to Speech Voice (ko-KR, Heami)");
                tts.SetOutputToDefaultAudioDevice();
                tts.Volume = 100;
                main.voicelabel.Content = tts.Volume.ToString();

            }
            catch (Exception e)
            {
                main.label1.Content = "init TTS Error : " + e.ToString();
            }
        }

        //타이머 셋팅
        void timer_Tick(object sender, EventArgs e)
        {
            if (say == false)
            {
                if (time > 0)
                {
                    time = time - 1;
                    main.timeLabel.Content = time + " sec";
                }
                else
                {
                    mytimer.Stop();
                    main.timeLabel.Content = "대기중";
                    Thread.Sleep(1000);
                    its_me = false;
                    time = 10;
                }
            }


        }

        #endregion

        #region Listener
        public Listener(MainWindow _mainwindow)
        {
            main = _mainwindow;
            main.timeLabel.Content = "대기중";                      //라벨 초기값
            mytimer.Interval = TimeSpan.FromMilliseconds(1000);    //시간간격 설정
            mytimer.Tick += new EventHandler(timer_Tick);          //이벤트 추가
        }
        #endregion

        #region 명령어
        //음성명령
        public void Listen(object sender, SpeechRecognizedEventArgs e)
        {
            main.label1.Content = e.Result.Text;

            if (e.Result.Text == "예림이" || e.Result.Text == "예림아" || e.Result.Text == "컴퓨터")
            {
                time = 20;
                mytimer.Start();    //타이머 시작. 종료는 timer.Stop(); 으로 한다

                tts.SpeakAsync("네 부르셨나요");
                its_me = true;
                Thread.Sleep(2000);

                //1. 쓰레드로 시간 흘러가게하고
                //2. 일정시간 지나면 its_me = false;
            }
            
            //실행&닫기 코드
            if (its_me == true)
            {
                switch (e.Result.Text)
                {
                    case "안녕":
                        tts.SpeakAsync("반갑습니다 음성인식 테스트입니다");
                        break;

                    case "프로그램 종료":
                        {
                            tts.Speak("프로그램을 종료합니다");
                            Application.Current.Shutdown();
                            main.notify.Dispose();
                            break;
                        }
                    case "프로그램 숨겨줘":
                        {
                            main.Hide();
                            break;
                        }
                    case "프로그램 보여줘":
                        {
                            main.Show();
                            break;
                        }
                    //=============================================================
                    case "계산기 실행":
                        {
                            Mutex mutex = new Mutex(true, "MyMutex1", out calNew);
                            if (calNew)
                            {
                                calNew = true;
                                tts.SpeakAsync("알겠습니다");
                                doProgram("calc2.exe", "");
                                Thread.Sleep(500);
                                mutex.ReleaseMutex();
                                Cur_process.Refresh();
                                time = 30;

                                Cur_process = Process.GetProcessesByName("calc2")[0];
                                currentProcessHandle = FindWindow("SciCalc", "계산기");
                                mutex.Close();
                              //  MessageBox.Show(currentProcessHandle.ToString());
                            }
                            else
                                tts.SpeakAsync("이미 열려있습니다");
                            break;
                        }
                    case "메모장 실행":
                        {
                            Mutex mutex = new Mutex(true, "MyMutex2", out memoNew);
                            if (memoNew)
                            {
                                memoNew = true;
                                tts.SpeakAsync("알겠습니다");
                                doProgram("c:\\windows\\system32\\notepad.exe", "");
                                mutex.ReleaseMutex();
                                Cur_process.Refresh();
                                mutex.Close();
                                Thread.Sleep(500);
                                Cur_process = Process.GetProcessesByName("notepad")[0];
                                IntPtr notepadTextbox = FindWindowEx(Cur_process.MainWindowHandle, IntPtr.Zero, "Edit", null);
                                //this is a constant indicating the window that we want to send a text message
                                const int WM_SETTEXT = 0X000C;
                                //Thread.Sleep(2000);
                                SendMessage(notepadTextbox, WM_SETTEXT, 0, "Hello World!");
                            }
                            else
                                tts.SpeakAsync("이미 열려있습니다");
                            break;
                        }
                    case "콘솔 실행":
                        {
                            Mutex mutex = new Mutex(true, "MyMutex3", out consoleNew);
                            if (consoleNew)
                            {
                                mutex.Close();
                                consoleNew = true;
                                tts.SpeakAsync("알겠습니다");
                                doProgram("c:\\windows\\system32\\cmd.exe", "");
                                mutex.ReleaseMutex();
                                Cur_process.Refresh();
                            }
                            else
                                tts.SpeakAsync("이미 열려있습니다");
                            break;
                        }
                    case "그림판 실행":
                        {
                            Mutex mutex = new Mutex(true, "MyMutex4", out paintNew);
                            if (paintNew)
                            {
                                paintNew = true;
                                tts.SpeakAsync("알겠습니다");
                                doProgram("c:\\windows\\system32\\mspaint.exe", "");
                                mutex.ReleaseMutex();
                                Cur_process.Refresh();
                                mutex.Close();
                            }
                            else
                                tts.SpeakAsync("이미 열려있습니다");
                            break;
                        }
                    case "플레이어 실행":
                        {
                            Mutex mutex = new Mutex(true, "MyMutex5", out playerNew);
                            if (playerNew)
                            {
                                playerNew = true;
                                tts.SpeakAsync("알겠습니다");
                                doProgram(@"C:\Program Files (x86)\Windows Media Player/wmplayer.exe", "");
                                mutex.ReleaseMutex();
                                Cur_process.Refresh();
                            }
                            else
                                tts.SpeakAsync("이미 열려있습니다");
                            break;
                        }
                    //=================================================================
                    case "플레이어 닫기":
                        {
                            tts.SpeakAsync("종료합니다");
                            closeProcess("wmplayer");
                            playerNew = false;
                            break;
                        }
                    case "계산기 닫기":
                        {
                            tts.SpeakAsync("종료합니다");
                            closeProcess("calc2");
                            calNew = false;
                            break;
                        }
                    case "메모장 닫기":
                        {
                            tts.SpeakAsync("종료합니다");
                            closeProcess("notepad");
                            memoNew = false;
                            break;
                        }
                    case "콘솔 닫기":
                        {
                            tts.SpeakAsync("종료합니다");
                            closeProcess("cmd");
                            consoleNew = false;
                            break;
                        }
                    case "그림판 닫기":
                        {
                            tts.SpeakAsync("종료합니다");
                            closeProcess("mspaint");
                            paintNew = false;
                            break;
                        }
                    case "자기소개":
                        {
                            VoiceInfo info;
                            SpeechSynthesizer myvoice = new SpeechSynthesizer();

                            foreach (InstalledVoice sdo in myvoice.GetInstalledVoices())
                            {
                                info = sdo.VoiceInfo;
                                string gen = "";
                                if (info.Gender == VoiceGender.Male)
                                    gen = "남자";
                                else
                                    gen = "여자";
                                tts.SpeakAsync("저의 이름은 예림이 입니다.");
                                tts.SpeakAsync("Culture는 " + info.Culture + "이고");
                                tts.SpeakAsync("스물일곱살  " + gen + "입니다.");
                                tts.SpeakAsync("참고로 몸무게는 비밀입니다.");
                                tts.SpeakAsync("ID " + info.Id);
                            }
                            break;
                        }
                    case "목소리 크게":
                        {
                            if (tts.Volume == 100)
                            {
                                tts.SpeakAsync("최대크기입니다");
                            }
                            else
                            {
                                tts.Volume += 20;
                                tts.SpeakAsync("키웠습니다");
                                main.voicelabel.Content = tts.Volume.ToString();
                            }
                            break;
                        }
                    case "목소리 작게":
                        {
                            if (tts.Volume == 0)
                            {
                                tts.SpeakAsync("최소크기입니다");
                               
                            }
                            else
                            {
                                tts.Volume -= 20;
                                tts.SpeakAsync("줄였습니다");
                                main.voicelabel.Content = tts.Volume.ToString();
                            }
                            break;
                        }
                    case "목소리 최대":
                        {
                            if (tts.Volume == 100)
                            {
                                tts.SpeakAsync("이미 최대크기입니다");

                            }
                            else
                            {
                                tts.Volume = 100;
                                tts.SpeakAsync("키웠습니다");
                                main.voicelabel.Content = tts.Volume.ToString();
                            }
                            break;
                        }
                    case "목소리 최소":
                        {
                            if (tts.Volume == 0)
                            {
                                tts.SpeakAsync("이미 최소크기입니다");

                            }
                            else
                            {
                                tts.Volume = 0;
                                main.voicelabel.Content = tts.Volume.ToString();
                            }
                            break;
                        }
                    case "레지스트리 등록":
                        {
                            if (Register.AutoRegist())
                            {
                                tts.SpeakAsync("등록했습니다");
                                break;
                            }
                            tts.SpeakAsync("이미등록되어있습니다");
                            break;
                        }
                    case "레지스트리 삭제":
                        {
                            if (Register.AutoRunDisRegist())
                            {
                                tts.SpeakAsync("삭제했습니다");
                                break;
                            }
                            tts.SpeakAsync("이미삭제되어있습니다");
                            break;
                        }
                    case "도움말":
                        {
                            MessageBox.Show("늬미 도움말");
                            StreamReader text = new StreamReader(@"input.xml");
                            string str = "";
                            string chonghap = "";
                            string strback = "";
                            int index;
                            int index2;
                            bool Run = true;
                            string hap;
                            str = text.ReadToEnd();
                            //=============================
                            string str1 = str;

                            
                            if (Run)
                            {
                                
                                index = str1.IndexOf("<item>");  //검색키워드 target
                                //strback ㅣㅣ </item> 까지 
                                strback = str1.Substring(index + 6);   //뒤
                                index2 = strback.IndexOf("</item>");  //검색키워드 target
                                hap = strback.Substring(0, index2); //키워드 짤라내기
                                chonghap = hap + chonghap;
                                strback = strback.Substring(index2 + 7); //
                                Run = false;
                                
                            }
                            while (true)
                            {
                                
                                index = strback.IndexOf("<item>");  //검색키워드 target
                                if (index == -1)
                                {
                                    break;
                                }
                                strback = strback.Substring(index + 6);   //뒤
                                index2 = strback.IndexOf("</item>");  //검색키워드 target
                                hap = strback.Substring(0, index2); //키워드 짤라내기
                                hap += " / ";
                                chonghap = hap + chonghap;
                                strback = strback.Substring(index2 + 7); //
                            }
                            help = null;
                            help = new Help();

                            help.text(chonghap);

                            help.Show();
                           
                            text.Close();

                            break;
                        }
                    case "도움말 닫기":
                        {
                            help.Close();
                            break;
                        }
                    //target
                }
            }
            else
            {
                tts.SpeakAsync("저 말인가요?");
            }
            if (Cur_process == null)
            {
                return;
            }
            //응용프로그램 제어코드
            if (Cur_process.ProcessName!=null)
            {
                if(Cur_process.ProcessName.Equals("calc2"))
                {
                    MyCal(e.Result.Text, Cur_process, currentProcessHandle);
                }
                else if(Cur_process.ProcessName.Equals("wmplayer"))
                {
                    MyMediaPlayer(Cur_process, currentProcessHandle, e.Result.Text);
                }
               
            }
            


        }
        
       
        //계산기 입력용 명령
        CalProcess calculator=null;
        private void MyCal(string con,Process myProc, int myProcHdl)      
        {
            //con은 음성명령에서 넘어온 명령어
            //CalProcess(Process _proc,int _hwnd)
            if (calculator==null)
            {
                calculator = new CalProcess(myProc, myProcHdl);
            }
            
            calculator.Action(con);
            time = 20;
        }

        //플레이어 입력용 명령
        MediaProcess player = null;
        private void MyMediaPlayer(Process myProc, int myProcHdl,string con)  
        {
            //con은 음성명령에서 넘어온 명령어
            if(player==null)
            {
                player = new MediaProcess(myProc, myProcHdl);
            }
            player.Action(con);
            time = 20;
        }
        #endregion

        #region 프로세스 실행/종료
        // 프로세스 실행
        private void doProgram(string filename, string arg)
        {
            ProcessStartInfo psi;
            if (arg.Length != 0)
                psi = new ProcessStartInfo(filename, arg);
            else
                psi = new ProcessStartInfo(filename);

            Cur_process = Process.Start(psi);

        }

        // 프로세스 종료
        private void closeProcess(string filename)
        {
            Process[] myProcesses;
            // Returns array containing all instances of Notepad.
            myProcesses = Process.GetProcessesByName(filename);
            foreach (Process myProcess in myProcesses)
            {
                myProcess.CloseMainWindow();
            }
        }
        #endregion
    }
}
