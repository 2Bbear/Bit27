using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Account2_0412
{
   

    //이벤트 구독자
    class AccountLog
    {
        //======================수정 내용
        private static AccountLog singletone;

        internal static AccountLog Singletone { get => singletone; private set => singletone = value; }

        private AccountLog()
        {
            //바인딩
            Bank bank = Bank.Singletone;
            bank.InputAcc += InputAccountEventHandler;
            bank.InsertAcc += InsertAccEventHandler;
            bank.PrintAll += PrintAllEventHandler;
        }
        static AccountLog()
        {
            Singletone = new AccountLog();
        }

        //=======================
        //public AccountLog()
        //{
        //    //바인딩
        //    Bank bank = Bank.Singletone;
        //    bank.InputAcc += InputAccountEventHandler;
        //    bank.InsertAcc += InsertAccEventHandler;
        //    bank.PrintAll += PrintAllEventHandler;
        //}
        void InsertAccEventHandler(object obj,InsertAccountEventArgs e)
        {
            string str = string.Format(
               " [계좌생성로그] {0} 계좌 생성 / 생성시간 : {1}", e.Acc.Name, e.Logtime);
            Console.WriteLine(str);
            
           
        }
        void PrintAllEventHandler(object obj,PrintAllLogEventArgs e)
        {
            string str = string.Format(
               " [계좌출력로그] {0} 계좌 출력 / 계좌시간 : {1}", e.Acc.Name, e.Logtime);
            Console.WriteLine(str);

        }
        void InputAccountEventHandler(object obj,InputAccountLogEventArgs e)
        {
            string str = string.Format(
                " [입금로그] {0} 계좌 {1}원 입금", e.Acc.Accid, e.Acc.Balance);
            Console.WriteLine(str);
        }

    
    }
}
