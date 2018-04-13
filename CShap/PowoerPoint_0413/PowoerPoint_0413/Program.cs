using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PowoerPoint_0413
{
    class Application
    {
        #region SingleTonePathern
        private static Application singleTone;

        public static Application SingleTone { get => singleTone; set => singleTone = value; }

        private Application() { }
        static Application()
        {
            SingleTone = new Application();
        }
        #endregion


        #region Method
        public void Init()
        {
            Control cc = Control.SingleTone;
            PowerPointLog tt = PowerPointLog.Singletone;
            
        }
        public void Run()
        {
            while(true)
            {
                Console.Clear();
                Pptproces ppt = new Pptproces();
                ppt.PrintPPT();
               
              
                switch (MenuPrint())
                {
                        //Console.WriteLine("[0]파일 선택");
                    case ConsoleKey.D0:
                        {
                            ppt.Selectppt();
                            break;
                        }
                    //Console.WriteLine("[1]파일 생성");
                    case ConsoleKey.D1:
                        {
                            ppt.Createppt();
                            break;
                        }
                        // Console.WriteLine("[2]파일 불러오기");
                    case ConsoleKey.D2:
                        {
                            break;
                        }
                        // Console.WriteLine("[3]편집");
                    case ConsoleKey.D3:
                        {
                            ppt.Editppt();
                            break;
                        }
                        // Console.WriteLine("[4]랜덤페이지 이동");//숫자를 누르면 해당 페이지로 이동
                    case ConsoleKey.D4:
                        {
                            ppt.SelectCurPage();
                            break;
                        }
                    // Console.WriteLine("[5]프레젠테이션 실행");
                    case ConsoleKey.D5:
                        {
                            ppt.Runppt();
                            break;
                        }
                        //Console.WriteLine("[Down/Enter]다음 페이지");
                    case ConsoleKey.Enter:
                    case ConsoleKey.DownArrow:
                        {
                            ppt.NextPage();
                            break;
                        }
                        //Console.WriteLine("[Up]이전 페이지");
                    case ConsoleKey.UpArrow:
                        {
                            ppt.PrevPage();
                            break;
                        }
                        // Console.WriteLine("[ESC]프레젠테이션 종료");
                    case ConsoleKey.Escape:
                        {
                            ppt.Stopppt();
                            break;
                        }
                        // Console.WriteLine("[0]프로그램 종료");
                    case ConsoleKey.End:
                        {
                          
                            return;
                        }
                    
                    default:
                        break;
                }

            }

        }
        public void End()
        {
            Console.WriteLine("프로그램 종료");
        }

        ConsoleKey MenuPrint()
        {
            Console.WriteLine("++++++++++++++++++++++++++++++++++++");
            Console.WriteLine("[0]파일 선택");
            Console.WriteLine("[1]파일 생성");
            Console.WriteLine("[2]파일 불러오기");
            Console.WriteLine("[3]편집");
            Console.WriteLine("[4]랜덤페이지 이동");//숫자를 누르면 해당 페이지로 이동
            Console.WriteLine("[5]프레젠테이션 실행");
            Console.WriteLine("[Down/Enter]다음 페이지");
            Console.WriteLine("[Up]이전 페이지");
            Console.WriteLine("[ESC]프레젠테이션 종료");
            Console.WriteLine("[end]프로그램 종료");
            Console.WriteLine("++++++++++++++++++++++++++++++++++++");

            return Console.ReadKey().Key;
        }
        #endregion
    }

    class Program
    {
        static void Main(string[] args)
        {
            Application app= Application.SingleTone;
            app.Init();
            app.Run();
            app.End();
        }
    }
}
