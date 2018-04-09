using System;
using System.Collections.Generic;
using System.Text;

namespace _0409_Account
{
    class App
    {

        private static App app;

        private Bank bank;

        //Constructor
        public static App Instance
        {
            get
            {
                return app;
            }
        }
       static  App()
        {
            app = new App();

        }
        private App()
        {
            Console.Write("[저장개수]");
            int max = int.Parse(Console.ReadLine());
            bank = new Bank(max);
        }

        //Method
        public void Init()
        {
            WbPrint.Logo();
        }
        public void Run()
        {
            while(true)
            {
                Console.Clear();
                bank.SelectAll_Account();
                switch(WbPrint.MenuPrint())
                {
                    case ConsoleKey.F1: { bank.Insert_Account(); break; }
                    case ConsoleKey.F2: { bank.Select_Account(); break; }
                    case ConsoleKey.F3: { bank.Input_Account(); break; }
                    case ConsoleKey.F4: { bank.Output_Account(); break; }
                    case ConsoleKey.F5: { bank.Delete_Account(); break; }
                    case ConsoleKey.Escape: { return; }



                }
                
                WbPrint.Pause();

            }
        }
        public void Exit()
        {
            WbPrint.Ending();
        }

    }
}
