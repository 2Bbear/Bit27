using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Account2_0412
{
    class Bank
    {
        #region singletone
        static Bank singletone;

        public static Bank Singletone { get => singletone; private set => singletone = value; }


        static Bank()
        {
            singletone = new Bank();
        }

        private Bank()
        {

        }

        #endregion

        #region attribute
        Dictionary<int, Account> acclist=new Dictionary<int, Account>();
        #endregion

        public event InsertEvent InsertAcc = null;
        public event PrintAllEvent PrintAll = null;
        public event InputAccountEvent InputAcc = null;

        #region methode
        //insert 이벤트가 발생했다.
        public bool InsertAccount( String name, int balance)
        {
            Random r = new Random();
            //id 중복 문제 발생
            int accid =r.Next(1000,2000);
            if(acclist.ContainsKey(accid))
            {
                return false;
            }
            //이벤트 핸들러 호출
            Account acc= new Account(accid, name, balance);
            acclist[accid] = acc;
            if(InsertAcc != null)
            {
                //호출
                InsertAcc(this, new InsertAccountEventArgs(acc));  
            }
            return true;
        }

        public void SelectAllAccount()
        {
            foreach(KeyValuePair<int,Account> acckey in acclist)
            {
                Console.WriteLine(acckey.Value);
                if (PrintAll != null)
                {
                    //PrintAll(this, new PrintAllEvent());
                }
            }
        }

        public bool InputAccount(int sid, int money)
        {
            if(acclist.ContainsKey(sid))
            {
                acclist[sid].AddMoney(money);
                if (InputAcc != null)
                {
                    InputAcc(this, new InputAccountLogEventArgs(acclist[sid], money));
                }
                return true;
            }
            return false;
        }


        #endregion

    }
}
