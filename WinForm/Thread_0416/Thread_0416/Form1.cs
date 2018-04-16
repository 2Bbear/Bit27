using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;

namespace Thread_0416
{
    public partial class Form1 : Form
    {
        //public static void Print1()
        //{
        //    MessageBox.Show("첫번째 Thread...");
           
        //}
        //public void Print2()
        //{
        //    MessageBox.Show("두번째 Thread...");
        //}
        ////이거 실행시키면 개판된다.
        //public void Test()
        //{

        //    // 스레드 생성
        //    // ThreadStart 델리게이트를 이용해 static 매서드인 Print1 등록
        //    Thread thread = new Thread(new ThreadStart(Print1));

        //    // 스레드 실행
        //    thread.Start();

        //    // 스레드 생성
        //    // static 형태가 아닌 메서드일 경우 
        //    // new 연산자를 이용해 인스턴스를 만든 후 ThreadStart 델리게이트
        //    // 에 등록
        //    thread = new Thread(new ThreadStart((new Form1()).Print2));

        //    thread.Start();


        //    MessageBox.Show("세번째 Thread...");
        //}


        static int i = 0;

        // 첫번째 스레드
        public static void Print1(object obj)
        {
            for (i = 0; i < 3; i++)
            {
             
                listBox1.Items.Add(String.Format("첫번째 Thread : {0} ***", i));
                Thread.Sleep(100);
            }
        }

        // 두번째 스레드
        public void Print2(object obj)
        {
            for (i = 0; i < 3; i++)
            {
                listBox1.Items.Add(String.Format("두번째 Thread : {0} ***", i));
               
                Thread.Sleep(100);
            }
        }


        public void Test2()
        {
            //// static method를 이용한 ThreadPool에대한 작업 요청
            //ThreadPool.QueueUserWorkItem(new WaitCallback(Print1), null);

            // method를 이용한 ThreadPool에대한 작업 요청
            ThreadPool.QueueUserWorkItem(new WaitCallback(
                (new Form1()).Print2), null);

            for (int i = 0; i < 10; i++)
            {
                listBox1.Items.Add(String.Format("main : {0}", i));
                
                Thread.Sleep(100);

            }

        }
        public Form1()
        {
            InitializeComponent();
           
            Test2();
        }
    }
}
