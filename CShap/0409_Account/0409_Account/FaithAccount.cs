using System;
using System.Collections.Generic;
using System.Text;

namespace _0409_Account
{
    class FaithAccount : Account
    {
        //Costructor
        public FaithAccount(String name,int balance):base(name,(int)(balance+balance*0.01))
        {

        }

        //override
        public override void AddMoney(int money)
        {
            if (money < 0)
            {
                //c++ 코드 예외처리 방법
                throw new Exception("마이너스 값 입금 불가");
            }
            base.AddMoney((int)(money + money * 0.01));
        }
    }
}
