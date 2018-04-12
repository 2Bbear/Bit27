using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Account2_0412
{
    public class Account
    {
        private int accid;
        private string name;
        private int balance;

        public int Accid { get => accid; private set => accid = value; }
        public string Name { get => name; private set => name = value; }
        public int Balance { get => balance; private set => balance = value; }

        //private static int s_id = 1000;
        public Account(int accid ,string name, int balance)
        {
           
            Name = name;
            Balance = balance;
            Accid = accid;
        }

        public Account(int accid ,string name)
        {
           
            Name = name;
            Balance = 0;
            Accid = accid;
        }
        public void AddMoney(int money)
        {
            Balance += money;
        }
        public override string ToString()
        {
            String temp = "[" + Accid + "]";
            temp += Name + " ";
            temp += Balance + "원";
            return temp;
        }
    }
}
