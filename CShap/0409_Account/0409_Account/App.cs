using System;
using System.Collections.Generic;
using System.Text;

namespace _0409_Account
{
    enum Menu {
        DEFAULT=0,
        INSERTACC = ConsoleKey.F1,
        SELECTACC = ConsoleKey.F2,
        INPUTACC = ConsoleKey.F3,
        OUTPUTACC = ConsoleKey.F4,
        DELETEACC = ConsoleKey.F5,
        PRINTACC = ConsoleKey.F6,
        PRINTFAITHACC = ConsoleKey.F7,
        PRINTCONTRIACC = ConsoleKey.F8,
        EXIT = ConsoleKey.Escape
    };
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
                switch((Menu)WbPrint.MenuPrint())
                {
                    case Menu.INSERTACC: { bank.Insert_Account(); break; }
                    case Menu.SELECTACC: { bank.Select_Account(); break; }
                    case Menu.INPUTACC: { bank.Input_Account(); break; }
                    case Menu.OUTPUTACC: { bank.Output_Account(); break; }
                    case Menu.DELETEACC: { bank.Delete_Account(); break; }
                    case Menu.PRINTACC: { bank.PrintAcc_Account(); break; }
                    case Menu.PRINTFAITHACC: { bank.PrintFaith_Account(); break; }
                    case Menu.PRINTCONTRIACC: { bank.PrintContri_Account(); break; }
                    case Menu.EXIT: { return; }



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
