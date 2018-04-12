using System;
using System.Collections.Generic;
using System.Runtime.Remoting.Messaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace ConsoleApp9
{
    

    class Program
    {
        static void Main(string[] args)
        {
            Result result = new Result();

            Control con = Control.Instance();
            con.DataInit();
            con.Login2(result.SendResult, "11", "11");




            //NewMethod1();
            //NewMethod();

        }

        //내가 호출하고 -> 결과는 다른사람에게 전달해라.
        private static void NewMethod1()
        {
            Result result = new Result();

            Control con = Control.Instance();
            con.DataInit();
            con.Login1(result, "11", "11");
        }

        //내가 호출 -> 내가 결과 획득
        private static void NewMethod()
        {
            Control con = Control.Instance();
            con.DataInit();

            Member mem = con.Login("11", "11");
            if (mem != null)
            {
                Console.WriteLine(mem);
            }
        }
    }
}
