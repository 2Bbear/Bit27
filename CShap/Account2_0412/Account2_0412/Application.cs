using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Account2_0412
{
    class Application
    {
        #region attribute
        private static Application sington;

        #endregion

        public static Application Sington { get => sington; private set => sington = value; }


        private Application()
        {
        }
        static Application()
        {
            sington = new Application();
        }

        AccountProcess ap = new AccountProcess();
        
        #region method
        public void Init()
        {
            //이벤트 바인딩
            AccountLog alog = AccountLog.Singletone;
        }
        public void Run()
        {
            while(true)
            {
                Console.Clear();
                ap.SelectAllAccount();
                
                switch (MenuPrint())
                { 
                    case ConsoleKey.D1:
                        {
                            ap.InsertAccount();
                            break;
                        }
                    case ConsoleKey.D2:
                        {
                            
                            break;
                        }
                    case ConsoleKey.D3:
                        {
                            break;
                        }
                    case ConsoleKey.D4:
                        {
                           
                            break;
                        }
                    case ConsoleKey.D5:
                        {
                            ap.InputAccount();
                            break;
                        }
                    case ConsoleKey.Escape:
                        {
                            return;
                        }
                }
                Console.WriteLine(">>아무키나 누르세요");
                Console.ReadKey();

            }
        }

        public ConsoleKey MenuPrint()
        {
            Console.WriteLine("****************************************");
            Console.WriteLine("[1] 계좌생성");
            Console.WriteLine("[2] 계좌검색");
            Console.WriteLine("[3] 계좌삭제");
            Console.WriteLine("[4] 계좌수정");
            Console.WriteLine("[5] 계좌입금");
            Console.WriteLine("[6] 계좌출금");
            Console.WriteLine("[ESC] 종료");

            Console.WriteLine("****************************************");
            return Console.ReadKey().Key;
        }

       
        #endregion


    }
}
