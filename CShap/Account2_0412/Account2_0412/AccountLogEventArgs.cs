using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Account2_0412
{/// <summary>
    /// Account의 로그 이벤트 인자
    /// </summary>
    public class InsertAccountEventArgs:EventArgs
    {
       
        private Account acc;
        private DateTime logtime;

        public Account Acc { get => acc; private set => acc = value; }
        public DateTime Logtime { get => logtime; private set => logtime = value; }

        public InsertAccountEventArgs(Account acc)
        { 
            Acc = acc;
            Logtime = DateTime.Now;
        }
    }
    
    public class PrintAllLogEventArgs : EventArgs
    {
       
        private Account acc;
        private DateTime logtime;

       
        public Account Acc { get => acc; private set => acc = value; }
        public DateTime Logtime { get => logtime; private set => logtime = value; }

        public PrintAllLogEventArgs(Account acc)
        {
            Acc = acc;
            Logtime = DateTime.Now;
        }



    }

    public class InputAccountLogEventArgs : EventArgs
    {
        private Account acc;
        private int money;
        private DateTime logtime;

        internal Account Acc { get => acc; private set => acc = value; }
        public int Money { get => money; set => money = value; }
        public DateTime Logtime { get => logtime; private set => logtime = value; }

        public InputAccountLogEventArgs(Account acc, int money)
        { 
            Acc = acc;
            Money = money;
            Logtime = DateTime.Now;
        }
    }

    public delegate void InsertEvent(object obj, InsertAccountEventArgs e);
    public delegate void PrintAllEvent(object obj, PrintAllLogEventArgs e);
    public delegate void InputAccountEvent(object obj, InputAccountLogEventArgs e);

}
