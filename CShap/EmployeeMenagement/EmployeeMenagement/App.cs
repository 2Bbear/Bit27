using System;
using System.Collections.Generic;
using System.Text;

namespace EmployeeMenagement
{
    class App
    {

        #region Attribut
        static App me;

        #endregion

        #region Constructor
        private App()
        {

        }

        #endregion

        #region Method
        public static App GetInstance()
        {
            if (me == null)
            {
                me = new App();
            }
            return me;
        }
        public void Init()
        {

        }
        public void Run()
        {

        }
        public void Exit()
        {

        }

        //Private Method=============================
        private void PrintMenu()
        {
            Console.WriteLine("=================================");
            Console.WriteLine("1.사원등록");
            Console.WriteLine("2.사원검색");
            Console.WriteLine("3.사원수정");
            Console.WriteLine("4.사원삭제");
            Console.WriteLine("5.사원리스트 출력");
            Console.WriteLine("=================================");
        }
        private void Intro()
        {

        }
        private void Ending()
        {

        }
        #endregion




    }
}
