using System;
using System.Collections.Generic;
using System.Text;

namespace _0409_Account
{
    enum AccType { DEFAULT,ACCOUNT=1,FAITHACCOUNT,CONTRIACCOUNT};

    class Bank
    {
        private WbArray arrlist;
        //Controuctor
        public Bank(int _max)
        {
            arrlist = new WbArray(_max);
        }


        //Method
        public void Insert_Account()
        {
            Console.Write("[이름] ");
            String name = Console.ReadLine();
            Console.Write("[입금액] ");
            int money = int.Parse(Console.ReadLine());
            Console.Write("[계좌 종류(1:일반계좌 2: 신용계좌 3:기부계좌)]");
            AccType type = (AccType)(int.Parse(Console.ReadLine()));

            Account acc = null;
            if(type==  AccType.ACCOUNT)
            {
                acc = new Account(name, money);
            }
            else if (type == AccType.FAITHACCOUNT)
            {
                acc = new FaithAccount(name, money);
            }
            else if (type == AccType.CONTRIACCOUNT)
            {
                acc = new ContriAccount(name, money);
            }
            else 
            {
                Console.WriteLine("계좌 생성 실패");
                return;
            }
            

            try
            {
                arrlist.push_back(acc);
                Console.WriteLine(">>저장되었습니다.");
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
          

           
        }
        public void SelectAll_Account()
        {
            for(int i =0;i<arrlist.Size ;i++)
            {
                Account acc = (Account)arrlist[i];
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
            arrlist.erase(idx);
            Console.WriteLine("삭제되었습니다.");

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
              
                if (money<=0)
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
            for(int i=0;i<arrlist.Size;i++)
            {
                Account acc = (Account)arrlist[i];
                if(acc.Name==name)
                {
                    return acc;
                }
            }
            return null;
        }
        private int NameToIdx(string name)
        {
           for(int i =0;i<arrlist.Size ;i++)
            {
                Account acc = (Account)arrlist[i];
                if (acc.Name.Equals(name))
                {
                    return i;
                }
            }
            return -1;
        }

        public void PrintAcc_Account()
        {
            for (int i = 0; i < arrlist.Size; i++)
            {
                Account acc = (Account)arrlist[i];

                if(!(acc is FaithAccount)&& !(acc is ContriAccount))
                {
                    Console.WriteLine((FaithAccount)acc);
                }
            }
        }

        public void PrintFaith_Account()
        {
            for (int i = 0; i < arrlist.Size; i++)
            {
                Account acc = (Account)arrlist[i];
                
                if (acc is FaithAccount)
                {
                    Console.WriteLine((FaithAccount)acc);
                }

            }
        }

        public void PrintContri_Account()
        {
            for (int i = 0; i < arrlist.Size; i++)
            {
                Account acc = (Account)arrlist[i];
                ContriAccount conacc = acc as ContriAccount;
                if(conacc!=null)
                {
                    Console.WriteLine(conacc);
                }
                
            }
        }

    }
}
