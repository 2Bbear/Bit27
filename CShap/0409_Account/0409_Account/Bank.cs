using System;
using System.Collections.Generic;
using System.Text;

namespace _0409_Account
{
    class Bank
    {
        private Account[] acclist;
        private int size;
        private int max;
        //Controuctor
        public Bank(int _max)
        {
            acclist = new Account[_max];
            size = 0;
            max = _max;
        }


        //Method
        public void Insert_Account()
        {
            Console.Write("[이름] ");
            String name = Console.ReadLine();
            Console.Write("[입금액] ");
            int money = int.Parse(Console.ReadLine());

            Account acc = new Account(name, money);

            acclist[size] = acc;
            size++;
            Console.WriteLine(">>저장되었습니다.");
        }
        public void SelectAll_Account()
        {
            foreach(Account acc in acclist)
            {
                Console.WriteLine(acc);
            }
        }
        public void Select_Account()
        {
            Console.Write("[검색할 계좌의 고객명]");
            String name = Console.ReadLine();
            Account acc = NameToAccount(name);
            if(acc==null)
            {
                Console.WriteLine ("해당 계좌가 없습니다.");
                return;
            }
            Console.WriteLine("");
            //error
        }
        public void Delete_Account()
        {
            Console.Write("[삭제할 계좌의 고객명]");
            String name = Console.ReadLine();
            int idx = NameToIdx(name);
            if (idx == -1)
            {
                Console.WriteLine("해당 계좌가 없습니다.");
                return;
            }
            //배열 삭제
            for(int i =idx;i<size ;i++)
            {
                acclist[i] = acclist[i + 1];
            }
            size--;
           
        }
        public void Input_Account()
        {
            Console.Write("[입금 계좌 고객명]");
            string name = Console.ReadLine();
            Account acc = NameToAccount(name);
            if(acc==null)
            {
                Console.WriteLine("해당 계좌가 없습니다.");
                return;
            }
            try
            {
                Console.Write("[입금액] ");
                int money = int.Parse(Console.ReadLine());
                if(money<=0)
                {
                    throw new Exception("입금액이 0이거나 숫자가 아닙니다.");
                }
                acc.AddMoney(money);
                Console.WriteLine("입금 성공.");
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
        public void Output_Account()
        {
            Console.Write("[출금 계좌 고객명]");
            string name = Console.ReadLine();
            Account acc = NameToAccount(name);
            if (acc == null)
            {
                Console.WriteLine("출금 계좌가 없습니다.");
                return;
            }
            try
            {
                Console.Write("[출금액] ");
                int money = int.Parse(Console.ReadLine());
                if (money <= 0)
                {
                    throw new Exception("출금액이 0이거나 숫자가 아닙니다.");
                }
                acc.MinMoney(money);
                Console.WriteLine("출금 성공.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
        private Account NameToAccount(String name)
        {
            foreach(Account acc in acclist)
            {
                if(acc.Name==name)
                {
                    return acc;
                }
            }
            return null;
        }
        private int NameToIdx(string name)
        {
           for(int i =0;i<size ;i++)
            {
                Account acc = acclist[i];
                if(acc.Name.Equals(name))
                {
                    return i;
                }
            }
            return -1;
        }
    }
}
