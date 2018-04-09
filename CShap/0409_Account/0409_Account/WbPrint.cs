using System;
using System.Collections.Generic;
using System.Text;

namespace _0409_Account
{
    /// <summary>
    /// 출력 메서드를 static 형태로 갖고 있는 상태가 없는 클래스
    /// 상태가 없다 == 멤버가 없다.
    /// </summary>
    class WbPrint
    {
        public static ConsoleKey MenuPrint()
        {
           // System.Console.Clear();
            Console.WriteLine("**************************************");
            Console.WriteLine("[F1] 계좌 생성");
            Console.WriteLine("[F2] 계좌 검색");
            Console.WriteLine("[F3] 계좌 입금");
            Console.WriteLine("[F4] 계좌 출금");
            Console.WriteLine("[F5] 계좌 삭제");
            Console.WriteLine("[ESC] 프로그램 종료");
            Console.WriteLine("**************************************");
            return Console.ReadKey().Key;
        }
        public static void Logo()
        {
            System.Console.Clear();
            Console.WriteLine("**************************************");
            Console.WriteLine("C# 언어를 이용한 관리프로그램");
            Console.WriteLine("2018/04/09");
            Console.WriteLine("jjh");
            Console.WriteLine("**************************************");
            Pause();
        }
        public static void Ending()
        {
            System.Console.Clear();
            Console.WriteLine("**************************************");
            Console.WriteLine("Program close");
            Console.WriteLine("**************************************");
            Pause();
        }

        public static void Pause()
        {
            Console.Write("아무키나 누르세요....");

            Console.ReadKey();
            
        }
    }
}
