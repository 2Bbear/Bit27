using System;
using System.Collections.Generic;
using System.Text;

namespace _0409_Account
{
    class Account
    {
        private int id=0;
        private string name=String.Empty;
        private int balance=0;
        private static int s_id;

        #region Member Property
        public int Id { get{ return id; } private set => id = value; }

        public string Name { get { return name; } private set => name = value; }
        public int Balance { get { return balance; } private set => balance = value; }

        #endregion

        #region Constructor
        public Account(String _name,int _balance)
        {
            this.id = s_id;
            s_id = s_id + 10;

            this.Name = _name;
            this.Balance = _balance;
        }
        /*
         정적 멤버 변수를 초기화
         딱 한번만 호출하기 위해 사용함
         매개변수가 있을 수가 없다.
             */
        static Account()
        {
            s_id = 1000;
        }
        #endregion

        #region Method
        public virtual void AddMoney(int money)
        {
            if(money<0)
            {
                //c++ 코드 예외처리 방법
                throw new Exception("마이너스 값 입금 불가");
            }
            Balance += money;
        }
        public void MinMoney(int money)
        {
            if(money<0)
            {
                throw new Exception("마이너스 값 출금 불가");
            }
            if (Balance < money)
            {
                //c++ 코드 예외처리 방법
                throw new Exception("잔액이 부족합니다.");
            }
            Balance -= money;
        }
      
        #endregion

        #region Override Method
        public override string ToString()
        {
            String result=string.Empty;
            result = "[ID]" + this.id + "\t";
            result+="[NAME]"+this.name + "\t";
            result += "[BALANCE]" + this.balance+"\t" ;
            return result;
        }
        #endregion

    }
}
