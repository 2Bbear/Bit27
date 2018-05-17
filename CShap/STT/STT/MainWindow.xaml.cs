using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using Microsoft.Speech.Recognition;
using Microsoft.Speech.Synthesis;
using System.Diagnostics;
using System.Threading;
using System.Globalization;
using System.Windows.Forms;
using System.Runtime.InteropServices;



namespace STT
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        [DllImport("user32.dll", SetLastError = true)]
        private static extern IntPtr FindWindow(string lpClassName, string lpWindowName);
        [DllImport("User32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int uMsg, int wParam, string lParam);
        [DllImport("user32.dll")]
        public static extern IntPtr FindWindowEx(IntPtr hwndParent, IntPtr hwndChildAfter, string lpszClass, string lpszWindow);


        SpeechSynthesizer tts;

        private void SetRegister()
        {
            bool enable = true;
            // 시작프로그램에 등록하는 레지스트리
            string runkey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
            Microsoft.Win32.RegistryKey startupekey = Microsoft.Win32.Registry.LocalMachine.OpenSubKey(runkey);

            if (enable)
            {
                if (startupekey.GetValue("StartTest") == null)
                {
                    startupekey.Close();
                    startupekey = Microsoft.Win32.Registry.LocalMachine.OpenSubKey(runkey, true);
                    startupekey.SetValue("StartTest", System.Windows.Forms.Application.ExecutablePath.ToString());
                    startupekey.Close();
                    System.Windows.MessageBox.Show("성공");
                }
                else
                {
                    Thread.Sleep(2000);
                    System.Windows.MessageBox.Show("이미등록이 되어 있습니다.");
                   
                }
            }
            else
                System.Windows.MessageBox.Show("실패");

        }
        private void DisRegister()
        {
            bool enable = false;
            try
            {
                string runkey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
                Microsoft.Win32.RegistryKey startupekey = Microsoft.Win32.Registry.LocalMachine.OpenSubKey(runkey);

                if (enable)
                {
                    if (startupekey.GetValue("StartTest") != null)
                    {
                        startupekey.DeleteValue("StartTest", false);
                        startupekey.Close();
                    }
                }

                System.Windows.MessageBox.Show("성공");
            }
            catch (Exception error)
            {
                System.Windows.MessageBox.Show(error.Message);
            }
        }



        public MainWindow()
        {
            
            InitializeComponent();
            //DisRegister();
            initRS();
            
            initTTS();
            
        }
        private void Soem()
        {
            try
            {
                SpeechRecognitionEngine sre = new SpeechRecognitionEngine(new CultureInfo("ko-KR"));
                Grammar g = new Grammar("input.xml");
                //Grammar g = new Grammar("input.xml");
                //Grammar g = new Grammar("myKo-KR.xml");
                sre.LoadGrammar(g);


                sre.SpeechRecognized += new EventHandler<SpeechRecognizedEventArgs>(sre_SpeechRecognized);
                sre.SetInputToDefaultAudioDevice();
                sre.RecognizeAsync(RecognizeMode.Multiple);
            }
            catch (Exception e)
            {
                label1.Content = "init RS Error : " + e.ToString();
            }
        }
        public void initRS()
        {
            try
            {
                SpeechRecognitionEngine sre = new SpeechRecognitionEngine(new CultureInfo("ko-KR"));
                Grammar g = new Grammar("input.xml");
                //Grammar g = new Grammar("input.xml");
                //Grammar g = new Grammar("myKo-KR.xml");
                sre.LoadGrammar(g);
                
                
                sre.SpeechRecognized += new EventHandler<SpeechRecognizedEventArgs>(sre_SpeechRecognized);
                sre.SetInputToDefaultAudioDevice();
                sre.RecognizeAsync(RecognizeMode.Multiple);
            }
            catch (Exception e)
            {
                label1.Content = "init RS Error : " + e.ToString();
            }
        }
        public void initTTS()
        {
            try
            {
                tts = new SpeechSynthesizer();
                tts.SelectVoice("Microsoft Server Speech Text to Speech Voice (ko-KR, Heami)");
                tts.SetOutputToDefaultAudioDevice();
                tts.Volume = 100;
            }
            catch (Exception e)
            {
                label1.Content = "init TTS Error : " + e.ToString();
            }
        }
        void sre_SpeechRecognized(object sender, SpeechRecognizedEventArgs e)
        {
            label1.Content = e.Result.Text;

            switch (e.Result.Text)
            {
                case "컴퓨터":
                    tts.SpeakAsync("네 컴퓨터입니다");
                    break;

                case "안녕":
                    tts.SpeakAsync("반갑습니다 음성인식 테스터입니다");
                    break;

                case "종료":
                    {
                        tts.Speak("프로그램을 종료합니다");
                        this.Close();
                        break;
                    }

                case "계산기":
                    {
                        tts.SpeakAsync("계산기를 실행합니다");
                        doProgram("c:\\windows\\system32\\calc.exe", "");
                        break;
                    }

                case "메모장":
                    {
                        bool createdNew;

                        Mutex gM1 = new Mutex(true, "MyMutex", out createdNew);

                        if (createdNew)
                        {
                            
                            tts.SpeakAsync("메모장을 실행합니다");
                           
                            doProgram("c:\\windows\\system32\\notepad.exe", "");
                            gM1.ReleaseMutex();
                            temp.Refresh();
                            Thread.Sleep(500);
                            temp = Process.GetProcessesByName("notepad")[0];
                            IntPtr notepadTextbox = FindWindowEx(temp.MainWindowHandle, IntPtr.Zero, "Edit", null);
                            //this is a constant indicating the window that we want to send a text message
                            const int WM_SETTEXT = 0X000C;
                            //Thread.Sleep(2000);
                            SendMessage(notepadTextbox, WM_SETTEXT, 0, "This is the new Text!!!");
                            //반복



                        }
                        else
                            tts.SpeakAsync("메모장으로 이동합니다");
                        break;



                    }

                case "콘솔":
                    {
                        tts.SpeakAsync("콘솔을 실행합니다");
                        doProgram("c:\\windows\\system32\\cmd.exe", "");
                        break;
                    }

                case "그림판":
                    {
                        tts.SpeakAsync("그림판을 실행합니다");
                        doProgram("c:\\windows\\system32\\mspaint.exe", "");
                        break;
                    }

                case "계산기 닫기":
                    {
                        tts.SpeakAsync("계산기를 종료합니다");
                        closeProcess("calculator");
                        break;
                    }
                case "메모장 닫기":
                    {
                        tts.SpeakAsync("메모장을 종료합니다");
                        closeProcess("notepad");
                        break;
                    }

                case "콘솔 닫기":
                    {
                        tts.SpeakAsync("콘솔을 종료합니다");
                        closeProcess("cmd");
                        break;
                    }

            }
        }
        static Process temp;
        // 프로세스 실행
        private static void doProgram(string filename, string arg)
        {
            ProcessStartInfo psi;
            if (arg.Length != 0)
            {
                psi = new ProcessStartInfo(filename, arg);
            }
               
            else
                psi = new ProcessStartInfo(filename);


           
            temp =Process.Start(psi);
          

        }

        // 프로세스 종료
        private static void closeProcess(string filename)
        {
            Process[] myProcesses;
            // Returns array containing all instances of Notepad.
            myProcesses = Process.GetProcessesByName(filename);
            foreach (Process myProcess in myProcesses)
            {
                myProcess.CloseMainWindow();
            }
        }

    }
}
