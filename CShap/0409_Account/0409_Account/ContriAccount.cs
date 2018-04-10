using System;
using System.Collections.Generic;
using System.Text;

namespace _0409_Account
{
    class ContriAccount : Account
    {
        public int Contribution { get; private set; }


        //Constuctor
        public ContriAccount(String name, int balance) :base(name, (int)(balance - balance * 0.01))
        {
            Contribution = (int)(balance * 0.01);
        }

        //override
        public override void AddMoney(int money)
        {
            if (money < 0)
            {
                //c++ 코드 예외처리 방법
                throw new Exception("마이너스 값 입금 불가");
            }
            base.AddMoney((int)(money - money * 0.01));
            Contribution += (int)(money * 0.01);
        }

        public override string ToString()
        {
            string temp = base.ToString();
            temp = "[CONTRIBUTION]" + this.Contribution;

            return temp;
        }
    }
}
