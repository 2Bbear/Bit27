using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Account2_0412
{
    class AccountProcess
    {
        public void InsertAccount()
        {
            Console.Write("이름 : ");
            String name = Console.ReadLine();

            Console.Write("입금액 : ");
            int balance = int.Parse(Console.ReadLine());

            Bank bank = Bank.Singletone;
            if(bank.InsertAccount(name, balance))
            {
                Console.WriteLine("저장성공");
            }
            else
            {
                Console.WriteLine("저장실패");
            }


        }

        public void SelectAllAccount()
        {
            Bank.Singletone.SelectAllAccount();
        }
        public void InputAccount()
        {
            Console.Write("계좌번호 : ");
            int sid = int.Parse(Console.ReadLine());
            Console.Write("입금액 : ");
            int money = int.Parse(Console.ReadLine());

           
            if (Bank.Singletone.InputAccount(sid, money))
            {
                Console.WriteLine("입금성공");
            }
            else
            {
                Console.WriteLine("입금실패");
            }
        }

    }
}
